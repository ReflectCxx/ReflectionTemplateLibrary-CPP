#pragma once
// #include <iostream>

#ifdef RTL_DEBUG

// Runs arbitrary code safely in Debug builds (single-statement safe)
#define RTL_DEBUG_ONLY(code) do { code } while(0)

// Simple debug log
// #define RTL_LOG(msg) do { std::cout << "[RTL-DEBUG] " << msg << '\n'; } while(0)

// Exception-free assert: if condition fails, prints message and returns error code
// #define RTL_ASSERT(cond, err_code) do {                       \
//     if (!(cond)) {                                            \
//         std::cerr << "[RTL-ASSERT] " #cond " failed!\n";     \
//         return err_code;                                      \
//     }                                                         \
// } while(0)

#else

// Release builds: completely stripped out
#define RTL_DEBUG_ONLY(code) do {} while(0)
// #define RTL_LOG(msg) do {} while(0)
// #define RTL_ASSERT(cond, err_code) do {} while(0)

#endif
