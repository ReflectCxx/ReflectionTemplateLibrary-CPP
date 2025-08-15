### 🧠 Metadata Providers & Runtime Consumers – A Tooling-Friendly Architecture

**RTL** separates the *generation* of reflection metadata from its *consumption*. This makes it ideal not just for runtime introspection, but also for external tools like:

* Code generators
* Serialization pipelines
* Game or UI editors
* Live scripting or plugin systems

### ✨ The Mirror & The Reflection

> A client system hands off a `CxxMirror` to RTL — and RTL sees its reflection.

That’s it. The mirror is a **single object**, typically returned from a function like:

```cpp
extern const rtl::CxxMirror& MyReflection();
```

This function is:

* **Externally linkable** — can live in any translation unit or even dynamic module
* **Lazy** — doesn’t require metadata unless explicitly accessed
* **Pure** — returns a complete, immutable view of reflection metadata

### 📎 Why This Matters for Tooling

This design turns RTL into a **pluggable, runtime-agnostic consumer** of metadata. You can:

* Reflect types from external libraries
* Link in auto-generated metadata modules
* Expose your reflection system to scripts or tools without tight coupling
* Swap different `CxxMirror` sources depending on build mode (dev/editor/runtime)

### 🗉 No Static Globals, No Macros, No Surprises

RTL does not rely on:

* Hidden static registration
* Centralized global registries
* Preprocessor hacks

Instead, you choose *when* and *how* to expose the metadata. The reflection engine remains lightweight, predictable, and truly **zero-overhead until used**.

### 🛡 Exception-Free Guarantee

RTL is designed to be virtually exception-free. If an exception ever emerges from RTL, it signals that something deeper is wrong. In practice, such exceptions are almost always caused by client/user code and merely propagate through RTL. Internally, only one scenario could theoretically throw:

* `std::any_cast` — guarded by strict, break-proof type checks that make throwing virtually impossible.

This is extremely unlikely, but not absolutely impossible — no system is perfect.
For every predictable failure case, RTL returns explicit error codes instead of throwing.
RTL validates all critical assumptions before proceeding, ensuring predictable behavior and eliminating mid-operation surprises.

### 🛡 Const-By-Default Discipline

RTL enforces a *const-by-default* philosophy.
All objects instantiated via RTL are treated as **immutable** unless the caller explicitly requests mutation.

This design ensures:

* **No accidental state changes** — methods that modify state must be consciously invoked.
* **Immediate code clarity** — mutable calls are visually obvious during code review.
* **Defensive programming** — the default assumption is safety, mutation is a deliberate opt-in.

> *“You can’t change an RTL-managed object unless you loudly tell the compiler and everyone reading your code that you are about to change it.”*

This rule complements RTL’s exception-free guarantee, giving both **predictability** and **safety** at the API boundary.

### 🏱 Transparent Unwrapping of Smart Pointers

Reflection should never feel like a cage.
In native C++, if you hold a `std::unique_ptr<T>`, `std::shared_ptr<T>`, or `std::weak_ptr<T>`, you can still legally create independent copies of the underlying `T` — as long as it’s constructible. RTL extends this exact intuition into runtime reflection.

Every object created on the heap via RTL is internally managed as a `std::unique_ptr`.
If you know the type `T`, you can view it either as `std::unique_ptr<T>` **or** directly as `T`. By default, when unwrapping, RTL performs a **deep clone** of the pointee — ensuring you get a completely independent object without altering the original.
If you don’t know the type, this behavior is entirely transparent — you remain blissfully oblivious, yet safe.

Two new allocation selectors make this intent explicit:

* `alloc::UnwrapOnStack` — create a stack-allocated `T` from the smart pointer’s pointee.
* `alloc::UnwrapOnHeap` — create a heap-allocated `T` from the smart pointer’s pointee.

Native semantics are preserved:

* For `shared_ptr`, the unwrapped copy is independent and does not share ownership.
* For `unique_ptr`, the original retains its ownership — your copy is separate.
* For `weak_ptr`, the pointee is locked and copied, or creation fails gracefully if expired.

> **Why it matters:** This is an “Oh wow!” moment for developers — you don’t have to know what wrapper you’re looking at to still get to the type you care about. It’s transparent, intuitive, and feels exactly like “normal C++ at runtime.”
