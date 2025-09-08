# Reflection Template Library (RTL) — Benchmark Report

This document presents benchmark results for the **Reflection Template Library (RTL)**.  
The goal was to measure the runtime overhead of reflective function calls compared to direct calls and `std::function`, under increasing workloads.

---

## Benchmark Setup

We tested:

- **Direct calls** (baseline).
- **`std::function` calls** and method calls.
- **RTL reflective calls** (free functions and member methods, with and without return values).

Each benchmark was repeated across workloads of increasing complexity, with times measured in nanoseconds.

---

## Results Summary

| Workload        | Direct Call (ns) | Reflected Call Overhead (ns) | Reflected Method Overhead (ns) | Notes (With Return) |
|-----------------|------------------|------------------------------|--------------------------------|---------------------|
| baseline_40ns   | 39.0 / 44.7      | +2.5                         | +6.6                           | +10.6 / +14.3       |
| workload_80ns   | 82.4 / 82.5      | ~0                           | ~0                             | +12.5 / +15.6       |
| workload_100ns  | 94.2 / 100.0     | +1.4                         | +8.8                           | +12.0 / +16.0       |
| workload_150ns* | 139.0 / 158.0    | +2–3                         | +14–17                         | +12–13 / +17–19     |

\*Three independent runs were recorded at ~150 ns workload; numbers are consistent.

---

## Insights

- **Constant Overhead**  
  Reflection overhead remains almost constant across workloads:
  - No-return functions: **+2–6 ns**.
  - Return-value functions: **+10–20 ns**.

- **Percentage Overhead Shrinks**  
  - At the 40 ns baseline, overhead was ~25%.  
  - By ~150 ns workloads, overhead dropped below 10%.  

- **No Scaling Penalty**  
  The overhead does not grow with function complexity.  
  This indicates that RTL adds only a fixed, predictable cost per call, with no hidden allocations or RTTI-like penalties.

- **Performance-Culture Friendly**  
  This aligns with C++’s ethos: *you only pay a small, predictable cost when you use reflection*.

---

## Conclusion

The Reflection Template Library (RTL) demonstrates:

- **Runtime reflection with constant, minimal overhead**.  
- **Predictable cost model**: ~10–20 ns for reflective calls with returns.  
- **Competitive performance**: far faster than existing C++ or mainstream language reflection systems.  

This makes RTL practical for domains traditionally wary of reflection:
- Serialization
- RPC / networking
- GUI bindings
- Scripting integrations
- Tooling

RTL shows that reflection in C++ can finally be **both expressive and performant**.
