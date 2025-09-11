### 🗨️ Dev Conversation (Revised): Evaluating RTL’s Handling of C++ Const‑Method Quirks

**Updated:** 2025-08-25

> Two engineers are evaluating RTL from the outside (they don’t own it). They’re cross‑checking RTL’s behavior against **native C++ const overload rules** and reconciling any gotchas.

---

#### Quick refresher: Native C++ rules for `const` vs `non‑const` member overloads

1. **Call on a `const` object**

   * Overload resolution prefers **`const`‑qualified** member functions.
   * If **no `const` overload exists**, a direct call to a non‑const member is a **compile‑time error**.
   * A user may write `const_cast<T&>(obj).nonConst()`; the call compiles, **but any mutation of an originally `const` object yields undefined behavior**.

2. **Call on a non‑const object**

   * If both overloads exist, overload resolution prefers the **non‑const** overload.
   * If **only a `const` overload** exists, **calling it is perfectly valid**; there is **no compile error**. (A non‑const object can call a `const` member function.)

These are the ground truths we’ll map RTL onto.

---

#### Conversation

**Dev A:** I’m reading RTL’s docs about const semantics. They talk about “logically‑const” for RTL‑created objects and “true‑const” for external ones. Before we judge that, let’s sanity‑check against native C++ rules we just reviewed.

**Dev B:** Right. In native C++, a `const` object can only call `const` members unless you `const_cast`—and mutating that object is UB. A non‑const object prefers the non‑const overload, but it can still call a `const` member if that’s the only one available.

**Dev A:** Cool. Now, how does RTL line up?

**Dev B:** From what I gather:

* **True‑const objects (externally provided into RTL):**
  RTL treats them like native C++ `const` objects. It **only considers `const` overloads**.
  • If the `const` overload is **missing**, RTL returns **`rtl::error::ConstOverloadMissing`** instead of trying anything clever.
  • If the user **explicitly** tries to bind to a non‑const overload using `rtl::constCast()`, RTL rejects it with **`rtl::error::IllegalConstCast`**.
  • RTL never performs an internal `const_cast` on such objects.

* **Logically‑const objects (created by RTL via reflection):**
  RTL defaults to the `const` overload to keep things safe and predictable.
  • If **both** overloads exist, users can **explicitly opt into** the non‑const one using **`rtl::constCast()`**.
  • If the **`const` overload is missing** but a **non‑const** one exists, RTL may **safely fall back** to the non‑const overload by performing an internal, guaranteed‑safe logical `const_cast` (since RTL owns the object’s lifecycle).
  • This mirrors the “you could `const_cast` in C++ if it’s safe,” but **with stronger guarantees** because RTL distinguishes logical vs true constness.

**Dev A:** So we should tweak the summary line to be precise: *“If the reflected object is const, RTL only considers the const overload. If it doesn’t exist, you’ll get `ConstOverloadMissing`.”* → That’s **only** for **true‑const** objects, right?

**Dev B:** Exactly. For **true‑const**, missing `const` → `ConstOverloadMissing`. But for **logically‑const** RTL‑created objects, **missing `const` + present non‑const** → RTL will legitimately call the non‑const overload (safe internal `const_cast`).

**Dev A:** And on the non‑const side, does RTL emulate native C++’s preference for the non‑const overload when both exist?

**Dev B:** Conceptually yes—but with RTL’s **const‑by‑default discipline**, calls start from a logically‑const stance. So by default, RTL picks the `const` overload; **users must be explicit** (via `rtl::constCast()`) to select the non‑const overload. That’s a deliberate design: *safety first, explicit mutation second.*

**Dev A:** That’s fair. It’s stricter than C++’s default, but predictable. And it still lets you reach the non‑const path when you mean it.

**Dev B:** Right. And the error taxonomy makes intent obvious:

* `rtl::error::ConstOverloadMissing` → true‑const object, only non‑const overload exists.
* `rtl::error::IllegalConstCast` → explicit attempt to force a non‑const call on a true‑const object.
* No error for RTL‑created objects when falling back to a non‑const overload—the fallback is **by design** and **safe**.

**Dev A:** Last cross‑check with native C++: non‑const object calling a `const` member when that’s the only option—valid in C++. Does RTL allow the analogous scenario?

**Dev B:** Yes—that maps to either (a) true‑const objects calling `const` members (the only option), or (b) logically‑const objects defaulting to `const` members even if the underlying instance is mutable. Both are consistent.

**Dev A:** Makes sense. So the headline is: *RTL codifies C++’s const rules at runtime, adds provenance‑aware safety (true‑const vs logically‑const), defaults to const for clarity, and requires explicit opt‑in for mutation via `rtl::constCast()`.*

**Dev B:** Exactly. Cleaner than ad‑hoc const\_casts in user code, and safer than pretending const doesn’t matter at runtime.

---

#### TL;DR

* Native C++: `const` object → only `const` overload (non‑const needs cast; mutating originally `const` is UB). Non‑const object → prefers non‑const; may call `const` if that’s all there is.
* RTL (true‑const): only `const` overload; missing `const` → `ConstOverloadMissing`; forcing non‑const → `IllegalConstCast`.
* RTL (logically‑const): defaults to `const`; missing `const` but non‑const present → safe fallback to non‑const; both present → user can explicitly pick non‑const with `rtl::constCast()`.
