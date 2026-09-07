//------------------------------------------------------------------------------
/*
    This file is part of rippled: https://github.com/ripple/rippled

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#ifndef HOOK_BENCH_H_INCLUDED
#define HOOK_BENCH_H_INCLUDED

// This header only does anything when the hook_cost_bench CMake option is
// enabled (-DHOOK_COST_BENCH). It is used by the HookAPICost benchmark
// (docs/hook-api-cost/HookAPICost.md, src/test/app/HookAPICost_test.cpp) and must
// never affect a normal build: every symbol below is compiled out when the
// flag is off, except the empty namespace declaration.

#ifdef HOOK_COST_BENCH

#include <chrono>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace hook {
namespace bench {

inline std::uint64_t
nowNs()
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
               std::chrono::steady_clock::now().time_since_epoch())
        .count();
}

// One counter per hook API function (e.g. one per DEFINE_HOOK_FUNCTION).
// Registers itself into registry() on construction so snapshot() can walk
// every API without a separate manual list.
struct ApiCounter
{
    char const* name;
    std::uint64_t calls{0};
    std::uint64_t ns{0};

    explicit ApiCounter(char const* n) : name(n)
    {
        registry().push_back(this);
    }

    static std::vector<ApiCounter*>&
    registry()
    {
        static std::vector<ApiCounter*> r;
        return r;
    }
};

// Accumulated over all hook executions since the last reset().
struct ExecStat
{
    std::uint64_t ns{0};
    std::uint64_t instructions{0};
    std::uint64_t count{0};
};
inline ExecStat exec;

// finalizeHookState / finalizeHookResult: time the whole function, and count
// the synchronous side-effect items it produced (modified state entries /
// emitted transactions) so the per-call cost of state_set/emit can amortise
// this work (HookAPICost.md sec 2.1).
struct FinalizeStat
{
    std::uint64_t ns{0};
    std::uint64_t items{0};
    std::uint64_t count{0};
};
inline FinalizeStat finalizeState;
inline FinalizeStat finalizeResult;
// ApplyContext::checkInvariantsHelper's visit() over modified/inserted/
// erased ledger entries (review finding #5): Action::modify re-reads the
// base-ledger SLE per entry, unattributed until now. items = entries
// visited (any action), attributed to state_set/state_foreign_set rows.
inline FinalizeStat invariants;

struct Snapshot
{
    std::map<std::string, std::pair<std::uint64_t, std::uint64_t>>
        api;  // name -> {calls, ns}
    ExecStat exec;
    FinalizeStat finalizeState;
    FinalizeStat finalizeResult;
    FinalizeStat invariants;
};

inline Snapshot
snapshot()
{
    Snapshot s;
    for (auto* c : ApiCounter::registry())
        s.api[c->name] = {c->calls, c->ns};
    s.exec = bench::exec;
    s.finalizeState = bench::finalizeState;
    s.finalizeResult = bench::finalizeResult;
    s.invariants = bench::invariants;
    return s;
}

inline void
reset()
{
    for (auto* c : ApiCounter::registry())
    {
        c->calls = 0;
        c->ns = 0;
    }
    exec = ExecStat{};
    finalizeState = FinalizeStat{};
    finalizeResult = FinalizeStat{};
    invariants = FinalizeStat{};
}

// RAII helper: on destruction, adds elapsed ns to `stat.ns`, increments
// `stat.count`, and adds `items` (read at destruction time via pointer, so
// the caller can keep incrementing a local counter across the scope) to
// `stat.items`.
class FinalizeTimer
{
public:
    FinalizeTimer(FinalizeStat& stat, std::uint64_t const& items)
        : stat_(stat), items_(items), t0_(nowNs())
    {
    }

    ~FinalizeTimer()
    {
        stat_.ns += nowNs() - t0_;
        stat_.count++;
        stat_.items += items_;
    }

private:
    FinalizeStat& stat_;
    std::uint64_t const& items_;
    std::uint64_t t0_;
};

}  // namespace bench
}  // namespace hook

#else

namespace hook {
namespace bench {
}  // namespace bench
}  // namespace hook

#endif  // HOOK_COST_BENCH

#endif  // HOOK_BENCH_H_INCLUDED
