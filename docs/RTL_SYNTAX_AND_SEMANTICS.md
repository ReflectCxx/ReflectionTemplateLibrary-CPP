# RTL at a Glance: Syntax & Semantics ⚡

RTL makes C++ reflection feel like a natural extension of the language. Let’s explore its syntax and the semantics it unlocks.
This guide walks you step by step through RTL’s reflection syntax.

### 📖 Index

1. [Building the Mirror 🪞](#building-the-mirror-)
2. [Getting Started with Registration 📝](#getting-started-with-registration-)
3. [Reflective Invocations with RTL ✨](#reflective-invocations-with-rtl-)

   * [Querying C-Style Functions 🔍](#querying-c-style-functions)
   * [Performing Reflective Calls ⚙️](#performing-reflective-calls)
   * [Extracting Return Values 📤](#extracting-return-values)
   * [Querying Member Functions 👤](#querying-member-functions)
   * [Binding an Object and Calling 🔗](#binding-an-object-and-calling)
   * [Binding Signatures and Perfect Forwarding 🎯](#binding-signatures-and-perfect-forwarding)
   * [Const vs Non-Const Method Binding ⚡](#const-vs-non-const-method-binding)
4. [Reflective Construction and Destruction 🏗️](#reflective-construction-and-destruction)
5. [Move Semantics in RTL 🔀](#move-semantics-in-rtl)

---

## Building the Mirror 🪞

Before querying or using reflection, a `rtl::CxxMirror` instance is created to aggregate references to the registered entities.
The mirror is constructed using an initializer list of registration expressions, typically produced via `rtl::type<T>()`.

```cpp
auto cxx_mirror = rtl::CxxMirror({
    // registration expressions, comma separated
});
```

Each registration expression contributes references to the underlying metadata objects, which are created by RTL only if they do not already exist.
`rtl::CxxMirror` does not own or duplicate this metadata; it encapsulates references to it and acts as a lightweight access interface.

Through the mirror, all registered types, functions, and methods can be queried, inspected, and instantiated at runtime. The mirror serves as a single entry point for reflection operations without introducing centralized global state.

### Key Points on Managing `rtl::CxxMirror`

* **Dispensable by design** – `rtl::CxxMirror` carries no hidden global state. You may define a single central mirror, create multiple mirrors in different scopes, or rebuild mirrors on demand. RTL imposes no restrictions on how its lifetime is managed.

* **Duplicate registration is harmless** – Identical registrations always resolve to the same metadata. If a canonical function-pointer is already registered, it is not inserted again; subsequent registrations simply reference the existing entry.

* **Thread-safety guaranteed by RTL** – Regardless of how mirrors are managed (singleton, multiple, or transient), RTL ensures synchronized, race-free registration and access across threads.

* **Registration overhead is deliberate** – Each registration incurs a small, one-time cost in memory and initialization time:

  * A lock is acquired on the metadata cache.
  * Existing entries are checked for a function-pointer.
  * If no match is found, a new entry is inserted.

  This ensures thread safety and prevents redundant metadata. While negligible for typical usage, the cost can accumulate if registrations are repeatedly performed in hot paths or tight loops.

👉 Bottom Line
> *Manage `rtl::CxxMirror` according to your design needs– singleton, multiple, or transient. Registration involves a lock and a lookup, but the cost is incurred only during initialization and remains negligible for normal usage.*

---

## Getting Started with Registration 📝

Registration in RTL follows a builder-style composition pattern. Individual components are chained together to describe the reflected entity, and `.build()` finalizes the registration.

### Non-Member Functions

```cpp
rtl::type().ns("ext").function("func").build(ptr);
```

* **`ns("ext")`** – Specifies the namespace under which the function is registered.
  Omitting `.ns()` or passing an empty string (`.ns("")`) registers the function in the global namespace.

* **`function("func")`** – Declares the function by name.
  If multiple overloads exist, the template parameter (`function<...>("..")`) disambiguates the selected overload.

* **`.build(ptr)`** – Supplies the function pointer and completes the registration.

### Handling Overloads

If multiple overloads exist, the signature must be specified as a template argument. Otherwise, the compiler cannot resolve the intended function pointer.

For example:

```cpp

bool sendMessage(const char*);
void sendMessage(int, std::string);

rtl::type().ns("ext").function<const char*>("sendMessage").build(ext::sendMessage);
rtl::type().ns("ext").function<int, std::string>("sendMessage").build(ext::sendMessage);
```

### Classes / Structs

```cpp
rtl::type().ns("ext").record<T>("Name").build();
```

* Registers a type by name and associates it with the specified namespace.
* This type `T` registration is **mandatory** for any of its members to be registered. The order of registration does not matter.
* The default, copy, and move constructors, along with the destructor, are registered automatically. Explicit registration of these special members is disallowed and will result in a compile-time error.

### Constructors

```cpp
rtl::type().member<T>().constructor<..signature..>().build();
```

* **`.member<T>()`**: enters the scope of class/struct `T`.
* **`.constructor<..signature..>()`**: registers a user-defined constructor. The template parameter `<..signature..>` must be provided since no function pointer is available for deduction, and this also disambiguates overloads.

### Member Functions

```cpp
rtl::type().member<T>().method<..signature..>("method").build(&T::f);
```

* **`.member<T>()`**: enters the scope of class/struct `T`.
* **`.method<..signature..>(...)`**: registers a non-const member function. The template parameter `<..signature..>` disambiguates overloads.
* Variants exist for const (`.methodConst`) and static (`.methodStatic`) methods.

👉 **Note:** 
> ***The `function<..signature..>` and `method<..signature..>` template parameters are primarily for overload resolution. They tell RTL exactly which overload of a function or method you mean to register.***

With these constructs–namespaces, non-member functions, overloads, records `(class/struct)`, constructors, and methods–you now have the full registration syntax for RTL. Together, they let you build a complete reflective model of your C++ code.

---

## Reflective Invocations with RTL ✨

Discover how to query, invoke, and manipulate functions and objects at runtime using RTL’s powerful reflection API.
Once a function is registered in `rtl::CxxMirror`, you can query it and perform reflective calls dynamically.

<a id="querying-c-style-functions" name="querying-c-style-functions"></a>

### Querying C-Style Functions 🔍

```cpp
// Function without a namespace
std::optional<rtl::Function> popMessage = cxx::mirror().getFunction("popMessage");

// Function registered with a namespace
std::optional<rtl::Function> sendMessage = cxx::mirror().getFunction("utils", "sendMessage");
```

* If a function is registered **without a namespace**, it can only be retrieved without specifying a namespace.
* If a function is registered **with a namespace**, it **must** be queried with the correct namespace.
* The returned value is an `std::optional<rtl::Function>`. If the function is not found, the optional is empty.

```cpp
if (popMessage)
{
    // function exists, safe to invoke
}
```
---

<a id="performing-reflective-calls" name="performing-reflective-calls"></a>

### Performing Reflective Calls ⚙️

Once you have a `rtl::Function`, a complete reflective call involves two steps:

**[THIS API IS REMOVED, NOW CALLABLES ARE USED. DOC NOT UPDATED YET]**

```cpp
auto [err, retObj] = popMessage->bind().call();
```

* **`.bind<>()`**: Associates an object for member functions and allows explicit specification of the **signature** of the arguments to be forwarded. For non-member functions, you can simply call `.bind()` without arguments.
* **`.call(args...)`**: Executes the function with the provided arguments.

Every reflective call returns a `std::pair<rtl::error, rtl::RObject>`:

* `rtl::error` indicates whether the call was successful (`rtl::error::None`) or if an error occurred.

  * `rtl::error::SignatureMismatch` → provided arguments/signature don’t match with expected signature or any overload.
* `rtl::RObject` contains the return value if the function returns something, or is empty if the function returns `void`.

---

<a id="extracting-return-values" name="extracting-return-values"></a>

### Extracting Return Values 📤

```cpp
if (err == rtl::error::None)
{
    if (!retObj.isEmpty() && retObj.canViewAs<std::string>())
    {
        std::optional<rtl::view<std::string>> viewStr = retObj.view<std::string>();
        std::string retStr = viewStr->get(); // fully-typed returned string
    }
}
```

* Return Handling Summary

When dealing with `rtl::RObject` results:

| Function           | Purpose                                                                                                                 |
| ------------------ | ----------------------------------------------------------------------------------------------------------------------- |
| `isEmpty()`        | Checks if the function returned anything (i.e., non-`void`).                                                            |
| `canViewAs<T>()`   | Quick type check: returns `true` if the stored type is exactly `T` or safely convertible.                               |
| `view<T>()`        | Retrieves a typed **view** of the stored value if possible. Returns an empty `std::optional` if the type doesn’t match. |
| `view<T>()->get()` | Extracts a const reference or value of `T` from the view, safely typed.                                                 |

👉 **Tip**

> ***Use `canViewAs<T>()` for a cheap boolean check when branching, and `view<T>()` when you actually need the value.***

---

<a id="querying-member-functions" name="querying-member-functions"></a>

### Querying Member Functions 👤

Member functions require an instance of the class to call upon. RTL provides a two-step process: first retrieve the `rtl::Record` for the type, then get the `rtl::Method` from that record.

```cpp
// Retrieve the record for the class
std::optional<rtl::Record> classPerson = cxx::mirror().getRecord("Person");

if (classPerson)
{
    // Retrieve a specific method from the record
    std::optional<rtl::Method> setProfile = classPerson->getMethod("setProfile");

    if (setProfile)
    {
        // You can now bind an object and call the method
    }
}
```

* `getRecord("TypeName")` returns the registered class/struct as `rtl::Record`.
* `getMethod("methodName")` retrieves a member function from the record. Returns `std::optional<rtl::Method>`.
* An empty optional indicates the method was not found.

---

<a id="binding-an-object-and-calling" name="binding-an-object-and-calling"></a>

### Binding an Object and Calling 🔗

**[THIS API IS REMOVED, NOW CALLABLES ARE USED. DOC NOT UPDATED YET]**

```cpp
auto [err, retObj] = setProfile->bind(targetObj).call(std::string("Developer"));
```

* **`.bind(targetObj)`**: binds the target instance for the method.

  * `targetObj` is an `rtl::RObject` instance representing the object.
  * You can create this instance reflectively using the `rtl::Record`’s constructor (we’ll cover this shortly).
* **`.call(args...)`**: executes the method on the bound object with the provided arguments.

Errors specific to member function calls:

* `rtl::error::TargetMismatch` → when the bound `RObject` does not represent the same type as the method’s owning class.
* `rtl::error::EmptyTarget` → when attempting to bind an empty `RObject`.
* `rtl::error::SignatureMismatch` → provided arguments/signature don’t match with expected signature or any overload.

---

<a id="binding-signatures-and-perfect-forwarding" name="binding-signatures-and-perfect-forwarding"></a>

### Binding Signatures and Perfect Forwarding 🎯

**[THIS API IS REMOVED, NOW CALLABLES ARE USED. DOC NOT UPDATED YET]**

```cpp
setProfile->bind(targetObj).call(10);          // 10 forwarded as int
setProfile->bind<double>(targetObj).call(10);  // 10 forwarded as double (10.0)
setProfile->bind<std::string>(targetObj).call(10); // compile-time error
```

* The template parameter in `bind<..signature..>()` tells RTL how to perceive and forward the arguments.
* RTL uses the template signature to ***figure out*** which method (and which overload, if multiple exist) to select from the registration.
* All arguments are forwarded as universal references (`&&`), enabling **perfect forwarding** with **no copies**. Arguments are ultimately received exactly as the registered function expects (`lvalue`, `rvalue`, `const-lvalue-ref`).
* `rtl::RObject` contains the return value, or is empty if the method returns `void`.

> ***By retrieving a `Method` from a `Record`, binding a target instance, and specifying the signature as needed, RTL allows safe, perfectly-forwarded reflective calls on member functions.***

---

<a id="const-vs-non-const-method-binding" name="const-vs-non-const-method-binding"></a>

### Const vs Non-Const Method Binding ⚡

**[THIS SECTION NEEDS TO BE UPDATED AS PER THE NEW CALLABLES]**

When binding methods reflectively, RTL enforces const-correctness in a way that mirrors C++ itself, but with an extra layer of runtime safety. Let’s walk through how this works.

#### Default Behavior

Whenever both `const` and `non-const` overloads of a method exist, RTL prefers the **const overload**. This is consistent with RTL’s *const-by-default* philosophy: reflective calls always begin from the safest stance possible.

```cpp
Person john("John");
rtl::RObject robj = rtl::type(john);    // Reflect object with statically-type; details covered later.

// If both overloads exist, RTL selects the const one.
auto [err, ret] = someMethod->bind(robj).call();
```

#### Choosing the Non-Const Path

[THIS API IS REMOVED, NOW CALLABLES ARE USED. DOC NOT UPDATED YET]
Sometimes you really do want the non-const overload. RTL requires you to be explicit in that case, by using `rtl::constCast()`:

```cpp
auto [err, ret] = someMethod->bind(rtl::constCast(robj)).call();
```

This signals intent clearly: *“Treat this object as non-const for this call.”* If the object is safe to cast, RTL allows it.

#### Fallback to Non-Const

If a class only defines a non-const method and no const variant exists, RTL will safely fall back and bind to the non-const overload. No extra steps are required, and this remains safe so long as the object wasn’t originally declared `const`.

#### Declared-Const Objects

Things change when the reflected object itself was declared `const` in the first place:

```cpp
const Person constSam("Const-Sam");    // Reflect 'const' with statically-type; details covered later.
rtl::RObject robj = rtl::type(constSam);
```

Here, RTL preserves that constness strictly. Non-const methods cannot be invoked on such an object. Attempts to do so will result in `rtl::error::IllegalConstCast`.

If you attempt a method where **no const overload exists**, RTL reports `rtl::error::ConstOverloadMissing`.

#### Checking Provenance

Because reflective calls may hand back new `RObject`s, you may sometimes wonder whether an object is safe to cast. That’s what `isConstCastSafe()` is for:

```cpp
bool safe = robj.isConstCastSafe();
```

* `false` → The object was originally declared const; treating it as mutable is unsafe.
* `true` → The object wasn’t originally const; RTL may relax constness internally if needed.

#### Error Codes

* **None** → Success; call resolved safely.
* **ConstOverloadMissing** → A const-qualified overload was required but not found.
* **NonConstOverloadMissing** → A non-const overload was explicitly requested but not found.
* **IllegalConstCast** → Attempted to cast away `const` from a true-const object.

#### Summary

* RTL defaults to the const overload when both exist.
* Explicitly request the non-const overload with `rtl::constCast()`.
* If only non-const exists, RTL uses it safely (unless the object was declared const).
* Declared-const objects reject non-const calls (`rtl::error::IllegalConstCast`) and fail if no const overload is present (`rtl::error::ConstOverloadMissing`).
* `isConstCastSafe()` tells you whether relaxation is permitted.
* Reflective objects are always const-first; declared-const objects are strictly immutable.

---

<a id="reflective-construction-and-destruction" name="reflective-construction-and-destruction"></a>
## Reflective Construction and Destruction 🏗️

Reflection in RTL doesn’t stop at functions and methods – you can also create full-fledged objects at runtime, directly through their reflected constructors. Cleanup, on the other hand, is fully automatic thanks to C++’s RAII.

### Constructing Objects

To construct a reflected object, first grab the `Record` that represents the type, then call one of its `create` helpers:

```cpp
std::optional<rtl::Record> classPerson = cxx::mirror().getRecord("Person");

// Default constructor – create on heap

[THIS API IS REMOVED, NOW CALLABLES ARE USED. DOC NOT UPDATED YET]
auto [err, person] = classPerson->create<alloc::Heap>();

if (err == rtl::error::None)
{
    // construction successful, use object to call methods now...
}

// Overloaded constructor – this time create on stack

[THIS API IS REMOVED, NOW CALLABLES ARE USED. DOC NOT UPDATED YET]
auto [err, person] = classPerson->create<alloc::Stack>(
    std::string("John Doe"),
    42
);
```

Key takeaways:

* Allocation policy is always explicit – you decide `Heap` or `Stack`.
* Creation returns `[rtl::error, rtl::RObject]`.
* If construction fails, `error != rtl::error::None` and the `RObject` will be empty.
* `rtl::error::SignatureMismatch` if provided arguments/signature don’t match with expected signature or any overload.
* `RObject` is the type-erased container that can hold either:

  * An instance created via a reflected constructor.
  * A return value from any reflected call (as we have already seen earlier).

### Destruction Semantics

RTL does **not** give you a “destroy” API. All lifetime management is pure **RAII**:

* **Heap objects** → wrapped in `std::unique_ptr`, destroyed automatically when the owning `RObject` goes out of scope.
* **Stack objects** → destroyed at scope exit like any local variable.
* **Return values** → temporary values that follow normal C++ value semantics.

This design is intentional:

* No risk of manual double-free or dangling references.
* Mirrors idiomatic C++ usage – you never call destructors explicitly in regular code, and you don’t here either.

**Bottom line:** you never destroy a reflected object yourself – RAII does it for you.

### Creating Reflected Objects With Static-Type

Besides constructing objects via reflective calls (`create<Heap>()` or `create<Stack>()`), RTL also lets you create an `RObject` by **reflecting an existing object**:

```cpp
Person mutableSam("Mutable-Sam");
const Person constSam("Const-Sam");

rtl::RObject robj1 = rtl::type(mutableSam);
rtl::RObject robj2 = rtl::type(constSam);
```

* This always creates a **copy on the stack** inside the `RObject`.
* These stack-based reflections are **scope bound** and never heap-managed.
* Useful for **testing**, since you can quickly reflect arbitrary statically-typed objects.

---

<a id="move-semantics-in-rtl" name="move-semantics-in-rtl"></a>
## Move Semantics in RTL 🔀

Let’s walk you through how **move semantics** work in RTL. Since `rtl::RObject` is **move-only** (copying is disallowed), moving objects is the primary way ownership is transferred. The behavior differs depending on whether the object was created on the **stack** or the **heap**.

### Moving Stack-Allocated Objects

When you create an object reflectively with `alloc::Stack`, the underlying instance lives directly inside the `RObject`. Moving such an `RObject` looks just like a regular C++ move:

```cpp
RObject obj1 = /* created on stack */;
RObject obj2 = std::move(obj1);
```
**What happens here:**

* The reflected type’s **move constructor** is invoked.
* Ownership of the object transfers into `obj2`.
* The moved-from object (`obj1`) becomes **empty**.
* No duplication or destruction happens – the object is simply relocated.

👉 **Key idea:** 
> *Stack move = reflected type’s move constructor is called.*

### Moving Heap-Allocated Objects

When you create an object reflectively with `alloc::Heap`, the instance is managed inside a **`std::unique_ptr<T>`**. Moving such an `RObject` also uses standard C++ move semantics:

```cpp
RObject obj1 = /* created on heap */;
RObject obj2 = std::move(obj1);
```
**What happens here:**

* The internal `unique_ptr` is moved.
* No move constructor of the reflected type is called.
* Ownership transfers to `obj2`.
* The moved-from object (`obj1`) becomes **empty**.
* The underlying heap object remains untouched and alive until its final owner is destroyed.

👉 **Key idea** 
> ***Heap move = `unique_ptr` move semantics (cheap pointer transfer).***

### Consistent Guarantees 🟨

Across both stack and heap moves:

* The moved-from `RObject` is always **empty**.
* The destination `RObject` becomes the sole owner.
* RAII ensures proper cleanup – objects are destroyed once and only once.
* Cloning or invoking a moved-from object results in `rtl::error::EmptyRObject`.

✅ Bottom Line
> ***“When you move an `RObject`, RTL either calls your type’s move constructor (stack) or transfers ownership of its `unique_ptr` (heap). In both cases, the source is emptied and ownership remains safe.”***

---

***More to come...***
