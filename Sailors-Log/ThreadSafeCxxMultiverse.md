# 📓 RTL Design Log — `CxxMirror` Thread-Safety & Singleton Model

**Date:** 2025-08-29
**Author:** Neeraj Singh

---

## Background

`rtl::CxxMirror` is the **root container** of RTL, holding all registrations (records, functions, methods, constructors).
By design, it should:

* Be a **singleton** (one shared mirror across the program).
* Be **thread-safe** (registration happens once, and the mirror becomes immutable).
* Avoid unnecessary **runtime overhead** (locks, contention, etc.).

Earlier, RTL used **internal locking** to guard critical sections during registration and query. This made the system **idiot-proof** — safe even if a user misused the mirror.

At the same time, C++ itself guarantees that **`static` local initialization is thread-safe and atomic** (since C++11). This means that if a user follows the recommended *singleton pattern* (placing the mirror in a `static` local), the compiler already enforces thread-safety.

This raised the question:
➡️ *Should RTL still keep internal locks even when the compiler already provides thread-safety guarantees?*

---

## Initial Options Considered

### Option 1 — Always Keep Locks

* ✅ Safe in all cases (idiot-proof).
* ✅ Protects against misuse (e.g., non-static mirrors created across threads).
* ❌ Adds small but non-zero runtime overhead (mutex acquire/release).
* ❌ Redundant in canonical usage (`static` local mirror).

### Option 2 — Remove Locks in `Static` Mode

* ✅ Zero runtime overhead.
* ✅ Leverages compiler’s thread-safety.
* ❌ Risk of misuse: a user could instantiate a `CxxMirror<Static>` as a local/automatic variable in multiple threads and break invariants.
* ❌ “God mode” is nice for experts, but dangerous in practice.

### Option 3 — Configurable Policy (ThreadSafe vs Static)

* ✅ Gives users control (`rtl::CxxMirror<rtl::ThreadSafe>` vs `rtl::CxxMirror<rtl::Static>`).
* ✅ Defaults to safe mode.
* ❌ Opens a footgun: users might misuse `Static` in a non-static context.
* ❌ Adds cognitive load (users must pick policies).

---

## Final Idea: Template Singleton with Universe Indices

Instead of policies, we arrived at a **cleaner, safer design**:

* `CxxMirror` is **always static + thread-safe** by compiler guarantees.
* Users can create **multiple independent reflective universes** by indexing with a template parameter.

```cpp
// Universe 0
const rtl::CxxMirror<0>& mirror0() {
    static rtl::CxxMirror<0> m({
        // registrations for universe 0
    });
    return m;
}

// Universe 1
const rtl::CxxMirror<1>& mirror1() {
    static rtl::CxxMirror<1> m({
        // registrations for universe 1
    });
    return m;
}
```

### Benefits

* ✅ **True thread-safety**: enforced by compiler, no internal locks needed.
* ✅ **Singleton by design**: each `CxxMirror<N>` can only exist once, as a static.
* ✅ **Zero runtime overhead**: no mutexes, no branches.
* ✅ **Multiple universes**: users can easily isolate different reflective domains (`<0>, <1>, <2>…`).
* ✅ **No misuse path**: users can’t accidentally create a per-thread or per-call `CxxMirror` with the wrong policy — static + singleton is the only model.
* ✅ **Self-documenting**: template index makes it explicit which “universe” the mirror belongs to.

---

## Developer Responsibility — Managing Indices

While this model solves thread-safety and singleton concerns at the compiler level, it shifts one piece of responsibility onto the developer:

* Developers must **choose and manage unique indices** (`<0>, <1>, <2>…`).
* The indices themselves carry **no semantic meaning** — they are just numbers.
* This requires conventions or aliases to avoid confusion.

### Pros

* ✅ **Compiler-enforced singleton** — no duplicate mirrors.
* ✅ **Zero runtime overhead** — nothing to lock or check.
* ✅ **Simple mental model** — index = isolated reflective universe.
* ✅ **Flexible** — multiple independent mirrors for core, plugins, tests, etc.
* ✅ **Self-documenting at call site** — seeing `<2>` makes it clear you’re in a separate universe.

### Cons

* ❌ **Developer-managed indices** — requires discipline.
* ❌ **No built-in meaning** — `<0>` doesn’t tell you if it’s core, plugin, or test.
* ❌ **Risk of collisions** — two teams may both pick `<1>` without coordination.
* ❌ **Scalability issues** — managing many indices becomes cumbersome.
* ❌ **No intent guarantee** — compiler enforces uniqueness, not semantics.

---

## Mitigations

To soften the developer burden, idioms can be introduced:

```cpp
enum Universe { Core=0, Plugin=1, Tests=2 };
using CoreMirror   = rtl::CxxMirror<Universe::Core>;
using PluginMirror = rtl::CxxMirror<Universe::Plugin>;
```

* Aliases or enums give **semantic meaning** to indices.
* Keeps code self-explanatory without relying on magic numbers.

---

## Key Takeaway

> **CxxMirror is now a templated, static, compiler-enforced singleton.**
> Each instantiation `<N>` represents a unique reflective universe, guaranteed thread-safe by design.
> Developers must manage indices, but conventions (aliases, enums) make this simple and maintainable.
> In practice, most users will only ever need a single universe (`<0>`), making the resolution effectively **no trade-off**.
