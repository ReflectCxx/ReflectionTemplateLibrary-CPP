# RTL Reflection Call Overhead Analysis

## Overview

This document summarizes the flat overhead cost associated with using RTL's reflective call paths across all benchmarked call types. It categorizes overhead into **non-erased** and **erased** call paths and establishes upper and lower bounds observed across the entire test suite.

---

## Non-Erased RTL Calls (Fast Path)

### Summary

Non-erased calls (`rtl::function` / `rtl::method`) exhibit near-zero overhead in all realistic workloads and only minimal overhead in microbenchmarks.

### Overhead Range

* **Best case (real workloads):** Effectively *0 ns* overhead. Measurements match direct calls within noise.
* **Worst case (scale = 0):**

  * set: ~+0.4 ns overhead
  * get: ~+1.1 ns overhead
  * Relative cost: ~1.6×–1.8× direct call cost in pure overhead tests.

### Practical Interpretation

Non-erased RTL calls are effectively *free* for practical purposes and safe even for ultra-hot loops.

---

## Erased RTL Calls (Most Expensive Path)

### Absolute Worst Case (All Benchmarks)

The highest overhead observed occurs in fully erased `get` calls on trivial functions.

* **Fully Erased get:** ~+15–16 ns overhead
* **Relative:** ~12×–13× slower than direct
* **Condition:** Function body is trivial (scale = 0)

This is the *maximum possible overhead* identified.

### Typical Hotpath Overhead (Real Workload)

When the function performs meaningful computation (scale ≥ 5):

* **set:** +3–6% overhead
* **get:** +5–10% overhead
* **Erased target only:** +1–3% overhead, often nearly at parity with direct

### Practical Interpretation

Erased calls introduce a measurable cost in pure overhead scenarios, but once real work exists, the relative overhead becomes small and predictable.

---

## Flat Overhead Price Card

### Non-Erased RTL

* **Realistic Overhead:** 0–1 ns
* **Pathological Worst Case:** ~1.2 ns
* **Use Case:** Safe for ultra-hot loops; equivalent to direct calls and often faster than `std::function`.

### Erased RTL

* **Maximum Overhead Across All Tests:** ~16 ns
* **Realistic Overhead:** +3–10% per call
* **Target-Only Erasure:** +1–3%
* **Use Case:** Suitable for high-performance code unless the function body is trivial.

---

## One-Line Summary

Across all callables, RTL's overhead ranges from **effectively zero** (non-erased) to a **maximum of ~16 ns** (fully erased trivial calls), with real-world workloads sitting comfortably at **+3–10%** overhead for erased calls.
