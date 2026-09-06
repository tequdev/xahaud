#!/usr/bin/env python3
"""Compare the proposed HOOK_API_COST blocks of two RESULTS.md files (DESIGN §5).

usage: compare_results.py CANONICAL.md OTHER.md [--gate 1.5]

Prints one row per API with both values and their ratio, flags APIs outside
the gate, and emits a merged block: the canonical value unless the ratio is
outside the gate, in which case the larger of the two (protects validators).
"""
import re
import sys


def load(path):
    text = open(path).read()
    start = text.index("## Proposed HOOK_API_COST block")
    block = text[start:]
    out = {}
    order = []
    for m in re.finditer(r"HOOK_API_COST\((\w+), (\d+), ([^)]*)\)([^\n]*)", block):
        name, cost, amend, note = m.group(1), int(m.group(2)), m.group(3), m.group(4)
        if name in out:
            continue
        out[name] = (cost, amend, "unmeasured" in note)
        order.append(name)
    return out, order


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    gate = 1.5
    for a in sys.argv[1:]:
        if a.startswith("--gate="):
            gate = float(a.split("=", 1)[1])
    canon, order = load(args[0])
    other, _ = load(args[1])
    print(f"| API | {args[0]} | {args[1]} | ratio | verdict |")
    print("|---|---:|---:|---:|---|")
    merged = []
    flagged = 0
    for name in order:
        c, amend, unm = canon[name]
        o = other.get(name, (None, amend, True))[0]
        if unm or o is None or other[name][2]:
            merged.append((name, c, amend, "unmeasured"))
            print(f"| {name} | {c} | {o} | - | unmeasured |")
            continue
        ratio = o / c
        if ratio > gate or ratio < 1 / gate:
            flagged += 1
            chosen = max(c, o)
            verdict = f"outside {gate}x gate -> max {chosen}"
        else:
            chosen = c
            verdict = "ok"
        merged.append((name, chosen, amend, "" if chosen == c else "// cross-platform max"))
        print(f"| {name} | {c} | {o} | {ratio:.2f} | {verdict} |")
    print(f"\n{flagged} of {len(order)} APIs outside the {gate}x gate.\n")
    print("```")
    for name, cost, amend, note in merged:
        tail = f"  // {note}" if note == "unmeasured" else (f"  {note}" if note else "")
        print(f"HOOK_API_COST({name}, {cost}, {amend}){tail}")
    print("```")


if __name__ == "__main__":
    main()
