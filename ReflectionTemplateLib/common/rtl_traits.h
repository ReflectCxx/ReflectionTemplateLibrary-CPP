#pragma once

#include <any>
#include <array>
#include <string>
#include <type_traits>

#include "TypeId.h"
#include "Constants.h"

namespace rtl
{
    namespace traits
    {
        template<typename T>
        struct base {
            using type = std::remove_cv_t<std::remove_pointer_t<std::remove_reference_t<std::remove_all_extents_t<T>>>>;
        };


        template<typename T>
        using base_t = typename base<T>::type;


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
    }
}