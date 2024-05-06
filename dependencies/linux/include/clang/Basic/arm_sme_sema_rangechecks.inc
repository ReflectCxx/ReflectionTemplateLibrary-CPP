#ifdef GET_SME_IMMEDIATE_CHECK
case SME::BI__builtin_sme_svaddha_za32_s32_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
  break;
case SME::BI__builtin_sme_svaddha_za32_u32_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
  break;
case SME::BI__builtin_sme_svaddha_za64_s64_m:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
  break;
case SME::BI__builtin_sme_svaddha_za64_u64_m:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
  break;
case SME::BI__builtin_sme_svaddva_za32_s32_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
  break;
case SME::BI__builtin_sme_svaddva_za32_u32_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
  break;
case SME::BI__builtin_sme_svaddva_za64_s64_m:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
  break;
case SME::BI__builtin_sme_svaddva_za64_u64_m:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
  break;
case SME::BI__builtin_sme_svld1_hor_vnum_za128:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svld1_hor_vnum_za16:
ImmChecks.push_back(std::make_tuple(0, 13, 0));
ImmChecks.push_back(std::make_tuple(2, 6, 0));
  break;
case SME::BI__builtin_sme_svld1_hor_vnum_za32:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
ImmChecks.push_back(std::make_tuple(2, 15, 0));
  break;
case SME::BI__builtin_sme_svld1_hor_vnum_za64:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
ImmChecks.push_back(std::make_tuple(2, 13, 0));
  break;
case SME::BI__builtin_sme_svld1_hor_vnum_za8:
ImmChecks.push_back(std::make_tuple(0, 16, 0));
ImmChecks.push_back(std::make_tuple(2, 17, 0));
  break;
case SME::BI__builtin_sme_svld1_hor_za128:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svld1_hor_za16:
ImmChecks.push_back(std::make_tuple(0, 13, 0));
ImmChecks.push_back(std::make_tuple(2, 6, 0));
  break;
case SME::BI__builtin_sme_svld1_hor_za32:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
ImmChecks.push_back(std::make_tuple(2, 15, 0));
  break;
case SME::BI__builtin_sme_svld1_hor_za64:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
ImmChecks.push_back(std::make_tuple(2, 13, 0));
  break;
case SME::BI__builtin_sme_svld1_hor_za8:
ImmChecks.push_back(std::make_tuple(0, 16, 0));
ImmChecks.push_back(std::make_tuple(2, 17, 0));
  break;
case SME::BI__builtin_sme_svld1_ver_vnum_za128:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svld1_ver_vnum_za16:
ImmChecks.push_back(std::make_tuple(0, 13, 0));
ImmChecks.push_back(std::make_tuple(2, 6, 0));
  break;
case SME::BI__builtin_sme_svld1_ver_vnum_za32:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
ImmChecks.push_back(std::make_tuple(2, 15, 0));
  break;
case SME::BI__builtin_sme_svld1_ver_vnum_za64:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
ImmChecks.push_back(std::make_tuple(2, 13, 0));
  break;
case SME::BI__builtin_sme_svld1_ver_vnum_za8:
ImmChecks.push_back(std::make_tuple(0, 16, 0));
ImmChecks.push_back(std::make_tuple(2, 17, 0));
  break;
case SME::BI__builtin_sme_svld1_ver_za128:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svld1_ver_za16:
ImmChecks.push_back(std::make_tuple(0, 13, 0));
ImmChecks.push_back(std::make_tuple(2, 6, 0));
  break;
case SME::BI__builtin_sme_svld1_ver_za32:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
ImmChecks.push_back(std::make_tuple(2, 15, 0));
  break;
case SME::BI__builtin_sme_svld1_ver_za64:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
ImmChecks.push_back(std::make_tuple(2, 13, 0));
  break;
case SME::BI__builtin_sme_svld1_ver_za8:
ImmChecks.push_back(std::make_tuple(0, 16, 0));
ImmChecks.push_back(std::make_tuple(2, 17, 0));
  break;
case SME::BI__builtin_sme_svldr_vnum_za:
ImmChecks.push_back(std::make_tuple(1, 17, 0));
  break;
case SME::BI__builtin_sme_svmopa_za32_bf16_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
  break;
case SME::BI__builtin_sme_svmopa_za32_f16_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
  break;
case SME::BI__builtin_sme_svmopa_za32_f32_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
  break;
