# RTL: Syntax & Semantics 🔍

RTL makes C++ reflection feel like a natural extension of the language. Let’s explore its syntax and the semantics it unlocks.

### 📖 Index

1. [The `rtl::CxxMirror`](#the-rtlcxxmirror)
2. [Getting Started with Registration](#getting-started-with-registration)
3. [Querying the Metadata](#querying-the-metadata)
4. [The `rtl::RObject`](#the-rtlrobject)
5. [The `rtl::view`](#the-rtlview)
6. [Reflective Invocations with RTL](#reflective-invocations-with-rtl)
   - [`rtl::constructor`](#rtlconstructor)
   - [`rtl::function` – Type Aware](#rtlfunction--type-aware)
   - [`rtl::function` – Type Erased](#rtlfunction--type-erased)
   - [`rtl::method` – Type Aware](#rtlmethod--type-aware)
   - [`rtl::method` – Type Erased](#rtlmethod--type-erased)
7. [Perfect Forwarding](#perfect-forwarding)
8. [Error Taxonomy](#error-taxonomy)

---

## The `rtl::CxxMirror`

`rtl::CxxMirror` is the runtime entry point for querying reflection metadata registered with RTL.
It aggregates references to metadata descriptors produced by `rtl::type()...build();` registration expressions and exposes them through a unified lookup interface.

```cpp
auto cxx_mirror = rtl::CxxMirror({
    // registration expressions
});
```

Each registration expression contributes references to metadata objects that are lazily created on first use.
`rtl::CxxMirror` **does not own** this metadata and never duplicates it; it merely provides structured access to already-registered entities.

Through the mirror, all registered types, functions, and methods can be queried, inspected, and materialized at runtime. The mirror itself is a lightweight facade and does not introduce centralized global state.

#### Managing `rtl::CxxMirror`

* **No hidden global state** – `rtl::CxxMirror` is dispensable by design. You may use a single global mirror, multiple mirrors, or construct mirrors on demand. All mirrors reference the same underlying metadata cache.

* **Duplicate registration is benign** – Re-registering the same function pointer or type is safe. If matching metadata already exists, RTL reuses it; no duplicate entries are created.

* **Thread-safe by construction** – Metadata registration and access are internally synchronized. Thread safety is guaranteed regardless of how many mirrors exist or where they are constructed.

* **Registration cost is one-time** –  Each registration performs:
  * a synchronized lookup in the metadata cache
  * conditional insertion if no match exists

  This cost is incurred only during registration and is negligible for normal initialization paths. Repeated registration in hot paths should be avoided.

👉 Bottom Line
> *`rtl::CxxMirror` is a lightweight, non-owning access layer over RTL’s metadata. Its lifetime and multiplicity are entirely user-controlled, and its overhead is limited to initialization-time lookups.*

---

## Getting Started with Registration

Registration in RTL follows a builder-style composition pattern. Individual components are chained together to describe the reflected entity, and `.build()` finalizes the registration. The builder interface is exposed via the `rtl_builder.h` header.

### Non-Member Functions

```cpp
rtl::type().ns("ext").function("fn-name").build(fn-ptr);
```

* `ns("ext")` – Specifies the namespace under which the function is registered.
  Omitting `.ns()` or passing an empty string (`.ns("")`) registers the function under `rtl::global`. This is not a declared C++ namespace; rather, it is a logical, string-based grouping used to prevent naming conflicts.

* `function("fn-name")` – Declares the function by name.
  If multiple overloads exist, the template parameter (`function<...>(..)`) disambiguates the selected overload.

* `.build(fn-ptr)` – Supplies the function-pointer and completes the registration.

### Handling Overloads

If multiple overloads exist, the signature must be specified as a template argument. Otherwise, the compiler cannot resolve the intended function-pointer.

For example:

```cpp
namespace ext {
    bool sendMessage(const char*);
    void sendMessage(int, std::string);
}
```
```c++
rtl::type().ns("ext").function<const char*>("sendMessage").build(ext::sendMessage);
rtl::type().ns("ext").function<int, std::string>("sendMessage").build(ext::sendMessage);
```

### PODs / Classes / Structs

```cpp
rtl::type().ns("ext").record<T>("type-name").build();
```

* Registers a type by name and associates it with the specified namespace.
* This type (`T`) registration is **mandatory** for any of its members to be registered. The order of registration does not matter.
* The default, copy, and move constructors, along with the destructor, are registered automatically. Explicit registration of these special members is disallowed and will result in a compile-time error.

### Constructors

```cpp
rtl::type().member<T>().constructor<...>().build();
```

* `.member<T>()`: enters the scope of `T` (POD/class/struct).
* `.constructor<...>()`: registers a user-defined constructor. The template parameter `<..signature..>` must be provided since no function-pointer is available for type deduction, and this also disambiguates overloads.

### Member Functions

```cpp
rtl::type().member<T>().method<...>("method-name").build(&T::f);
```

* `.method<...>(..)`: registers a non-const member function. The template parameter `<..signature..>` disambiguates overloads.
* Variants exist for const (`.methodConst`) and static (`.methodStatic`) methods.

👉 Note
> *The `function<..signature..>` and `method<..signature..>` template parameters are primarily for overload resolution. They tell RTL exactly which overload of a function or method you mean to register.*

---

## Querying the Metadata

Once the Mirror is initialized with metadata references, it can be queried for registered entities and used to introspect types at runtime through RTL’s access interface, which is exposed via the `rtl_access.h` header.

`rtl::CxxMirror` provides lookup APIs that return reflection metadata objects.
Registered types (`class`, `struct`, or POD) are queried as `rtl::Record`, while non-member functions are queried as `rtl::Function`.
For example:

```cpp
// Function without a namespace
std::optional<rtl::Function> popMessage = cxx::mirror().getFunction("popMessage");

// Function registered with a namespace, e.g. "ext"
std::optional<rtl::Function> sendMessage = cxx::mirror().getFunction("ext", "sendMessage");
```

These metadata are returned wrapped in `std::optional`, which is empty if the requested entity is not found by the name specified.

```cpp
// Querying a type without a namespace
std::optional<rtl::Record> classPerson = cxx::mirror().getRecord("Person");

// Querying a type with a namespace, e.g. "model"
std::optional<rtl::Record> classPerson = cxx::mirror().getRecord("model", "Person");
```

* If a type or function is registered without a namespace, it must be queried without specifying a namespace.
* If a type or function is registered with a namespace, it must be queried using the same namespace.

`rtl::Record` represents any registered C++ type, including user-defined `class` and `struct` types, as well as POD types.
The term **Record** follows the naming convention used in the **LLVM** project (e.g. `CXXRecordDecl`).

All registered member functions of a type can be obtained from its corresponding `rtl::Record` as `rtl::Method` objects.
For POD types such as `char`, the type can still be registered as an `rtl::Record`.
In this case, only the implicitly supported special members (copy/move constructors and the destructor) are available.
POD types do not have member functions.

`rtl::CxxMirror` also provides an overload of `getRecord()` that accepts an `std::uintptr_t` instead of a string identifier.
This ID can be generated using `rtl::traits::uid<T>`, where `T` is a compile time known type.
The generated ID may be cached and reused for runtime lookups without requiring a namespace or string-based queries.

The `rtl::Method` and `rtl::Function` metadata objects can be further queried to determine whether a specific call signature is valid for a given function or method. This allows callers to validate argument compatibility before attempting materialization or invocation.

```c++
// Obtain metadata for the registered function.
std::optional<rtl::Function> sendMessage = cxx::mirror().getFunction("ext", "sendMessage");

// Query supported call signatures.
bool isSignature0 = sendMessage->hasSignature<const char*>();        // true
bool isSignature1 = sendMessage->hasSignature<int, std::string>();   // true
bool isSignature2 = sendMessage->hasSignature<>();                   // false (no parameters)
```
---

## The `rtl::RObject`

`rtl::RObject` exists to wrap values or objects of any type in a type-erased form while providing safe access interfaces.
It can be returned from reflective function calls, method calls, and constructor calls.
It can also be created directly from a known value or object.

Objects constructed on the **Heap** via a reflective constructor call are returned as an `rtl::RObject` and are internally managed using `std::unique_ptr` for automatic lifetime management.

Objects returned from reflective function or method calls, as well as values directly wrapped in an `rtl::RObject`, are stored on the **Stack** using `std::any`.

#### Accessing Values from `rtl::RObject`:

When working with `rtl::RObject`, the following interfaces provide safe access to the stored value:

| Function           | Purpose                                                                |
| ------------------ | ---------------------------------------------------------------------- |
| `isEmpty()`        | Checks whether the object contains a value.                            |
| `canViewAs<T>()`   | Returns `true` if the stored type is `T` or safely convertible to `T`. |
| `view<T>()`        | Returns a typed view of the stored value, or an empty `std::optional`. |
| `view<T>()->get()` | Accesses the stored value as a `const T&`.                             |

👉 Tip

> *Use `.canViewAs<T>()` for a lightweight boolean check when branching, and `.view<T>()` when you need to access the value.*

### Move Semantics with `rtl::RObject`

`rtl::RObject` is a **move-only** type. Copying is disallowed, and ownership transfer is performed exclusively through move semantics.
The behavior differs internally based on whether the underlying object is stored on the **Stack** or on the **Heap**, without any impact on the public interface or user-visible behavior.

#### Stack-Allocated Objects:

When an object is created on **Stack**, the underlying instance is stored directly inside `rtl::RObject` using `std::any`.

```cpp
rtl::RObject obj1 = rtl::RObject(std::string_view("Hello"));  // No internal heap allocation, stored on the stack.
rtl::RObject obj2 = std::move(obj1);
```

**Behavior:**

* The reflected type’s **move constructor** is invoked.
* Ownership transfers to `obj2`.
* The moved-from object (`obj1`) becomes empty.
* No duplication occurs.

👉 Mental Note
> *Stack move semantics invoke the reflected type’s move constructor.*

`rtl::RObject` itself does not perform heap allocation when wrapping stack-stored values. Any dynamic allocation that occurs is solely an implementation detail of `std::any`. By leveraging `std::any`, RTL provides controlled, type-erased storage with retained runtime type information as a safe alternative to `void*`, enforcing validated access and well-defined semantics while avoiding unchecked casts and undefined behavior.

#### Heap-Allocated Objects:

Objects on the **Heap** can only be created through a reflective constructor call. The returned instance is managed internally using `std::unique_ptr`.
Moving such an `rtl::RObject` transfers ownership of the pointer.

**Behavior:**

* The internal `std::unique_ptr` is moved.
* The reflected type’s move constructor is **not** invoked.
* Ownership transfers to the destination object.
* The moved-from object becomes empty.
* The underlying heap object remains valid until the final owner is destroyed.

👉 Mental Note
> *Heap move semantics transfer the `unique_ptr` without moving the underlying object.*

Across both **Stack** and **Heap** moves:

* The moved-from `rtl::RObject` becomes empty.
* The destination `rtl::RObject` becomes the sole owner.
* Object destruction occurs exactly once.
* Cloning or invoking a moved-from object results in `rtl::error::EmptyRObject`.

**Summary:**

When an `rtl::RObject` is moved, RTL either:

* Invokes the reflected type’s move constructor (**Stack** allocation), or
* Transfers ownership of the internal `std::unique_ptr` (**Heap** allocation).

In both cases, the source object is invalidated and ownership remains well-defined.

---

## The `rtl::view`

`rtl::view<T>` is a lightweight, immutable handle that provides safe, read-only access to a value stored inside an `rtl::RObject`.

It exists to bridge the gap between:

* type-erased storage (`rtl::RObject`), and
* typed access (`const T&`).

A `rtl::view<T>` never exposes ownership. It only exposes **observation**.

#### Properties:

* **Read-only** – A `rtl::view<T>` only provides access as `const T&`.
* **Non-owning abstraction** – Whether the underlying value is owned or referenced is intentionally hidden.
* **Non-copyable and non-movable** – A `rtl::view<T>` cannot be copied or moved and must be consumed immediately.
* **Lifetime-bound** – A `rtl::view<T>` is only valid as long as the originating `rtl::RObject` remains alive. Using a `rtl::view<T>` after the `rtl::RObject` is destroyed results in undefined behavior.

#### Access Pattern:

```cpp
auto view = robj.view<T>();
if (view) {
    const T& value = view->get();
}
```

This contract is uniform across all reflected types, including PODs, user-defined types, and standard library wrappers and smart pointers.

👉 Ongoing

> *RTL is designed to support seamless and transparent access to standard library wrapper types (such as `std::optional`, `std::variant`, `std::weak_ptr`, and others) while preserving their native semantics. At present, this behavior is fully implemented and validated only for `std::shared_ptr` and `std::unique_ptr`.*

### Smart Pointer Semantics with `rtl::view`

RTL treats smart pointers as **first-class reflected values** while preserving their native ownership rules.
No implicit deep copies are ever performed.

#### `std::shared_ptr`:

When an `rtl::RObject` reflects a `std::shared_ptr<T>`, it can be viewed either as `T` directly or as `std::shared_ptr<T>`.

While viewing directly as `T`, a `const T&` access is provided. The user may either observe the value or create copies, depending on what liberties are provided by `T`’s copy semantics.

```cpp
rtl::RObject robj = rtl::reflect(std::make_shared<int>(20438)); // std::shared_ptr is on Stack.

if (robj.canViewAs<int>()) {          // true
    int viewCpy = robj.view<int>();   // Creates a copy of int.
    const int& viewCRef = robj.view<int>(); // References the underlying value.
}
```

The same object can also be accessed as `std::shared_ptr<T>`, in which case native shared ownership semantics are preserved:

```cpp
if (robj.canViewAs<std::shared_ptr<int>>()) { // true
    auto view = robj.view<std::shared_ptr<int>>();
    {
        const std::shared_ptr<int>& sptrRef = view->get();
        bool hasSingleOwner = (sptrRef.use_count() == 1);   // true
    } {
        std::shared_ptr<int> sptrCpy = view->get();
        bool hasTwoOwners = (sptrCpy.use_count() == 2);    // true
    }
	// After temporary copies go out of scope, ownership returns to robj alone.
	bool backToSingleOwner = (view->get().use_count() == 1);   // true (robj is still alive)
}
```

Accessing a reflected `std::shared_ptr<T>` through `rtl::RObject` preserves native shared ownership semantics: observing it does not change the reference count, and copying it produces a shallow, ref-counted copy exactly as in normal C++.

#### `std::unique_ptr`:

The behavior of `std::unique_ptr` differs from `std::shared_ptr` only in its ownership model.

When an `rtl::RObject` reflects a `std::unique_ptr<T>`, it can likewise be viewed as `T` directly or as `std::unique_ptr<T>`. Viewing it as `T` provides the same `const T&` access as described earlier, and the user may observe or copy the value according to `T`’s copy semantics.

However, unlike `std::shared_ptr<T>`, a reflected `std::unique_ptr<T>` does **not** permit ownership transfer through a view:

```c++

// This is NOT allowed, std::unique_ptr is move-only
auto view = robj.view<std::unique_ptr<int>>();
std::unique_ptr<int> uptrCpy = view->get();  // ERROR: cannot copy unique_ptr

// the pointee can be accessed
if (robj.canViewAs<int>()) {
    int value = robj.view<int>()->get(); // Creates a copy of int.
}

```

* Access is always provided as `const std::unique_ptr<T>&`.
* No move operation is possible through `rtl::view`.
* Ownership remains exclusively with the `rtl::RObject`.
* The pointee can still be accessed safely via `view<T>()`.

In other words, within RTL:

* `std::shared_ptr` exposes shared-ownership semantics because it is copy-constructible and reference-counted.
* `std::unique_ptr` is treated as an exclusive-ownership wrapper whose lifetime is managed entirely by `rtl::RObject`, because it is not copy-constructible and represents unique ownership.

---

## Reflective Invocations with RTL

`rtl::Method` and `rtl::Function` are metadata descriptors. Functions and methods cannot be directly called through these objects. Instead, RTL uses a materialization model to produce callable entities.

Callable entities are materialized by explicitly specifying the argument and return types. This design avoids a single, fully type-erased invocation path for all use cases. By requiring the user to declare the intended call signature, RTL can validate the request and select an invocation path optimized for the available type information.

When full type information is provided, materialized callables compile to **direct function-pointer** calls with near-zero overhead. When type erasure is required (for example, for an unknown return or target type), invocation proceeds through a lightweight dispatch layer with performance **comparable** to `std::function`.

👉 The Idea
> *In RTL, materialization makes the performance–flexibility trade-off explicit at each call site.*

Every type-erased reflective call returns either `std::pair<rtl::error, rtl::RObject>` or `std::pair<rtl::error, std::optional<T>>`.

* `rtl::error` indicates whether the call was successful (`rtl::error::None`) or if an error occurred.
* `rtl::RObject` or `std::optional` contains the return value if the function returns something, or is empty if the function returns `void`.

Fully type-specified callables do not return an error code (except constructors). Once materialized successfully, they are guaranteed to be safe to call.

RTL provides the following callable entities:

### `rtl::constructor`

Constructors can be materialized directly from an `rtl::Record`.
For example, an overloaded constructor can be materialized as follows:

```cpp
// classPerson is of type std::optional<rtl::Record>.
rtl::constructor<std::string, int> personCtor = classPerson->ctorT<std::string, int>();
if (personCtor) {	// Constructor successfully materialized
	auto [err, person] = personCtor(rtl::alloc::Stack, "Waldo", 42);	// Safe to call.
}
```

If no constructor is registered with the specified signature, the callable is not initialized. Calling it without validation does not throw an exception; instead, it returns `rtl::error::SignatureMismatch` in the `err` variable.

A default constructor can be materialized as follows:

```cpp
rtl::constructor<> personCtor = classPerson->ctorT();
// No validation required
auto [err, person] = personCtor(rtl::alloc::Heap);	// Safe to call.
```

The default constructor for a type `T` is implicitly registered when the type is registered using `rtl::type().record<T>()`. It is guaranteed to be materializable and safe to call. If the default constructor is not publicly accessible or is deleted,
`rtl::error::TypeNotDefaultConstructible` is returned in the `err` variable.

Objects can be constructed by specifying `rtl::alloc::Stack` or `rtl::alloc::Heap` as the first parameter. The constructed object is returned as an `rtl::RObject`, which type-erases the underlying object.

* `Heap` allocated objects are managed using `std::unique_ptr`.
* `Stack` allocated objects are stored directly in `std::any`.

### `rtl::function` – Type Aware

Non-member functions can be materialized from an `rtl::Function`:

```c++
rtl::function<std::string(float, float)> cToStr = cxx::mirror().getFunction("complexToStr")
                                                               ->argsT<float, float>()
                                                               .returnT<std::string>();
if(cToStr) {    // Function successfully materialized
    std::string result = cToStr(61, 35);
}
else {
    std::cerr << rtl::to_string(cToStr.get_init_err());
}
```

Here, the return type and argument types are fully specified at compile time.
This allows RTL to resolve the function pointer by signature and provide it wrapped in a thin callable layer that effectively reduces to a single **function-pointer hop** at runtime. The overhead is comparable to a native C-style function pointer call.

The materialized `rtl::function` must be validated before invocation. Calling it without validation may result in undefined behavior.
If materialization fails, the error can be retrieved using `get_init_err()`.
Possible error values include:

* `rtl::error::InvalidCaller`
* `rtl::error::SignatureMismatch`
* `rtl::error::ReturnTypeMismatch`

### `rtl::function` – Type Erased

If the return type is not known at compile time, `rtl::Return` can be used as the return type.
In this case, the `.returnT()` template parameter can be omitted, and `rtl::Return` will be selected automatically.

```c++
rtl::function<rtl::Return(float, float)> cToStr = cxx::mirror().getFunction("complexToStr")
                                                               ->argsT<float, float>()
                                                               .returnT();
auto [err, ret] = cToStr(61, 35);
if(err != rtl::error::None && ret.canViewAs<std::string>()) {
    std::string resultStr = ret.view<std::string>()->get(); // Safely view the returned std::string.
}
else {
    std::cerr << rtl::to_string(err);
}
```

Validation of the materialized `rtl::function` is optional in this case. Calling it without validation does not result in undefined behavior; instead, an appropriate `rtl::error` is returned. If the callable was not successfully materialized, invoking it returns the same error as `get_init_err()` on the callable, typically `rtl::error::SignatureMismatch`.

If materialization succeeds but the call fails, possible error values include:

* `rtl::error::InvalidCaller`
* `rtl::error::RefBindingMismatch`
* `rtl::error::ExplicitRefBindingRequired`

👉 Mental Note
> *Fully type-specified callables must be validated before invocation to avoid undefined behavior; type-erased callables are safe to invoke without prior validation and report errors at runtime.*

### `rtl::method` – Type Aware

To materialize a member function, the corresponding `rtl::Method` metadata must first be obtained.
This requires querying the `rtl::CxxMirror` for the desired `class` or `struct` as an `rtl::Record`.

```c++
std::optional<rtl::Record> classPerson = cxx::mirror().getRecord("Person");
if (!classPerson) { /* Type not registered. */ }

// From rtl::Record, fetch the desired member-function metadata
std::optional<rtl::Method> oGetName = classPerson->getMethod("getName");
if (!oGetName) { /* Member function not registered */ }
```

Once the `rtl::Method` is available, member functions can be materialized from it.

```c++
rtl::method<Person, std::string()> getName = oGetName->targetT<Person>().argsT()
                                                     .returnT<std::string>();
if (!getName) { // Member-function with expected signature not found.
    std::cerr << rtl::to_string(getName.get_init_err()); 
}
else {
    Person person("Alex", 23);
    std::string nameStr = getName(person)(); // Returns string 'Alex'.
}
```

#### `rtl::const_method`:

The `rtl::method` can only invoke non-`const` member functions. To invoke a `const` qualified member function, `rtl::const_method` must be used.

An `rtl::const_method` is materialized by specifying a `const` target type in the `.targetT<>()` call:
```c++
rtl::const_method<Person, std::string()> getName = oGetName->targetT<const Person>().argsT()
                                                           .returnT<std::string>();
if (getName) {
    const Person person("Alex", 23);
    std::string nameStr = getName(person)(); // Returns string 'Alex'.
}
```

Here, the target type is marked `const` via the template argument to `.targetT<const Person>()`. As a result, `rtl::const_method` only accepts a `const Person` object as its invocation target.

#### `rtl::static_method`:

To invoke a `static` member function, `rtl::static_method` is used. Static methods do not require a target object, so the `.targetT()` call is omitted:

```c++
// Assume Person::getName() is a static function registered under the same name.
rtl::static_method<std::string()> getName = oGetName->argsT().returnT<std::string>();
if (getName) {
    std::string nameStr = getName()(); // Returns a default std::string.
}
```

When the return type, target type, and argument types are fully specified, these materialized callables reduce to a **direct function-pointer** invocation at runtime.

If materialization fails, calling `rtl::method`, `rtl::const_method`, or `rtl::static_method` without validation results in undefined behavior.
The initialization error can be retrieved using `get_init_err()`.

Possible error values include:

* `rtl::error::InvalidCaller`
* `rtl::error::SignatureMismatch`
* `rtl::error::ReturnTypeMismatch`
* `rtl::error::InvalidNonStaticMethodCaller`

`rtl::error::InvalidNonStaticMethodCaller` is returned when a non-static member function is materialized without specifying a target type using `.targetT<>()`, causing it to be treated as a static function.

### `rtl::method` – Type Erased

When the concrete target type is not available at compile time, `rtl::method` can be materialized without specifying a target type.
Calling `.targetT()` without a template parameter defaults the target type to `rtl::RObject`.

```c++

// Materializing a default constructor
rtl::constructor<> personCtor = classPerson->ctorT();

// No validation required
auto [err, personObj] = personCtor(rtl::alloc::Stack); // Safe to call

rtl::method<rtl::RObject, std::string()> getName = oGetName->targetT().argsT()
                                                           .returnT<std::string>();
auto [err0, ret] = getName(personObj)();	// Invoke and receive return as std::optional<std::string>.
if (err0 == rtl::error::None && ret.has_value()) {
    std::string nameStr = ret.value();
}
```
In this case, the typed return value is wrapped in `std::optional`. If the member function returns `void`, the optional is empty.

Along with the target type, the return type can also be erased. Leaving the `.returnT()` template parameter empty defaults the return type to `rtl::Return`.

```c++

rtl::method<rtl::RObject, rtl::Return()> getName = oGetName->targetT().argsT().returnT();

auto [err0, ret] = getName(personObj)();	// Invoke and receive return as rtl::RObject.
if (err0 == rtl::error::None && ret.canViewAs<std::string>()) {
    std::string nameStr = ret.view<std::string>()->get(); // Safely view the returned std::string.
}
```

And finally, If the target type is known but the return type is erased:

```c++
rtl::method<Person, rtl::Return()> getName = oGetName->targetT<Person>().argsT().returnT();
```
For static methods, `rtl::static_method` is used and `.targetT()` is omitted:

```c++
rtl::static_method<rtl::Return()> getName = oGetName->argsT().returnT();
```

All of these variants follow the same invocation semantics. The only difference is the return representation:

* Known return types are returned as `std::optional`
* Erased return types are returned as `rtl::RObject`

#### `const` and non-`const` Member Functions with Type-Erased Targets:

There is no separate callable entity such as `rtl::const_method` for type-erased invocation of `const`-qualified member function overloads.
The same `rtl::method` is used for both `const` and non-`const` member functions.
To invoke a `const` member function, the target must be passed as a `const` reference:

```c++
auto [err, ret] = getName(std::cref(personObj))();
```
This call will succeed only if a `const`-qualified overload of `Person::getName()` exists. If it does not, the call returns `rtl::error::ConstOverloadMissing`.

If only a `const` overload exists and a non-`const` target is provided, the call returns `rtl::error::NonConstOverloadMissing`.

When both `const` and non-`const` overloads are registered, the following rules apply:

* Passing a non-`const` target binds to the non-`const` overload.
* Passing a `const` target (`std::cref(personObj)`) binds to the `const` overload.

👉 Note 
> *RTL does not perform automatic `const`/non-`const` overload resolution. The intended overload must be selected explicitly by the user through the target’s `const` qualification.*

As with `rtl::function`, validation of the materialized `rtl::method` is optional in this case.
Calling it without validation does not result in undefined behavior; instead, an appropriate `rtl::error` is returned. If the callable was not successfully materialized, invoking it returns the same error as `get_init_err()` on the callable, typically `rtl::error::SignatureMismatch`.

If materialization succeeds but the call fails, possible error values include:

* `rtl::error::InvalidCaller`
* `rtl::error::ConstOverloadMissing`
* `rtl::error::NonConstOverloadMissing`
* `rtl::error::RefBindingMismatch`
* `rtl::error::ExplicitRefBindingRequired`
* `rtl::error::EmptyRObject`

---

## Perfect Forwarding

When multiple reference-based overloads of the same function signature exist, for example:

```c++
std::string reverse(std::string);              // (1) by value
std::string reverse(std::string&);             // (2) lvalue ref
std::string reverse(const std::string&);       // (3) const lvalue ref
std::string reverse(std::string&&);            // (4) rvalue ref

```

In standard C++, invoking `reverse` by name with such an overload set results in a compile-time ambiguity error.
This occurs because the pass-by-value overload conflicts with every reference-based overload, and overload resolution cannot establish a single best match.

If these functions are not invoked by name, but instead referenced through explicitly typed function-pointers, each overload can be selected unambiguously:

```c++
auto fptr0 = static_cast<std::string(*)(std::string)>(reverseString);
auto fptr1 = static_cast<std::string(*)(std::string&&)>(reverseString);
auto fptr3 = static_cast<std::string(*)(std::string&)>(reverseString);
auto fptr2 = static_cast<std::string(*)(const std::string&)>(reverseString);
```
Here, the explicit function-pointer type fully specifies the intended overload, bypassing overload resolution ambiguity.
Since RTL requires only a distinct function-pointer to register a function or method, all of the above overloads can be registered without ambiguity. 

During invocation, where the compiler would reject a direct call due to pass-by-value overload ambiguity, RTL instead deterministically defaults to the **pass-by-value** overload unless a more specific intent is explicitly expressed by the user.

Meaning, if all such overloads are registered and an `rtl::function<rtl::Return(std::string)>` is materialized and invoked, the call will unambiguously bind to the **pass-by-value** overload.

This behavior follows directly from the fact that RTL invocation is equivalent to calling through a fully specified function-pointer, which is explicitly permitted by standard C++.

#### Reference Binding:

Each overload shown above can be invoked by explicitly providing the intended call signature as a template parameter to `bind<>()`. RTL then perfect-forwards the arguments to the selected overload:

```c++
rtl::function<rtl::Return(std::string)> reverseStr = cxx::mirror().getFunction("reverseString")
                                                                  .argsT().returnT();

auto [err0, ret0] = reverseStr("Hello");                         // calls by-value overload (1)
auto [err1, ret1] = reverseStr.bind<std::string&>()("Hello");    // calls lvalue-ref overload (2)
auto [err2, ret2] = reverseStr.bind<const std::string&>()("Hello"); // calls const lvalue-ref overload (3)
auto [err3, ret3] = reverseStr.bind<std::string&&>()("Hello");   // calls rvalue-ref overload (4)
```

If no pass-by-value overload is registered, explicit binding is required to invoke the desired overload. Otherwise, the call results in `rtl::error::ExplicitRefBindingRequired`.

Now consider a case where only overloads (2) and (3) are registered:

```c++
std::string reverse(std::string&);             // (2)
std::string reverse(const std::string&);       // (3)
```

Both overloads can be invoked explicitly using `bind<>()`. However, if the user attempts to bind a signature that has not been registered, for example:

```c++
auto [err, ret] = reverseStr.bind<std::string&&>()("Hello");
```

the invocation fails with `rtl::error::RefBindingMismatch`, as no rvalue-reference overload exists in the registered overload set. Now consider the case where only overload (3) is registered:

```c++
std::string reverse(const std::string&);  // (3)
```

In this case, no explicit binding is required, as there is no overload ambiguity and the function guarantees that the argument will not be modified. If only overload (2) or only overload (4) is registered:

```c++
std::string reverse(std::string&);    // (2)
std::string reverse(std::string&&);   // (4)
```

explicit binding is required, even when these overloads exist in isolation. This is because both signatures permit mutation of the argument, and RTL requires such intent to be expressed explicitly by the user.

👉 Rationale
> *RTL’s philosophy is to make mutating calls loud and explicit, as reflection inherently hides type information.*

---

## Error Taxonomy

The table below lists RTL errors with brief, intent-focused descriptions, providing a direct mapping from failure conditions to their semantic meaning.

| Error                          | semantic meaning                                                                |
| ------------------------------ | ------------------------------------------------------------------------------- |
| `None`                         | Operation completed successfully; no error occurred.                            |
| `EmptyRObject`                 | The `RObject` is empty, typically due to a move or invalidation.                |
| `InvalidCaller`                | The callable was never successfully materialized or is otherwise invalid.       |
| `SignatureMismatch`            | No registered overload matches the requested call signature.                    |
| `TargetTypeMismatch`           | The bound target object type is incompatible with the method’s expected target. |
| `ReturnTypeMismatch`           | The specified return type does not match the function’s actual return type.     |
| `RefBindingMismatch`           | Reference qualifiers of the arguments do not match any registered overload.     |
| `ExplicitRefBindingRequired`   | Overload set allows mutation; binding intent must be stated explicitly.         |
| `InvalidNonStaticMethodCaller` | A non-static method was invoked without providing a valid target object.        |
| `ConstOverloadMissing`         | A const-qualified overload does not exist for the given invocation.             |
| `NonConstOverloadMissing`      | A non-const overload does not exist as explicitly requested.                    |
| `InvalidCallOnConstTarget`     | A non-const method was invoked on an object reflecting const state.             |
| `TypeNotCopyConstructible`     | The reflected type cannot be copy-constructed due to access or deletion.        |
| `TypeNotDefaultConstructible`  | The reflected type cannot be default-constructed.                               |

---
***More to come...***
