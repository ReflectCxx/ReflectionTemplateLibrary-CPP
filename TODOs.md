🔴 Top Priority
Const-Safety Test

Reflect a method returning a truly const object.

Attempt calling a mutable method by explicitly selecting the non-const overload.

Expect error::UnableToCallNonConstOnConstTarget.

Complements existing error::ImplicitCallToNonConstOnConstTarget handling.

🟡 Medium Priority
Dynamic Assert Cleanup

Keep dynamic asserts for now.

Future: replace with error codes in line with RTL’s never-throw standard.

Move-Only Type Cloning

Handle cases where move constructor exists but copy constructor is deleted.

Provide fallback cloning via serialization if needed.

Graceful Destructor Handling

Reject heap allocation via build() if destructor is private or deleted.

Reference-Qualified Member Functions Support (C++11+)

Add reflection support for & and && qualified member functions.

🟢 Low Priority
std::any_cast Exception Guarding

Verify all call sites.

Ensure that even if triggered externally, exceptions propagate cleanly.

Deep Cloning of Nested Members

Ensure RObject::clone() deeply clones composed reflected members when applicable.

Empty Type Registration

Confirm RTL correctly handles metadata, construction, and reflection for empty types.

Relaxed Parameter Matching

Support compatible-but-not-exact types in reflected function calls
(e.g., const char* → std::string_view when std::string is expected).