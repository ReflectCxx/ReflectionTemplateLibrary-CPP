#pragma once

#include <any>
#include <array>
#include <string>
#include <memory>
#include <functional>
#include <type_traits>

#include "TypeId.h"
#include "Constants.h"

namespace rtl
{
    namespace traits
    {
        using Converter = std::function< std::any(const std::any&, const detail::Contains&, detail::ConversionKind&) >;
        using ConverterPair = std::pair< std::size_t, Converter >;
    }

    namespace traits
    {
        template<typename T>
        struct raw_type {
            using type = std::remove_cv_t<std::remove_pointer_t<std::remove_reference_t<std::remove_all_extents_t<T>>>>;
        };

        template<typename T>
        using raw_t = typename raw_type<T>::type;

        // Utility: Remove const and reference qualifiers from T.
        template <typename T>
        using remove_const_n_ref_t = std::remove_const_t<std::remove_reference_t<T>>;

        // Utility: Remove const from T if T is not a reference; otherwise, leave as is.
        template <typename T>
        using remove_const_if_not_reference = std::conditional_t< std::is_reference_v<T>, T, std::remove_const_t<T>>;

        // Utility: Remove const, reference, and pointer from T (after decay).
        template<typename T>
        using remove_const_n_ref_n_ptr = std::remove_const_t<std::remove_reference_t<std::remove_pointer_t<std::decay_t<T>>>>;

        template<typename T>
        constexpr bool is_raw_ptr_v = std::is_pointer_v<remove_const_n_ref_t<T>>;

        template<typename T>
        constexpr bool is_const_v = (std::is_const_v<std::remove_reference_t<T>> || (std::is_pointer_v<T> && std::is_const_v<std::remove_pointer_t<T>>));

        template<typename _checkType, typename..._typeList>
        constexpr bool is_first_type_same_v = std::is_same_v<raw_t<typename detail::TypeId<_typeList...>::HEAD>, raw_t<_checkType>>;
    }
    
    
    namespace traits
    {
        template<typename T>
        struct std_wrapper
        {
            using value_type = std::nullptr_t;
            static constexpr const auto type = detail::Wrapper::None;
            static auto id() { return detail::TypeId<>::None; }
        };


        template<typename T>
        struct std_wrapper<std::shared_ptr<T>>
        {
            using value_type = T;
            static constexpr const auto type = detail::Wrapper::Shared;
            static auto id() { return detail::TypeId<std::shared_ptr<T>>::get(); }
        };


        template<typename T>
        struct std_wrapper<std::unique_ptr<T>>
        {
            using value_type = T;
            static constexpr const auto type = detail::Wrapper::Unique;
            static auto id() { return detail::TypeId<std::unique_ptr<T>>::get(); }
        };


        template<typename T>
        struct std_wrapper<std::weak_ptr<T>>
        {
            using value_type = T;
            static constexpr const auto type = detail::Wrapper::Weak;
            static auto id() { return detail::TypeId<std::weak_ptr<T>>::get(); }
        };

        template<typename T>
        using enable_if_raw_pointer = std::enable_if<std::is_pointer_v<remove_const_n_ref_t<T>>, int>::type;

        template<typename T>
        using enable_if_unique_ptr = std::enable_if<std_wrapper<T>::type == detail::Wrapper::Unique, int>::type;

        template<typename T>
        using enable_if_shared_ptr = std::enable_if<std_wrapper<T>::type == detail::Wrapper::Shared, int>::type;

        template<typename T>
        using enable_if_std_wrapper = std::enable_if<std_wrapper<remove_const_n_ref_t<T>>::type != detail::Wrapper::None, int>::type;

        template<typename T>
        using enable_if_not_std_wrapper = std::enable_if<std_wrapper<remove_const_n_ref_t<T>>::type == detail::Wrapper::None, int>::type;

        template<typename T>
        using enable_if_not_std_wrapper_or_raw_ptr = std::enable_if<!std::is_pointer_v<remove_const_n_ref_t<T>> &&
                                                                    std_wrapper<remove_const_n_ref_t<T>>::type == detail::Wrapper::None, int>::type;
    }


    namespace traits 
    {
        template <typename T, typename = void>
        struct is_complete : std::false_type {};

        template <typename T>
        struct is_complete<T, std::void_t<decltype(sizeof(T))>> : std::true_type {};

        // Usage:
        template<typename T>
        inline constexpr bool is_incomplete_v = !is_complete<T>::value;

        template<typename T>
        struct instantiation_error 
        {
            static constexpr error value = std::is_void_v<T> ? error::Instantiating_typeVoid :
                                           std::is_abstract_v<T> ? error::Instantiating_typeAbstract :
                                           std::is_function_v<T> ? error::Instantiating_typeFunction :
                                           is_incomplete_v<T> ? error::Instantiating_typeIncomplete : // requires customization
                                           !std::is_default_constructible_v<T> ? error::Instantiating_typeNotDefaultConstructible :
                                           !std::is_copy_constructible_v<T> ? error::Instantiating_typeNotCopyConstructible :
                                           !std::is_move_constructible_v<T> ? error::Instantiating_typeNotMoveConstructible :
                                           error::None;
        };

        template<typename T>
        constexpr rtl::error instantiation_error_v = instantiation_error<raw_t<T>>::value;

        template<class T>
        constexpr bool is_view_suported()
        {
            using _T = traits::raw_t<T>;
            constexpr bool isReference = std::is_reference_v<T>;
            constexpr bool isWrapperPtr = (std::is_pointer_v<T> && std_wrapper<_T>::type != detail::Wrapper::None);
            constexpr bool isNonConstPtr = (std::is_pointer_v<T> && !std::is_const_v<std::remove_pointer_t<T>>);
            return (!isReference && !isWrapperPtr && !isNonConstPtr);
        }

        template<class T>
        constexpr void validate_view()
        {
            using _T = traits::raw_t<T>;
            constexpr bool isReference = std::is_reference_v<T>;
            constexpr bool isWrapperPtr = (std::is_pointer_v<T> && std_wrapper<_T>::type != detail::Wrapper::None);
            constexpr bool isNonConstPtr = (std::is_pointer_v<T> && !std::is_const_v<std::remove_pointer_t<T>>);

            static_assert(!isReference, "explicit reference views are not supported.");
            static_assert(!isWrapperPtr, "viewing standard wrappers (like std::optional or smart pointers) as raw pointers, not supported.");
            static_assert(!isNonConstPtr, "non-const pointers not supported, Only read-only (const) pointer views are supported.");
        }
    }
}