case SME::BI__builtin_sme_svmopa_za32_s8_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
  break;
case SME::BI__builtin_sme_svmopa_za32_u8_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
  break;
case SME::BI__builtin_sme_svmopa_za64_f64_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
  break;
case SME::BI__builtin_sme_svmopa_za64_s16_m:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
  break;
case SME::BI__builtin_sme_svmopa_za64_u16_m:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
  break;
case SME::BI__builtin_sme_svmops_za32_bf16_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
  break;
case SME::BI__builtin_sme_svmops_za32_f16_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
  break;
case SME::BI__builtin_sme_svmops_za32_f32_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
  break;
case SME::BI__builtin_sme_svmops_za32_s8_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
  break;
case SME::BI__builtin_sme_svmops_za32_u8_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
  break;
case SME::BI__builtin_sme_svmops_za64_f64_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
  break;
case SME::BI__builtin_sme_svmops_za64_s16_m:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
  break;
case SME::BI__builtin_sme_svmops_za64_u16_m:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
  break;
case SME::BI__builtin_sme_svread_hor_za128_bf16_m:
ImmChecks.push_back(std::make_tuple(2, 17, 0));
ImmChecks.push_back(std::make_tuple(4, 16, 0));
  break;
case SME::BI__builtin_sme_svread_hor_za128_f16_m:
ImmChecks.push_back(std::make_tuple(2, 17, 0));
ImmChecks.push_back(std::make_tuple(4, 16, 0));
  break;
case SME::BI__builtin_sme_svread_hor_za128_f32_m:
ImmChecks.push_back(std::make_tuple(2, 17, 0));
ImmChecks.push_back(std::make_tuple(4, 16, 0));
  break;
case SME::BI__builtin_sme_svread_hor_za128_f64_m:
ImmChecks.push_back(std::make_tuple(2, 17, 0));
ImmChecks.push_back(std::make_tuple(4, 16, 0));
  break;
case SME::BI__builtin_sme_svread_hor_za128_s16_m:
ImmChecks.push_back(std::make_tuple(2, 17, 0));
ImmChecks.push_back(std::make_tuple(4, 16, 0));
  break;
case SME::BI__builtin_sme_svread_hor_za128_s32_m:
ImmChecks.push_back(std::make_tuple(2, 17, 0));
ImmChecks.push_back(std::make_tuple(4, 16, 0));
  break;
case SME::BI__builtin_sme_svread_hor_za128_s64_m:
ImmChecks.push_back(std::make_tuple(2, 17, 0));
ImmChecks.push_back(std::make_tuple(4, 16, 0));
  break;
case SME::BI__builtin_sme_svread_hor_za128_s8_m:
ImmChecks.push_back(std::make_tuple(2, 17, 0));
ImmChecks.push_back(std::make_tuple(4, 16, 0));
  break;
case SME::BI__builtin_sme_svread_hor_za128_u16_m:
ImmChecks.push_back(std::make_tuple(2, 17, 0));
ImmChecks.push_back(std::make_tuple(4, 16, 0));
  break;
case SME::BI__builtin_sme_svread_hor_za128_u32_m:
ImmChecks.push_back(std::make_tuple(2, 17, 0));
ImmChecks.push_back(std::make_tuple(4, 16, 0));
  break;
case SME::BI__builtin_sme_svread_hor_za128_u64_m:
ImmChecks.push_back(std::make_tuple(2, 17, 0));
ImmChecks.push_back(std::make_tuple(4, 16, 0));
  break;
case SME::BI__builtin_sme_svread_hor_za128_u8_m:
ImmChecks.push_back(std::make_tuple(2, 17, 0));
ImmChecks.push_back(std::make_tuple(4, 16, 0));
  break;
case SME::BI__builtin_sme_svread_hor_za16_bf16_m:
ImmChecks.push_back(std::make_tuple(2, 13, 0));
ImmChecks.push_back(std::make_tuple(4, 6, 0));
  break;
case SME::BI__builtin_sme_svread_hor_za16_f16_m:
ImmChecks.push_back(std::make_tuple(2, 13, 0));
ImmChecks.push_back(std::make_tuple(4, 6, 0));
  break;
case SME::BI__builtin_sme_svread_hor_za16_s16_m:
ImmChecks.push_back(std::make_tuple(2, 13, 0));
ImmChecks.push_back(std::make_tuple(4, 6, 0));
  break;
