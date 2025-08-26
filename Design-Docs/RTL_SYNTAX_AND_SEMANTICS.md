# RTL at a Glance: Syntax & Semantics ⚡

RTL makes C++ reflection feel like a natural extension of the language. Let’s explore its syntax and the semantics it unlocks.
This guide walks you step by step through RTL’s reflection syntax.

## Building the Mirror 🪞

Before registering anything, we need a central place to hold all reflection metadata: the `rtl::CxxMirror`. Its constructor takes an initializer list containing all the type metadata.

```cpp
const rtl::CxxMirror& cxx_mirror()
{
    static rtl::CxxMirror cxxMirror({
        // .. all the registrations go here, comma separated ..
    });
    return cxxMirror;
}
```

The `CxxMirror` remains immutable throughout the application. Declaring it as a `static` local instance ensures one-time initialization and global availability, making initialization inherently thread-safe. RTL internally manages registration safety, but this design also leverages compiler guarantees for automatic thread-safety.

> *Tip: Always use the singleton pattern for ************`CxxMirror`************. It guarantees stability, thread-safe lazy initialization, and provides a predictable reflective universe.*

**Note:** Every registration you make using the builder pattern is collected into the `CxxMirror` as an `rtl::Function` object. The `CxxMirror` forms the backbone of RTL. Every type, function, or method you register ultimately gets encapsulated into this single object, serving as the gateway to query, introspect, and instantiate all registered types at runtime.

## Getting Started with Registration

The fundamental pattern of registration in RTL is a **builder combination**. You chain together parts to declare what you are reflecting, and then call `.build()` to complete it.

### Non-Member Functions

```cpp
rtl::Reflect().nameSpace("ns").function<..signature..>("func").build(ptr);
```

* **`nameSpace("ns")`**: specifies the namespace under which the function lives. If you want global scope, pass an empty string: `.nameSpace("")`. The call itself cannot be omitted when registering functions or records.
* **`function<..signature..>("func")`**: declares the function by name. If overloaded, the template parameter `<..signature..>` disambiguates which overload to pick.
* **`.build(ptr)`**: supplies the actual function pointer to complete the registration.

### Handling Overloads

If multiple overloads exist, you must specify the signature in the template argument. Otherwise, the compiler cannot resolve which function pointer you mean.

For example:

```cpp

bool sendMessage(const char*);
void sendMessage(int, std::string);

rtl::Reflect().nameSpace("ns").function<const char*>("sendMessage").build(sendMessage);
rtl::Reflect().nameSpace("ns").function<int, std::string>("sendMessage").build(sendMessage);
```

### Classes / Structs

```cpp
rtl::Reflect().nameSpace("ns").record<T>("Name").build();
```

* Registers a type by reflective name under a namespace.
* This step is **mandatory** to register any of its members.
* Default, copy, and move constructors, along with the destructor, are automatically registered. Explicit registration of these special members is disallowed and will result in a compile error.

### Constructors

```cpp
rtl::Reflect().member<T>().constructor<..signature..>().build();
```

* **`.member<T>()`**: enters the scope of class/struct `T`.
* **`.constructor<..signature..>()`**: registers a user-defined constructor. The template parameter `<..signature..>` must be provided since no function pointer is available for deduction, and this also disambiguates overloads.

### Member Functions

```cpp
rtl::Reflect().member<T>().method<..signature..>("method").build(&T::f);
```

* **`.member<T>()`**: enters the scope of class/struct `T`.
* **`.method<..signature..>(...)`**: registers a non-const member function. The template parameter `<..signature..>` disambiguates overloads.
* Variants exist for const (`.methodConst`) and static (`.methodStatic`) methods.

> **Note:** The `function<..signature..>` and `method<..signature..>` template parameters are primarily for overload resolution. They tell RTL exactly which overload of a function or method you mean to register.

---

With these constructs—namespaces, non-member functions, overloads, records `(class/struct)`, constructors, and methods—you now have the full registration syntax for RTL. Together, they let you build a complete reflective model of your C++ code.

---

# Reflective Programming with RTL ⚡

