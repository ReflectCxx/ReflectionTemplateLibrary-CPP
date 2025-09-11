RTL Design Evolution Log
Date: 2025-08-19
Author: Neeraj Singh

# Design Exploration Log — `rtl::alloc::Shared`

## 🧩 The Motivation

So far, RTL supports cloning semantics across **stack**, **heap**, and **wrapper-aware** modes. But one common C++ pattern isn’t fully reflected yet: **shared ownership.**

In native C++, developers often pass around `std::shared_ptr<T>` instead of deep-copying or moving values — especially when sharing is cheaper and semantically correct. RTL should preserve this intuition by offering a reflection-level equivalent.

## ✨ The Proposal: `rtl::alloc::Shared`

Introduce a new allocation selector:

```c++
enum class alloc {
    Stack,
    Heap,
    Shared,   // NEW: share ownership instead of cloning
    // (Wrapper/Auto handled as part of copy semantics)
};
```

## 🔧 Behavior by Case

* **If the RObject wraps a `std::shared_ptr<T>`** → produce a shallow copy (increment ref count).

* **If the RObject wraps a `std::unique_ptr<T>` owned by RTL** → promote to `std::shared_ptr<T>` via `std::shared_ptr<T>(std::move(unique_ptr))`. RTL keeps the semantics natural — a unique resource can be turned into shared ownership.

* **If the RObject holds a stack/heap `T` (value)** → allocate a new `std::shared_ptr<T>` holding that value, making it shareable across RTL boundaries.

* **If the RObject holds a `std::weak_ptr<T>`** → lock and wrap into `std::shared_ptr<T>` if valid, or fail gracefully with `error::ExpiredWeakPtr`.

## 🎯 Why This Matters

* **Performance** – avoids deep copies when unnecessary, mirrors what devs already do manually with `shared_ptr`.
* **Intuition** – fits seamlessly with C++ semantics. You can choose: value-copy, heap-owning unique, or shareable pointer — exactly what you’d expect.
* **Flexibility** – lets RTL adapt to client code that’s designed around sharing semantics without forcing developers to write workarounds.

## 📝 Example

```c++
RObject robj = reflect(std::make_unique<MyType>());

// Instead of deep-copying MyType, just create a shared wrapper
auto [err, sharedObj] = robj.clone<rtl::alloc::Shared>();

// sharedObj now reflects `std::shared_ptr<MyType>`
EXPECT_TRUE(sharedObj.canViewAs<std::shared_ptr<MyType>>());
```

## 🌱 Design Status

This is an **exploration**, not finalized yet. The semantics look natural and consistent, but needs validation through:

* Performance tests (to ensure shared vs deep-copy is beneficial in practice).
* API ergonomics (does `Shared` feel natural to users, or is it surprising?).
* Integration with `copy::Auto` (does auto-selection need to consider `Shared`?).