case SME::BI__builtin_sme_svread_hor_za16_u16_m:
ImmChecks.push_back(std::make_tuple(2, 13, 0));
ImmChecks.push_back(std::make_tuple(4, 6, 0));
  break;
case SME::BI__builtin_sme_svread_hor_za32_f32_m:
ImmChecks.push_back(std::make_tuple(2, 15, 0));
ImmChecks.push_back(std::make_tuple(4, 15, 0));
  break;
case SME::BI__builtin_sme_svread_hor_za32_s32_m:
ImmChecks.push_back(std::make_tuple(2, 15, 0));
ImmChecks.push_back(std::make_tuple(4, 15, 0));
  break;
case SME::BI__builtin_sme_svread_hor_za32_u32_m:
ImmChecks.push_back(std::make_tuple(2, 15, 0));
ImmChecks.push_back(std::make_tuple(4, 15, 0));
  break;
case SME::BI__builtin_sme_svread_hor_za64_f64_m:
ImmChecks.push_back(std::make_tuple(2, 6, 0));
ImmChecks.push_back(std::make_tuple(4, 13, 0));
  break;
case SME::BI__builtin_sme_svread_hor_za64_s64_m:
ImmChecks.push_back(std::make_tuple(2, 6, 0));
ImmChecks.push_back(std::make_tuple(4, 13, 0));
  break;
case SME::BI__builtin_sme_svread_hor_za64_u64_m:
ImmChecks.push_back(std::make_tuple(2, 6, 0));
ImmChecks.push_back(std::make_tuple(4, 13, 0));
  break;
case SME::BI__builtin_sme_svread_hor_za8_s8_m:
ImmChecks.push_back(std::make_tuple(2, 16, 0));
ImmChecks.push_back(std::make_tuple(4, 17, 0));
  break;
case SME::BI__builtin_sme_svread_hor_za8_u8_m:
ImmChecks.push_back(std::make_tuple(2, 16, 0));
ImmChecks.push_back(std::make_tuple(4, 17, 0));
  break;
case SME::BI__builtin_sme_svread_ver_za128_bf16_m:
ImmChecks.push_back(std::make_tuple(2, 17, 0));
ImmChecks.push_back(std::make_tuple(4, 16, 0));
  break;
case SME::BI__builtin_sme_svread_ver_za128_f16_m:
ImmChecks.push_back(std::make_tuple(2, 17, 0));
ImmChecks.push_back(std::make_tuple(4, 16, 0));
  break;
case SME::BI__builtin_sme_svread_ver_za128_f32_m:
ImmChecks.push_back(std::make_tuple(2, 17, 0));
ImmChecks.push_back(std::make_tuple(4, 16, 0));
  break;
case SME::BI__builtin_sme_svread_ver_za128_f64_m:
ImmChecks.push_back(std::make_tuple(2, 17, 0));
ImmChecks.push_back(std::make_tuple(4, 16, 0));
  break;
case SME::BI__builtin_sme_svread_ver_za128_s16_m:
ImmChecks.push_back(std::make_tuple(2, 17, 0));
ImmChecks.push_back(std::make_tuple(4, 16, 0));
  break;
case SME::BI__builtin_sme_svread_ver_za128_s32_m:
ImmChecks.push_back(std::make_tuple(2, 17, 0));
ImmChecks.push_back(std::make_tuple(4, 16, 0));
  break;
case SME::BI__builtin_sme_svread_ver_za128_s64_m:
ImmChecks.push_back(std::make_tuple(2, 17, 0));
ImmChecks.push_back(std::make_tuple(4, 16, 0));
  break;
case SME::BI__builtin_sme_svread_ver_za128_s8_m:
ImmChecks.push_back(std::make_tuple(2, 17, 0));
ImmChecks.push_back(std::make_tuple(4, 16, 0));
  break;
case SME::BI__builtin_sme_svread_ver_za128_u16_m:
ImmChecks.push_back(std::make_tuple(2, 17, 0));
ImmChecks.push_back(std::make_tuple(4, 16, 0));
  break;
case SME::BI__builtin_sme_svread_ver_za128_u32_m:
ImmChecks.push_back(std::make_tuple(2, 17, 0));
ImmChecks.push_back(std::make_tuple(4, 16, 0));
  break;
