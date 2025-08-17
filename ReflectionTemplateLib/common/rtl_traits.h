/*_________________________________________________________________________
* Copyright 2025 Neeraj Singh
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
___________________________________________________________________________*/

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
        using Converter = std::function< std::any(const std::any&, const EntityKind&, EntityKind&) >;
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
        inline constexpr bool is_raw_ptr_v = std::is_pointer_v<remove_const_n_ref_t<T>>;

        template<typename T>
        inline constexpr bool is_const_v = (std::is_const_v<std::remove_reference_t<T>> || (std::is_pointer_v<T> && std::is_const_v<std::remove_pointer_t<T>>));

        template<typename _checkType, typename..._typeList>
        inline constexpr bool is_first_type_same_v = std::is_same_v<raw_t<typename detail::TypeId<_typeList...>::HEAD>, raw_t<_checkType>>;
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
        template<class T>
        constexpr bool is_bare_type()
        {
            static_assert(!std::is_const_v<T>, "Provide bare type (remove const).");
            static_assert(!std::is_pointer_v<T>, "Provide bare type (remove pointer).");
            static_assert(!std::is_reference_v<T>, "Provide bare type (remove reference).");

            return !(std::is_const_v<T> || std::is_pointer_v<T> || std::is_reference_v<T>);
        }
    }
}