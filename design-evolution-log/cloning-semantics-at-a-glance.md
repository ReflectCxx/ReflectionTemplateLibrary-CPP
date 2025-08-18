# 🔄 Cloning Semantics — At a Glance

Cloning in RTL is explicit and predictable.
When you call:

```cpp
auto [err, copyObj] = robj.clone<alloc::X, copy::Y>();
```

you control **where** the clone is created (`alloc::Heap` vs `alloc::Stack`) and **what** is cloned (`copy::Value` vs `copy::Wrapper` vs `copy::Auto`).

---

## 📌 The `copy` modes

### `copy::Value`

Deep copy of the underlying *contained type `T`*.
Wrappers are treated as transparent.

✅ Examples:

* `RObject` of `std::shared_ptr<int>` → copy of `int`.
* `RObject` of `std::unique_ptr<MyType>` → copy of `MyType` (if copy-constructible).

❌ Errors if:

* Contained type is not copy-constructible.
* Wrapper forbids value copy (e.g. `unique_ptr<T>` with deleted copy ctor).

---

### `copy::Wrapper`

Copy the wrapper itself (shallow copy semantics).
Contained entity is *not* copied.

✅ Examples:

* `RObject` of `std::shared_ptr<int>` → shallow copy (`use_count` increases).
* `RObject` of `std::optional<MyType>` → copy of the optional wrapper.

❌ Errors if:

* Wrapper is not copyable (e.g. `unique_ptr<T>`).
* Heap allocation of wrapper is disallowed (`StlWrapperHeapAllocForbidden`).

---

### `copy::Auto` *(Default)*

RTL decides based on context:

* If object came from **RTL-managed heap allocation** (`unique_ptr` wrapping a constructed type) → deep-copy `Value`.
* If object came from an **external wrapper** (e.g. return value `shared_ptr<T>`) → shallow-copy `Wrapper`.

✅ Intuitive:
Behaves like “do what a C++ dev would expect here.”
You get value-copies for RTL-created objects, wrapper-copies for externally-supplied smart pointers.

⚠️ Important Clarification
When an object originates from an RTL-managed heap allocation (internally wrapped in std::unique_ptr), the default copy::Auto resolves to Value semantics.
👉 However, RTL never performs deep copies internally during normal operations. All internal access uses zero-cost, read-only views by reference.
➡️ A deep copy of the contained type only occurs if the user explicitly requests it via clone<Value>().
This ensures maximum efficiency while keeping semantics intuitive.

---

## 📌 The `alloc` modes

* **`alloc::Stack`** → new clone lives on the stack.
* **`alloc::Heap`** → new clone lives on the heap.
* Heap + Wrapper is forbidden → `error::StlWrapperHeapAllocForbidden`.

---

## ⚡ Examples

```cpp
RObject robj = reflect(std::make_shared<int>(42));

// Deep copy the int (wrapper is transparent).
auto [e0, vCopy] = robj.clone<alloc::Stack, copy::Value>();

// Shallow copy the shared_ptr (reference-counted).
auto [e1, wCopy] = robj.clone<alloc::Stack, copy::Wrapper>();

// Let RTL decide: shared_ptr → wrapper copy.
auto [e2, autoCopy] = robj.clone<alloc::Stack, copy::Auto>();
```

---

## 🧭 Quick Rules of Thumb

* Want the **thing inside**? → `copy::Value`
* Want the **wrapper itself**? → `copy::Wrapper`
* Don’t want to think about it? → `copy::Auto`

---

👉 With this, RTL cloning semantics mirror **how you’d naturally treat smart pointers and wrappers in C++** — no surprises, no magic, just transparent, explicit control.