case SME::BI__builtin_sme_svread_ver_za128_u64_m:
ImmChecks.push_back(std::make_tuple(2, 17, 0));
ImmChecks.push_back(std::make_tuple(4, 16, 0));
  break;
case SME::BI__builtin_sme_svread_ver_za128_u8_m:
ImmChecks.push_back(std::make_tuple(2, 17, 0));
ImmChecks.push_back(std::make_tuple(4, 16, 0));
  break;
case SME::BI__builtin_sme_svread_ver_za16_bf16_m:
ImmChecks.push_back(std::make_tuple(2, 13, 0));
ImmChecks.push_back(std::make_tuple(4, 6, 0));
  break;
case SME::BI__builtin_sme_svread_ver_za16_f16_m:
ImmChecks.push_back(std::make_tuple(2, 13, 0));
ImmChecks.push_back(std::make_tuple(4, 6, 0));
  break;
case SME::BI__builtin_sme_svread_ver_za16_s16_m:
ImmChecks.push_back(std::make_tuple(2, 13, 0));
ImmChecks.push_back(std::make_tuple(4, 6, 0));
  break;
case SME::BI__builtin_sme_svread_ver_za16_u16_m:
ImmChecks.push_back(std::make_tuple(2, 13, 0));
ImmChecks.push_back(std::make_tuple(4, 6, 0));
  break;
case SME::BI__builtin_sme_svread_ver_za32_f32_m:
ImmChecks.push_back(std::make_tuple(2, 15, 0));
ImmChecks.push_back(std::make_tuple(4, 15, 0));
  break;
case SME::BI__builtin_sme_svread_ver_za32_s32_m:
ImmChecks.push_back(std::make_tuple(2, 15, 0));
ImmChecks.push_back(std::make_tuple(4, 15, 0));
  break;
case SME::BI__builtin_sme_svread_ver_za32_u32_m:
ImmChecks.push_back(std::make_tuple(2, 15, 0));
ImmChecks.push_back(std::make_tuple(4, 15, 0));
  break;
case SME::BI__builtin_sme_svread_ver_za64_f64_m:
ImmChecks.push_back(std::make_tuple(2, 6, 0));
ImmChecks.push_back(std::make_tuple(4, 13, 0));
  break;
case SME::BI__builtin_sme_svread_ver_za64_s64_m:
ImmChecks.push_back(std::make_tuple(2, 6, 0));
ImmChecks.push_back(std::make_tuple(4, 13, 0));
  break;
case SME::BI__builtin_sme_svread_ver_za64_u64_m:
ImmChecks.push_back(std::make_tuple(2, 6, 0));
ImmChecks.push_back(std::make_tuple(4, 13, 0));
  break;
case SME::BI__builtin_sme_svread_ver_za8_s8_m:
ImmChecks.push_back(std::make_tuple(2, 16, 0));
ImmChecks.push_back(std::make_tuple(4, 17, 0));
  break;
case SME::BI__builtin_sme_svread_ver_za8_u8_m:
ImmChecks.push_back(std::make_tuple(2, 16, 0));
ImmChecks.push_back(std::make_tuple(4, 17, 0));
  break;
case SME::BI__builtin_sme_svst1_hor_vnum_za128:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svst1_hor_vnum_za16:
ImmChecks.push_back(std::make_tuple(0, 13, 0));
ImmChecks.push_back(std::make_tuple(2, 6, 0));
  break;
case SME::BI__builtin_sme_svst1_hor_vnum_za32:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
ImmChecks.push_back(std::make_tuple(2, 15, 0));
  break;
case SME::BI__builtin_sme_svst1_hor_vnum_za64:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
ImmChecks.push_back(std::make_tuple(2, 13, 0));
  break;
case SME::BI__builtin_sme_svst1_hor_vnum_za8:
ImmChecks.push_back(std::make_tuple(0, 16, 0));
ImmChecks.push_back(std::make_tuple(2, 17, 0));
  break;
case SME::BI__builtin_sme_svst1_hor_za128:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svst1_hor_za16:
ImmChecks.push_back(std::make_tuple(0, 13, 0));
ImmChecks.push_back(std::make_tuple(2, 6, 0));
  break;
case SME::BI__builtin_sme_svst1_hor_za32:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
ImmChecks.push_back(std::make_tuple(2, 15, 0));
  break;
case SME::BI__builtin_sme_svst1_hor_za64:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
ImmChecks.push_back(std::make_tuple(2, 13, 0));
  break;
