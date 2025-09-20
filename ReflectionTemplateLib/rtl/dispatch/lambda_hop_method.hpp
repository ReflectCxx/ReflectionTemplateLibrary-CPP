/*************************************************************************
 *                                                                       *
 *  Reflection Template Library (RTL) - Modern C++ Reflection Framework  *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP          *
 *                                                                       *
 *  Copyright (c) 2025 Neeraj Singh <reflectcxx@outlook.com>             *
 *  SPDX-License-Identifier: MIT                                         *
 *                                                                       *
 *************************************************************************/


#pragma once

//#include "functor.h"
//#include "lambda_method.h"
//#include "hopper_nonconst.h"

namespace rtl::detail
{

	//template<class record_t, class ...signature_ts>
	//template<class return_t>
	//inline lambda_method<record_t, signature_ts...> lambda_method<record_t, signature_ts...>::create(const functor* fptr_hopper)
	//{
 //       return lambda_method<record_t, signature_ts...>();
 //           //lambda_method(detail::TypeId<return_t>::get(), fptr_hopper,
	//		//	             &hopper_nonconst<signature_ts...>::template dispatch<std::is_same_v<return_t, void>, return_t>);
	//}


    //template<class record_t, class ...signature_ts>
    //inline decltype(auto) lambda_method<class record_t, signature_ts...>::operator()(record_t& target, const signature_ts& ...params) const noexcept
    //{
    //    //TODO: static-assert signature_ts == args_t && enable perfect-forwarding
    //    return m_hopper(target, *this, params...);
    //}


    // template<class record_t, class ...signature_ts>
    // template<class return_t>
    // inline return_t lambda_method<record_t, signature_ts...>::dispatch(record_t& target, const signature_ts&...params) const noexcept
    // {
    //    if constexpr (std::is_same_v<return_t, void>) {
    //        hopper_nonconst<record_t, signature_ts...>::template dispatch<return_t>(target, *this, params...);
    //    }
    //    else {
    //        return hopper_nonconst<record_t, signature_ts...>::template dispatch<return_t>(target, *this, params...);
    //    }
    // }
}