RTL Design Evolution Log
Milestone: RObject – The Runtime Instance Container
Date: 2025-08-13
Author: Neeraj Singh

---

## Purpose

`RObject` is the central runtime container in RTL — the bridge between compile-time registered metadata and actual object instances at runtime. It encapsulates:

* The underlying value or pointer (type-erased in `std::any`).
* Ownership and lifetime management logic.
* Metadata (`RObjectId`) linking the instance to its reflection type info.
* Cloning and controlled movement.

This design allows RTL to operate on objects without compile-time type knowledge while preserving safety, performance, and predictable semantics.

---

## Core Characteristics

* **Move-only:** No accidental copies; move constructor provided, move assignment deleted.
* **Explicit Cloning:** All duplication is via a stored `Cloner` function pointer; no hidden copies.
* **Type-Erased Storage:** `std::any` holds stack values, heap allocations, or wrapped move-only types like `std::unique_ptr<T>`.
* **Consistent Metadata Link:** Every `RObject` carries an `RObjectId` to resolve runtime type operations.

---

## Creation & Storage Rules

* Built via type-trait-dispatched builders.
* Special handling for string-like types and raw C strings.
* Heap vs stack distinction recorded in metadata.
* Uses safe wrappers (e.g., `RObjectUptr`) for move-only types to ensure cross-compiler compatibility.
* RTL rule: **All `any_cast` operations retrieve values only as `const T&`** — preventing unwanted copies, even for copyable types.

---

## Cloning & Lifetime Management

* `Cloner` supports type-specific shallow or deep copies.
* Metadata preserves original allocation type and const-cast safety.
* Destructor access is validated — if deleted/private, heap allocation is rejected.
* No double-deletes or leaks across move and clone operations.

---

## Interoperability & Conversion

* Planned relaxed parameter type matching (e.g., `const char*` → `std::string`).
* Safe implicit conversions recognized.
* Works with values, refs, and pointers.

---

## Benefits

* **Predictable API:** Logical constness enforced; internal mutability for reflection only.
* **Cross-Compiler Consistency:** Single code path for MSVC, GCC, Clang.
* **Performance-Aware:** Avoids redundant copies and allocations.
* **Extensible:** Designed for future relaxed conversions, advanced lifetime rules, and complex type handling.
