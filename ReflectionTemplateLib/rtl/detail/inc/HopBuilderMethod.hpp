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

#include <inc/Method.h>
#include <inc/RObject.h>

#include <dispatch/method_ptr.h>
#include <dispatch/method_ptr_const.h>
#include <detail/inc/HopBuilderMethod.h>

#include <rtl_method.h>
#include <rtl_method_const.h>
#include <rtl_method_erased.h>
#include <rtl_method_erased_target.h>
#include <rtl_method_erased_return.h>

namespace rtl::detail 
{
    template<member member_kind, class record_t>
    template<class ...args_t> requires (member_kind != member::None)
    inline constexpr InitMethodHop<member_kind, record_t, args_t...> HopBuilder<member_kind, record_t>::argsT() const
    {
        auto normalId = traits::uid<traits::normal_sign_id_t<args_t...>>::value;
        return { m_method, getRefAndValueOverloads(m_method, normalId) };
    }


    template<member member_kind, class record_t>
    inline std::vector<type_meta>HopBuilder <member_kind, record_t>::getRefAndValueOverloads(const Method& pMethod, 
                                                                                             const traits::uid_t pNormalId)
    {
        std::vector<rtl::type_meta> fnTypeMetas(call_by::ncref);
        for (auto& typeMeta : pMethod.getFunctorsMeta())
        {
            if constexpr (!std::is_same_v<record_t, RObject>)
            {
                if (traits::uid<record_t>::value != typeMeta.get_record_id()) {
                    return fnTypeMetas;
                }
            }
            if (member_kind != typeMeta.get_member_kind()) {
                continue;
            }
            if (pNormalId == typeMeta.get_normal_args_id())
            {
                if (pNormalId == typeMeta.get_strict_args_id()) {
                    fnTypeMetas[call_by::value] = typeMeta;
                }
                else if (!typeMeta.is_any_arg_ncref()) {
                    fnTypeMetas[call_by::cref] = typeMeta;
                }
                else fnTypeMetas.push_back(typeMeta);
            }
        }
        return fnTypeMetas;
    }
}



namespace rtl::detail
{
    template<member member_kind, class record_t, class ...args_t>
    template<class return_t> requires (!traits::type_aware_v<record_t, return_t>)
    inline constexpr method<record_t, return_t(args_t...)> InitMethodHop<member_kind, record_t, args_t...>::returnT() const
    {
        using hopper_t = typename method<record_t, return_t(args_t...)>::hopper_t;

        auto validateReturn = [](const std::vector<type_meta>& overloadsMeta, hopper_t& pHopper)-> bool {
            if constexpr (!std::is_same_v <return_t, Return>) {
                for (auto& tyMeta : overloadsMeta) {
                    if (!tyMeta.is_empty() && tyMeta.is_void()) {    // Temporary Quick Fix.
                        //TODO: needs to be fixed for erased-target-known-return. specifically for 'void'.
                        return true;
                    }
                    if (!tyMeta.is_empty())
                    {
                        if (tyMeta.get_return_id() != traits::uid<return_t>::value) {
                            //TODO: Not tested yet.
                            pHopper.set_init_error(error::ReturnTypeMismatch);
                            return false;
                        }
                    }
                }
            }
            return true;
        };

        auto mth = method<record_t, return_t(args_t...)>();
        auto normalId = traits::uid<traits::normal_sign_id_t<args_t...>>::value;
        auto recordId = m_method.getRecordTypeId();

        if constexpr (member_kind == member::Const) {

            if (validateReturn(m_overloadsMeta, mth.get_c_hops())) {
                init<return_t>(recordId, m_overloadsMeta, mth.get_c_hops());
            }
            auto overloadsMeta = HopBuilder<member::NonConst, record_t>::getRefAndValueOverloads(m_method, normalId);
            if (validateReturn(overloadsMeta, mth.get_nc_hops())) {
                init<return_t>(recordId, overloadsMeta, mth.get_nc_hops());
            }
        }
        else if constexpr (member_kind == member::NonConst) {

            if (validateReturn(m_overloadsMeta, mth.get_nc_hops())) {
                init<return_t>(recordId, m_overloadsMeta, mth.get_nc_hops());
            }
            auto overloadsMeta = HopBuilder<member::Const, record_t>::getRefAndValueOverloads(m_method, normalId);
            if (validateReturn(overloadsMeta, mth.get_c_hops())) {
                init<return_t>(recordId, overloadsMeta, mth.get_c_hops());
            }
        }

        if (mth.get_nc_hops().get_init_error() == error::None &&
            mth.get_c_hops().get_init_error() != error::None) {
            mth.get_c_hops().set_init_error(error::ConstOverloadMissing);
        }
        else if (mth.get_c_hops().get_init_error() == error::None &&
            mth.get_nc_hops().get_init_error() != error::None) {
            mth.get_nc_hops().set_init_error(error::NonConstOverloadMissing);
        }
        return mth;
    }


