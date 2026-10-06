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

#include <detail/inc/ReflectCast.h>

namespace
{
    template<typename From, typename To>
    struct TypeConversion 
    {
        using from = From;
        using to = To;
    };


    template<typename TypeList, std::size_t I, std::size_t... Js>
    auto make_pairs_for_index(std::index_sequence<Js...>) 
    {
        using From = std::tuple_element_t<I, TypeList>;
        return std::tuple<TypeConversion<From, std::tuple_element_t<Js, TypeList>>...>{};
    }


    template<typename TypeList, std::size_t... Is>
    auto make_all_pairs(std::index_sequence<Is...>)
    {
        return std::tuple_cat(
                                make_pairs_for_index<TypeList, Is>
                                (
                                    std::make_index_sequence<std::tuple_size<TypeList>::value>{}
                                )...
                             );
    }


    template<typename TypeList>
    constexpr auto make_conversion_pairs() 
    {
        return make_all_pairs<TypeList>(
            std::make_index_sequence<std::tuple_size<TypeList>::value>{}
        );
    }


    template<typename Tuple, std::size_t... Is>
    void register_all_conversions_impl(std::index_sequence<Is...>) 
    {
        (...,
            (
                []{
                    using Conversion = std::tuple_element_t<Is, Tuple>;
                    using From = typename Conversion::from;
                    using To = typename Conversion::to;
                    if constexpr (!std::is_same_v<From, To>) {
                        rtl::detail::ReflectCast<From>::template pushConversion<To>();
                    }
                }()
            )
        );
    }


    template<typename Tuple>
    void register_all_conversions() 
    {
        register_all_conversions_impl<Tuple>(
            std::make_index_sequence<std::tuple_size<Tuple>::value> { }
        );
    }
}