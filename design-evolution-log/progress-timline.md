# RTL Milestone Timeline — RObject, `rtl::view`, and Cloning Semantics

**Goal**: Build a non-intrusive, native-feeling runtime reflection system for C++ that preserves C++’s ownership, value categories, and performance expectations while enabling **relaxed parameter matching** across type-erased boundaries.

---

## Phase 0 — Principles & North Star

* **Non-intrusive**: No macros in user types. Registration is external and explicit.
* **C++-native intuition**: Reflected calls should behave like normal C++ calls (ownership, constness, overload resolution).
* **Zero accidental cost**: No hidden copies; pay only when you ask for it.
* **Deterministic lifetime**: Clear heap/stack semantics, explicit ownership.
* **Error-code based**: Robust, exception-free error paths.

---

## Phase 1 — Why `RObject` exists

**Problem**: After a reflected call, you often don’t know the static type of the result (or you want to pass it to another reflected call that expects a *different* but compatible type).

**Solution**: `RObject` is a **type-erased, lifetime-aware runtime handle** that:

* Stores the produced value (or pointer) and its metadata.
* Lets you **view** it as different target types (`view<T>()`) when safe.
* Enables **relaxed parameter matching** by projecting the same stored entity into multiple compatible request shapes (e.g., `std::string` ↔ `const char*`, safe arithmetic widenings, etc.).

**Design anchors**:

* Internally uses `std::any` for storage (with strict rules, see Phase 2).
* Tracks allocation site and wrapper kind in `RObjectId` (heap/stack, wrapper type, const-cast safety).
* All internal access is via **read-only views by reference**; **no implicit cloning**.

---

## Phase 2 — Storage & Ownership (type erasure without footguns)

**Challenges**

* `std::unique_ptr<T>` cannot be copied; some toolchains reject placing it directly into `std::any`.
* `std::any` may trigger copy paths in naive designs.

**Decisions**

1. **Wrapper for move-only types**: Introduced `RObjectUPtr<T>` — a simple, copyable-looking façade whose semantics are controlled by RTL. It enables consistent storage of `unique_ptr` across MSVC/GCC/Clang.
2. **`std::any` access rule**: **Every `any_cast` inside RTL is by `const T&` only**. Once constructed in-place, RTL never triggers a copy via `std::any` operations.
3. **Metadata (`RObjectId`)**: Records whether the stored entity is on heap or stack, whether it is a wrapper (`shared_ptr`, `unique_ptr`, etc.), and whether const-cast is safe (for RTL-managed instances only).

**Outcomes**

* Cross-compiler consistent behavior for move-only storage.
* No hidden copies; lifetime stays intuitive and explicit.

---

## Phase 3 — `rtl::view<T>` (see-through, zero-overhead access)

**What a view is**

* An immutable façade over the stored entity that **either** references the original value **or** materializes a value when a conversion is requested.
* Constructed with **bare types** only (`T`), then you decide how to consume it (ref/pointer/value) via `get()`.

**Properties**

* **Zero-copy until needed**: Viewing as the same type yields a const reference; viewing as different but compatible type *may* materialize a temporary (e.g., `std::string` from `const char*`).
* **No dangling**: The view’s lifetime is scoped to the `RObject` and call site.
* **Validation**: Views are only produced when statically/semantically safe; otherwise `std::optional` is empty.

**Why it matters for relaxed matching**

* A single stored value can be presented as `T`, `U`, or `V` if (and only if) conversions are safe by RTL policy.

---

## Phase 4 — Smart Pointers: reflecting real-world ownership

**Support added**: `std::unique_ptr<T>`, `std::shared_ptr<T>`

**Semantics**

* **`view<std::unique_ptr<T>>`**:

  * Multiple views can exist. Calling `get()` **moves** the pointer **once** out of the `RObject`-held storage; subsequent `get()` calls yield an empty `unique_ptr`.
  * `RObject` itself remains valid after the move; only the contained `unique_ptr` becomes empty.
* **`view<std::shared_ptr<T>>`**:

  * `view->get()` as `const std::shared_ptr<T>&` does **not** bump refcount.
  * Acquiring by value creates a **shallow, ref-counted copy** (obvious from C++ intuition).
* **Transparent access to underlying `T`**: Users can request `view<T>` directly; wrappers act as transparent containers whenever reasonable.

**Safety rules**

* RTL does **not** invent copying for noncopyable `T`.
* If the original object was **RTL-constructed on heap**, it is stored in an RTL-owned `unique_ptr` (transparent internally). Internal operations never deep-copy; cloning happens only on explicit request.

