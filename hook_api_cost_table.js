#!/usr/bin/env node

const fs = require("fs");

const DEFAULT_INPUT = "build/hook_api_benchmark.csv";

function usage() {
  console.error(
    [
      "Usage: node hook_api_cost_table.js [--sort=p95-desc|name-asc] [csv-path]",
      "",
      "Reads hook_api_benchmark CSV output and writes the Hook API cost",
      "Markdown table to stdout. Cost columns use only successful API results",
      "(return_code >= 0, RC_ACCEPT, or RC_ROLLBACK); error calls are excluded.",
      "Terminal RC_ACCEPT/RC_ROLLBACK calls are included and reported separately.",
      "Relative costs are computed by the instrumented binary from",
      "WasmEdge_StatisticsGetInstrPerSecond(), not from full VM wall time.",
      "",
      "Sort options:",
      "",
      "  --sort=p95-desc   Sort by p95 descending. This is the default.",
      "  --sort=name-asc  Sort by API name ascending.",
      "",
      "To generate build/hook_api_benchmark.csv:",
      "",
      "  cmake -S . -B build -DHOOK_BENCHMARK=ON",
      "  cmake --build build --target rippled -j $(nproc)",
      "  build/rippled --unittest=SetHook0,SetHook1,SetHook2,SetHook3,SetHook4,SetHook5,SetHook6,SetHook7 --unittest-jobs $(nproc) --quiet > build/hook_api_benchmark_test.log 2> build/hook_api_benchmark_raw.log",
      "  rg '^hook_api_benchmark_' build/hook_api_benchmark_raw.log > build/hook_api_benchmark.csv",
      "",
      "After measuring, disable the benchmark instrumentation again:",
      "",
      "  cmake -S . -B build -DHOOK_BENCHMARK=OFF",
      "  cmake --build build --target rippled -j $(nproc)",
    ].join("\n")
  );
}

function parseCsvLine(line) {
  const fields = [];
  let field = "";
  let quoted = false;

  for (let i = 0; i < line.length; ++i) {
    const ch = line[i];
    if (quoted) {
      if (ch === '"') {
        if (line[i + 1] === '"') {
          field += '"';
          ++i;
        } else {
          quoted = false;
        }
      } else {
        field += ch;
      }
    } else if (ch === '"') {
      quoted = true;
    } else if (ch === ",") {
      fields.push(field);
      field = "";
    } else {
      field += ch;
    }
  }

  fields.push(field);
  return fields;
}

function weightedPercentile(values, percentile) {
  const totalWeight = values.reduce((sum, item) => sum + item.weight, 0);
  if (totalWeight === 0) {
    return null;
  }

  const target = (totalWeight * percentile) / 100;
  let seen = 0;
  for (const item of [...values].sort((a, b) => a.value - b.value)) {
    seen += item.weight;
    if (seen >= target) {
      return item.value;
    }
  }

  return values[values.length - 1].value;
}

function formatNumber(value) {
  return value === null || value === undefined ? "n/a" : value.toFixed(2);
}

function formatInteger(value) {
  return value.toLocaleString("en-US");
}

function confidence(entry) {
  if (entry.successCalls === 0) {
    return "n/a";
  }

  const p50 = weightedPercentile(entry.successRelativeCosts, 50);
  const p95 = weightedPercentile(entry.successRelativeCosts, 95);
  const spread = p50 > 0 ? p95 / p50 : Infinity;
  const executionSamples = entry.successRelativeCosts.length;

  if (entry.successCalls >= 1000 && executionSamples >= 50 && spread <= 8) {
    return "high";
  }
  if (entry.successCalls >= 100 && executionSamples >= 10 && spread <= 20) {
    return "medium";
  }
  return "low";
}

function makeEntry() {
  return {
    calls: 0,
    nanos: 0,
    successCalls: 0,
    successNanos: 0,
    errorCalls: 0,
    terminalCalls: 0,
    successRelativeCosts: [],
  };
}

function readApiRows(csvText) {
  let header = null;
  const rows = [];

  for (const line of csvText.split(/\r?\n/)) {
    if (!line.startsWith("hook_api_benchmark_api,")) {
      continue;
    }

    const fields = parseCsvLine(line);
    if (fields[1] === "name") {
      header = fields;
    } else if (header) {
      rows.push(fields);
    }
  }

  if (!header) {
    throw new Error("No hook_api_benchmark_api header found.");
  }

  const indexes = Object.fromEntries(header.map((name, index) => [name, index]));
  const required = [
    "name",
    "calls",
    "total_ns",
    "success_calls",
    "success_ns",
    "success_relative_cost",
    "error_calls",
    "terminal_calls",
  ];
  const missing = required.filter((name) => indexes[name] === undefined);
  if (missing.length) {
    throw new Error(`Missing CSV columns: ${missing.join(", ")}`);
  }

  return { rows, indexes };
}

