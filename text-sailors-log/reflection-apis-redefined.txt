Design log, 06/11/2025
Author, Neeraj Singh.
-------------------------------------
# Why RTL's API is Different

Most C++ reflection libraries follow patterns inherited from dynamically-typed languages like Python, Ruby, or JavaScript. These patterns make sense in those contexts—but they're fundamentally mismatched to C++'s nature as a statically-typed, performance-oriented language.

RTL takes a different approach: **leverage C++'s type system instead of fighting it**.

---

## The Traditional Reflection Model: "Shooting in the Dark"

**The typical reflection API looks like this:**

```cpp
// Traditional reflection (most libraries)
result = invoke("functionName", arg1, arg2, arg3);
```

**What happens at runtime:**

1. **Lookup:** Hash map search for "functionName" (~10-50ns)
2. **Arity check:** Does argument count match? (~5ns)
3. **Type validation:** Do argument types match expected types? (~10-30ns)
4. **Type conversion:** Convert arguments if possible (~10-50ns)
5. **Dispatch:** Finally, call the function (~1-2ns)

**If any step 1-4 fails:** Throw exception (after consuming all that time).

**If you call this function 1,000 times:** Pay the lookup + validation cost 1,000 times.

---

### **The Problems with This Model**

#### **1. Performance Degrades at Scale**

```cpp
// Every call repeats the entire lookup + validation process
for (int i = 0; i < 1000000; i++) {
    invoke("processData", data[i]);  // 1M × (lookup + validate + dispatch)
}
```

**Cost per call:** 30-100ns overhead, even if the function itself is fast.

For a trivial function (say, 5ns of actual work), **you're spending 85-95% of time on reflection overhead**.

---

#### **2. Error Handling is Reactive, Not Proactive**

```cpp
try {
    result = invoke("funcName", arg1, arg2);
} catch (const ReflectionException& e) {
    // What failed?
    // - Function not found?
    // - Wrong argument count?
    // - Type mismatch?
    // - Can't convert types?
    
    // Parse error message to figure it out? 😞
}
```

**You discover errors during the call, not before.**

Every invocation is a gamble: will it work, or will it throw?

---

#### **3. User Intent is Ambiguous**

```cpp
invoke("compute", 42, 3.14);
```

**Questions the library must guess:**
- Is this a function taking `(int, double)`?
- Or `(double, double)` with int→double conversion?
- Or `(float, float)` with narrowing conversions?
- Or `(long, float)` with multiple conversions?

**The library guesses. Sometimes it guesses wrong.**

---

## The RTL Model: "Turn On the Lights First"

RTL separates reflection into **two distinct phases**:

### **Phase 1: Lookup & Validation (Once)**

```cpp
rtl::function<std::string(float, float)> compute = 
    mirror.getFunction("compute")
          ->argsT<float, float>()
          .returnT<std::string>();

if (!compute) {
    // Function doesn't exist or signature doesn't match
    // Handle this ONCE, at setup time
    std::cerr << "Function 'compute' not found or signature mismatch\n";
    return;
}
```

**This is where you "agree and commit":**
- "I want a function named `compute`"
- "That takes `(float, float)`"  
- "And returns `std::string`"

**If this succeeds:** You have a **valid, typed callable**. Invocation is guaranteed to work.

**If this fails:** You get an empty `optional`. Handle it gracefully, once.

---

### **Phase 2: Dispatch (Many Times, Zero Overhead)**

```cpp
// Now call it as many times as you want
for (int i = 0; i < 1000000; i++) {
    std::string result = compute(data[i].x, data[i].y);  // Just dispatch
}
```

**What happens per call:**
1. **Dispatch:** Jump to function pointer (~1-2ns)
2. Done.

**No lookup. No validation. No type checking. No exceptions.**

**Just a single, native function pointer jump.**

---

## Why This is Architecturally Superior

### **1. Performance: Amortize the Cost**

**Traditional Model:**
```
Total cost = N × (Lookup + Validate + Dispatch)
1,000 calls = 1,000 × (50ns) = 50,000ns = 50µs
```

**RTL Model:**
```
Total cost = 1 × (Lookup + Validate) + N × (Dispatch)
1,000 calls = 1 × (50ns) + 1,000 × (2ns) = 2,050ns = 2µs
```

