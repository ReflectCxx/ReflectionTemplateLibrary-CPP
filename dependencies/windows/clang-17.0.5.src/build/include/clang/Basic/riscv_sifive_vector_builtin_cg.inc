case RISCVVector::BI__builtin_rvv_sf_vc_fv_se:
  ID = Intrinsic::riscv_sf_vc_fv_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_fvv_se:
  ID = Intrinsic::riscv_sf_vc_fvv_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[1]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_fvw_se:
  ID = Intrinsic::riscv_sf_vc_fvw_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[1]->getType(), Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_i_se_u16m1:
  ID = Intrinsic::riscv_sf_vc_i_se_e16m1;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_i_se_u16m2:
  ID = Intrinsic::riscv_sf_vc_i_se_e16m2;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_i_se_u16m4:
  ID = Intrinsic::riscv_sf_vc_i_se_e16m4;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_i_se_u16m8:
  ID = Intrinsic::riscv_sf_vc_i_se_e16m8;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_i_se_u16mf2:
  ID = Intrinsic::riscv_sf_vc_i_se_e16mf2;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_i_se_u16mf4:
  ID = Intrinsic::riscv_sf_vc_i_se_e16mf4;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_i_se_u32m1:
  ID = Intrinsic::riscv_sf_vc_i_se_e32m1;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_i_se_u32m2:
  ID = Intrinsic::riscv_sf_vc_i_se_e32m2;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_i_se_u32m4:
  ID = Intrinsic::riscv_sf_vc_i_se_e32m4;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_i_se_u32m8:
  ID = Intrinsic::riscv_sf_vc_i_se_e32m8;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_i_se_u32mf2:
  ID = Intrinsic::riscv_sf_vc_i_se_e32mf2;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_i_se_u64m1:
  ID = Intrinsic::riscv_sf_vc_i_se_e64m1;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_i_se_u64m2:
  ID = Intrinsic::riscv_sf_vc_i_se_e64m2;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_i_se_u64m4:
  ID = Intrinsic::riscv_sf_vc_i_se_e64m4;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_i_se_u64m8:
  ID = Intrinsic::riscv_sf_vc_i_se_e64m8;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_i_se_u8m1:
  ID = Intrinsic::riscv_sf_vc_i_se_e8m1;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_i_se_u8m2:
  ID = Intrinsic::riscv_sf_vc_i_se_e8m2;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_i_se_u8m4:
  ID = Intrinsic::riscv_sf_vc_i_se_e8m4;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_i_se_u8m8:
  ID = Intrinsic::riscv_sf_vc_i_se_e8m8;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_i_se_u8mf2:
  ID = Intrinsic::riscv_sf_vc_i_se_e8mf2;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_i_se_u8mf4:
  ID = Intrinsic::riscv_sf_vc_i_se_e8mf4;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_i_se_u8mf8:
  ID = Intrinsic::riscv_sf_vc_i_se_e8mf8;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_iv_se:
  ID = Intrinsic::riscv_sf_vc_iv_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_ivv_se:
  ID = Intrinsic::riscv_sf_vc_ivv_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[1]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_ivw_se:
  ID = Intrinsic::riscv_sf_vc_ivw_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[1]->getType(), Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_fv:
  ID = Intrinsic::riscv_sf_vc_v_fv;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[0]->getType(), Ops[2]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_fv_se:
  ID = Intrinsic::riscv_sf_vc_v_fv_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[0]->getType(), Ops[2]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_fvv:
  ID = Intrinsic::riscv_sf_vc_v_fvv;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_fvv_se:
  ID = Intrinsic::riscv_sf_vc_v_fvv_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_fvw:
  ID = Intrinsic::riscv_sf_vc_v_fvw;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[0]->getType(), Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_fvw_se:
  ID = Intrinsic::riscv_sf_vc_v_fvw_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[0]->getType(), Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_i:
  ID = Intrinsic::riscv_sf_vc_v_i;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[1]->getType(), Ops[2]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_i_se:
  ID = Intrinsic::riscv_sf_vc_v_i_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[1]->getType(), Ops[2]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_iv:
  ID = Intrinsic::riscv_sf_vc_v_iv;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[0]->getType(), Ops[2]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_iv_se:
  ID = Intrinsic::riscv_sf_vc_v_iv_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[0]->getType(), Ops[2]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_ivv:
  ID = Intrinsic::riscv_sf_vc_v_ivv;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_ivv_se:
  ID = Intrinsic::riscv_sf_vc_v_ivv_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_ivw:
  ID = Intrinsic::riscv_sf_vc_v_ivw;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[0]->getType(), Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_ivw_se:
  ID = Intrinsic::riscv_sf_vc_v_ivw_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[0]->getType(), Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_vv:
  ID = Intrinsic::riscv_sf_vc_v_vv;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[0]->getType(), Ops[2]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_vv_se:
  ID = Intrinsic::riscv_sf_vc_v_vv_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[0]->getType(), Ops[2]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_vvv:
  ID = Intrinsic::riscv_sf_vc_v_vvv;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_vvv_se:
  ID = Intrinsic::riscv_sf_vc_v_vvv_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_vvw:
  ID = Intrinsic::riscv_sf_vc_v_vvw;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[0]->getType(), Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_vvw_se:
  ID = Intrinsic::riscv_sf_vc_v_vvw_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[0]->getType(), Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_x:
  ID = Intrinsic::riscv_sf_vc_v_x;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[1]->getType(), Ops[2]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_x_se:
  ID = Intrinsic::riscv_sf_vc_v_x_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[1]->getType(), Ops[2]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_xv:
  ID = Intrinsic::riscv_sf_vc_v_xv;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[0]->getType(), Ops[2]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_xv_se:
  ID = Intrinsic::riscv_sf_vc_v_xv_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[0]->getType(), Ops[2]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_xvv:
  ID = Intrinsic::riscv_sf_vc_v_xvv;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_xvv_se:
  ID = Intrinsic::riscv_sf_vc_v_xvv_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_xvw:
  ID = Intrinsic::riscv_sf_vc_v_xvw;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[0]->getType(), Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_v_xvw_se:
  ID = Intrinsic::riscv_sf_vc_v_xvw_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {ResultType, Ops[0]->getType(), Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_vv_se:
  ID = Intrinsic::riscv_sf_vc_vv_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_vvv_se:
  ID = Intrinsic::riscv_sf_vc_vvv_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[1]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_vvw_se:
  ID = Intrinsic::riscv_sf_vc_vvw_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[1]->getType(), Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_x_se_u16m1:
  ID = Intrinsic::riscv_sf_vc_x_se_e16m1;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_x_se_u16m2:
  ID = Intrinsic::riscv_sf_vc_x_se_e16m2;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_x_se_u16m4:
  ID = Intrinsic::riscv_sf_vc_x_se_e16m4;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_x_se_u16m8:
  ID = Intrinsic::riscv_sf_vc_x_se_e16m8;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_x_se_u16mf2:
  ID = Intrinsic::riscv_sf_vc_x_se_e16mf2;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_x_se_u16mf4:
  ID = Intrinsic::riscv_sf_vc_x_se_e16mf4;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_x_se_u32m1:
  ID = Intrinsic::riscv_sf_vc_x_se_e32m1;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_x_se_u32m2:
  ID = Intrinsic::riscv_sf_vc_x_se_e32m2;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_x_se_u32m4:
  ID = Intrinsic::riscv_sf_vc_x_se_e32m4;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_x_se_u32m8:
  ID = Intrinsic::riscv_sf_vc_x_se_e32m8;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_x_se_u32mf2:
  ID = Intrinsic::riscv_sf_vc_x_se_e32mf2;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_x_se_u64m1:
  ID = Intrinsic::riscv_sf_vc_x_se_e64m1;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_x_se_u64m2:
  ID = Intrinsic::riscv_sf_vc_x_se_e64m2;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_x_se_u64m4:
  ID = Intrinsic::riscv_sf_vc_x_se_e64m4;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_x_se_u64m8:
  ID = Intrinsic::riscv_sf_vc_x_se_e64m8;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_x_se_u8m1:
  ID = Intrinsic::riscv_sf_vc_x_se_e8m1;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_x_se_u8m2:
  ID = Intrinsic::riscv_sf_vc_x_se_e8m2;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_x_se_u8m4:
  ID = Intrinsic::riscv_sf_vc_x_se_e8m4;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_x_se_u8m8:
  ID = Intrinsic::riscv_sf_vc_x_se_e8m8;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_x_se_u8mf2:
  ID = Intrinsic::riscv_sf_vc_x_se_e8mf2;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_x_se_u8mf4:
  ID = Intrinsic::riscv_sf_vc_x_se_e8mf4;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_x_se_u8mf8:
  ID = Intrinsic::riscv_sf_vc_x_se_e8mf8;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_xv_se:
  ID = Intrinsic::riscv_sf_vc_xv_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_xvv_se:
  ID = Intrinsic::riscv_sf_vc_xvv_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[1]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;
case RISCVVector::BI__builtin_rvv_sf_vc_xvw_se:
  ID = Intrinsic::riscv_sf_vc_xvw_se;
  PolicyAttrs = 3;
  IntrinsicTypes = {Ops[0]->getType(), Ops[1]->getType(), Ops[2]->getType(), Ops[3]->getType(), Ops.back()->getType()};
  break;

