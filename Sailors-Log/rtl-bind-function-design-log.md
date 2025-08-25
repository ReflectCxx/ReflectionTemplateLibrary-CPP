# Design Log: bind() — API semantics, purpose and usage

**Author:** Neeraj Singh
**Date:** 2025-08-25

---

## Overview

`bind()` is the central invocation API in RTL that expresses two responsibilities in one call:

1. **Target binding** — which runtime object (if any) the method should be invoked on.
2. **Argument forwarding policy** — how call-site arguments are to be forwarded (value, lvalue-ref, rvalue-ref, const-ref).

`bind()` therefore gives the user explicit control over *how* RTL should perceive the invocation context and *how* to forward arguments to resolve overloads correctly. This is essential in a C++ reflection system because value-category and constness affect overload selection and correctness.

---

## API Surface (conceptual)

```cpp
// Zero-argument form: no target, default forwarding
auto callSite = funcOrMethod->bind();

// Bind to an RObject target (by value) — used for instance methods
auto callSite = method->bind(RObject{...});

// Explicitly request treating the target as non-const
auto callSite = method->bind(rtl::constCast(RObject{...}));

// Template form: specify forwarding categories for parameters
auto callSite = func->bind<T1, T2, ...>(); // e.g. bind<Person&&, const char*&>()

// Combination: bind the target and specify forwarding
auto callSite = method->bind<T1, T2>(target);
```
---

## Accepted argument types for `bind()`

* `rtl::access::RObject` — binds the reflected object as the call target. This is the normal case for invoking instance methods.
* `rtl::constCast<RObject>&&` (or equivalent explicit wrapper) — signals to RTL: "treat this RObject as non-const for this call". This is an explicit, user-driven request to relax logical constness; if the RObject is *true-const*, the runtime rejects the attempt (`rtl::error::IllegalConstCast`).

`bind()` *only* accepts these target forms for instance binding. Passing other types as the target should be a compile-time error.

---

## Template parameter pack (perfect-forwarding control)

* `bind<Ts...>()` allows the caller to *explicitly declare the forwarding category* for each function parameter, e.g. `T`, `T&`, `T&&`, `const T&`.
* This is necessary because reflection cannot deduce value category from a runtime `any`-style container; when overload selection depends on rvalue vs lvalue, `bind<...>()` disambiguates the call.
* If omitted, RTL will attempt best-effort matching using available argument values; but some overloads (especially rvalue-ref overloads) require explicit `bind<T&&>()` to select.

---

## Semantics — how `bind()` interacts with RTL const model

* If binding an **RObject created by RTL** (logically-const):

  * Default behavior: bind the target as logically-const (no mutation). Overload resolution will prefer `const` overloads.
  * If `const` overload doesn't exist but a non-const overload does, RTL may internally perform a **safe logical `const_cast`** and call the non-const overload.
  * If caller explicitly uses `rtl::constCast(RObject)` in `bind()`, RTL will select the non-const overload when safe.

* If binding an **externally-provided true-const** RObject:

  * `bind()` preserves true constness. RTL will consider only `const` overloads.
  * If user calls `bind(rtl::constCast(robj))`, RTL will reject with `rtl::error::IllegalConstCast`.

* For **static functions**, the object-target passed to `bind()` is ignored (becomes a sink). However, `bind<Ts...>()` still controls perfect-forwarding for parameters.

---

## Error behavior and diagnostics

* `rtl::error::ConstCallViolation` — raised when a non-const method is attempted on a true-const object without constCast.
* `rtl::error::IllegalConstCast` — raised when user explicitly requests a constCast on a true-const object.
* `rtl::error::ConstOverloadMissing` — raised when a true-const object has no const overload to call.
* `rtl::error::SignatureMismatch` — raised when the forwarded argument types do not match any registered signature.

Design note: `bind()` should validate as early as possible (during `bind()` return or immediately on `.call()` entry) and provide clear diagnostics. In debug builds provide helpful messages; in release builds keep errors lightweight.

---

## Rationale and benefits

* **Explicitness:** users can express intent (target identity, const-relaxation, forwarding categories) in a single, discoverable call.
* **Correctness:** avoids ambiguous runtime overload resolution; reduces accidental UB from naive const\_casts.
* **Ergonomics:** templates on `bind()` provide the minimal, explicit syntax needed for perfect-forwarding without changing the call-site semantics.
* **Consistency:** aligns with C++ overload and const rules while providing reflection-specific guarantees (logical vs true constness).

---

## Recommended usage patterns

* Use `bind()` with no template parameters for common cases where value-categories are natural (lvalue args, no rvalue-only overloads).
* Use `bind<T&&>()` when you need to target rvalue-ref overloads.
* Use `bind(rtl::constCast(robj))` only when you intentionally want to invoke a non-const overload on an RTL-created object.
* Avoid binding an object to static methods in production code if you want stricter correctness.

---

## Summary

`bind()` is the explicit control point for method/function invocation in RTL. It unifies target binding and argument forwarding, enabling correct overload resolution in the face of C++'s value-category and const subtleties. The design balances strictness and ergonomics: conservative by default (favoring const), explicit when mutation or rvalue selection is intended.
