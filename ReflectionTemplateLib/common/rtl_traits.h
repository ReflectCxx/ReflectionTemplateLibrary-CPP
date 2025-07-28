#pragma once

#include <any>
#include <array>
#include <string>
#include <type_traits>

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
    }
}