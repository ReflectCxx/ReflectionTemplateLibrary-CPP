#pragma once

#include <array>
#include <string>
#include <atomic>
#include <cassert>
#include <functional>
#include <type_traits>

#include "RObject.hpp"

namespace rtl::detail
{
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

    template<typename T, std::size_t N, std::size_t... _Indices>
    inline constexpr std::array<T, N> to_std_array_n(const T(&pArr)[N], std::index_sequence<_Indices...>) {
        return { pArr[_Indices]... };
    }

    template<typename T, std::size_t N>
    inline constexpr std::array<T, N> to_std_array(const T(&pArr)[N]) {
        return to_std_array_n(pArr, std::make_index_sequence<N>{});
    }
}


namespace rtl::detail
{
    struct RObjectBuilder : protected access::RObject
    {
        RObjectBuilder() = delete;
        RObjectBuilder(const RObjectBuilder&) = delete;

        template<class T, typename enable_if_string_t<T> = 0>
        inline static access::RObject build(T&& pVal, const std::function<void()>& pDeleter, const TypeQ& pTypeQ, const alloc& pAllocOn) 
        {
            if (pDeleter && pAllocOn == alloc::Heap && pTypeQ != TypeQ::None) {
                return smartRObject(std::string(std::forward<T>(pVal)), pDeleter, pTypeQ, pAllocOn);
            }
            else {
                return access::RObject::create(std::string(std::forward<T>(pVal)), std::shared_ptr<void>(), pTypeQ, pAllocOn);
            }
        }

        template<class T, typename enable_if_array_t<T> = 0>
        inline static access::RObject build(T&& pArr, std::function<void()>&& pDeleter, const TypeQ& pTypeQ, const alloc& pAllocOn) 
        {
            if (pDeleter && pAllocOn == alloc::Heap && pTypeQ != TypeQ::None) {
                return smartRObject(std::move(to_std_array(pArr)), pDeleter, pTypeQ, pAllocOn);
            }
            else {
                return access::RObject::create(std::move(to_std_array(pArr)), std::shared_ptr<void>(), pTypeQ, pAllocOn);
            }
        }

        template<class T, typename enable_if_neither_string_nor_array_t<T> = 0>
        inline static access::RObject build(T&& pVal, std::function<void()>&& pDeleter, const TypeQ& pTypeQ, const alloc& pAllocOn) 
        {
            if (pDeleter && pAllocOn == alloc::Heap && pTypeQ != TypeQ::None) {
                return smartRObject(std::forward<T>(pVal), pDeleter, pTypeQ, pAllocOn);
            }
            else{
                return access::RObject::create(std::forward<T>(pVal), std::shared_ptr<void>(), pTypeQ, pAllocOn);
            }
        }

        inline static const std::size_t& reflectedInstanceCount() {
            return m_reflectedInstanceCount;
        }

    private: 

        template<class T>
        inline static access::RObject smartRObject(T&& pVal, const std::function<void()>& pDeleter,
                                                   const TypeQ& pTypeQ, const alloc& pAllocOn)
        {
            m_reflectedInstanceCount.fetch_add(1);
            return access::RObject::create(std::forward<T>(pVal),
                std::shared_ptr<void>(static_cast<void*>(&m_reflectedInstanceCount), [=](void*)
                {
                    pDeleter();
                    m_reflectedInstanceCount.fetch_sub(1);
                    assert(m_reflectedInstanceCount >= 0 && "instance count can't be less than zero. memory leak alert!");
                }), pTypeQ, pAllocOn);
        }

        static std::atomic<std::size_t> m_reflectedInstanceCount;
    };
}


namespace rtl
{
    template <class T>
    inline access::RObject reflect(T&& pVal) 
    {
        static_assert(!std::is_same_v<remove_const_n_ref_n_ptr<T>, std::any>, "cannot reflect std::any.");
        return detail::RObjectBuilder::build(std::forward<T>(pVal), nullptr, TypeQ::None, alloc::None);
    }

    inline const std::size_t& getReflecetedInstanceCount() {
        return detail::RObjectBuilder::reflectedInstanceCount();
    }
}