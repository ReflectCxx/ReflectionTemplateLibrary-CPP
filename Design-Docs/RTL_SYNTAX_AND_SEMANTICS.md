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

> *Tip: Always use the singleton pattern for **`CxxMirror`**. It guarantees stability, thread-safe lazy initialization, and provides a predictable reflective universe.*

**Note:** Every registration you make using the builder pattern is collected into the `CxxMirror` as an `rtl::Function` object. The `CxxMirror` forms the backbone of RTL. Every type, function, or method you register ultimately gets encapsulated into this single object, serving as the gateway to query, introspect, and instantiate all registered types at runtime.

## Getting Started with Registration

The fundamental pattern of registration in RTL is a **builder combination**. You chain together parts to declare what you are reflecting, and then call `.build()` to complete it.

### Non-Member Functions

```cpp
Reflect().nameSpace("ns").function<..signature..>("func").build(ptr);
```

* **`nameSpace("ns")`**: specifies the namespace under which the function lives. If you want global scope, pass an empty string: `.nameSpace("")`. The call itself cannot be omitted when registering functions or records.
* **`function<..signature..>("func")`**: declares the function by name. If overloaded, the template parameter `<..signature..>` disambiguates which overload to pick.
* **`.build(ptr)`**: supplies the actual function pointer to complete the registration.

### Handling Overloads

If multiple overloads exist, you must specify the signature in the template argument. Otherwise, the compiler cannot resolve which function pointer you mean.

For example:

```cpp
void sendMessage(int id, std::string msg);
bool sendMessage(const char*);

Reflect().nameSpace("ns").function<const char*>("sendMessage").build(sendMessage);
Reflect().nameSpace("ns").function<int, std::string>("sendMessage").build(sendMessage);
```

### Classes / Structs

```cpp
Reflect().nameSpace("ns").record<T>("Name").build();
```

* Registers a type by reflective name under a namespace.
* This step is **mandatory** to register any of its members.
* Default, copy, and move constructors, along with the destructor, are automatically registered. Explicit registration of these special members is disallowed and will result in a compile error.

### Constructors

```cpp
Reflect().member<T>().constructor<..signature..>().build();
```

* **`.member<T>()`**: enters the scope of class/struct `T`.
* **`.constructor<..signature..>()`**: registers a user-defined constructor. The template parameter `<..signature..>` must be provided since no function pointer is available for deduction, and this also disambiguates overloads.

### Member Functions

```cpp
Reflect().member<T>().method<..signature..>("method").build(&T::f);
```

* **`.member<T>()`**: enters the scope of class/struct `T`.
* **`.method<..signature..>(...)`**: registers a non-const member function. The template parameter `<..signature..>` disambiguates overloads.
* Variants exist for const (`.methodConst`) and static (`.methodStatic`) methods.

> **Note:** The `function<..signature..>` and `method<..signature..>` template parameters are primarily for overload resolution. They tell RTL exactly which overload of a function or method you mean to register.

---

With these constructs—namespaces, non-member functions, overloads, records `(class/struct)`, constructors, and methods—you now have the full registration syntax for RTL. Together, they let you build a complete reflective model of your C++ code.

## Our Playground: `struct Person` and `namespace ext` 🛠️

Throughout this guide, we’ll reflect over the following class and namespace. All registration and semantic examples come from these declarations:

```cpp
struct Person
{
    const std::string name;          // identity locked in once constructed

    Person(std::string&);            // construct from mutable string
    Person(const std::string&);      // construct from const string

    std::string getName();           // returns the name

    std::string setTitle(std::string&&);        // rvalue overload
    std::string setProfile(std::string);        // by value
    std::string setProfile(std::string&);       // lvalue overload
    std::string setOccupation(std::string&&);   // rvalue overload
    std::string setOccupation(const std::string&); // const-ref overload

    std::string updateAddress();     // non-const version
    std::string updateAddress() const; // const version

    static std::string getDefaults(); // handy static function
};

namespace ext
{
    static std::string sendAsString(Person);      // pass by value
    static std::string sendAsString(Person&&);    // pass by rvalue
    static std::string sendAsString(const char*); // convenience overload

    static std::string sendString(std::string);   // another free helper
}
```

