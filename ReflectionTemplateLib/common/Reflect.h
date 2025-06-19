#pragma once

#include <array>
#include <string>
#include <type_traits>

namespace rtl
{
    namespace utils {

        // Trait to detect string-like types. Defaults to false for all types.
        template<typename T>
        struct is_string_like : std::false_type {};

        // Specialization: std::string is string-like.
        template<>
        struct is_string_like<std::string> : std::true_type {};

        // Specialization: std::string_view is string-like.
        template<>
        struct is_string_like<std::string_view> : std::true_type {};

        // Specialization: char* is string-like.
        template<>
        struct is_string_like<char*> : std::true_type {};

        // Specialization: const char* is string-like.
        template<>
        struct is_string_like<const char*> : std::true_type {};

        // Specialization: const char[N] (C-style string literal) is string-like.
        template<std::size_t N>
        struct is_string_like<const char[N]> : std::true_type {};

        // Base: not a C array
        template<typename T>
        struct is_c_array : std::false_type {};

        // General array case
        template<typename T, std::size_t N>
        struct is_c_array<T[N]> : std::conditional_t<
            std::is_same_v<std::remove_cv_t<T>, char>,
            std::false_type,  // Exclude char arrays
            std::true_type> {
        };

        // Unknown bound array (e.g. function args like T[])
        template<typename T>
        struct is_c_array<T[]> : std::conditional_t<
            std::is_same_v<std::remove_cv_t<T>, char>,
            std::false_type,
            std::true_type> {
        };

        template<typename T>
        using enable_if_string_t = std::enable_if<is_string_like<std::decay_t<T>>::value, int>::type;

        template<typename T>
        using enable_if_array_t = typename std::enable_if< is_c_array<typename std::remove_reference<T>::type>::value, int>::type;

        template<typename T>
        using enable_if_neither_string_nor_array_t = std::enable_if<!is_string_like<std::decay_t<T>>::value &&
                                                                    !is_c_array<typename std::remove_reference<T>::type>::value, int>::type;
    }
}


namespace rtl 
{
    template<typename T, std::size_t N, std::size_t... _Indices>
    inline constexpr std::array<T, N> to_std_array_n(const T(&pArr)[N], std::index_sequence<_Indices...>) {
        return { pArr[_Indices]... };
    }

    template<typename T, std::size_t N>
    inline constexpr std::array<T, N> to_std_array(const T(&pArr)[N]) {
        return to_std_array_n(pArr, std::make_index_sequence<N>{});
    }

    template <class T, typename rtl::utils::enable_if_string_t<T> = 0>
    inline access::RObject reflect(T&& pVal) 
    {
        return access::RObject::create(std::string(std::forward<T>(pVal)));
    }

    template<typename T, typename rtl::utils::enable_if_array_t<T> = 0>
    inline access::RObject reflect(T&& pArr)
    {
        return access::RObject::create(std::move(rtl::to_std_array(pArr)));
    }

    template <class T, typename rtl::utils::enable_if_neither_string_nor_array_t<T> = 0>
    inline access::RObject reflect(T&& pVal)
    {
        static_assert(!std::is_same_v<T, std::any>, "cannot reflect std::any.");
        return access::RObject::create(std::forward<T>(pVal));
    }
}