### 🪶 No Static Globals, No Macros, No Surprises

RTL does not rely on:

* Hidden static registration
* Centralized global registries
* Preprocessor hacks

Instead, registration is explicit and lazy.

For each registered type, RTL contributes **two lightweight entries** into its process-local tables:

* A **lambda wrapper** placed in a scoped `static` `std::vector` and is responsible for making the final call using the actual function pointer with perfect forwarding.
* A **raw function pointer** stored in a parallel scoped `static` `std::vector`, used to detect and prevent redundant registrations.

From there, `rtl::CxxMirror` does not hold onto heavyweight state. It is **as ordinary as any local variable** — you can construct one, keep it alive for the entire application, or discard it after a short-lived query. The same `rtl::CxxMirror` can be materialized again with the same or different set of types. RTL guarantees that **materializing the same registration sequence multiple times** (for example):

```cpp
rtl::type().member<Person>().method("getName").build(&Person::getName);
```

will always yield **exactly the same metadata**, without ever admitting redundant lambdas or function pointers into the static tables.

> *"Mirrors are **cheap and repeatable**: the metadata is stable, redundant entries are never entertained, and the user remains in full control of a mirror’s lifetime."*

---

### ⚡ Reflective Call Performance

Reflective calls in RTL are designed to be explicit, predictable, and minimal. The mechanism unfolds in two clear steps:

1. **Signature Matching** — Each call signature yields a unique type-ID, compared directly against the ID of the lambda-table holding the final call. With a single overload this resolves immediately; if multiple overloads exist, RTL just scans a tiny `std::vector` of candidate IDs.

2. **Call Dispatch** — Once the correct overload is identified, RTL performs constant-time `std::vector` indexing to retrieve the associated lambda wrapper. This wrapper executes a single hop to the underlying function pointer, forwarding the provided arguments perfectly.

The net overhead of a reflective call is thus a handful of integer comparisons, one direct `std::vector` access, and one lambda-to-function-pointer indirection. There are no dynamic allocations, RTTI lookups, or hidden metadata traversals at call time. The cost is transparent and limited to exactly what is required for overload resolution and safe forwarding — no more, no less.

> *"A reflective call in RTL is not free, but its cost is explicit, transparent, and no greater than what you would write by hand."*

---

### 🛡 Exception-Free Guarantee

RTL is designed to be virtually exception-free. If an exception ever emerges from RTL, it signals that something deeper is wrong. In practice, such exceptions are almost always caused by client/user code and merely propagate through RTL. Internally, only one scenario could theoretically throw:

* `std::any_cast` — guarded by strict, break-proof type checks that make throwing virtually impossible.

This is extremely unlikely, but not absolutely impossible — no system is perfect.
For every predictable failure case, RTL returns explicit error codes instead of throwing.
RTL validates all critical assumptions before proceeding, ensuring predictable behavior and eliminating mid-operation surprises.

---

### 🔒 Const-By-Default Discipline

RTL enforces a *const-by-default* discipline. All objects **created through reflection** start as *logically-const* — they default to immutability. If no const overload exists, RTL will **automatically fall back** to the non-const overload, since these objects were never originally declared `const`. Explicit `rtl::constCast()` is only required when both const and non-const overloads are present.
 
The guiding principle is simple: reflective objects are safe by default, and any mutation must be a conscious, visible decision by the caller.
 
At the same time, RTL strictly respects **true-const** objects (e.g., declared-`const` instances or const return values). Such objects remain immutable inside RTL — any attempt to force mutation results in predictable error code (`rtl::error::IllegalConstCast`).

> *"RTL never mutates true-const objects, and for RTL-created ones it defaults to const, falling back only if needed — explicit rtl::constCast() is required when both overloads exist."*

This discipline complements RTL’s exception-free guarantee, ensuring both **predictability** and **safety** at the API boundary.

---

### 🎁 Transparent Handling of Smart Pointers

Reflection should never feel like a cage.
In everyday C++, if you hold a `std::unique_ptr<T>` or `std::shared_ptr<T>`, you don’t think twice about how to use it — you simply work with the object it points to, sometimes copying it, sometimes sharing it, sometimes moving it. RTL extends this same natural experience into runtime reflection.

Every heap object created through RTL is safely managed inside a smart pointer. Yet to you, as the developer, that detail is invisible. You can look at it as the smart pointer if you wish, or simply as the underlying type `T`.

When you ask RTL to clone, it adapts to the situation in the most intuitive way:

* If a type is naturally shared, you can get a shared view.
* If it is unique, RTL respects that uniqueness.
* And if the value itself can be copied, you can always ask for a fresh independent object.

The key idea is that RTL doesn’t force you into a wrapper-first mindset. Instead, it makes wrappers feel transparent — you can still reason in terms of *your type*, just as you would in normal C++.

> *"Developers shouldn’t have to think about “reflection semantics” versus “normal C++ semantics.” With RTL, the two worlds are aligned. Whether you’re holding a raw object or a smart pointer, the same intuition applies — reflection just works the way you expect."*

---

### 🧠 Tooling-Friendly Architecture

**RTL** separates the *generation* of reflection metadata from its *consumption*. This makes it ideal not just for runtime introspection, but also for external tools like:

* Code generators
* Serialization pipelines
* Game or UI editors
* Live scripting or plugin systems

#### ✨ The Mirror & The Reflection

> *A client system hands off a `CxxMirror` to RTL — and RTL sees its reflection.*

That’s it. The mirror is a **single object**, typically returned from a function like:

```cpp
extern const rtl::CxxMirror& MyReflection();
```

This function is:

* **Externally linkable** — can live in any translation unit or even dynamic module
* **Lazy** — doesn’t require metadata unless explicitly accessed
* **Pure** — returns a complete, immutable view of reflection metadata

#### 📎 Why This Matters for Tooling

This design turns RTL into a **pluggable, runtime-agnostic consumer** of metadata. You can:

* Reflect types from external libraries
* Link in auto-generated metadata modules
* Expose your reflection system to scripts or tools without tight coupling
* Swap different `CxxMirror` sources depending on build mode (dev/editor/runtime)
