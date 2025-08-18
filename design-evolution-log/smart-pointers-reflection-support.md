# RTL Design Evolution Log

## Milestone: Smart Pointer Reflection & Unwrap Semantics

**Date:** 2025-08-15
**Author:** Neeraj Singh

---

### Problem Context

While adding support for `std::unique_ptr`, `std::shared_ptr`, and `std::weak_ptr` to **RObject**, the challenge was to maintain:

* Full reflection transparency.
* Correct ownership semantics.
* Cross-compiler compatibility.
* Intuitive behavior that matches native C++ usage.

The goal: **Make working with reflected smart pointers feel as natural as working with them directly in C++.**

---

### Key Challenges

1. **Move-only types (`std::unique_ptr`)**

   * `std::any` requires `CopyConstructible` types in certain code paths.
   * Direct storage of `unique_ptr` in `std::any` can fail on MSVC.

2. **Shared ownership (`std::shared_ptr`)**

   * Reflection must preserve reference counts when passing between `RObject`s.

3. **Weak references (`std::weak_ptr`)**

   * Reflection must allow locking to create temporary usable objects without accidental ownership transfer.

4. **Developer intuition**

   * If you can do it in C++ normally, you should be able to do it via reflection — without unexpected surprises.

---

### Final Design

**1. Smart Pointer Storage**

* All heap-created objects in RTL are wrapped in `std::unique_ptr` internally.
* The underlying type `T` can be accessed either as `std::unique_ptr<T>` or directly as `T`.
* Deep-cloning from `unique_ptr` is the default when unwrapping.

**2. `RObjectUptr<T>` Wrapper**

* Bypasses `std::any`'s copy-constructor requirement.
* Stores move-only types safely.
* Preserves cross-compiler behavior.

**3. New Allocation Modes**

* `alloc::Heap` – Normal heap allocation.
* `alloc::Stack` – Stack allocation.
* `alloc::UnwrapOnHeap` – Deep-clone underlying type `T` from inside smart pointer into a new heap object.
* `alloc::UnwrapOnStack` – Deep-clone underlying type `T` from inside smart pointer into a new stack object.

**4. Transparent View Semantics**

* If you know the type, you can view as `T` or `std::unique_ptr<T>` directly.
* If you don't know the type, treating it as an opaque `RObject` is harmless — ownership rules are preserved.

---

### Why This Matters

In standard C++ development, handling smart pointers is muscle memory — you know when you can move, copy, or share. The **Unwrap-on-Heap/Stack** modes extend that instinct into reflection, allowing you to:

* Safely clone from `unique_ptr` without stealing ownership.
* Share `shared_ptr` across reflected calls.
* Lock and use `weak_ptr` without surprises.

The result: a **zero-friction reflection experience** where the developer’s mental model matches the runtime behavior.

---

### Benefits

* **Predictable behavior** — matches native C++ semantics.
* **Cross-platform consistency** — identical behavior on MSVC, GCC, and Clang.
* **Intuitive API** — unwrapping and cloning are explicit and intention-revealing.
* **Safe by default** — no accidental ownership leaks or lifetime bugs.

---

### Next Steps

* Expand test coverage for all combinations of smart pointer types and allocation modes.
* Document real-world usage patterns for devs unfamiliar with smart pointer internals.
* Add diagnostics when unwrapping fails due to inaccessible copy constructors.