Discover how to query, invoke, and manipulate functions and objects at runtime using RTL’s powerful reflection API.

## Accessing and Invoking Functions

Once a function is registered in `rtl::CxxMirror`, you can query it and perform reflective calls dynamically.

### Querying Functions

```cpp
// Function without a namespace
std::optional<rtl::Function> popMessage = cxx_mirror().getFunction("popMessage");

// Function registered with a namespace
std::optional<rtl::Function> sendMessage = cxx_mirror().getFunction("utils", "sendMessage");
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

### Performing Reflective Calls

Once you have a `rtl::Function`, a complete reflective call involves two steps:

```cpp
auto [err, retObj] = popMessage->bind().call();
```

* **`.bind<>()`**: Associates an object for member functions and allows explicit specification of the **signature** of the arguments to be forwarded. For non-member functions, you can simply call `.bind()` without arguments.
* **`.call(args...)`**: Executes the function with the provided arguments.

Every reflective call returns a `std::pair<rtl::error, RObject>`:

* `rtl::error` indicates whether the call was successful (`rtl::error::None`) or if an error occurred.
* `RObject` contains the return value if the function returns something, or is empty if the function returns `void`.

### Extracting Return Values

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

**Return Handling Summary** 📦

When dealing with `RObject` results:

| Function           | Purpose                                                                                                                 |
| ------------------ | ----------------------------------------------------------------------------------------------------------------------- |
| `isEmpty()`        | Checks if the function returned anything (i.e., non-`void`).                                                            |
| `canViewAs<T>()`   | Quick type check: returns `true` if the stored type is exactly `T` or safely convertible.                               |
| `view<T>()`        | Retrieves a typed **view** of the stored value if possible. Returns an empty `std::optional` if the type doesn’t match. |
| `view<T>()->get()` | Extracts a const reference or value of `T` from the view, safely typed.                                                 |

👉 **Tip:** Use `canViewAs<T>()` for a cheap boolean check when branching, and `view<T>()` when you actually need the value.

---

## Accessing and Invoking Member Functions 🧩

Member functions require an instance of the class to call upon. RTL provides a two-step process: first retrieve the `rtl::Record` for the type, then get the `rtl::Method` from that record.

### Querying a Member Function

```cpp
// Retrieve the record for the class
std::optional<rtl::Record> classPerson = cxx_mirror().getRecord("Person");

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

### Binding an Object and Calling

```cpp
auto [err, retObj] = setProfile->bind(targetObj).call(std::string("Developer"));
```

* **`.bind(targetObj)`**: binds the target instance for the method.

  * `targetObj` is an `RObject` instance representing the object.
  * You can create this instance reflectively using the `rtl::Record`’s constructor (we’ll cover this shortly).
* **`.call(args...)`**: executes the method on the bound object with the provided arguments.

### Binding Signatures and Perfect Forwarding

```cpp
setProfile->bind(targetObj).call(10);          // 10 forwarded as int
setProfile->bind<double>(targetObj).call(10);  // 10 forwarded as double (10.0)
setProfile->bind<std::string>(targetObj).call(10); // compile-time error
```

* The \*\*template parameter in \*\***`bind<...signature...>()`** tells RTL how to perceive and forward the arguments.
* RTL uses the template signature as a **unique ID** to select the correct method from the registration.
* All arguments are forwarded as universal references (`&&`), enabling **perfect forwarding** with **no copies**. Arguments are ultimately received exactly as the registered function expects (by-value, by-ref, const-ref).

### Return Values

```cpp
if (err == rtl::error::None)
{
    if (!retObj.isEmpty() && retObj.canViewAs<std::string>())
    {
        std::optional<rtl::view<std::string>> viewStr = retObj.view<std::string>();
        std::string retStr = viewStr->get(); // fully-typed return value
    }
}
```

* `RObject` contains the return value, or is empty if the method returns `void`.

---

> By retrieving a `Method` from a `Record`, binding a target instance, and specifying the signature as needed, RTL allows safe, perfectly-forwarded reflective calls on member functions.
