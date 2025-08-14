RTL Design Evolution Log
Milestone: RObjectUptr – Safe Ownership of Move-Only Types
Date: 2025-08-13
Author: Neeraj Singh

---

## Problem Context

While integrating `std::unique_ptr` support into `RObject` for storing move-only types, an issue surfaced:

* `std::any` requires the contained type to be CopyConstructible when using certain APIs or performing unintended copy operations.
* `std::unique_ptr` is move-only and cannot be copied, making it incompatible with `std::any` in some compilers (notably MSVC) at the construction step itself.

### Key Goal

Store move-only types (especially `std::unique_ptr<T>`) inside `RObject` without relying on compiler-specific quirks and without triggering copy construction.

---

## Initial Exploration

### Direct `std::any` Storage

* Works in GCC/Clang for some cases, but fails on MSVC during `std::any` construction.
* Behavior inconsistent across compilers — unacceptable for RTL’s cross-platform guarantee.

### Conditional Compilation

* Possible workaround, but introduces complexity and risk of platform divergence.
* Violates RTL’s design principle of consistent behavior across compilers.

---

## Final Design

A dedicated wrapper class — **RObjectUptr** — was introduced:

### Key Features

* Stores the move-only type directly in a safe, non-copyable wrapper.
* Enforces no accidental copy-construction within RTL internals.
* **All `std::any_cast` operations in RTL retrieve values only via `const T&`** — guaranteeing that no copies are ever made, even for copyable types.
* Allows `RObject` to hold and operate on move-only types transparently.
* No compiler-specific hacks; same code path for MSVC, GCC, and Clang.

---

## Core Design Decisions

1. **No Ownership Transfer in Copy Constructor**
   The wrapper ensures no implicit transfer or move in copy contexts — this avoids subtle ownership bugs.

2. **No `std::move` in Copy Constructor**
   Now a simple, safe, “harmless-looking” class — easier to maintain and audit.

3. **One Code Path for All Compilers**
   Consistency is a feature, not an afterthought.

---

## Benefits

* **Predictable Behavior:** Developers using RTL know that move-only types will *just work* without compiler-specific surprises.
* **Maintainability:** No preprocessor conditionals to juggle.
* **Safety First:** Internals of RTL can’t accidentally cause lifetime errors.
* **Extensibility:** Paves the way for storing other move-only, non-copyable types.