---

## Phase 5 — Cloning Semantics (explicit, predictable)

**Public API**

```cpp
// Choose allocation site and clone target (Auto / Value / Wrapper)
template<rtl::alloc A, rtl::copy C = rtl::copy::Auto>
std::pair<rtl::error, RObject> RObject::clone() const;
```

**Copy target policy**

* `copy::Value`  → Deep-copy the **underlying value** `T` (if copy-constructible). Allocation site decided by `A`.
* `copy::Wrapper` → Copy the **wrapper** when applicable:

  * `shared_ptr` → shallow, ref-counted copy (allowed on `alloc::Stack`; **heap forbidden**).
  * `unique_ptr` → not copyable → `error::TypeNotCopyConstructible`.
* `copy::Auto` → The intuitive default:

  * If the object is a **non-RTL** wrapper (e.g., a `shared_ptr` or a `unique_ptr` returned from user code), clone the **Wrapper**.
  * If the object is **RTL-managed heap instance** (constructed via reflection, owned by RTL’s internal `unique_ptr`), clone the **Value** (deep-copy) *only when explicitly requested by the user via `clone()`*.

**Allocation policy**

* `alloc::Stack` → produces a stack-held instance when cloning `Value`, or a stack-held wrapper when cloning `Wrapper` (for `shared_ptr`).
* `alloc::Heap` → deep-copy to heap for `Value`; **forbid** heap-alloc of wrapper clones (`error::StlWrapperHeapAllocForbidden`).

**Errors you’ll see**

* `error::EmptyRObject`, `error::NotWrapperType`, `error::TypeNotCopyConstructible`, `error::StlWrapperHeapAllocForbidden`.

**Crucial nuance**

* *Efficiency preserved*: Despite the rule “If RTL-managed heap ⇒ deep-copy Value,” **RTL never performs hidden clones**. Internally, RTL only uses read-only references; cloning happens **solely** when the user calls `clone()`.

**Evolution note**

* Early iterations used an internal `EntityKind` (Value/Wrapper). Public API is now unified as `rtl::copy { Auto, Value, Wrapper }` for clarity.

---

## Phase 6 — Relaxed Parameter Matching (roadmap & current policy)

**Motivation**: Let users compose reflected calls without hand-writing glue types.

**Current safe projections**

* **String-like**: `const char* → std::string` (materialize), `std::string_view ↔ std::string` (configurable, conservative by default).
* **Arithmetic**: only **proven-safe widenings** (e.g., `int → long long`, `float → double`). No narrowing; no int↔float unless explicitly allowed. Policy backed by a compile-time trait (conservative by design).
* **Pointer/view**: From `unique_ptr<T>` / `shared_ptr<T>` to `T` via `view<T>` (transparent read-only access), honoring ownership rules.

**Future**

* Enums, properties, composite types, inheritance — each with explicit, conservative matching tables.

---

## Phase 7 — Testing Milestones

* **`unique_ptr<T>` round-trip**: reflect, multiple views, single-move extraction, post-move stability of `RObject`.
* **`shared_ptr<T>` sharing**: ref-count behavior via read-only vs by-value access; wrapper clone vs value clone behavior; mixed ownership lifetimes.
* **User-defined noncopyable types** (`Node`): verify wrapper-level shallow clones succeed while value-level clones fail with `TypeNotCopyConstructible`; resource counters prove correct destruction.
* **Constructor misuse guard**: Calling `Record::create` with a copy-ctor signature reports `SignatureMismatch` (design choice: copy construction is reserved for `RObject::clone`).

---

## Phase 8 — Performance & Safety Posture

* **No hidden work**: All internal access is via const refs; no implicit deep copies.
* **Explicit costs**: Cloning is explicit; conversions happen only when `view<T>` asks for them.
* **Thread- & exception-safety**: Error codes over exceptions; atomic counters for diagnostics; clear ownership tracking.
* **Cross-compiler consistency**: `RObjectUPtr<T>` and `const-ref any_cast` discipline keep MSVC/GCC/Clang aligned.

---

## Phase 9 — What’s Next

* **Relaxed matching tables** (documented, auditable) for string-like and arithmetic families.
* **Property/Enum/Composite/Inheritance** reflection with the same semantics discipline.
* **ABI boundary story** (plugins): keeping binary boundaries stable by constraining surface types to ABI-friendly shapes.

---

## One-liner Summary

**RObject** stores *what you have*; **`rtl::view<T>`** gives you *what you need*; **clone semantics** make the cost *explicit and intuitive*. Together, they enable relaxed parameter matching that still *feels like C++.*
