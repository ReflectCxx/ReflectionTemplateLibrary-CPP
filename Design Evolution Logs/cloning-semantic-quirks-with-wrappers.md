# RTL Design Evolution Log

## Milestone: Cloning Semantics — Unified Control with `rtl::copy`

**Date:** 2025-08-16
**Author:** Neeraj Singh

---

### Problem Context

Cloning objects inside RTL (`RObject`) originally had semantics tied only to value-copying. While this worked for most user-defined types, ambiguity and inconsistency emerged when dealing with **STL wrappers** such as `std::shared_ptr`, `std::unique_ptr`, and `std::optional`:

* Should cloning a wrapper clone the *wrapper itself* (shallow copy)?
* Or should it clone the *underlying contained type* (deep copy)?
* What happens when the contained type is **non-copyable**?
* How do we make this intuitive yet efficient for real-world use?

Performance concerns also came into play: deep-copying wrappers like `shared_ptr` in performance-critical applications would be wasteful when shallow-copy semantics (ref-count increments) are usually what developers expect.

### Early Exploration

1. **Default to Value Copy:**

   * Simple and safe.
   * But performance-heavy when working with smart pointers.
   * Non-intuitive: developers returning/consuming wrappers usually expect to work with the wrapper itself.

2. **Default to Wrapper Copy:**

   * Better aligned with performance and developer expectations for `shared_ptr` and `optional`.
   * But breaks intuition for cases where deep-copy of the underlying type was actually intended.

Neither extreme fully captured the range of C++-native expectations.

### Final Design

To reconcile the competing needs, a **two-axis control** was introduced:

```cpp
enum class alloc { Heap, Stack };
enum class copy  { Auto, Value, Wrapper };

template<rtl::alloc _allocOn, rtl::copy _copyTarget = rtl::copy::Auto>
std::pair<rtl::error, RObject> clone() const;
```

#### Modes of Operation

* **`copy::Value`**  → Force deep copy of the contained entity `T`.

  * Errors out with `TypeNotCopyConstructible` if `T`’s copy ctor is deleted.
  * Heap/stack behavior respected via `alloc`.

* **`copy::Wrapper`** → Copy the wrapper itself.

  * `std::shared_ptr` shallow-copy increments ref-count.
  * `std::unique_ptr` is forbidden (`TypeNotCopyConstructible`).
  * Heap allocation of wrapper is disallowed (`StlWrapperHeapAllocForbidden`).

* **`copy::Auto`** → Context-sensitive default:

  * If object was **RTL-allocated** (heap objects wrapped in `unique_ptr` internally): treat wrapper as transparent → **Value copy**.
  * If object is a **non-RTL wrapper** (e.g., obtained from user return value): treat wrapper as significant → **Wrapper copy**.

This provides an API that is **intuitive for developers**, while giving them control when they need it.

---

### Error Handling Philosophy

* **Fail Fast, No UB**: every illegal operation returns a clear `rtl::error`.

  * `error::EmptyRObject` if attempting to clone an empty `RObject`.
  * `error::NotWrapperType` if `Wrapper` mode is requested on non-wrapper.
  * `error::StlWrapperHeapAllocForbidden` if heap clone of wrapper is attempted.
  * `error::TypeNotCopyConstructible` if underlying entity is not copyable.
* No silent fallbacks — clarity is always preferred.

### Benefits

* **Performance-Aware Defaults**: `Auto` intelligently chooses between shallow and deep copy based on context.
* **C++-Native Intuition**: Mirrors how developers think about copying raw types vs. wrappers in day-to-day C++.
* **Explicit Overrides**: Power users can explicitly request deep or shallow copy.
* **Consistency & Safety**: No hidden behavior, all outcomes expressed via `rtl::error`.

### Example Use

```cpp
// Smart default: deep-copy value if RTL-allocated, else shallow-copy wrapper
auto [err0, copy0] = robj.clone<alloc::Stack, copy::Auto>();

// Explicit deep-copy
auto [err1, copy1] = robj.clone<alloc::Heap, copy::Value>();

// Explicit shallow-copy of shared_ptr wrapper
auto [err2, copy2] = robj.clone<alloc::Stack, copy::Wrapper>();
```

---

### Why This Matters

Reflection systems in C++ live at the intersection of **type safety**, **performance**, and **developer intuition**. By separating `alloc` and `copy` dimensions:

* RTL ensures **safe lifetime management**.
* Developers get **precise control** without boilerplate.
* The library avoids performance pitfalls while staying faithful to native C++ semantics.

This design resolves one of the most subtle challenges in runtime reflection — making **wrapper types transparent when desired, but still first-class citizens when needed**.
