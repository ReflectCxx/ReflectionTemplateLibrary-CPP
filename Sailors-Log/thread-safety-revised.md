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

At the same time, C++ itself guarantees that **`static`**\*\* local initialization is thread-safe and atomic\*\* (since C++11). This means that if a user follows the recommended *singleton pattern* (placing the mirror in a `static` local), the compiler already enforces thread-safety.

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

## Later Idea: Template Singleton with Universe Indices

We then considered making `CxxMirror` a **templated, compiler-enforced singleton**:

* `CxxMirror` is **always static + thread-safe** by compiler guarantees.
* Users create **independent reflective universes** by indexing with a template parameter (`<0>, <1>, <2>…`).

### Benefits

* ✅ Compiler-enforced singleton.
* ✅ Zero runtime overhead.
* ✅ Multiple isolated universes.

### Downsides

* ❌ Burden on developers to manage indices.
* ❌ No semantic meaning behind numbers (risk of collisions, confusion).
* ❌ Removes flexibility of explicit construction.

---

## 📅 Update — 2025-08-31 (Decision Reversal)

After deeper consideration, we are **reverting to the original design** with **internal locking** and explicit user-managed construction.

### Reasons for Reversal

1. **Flexibility matters** — Users should retain the ability to explicitly construct and manage `rtl::CxxMirror`, not be forced into a rigid template+static model.
2. **Idiot-proof safety is already achieved** — Internal locks guarantee correctness even if a mirror is instantiated incorrectly (e.g., non-static, multi-threaded scenarios).
3. **Programmer responsibility is acceptable** — programmers will naturally recognize the essence of the singleton design pattern and use it wisely (placing the mirror in a `static` local). The docs can emphasize this idiom without enforcing it at the type system level.
4. **Simplicity of usage** — No need to manage artificial template indices or worry about collisions.

### Final Takeaway

> **CxxMirror will remain internally thread-safe via locks, with flexibility for explicit construction.**
> The **singleton pattern** (via `static` local) remains the recommended best practice, but it is *advisory, not enforced*.
> This keeps RTL both **idiot-proof and flexible**, avoiding unnecessary limitations while ensuring correctness in all usage scenarios.
