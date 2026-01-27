### 🪶 Registration Model and Metadata Lifetime

RTL does not use macro-based reflection, implicit static initialization at program startup, or centralized global registries.
All registration is performed lazily and explicitly by user code, and registered metadata persists for the lifetime of the process.

For every registered type, method, or function, RTL creates a **dedicated dispatch object** that encapsulates:

* The callable function-pointer
* The associated reflection metadata

These dispatch objects are defined in:

```
rtl/dispatch/function_ptr.h  
rtl/dispatch/method_ptr.h  
```

Each dispatch object is:

* Created **exactly once per unique registration**
* Stored in a process-lifetime (`static std::list`)
* Reused across all `rtl::CxxMirror` instances

Repeated registration attempts always resolve to the same existing object. This ensures deterministic behavior – 
metadata identity is stable regardless of initialization order or how many translation units register the same type.

`rtl::CxxMirror` does not own or duplicate this metadata. It encapsulates references to it as a lightweight, ordinary object. Mirrors may be created with different type sets, and the same registration statements can be materialized multiple times.

For example:

```cpp
rtl::type().member<Person>().method("getName").build(&Person::getName);
```

will always yield the same metadata and dispatch object for `Person::getName`.
The lifetime of registered metadata is independent of any individual `rtl::CxxMirror` instance and persists for the duration of the program.

---

### ⚡ Reflective Call Materialization and Performance

RTL employs a two-phase invocation model. Metadata queries return lightweight descriptors such as `rtl::Function` and `rtl::Method`, which must be explicitly **materialized** into callable entity by specifying the expected signature.

This deferred materialization acts as a compile-time contract: the user declares the argument and return types they intend to use, and RTL validates and prepares an optimized invocation path accordingly.

Performance depends on how much type information is provided:

* Fully specified signatures compile to **direct function-pointer calls**, faster than `std::function`.
* Type-erased signatures invoke through a lightweight dispatch layer whose performance **is comparable** to `std::function` under real workloads.

By requiring explicit materialization, RTL produces lightweight, reusable callable entity that behave like ordinary value-type objects and can be stored in standard containers.

At call time, RTL performs no dynamic allocations, no RTTI lookups, no `void*` stuff, and no hidden metadata traversals. The runtime cost is explicit, minimal, and comparable to what a developer would implement manually for equivalent type safety and flexibility.

---

### 🛡 Exception-Free Guarantee

RTL is designed to be exception-free. In practice, any exceptions that occur are almost always introduced by user code and merely propagate through RTL.

For all predictable failure cases, RTL reports errors through explicit error codes(`rtl::error`) rather than throwing exceptions. Critical assumptions are validated before execution, ensuring that failure conditions are detected early and handled in a controlled manner.

This design promotes predictable behavior and avoids unexpected control flow during reflective operations.

> *Exception-handling behavior has not yet been exhaustively stress-tested across all edge cases, but the system is architected to avoid exception-based control flow by design.*

---

### 🎁 Smart Pointer Handling

RTL supports working with objects managed by `std::unique_ptr` and `std::shared_ptr` in a manner consistent with standard C++ usage.

Heap-allocated objects created through RTL are internally managed using smart pointers to ensure safe ownership and lifetime control. These details are not imposed on the user: reflected objects can be accessed either through their smart-pointer representation or through views of the underlying type `T`.

When cloning or transferring reflected objects, RTL preserves the ownership semantics of the original type:

* Objects intended to be shared can be accessed through shared ownership.
* Uniquely owned objects retain their uniqueness.
* Copyable values can be duplicated to produce independent instances.

This design allows developers to work with reflected objects using the same ownership and lifetime expectations they would apply in ordinary C++ code, without requiring special handling for reflection-specific wrappers.

Reflection semantics are aligned with standard C++ object semantics, ensuring consistent behavior regardless of whether an object is accessed directly or through a smart pointer.

---

### 💡 Tooling-Friendly Architecture

**RTL** separates the *generation* of reflection metadata from its *consumption*. This makes it ideal not just for runtime introspection, but also for external tools like:

* Code generators
* Serialization pipelines
* Game or UI editors
* Live scripting or plugin systems

#### ✨ The Mirror & The Reflection

> *A client system hands off a `rtl::CxxMirror` to RTL — and RTL sees its reflection.*

The mirror is a **single object**, typically returned from a function like:

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
* Swap different `rtl::CxxMirror` sources depending on build mode (dev/editor/runtime)