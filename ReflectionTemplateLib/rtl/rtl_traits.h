/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#pragma once

#include <any>
#include <memory>
#include <utility>
#include <optional>
#include <functional>
#include <type_traits>

#include <rtl_typeid.h>
#include <rtl_errors.h>
#include <rtl_constants.h>
#include <rtl_forward_decls.h>

namespace rtl
{
    namespace traits
    {
        using Converter = std::function< std::any(const std::any&, const detail::EntityKind&, detail::EntityKind&) >;
        
        using ConverterPair = std::pair< std::size_t, Converter >;

        using cloner_t = Return(*)(alloc, const RObject&);

        template<typename T>
        struct raw_type {
            using type = std::remove_cv_t<std::remove_pointer_t<std::remove_reference_t<std::remove_all_extents_t<T>>>>;
        };

        template<typename T>
        using raw_t = typename raw_type<T>::type;

        // Utility: Remove const and reference qualifiers from T.
        template <typename T>
        using remove_cref_t = std::remove_const_t<std::remove_reference_t<T>>;

        // Utility: Remove const from T if T is not a reference; otherwise, leave as is.
        template <typename T>
        using remove_const_if_not_reference = std::conditional_t< std::is_reference_v<T>, T, std::remove_const_t<T>>;

        // Utility: Remove const, reference, and pointer from T (after decay).
        template<typename T>
        using remove_const_n_ref_n_ptr = std::remove_const_t<std::remove_reference_t<std::remove_pointer_t<std::decay_t<T>>>>;

        template<typename T>
        inline constexpr bool is_raw_ptr_v = std::is_pointer_v<remove_cref_t<T>>;

        template<typename T>
        inline constexpr bool is_const_v = (std::is_const_v<std::remove_reference_t<T>> || (std::is_pointer_v<T> && std::is_const_v<std::remove_pointer_t<T>>));

        template<typename _checkType, typename..._typeList>
        inline constexpr bool is_first_type_same_v = std::is_same_v<raw_t<typename detail::TypeId<_typeList...>::HEAD>, raw_t<_checkType>>;
    }
    

    namespace traits
    {
        using uid_t = std::uintptr_t;

        // Returns an opaque, unique identifier per type T.
        // Must only be compared or hashed - never interpreted numerically.
        template<class T = std::nullptr_t>
        class uid
        {
            static
            #if __cpp_static_local_constexpr >= 202306L
            constexpr
            #endif
            uid_t get() noexcept
            {
                if constexpr (!std::is_same_v<T, std::nullptr_t>) {
                    static const int unique_tag = 0;
                    return reinterpret_cast<uid_t>(&unique_tag);
                }
                return 0;
            }

        public:

            static constexpr uid_t none = 0;
            static inline const uid_t value = get();
        };
    }


    namespace traits
    {
        template<typename T>
        struct std_wrapper
        {
            using value_type = std::nullptr_t;
            static constexpr const auto type = detail::Wrapper::None;
            static constexpr uid_t id() { return uid<>::none; }
        };


        template<typename T>
        struct std_wrapper<std::shared_ptr<T>>
        {
            using value_type = T;
            static constexpr const auto type = detail::Wrapper::Shared;
            static constexpr uid_t id() { return uid<std::shared_ptr<T>>::value; }
        };


        template<typename T>
        struct std_wrapper<std::unique_ptr<T>>
        {
            using value_type = T;
            static constexpr const auto type = detail::Wrapper::Unique;
            static constexpr uid_t id() { return uid<std::unique_ptr<T>>::value; }
        };


        template<typename T>
        struct std_wrapper<std::weak_ptr<T>>
        {
            using value_type = T;
            static constexpr const auto type = detail::Wrapper::Weak;
            static constexpr uid_t id() { return uid<std::weak_ptr<T>>::value; }
        };

        template<typename T>
        constexpr auto wrapper_type_v = std_wrapper<T>::type;

        template<typename T>
        constexpr bool is_weak_ptr_v = (wrapper_type_v<T> == detail::Wrapper::Weak);

        template<typename T>
        constexpr bool is_unique_ptr_v = (wrapper_type_v<T> == detail::Wrapper::Unique);

        template<typename T>
        constexpr bool is_shared_ptr_v = (wrapper_type_v<T> == detail::Wrapper::Shared);

        template<typename T>
        constexpr bool is_not_any_wrapper_v = (wrapper_type_v<T> == detail::Wrapper::None);

        template<typename T>
        using enable_if_unique_ptr = std::enable_if<std_wrapper<T>::type == detail::Wrapper::Unique, int>::type;

        template<typename T>
        using enable_if_shared_ptr = std::enable_if<std_wrapper<T>::type == detail::Wrapper::Shared, int>::type;
    }


    namespace traits 
    {
        template<typename T, typename... signature_t>
        concept has_constructor = requires(signature_t&&... args) {
            T{ std::forward<signature_t>(args)... };
        };

        template<class T>
        constexpr bool is_bare_type()
        {
            static_assert(!std::is_const_v<T>, "Provide bare type (remove const).");
            static_assert(!std::is_pointer_v<T>, "Provide bare type (remove pointer).");
            static_assert(!std::is_reference_v<T>, "Provide bare type (remove reference).");

            return !(std::is_const_v<T> || std::is_pointer_v<T> || std::is_reference_v<T>);
        }

        template<class T>
        using normal_sign_t = std::remove_const_t<std::remove_reference_t<T>>;

        template<class ...signature_t>
        using normal_sign_id_t = std::tuple<normal_sign_t<signature_t>...>;

        template<class ...signature_t>
        using strict_sign_id_t = std::tuple<signature_t...>;

        template<class T>
        inline constexpr bool is_nonconst_ref_v = ((std::is_lvalue_reference_v<T> || std::is_rvalue_reference_v<T>) &&
                                                   !std::is_const_v<std::remove_reference_t<T>>);

        template<class record_t, class return_t>
        constexpr static const bool type_aware_v = (!std::is_same_v<record_t, rtl::RObject> && !std::is_same_v<return_t, rtl::Return>);

        template<class record_t, class return_t>
        constexpr static const bool return_erased_v = (!std::is_same_v<record_t, rtl::RObject> && std::is_same_v<return_t, rtl::Return>);

        template<class record_t, class return_t>
        constexpr static const bool target_erased_v = (std::is_same_v<record_t, rtl::RObject> && !std::is_same_v<return_t, rtl::Return>);

        template<class record_t, class return_t>
        constexpr static const bool type_erased_v = (std::is_same_v<record_t, rtl::RObject> && std::is_same_v<return_t, rtl::Return>);
    }
}