With this as our foundation, we can explore how RTL reflects each piece.

RTL exposes a **fluent API** that lets you describe C++ constructs as if you were writing in a small reflective DSL. The syntax declares intent, while the semantics follow C++ language rules.
































# RTL at a Glance: Syntax & Semantics

**"RTL makes C++ reflection feel like a natural extension of the language. Let’s explore its syntax and the semantics it unlocks."**

---

This guide walks you step by step through RTL’s reflection syntax.

---

## Our Playground: `struct Person` and `namespace ext`

Throughout this guide, we’ll reflect over the following class and namespace. Every registration and semantic example comes from these declarations:

```cpp
struct Person
{
    const std::string name;          // identity locked in once constructed

    Person(std::string&);            // construct from mutable string
    Person(const std::string&);      // construct from const string

    std::string getName();           // returns the name

    std::string setTitle(std::string&&);        // rvalue overload
    std::string setProfile(std::string);        // by value
    std::string setProfile(std::string&);       // lvalue overload
    std::string setOccupation(std::string&&);   // rvalue overload
    std::string setOccupation(const std::string&); // const-ref overload

    std::string updateAddress();     // non-const version
    std::string updateAddress() const; // const version

    static std::string getDefaults(); // handy static function
};

namespace ext
{
    static std::string sendAsString(Person);      // pass by value
    static std::string sendAsString(Person&&);    // pass by rvalue
    static std::string sendAsString(const char*); // convenience overload

    static std::string sendString(std::string);   // another free helper
}
```

With this as our foundation, let’s see how RTL reflects each piece.

---

RTL exposes a fluent API that lets you describe C++ constructs as if you were writing in a small reflective DSL.  
The syntax declares intent; the semantics follow C++ language rules.

---

## Getting Started with Registration

The fundamental pattern of registration in RTL is a **builder combination**. You chain together parts to declare what you are reflecting, and then call `.build()` to complete it.

### Non-Member Functions,

```cpp
Reflect().nameSpace("ns").function<Signature>("func").build(ptr);
```

- **`nameSpace("ns")`**: specifies the namespace under which the function lives. Use `.nameSpace()` with no argument for global scope.
- **`function<Signature>("func")`**: declares the function by name. If overloaded, the template argument `Signature` disambiguates which overload to pick.
- **`.build(ptr)`**: supplies the actual function pointer to complete the registration.

### Classes / Structs

```cpp
Reflect().nameSpace("ns").record<T>("Name").build();
```

- **Registers a type** by reflective name under a namespace.
- This step is **mandatory** to register any of its members.

### Member Functions

```cpp
Reflect().member<T>().method<Signature>("method").build(&T::f);
```

- **`.member<T>()`**: enters the scope of class/struct `T`.
- **`.method<Signature>(...)`**: registers a non-const member function. Template parameter `Signature` is used to disambiguate overloads.
- Variants exist for const (`.methodConst`) and static (`.methodStatic`) methods.

> **Note:** The `function<>` and `method<>` template parameters are primarily used for overload resolution. They tell RTL exactly which overload of a function or method you mean to register.

---

## Namespaces

- `.nameSpace("ns")`  
  - **Syntax:** scopes a function or record into namespace `ns`.  
  - **Semantics:** lookup requires the namespace; absence of namespace implies global scope.  

---

## Records (Classes/Structs)

- `.record<T>("Name").build()`  
  - **Syntax:** registers type `T` under a reflective name.  
  - **Semantics:**  
    - Default/copy/move constructors and destructor are automatically registered.  
    - Explicit registration of these special members is disallowed.  
    - Instance creation through reflection follows C++ constructor overload rules.  

---

## Free Functions

- `.function("Name").build(ptr)`  
  - **Syntax:** registers a free function by pointer.  
  - **Semantics:**  
    - If overloaded, the parameter type must be specified: `.function<T>(...)`.  
    - Invocation requires no instance.  
    - Lookup is fully qualified by namespace if declared.  

