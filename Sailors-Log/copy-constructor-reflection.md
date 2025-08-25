# RTL Design Evolution Log

## Entry: Restricting Direct Copy Constructor Calls in Reflection

**Date:** 2025-08-16
**Author:** Neeraj Singh

### Problem Context

In C++, copy constructors are universally available (unless explicitly deleted), but their **direct invocation is not semantically equivalent** to creating new objects via constructors. In most cases, if a programmer knows the type `T`, they would simply invoke `T()` or `T(other)` themselves. Reflection should not encourage redundant or confusing usage patterns.

During testing with POD types like `char`, it became clear that exposing direct copy constructor calls through `Record::create<>()` added no value and introduced ambiguity:

```cpp
optional<Record> charType = cxx::mirror().getRecord(reflected_id::char_t);
auto [err, rchar] = charType->create<rtl::alloc::Stack>('Q');
EXPECT_TRUE(err == rtl::error::SignatureMismatch);
```

The call above attempts to use the copy constructor signature for `char`. RTL rejects it with a `SignatureMismatch` error — **by design**.

### Design Decision

* **No direct copy constructor invocation via `Record::create<>()`.**

  * If the user knows the type `T`, they should construct it directly.
  * Reflection only steps in when type erasure or runtime indirection is needed.

* **Copy semantics are still fully supported, but in the right places:**

  * `RObject::clone<>()` uses the implicitly registered copy constructor safely.
  * `rtl::reflect(T)` lets you reflect an existing object (copy constructed into `RObject`) when you want to treat it as type-erased.

### Why This Matters

This design avoids feature-bloat while preserving clarity:

* Prevents **unintuitive misuse** of copy constructors through reflection.
* Ensures reflection remains a **tool for runtime type-erasure** and not a redundant duplication of normal C++ syntax.
* Keeps `Record::create<>()` semantically tied to *real object construction* (default or parameterized), not copying.
* Developers who need copying in a reflection context still have a direct and intuitive API: `clone()` or `reflect()`.

### Benefits

* **Clarity:** Users immediately understand what `create<>()` means — it *creates*, not *copies*.
* **Safety:** Avoids accidental misuse that could lead to semantic confusion.
* **Consistency:** Copying is consistently handled through `clone()` across all types.
* **Alignment with C++ Philosophy:** If you know the type, do it in plain C++; reflection is for when you don’t.

---

✅ **Final Rule:** `Record::create<>()` never binds to copy constructor overloads. Copy semantics are available only through `RObject::clone()` or `rtl::reflect(T)`.
