### 🪶 Registration Model and Metadata Lifetime

RTL does not use macro-based reflection, implicit static initialization at program startup, or centralized global registries.
All registration is performed lazily and explicitly by user code, and registered metadata persists for the lifetime of the process.

For every registered type, method, or function, RTL creates a **dedicated dispatch object** that encapsulates:

* The callable pointer (function, method, or functor)
* The associated reflection metadata

These dispatch objects are defined in:

```
rtl/dispatch/function_ptr.h  
rtl/dispatch/method_ptr.h  
```

Each dispatch object is:

* Created **exactly once per unique registration**
* Stored in a process-lifetime `std::list`
* Reused across all `rtl::CxxMirror` instances
* Never duplicated, regardless of how many times or where the same registration statement is executed

Repeated registration attempts always resolve to the same existing object.

`rtl::CxxMirror` does not own or duplicate this metadata. It is a lightweight, ordinary object that can be constructed, copied, or destroyed without affecting the underlying registration state. Mirrors may be created with different type sets, and the same registration statements can be materialized multiple times.

For example:

```cpp
rtl::type().member<Person>().method("getName").build(&Person::getName);
```

will always yield the same metadata and dispatch object for `Person::getName`.
The lifetime of registered metadata is independent of any individual `rtl::CxxMirror` instance and persists for the duration of the program.

---

### ⚡ Reflective Call Materialization and Performance

RTL employs a two-phase invocation model. Metadata queries return lightweight descriptors such as `rtl::Function` and `rtl::Method`, which must be explicitly **materialized** into callable objects by specifying the expected signature.

This deferred materialization acts as a compile-time contract: the user declares the argument and return types they intend to use, and RTL validates and prepares an optimized invocation path accordingly.

Performance depends on how much type information is provided:

* **Fully specified signatures** compile to direct function-pointer calls, faster than `std::function`.
* **Type-erased signatures** invoke through a lightweight dispatch layer whose performance is comparable to `std::function` under real workloads.

By requiring explicit materialization, RTL produces lightweight, reusable callables that behave like ordinary value-type objects and can be stored in standard containers.

At call time, RTL performs no dynamic allocations, no RTTI lookups, and no hidden metadata traversals. The runtime cost is explicit, minimal, and comparable to what a developer would implement manually for equivalent type safety and flexibility.

---

### 🛡 Exception-Free Guarantee

RTL is designed to be exception-free. In practice, any exceptions that occur are almost always introduced by user code and merely propagate through RTL.

For all predictable failure cases, RTL reports errors through explicit error codes(`rtl::error`) rather than throwing exceptions. Critical assumptions are validated before execution, ensuring that failure conditions are detected early and handled in a controlled manner.

This design promotes predictable behavior and avoids unexpected control flow during reflective operations.

> *Exception-handling behavior has not yet been exhaustively stress-tested across all edge cases, but the system is architected to avoid exception-based control flow by design.*

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
