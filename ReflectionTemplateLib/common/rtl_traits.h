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
        using Converter = std::function< std::any(const std::any&, const IsPointer&, ConversionKind&) >;
        using ConverterPair = std::pair< std::size_t, Converter >;
    }

    namespace traits
    {
        template<typename T>
        struct base {
            using type = std::remove_cv_t<std::remove_pointer_t<std::remove_reference_t<std::remove_all_extents_t<T>>>>;
        };

        template<typename T>
        using base_t = typename base<T>::type;

        // Utility: Remove const and reference qualifiers from T.
        template <typename T>
        using remove_const_n_reference = std::remove_const_t<std::remove_reference_t<T>>;

        // Utility: Remove const from T if T is not a reference; otherwise, leave as is.
        template <typename T>
        using remove_const_if_not_reference = std::conditional_t< std::is_reference_v<T>, T, std::remove_const_t<T>>;

        // Utility: Remove const, reference, and pointer from T (after decay).
        template<typename T>
        using remove_const_n_ref_n_ptr = std::remove_const_t<std::remove_reference_t<std::remove_pointer_t<std::decay_t<T>>>>;
    }
    
    
    namespace traits
    {
        template<typename T>
        struct std_wrapper
        {
            using baseT = std::nullptr_t;
            static constexpr const auto type = Wrapper::None;
            static auto id() { return detail::TypeId<>::None; }
        };


        template<typename T>
        struct std_wrapper<std::shared_ptr<T>>
        {
            using baseT = T;
            static constexpr const auto type = Wrapper::Shared;
            static auto id() { return detail::TypeId<std::shared_ptr<T>>::get(); }
        };


        template<typename T>
        struct std_wrapper<std::unique_ptr<T>>
        {
            using baseT = T;
            static constexpr const auto type = Wrapper::Unique;
            static auto id() { return detail::TypeId<std::unique_ptr<T>>::get(); }
        };


        template<typename T>
        struct std_wrapper<std::weak_ptr<T>>
        {
            using baseT = T;
            static constexpr const auto type = Wrapper::Weak;
            static auto id() { return detail::TypeId<std::weak_ptr<T>>::get(); }
        };

        template<typename T>
        using enable_if_std_wrapper = std::enable_if<std_wrapper<std::remove_reference_t<T>>::type != Wrapper::None, int>::type;

        template<typename T>
        using enable_if_not_std_wrapper = std::enable_if<std_wrapper<std::remove_reference_t<T>>::type == Wrapper::None, int>::type;
    }
}