const fs = require("fs");

const input = fs.readFileSync(0, "utf8"); // 0 = stdin
console.log("stdin length:", input.length);
console.log(input);

if (input === undefined) {
  console.error('No output provided')
  process.exit(1)
}

const lines = input.split('\n')

const benchmarkLines = lines.filter(line => line.startsWith('| "') && line.endsWith('|'))

const benchmarkData = benchmarkLines.map(line => {
  const [_, api, count, totalTime, averageBasedCost, maxBasedCost] = line.split('|').map(item => item.trim().replace(/\"/g, ""), "")
  return {
    api,
    count: Number(count),
    totalTime: Number(totalTime),
    averageBasedCost: Number(averageBasedCost),
    maxBasedCost: Number(maxBasedCost),
  }
})

// console.log(benchmarkData)

const totalTime = benchmarkData.reduce((prev, curr) =>
  ({ ...prev, [curr.api]: parseInt(Math.max(curr.maxBasedCost, prev[curr.api] || 0)) }),
  {})

Object.entries(totalTime).sort((a, b) => a[0].localeCompare(b[0])).forEach(([api, maxBasedCost]) => {
  console.log(`${api},${maxBasedCost}`)
})
