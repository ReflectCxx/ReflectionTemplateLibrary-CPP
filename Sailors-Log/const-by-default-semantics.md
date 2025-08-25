# Design Log: Const Semantics in RTL

**Author:** Neeraj Singh
**Date:** 2025-08-24

---

## Overview

This document details the **const semantics** in RTL (ReflectionTemplateLibrary-CPP), covering the distinction between RTL-created (logically-const) objects and externally provided (true-const) objects. It also explains how method binding, overload resolution, and error handling are governed by this model.

---

## Core Principles

1. **Const-by-Default Discipline**

   * All objects created via RTL reflection are treated as immutable by default.
   * External objects passed to RTL retain their declared constness without alteration.

2. **Two Kinds of Constness**

   * **Logically-Const (RTL-Created):** Objects appear immutable but may be safely cast internally by RTL.
   * **True-Const (External):** Objects declared const by user code; RTL strictly respects their constness and never applies const\_cast internally.

---

## Method Binding & Overload Resolution

### 1. RTL-Created Objects (Logically-Const)

* **Default:** RTL always prefers binding to the `const` overload of a method.
* **Fallback:** If no `const` overload exists but a non-const overload is present, RTL applies a *safe logical const\_cast* and binds to the non-const overload.
* **Explicit Choice:** If both overloads exist, the user may explicitly select which to bind by using `rtl::constCast()`.

### 2. Externally Provided Objects (True-Const)

* **Allowed Binding:** RTL binds only to `const` overloads.
* **Illegal Binding Attempt:** If the user explicitly attempts to bind a true-const object to a non-const overload, RTL reports:

  * `rtl::error::IllegalConstCast`.
* **Missing Const Overload:** If only a non-const overload exists (no `const` variant), RTL reports:

  * `rtl::error::ConstOverloadMissing`.
* **Guarantee:** RTL never internally const\_casts true-const objects.

---

## Error Semantics

* `rtl::error::IllegalConstCast` → Raised when the user attempts to bind a true-const object to a non-const method.
* `rtl::error::ConstOverloadMissing` → Raised when a true-const object attempts a call but no `const` overload is available.

---

### 📌 Const Overload Handling: Native C++ vs RTL

**Objective:** Verify whether RTL’s fallback and overload resolution for const/non-const methods aligns with native C++ semantics.

---

#### 🟦 Native C++ Const Method Resolution

* **Case 1: Call on `const T` / `const T&` / `const T*`:**

  * Only `const` member functions are viable.
  * If only a non-const overload exists → **compile-time error**.
  * User may `const_cast` and call non-const, but that’s UB if the object is truly const.

* **Case 2: Call on non-const `T` / `T&` / `T*`:**

  * If both const and non-const overloads exist → compiler **chooses the non-const overload**.

    * Reason: binding to a non-cv-qualified `this` is a better match than converting to `const this`.
  * If only the const overload exists → call is **valid**. A non-const object **can call a const member**.

---

#### 🟦 RTL Const Method Resolution

* **True-const objects (external const instances):**

  * RTL mirrors native C++ strictly.
  * Only const overloads are considered.
  * If missing → returns **`rtl::error::ConstOverloadMissing`**.
  * If user explicitly attempts a constCast → **`rtl::error::IllegalConstCast`**.

* **Logically-const objects (RTL-created, safe for const\_cast):**

  * RTL defaults to **binding the const overload** even if both exist → defensive by design.
  * User can explicitly call the non-const overload via **`rtl::constCast()`** when intended.
  * If only non-const exists, RTL safely **falls back to non-const** (guaranteed safe, since RTL owns the object).

---

#### ✅ Cross-Verification Result

* With a **non-const object**, native C++ picks non-const overload if available, otherwise falls back to const overload.
* With a **const object**, native C++ restricts to const overloads, otherwise errors.
* RTL matches this baseline but adds safety defaults for **logically-const** objects:

  * Defaults to const when both are present.
  * Requires explicit opt-in (`rtl::constCast()`) for non-const.
  * Provides error signaling instead of UB for illegal casts.

---

📖 **Conclusion:**
RTL’s fallback is fully aligned with native C++ semantics for true constness, while extending the model with explicit safety rules and clearer error channels for logically-const cases. This preserves C++ familiarity while adding reflection-layer discipline.


## Strengths of the Model

* **Safety First:** Prevents unsafe const-casting on external objects.
* **Flexibility:** Allows controlled safe relaxation of constness on RTL-managed objects.
* **Clarity:** Overload resolution is predictable and explicit.
* **Alignment with C++:** Fully consistent with const-correctness principles.

---

## Considerations

* **Documentation Needs:** Users must clearly understand the distinction between logically-const and true-const.
* **Testing:** Edge cases (e.g., methods with only non-const overloads) must be thoroughly verified.
* **Consistency:** Const semantics must remain uniform across cloning, moving, and nested reflection contexts.

---

## Comparative Note

* **Java Reflection:** Does not enforce constness; all members can be accessed/mutated freely.
* **C# Reflection:** Similar to Java, though `readonly` exists at field level; reflection can still override it.
* **RTL:** Unique in enforcing const-by-default while distinguishing between safe logical const-casts (for RTL-owned objects) and strict const adherence (for external objects).

---

## Summary

The const semantics in RTL establish a principled model:

* **RTL-created objects:** const by default, but safe to relax when needed; users may explicitly call non-const overloads with `rtl::constCast()`.
* **External objects:** const is strictly enforced; unsafe relaxation is disallowed.