---

## Member Functions

### Non-const
- `.member<T>().method("Name").build(&T::f)`  
  - **Syntax:** registers a non-const member function.  
  - **Semantics:**  
    - Can only be called on non-const objects.  
    - Calling on true-const yields `ConstCallViolation`.  
    - Logically-const objects created by RTL may allow safe const_cast under the hood.  

### Const
- `.member<T>().methodConst("Name").build(&T::f)`  
  - **Syntax:** registers a const-qualified member function.  
  - **Semantics:** callable on const and non-const objects.  

### Static
- `.member<T>().methodStatic("Name").build(&T::f)`  
  - **Syntax:** registers a static member function.  
  - **Semantics:** callable without an instance; bound instance is ignored.  

---

## Overloads

- `.function<U>("Name").build(...)`  
- `.method<U>("Name").build(...)`  

**Semantics:**  
- Each overload must be explicitly registered with its signature type `U`.  
- At invocation, RTL applies overload resolution consistent with C++.  
- Ambiguity must be resolved with explicit `.bind<U>()`.  
- Includes strict rules for lvalues, rvalues, references, and const correctness.  

---

## Invocation

- `.bind(args...).call(args...)`  
  - **Syntax:**  
    - `.bind()` associates an object (for member calls).  
    - `.call(...)` executes with arguments.  
  - **Semantics:**  
    - Returns `(error_code, result)`.  
    - Error codes include `SignatureMismatch`, `ConstCallViolation`, `IllegalConstCast`, and a few more.  
    - Results can be viewed with `view<T>()` for type-safe access.  

---

## DSL Essence

- **Declarative registration**: `Reflect()` + builder chain.  
- **Explicit disambiguation**: overloads and rvalue refs require signature guides.  
- **Semantic fidelity**: runtime behavior strictly matches C++ rules on constness, staticness, overloads, forwarding.  
- **Safety guarantees**: API design forbids invalid registrations; errors are explicit at runtime.  

---

## Putting It All Together

### Registering Free Functions

**Syntax**
```cpp
Reflect().nameSpace("ext").function("sendString").build(ext::sendString);
```
- `nameSpace("ext")` → tells RTL this function lives in the namespace `ext`.
- `.function("sendString")` → declares the name to reflect under.
- `.build(ext::sendString)` → registers the pointer.

**Semantics**
```cpp
auto sendString = cxx_mirror().getFunction("ext", "sendString");
ASSERT_TRUE(sendString);

std::string theStr = "Initiating reflection tests.";
auto [err, ret] = sendString->bind().call(theStr);
```
- Lookup: Without the namespace, lookup fails. With the namespace, it succeeds.
- Invocation: `bind().call(...)` is all it takes. Because it’s free, no instance is needed.
- Semantics: Just like in C++, the argument is passed by value and the return type is preserved. Reflection introduces no surprises.

> **Takeaway:** Registering and calling a free function through RTL feels like calling it directly — only you discover it through the mirror instead of writing its name.

---

### Registering Overloaded Free Functions

Overloads can’t be guessed by the compiler — you need to guide RTL by giving the parameter type explicitly.

**Syntax**
```cpp
Reflect().nameSpace("ext").function<const char*>("sendAsString").build(ext::sendAsString);
Reflect().nameSpace("ext").function<Person>("sendAsString").build(ext::sendAsString);
Reflect().nameSpace("ext").function<Person&&>("sendAsString").build(ext::sendAsString);
```
- Each template argument (`const char*`, `Person`, `Person&&`) selects the correct overload.
- Omitting it results in a compile-time error.

**Semantics**
1. **`const char*` overload**
```cpp
auto sendAsString = cxx_mirror().getFunction("ext", "sendAsString");
auto [err, ret] = sendAsString->bind().call(theStr.c_str());
```
- Resolves to `sendAsString(const char*)`.
- Returns the expected string literal-based result.