    template<member member_kind, class record_t, class ...args_t>
    template<class return_t> requires (traits::type_aware_v<record_t, return_t>)
    inline constexpr typename InitMethodHop<member_kind, record_t, args_t...>::template method_t<return_t>
    InitMethodHop<member_kind, record_t, args_t...>::returnT() const
    {
        auto mth = []()->decltype(auto) {
            if constexpr (member_kind == member::Const) {
                return const_method<record_t, return_t(args_t...)>();
            }
            else {
                return method<record_t, return_t(args_t...)>();
            }
        }();

        auto strictId = traits::uid<traits::strict_sign_id_t<args_t...>>::value;
        using rec_t = std::conditional_t<member_kind == member::Const, const record_t, record_t>;
        using method_ptr_t = dispatch::method_ptr<rec_t, return_t, args_t...>;

        for (auto& tyMeta : m_overloadsMeta) {
            if (!tyMeta.is_empty())
            {
                if (tyMeta.get_return_id() != traits::uid<return_t>::value) {
                    mth.set_init_error(error::ReturnTypeMismatch);
                    return mth;
                }
                if (tyMeta.get_strict_args_id() == strictId) {
                    auto fptr = static_cast<const method_ptr_t&>(tyMeta.get_functor()).f_ptr();
                    return method_t<return_t>(fptr);
                }
            }
        }
        mth.set_init_error(error::SignatureMismatch);
        return mth;
    }


    template<member member_kind, class record_t, class ...args_t>
    template<class return_t>
    inline void InitMethodHop<member_kind, record_t, args_t...>::init(const traits::uid_t pRecordId, 
                                                                      const std::vector<rtl::type_meta>& pRefOverloads,
                                                                      typename method<record_t, return_t(args_t...)>::hopper_t& pHopper)
    {
        for (auto& typeMeta : pRefOverloads)
        {
            if (typeMeta.is_empty()) {
                pHopper.get_hopper().push_back(nullptr);
                pHopper.get_overloads().push_back(nullptr);
                continue;
            }

            auto fn = [&]()-> decltype(auto) {
                if constexpr (traits::type_erased_v<record_t, return_t>) {

                    using fn_cast = dispatch::functor_cast<traits::normal_sign_t<args_t>...>;
                    return fn_cast(typeMeta.get_functor()).to_method();
                }
                else if constexpr (traits::target_erased_v<record_t, return_t>) {

                    using fn_cast = dispatch::functor_cast<traits::normal_sign_t<args_t>...>;
                    return fn_cast(typeMeta.get_functor()).template to_method<dispatch::erase::t_target, return_t>();
                }
                else if constexpr (traits::return_erased_v<record_t, return_t>) {

                    using fn_cast = dispatch::functor_cast<traits::normal_sign_t<args_t>...>;
                    return fn_cast(typeMeta.get_functor()).template to_method<dispatch::erase::t_return, record_t>();
                }
            }();

            pHopper.get_hopper().push_back(fn.f_ptr());
            pHopper.get_overloads().push_back(&typeMeta.get_functor());
            pHopper.set_init_error(error::None);
        }

        if (pHopper.get_init_error() != error::None) {
            pHopper.set_init_error(error::SignatureMismatch);
        }
        else {
            pHopper.set_record_id(pRecordId);
        }
    }
}