**RTL is 24× faster for 1,000 calls.**

**The more you call, the bigger RTL's advantage.**

---

### **2. Error Handling: Fail Fast**

**Traditional:**
```cpp
try {
    for (auto& item : data) {
        invoke("process", item);  // Might fail on iteration 847
    }
} catch (...) {
    // Crashed mid-loop. Now what?
}
```

**RTL:**
```cpp
auto process = mirror.getFunction("process")->argsT<Item>().returnT<>();

if (!process) {
    // Failed at setup. Handle it BEFORE the loop.
    return error("Function 'process' not found");
}

// If we get here, all 1,000 calls are guaranteed to work:
for (auto& item : data) {
    process(item);  // No try-catch needed
}
```

**Errors are discovered at lookup time, not call time.**

**"Fail fast" done right.**

---

### **3. User Intent is Explicit**

**Traditional (ambiguous):**
```cpp
invoke("func", 42, 3.14);  // What signature does user expect?
```

**RTL (explicit):**
```cpp
rtl::function<double(int, double)> func = ...;  // User declares intent
func(42, 3.14);  // Compiler enforces it
```

**No guessing. User's expectations are crystal clear.**

---

### **4. Composability**

RTL's callables are **first-class objects**:

```cpp
// Store them
std::map<std::string, rtl::function<void(int)>> handlers;
handlers["onConnect"] = mirror.getFunction("handleConnect")->argsT<int>();
handlers["onDisconnect"] = mirror.getFunction("handleDisconnect")->argsT<int>();

// Pass them around
void registerHandler(const std::string& event, rtl::function<void(int)> handler);

// Compose them
auto combined = [f1, f2](int x) { f1(x); f2(x); };
```

**You can't do this with `invoke("name", ...)` — the lookup is coupled to the call.**

---

## The Type System is Your Friend

### **Insight: Types Exist at the Call Site**

When you write:
```cpp
int x = 42;
float y = 3.14f;
invoke("compute", x, y);
```

**The compiler knows `x` is `int` and `y` is `float`.**

**Why throw away that information just to rediscover it at runtime?**

---

### **RTL's Philosophy:**

> **"C++ is statically typed. Users write typed code. Reflection should use those types, not fight them."**

When you write:
```cpp
rtl::function<double(int, float)> compute = ...;
compute(x, y);
```

**The compiler:**
- Knows you're calling a function expecting `(int, float)`
- Knows you're passing `(int, float)`  
- Validates this at compile time (if variables are typed)
- Generates the call with zero overhead

**RTL just forwards the arguments. The compiler does the rest.**

---

## The Two Design Decisions That Make This Work

### **Decision 1: Let C++ Handle Implicit Conversions**

**Most reflection libraries try to implement conversion logic:**

```cpp
// What other libraries do (pseudocode):
if (arg_type == int && param_type == float) {
    float converted = static_cast<float>(arg);
    // Now handle: double, long, short, unsigned...
    // Also handle: const, pointers, references...
    // Also handle: user-defined conversions...
    // 5,000 lines later...
}
```

**RTL's approach:**

```cpp
// User declares expected types
rtl::function<void(float, float)> func = ...;

// User passes ints
func(61, 35);  // Compiler converts int→float (standard C++)
```

**RTL doesn't handle conversions. C++ does.**

**Benefits:**
- ✅ Zero conversion code to write/maintain
- ✅ Zero runtime overhead (compiler optimizes)
- ✅ All standard conversions work automatically
- ✅ User-defined conversions work automatically
- ✅ Perfect forwarding works  
- ✅ Const-correctness preserved

**RTL leverages the compiler instead of reimplementing it.**

---

### **Decision 2: Decouple Lookup from Invocation**

**Most libraries couple them:**
```cpp
invoke(name, args) = [Lookup + Validate + Call] as one operation
```

**RTL decouples them:**
```cpp
callable = lookup(name, signature)  // Once
callable(args)                       // Many times
```

**This separation gives you:**
- ✅ Performance (amortize lookup cost)
- ✅ Safety (validate once, call many)
- ✅ Clarity (errors at lookup, not call)
- ✅ Composability (callables are values)

**Single Responsibility Principle applied to reflection.**