2. **Lvalue overload**
```cpp
Person person(nameStr);
auto [err, ret] = sendAsString->bind().call(person);
```
- Resolves to `sendAsString(Person)`.
- Behaves like direct C++ overload resolution.

3. **Rvalue-ref overload**
```cpp
auto [err, ret] = sendAsString->bind<Person&&>().call(Person(nameStr));
```
- Requires explicitly binding `Person&&`.
- Semantics: Perfect forwarding ensures the rvalue overload is chosen.

> **Takeaway:** Overload resolution in reflection is explicit at registration and still feels natural at runtime — the same overload rules you know from C++ apply here.

---

### Registering a Class (Record)

**Syntax**
```cpp
Reflect().nameSpace().record<Person>("Person").build();
```
- Registers `Person` as a reflective type.
- Default constructor, copy constructor, and destructor are added automatically.
- Explicit registration of these special members is disallowed — compile-time error.

**Semantics**
```cpp
auto classPerson = cxx_mirror().getRecord("Person");
std::string name = "Charlie";
auto [err, robj] = classPerson->create<rtl::alloc::Stack>(name);
```
- Passing `std::string` resolves naturally to the constructor that takes `const std::string&`.
- Reflection delegates the overload decision to the compiler — just like native C++.
- The returned `RObject` wraps an instance of `Person` on the stack.

> **Takeaway:** When you register a class, you don’t need to micro-manage special members. Creation, copy, and destruction just work according to normal C++ rules.

---

### Registering Member Functions

**Non-const method**
```cpp
Reflect().member<Person>().method("getName").build(&Person::getName);
```
- Only non-const methods can be passed here.

**Semantics:**
- On a true-const `Person`: reflective call fails with `ConstCallViolation`.
- On a logically-const `Person` (created internally by RTL): RTL safely const_casts, and the call succeeds.

**Static method**
```cpp
Reflect().member<Person>().methodStatic("getDefaults").build(&Person::getDefaults);
```
- Must be declared with `.methodStatic()`.

**Semantics:**
- Invoked without any instance.
- Even if you bind an object, it’s ignored (mirroring native C++ static behavior).

**Const method**
```cpp
Reflect().member<Person>().methodConst("updateAddress").build(&Person::updateAddress);
```
- Only accepts const-qualified member function pointers.

**Semantics:**
- Invokable on const and non-const objects.
- Respects const correctness.

> **Takeaway:** RTL enforces constness and staticness at registration. You can’t accidentally register a non-const function as const — the API makes such mistakes impossible.

---

### Overloaded Member Functions

**`setOccupation` overloads**
```cpp
Reflect().member<Person>().method<std::string&&>("setOccupation").build(&Person::setOccupation);
Reflect().member<Person>().method<const std::string&>("setOccupation").build(&Person::setOccupation);
```
**Semantics:**
- Simple calls mismatch and return `SignatureMismatch`.
- Correct calls require explicit forwarding:
```cpp
setOccupation->bind<std::string&&>(robjTim).call("Teacher");
setOccupation->bind<const std::string&>(robjTim).call("Teacher");
```

**`setProfile` overloads**
```cpp
Reflect().member<Person>().method<std::string>("setProfile").build(&Person::setProfile);
Reflect().member<Person>().method<std::string&>("setProfile").build(&Person::setProfile);
```
**Semantics:**
- Both overloads are registered.
- At runtime, RTL resolves calls in a way that prefers the by-value overload if it’s the only valid choice.
- Even if you try binding `std::string&`, it can still resolve to by-value, matching C++ overload rules.

> **Takeaway:** Overload registration is explicit; overload resolution is natural. RTL mirrors the subtle rules of C++ so reflective calls behave exactly like direct calls.

---

## Recap

- **Free functions**: register with namespaces; overloads require explicit type templates.
- **Class registration**: implicit special members; constructor resolution follows native rules.
- **Member functions**: constness and staticness enforced by API design.
- **Overloaded methods**: explicitly registered; runtime resolution matches C++.

---