case SME::BI__builtin_sme_svst1_hor_za8:
ImmChecks.push_back(std::make_tuple(0, 16, 0));
ImmChecks.push_back(std::make_tuple(2, 17, 0));
  break;
case SME::BI__builtin_sme_svst1_ver_vnum_za128:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svst1_ver_vnum_za16:
ImmChecks.push_back(std::make_tuple(0, 13, 0));
ImmChecks.push_back(std::make_tuple(2, 6, 0));
  break;
case SME::BI__builtin_sme_svst1_ver_vnum_za32:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
ImmChecks.push_back(std::make_tuple(2, 15, 0));
  break;
case SME::BI__builtin_sme_svst1_ver_vnum_za64:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
ImmChecks.push_back(std::make_tuple(2, 13, 0));
  break;
case SME::BI__builtin_sme_svst1_ver_vnum_za8:
ImmChecks.push_back(std::make_tuple(0, 16, 0));
ImmChecks.push_back(std::make_tuple(2, 17, 0));
  break;
case SME::BI__builtin_sme_svst1_ver_za128:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svst1_ver_za16:
ImmChecks.push_back(std::make_tuple(0, 13, 0));
ImmChecks.push_back(std::make_tuple(2, 6, 0));
  break;
case SME::BI__builtin_sme_svst1_ver_za32:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
ImmChecks.push_back(std::make_tuple(2, 15, 0));
  break;
case SME::BI__builtin_sme_svst1_ver_za64:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
ImmChecks.push_back(std::make_tuple(2, 13, 0));
  break;
case SME::BI__builtin_sme_svst1_ver_za8:
ImmChecks.push_back(std::make_tuple(0, 16, 0));
ImmChecks.push_back(std::make_tuple(2, 17, 0));
  break;
case SME::BI__builtin_sme_svstr_vnum_za:
ImmChecks.push_back(std::make_tuple(1, 17, 0));
  break;
case SME::BI__builtin_sme_svsumopa_za32_s8_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
  break;
case SME::BI__builtin_sme_svsumopa_za64_s16_m:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
  break;
case SME::BI__builtin_sme_svsumops_za32_s8_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
  break;
case SME::BI__builtin_sme_svsumops_za64_s16_m:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
  break;
case SME::BI__builtin_sme_svusmopa_za32_u8_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
  break;
case SME::BI__builtin_sme_svusmopa_za64_u16_m:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
  break;
case SME::BI__builtin_sme_svusmops_za32_u8_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
  break;
case SME::BI__builtin_sme_svusmops_za64_u16_m:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
  break;
case SME::BI__builtin_sme_svwrite_hor_za128_bf16_m:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svwrite_hor_za128_f16_m:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svwrite_hor_za128_f32_m:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svwrite_hor_za128_f64_m:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svwrite_hor_za128_s16_m:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svwrite_hor_za128_s32_m:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svwrite_hor_za128_s64_m:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svwrite_hor_za128_s8_m:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svwrite_hor_za128_u16_m:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svwrite_hor_za128_u32_m:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svwrite_hor_za128_u64_m:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svwrite_hor_za128_u8_m:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svwrite_hor_za16_bf16_m:
ImmChecks.push_back(std::make_tuple(0, 13, 0));
ImmChecks.push_back(std::make_tuple(2, 6, 0));
  break;
case SME::BI__builtin_sme_svwrite_hor_za16_f16_m:
ImmChecks.push_back(std::make_tuple(0, 13, 0));
ImmChecks.push_back(std::make_tuple(2, 6, 0));
  break;
case SME::BI__builtin_sme_svwrite_hor_za16_s16_m:
ImmChecks.push_back(std::make_tuple(0, 13, 0));
ImmChecks.push_back(std::make_tuple(2, 6, 0));
  break;
case SME::BI__builtin_sme_svwrite_hor_za16_u16_m:
ImmChecks.push_back(std::make_tuple(0, 13, 0));
ImmChecks.push_back(std::make_tuple(2, 6, 0));
  break;
case SME::BI__builtin_sme_svwrite_hor_za32_f32_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
ImmChecks.push_back(std::make_tuple(2, 15, 0));
  break;
case SME::BI__builtin_sme_svwrite_hor_za32_s32_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
ImmChecks.push_back(std::make_tuple(2, 15, 0));
  break;