---

## A Complete Example: Before and After

### **Traditional Reflection Library**

```cpp
// Setup (none needed, everything happens at call-time)

// Usage
void processData(const std::vector<DataPoint>& data) {
    for (const auto& point : data) {
        try {
            // Every call: lookup + validate + dispatch
            auto result = reflection::invoke("computeValue", point.x, point.y);
            
            // Type-cast the result (runtime check)
            double value = std::any_cast<double>(result);
            
            // Use value...
        } catch (const reflection::NotFoundException& e) {
            // Function not found
        } catch (const reflection::TypeMismatchException& e) {
            // Type error
        } catch (const std::bad_any_cast& e) {
            // Wrong return type
        }
    }
}
```

**Problems:**
- ❌ Lookup + validation × N times (slow)
- ❌ Three different exception types to catch
- ❌ Runtime type casting required
- ❌ Errors discovered during loop (too late)

---

### **RTL Approach**

```cpp
// Setup (once, at initialization)
auto computeValue = mirror.getFunction("computeValue")
                          ->argsT<double, double>()
                          .returnT<double>();

if (!computeValue) {
    // Handle error at setup time
    return error("Function 'computeValue' not found or signature mismatch");
}

// Usage
void processData(const std::vector<DataPoint>& data) {
    for (const auto& point : data) {
        // Just dispatch (no lookup, no validation, no exceptions)
        double value = computeValue(point.x, point.y);
        
        // Use value...
    }
}
```

**Benefits:**
- ✅ Lookup + validation once (fast)
- ✅ Zero exception handling in loop
- ✅ Statically typed result (no casting)
- ✅ Errors discovered before loop (fail fast)

---

## When to Use Each API Style

RTL provides **two APIs** for different scenarios:

### **Typed API (When You Know Types)**

```cpp
// You know the signature at the call site
rtl::function<std::string(int, int)> func = 
    mirror.getFunction("toString")
          ->argsT<int, int>()
          .returnT<std::string>();

std::string result = func(42, 100);  // Compile-time type checking
```

**Use when:**
- You know the function signature
- You want compile-time type safety
- You need maximum performance (~1-2ns overhead)

---

### **Type-Erased API (When Types are Unknown)**

```cpp
// Runtime flexibility when types aren't known at compile time
auto [err, result] = mirror.getFunction("toString")
                           ->bind(obj)
                           .call(42, 100);

if (err == rtl::error::None && result.canViewAs<std::string>()) {
    std::string str = result.view<std::string>()->get();
}
```

**Use when:**
- Loading plugins at runtime
- Scripting language integration
- Serialization/deserialization
- Generic tool building (debuggers, editors)

**Even the type-erased API separates lookup from invocation:**
- Lookup: `getFunction("toString")`
- Invocation: `call(args)`

---

## The Philosophy: "Ask, Don't Assume"

**Traditional reflection:**
```cpp
invoke("func", args);  // Hope it works, catch if it doesn't
```

**RTL:**
```cpp
auto func = mirror.getFunction("func")->argsT<Args...>();
if (func) {
    func(args);  // Guaranteed to work
} else {
    // Handle the known error
}
```

**Instead of assuming the function exists and catching exceptions when it doesn't, RTL lets you ASK:**

- "Does this function exist?"
- "Does it have this signature?"  
- "Give me a callable if yes, null if no."

**Then you decide what to do.**

**This is:**
- More explicit (no hidden exceptions)
- More efficient (no wasted work on invalid calls)
- More composable (callables are values)

---

## Summary: Two Key Insights

### **1. C++ Has Types — Use Them**

**Don't throw away type information just to rediscover it at runtime.**

Let users declare expected types. Let the compiler handle conversions and validation. Reflection becomes a thin layer, not a complex runtime system.

---

### **2. Separate Lookup from Dispatch**

**Don't couple lookup + validation with every call.**

Validate once at setup. Then dispatch becomes a single function pointer jump — as fast as C++ can possibly be.

---

## The Result

**RTL reflection calls are 10-50× faster than traditional reflection.**

**Not through clever optimization tricks.**

**Through better architecture.**

---

**By thinking in C++ instead of copying dynamic languages, RTL achieves both flexibility AND performance.**

**That's the RTL difference.**