function aggregate(rows, indexes) {
  const byApi = new Map();

  for (const row of rows) {
    const name = row[indexes.name];
    const entry = byApi.get(name) ?? makeEntry();
    const calls = Number(row[indexes.calls]);
    const nanos = Number(row[indexes.total_ns]);
    const successCalls = Number(row[indexes.success_calls]);
    const successNanos = Number(row[indexes.success_ns]);
    const errorCalls = Number(row[indexes.error_calls]);
    const terminalCalls = Number(row[indexes.terminal_calls]);

    entry.calls += calls;
    entry.nanos += nanos;
    entry.successCalls += successCalls;
    entry.successNanos += successNanos;
    entry.errorCalls += errorCalls;
    entry.terminalCalls += terminalCalls;

    if (successCalls > 0) {
      entry.successRelativeCosts.push({
        value: Number(row[indexes.success_relative_cost]),
        weight: successCalls,
      });
    }

    byApi.set(name, entry);
  }

  return byApi;
}

function compareRows(sort) {
  if (sort === "name-asc") {
    return (a, b) => a.name.localeCompare(b.name);
  }

  if (sort !== "p95-desc") {
    throw new Error(`Unsupported sort: ${sort}`);
  }

  return (a, b) => {
    if (a.p95 === null && b.p95 === null) {
      return a.name.localeCompare(b.name);
    }
    if (a.p95 === null) {
      return 1;
    }
    if (b.p95 === null) {
      return -1;
    }
    return b.p95 - a.p95 || a.name.localeCompare(b.name);
  };
}

function tableRows(byApi, sort) {
  return [...byApi.entries()]
    .map(([name, entry]) => {
      const totalWeight = entry.successRelativeCosts.reduce(
        (sum, item) => sum + item.weight,
        0
      );
      const mean =
        totalWeight > 0
          ? entry.successRelativeCosts.reduce(
              (sum, item) => sum + item.value * item.weight,
              0
            ) / totalWeight
          : null;

      return {
        name,
        entry,
        avgNanos:
          entry.successCalls > 0 ? entry.successNanos / entry.successCalls : null,
        mean,
        p50: weightedPercentile(entry.successRelativeCosts, 50),
        p80: weightedPercentile(entry.successRelativeCosts, 80),
        p95: weightedPercentile(entry.successRelativeCosts, 95),
        confidence: confidence(entry),
      };
    })
    .sort(compareRows(sort));
}

function writeMarkdownTable(rows) {
  console.log(
    "| API | success calls | avg ns/success | mean | p50 | p80 | p95 | errors | terminal | confidence |"
  );
  console.log("|---|---:|---:|---:|---:|---:|---:|---:|---:|---|");

  for (const row of rows) {
    const entry = row.entry;
    console.log(
      [
        `| \`${row.name}\``,
        formatInteger(entry.successCalls),
        formatNumber(row.avgNanos),
        formatNumber(row.mean),
        formatNumber(row.p50),
        formatNumber(row.p80),
        formatNumber(row.p95),
        formatInteger(entry.errorCalls),
        formatInteger(entry.terminalCalls),
        `${row.confidence} |`,
      ].join(" | ")
    );
  }
}

function main() {
  const args = process.argv.slice(2);
  if (args.includes("-h") || args.includes("--help")) {
    usage();
    return;
  }

  let sort = "p95-desc";
  const positional = [];
  for (const arg of args) {
    if (arg.startsWith("--sort=")) {
      sort = arg.slice("--sort=".length);
    } else {
      positional.push(arg);
    }
  }

  if (positional.length > 1) {
    throw new Error(`Unexpected arguments: ${positional.slice(1).join(" ")}`);
  }

  const input = positional[0] ?? DEFAULT_INPUT;
  const csvText = fs.readFileSync(input, "utf8");
  const { rows, indexes } = readApiRows(csvText);
  writeMarkdownTable(tableRows(aggregate(rows, indexes), sort));
}

try {
  main();
} catch (error) {
  console.error(`hook_api_cost_table.js: ${error.message}`);
  process.exitCode = 1;
}