case SME::BI__builtin_sme_svwrite_hor_za32_u32_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
ImmChecks.push_back(std::make_tuple(2, 15, 0));
  break;
case SME::BI__builtin_sme_svwrite_hor_za64_f64_m:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
ImmChecks.push_back(std::make_tuple(2, 13, 0));
  break;
case SME::BI__builtin_sme_svwrite_hor_za64_s64_m:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
ImmChecks.push_back(std::make_tuple(2, 13, 0));
  break;
case SME::BI__builtin_sme_svwrite_hor_za64_u64_m:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
ImmChecks.push_back(std::make_tuple(2, 13, 0));
  break;
case SME::BI__builtin_sme_svwrite_hor_za8_s8_m:
ImmChecks.push_back(std::make_tuple(0, 16, 0));
ImmChecks.push_back(std::make_tuple(2, 17, 0));
  break;
case SME::BI__builtin_sme_svwrite_hor_za8_u8_m:
ImmChecks.push_back(std::make_tuple(0, 16, 0));
ImmChecks.push_back(std::make_tuple(2, 17, 0));
  break;
case SME::BI__builtin_sme_svwrite_ver_za128_bf16_m:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svwrite_ver_za128_f16_m:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svwrite_ver_za128_f32_m:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svwrite_ver_za128_f64_m:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svwrite_ver_za128_s16_m:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svwrite_ver_za128_s32_m:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svwrite_ver_za128_s64_m:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svwrite_ver_za128_s8_m:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svwrite_ver_za128_u16_m:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svwrite_ver_za128_u32_m:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svwrite_ver_za128_u64_m:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svwrite_ver_za128_u8_m:
ImmChecks.push_back(std::make_tuple(0, 17, 0));
ImmChecks.push_back(std::make_tuple(2, 16, 0));
  break;
case SME::BI__builtin_sme_svwrite_ver_za16_bf16_m:
ImmChecks.push_back(std::make_tuple(0, 13, 0));
ImmChecks.push_back(std::make_tuple(2, 6, 0));
  break;
case SME::BI__builtin_sme_svwrite_ver_za16_f16_m:
ImmChecks.push_back(std::make_tuple(0, 13, 0));
ImmChecks.push_back(std::make_tuple(2, 6, 0));
  break;
case SME::BI__builtin_sme_svwrite_ver_za16_s16_m:
ImmChecks.push_back(std::make_tuple(0, 13, 0));
ImmChecks.push_back(std::make_tuple(2, 6, 0));
  break;
case SME::BI__builtin_sme_svwrite_ver_za16_u16_m:
ImmChecks.push_back(std::make_tuple(0, 13, 0));
ImmChecks.push_back(std::make_tuple(2, 6, 0));
  break;
case SME::BI__builtin_sme_svwrite_ver_za32_f32_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
ImmChecks.push_back(std::make_tuple(2, 15, 0));
  break;
case SME::BI__builtin_sme_svwrite_ver_za32_s32_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
ImmChecks.push_back(std::make_tuple(2, 15, 0));
  break;
case SME::BI__builtin_sme_svwrite_ver_za32_u32_m:
ImmChecks.push_back(std::make_tuple(0, 15, 0));
ImmChecks.push_back(std::make_tuple(2, 15, 0));
  break;
case SME::BI__builtin_sme_svwrite_ver_za64_f64_m:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
ImmChecks.push_back(std::make_tuple(2, 13, 0));
  break;
case SME::BI__builtin_sme_svwrite_ver_za64_s64_m:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
ImmChecks.push_back(std::make_tuple(2, 13, 0));
  break;
case SME::BI__builtin_sme_svwrite_ver_za64_u64_m:
ImmChecks.push_back(std::make_tuple(0, 6, 0));
ImmChecks.push_back(std::make_tuple(2, 13, 0));
  break;
case SME::BI__builtin_sme_svwrite_ver_za8_s8_m:
ImmChecks.push_back(std::make_tuple(0, 16, 0));
ImmChecks.push_back(std::make_tuple(2, 17, 0));
  break;
case SME::BI__builtin_sme_svwrite_ver_za8_u8_m:
ImmChecks.push_back(std::make_tuple(0, 16, 0));
ImmChecks.push_back(std::make_tuple(2, 17, 0));
  break;
case SME::BI__builtin_sme_svzero_mask_za:
ImmChecks.push_back(std::make_tuple(0, 18, 0));
  break;
#endif

