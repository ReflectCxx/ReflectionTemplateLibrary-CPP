# RTL Performance Summary

This document provides a concise, evidence-backed overview of the runtime performance characteristics of **RTL**, derived from systematic microbenchmarking across multiple workload scales, CPU frequencies, and representative API designs.

## Benchmark Overview

The benchmark measures the cost of invoking functions that perform simple but realistic string work. Two variants are evaluated using the types `std::string_view` and `std::string`.

### Lightweight Workflow

* The input string of length 500 is passed by value as `std::string_view`.

* The function `set(std::string_view)` copies the argument. This copy is very lightweight, as it only contains a pointer and a size.

* The actual work performed is concatenating the passed string into a global `std::string` for a given number of iterations (the workload scale).

* The getter, `std::string_view get(std::string_view)`, follows the same flow, including the argument copy, and returns a `std::string_view` pointing to the globally stored string, which is again a lightweight object.

### Heavy Workflow

The dispatch setup of the heavy workflow is the same, except it uses `std::string` instead of `std::string_view`, which means:

* The input string is passed by value as `std::string` and is copied on every call. Both `set` and `get` perform this copy operation for a 500-character string, typically involving heap allocation.

* Each workload iteration concatenates this 500-character string into the global storage.

* The getter `std::string get(std::string)`, returns a full `std::string` copy of the stored value, which again requires heap allocation.

In both cases, the real work is dominated by string concatenation, allocation, and copying.
The benchmarks therefore highlight how different call paths—direct calls, `std::function`, `rtl::function`, and reflected calls—behave when meaningful work is present, rather than measuring dispatch overhead in isolation.

Workload scales tested: *0, 1, 5, 10, 15, 20, 25 … up to 150.*
> *All benchmarks were compiled with clang 21.1 using the compiler’s default optimization flags in release configuration.*

## Results with `std::string_view` workflow

#### Dispatch Overhead (Scale = 0)

| Call Path        | Typical Cost |
| ---------------- | ------------ |
| Direct call      | ~9–13 ns     |
| Function pointer | ~10–13 ns    |
| `std::function`  | ~10–13 ns    |
| `rtl::function`  | ~10–12 ns    |
| RTL (erased)     | ~14–32 ns    |

#### Moderate Workload (Scale = 5)

| Call Path        | Setter      | Getter      |
| ---------------- | ----------- | ----------- |
| Direct           | ~114 ns     | ~185–217 ns |
| Function pointer | ~114–115 ns | ~185–214 ns |
| `std::function`  | ~115 ns     | ~186–216 ns |
| `rtl::function`  | ~113–114 ns | ~185–215 ns |
| RTL (erased)     | ~117–123 ns | ~200–225 ns |

#### Key Observations

* `rtl::function` matches or outperforms `std::function`.
* Non-erased RTL calls are effectively zero-overhead.
* Erased return types introduce measurable but bounded overhead.
* Dispatch cost is quickly amortized once real work is present.

## Results with `std::string` workflow

#### Dispatch Overhead (Scale = 0)

| Call Path        | Typical Cost |
| ---------------- | ------------ |
| Direct call      | ~9–13 ns     |
| Function pointer | ~10–13 ns    |
| `std::function`  | ~10–13 ns    |
| `rtl::function`  | ~10–12 ns    |
| RTL (erased)     | ~14–32 ns    |

#### Heavy Workload (Scale = 25)

| Call Path        | Setter      | Getter      |
| ---------------- | ----------- | ----------- |
| Direct           | ~348–362 ns | ~741–761 ns |
| Function pointer | ~354–355 ns | ~744–749 ns |
| `std::function`  | ~348–362 ns | ~752–761 ns |
| `rtl::function`  | ~356 ns     | ~745 ns     |
| RTL (erased)     | ~355–363 ns | ~765–781 ns |

#### Key Observations

* Getter cost is significantly higher due to return-by-value.
* Memory allocation and copying dominate runtime.
* Reflection overhead becomes negligible in comparison.
* Even fully erased RTL calls remain within ~3–5% of direct calls.

## Key Insights

* `rtl::function` consistently matches or outperforms `std::function` across all workloads.
* Non-erased RTL calls behave like **near-zero-overhead abstractions**, comparable to raw function pointers.
* Type erasure introduces overhead, but the cost is **bounded and predictable**.
* Return-type erasure is more expensive than target-type erasure, especially for `std::string` return values.
* As workload size increases, **real work dominates dispatch overhead**.
* Memory allocation and string copying become the primary performance costs.
* Reflection does not distort scaling behavior or introduce nonlinear slowdowns.
* API design (value vs view semantics) has a larger performance impact than reflection itself.

## Raw benchmark logs

[benchmark_runs_string.log](docs/benchmark_runs_string.log)

[benchmark_runs_string_view.log](docs/benchmark_runs_string_view.log)