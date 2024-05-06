
#ifdef GET_DIAG_ARRAYS
static const int16_t DiagArrays[] = {
  /* Empty */ -1,
  /* DiagArray1 */ diag::warn_pragma_message, -1,
  /* DiagArray2 */ diag::pp_hash_warning, -1,
  /* DiagArray3 */ diag::warn_cfstring_truncated, -1,
  /* DiagArray5 */ diag::warn_independentclass_attribute, diag::warn_ptr_independentclass_attribute, -1,
  /* DiagArray6 */ diag::warn_nsobject_attribute, -1,
  /* DiagArray8 */ diag::warn_abs_too_small, diag::warn_pointer_abs, diag::warn_unsigned_abs, diag::warn_wrong_absolute_value_type, -1,
  /* DiagArray9 */ diag::warn_abstract_final_class, -1,
  /* DiagArray10 */ diag::warn_abstract_vbase_init_ignored, -1,
  /* DiagArray12 */ diag::warn_taking_address_of_packed_member, -1,
  /* DiagArray13 */ diag::ext_typecheck_addrof_temporary, -1,
  /* DiagArray15 */ diag::warn_not_xl_compatible, diag::warn_pragma_align_not_xl_compatible, -1,
  /* DiagArray16 */ diag::warn_param_mismatched_alignment, -1,
  /* DiagArray18 */ diag::warn_alloca, -1,
  /* DiagArray19 */ diag::warn_alloca_align_alignof, -1,
  /* DiagArray20 */ diag::warn_always_inline_coroutine, -1,
  /* DiagArray21 */ diag::warn_ambiguous_suitable_delete_function_found, -1,
  /* DiagArray22 */ diag::warn_misplaced_ellipsis_vararg, -1,
  /* DiagArray23 */ diag::warn_pp_ambiguous_macro, -1,
  /* DiagArray24 */ diag::ext_nested_name_member_ref_lookup_ambiguous, -1,
  /* DiagArray25 */ diag::ext_ovl_ambiguous_oper_binary_reversed, -1,
  /* DiagArray26 */ diag::warn_incompatible_analyzer_plugin_api, -1,
  /* DiagArray27 */ diag::warn_arith_conv_mixed_anon_enum_types, -1,
  /* DiagArray28 */ diag::ext_abstract_pack_declarator_parens, -1,
  /* DiagArray30 */ diag::warn_arc_bridge_cast_nonarc, -1,
  /* DiagArray31 */ diag::warn_arc_possible_repeated_use_of_weak, -1,
  /* DiagArray32 */ diag::warn_arc_object_memaccess, -1,
  /* DiagArray33 */ diag::warn_arc_perform_selector_leaks, -1,
  /* DiagArray34 */ diag::warn_arc_repeated_use_of_weak, -1,
  /* DiagArray35 */ diag::warn_arc_retain_cycle, -1,
  /* DiagArray36 */ diag::warn_arc_literal_assign, diag::warn_arc_retained_assign, diag::warn_arc_retained_property_assign, -1,
  /* DiagArray37 */ diag::warn_argument_invalid_range, -1,
  /* DiagArray38 */ diag::warn_argument_undefined_behaviour, -1,
  /* DiagArray39 */ diag::warn_array_index_exceeds_bounds, diag::warn_array_index_exceeds_max_addressable_bounds, diag::warn_array_index_precedes_bounds, diag::warn_ptr_arith_exceeds_max_addressable_bounds, diag::warn_static_array_too_small, -1,
  /* DiagArray40 */ diag::warn_ptr_arith_exceeds_bounds, diag::warn_ptr_arith_precedes_bounds, -1,
  /* DiagArray41 */ diag::warn_inconsistent_array_form, -1,
  /* DiagArray43 */ diag::warn_asm_mismatched_size_modifier, -1,
  /* DiagArray44 */ diag::warn_not_in_enum_assignment, -1,
  /* DiagArray45 */ diag::warn_assume_side_effects, -1,
  /* DiagArray47 */ diag::warn_atimport_in_framework_header, -1,
  /* DiagArray48 */ diag::warn_atomic_member_access, -1,
  /* DiagArray49 */ diag::warn_atomic_op_misaligned, diag::warn_atomic_op_oversized, -1,
  /* DiagArray50 */ diag::warn_atomic_implicit_seq_cst, -1,
  /* DiagArray51 */ diag::warn_atomic_op_has_invalid_memory_order, -1,
  /* DiagArray53 */ diag::warn_atomic_property_rule, -1,
  /* DiagArray54 */ diag::warn_attribute_packed_for_bitfield, -1,
  /* DiagArray55 */ diag::warn_fe_backend_warning_attr, -1,
  /* DiagArray57 */ diag::warn_drv_disabling_vptr_no_rtti_default, -1,
  /* DiagArray59 */ diag::ext_auto_storage_class, -1,
  /* DiagArray60 */ diag::warn_auto_var_is_id, -1,
  /* DiagArray61 */ diag::warn_availability_and_unavailable, diag::warn_availability_fuchsia_unavailable_minor, diag::warn_availability_on_static_initializer, diag::warn_availability_swift_unavailable_deprecated_only, diag::warn_availability_unknown_platform, diag::warn_availability_version_ordering, diag::warn_expected_consistent_version_separator, diag::warn_mismatched_availability, diag::warn_mismatched_availability_override, diag::warn_mismatched_availability_override_unavail, -1,
  /* DiagArray62 */ diag::warn_drv_avr_family_linking_stdlibs_not_implemented, diag::warn_drv_avr_libc_not_found, diag::warn_drv_avr_linker_section_addresses_not_implemented, diag::warn_drv_avr_mcu_not_specified, diag::warn_drv_avr_stdlib_not_linked, -1,
  /* DiagArray63 */ diag::warn_fe_backend_plugin, diag::warn_fe_backend_resource_limit, -1,
  /* DiagArray64 */ diag::backslash_newline_space, -1,
  /* DiagArray65 */ diag::warn_bad_function_cast, -1,
  /* DiagArray67 */ diag::ext_rvalue_to_reference_access_ctor, diag::ext_rvalue_to_reference_temp_copy_no_viable, -1,
  /* DiagArray68 */ diag::ext_decomp_decl_cond, -1,
  /* DiagArray69 */ diag::ext_bit_int, -1,
  /* DiagArray70 */ diag::warn_impcast_bitfield_precision_constant, -1,
  /* DiagArray71 */ diag::warn_bitfield_too_small_for_enum, diag::warn_signed_bitfield_enum_conversion, diag::warn_unsigned_bitfield_assigned_signed_enum, -1,
  /* DiagArray72 */ diag::warn_bitfield_width_exceeds_type_width, -1,
  /* DiagArray73 */ diag::warn_precedence_bitwise_conditional, -1,
  /* DiagArray74 */ diag::warn_bitwise_instead_of_logical, -1,
  /* DiagArray75 */ diag::warn_bitwise_op_in_bitwise_op, -1,
  /* DiagArray76 */ diag::warn_block_capture_autoreleasing, -1,
  /* DiagArray77 */ diag::warn_impcast_bool_to_null_pointer, -1,
  /* DiagArray79 */ diag::warn_bitwise_negation_bool, -1,
  /* DiagArray80 */ diag::warn_braces_around_init, -1,
  /* DiagArray81 */ diag::warn_incompatible_branch_protection_option, diag::warn_target_unsupported_branch_protection_attribute, diag::warn_unsupported_branch_protection, diag::warn_unsupported_branch_protection_spec, -1,
  /* DiagArray82 */ diag::warn_objc_invalid_bridge, diag::warn_objc_invalid_bridge_to_cf, -1,
  /* DiagArray83 */ diag::warn_assume_aligned_too_great, -1,
  /* DiagArray84 */ diag::ext_pp_redef_builtin_macro, diag::ext_pp_undef_builtin_macro, -1,
  /* DiagArray85 */ diag::warn_builtin_chk_overflow, -1,
  /* DiagArray86 */ diag::warn_implicit_decl_requires_sysheader, -1,
  /* DiagArray87 */ diag::warn_zero_size_struct_union_compat, -1,
  /* DiagArray91 */ diag::ext_old_implicitly_unsigned_long_cxx, diag::warn_auto_storage_class, diag::warn_cxx11_compat_user_defined_literal, diag::warn_cxx11_keyword, diag::warn_cxx11_right_shift_in_template_arg, diag::warn_explicit_instantiation_inline_0x, diag::warn_explicit_instantiation_must_be_global_0x, diag::warn_explicit_instantiation_out_of_scope_0x, diag::warn_explicit_instantiation_unqualified_wrong_namespace_0x, diag::warn_old_implicitly_unsigned_long_cxx, -1,
  /* DiagArray92 */ diag::warn_deprecated_string_literal_conversion, -1,
  /* DiagArray94 */ diag::warn_cxx11_compat_reserved_user_defined_literal, -1,
  /* DiagArray95 */ diag::ext_alias_declaration, diag::ext_array_size_conversion, diag::ext_auto_type_specifier, diag::ext_cxx11_enum_fixed_underlying_type, diag::ext_defaulted_deleted_function, diag::ext_enum_friend, diag::ext_enumerator_list_comma_cxx, diag::ext_explicit_conversion_functions, diag::ext_extern_template, diag::ext_for_range, diag::ext_generalized_initializer_lists, diag::ext_nested_name_spec_is_enum, diag::ext_nonclass_type_friend, diag::ext_nonstatic_member_init, diag::ext_override_control_keyword, diag::ext_ref_qualifier, diag::ext_rvalue_reference, diag::ext_scoped_enum, diag::ext_static_data_member_in_union, diag::ext_template_arg_object_internal, diag::ext_template_outside_of_template, diag::ext_template_parameter_default_in_function_template, diag::ext_typename_outside_of_template, diag::ext_unelaborated_friend_type, diag::ext_variadic_templates, diag::warn_ext_cxx11_attributes, -1,
  /* DiagArray96 */ diag::ext_extra_semi_cxx11, -1,
  /* DiagArray97 */ diag::ext_inline_namespace, -1,
  /* DiagArray98 */ diag::ext_cxx11_longlong, -1,
  /* DiagArray99 */ diag::ext_cce_narrowing, diag::ext_init_list_constant_narrowing, diag::ext_init_list_type_narrowing, diag::ext_init_list_variable_narrowing, diag::warn_init_list_constant_narrowing, diag::warn_init_list_type_narrowing, diag::warn_init_list_variable_narrowing, -1,
  /* DiagArray100 */ diag::ext_cxx14_attr, -1,
  /* DiagArray101 */ diag::ext_binary_literal_cxx14, -1,
  /* DiagArray104 */ diag::ext_constexpr_body_invalid_stmt, diag::ext_constexpr_body_multiple_return, diag::ext_constexpr_local_var, diag::ext_constexpr_type_definition, diag::ext_decltype_auto_type_specifier, diag::ext_init_capture, diag::ext_variable_template, -1,
  /* DiagArray105 */ diag::ext_cxx17_attr, -1,
  /* DiagArray107 */ diag::warn_cxx17_compat_exception_spec_in_signature, -1,
  /* DiagArray109 */ diag::ext_auto_new_list_init, diag::ext_constexpr_if, diag::ext_constexpr_on_lambda_cxx17, diag::ext_cxx_static_assert_no_message, diag::ext_decomp_decl, diag::ext_fold_expression, diag::ext_for_range_begin_end_types_differ, diag::ext_hex_literal_invalid, diag::ext_init_statement, diag::ext_inline_variable, diag::ext_multi_using_declaration, diag::ext_nested_namespace_definition, diag::ext_ns_enum_attribute, diag::ext_star_this_lambda_capture_cxx17, diag::ext_template_template_param_typename, diag::ext_using_attribute_ns, diag::ext_using_declaration_pack, -1,
  /* DiagArray114 */ diag::ext_cxx20_attr, -1,
  /* DiagArray115 */ diag::warn_cxx17_compat_implicit_typename, diag::warn_cxx20_compat_aggregate_init_with_ctors, diag::warn_cxx20_compat_consteval, diag::warn_cxx20_compat_constinit, diag::warn_cxx20_compat_explicit_bool, diag::warn_cxx20_compat_spaceship, diag::warn_cxx20_compat_use_of_unaddressable_function, diag::warn_cxx20_compat_utf8_string, diag::warn_cxx20_keyword, -1,
  /* DiagArray117 */ diag::ext_cxx_designated_init, -1,
  /* DiagArray118 */ diag::ext_adl_only_template_id, diag::ext_bitfield_member_init, diag::ext_capture_binding, diag::ext_constexpr_body_invalid_stmt_cxx20, diag::ext_constexpr_ctor_missing_init, diag::ext_constexpr_function_try_block_cxx20, diag::ext_constexpr_local_var_no_init, diag::ext_constexpr_union_ctor_no_init, diag::ext_decomp_decl_spec, diag::ext_defaulted_comparison, diag::ext_equals_this_lambda_capture_cxx20, diag::ext_explicit_bool, diag::ext_for_range_init_stmt, diag::ext_implicit_typename, diag::ext_init_capture_pack, diag::ext_inline_nested_namespace_definition, diag::ext_lambda_template_parameter_list, diag::ext_pointer_to_const_ref_member_on_rvalue, diag::ext_using_decl_scoped_enumerator, diag::ext_using_enum_declaration, diag::warn_cxx17_compat_aggregate_init_paren_list, -1,
  /* DiagArray119 */ diag::ext_defaulted_comparison_constexpr_mismatch, -1,
  /* DiagArray120 */ diag::err_static_lambda, diag::ext_alias_in_init_statement, diag::ext_consteval_if, diag::ext_constexpr_body_invalid_stmt_cxx23, diag::ext_constexpr_static_var, diag::ext_cxx23_pp_directive, diag::ext_cxx23_size_t_suffix, diag::ext_cxx_label_end_of_compound_statement, diag::ext_decl_attrs_on_lambda, diag::ext_lambda_missing_parens, diag::ext_operator_overload_static, -1,
  /* DiagArray132 */ diag::warn_cxx11_compat_binary_literal, -1,
  /* DiagArray134 */ diag::warn_cxx98_compat_alias_declaration, diag::warn_cxx98_compat_alignas, diag::warn_cxx98_compat_alignof, diag::warn_cxx98_compat_attribute, diag::warn_cxx98_compat_auto_type_specifier, diag::warn_cxx98_compat_constexpr, diag::warn_cxx98_compat_ctor_list_init, diag::warn_cxx98_compat_decltype, diag::warn_cxx98_compat_defaulted_deleted_function, diag::warn_cxx98_compat_delegating_ctor, diag::warn_cxx98_compat_empty_scalar_initializer, diag::warn_cxx98_compat_empty_sizeless_initializer, diag::warn_cxx98_compat_enum_fixed_underlying_type, diag::warn_cxx98_compat_enum_friend, diag::warn_cxx98_compat_enum_nested_name_spec, diag::warn_cxx98_compat_explicit_conversion_functions, diag::warn_cxx98_compat_for_range, diag::warn_cxx98_compat_friend_is_member, diag::warn_cxx98_compat_generalized_initializer_lists, diag::warn_cxx98_compat_goto_into_protected_scope, diag::warn_cxx98_compat_indirect_goto_in_protected_scope, diag::warn_cxx98_compat_initializer_list_init, diag::warn_cxx98_compat_inline_namespace, diag::warn_cxx98_compat_lambda, diag::warn_cxx98_compat_less_colon_colon, diag::warn_cxx98_compat_literal_operator, diag::warn_cxx98_compat_literal_ucn_control_character, diag::warn_cxx98_compat_literal_ucn_escape_basic_scs, diag::warn_cxx98_compat_noexcept_decl, diag::warn_cxx98_compat_noexcept_expr, diag::warn_cxx98_compat_non_static_member_use, diag::warn_cxx98_compat_nonclass_type_friend, diag::warn_cxx98_compat_nonstatic_member_init, diag::warn_cxx98_compat_nontrivial_union_or_anon_struct_member, diag::warn_cxx98_compat_nullptr, diag::warn_cxx98_compat_override_control_keyword, diag::warn_cxx98_compat_pass_non_pod_arg_to_vararg, diag::warn_cxx98_compat_raw_string_literal, diag::warn_cxx98_compat_ref_qualifier, diag::warn_cxx98_compat_reference_list_init, diag::warn_cxx98_compat_rvalue_reference, diag::warn_cxx98_compat_scoped_enum, diag::warn_cxx98_compat_sfinae_access_control, diag::warn_cxx98_compat_static_assert, diag::warn_cxx98_compat_static_data_member_in_union, diag::warn_cxx98_compat_switch_into_protected_scope, diag::warn_cxx98_compat_template_arg_extra_parens, diag::warn_cxx98_compat_template_arg_null, diag::warn_cxx98_compat_template_arg_object_internal, diag::warn_cxx98_compat_template_outside_of_template, diag::warn_cxx98_compat_template_parameter_default_in_function_template, diag::warn_cxx98_compat_trailing_return_type, diag::warn_cxx98_compat_two_right_angle_brackets, diag::warn_cxx98_compat_typename_outside_of_template, diag::warn_cxx98_compat_unelaborated_friend_type, diag::warn_cxx98_compat_unicode_literal, diag::warn_cxx98_compat_unicode_type, diag::warn_cxx98_compat_using_decl_constructor, diag::warn_cxx98_compat_variadic_templates, -1,
  /* DiagArray135 */ diag::warn_cxx98_compat_temp_copy, -1,
  /* DiagArray136 */ diag::warn_cxx98_compat_top_level_semi, -1,
  /* DiagArray137 */ diag::warn_cxx98_compat_template_arg_local_type, -1,
  /* DiagArray138 */ diag::warn_cxx98_compat_array_size_conversion, diag::warn_cxx98_compat_cast_fn_obj, diag::warn_cxx98_compat_empty_fnmacro_arg, diag::warn_cxx98_compat_enumerator_list_comma, diag::warn_cxx98_compat_extern_template, diag::warn_cxx98_compat_longlong, diag::warn_cxx98_compat_no_newline_eof, diag::warn_cxx98_compat_pp_line_too_big, diag::warn_cxx98_compat_variadic_macro, -1,
  /* DiagArray139 */ diag::warn_cxx98_compat_template_arg_unnamed_type, -1,
  /* DiagArray140 */ diag::ext_anonymous_union, diag::ext_c11_anonymous_struct, diag::ext_c11_feature, diag::ext_typecheck_compare_complete_incomplete_pointers, -1,
  /* DiagArray141 */ diag::warn_c2x_keyword, -1,
  /* DiagArray142 */ diag::ext_c2x_bitint_suffix, diag::ext_c2x_pp_directive, diag::ext_c_empty_initializer, diag::ext_c_label_end_of_compound_statement, diag::ext_c_nullptr, diag::ext_c_static_assert_no_message, diag::ext_parameter_name_omitted_c2x, diag::warn_ext_c2x_attributes, -1,
  /* DiagArray143 */ diag::warn_c99_compat_unicode_id, diag::warn_c99_compat_unicode_literal, diag::warn_c99_keyword, diag::warn_old_implicitly_unsigned_long, -1,
  /* DiagArray144 */ diag::ext_designated_init, diag::ext_designated_init_array, diag::ext_designated_init_brace_elision, diag::ext_designated_init_mixed, diag::ext_designated_init_nested, -1,
  /* DiagArray145 */ diag::ext_aggregate_init_not_constant, diag::ext_c99_array_usage, diag::ext_c99_compound_literal, diag::ext_c99_feature, diag::ext_c99_flexible_array_member, diag::ext_c99_variable_decl_in_for_loop, diag::ext_c99_whitespace_required_after_macro_name, diag::ext_empty_fnmacro_arg, diag::ext_enumerator_list_comma_c, diag::ext_hex_constant_invalid, -1,
  /* DiagArray146 */ diag::warn_call_to_pure_virtual_member_function_from_ctor_dtor, -1,
  /* DiagArray147 */ diag::warn_called_once_gets_called_twice, diag::warn_called_once_never_called, diag::warn_called_once_never_called_when, -1,
  /* DiagArray148 */ diag::warn_cast_align, -1,
  /* DiagArray149 */ diag::warn_cast_calling_conv, -1,
  /* DiagArray150 */ diag::warn_cast_function_type, -1,
  /* DiagArray151 */ diag::warn_cast_function_type_strict, -1,
  /* DiagArray152 */ diag::warn_cast_pointer_from_sel, -1,
  /* DiagArray153 */ diag::warn_cast_qual, diag::warn_cast_qual2, -1,
  /* DiagArray154 */ diag::ext_bad_cxx_cast_qualifiers_away_incoherent, -1,
  /* DiagArray156 */ diag::warn_omp_section_is_char, diag::warn_subscript_is_char, -1,
  /* DiagArray157 */ diag::warn_drv_yc_multiple_inputs_clang_cl, diag::warn_drv_ycyu_different_arg_clang_cl, diag::warn_pp_hdrstop_filename_ignored, diag::warn_pp_macro_def_mismatch_with_pch, -1,
  /* DiagArray158 */ diag::warn_conv_to_base_not_used, diag::warn_conv_to_self_not_used, diag::warn_conv_to_void_not_used, -1,
  /* DiagArray159 */ diag::warn_pass_class_arg_to_vararg, -1,
  /* DiagArray160 */ diag::warn_cmse_nonsecure_union, -1,
  /* DiagArray161 */ diag::warn_comma_operator, -1,
  /* DiagArray162 */ diag::escaped_newline_block_comment_end, diag::ext_line_comment, diag::ext_multi_line_line_comment, diag::warn_nested_block_comment, -1,
  /* DiagArray164 */ diag::ext_typecheck_comparison_of_distinct_pointers, -1,
  /* DiagArray165 */ diag::warn_completion_handler_called_twice, diag::warn_completion_handler_never_called, diag::warn_completion_handler_never_called_when, -1,
  /* DiagArray166 */ diag::ext_complex_component_init, -1,
  /* DiagArray168 */ diag::warn_compound_token_split_by_macro, -1,
  /* DiagArray169 */ diag::warn_compound_token_split_by_whitespace, -1,
  /* DiagArray170 */ diag::ext_typecheck_cond_pointer_integer_mismatch, -1,
  /* DiagArray171 */ diag::warn_maybe_uninit_var, -1,
  /* DiagArray172 */ diag::warn_module_config_macro_undef, -1,
  /* DiagArray173 */ diag::warn_impcast_integer_precision_constant, -1,
  /* DiagArray174 */ diag::warn_is_constant_evaluated_always_true_constexpr, -1,
  /* DiagArray175 */ diag::warn_logical_instead_of_bitwise, -1,
  /* DiagArray176 */ diag::warn_cxx14_compat_constexpr_not_const, -1,
  /* DiagArray177 */ diag::warn_attr_on_unconsumable_class, diag::warn_loop_state_mismatch, diag::warn_param_return_typestate_mismatch, diag::warn_param_typestate_mismatch, diag::warn_return_typestate_for_unconsumable_type, diag::warn_return_typestate_mismatch, diag::warn_use_in_invalid_state, diag::warn_use_of_temp_in_invalid_state, -1,
  /* DiagArray178 */ diag::warn_impcast_complex_scalar, diag::warn_impcast_vector_scalar, diag::warn_opencl_generic_address_space_arg, diag::warn_template_arg_negative, diag::warn_template_arg_too_large, -1,
  /* DiagArray180 */ diag::warn_non_aligned_allocation_function, -1,
  /* DiagArray181 */ diag::warn_coroutine_handle_address_invalid_return_type, -1,
  /* DiagArray182 */ diag::warn_coroutine_promise_unhandled_exception_required_with_exceptions, -1,
  /* DiagArray183 */ diag::warn_unreachable_default, -1,
  /* DiagArray185 */ diag::warn_objc_cdirective_format_string, -1,
  /* DiagArray186 */ diag::warn_ctad_maybe_unsupported, -1,
  /* DiagArray188 */ diag::warn_ctu_incompat_triple, -1,
  /* DiagArray189 */ diag::warn_attribute_argument_n_negative, diag::warn_cuda_attr_lambda_position, diag::warn_kern_is_inline, diag::warn_kern_is_method, diag::warn_pragma_unroll_cuda_value_in_parens, -1,
  /* DiagArray190 */ diag::warn_default_atomic_custom_getter_setter, -1,
  /* DiagArray191 */ diag::ext_cxx11_attr_placement, -1,
  /* DiagArray192 */ diag::warn_dangling_variable, diag::warn_unsupported_lifetime_extension, -1,
  /* DiagArray193 */ diag::warn_dangling_else, -1,
  /* DiagArray194 */ diag::warn_bind_ref_member_to_parameter, diag::warn_dangling_member, diag::warn_init_ptr_member_to_parameter_addr, diag::warn_new_dangling_reference, -1,
  /* DiagArray195 */ diag::warn_dangling_lifetime_pointer, diag::warn_dangling_lifetime_pointer_member, -1,
  /* DiagArray196 */ diag::warn_new_dangling_initializer_list, -1,
  /* DiagArray197 */ diag::warn_drv_darwin_sdk_invalid_settings, -1,
  /* DiagArray198 */ diag::warn_pp_date_time, -1,
  /* DiagArray199 */ diag::warn_dealloc_in_category, -1,
  /* DiagArray200 */ diag::warn_debug_compression_unavailable, -1,
  /* DiagArray201 */ diag::ext_mixed_decls_code, diag::warn_mixed_decls_code, -1,
  /* DiagArray202 */ diag::warn_defaulted_comparison_deleted, diag::warn_defaulted_method_deleted, -1,
  /* DiagArray203 */ diag::warn_delegating_ctor_cycle, -1,
  /* DiagArray204 */ diag::warn_delete_abstract_non_virtual_dtor, -1,
  /* DiagArray205 */ diag::ext_delete_void_ptr_operand, diag::warn_delete_incomplete, -1,
  /* DiagArray206 */ diag::warn_delete_non_virtual_dtor, -1,
  /* DiagArray208 */ diag::ext_delimited_escape_sequence, -1,
  /* DiagArray209 */ diag::warn_deprecated_lax_vec_conv_all, -1,
  /* DiagArray210 */ diag::warn_O4_is_O3, diag::warn_access_decl_deprecated, diag::warn_drv_deprecated_arg, diag::warn_drv_treating_input_as_cxx, diag::warn_omp_depend_in_ordered_deprecated, diag::warn_omp_minus_in_reduction_deprecated, diag::warn_option_invalid_ocl_version, diag::warn_vector_long_decl_spec_combination, -1,
  /* DiagArray211 */ diag::warn_deprecated_altivec_src_compat, -1,
  /* DiagArray212 */ diag::warn_arith_conv_mixed_anon_enum_types_cxx20, -1,
  /* DiagArray213 */ diag::warn_depr_array_comparison, -1,
  /* DiagArray214 */ diag::warn_deprecated_noreturn_spelling, diag::warn_type_attribute_deprecated_on_decl, diag::warn_vector_mode_deprecated, -1,
  /* DiagArray215 */ diag::warn_deprecated_builtin, -1,
  /* DiagArray216 */ diag::warn_deprecated_comma_subscript, -1,
  /* DiagArray217 */ diag::warn_deprecated_copy, -1,
  /* DiagArray219 */ diag::warn_deprecated_copy_with_dtor, -1,
  /* DiagArray220 */ diag::warn_deprecated_copy_with_user_provided_copy, -1,
  /* DiagArray221 */ diag::warn_deprecated_copy_with_user_provided_dtor, -1,
  /* DiagArray222 */ diag::warn_deprecated_for_co_await, -1,
  /* DiagArray223 */ diag::warn_atl_uuid_deprecated, diag::warn_cstyle_param, diag::warn_deprecated, diag::warn_deprecated_fwdclass_message, diag::warn_deprecated_message, diag::warn_property_method_deprecated, -1,
  /* DiagArray224 */ diag::warn_exception_spec_deprecated, -1,
  /* DiagArray225 */ diag::warn_comparison_mixed_enum_types_cxx20, -1,
  /* DiagArray226 */ diag::warn_conditional_mixed_enum_types_cxx20, -1,
  /* DiagArray227 */ diag::warn_arith_conv_mixed_enum_types_cxx20, -1,
  /* DiagArray228 */ diag::warn_arith_conv_enum_float_cxx20, -1,
  /* DiagArray229 */ diag::warn_deprecated_def, diag::warn_unavailable_def, -1,
  /* DiagArray230 */ diag::warn_increment_bool, -1,
  /* DiagArray231 */ diag::warn_deprecated_literal_operator_id, -1,
  /* DiagArray232 */ diag::warn_non_prototype_changes_behavior, diag::warn_strict_uses_without_prototype, -1,
  /* DiagArray233 */ diag::warn_objc_isa_assign, diag::warn_objc_isa_use, -1,
  /* DiagArray234 */ diag::warn_objc_pointer_masking, -1,
  /* DiagArray235 */ diag::warn_objc_pointer_masking_performSelector, -1,
  /* DiagArray236 */ diag::warn_pragma_deprecated_macro_use, -1,
  /* DiagArray237 */ diag::warn_deprecated_redundant_constexpr_static_def, -1,
  /* DiagArray238 */ diag::warn_deprecated_register, -1,
  /* DiagArray239 */ diag::warn_analyzer_deprecated_option, diag::warn_analyzer_deprecated_option_with_alternative, -1,
  /* DiagArray240 */ diag::warn_deprecated_this_capture, -1,
  /* DiagArray241 */ diag::warn_ext_int_deprecated, -1,
  /* DiagArray242 */ diag::warn_deprecated_increment_decrement_volatile, diag::warn_deprecated_simple_assign_volatile, diag::warn_deprecated_volatile_param, diag::warn_deprecated_volatile_return, diag::warn_deprecated_volatile_structured_binding, -1,
  /* DiagArray244 */ diag::warn_direct_ivar_access, -1,
  /* DiagArray245 */ diag::pp_disabled_macro_expansion, -1,
  /* DiagArray248 */ diag::warn_conflicting_param_modifiers, diag::warn_conflicting_ret_type_modifiers, -1,
  /* DiagArray250 */ diag::warn_remainder_division_by_zero, -1,
  /* DiagArray251 */ diag::warn_attribute_dll_redeclaration, -1,
  /* DiagArray252 */ diag::warn_attribute_dllexport_explicit_instantiation_decl, -1,
  /* DiagArray253 */ diag::warn_attribute_dllimport_static_field_definition, -1,
  /* DiagArray254 */ diag::warn_doc_api_container_decl_mismatch, diag::warn_doc_block_command_duplicate, diag::warn_doc_block_command_empty_paragraph, diag::warn_doc_container_decl_mismatch, diag::warn_doc_function_method_decl_mismatch, diag::warn_doc_html_start_tag_expected_ident_or_greater, diag::warn_doc_html_start_tag_expected_quoted_string, diag::warn_doc_inline_command_not_enough_arguments, diag::warn_doc_param_duplicate, diag::warn_doc_param_invalid_direction, diag::warn_doc_param_not_attached_to_a_function_decl, diag::warn_doc_param_not_found, diag::warn_doc_returns_attached_to_a_void_function, diag::warn_doc_returns_not_attached_to_a_function_decl, diag::warn_doc_tparam_duplicate, diag::warn_doc_tparam_not_attached_to_a_template_decl, diag::warn_doc_tparam_not_found, diag::warn_not_a_doxygen_trailing_member_comment, diag::warn_splice_in_doxygen_comment, diag::warn_verbatim_block_end_without_start, -1,
  /* DiagArray255 */ diag::warn_doc_deprecated_not_sync, -1,
  /* DiagArray256 */ diag::warn_doc_html_end_forbidden, diag::warn_doc_html_end_unbalanced, diag::warn_doc_html_missing_end_tag, diag::warn_doc_html_start_end_mismatch, -1,
  /* DiagArray257 */ diag::warn_doc_param_spaces_in_direction, -1,
  /* DiagArray258 */ diag::warn_correct_comment_command_name, diag::warn_unknown_comment_command_name, -1,
  /* DiagArray259 */ diag::ext_dollar_in_identifier, -1,
  /* DiagArray260 */ diag::warn_impcast_double_promotion, -1,
  /* DiagArray261 */ diag::ext_dtor_name_ambiguous, diag::ext_dtor_named_in_wrong_scope, diag::ext_qualified_dtor_named_in_lexical_scope, -1,
  /* DiagArray262 */ diag::ext_destructor_typedef_name, -1,
  /* DiagArray263 */ diag::ext_duplicate_declspec, diag::ext_warn_duplicate_declspec, diag::warn_attribute_address_multiple_identical_qualifiers, diag::warn_duplicate_declspec, -1,
  /* DiagArray264 */ diag::warn_duplicate_enum_values, -1,
  /* DiagArray265 */ diag::warn_method_param_declaration, -1,
  /* DiagArray266 */ diag::warn_duplicate_method_decl, -1,
  /* DiagArray267 */ diag::warn_duplicate_protocol_def, -1,
  /* DiagArray268 */ diag::warn_drv_dxc_missing_dxv, -1,
  /* DiagArray269 */ diag::warn_dyn_class_memaccess, -1,
  /* DiagArray270 */ diag::ext_dynamic_exception_spec, -1,
  /* DiagArray271 */ diag::warn_eagerly_load_for_standard_cplusplus_modules, -1,
  /* DiagArray273 */ diag::ext_enum_base_in_type_specifier, -1,
  /* DiagArray274 */ diag::ext_elaborated_enum_class, -1,
  /* DiagArray275 */ diag::ext_embedded_directive, -1,
  /* DiagArray276 */ diag::warn_empty_for_body, diag::warn_empty_if_body, diag::warn_empty_range_based_for_body, diag::warn_empty_switch_body, diag::warn_empty_while_body, -1,
  /* DiagArray277 */ diag::ext_decomp_decl_empty, -1,
  /* DiagArray278 */ diag::warn_empty_init_statement, -1,
  /* DiagArray279 */ diag::ext_empty_translation_unit, -1,
  /* DiagArray280 */ diag::warn_incomplete_encoded_type, -1,
  /* DiagArray282 */ diag::warn_comparison_mixed_enum_types, -1,
  /* DiagArray283 */ diag::warn_conditional_mixed_enum_types, -1,
  /* DiagArray284 */ diag::warn_comparison_of_mixed_enum_types_switch, -1,
  /* DiagArray285 */ diag::warn_constexpr_unscoped_enum_out_of_range, -1,
  /* DiagArray286 */ diag::warn_impcast_different_enum_types, -1,
  /* DiagArray287 */ diag::warn_arith_conv_mixed_enum_types, -1,
  /* DiagArray288 */ diag::warn_arith_conv_enum_float, -1,
  /* DiagArray289 */ diag::ext_enum_too_large, diag::ext_enumerator_increment_too_large, -1,
  /* DiagArray290 */ diag::warn_cdtor_function_try_handler_mem_expr, diag::warn_exception_caught_by_earlier_handler, diag::warn_throw_in_noexcept_func, -1,
  /* DiagArray291 */ diag::ext_excess_initializers, diag::ext_excess_initializers_for_sizeless_type, diag::ext_excess_initializers_in_char_array_initializer, diag::ext_initializer_string_for_char_array_too_long, -1,
  /* DiagArray292 */ diag::warn_exit_time_destructor, -1,
  /* DiagArray293 */ diag::warn_defined_in_function_type_macro, diag::warn_defined_in_object_type_macro, -1,
  /* DiagArray294 */ diag::warn_experimental_header_unit, -1,
  /* DiagArray295 */ diag::warn_direct_initialize_call, diag::warn_direct_super_initialize_call, -1,
  /* DiagArray296 */ diag::warn_arc_strong_pointer_objc_pointer, -1,
  /* DiagArray298 */ diag::warn_zero_size_struct_union_in_extern_c, -1,
  /* DiagArray299 */ diag::warn_extern_init, -1,
  /* DiagArray300 */ diag::warn_arm_interrupt_calling_convention, -1,
  /* DiagArray301 */ diag::warn_namespace_member_extra_qualification, -1,
  /* DiagArray302 */ diag::ext_extra_semi, diag::warn_extra_semi_after_mem_fn_def, -1,
  /* DiagArray303 */ diag::warn_null_statement, -1,
  /* DiagArray304 */ diag::ext_pp_extra_tokens_at_eol, diag::warn_omp_extra_tokens_at_eol, -1,
  /* DiagArray305 */ diag::warn_final_dtor_non_final_class, -1,
  /* DiagArray306 */ diag::warn_pragma_final_macro, -1,
  /* DiagArray307 */ diag::ext_clang_c_enum_fixed_underlying_type, -1,
  /* DiagArray308 */ diag::warn_fixedpoint_constant_overflow, -1,
  /* DiagArray309 */ diag::warn_flag_enum_constant_out_of_range, -1,
  /* DiagArray310 */ diag::ext_flexible_array_in_array, diag::ext_flexible_array_in_struct, -1,
  /* DiagArray311 */ diag::warn_impcast_float_integer, -1,
  /* DiagArray312 */ diag::warn_floatingpoint_eq, -1,
  /* DiagArray313 */ diag::warn_impcast_float_to_integer, diag::warn_impcast_float_to_integer_out_of_range, -1,
  /* DiagArray314 */ diag::warn_impcast_float_to_integer_zero, -1,
  /* DiagArray315 */ diag::warn_redundant_loop_iteration, diag::warn_variables_not_in_loop_body, -1,
  /* DiagArray316 */ diag::warn_format_P_no_precision, diag::warn_format_argument_needs_cast, diag::warn_format_bool_as_character, diag::warn_format_conversion_argument_type_mismatch, diag::warn_format_invalid_annotation, diag::warn_format_invalid_positional_specifier, diag::warn_format_mix_positional_nonpositional_args, diag::warn_format_nonsensical_length, diag::warn_format_string_is_wide_literal, diag::warn_format_zero_positional_specifier, diag::warn_missing_format_string, diag::warn_printf_ObjCflags_without_ObjCConversion, diag::warn_printf_asterisk_missing_arg, diag::warn_printf_asterisk_wrong_type, diag::warn_printf_empty_objc_flag, diag::warn_printf_format_string_contains_null_char, diag::warn_printf_format_string_not_null_terminated, diag::warn_printf_ignored_flag, diag::warn_printf_incomplete_specifier, diag::warn_printf_invalid_objc_flag, diag::warn_printf_narg_not_supported, diag::warn_printf_nonsensical_flag, diag::warn_printf_nonsensical_optional_amount, diag::warn_printf_positional_arg_exceeds_data_args, diag::warn_scanf_nonzero_width, diag::warn_scanf_scanlist_incomplete, -1,
  /* DiagArray317 */ diag::warn_printf_data_arg_not_used, -1,
  /* DiagArray318 */ diag::warn_printf_insufficient_data_args, -1,
  /* DiagArray319 */ diag::warn_format_invalid_conversion, -1,
  /* DiagArray320 */ diag::warn_format_non_standard, diag::warn_format_non_standard_conversion_spec, diag::warn_format_non_standard_positional_arg, -1,
  /* DiagArray321 */ diag::warn_format_nonliteral, -1,
  /* DiagArray322 */ diag::warn_format_argument_needs_cast_pedantic, diag::warn_format_conversion_argument_type_mismatch_pedantic, -1,
  /* DiagArray323 */ diag::warn_format_nonliteral_noargs, -1,
  /* DiagArray324 */ diag::warn_format_conversion_argument_type_mismatch_confusion, -1,
  /* DiagArray326 */ diag::warn_empty_format_string, -1,
  /* DiagArray328 */ diag::warn_fortify_scanf_overflow, diag::warn_fortify_source_format_overflow, diag::warn_fortify_source_overflow, diag::warn_fortify_source_size_mismatch, diag::warn_fortify_strlen_overflow, -1,
  /* DiagArray329 */ diag::warn_four_char_character_literal, -1,
  /* DiagArray330 */ diag::warn_frame_address, -1,
  /* DiagArray331 */ diag::warn_fe_backend_frame_larger_than, diag::warn_fe_frame_larger_than, -1,
  /* DiagArray333 */ diag::warn_framework_include_private_from_public, -1,
  /* DiagArray334 */ diag::warn_free_nonheap_object, -1,
  /* DiagArray335 */ diag::warn_function_def_in_objc_container, -1,
  /* DiagArray336 */ diag::warn_dispatch_body_ignored, diag::warn_multiversion_duplicate_entries, diag::warn_target_clone_duplicate_options, diag::warn_target_clone_no_impact_options, -1,
  /* DiagArray337 */ diag::warn_drv_fuse_ld_path, -1,
  /* DiagArray340 */ diag::ext_clang_diagnose_if, diag::ext_clang_enable_if, diag::ext_warn_gnu_final, diag::warn_attribute_on_function_definition, diag::warn_break_binds_to_switch, diag::warn_cleanup_ext, diag::warn_gcc_attribute_location, diag::warn_gcc_ignores_type_attr, diag::warn_gcc_requires_variadic_function, diag::warn_gcc_variable_decl_in_for_loop, diag::warn_loop_ctrl_binds_to_inner, -1,
  /* DiagArray341 */ diag::ext_generic_with_type_arg, -1,
  /* DiagArray342 */ diag::warn_global_constructor, diag::warn_global_destructor, -1,
  /* DiagArray343 */ diag::warn_drv_global_isel_incomplete, diag::warn_drv_global_isel_incomplete_opt, -1,
  /* DiagArray345 */ diag::ext_alignof_expr, -1,
  /* DiagArray346 */ diag::ext_gnu_anonymous_struct, -1,
  /* DiagArray347 */ diag::ext_array_init_parens, -1,
  /* DiagArray348 */ diag::ext_auto_type, -1,
  /* DiagArray349 */ diag::ext_binary_literal, -1,
  /* DiagArray350 */ diag::ext_gnu_case_range, -1,
  /* DiagArray351 */ diag::ext_integer_complex, -1,
  /* DiagArray352 */ diag::ext_array_init_copy, -1,
  /* DiagArray353 */ diag::ext_gnu_conditional_expr, -1,
  /* DiagArray354 */ diag::ext_gnu_array_range, diag::ext_gnu_missing_equal_designator, diag::ext_gnu_old_style_field_designator, -1,
  /* DiagArray356 */ diag::ext_empty_struct_union, diag::ext_flexible_array_empty_aggregate_gnu, diag::ext_no_named_members_in_struct_union, -1,
  /* DiagArray357 */ diag::ext_flexible_array_init, -1,
  /* DiagArray358 */ diag::ext_flexible_array_union_gnu, -1,
  /* DiagArray359 */ diag::ext_expr_not_ice, diag::ext_in_class_initializer_non_constant, diag::ext_vla_folded_to_constant, -1,
  /* DiagArray360 */ diag::ext_imaginary_constant, -1,
  /* DiagArray361 */ diag::ext_pp_include_next_directive, -1,
  /* DiagArray362 */ diag::warn_gnu_inline_cplusplus_without_extern, -1,
  /* DiagArray363 */ diag::ext_gnu_address_of_label, diag::ext_gnu_indirect_goto, -1,
  /* DiagArray364 */ diag::ext_pp_gnu_line_directive, -1,
  /* DiagArray365 */ diag::warn_gnu_null_ptr_arith, -1,
  /* DiagArray366 */ diag::ext_type_defined_in_offsetof, -1,
  /* DiagArray367 */ diag::ext_gnu_ptr_func_arith, diag::ext_gnu_subscript_void_type, diag::ext_gnu_void_ptr, -1,
  /* DiagArray368 */ diag::ext_forward_ref_enum_def, -1,
  /* DiagArray369 */ diag::ext_gnu_statement_expr, -1,
  /* DiagArray370 */ diag::ext_gnu_statement_expr_macro, -1,
  /* DiagArray371 */ diag::ext_in_class_initializer_float_type, -1,
  /* DiagArray372 */ diag::ext_string_literal_operator_template, -1,
  /* DiagArray373 */ diag::ext_typecheck_cast_to_union, -1,
  /* DiagArray374 */ diag::ext_variable_sized_type_in_struct, -1,
  /* DiagArray375 */ diag::ext_pp_line_zero, -1,
  /* DiagArray376 */ diag::ext_missing_varargs_arg, diag::ext_paste_comma, -1,
  /* DiagArray377 */ diag::warn_maybe_capture_bad_target_this_ptr, -1,
  /* DiagArray378 */ diag::warn_header_guard, -1,
  /* DiagArray379 */ diag::warn_using_directive_in_header, -1,
  /* DiagArray380 */ diag::warn_hip_omp_target_directives, -1,
  /* DiagArray381 */ diag::warn_ignored_hip_only_option, -1,
  /* DiagArray382 */ diag::ext_hlsl_access_specifiers, -1,
  /* DiagArray383 */ diag::warn_condition_is_idiomatic_assignment, -1,
  /* DiagArray384 */ diag::ext_cannot_use_trivial_abi, diag::warn_alias_to_weak_alias, diag::warn_alias_with_section, diag::warn_aligned_attr_underaligned, diag::warn_attr_abi_tag_namespace, diag::warn_attribute_after_definition_ignored, diag::warn_attribute_cmse_entry_static, diag::warn_attribute_dllexport_explicit_instantiation_def, diag::warn_attribute_has_no_effect_on_compile_time_if, diag::warn_attribute_has_no_effect_on_infinite_loop, diag::warn_attribute_iboutlet, diag::warn_attribute_ignored, diag::warn_attribute_ignored_for_field_of_type, diag::warn_attribute_ignored_no_calls_in_stmt, diag::warn_attribute_ignored_non_function_pointer, diag::warn_attribute_ignored_on_inline, diag::warn_attribute_ignored_on_non_definition, diag::warn_attribute_invalid_on_definition, diag::warn_attribute_no_decl, diag::warn_attribute_nonnull_no_pointers, diag::warn_attribute_nonnull_parm_no_args, diag::warn_attribute_not_on_decl, diag::warn_attribute_pointer_or_reference_only, diag::warn_attribute_pointers_only, diag::warn_attribute_precede_definition, diag::warn_attribute_return_pointers_only, diag::warn_attribute_return_pointers_refs_only, diag::warn_attribute_sentinel_named_arguments, diag::warn_attribute_sentinel_not_variadic, diag::warn_attribute_type_not_supported, diag::warn_attribute_type_not_supported_global, diag::warn_attribute_unknown_visibility, diag::warn_attribute_void_function_method, diag::warn_attribute_weak_on_field, diag::warn_attribute_weak_on_local, diag::warn_attribute_wrong_decl_type, diag::warn_attribute_wrong_decl_type_str, diag::warn_attributes_likelihood_ifstmt_conflict, diag::warn_block_literal_attributes_on_omitted_return_type, diag::warn_cconv_unsupported, diag::warn_cxx11_gnu_attribute_on_type, diag::warn_declspec_allocator_nonpointer, diag::warn_declspec_attribute_ignored, diag::warn_deprecated_anonymous_namespace, diag::warn_deprecated_ignored_on_using, diag::warn_dllimport_dropped_from_inline_function, diag::warn_duplicate_attribute, diag::warn_duplicate_attribute_exact, diag::warn_function_attribute_ignored_in_stmt, diag::warn_function_stmt_attribute_precedence, diag::warn_gc_attribute_weak_on_local, diag::warn_gnu_inline_attribute_requires_inline, diag::warn_ignored_ms_inheritance, diag::warn_ignored_objc_externally_retained, diag::warn_import_on_definition, diag::warn_internal_linkage_local_storage, diag::warn_interrupt_attribute_invalid, diag::warn_microsoft_qualifiers_ignored, diag::warn_mig_server_routine_does_not_return_kern_return_t, diag::warn_mismatched_import, diag::warn_mmap_unknown_attribute, diag::warn_nocf_check_attribute_ignored, diag::warn_noderef_on_non_pointer_or_array, diag::warn_nothrow_attribute_ignored, diag::warn_ns_attribute_wrong_parameter_type, diag::warn_ns_attribute_wrong_return_type, diag::warn_objc_direct_ignored, diag::warn_objc_direct_property_ignored, diag::warn_opencl_attr_deprecated_ignored, diag::warn_require_const_init_added_too_late, diag::warn_riscv_repeated_interrupt_attribute, diag::warn_sycl_kernel_invalid_template_param_type, diag::warn_sycl_kernel_num_of_function_params, diag::warn_sycl_kernel_num_of_template_params, diag::warn_sycl_kernel_return_type, diag::warn_transparent_union_attribute_field_size_align, diag::warn_transparent_union_attribute_floating, diag::warn_transparent_union_attribute_not_definition, diag::warn_transparent_union_attribute_zero_fields, diag::warn_type_attribute_wrong_type, diag::warn_unhandled_ms_attribute_ignored, diag::warn_unsupported_target_attribute, diag::warn_unused_result_typedef_unsupported_spelling, diag::warn_wrong_clang_attr_namespace, -1,
  /* DiagArray385 */ diag::warn_missing_sdksettings_for_availability_checking, -1,
  /* DiagArray386 */ diag::warn_drv_unsupported_opt_for_target, diag::warn_ignored_gcc_optimization, -1,
  /* DiagArray387 */ diag::warn_pragma_intrinsic_builtin, -1,
  /* DiagArray389 */ diag::warn_clause_expected_string, diag::warn_pragma_align_expected_equal, diag::warn_pragma_align_invalid_option, diag::warn_pragma_comment_ignored, diag::warn_pragma_debug_dependent_argument, diag::warn_pragma_debug_missing_argument, diag::warn_pragma_debug_missing_command, diag::warn_pragma_debug_unexpected_argument, diag::warn_pragma_debug_unexpected_command, diag::warn_pragma_debug_unknown_module, diag::warn_pragma_expected_action_or_r_paren, diag::warn_pragma_expected_colon, diag::warn_pragma_expected_colon_r_paren, diag::warn_pragma_expected_comma, diag::warn_pragma_expected_identifier, diag::warn_pragma_expected_init_seg, diag::warn_pragma_expected_integer, diag::warn_pragma_expected_lparen, diag::warn_pragma_expected_non_wide_string, diag::warn_pragma_expected_predicate, diag::warn_pragma_expected_punc, diag::warn_pragma_expected_rparen, diag::warn_pragma_expected_section_label_or_name, diag::warn_pragma_expected_section_name, diag::warn_pragma_expected_section_push_pop_or_name, diag::warn_pragma_expected_string, diag::warn_pragma_extra_tokens_at_eol, diag::warn_pragma_force_cuda_host_device_bad_arg, diag::warn_pragma_fp_ignored, diag::warn_pragma_init_seg_unsupported_target, diag::warn_pragma_invalid_action, diag::warn_pragma_invalid_argument, diag::warn_pragma_invalid_specific_action, diag::warn_pragma_missing_argument, diag::warn_pragma_ms_fenv_access, diag::warn_pragma_ms_struct, diag::warn_pragma_options_align_reset_failed, diag::warn_pragma_options_expected_align, diag::warn_pragma_pack_invalid_alignment, diag::warn_pragma_pack_malformed, diag::warn_pragma_pop_failed, diag::warn_pragma_pop_macro_no_push, diag::warn_pragma_unknown_extension, diag::warn_pragma_unsupported_action, diag::warn_pragma_unsupported_extension, diag::warn_pragma_unused_expected_var, diag::warn_pragma_unused_expected_var_arg, diag::warn_pragma_unused_undeclared_var, diag::warn_stdc_unknown_rounding_mode, -1,
  /* DiagArray390 */ diag::warn_arc_lifetime_result_type, diag::warn_block_literal_qualifiers_on_omitted_return_type, diag::warn_qual_return_type, diag::warn_typecheck_function_qualifiers_ignored, -1,
  /* DiagArray391 */ diag::warn_typecheck_reference_qualifiers, -1,
  /* DiagArray393 */ diag::warn_auto_implicit_atomic_property, diag::warn_implicit_atomic_property, -1,
  /* DiagArray394 */ diag::warn_impcast_integer_float_precision_constant, -1,
  /* DiagArray395 */ diag::warn_impcast_floating_point_to_bool, -1,
  /* DiagArray396 */ diag::ext_implicit_exception_spec_mismatch, -1,
  /* DiagArray397 */ diag::warn_unannotated_fallthrough, -1,
  /* DiagArray398 */ diag::warn_unannotated_fallthrough_per_function, -1,
  /* DiagArray399 */ diag::warn_impcast_fixed_point_range, -1,
  /* DiagArray400 */ diag::warn_impcast_float_precision, diag::warn_impcast_float_result_precision, -1,
  /* DiagArray401 */ diag::ext_implicit_function_decl_c99, diag::ext_implicit_lib_function_decl, diag::ext_implicit_lib_function_decl_c99, diag::warn_builtin_unknown, diag::warn_implicit_function_decl, -1,
  /* DiagArray402 */ diag::ext_missing_type_specifier, diag::ext_param_not_declared, diag::warn_missing_type_specifier, -1,
  /* DiagArray403 */ diag::warn_impcast_high_order_zero_bits, diag::warn_impcast_integer_precision, -1,
  /* DiagArray404 */ diag::warn_impcast_integer_float_precision, -1,
  /* DiagArray405 */ diag::warn_implicitly_retains_self, -1,
  /* DiagArray406 */ diag::ext_integer_literal_too_large_for_signed, -1,
  /* DiagArray408 */ diag::ext_pp_import_directive, -1,
  /* DiagArray409 */ diag::warn_inaccessible_base_class, -1,
  /* DiagArray410 */ diag::pp_include_next_absolute_path, -1,
  /* DiagArray411 */ diag::pp_include_next_in_primary, -1,
  /* DiagArray412 */ diag::warn_deep_exception_specs_differ, diag::warn_incompatible_exception_specs, -1,
  /* DiagArray413 */ diag::ext_typecheck_convert_incompatible_function_pointer, -1,
  /* DiagArray414 */ diag::warn_typecheck_convert_incompatible_function_pointer_strict, -1,
  /* DiagArray415 */ diag::warn_redecl_library_builtin, -1,
  /* DiagArray416 */ diag::warn_cxx_ms_struct, diag::warn_npot_ms_struct, -1,
  /* DiagArray417 */ diag::ext_typecheck_convert_incompatible_pointer, -1,
  /* DiagArray418 */ diag::ext_nested_pointer_qualifier_mismatch, diag::ext_typecheck_convert_discards_qualifiers, diag::warn_bad_cxx_cast_nested_pointer_addr_space, -1,
  /* DiagArray419 */ diag::warn_property_types_are_incompatible, -1,
  /* DiagArray420 */ diag::warn_incompatible_sysroot, -1,
  /* DiagArray421 */ diag::warn_mmap_incomplete_framework_module_declaration, -1,
  /* DiagArray422 */ diag::warn_undef_method_impl, -1,
  /* DiagArray424 */ diag::warn_implicit_decl_no_jmp_buf, -1,
  /* DiagArray425 */ diag::warn_missing_submodule, diag::warn_mmap_umbrella_dir_not_found, diag::warn_uncovered_module_header, -1,
  /* DiagArray426 */ diag::warn_redeclaration_without_attribute_prev_attribute_ignored, diag::warn_redeclaration_without_import_attribute, -1,
  /* DiagArray427 */ diag::warn_inconsistent_destructor_marked_not_override_overriding, -1,
  /* DiagArray428 */ diag::warn_inconsistent_function_marked_not_override_overriding, -1,
  /* DiagArray429 */ diag::ext_increment_bool, -1,
  /* DiagArray430 */ diag::warn_infinite_recursive_function, -1,
  /* DiagArray432 */ diag::ext_initializer_overrides, diag::ext_initializer_union_overrides, diag::warn_initializer_overrides, -1,
  /* DiagArray433 */ diag::ext_out_of_line_qualified_id_type_names_constructor, -1,
  /* DiagArray435 */ diag::warn_fe_inline_asm, -1,
  /* DiagArray436 */ diag::warn_inline_namespace_reopened_noninline, -1,
  /* DiagArray437 */ diag::ext_operator_new_delete_declared_inline, -1,
  /* DiagArray438 */ diag::warn_explicit_instantiation_after_specialization, -1,
  /* DiagArray439 */ diag::ext_typecheck_convert_int_pointer, diag::ext_typecheck_convert_pointer_int, -1,
  /* DiagArray441 */ diag::warn_enum_constant_in_bool_context, diag::warn_left_shift_in_bool_context, -1,
  /* DiagArray442 */ diag::warn_int_to_pointer_cast, -1,
  /* DiagArray443 */ diag::warn_int_to_void_pointer_cast, -1,
  /* DiagArray444 */ diag::warn_integer_constant_overflow, -1,
  /* DiagArray445 */ diag::warn_anyx86_interrupt_regsave, -1,
  /* DiagArray446 */ diag::warn_drv_missing_plugin_arg, diag::warn_drv_missing_plugin_name, diag::warn_drv_msp430_hwmult_mismatch, diag::warn_drv_msp430_hwmult_no_device, diag::warn_drv_msp430_hwmult_unsupported, diag::warn_drv_object_size_disabled_O0, diag::warn_drv_optimization_value, diag::warn_fe_backend_invalid_feature_flag, diag::warn_fe_backend_readonly_feature_flag, diag::warn_target_unrecognized_env, diag::warn_target_unsupported_extension, -1,
  /* DiagArray447 */ diag::ext_constexpr_function_never_constant_expr, -1,
  /* DiagArray448 */ diag::warn_iboutlet_object_type, diag::warn_iboutletcollection_property_assign, -1,
  /* DiagArray449 */ diag::warn_invalid_initializer_from_system_header, -1,
  /* DiagArray450 */ diag::warn_invalid_ios_deployment_target, -1,
  /* DiagArray451 */ diag::warn_attribute_no_builtin_invalid_builtin_name, -1,
  /* DiagArray452 */ diag::warn_falloff_noreturn_function, diag::warn_noreturn_function_has_return_expr, -1,
  /* DiagArray453 */ diag::ext_offsetof_non_pod_type, diag::ext_offsetof_non_standardlayout_type, -1,
  /* DiagArray454 */ diag::warn_drv_unable_to_find_directory_expected, -1,
  /* DiagArray455 */ diag::ext_partial_spec_not_more_specialized_than_primary, -1,
  /* DiagArray457 */ diag::ext_empty_character, diag::ext_unterminated_char_or_string, -1,
  /* DiagArray458 */ diag::warn_bad_character_encoding, diag::warn_bad_string_encoding, -1,
  /* DiagArray459 */ diag::warn_static_assert_message_constexpr, -1,
  /* DiagArray460 */ diag::ext_pp_bad_paste_ms, -1,
  /* DiagArray461 */ diag::warn_unevaluated_string_prefix, -1,
  /* DiagArray462 */ diag::warn_invalid_utf8_in_comment, -1,
  /* DiagArray463 */ diag::warn_jump_out_of_seh_finally, -1,
  /* DiagArray464 */ diag::ext_keyword_as_ident, -1,
  /* DiagArray465 */ diag::warn_pp_macro_hides_keyword, -1,
  /* DiagArray466 */ diag::ext_param_promoted_not_compatible_with_prototype, -1,
  /* DiagArray467 */ diag::ext_token_used, -1,
  /* DiagArray468 */ diag::warn_parameter_size, diag::warn_return_value_size, -1,
  /* DiagArray470 */ diag::warn_fe_linking_module, -1,
  /* DiagArray471 */ diag::warn_impcast_literal_float_to_integer, diag::warn_impcast_literal_float_to_integer_out_of_range, -1,
  /* DiagArray472 */ diag::warn_float_compare_literal, diag::warn_float_overflow, diag::warn_float_underflow, -1,
  /* DiagArray473 */ diag::ext_template_arg_local_type, -1,
  /* DiagArray474 */ diag::warn_logical_not_on_lhs_of_check, -1,
  /* DiagArray475 */ diag::warn_logical_and_in_logical_or, -1,
  /* DiagArray476 */ diag::ext_c99_longlong, -1,
  /* DiagArray478 */ diag::ext_pp_macro_redef, -1,
  /* DiagArray479 */ diag::ext_main_used, diag::ext_noreturn_main, diag::ext_variadic_main, diag::warn_main_one_arg, diag::warn_main_redefined, diag::warn_main_returns_bool_literal, diag::warn_static_main, -1,
  /* DiagArray480 */ diag::ext_main_returns_nonint, -1,
  /* DiagArray481 */ diag::warn_has_warning_invalid_option, -1,
  /* DiagArray482 */ diag::ext_many_braces_around_init, -1,
  /* DiagArray483 */ diag::ext_mathematical_notation, -1,
  /* DiagArray484 */ diag::warn_max_tokens, diag::warn_max_tokens_total, -1,
  /* DiagArray485 */ diag::warn_max_unsigned_zero, -1,
  /* DiagArray486 */ diag::warn_suspicious_sizeof_memset, -1,
  /* DiagArray487 */ diag::warn_memsize_comparison, -1,
  /* DiagArray488 */ diag::warn_non_contravariant_param_types, diag::warn_non_covariant_ret_types, -1,
  /* DiagArray490 */ diag::ext_ms_abstract_keyword, -1,
  /* DiagArray491 */ diag::ext_anonymous_record_with_type, diag::ext_ms_anonymous_record, -1,
  /* DiagArray492 */ diag::ext_ms_cast_fn_obj, diag::ext_ms_impcast_fn_obj, -1,
  /* DiagArray493 */ diag::ext_charize_microsoft, -1,
  /* DiagArray494 */ diag::ext_comment_paste_microsoft, -1,
  /* DiagArray495 */ diag::ext_default_init_const, -1,
  /* DiagArray496 */ diag::ext_pp_operator_used_as_macro_name, -1,
  /* DiagArray497 */ diag::ext_param_default_argument_redefinition, -1,
  /* DiagArray498 */ diag::warn_attribute_section_drectve, -1,
  /* DiagArray499 */ diag::ext_ctrl_z_eof_microsoft, -1,
  /* DiagArray500 */ diag::ext_ms_forward_ref_enum, -1,
  /* DiagArray501 */ diag::ext_enumerator_too_large, -1,
  /* DiagArray502 */ diag::ext_ellipsis_exception_spec, diag::ext_incomplete_in_exception_spec, diag::ext_mismatched_exception_spec, diag::ext_mismatched_exception_spec_explicit_instantiation, diag::ext_override_exception_spec, -1,
  /* DiagArray503 */ diag::warn_microsoft_dependent_exists, -1,
  /* DiagArray504 */ diag::ext_ms_explicit_constructor_call, -1,
  /* DiagArray505 */ diag::warn_member_extra_qualification, -1,
  /* DiagArray506 */ diag::ext_ms_c_enum_fixed_underlying_type, -1,
  /* DiagArray507 */ diag::ext_flexible_array_empty_aggregate_ms, diag::ext_flexible_array_union_ms, -1,
  /* DiagArray508 */ diag::ext_goto_into_protected_scope, -1,
  /* DiagArray509 */ diag::ext_ms_ambiguous_direct_base, -1,
  /* DiagArray510 */ diag::ext_pp_include_search_ms, -1,
  /* DiagArray511 */ diag::ext_init_from_predefined, -1,
  /* DiagArray512 */ diag::ext_mutable_reference, -1,
  /* DiagArray513 */ diag::ext_pure_function_definition, -1,
  /* DiagArray514 */ diag::ext_static_non_static, -1,
  /* DiagArray515 */ diag::ext_ms_sealed_keyword, -1,
  /* DiagArray516 */ diag::ext_ms_static_assert, -1,
  /* DiagArray517 */ diag::ext_explicit_instantiation_duplicate, diag::ext_found_in_dependent_base, diag::ext_found_later_in_class, diag::ext_ms_delayed_template_argument, diag::ext_ms_deref_template_argument, diag::ext_ms_template_spec_redecl_out_of_scope, diag::ext_ms_template_type_arg_missing_typename, diag::ext_static_out_of_line, diag::ext_undeclared_unqual_id_with_dependent_base, diag::ext_unqualified_base_class, -1,
  /* DiagArray518 */ diag::ext_template_param_shadow, -1,
  /* DiagArray519 */ diag::ext_union_member_of_reference_type, -1,
  /* DiagArray520 */ diag::ext_friend_tag_redecl_outside_namespace, -1,
  /* DiagArray521 */ diag::ext_ms_using_declaration_inaccessible, -1,
  /* DiagArray522 */ diag::ext_pseudo_dtor_on_void, -1,
  /* DiagArray523 */ diag::warn_profile_data_misexpect, -1,
  /* DiagArray524 */ diag::warn_misleading_indentation, -1,
  /* DiagArray525 */ diag::warn_mismatched_delete_new, -1,
  /* DiagArray526 */ diag::warn_conflicting_param_types, -1,
  /* DiagArray527 */ diag::warn_conflicting_ret_types, -1,
  /* DiagArray528 */ diag::warn_struct_class_previous_tag_mismatch, diag::warn_struct_class_tag_mismatch, -1,
  /* DiagArray529 */ diag::warn_missing_braces, -1,
  /* DiagArray530 */ diag::ext_constinit_missing, -1,
  /* DiagArray531 */ diag::ext_no_declarators, diag::ext_standalone_specifier, diag::ext_typedef_without_a_name, diag::warn_standalone_specifier, -1,
  /* DiagArray532 */ diag::ext_missing_exception_specification, -1,
  /* DiagArray533 */ diag::warn_missing_field_initializers, -1,
  /* DiagArray536 */ diag::warn_missing_method_return_type, -1,
  /* DiagArray537 */ diag::warn_drv_missing_multilib, -1,
  /* DiagArray538 */ diag::warn_overriding_method_missing_noescape, -1,
  /* DiagArray539 */ diag::warn_suggest_noreturn_block, diag::warn_suggest_noreturn_function, -1,
  /* DiagArray540 */ diag::warn_cconv_knr, -1,
  /* DiagArray541 */ diag::warn_missing_prototype, -1,
  /* DiagArray542 */ diag::warn_missing_selector_name, -1,
  /* DiagArray543 */ diag::warn_missing_sysroot, -1,
  /* DiagArray544 */ diag::warn_missing_variable_declarations, -1,
  /* DiagArray545 */ diag::warn_assume_attribute_string_unknown_suggested, -1,
  /* DiagArray546 */ diag::remark_module_build, diag::remark_module_build_done, diag::remark_module_lock_failure, diag::remark_module_lock_timeout, -1,
  /* DiagArray547 */ diag::warn_module_conflict, diag::warn_module_system_bit_conflict, -1,
  /* DiagArray548 */ diag::warn_module_config_mismatch, -1,
  /* DiagArray549 */ diag::warn_duplicate_module_file_extension, -1,
  /* DiagArray550 */ diag::remark_module_import, -1,
  /* DiagArray551 */ diag::ext_module_import_in_extern_c, -1,
  /* DiagArray552 */ diag::remark_pp_include_directive_modular_translation, -1,
  /* DiagArray553 */ diag::remark_module_lock, -1,
  /* DiagArray554 */ diag::ext_equivalent_internal_linkage_decl_in_modules, -1,
  /* DiagArray555 */ diag::ext_module_import_not_at_top_level_noop, -1,
  /* DiagArray559 */ diag::warn_drv_msvc_not_found, -1,
  /* DiagArray560 */ diag::warn_drv_multi_gpu_arch, -1,
  /* DiagArray561 */ diag::warn_multichar_character_literal, -1,
  /* DiagArray562 */ diag::warn_vbase_moved_multiple_times, -1,
  /* DiagArray564 */ diag::ext_anonymous_record_with_anonymous_type, -1,
  /* DiagArray566 */ diag::warn_operator_new_returns_null, -1,
  /* DiagArray567 */ diag::ext_no_newline_eof, diag::warn_no_newline_eof, -1,
  /* DiagArray568 */ diag::warn_dereference_of_noderef_type, diag::warn_dereference_of_noderef_type_no_decl, diag::warn_noderef_to_dereferenceable_pointer, -1,
  /* DiagArray570 */ diag::ext_non_c_like_anon_struct_in_typedef, -1,
  /* DiagArray572 */ diag::warn_non_literal_null_pointer, -1,
  /* DiagArray573 */ diag::warn_non_modular_include_in_framework_module, -1,
  /* DiagArray574 */ diag::warn_non_modular_include_in_module, -1,
  /* DiagArray575 */ diag::warn_cannot_pass_non_pod_arg_to_vararg, diag::warn_non_pod_vararg_with_format_string, diag::warn_second_parameter_to_va_arg_not_pod, diag::warn_second_parameter_to_va_arg_ownership_qualified, -1,
  /* DiagArray576 */ diag::warn_alignment_not_power_of_two, -1,
  /* DiagArray577 */ diag::warn_non_virtual_dtor, -1,
  /* DiagArray578 */ diag::warn_null_arg, diag::warn_null_ret, -1,
  /* DiagArray580 */ diag::pp_nonportable_path, -1,
  /* DiagArray581 */ diag::pp_nonportable_system_path, -1,
  /* DiagArray582 */ diag::warn_neon_vector_initializer_non_portable, -1,
  /* DiagArray583 */ diag::warn_cstruct_memaccess, -1,
  /* DiagArray584 */ diag::warn_nsconsumed_attribute_mismatch, -1,
  /* DiagArray585 */ diag::warn_nsreturns_retained_attribute_mismatch, -1,
  /* DiagArray586 */ diag::warn_null_in_arithmetic_operation, diag::warn_null_in_comparison_operation, -1,
  /* DiagArray587 */ diag::null_in_char_or_string, diag::null_in_file, -1,
  /* DiagArray588 */ diag::warn_impcast_null_pointer_to_integer, -1,
  /* DiagArray589 */ diag::warn_binding_null_to_reference, diag::warn_indirection_through_null, -1,
  /* DiagArray590 */ diag::warn_pointer_arith_null_ptr, -1,
  /* DiagArray591 */ diag::warn_pointer_sub_null_ptr, -1,
  /* DiagArray592 */ diag::warn_conflicting_nullability_attr_overriding_param_types, diag::warn_conflicting_nullability_attr_overriding_ret_types, diag::warn_mismatched_nullability_attr, diag::warn_null_resettable_setter, diag::warn_nullability_duplicate, -1,
  /* DiagArray593 */ diag::warn_nullability_missing, -1,
  /* DiagArray594 */ diag::warn_nullability_missing_array, -1,
  /* DiagArray595 */ diag::warn_nullability_declspec, -1,
  /* DiagArray596 */ diag::ext_nullability, -1,
  /* DiagArray597 */ diag::warn_nullability_inferred_on_nested_type, -1,
  /* DiagArray598 */ diag::warn_nullability_lost, -1,
  /* DiagArray599 */ diag::warn_autosynthesis_property_ivar_match, -1,
  /* DiagArray600 */ diag::warn_impcast_constant_value_to_objc_bool, -1,
  /* DiagArray601 */ diag::warn_objc_boxing_invalid_utf8_string, -1,
  /* DiagArray602 */ diag::warn_objc_circular_container, -1,
  /* DiagArray604 */ diag::warn_objc_designated_init_missing_super_call, diag::warn_objc_designated_init_non_designated_init_call, diag::warn_objc_designated_init_non_super_designated_init_call, diag::warn_objc_implementation_missing_designated_init_override, diag::warn_objc_secondary_init_missing_init_call, diag::warn_objc_secondary_init_super_init_call, -1,
  /* DiagArray605 */ diag::warn_nsdictionary_duplicate_key, -1,
  /* DiagArray606 */ diag::warn_dup_category_def, -1,
  /* DiagArray607 */ diag::warn_superclass_variable_sized_type_not_at_end, diag::warn_variable_sized_ivar_visibility, -1,
  /* DiagArray608 */ diag::warn_forward_class_redefinition, -1,
  /* DiagArray609 */ diag::warn_ivars_in_interface, -1,
  /* DiagArray610 */ diag::warn_objc_literal_comparison, -1,
  /* DiagArray611 */ diag::warn_impcast_objective_c_literal_to_bool, diag::warn_objc_collection_literal_element, -1,
  /* DiagArray612 */ diag::warn_pp_objc_macro_redef_ignored, -1,
  /* DiagArray613 */ diag::warn_messaging_unqualified_id, -1,
  /* DiagArray614 */ diag::warn_class_method_not_found, diag::warn_class_method_not_found_with_typo, diag::warn_inst_method_not_found, diag::warn_instance_method_not_found_with_typo, diag::warn_instance_method_on_class_found, diag::warn_root_inst_method_not_found, -1,
  /* DiagArray615 */ diag::warn_missing_explicit_synthesis, -1,
  /* DiagArray616 */ diag::warn_objc_missing_super_call, -1,
  /* DiagArray617 */ diag::warn_multiple_method_decl, -1,
  /* DiagArray618 */ diag::warn_objc_property_retain_of_block, -1,
  /* DiagArray619 */ diag::warn_objc_pointer_cxx_catch_fragile, -1,
  /* DiagArray620 */ diag::warn_objc_property_assign_on_object, -1,
  /* DiagArray621 */ diag::warn_impl_required_for_class_property, diag::warn_impl_required_in_category_for_class_property, diag::warn_setter_getter_impl_required, diag::warn_setter_getter_impl_required_in_category, -1,
  /* DiagArray622 */ diag::warn_property_implicitly_mismatched, -1,
  /* DiagArray623 */ diag::warn_cocoa_naming_owned_rule, -1,
  /* DiagArray624 */ diag::warn_objc_property_default_assign_on_object, diag::warn_objc_property_no_assignment_attribute, -1,
  /* DiagArray625 */ diag::warn_autosynthesis_property_in_superclass, diag::warn_no_autosynthesis_property, diag::warn_no_autosynthesis_shared_ivar_property, -1,
  /* DiagArray626 */ diag::warn_category_method_impl_match, -1,
  /* DiagArray627 */ diag::warn_auto_synthesizing_protocol_property, -1,
  /* DiagArray628 */ diag::warn_objc_redundant_qualified_class_type, -1,
  /* DiagArray629 */ diag::warn_objc_readonly_property_has_setter, -1,
  /* DiagArray631 */ diag::warn_objc_redundant_literal_use, -1,
  /* DiagArray632 */ diag::warn_objc_root_class_missing, -1,
  /* DiagArray634 */ diag::warn_impcast_float_to_objc_signed_char_bool, -1,
  /* DiagArray635 */ diag::warn_impcast_int_to_objc_signed_char_bool, -1,
  /* DiagArray636 */ diag::warn_objc_string_literal_comparison, -1,
  /* DiagArray637 */ diag::warn_concatenated_nsarray_literal, -1,
  /* DiagArray638 */ diag::warn_objc_unsafe_perform_selector, -1,
  /* DiagArray639 */ diag::warn_odr_different_num_template_parameters, diag::warn_odr_different_template_parameter_kind, diag::warn_odr_field_type_inconsistent, diag::warn_odr_function_type_inconsistent, diag::warn_odr_ivar_type_inconsistent, diag::warn_odr_non_type_parameter_type_inconsistent, diag::warn_odr_objc_method_num_params_inconsistent, diag::warn_odr_objc_method_param_type_inconsistent, diag::warn_odr_objc_method_result_type_inconsistent, diag::warn_odr_objc_method_variadic_inconsistent, diag::warn_odr_objc_property_impl_kind_inconsistent, diag::warn_odr_objc_property_type_inconsistent, diag::warn_odr_objc_superclass_inconsistent, diag::warn_odr_objc_synthesize_ivar_inconsistent, diag::warn_odr_parameter_pack_non_pack, diag::warn_odr_tag_type_inconsistent, diag::warn_odr_variable_multiple_def, diag::warn_odr_variable_type_inconsistent, -1,
  /* DiagArray640 */ diag::warn_old_style_cast, -1,
  /* DiagArray642 */ diag::ext_opencl_ext_vector_type_rgba_selector, -1,
  /* DiagArray644 */ diag::ext_omp_attributes, -1,
  /* DiagArray645 */ diag::warn_omp_alignment_not_power_of_two, diag::warn_omp_allocate_thread_on_task_target_directive, diag::warn_omp_ctx_incompatible_property_for_selector, diag::warn_omp_ctx_incompatible_score_for_property, diag::warn_omp_ctx_incompatible_selector_for_set, diag::warn_omp_ctx_selector_without_properties, diag::warn_omp_declare_variant_ctx_mutiple_use, diag::warn_omp_declare_variant_ctx_not_a_property, diag::warn_omp_declare_variant_ctx_not_a_selector, diag::warn_omp_declare_variant_ctx_not_a_set, diag::warn_omp_declare_variant_expected, diag::warn_omp_declare_variant_string_literal_or_identifier, diag::warn_omp_linear_step_zero, diag::warn_omp_more_one_device_type_clause, diag::warn_omp_more_one_interop_type, diag::warn_omp_more_one_omp_all_memory, diag::warn_omp_unknown_assumption_clause_missing_id, diag::warn_omp_unknown_assumption_clause_without_args, diag::warn_omp_used_different_allocator, -1,
  /* DiagArray646 */ diag::ext_omp_loop_not_canonical_init, diag::warn_omp_loop_64_bit_var, -1,
  /* DiagArray647 */ diag::warn_omp_non_trivial_type_mapped, -1,
  /* DiagArray648 */ diag::warn_drv_omp_offload_target_duplicate, diag::warn_omp_declare_target_after_first_use, diag::warn_omp_not_in_target_context, -1,
  /* DiagArray649 */ diag::warn_drv_fine_grained_bitfield_accesses_ignored, diag::warn_drv_fjmc_for_elf_only, diag::warn_drv_jmc_requires_debuginfo, diag::warn_drv_loongarch_conflicting_implied_val, diag::warn_drv_moutline_atomics_unsupported_opt, diag::warn_drv_moutline_unsupported_opt, diag::warn_drv_needs_hvx, diag::warn_drv_ps_force_pic, diag::warn_drv_unsupported_diag_option_for_flang, diag::warn_drv_unsupported_longcalls, diag::warn_drv_unsupported_option_for_flang, diag::warn_drv_unsupported_option_for_offload_arch_req_feature, diag::warn_drv_unsupported_option_for_processor, diag::warn_drv_unsupported_option_for_target, diag::warn_drv_unsupported_pic_with_mabicalls, diag::warn_drv_unsupported_sdata, diag::warn_target_override_arm64ec, -1,
  /* DiagArray650 */ diag::ext_typecheck_ordered_comparison_of_function_pointers, diag::warn_typecheck_ordered_comparison_of_function_pointers, -1,
  /* DiagArray651 */ diag::ext_out_of_line_declaration, -1,
  /* DiagArray652 */ diag::ext_use_out_of_scope_declaration, -1,
  /* DiagArray653 */ diag::warn_overaligned_type, -1,
  /* DiagArray655 */ diag::ext_string_too_long, -1,
  /* DiagArray656 */ diag::warn_overloaded_shift_in_comparison, -1,
  /* DiagArray657 */ diag::warn_overloaded_virtual, -1,
  /* DiagArray659 */ diag::warn_fe_override_module, -1,
  /* DiagArray660 */ diag::warn_conflicting_overriding_param_modifiers, diag::warn_conflicting_overriding_param_types, diag::warn_conflicting_overriding_ret_type_modifiers, diag::warn_conflicting_overriding_ret_types, diag::warn_conflicting_overriding_variadic, diag::warn_non_contravariant_overriding_param_types, diag::warn_non_covariant_overriding_ret_types, -1,
  /* DiagArray661 */ diag::warn_drv_overriding_flag_option, -1,
  /* DiagArray662 */ diag::warn_unnecessary_packed, -1,
  /* DiagArray663 */ diag::warn_unpacked_field, -1,
  /* DiagArray664 */ diag::warn_padded_struct_anon_field, diag::warn_padded_struct_field, diag::warn_padded_struct_size, -1,
  /* DiagArray665 */ diag::warn_condition_is_assignment, diag::warn_precedence_bitwise_rel, diag::warn_precedence_conditional, -1,
  /* DiagArray666 */ diag::warn_equality_with_extra_parens, -1,
  /* DiagArray668 */ diag::remark_fe_backend_optimization_remark, -1,
  /* DiagArray669 */ diag::remark_fe_backend_optimization_remark_analysis, diag::remark_fe_backend_optimization_remark_analysis_aliasing, diag::remark_fe_backend_optimization_remark_analysis_fpcommute, -1,
  /* DiagArray670 */ diag::warn_fe_backend_optimization_failure, -1,
  /* DiagArray671 */ diag::remark_fe_backend_optimization_remark_missed, -1,
  /* DiagArray672 */ diag::warn_module_uses_date_time, -1,
  /* DiagArray673 */ diag::ext_aggregate_init_not_constant, diag::ext_anonymous_record_with_type, diag::ext_anonymous_struct_union_qualified, diag::ext_array_size_conversion, diag::ext_auto_new_list_init, diag::ext_c99_array_usage, diag::ext_c99_compound_literal, diag::ext_c99_feature, diag::ext_c99_flexible_array_member, diag::ext_c99_variable_decl_in_for_loop, diag::ext_c_empty_initializer, diag::ext_c_nullptr, diag::ext_cast_fn_obj, diag::ext_clang_diagnose_if, diag::ext_clang_enable_if, diag::ext_cxx11_enum_fixed_underlying_type, diag::ext_designated_init, diag::ext_dtor_name_ambiguous, diag::ext_dtor_named_in_wrong_scope, diag::ext_duplicate_declspec, diag::ext_ellipsis_exception_spec, diag::ext_empty_fnmacro_arg, diag::ext_enum_value_not_int, diag::ext_enumerator_list_comma_c, diag::ext_enumerator_list_comma_cxx, diag::ext_explicit_instantiation_without_qualified_id, diag::ext_expr_not_ice, diag::ext_extern_template, diag::ext_extra_semi, diag::ext_forward_ref_enum, diag::ext_freestanding_complex, diag::ext_gnu_array_range, diag::ext_hex_constant_invalid, diag::ext_hex_literal_invalid, diag::ext_ident_list_in_param, diag::ext_in_class_initializer_non_constant, diag::ext_integer_complement_complex, diag::ext_integer_increment_complex, diag::ext_internal_in_extern_inline_quiet, diag::ext_line_comment, diag::ext_main_used, diag::ext_mixed_decls_code, diag::ext_multi_line_line_comment, diag::ext_named_variadic_macro, diag::ext_no_newline_eof, diag::ext_nonstandard_escape, diag::ext_ns_enum_attribute, diag::ext_opencl_double_without_pragma, diag::ext_pointer_to_const_ref_member_on_rvalue, diag::ext_pp_bad_vaargs_use, diag::ext_pp_comma_expr, diag::ext_pp_ident_directive, diag::ext_pp_line_too_big, diag::ext_pp_opencl_variadic_macros, diag::ext_pp_warning_directive, diag::ext_return_has_void_expr, diag::ext_rvalue_to_reference_access_ctor, diag::ext_rvalue_to_reference_temp_copy_no_viable, diag::ext_sizeof_alignof_function_type, diag::ext_sizeof_alignof_void_type, diag::ext_subscript_non_lvalue, diag::ext_thread_before, diag::ext_typecheck_addrof_void, diag::ext_typecheck_cast_nonscalar, diag::ext_typecheck_comparison_of_fptr_to_void, diag::ext_typecheck_cond_one_void, diag::ext_typecheck_convert_pointer_void_func, diag::ext_typecheck_ordered_comparison_of_pointer_and_zero, diag::ext_variadic_macro, diag::warn_defined_in_function_type_macro, diag::warn_ext_c2x_attributes, diag::warn_ext_cxx11_attributes, diag::warn_format_conversion_argument_type_mismatch_pedantic, diag::warn_kern_is_method, diag::warn_strict_prototypes, -1,
  /* DiagArray674 */ diag::warn_opencl_unsupported_core_feature, diag::warn_pragma_extension_is_core, -1,
  /* DiagArray676 */ diag::warn_pessimizing_move_on_initialization, diag::warn_pessimizing_move_on_return, -1,
  /* DiagArray677 */ diag::ext_sizeof_alignof_function_type, diag::ext_sizeof_alignof_void_type, diag::warn_sub_ptr_zero_size_types, -1,
  /* DiagArray678 */ diag::warn_cast_nonnull_to_bool, diag::warn_impcast_pointer_to_bool, -1,
  /* DiagArray679 */ diag::warn_pointer_compare, -1,
  /* DiagArray680 */ diag::ext_typecheck_comparison_of_pointer_integer, -1,
  /* DiagArray681 */ diag::ext_typecheck_convert_incompatible_pointer_sign, -1,
  /* DiagArray682 */ diag::warn_pointer_to_enum_cast, -1,
  /* DiagArray683 */ diag::warn_pointer_to_int_cast, -1,
  /* DiagArray684 */ diag::ext_typecheck_cond_incompatible_pointers, -1,
  /* DiagArray685 */ diag::warn_poison_system_directories, -1,
  /* DiagArray686 */ diag::warn_potentially_direct_selector_expression, -1,
  /* DiagArray687 */ diag::warn_side_effects_typeid, -1,
  /* DiagArray688 */ diag::warn_pragma_attribute_unused, -1,
  /* DiagArray689 */ diag::pp_pragma_once_in_main_file, -1,
  /* DiagArray690 */ diag::warn_pragma_pack_modified_after_include, diag::warn_pragma_pack_no_pop_eof, -1,
  /* DiagArray691 */ diag::warn_pragma_pack_non_default_at_include, -1,
  /* DiagArray692 */ diag::pp_pragma_sysheader_in_main_file, -1,
  /* DiagArray693 */ diag::warn_no_support_for_eval_method_source_on_m32, diag::warn_redefine_extname_not_applied, -1,
  /* DiagArray694 */ diag::warn_cxx11_compat_constexpr_body_invalid_stmt, diag::warn_cxx11_compat_constexpr_body_multiple_return, diag::warn_cxx11_compat_constexpr_body_no_return, diag::warn_cxx11_compat_constexpr_local_var, diag::warn_cxx11_compat_constexpr_type_definition, diag::warn_cxx11_compat_decltype_auto_type_specifier, diag::warn_cxx11_compat_deduced_return_type, diag::warn_cxx11_compat_digit_separator, diag::warn_cxx11_compat_generic_lambda, diag::warn_cxx11_compat_init_capture, diag::warn_cxx11_compat_variable_template, -1,
  /* DiagArray696 */ diag::warn_cxx14_compat_class_template_argument_deduction, diag::warn_cxx14_compat_constexpr_if, diag::warn_cxx14_compat_constexpr_on_lambda, diag::warn_cxx14_compat_decomp_decl, diag::warn_cxx14_compat_fold_expression, diag::warn_cxx14_compat_init_statement, diag::warn_cxx14_compat_inline_variable, diag::warn_cxx14_compat_nested_namespace_definition, diag::warn_cxx14_compat_star_this_lambda_capture, diag::warn_cxx14_compat_static_assert_no_message, diag::warn_cxx14_compat_template_nontype_parm_auto_type, diag::warn_cxx14_compat_template_template_param_typename, diag::warn_cxx14_compat_u8_character_literal, diag::warn_cxx14_compat_using_attribute_ns, diag::warn_cxx17_compat_multi_using_declaration, diag::warn_cxx17_compat_using_declaration_pack, diag::warn_for_range_begin_end_types_differ, -1,
  /* DiagArray697 */ diag::warn_cxx14_compat_ns_enum_attribute, diag::warn_cxx17_hex_literal, -1,
  /* DiagArray698 */ diag::warn_cxx17_compat_adl_only_template_id, diag::warn_cxx17_compat_bitfield_member_init, diag::warn_cxx17_compat_capture_binding, diag::warn_cxx17_compat_constexpr_body_invalid_stmt, diag::warn_cxx17_compat_constexpr_ctor_missing_init, diag::warn_cxx17_compat_constexpr_function_try_block, diag::warn_cxx17_compat_constexpr_local_var_no_init, diag::warn_cxx17_compat_constexpr_union_ctor_no_init, diag::warn_cxx17_compat_constexpr_virtual, diag::warn_cxx17_compat_decomp_decl_spec, diag::warn_cxx17_compat_defaulted_comparison, diag::warn_cxx17_compat_defaulted_method_type_mismatch, diag::warn_cxx17_compat_equals_this_lambda_capture, diag::warn_cxx17_compat_explicit_bool, diag::warn_cxx17_compat_for_range_init_stmt, diag::warn_cxx17_compat_init_capture_pack, diag::warn_cxx17_compat_inline_nested_namespace_definition, diag::warn_cxx17_compat_lambda_def_ctor_assign, diag::warn_cxx17_compat_lambda_template_parameter_list, diag::warn_cxx17_compat_missing_varargs_arg, diag::warn_cxx17_compat_spaceship, diag::warn_cxx17_compat_template_nontype_parm_type, diag::warn_cxx17_compat_unicode_type, diag::warn_cxx17_compat_using_decl_class_member_enumerator, diag::warn_cxx17_compat_using_decl_non_member_enumerator, diag::warn_cxx17_compat_using_decl_scoped_enumerator, diag::warn_cxx17_compat_using_enum_declaration, -1,
  /* DiagArray699 */ diag::warn_cxx17_compat_designated_init, diag::warn_cxx17_compat_pointer_to_const_ref_member_on_rvalue, -1,
  /* DiagArray700 */ diag::ext_subscript_overload, diag::warn_cxx20_alias_in_init_statement, diag::warn_cxx20_compat_auto_expr, diag::warn_cxx20_compat_consteval_if, diag::warn_cxx20_compat_constexpr_body_invalid_stmt, diag::warn_cxx20_compat_constexpr_var, diag::warn_cxx20_compat_decl_attrs_on_lambda, diag::warn_cxx20_compat_label_end_of_compound_statement, diag::warn_cxx20_compat_operator_overload_static, diag::warn_cxx20_compat_size_t_suffix, diag::warn_cxx20_compat_static_lambda, diag::warn_cxx23_compat_defaulted_comparison_constexpr_mismatch, diag::warn_cxx23_compat_pp_directive, diag::warn_cxx23_compat_warning_directive, diag::warn_cxx23_delimited_escape_sequence, -1,
  /* DiagArray706 */ diag::warn_c2x_compat_bitint_suffix, diag::warn_c2x_compat_digit_separator, diag::warn_c2x_compat_empty_initializer, diag::warn_c2x_compat_keyword, diag::warn_c2x_compat_label_end_of_compound_statement, diag::warn_c2x_compat_literal_ucn_control_character, diag::warn_c2x_compat_literal_ucn_escape_basic_scs, diag::warn_c2x_compat_pp_directive, diag::warn_c2x_compat_warning_directive, diag::warn_c17_compat_ellipsis_only_parameter, diag::warn_c17_compat_static_assert_no_message, diag::warn_pre_c2x_compat_attributes, -1,
  /* DiagArray708 */ diag::warn_omp51_compat_attributes, -1,
  /* DiagArray709 */ diag::ext_predef_outside_function, -1,
  /* DiagArray710 */ diag::warn_private_extern, -1,
  /* DiagArray711 */ diag::warn_use_of_private_header_outside_module, -1,
  /* DiagArray712 */ diag::warn_mmap_mismatched_private_module_name, diag::warn_mmap_mismatched_private_submodule, diag::warn_mmap_redundant_export_as, diag::warn_no_priv_submodule_use_toplevel, -1,
  /* DiagArray713 */ diag::warn_profile_data_missing, -1,
  /* DiagArray714 */ diag::warn_profile_data_out_of_date, -1,
  /* DiagArray715 */ diag::warn_profile_data_unprofiled, -1,
  /* DiagArray716 */ diag::warn_property_access_suggest, -1,
  /* DiagArray717 */ diag::warn_property_attr_mismatch, diag::warn_property_attribute, diag::warn_property_redecl_getter_mismatch, diag::warn_readonly_property, -1,
  /* DiagArray718 */ diag::warn_unimplemented_protocol_method, -1,
  /* DiagArray719 */ diag::warn_protocol_property_mismatch, -1,
  /* DiagArray720 */ diag::warn_avx_calling_convention, -1,
  /* DiagArray721 */ diag::err_func_returning_qualified_void, -1,
  /* DiagArray722 */ diag::warn_quoted_include_in_framework_header, -1,
  /* DiagArray724 */ diag::warn_for_range_ref_binds_ret_temp, -1,
  /* DiagArray725 */ diag::warn_for_range_const_ref_binds_temp_built_from_ref, diag::warn_for_range_copy, -1,
  /* DiagArray726 */ diag::warn_reading_std_cxx_module_by_implicit_paths, -1,
  /* DiagArray727 */ diag::warn_var_decl_not_read_only, -1,
  /* DiagArray728 */ diag::warn_auto_readonly_iboutlet_property, -1,
  /* DiagArray729 */ diag::warn_bad_receiver_type, -1,
  /* DiagArray730 */ diag::warn_receiver_forward_class, diag::warn_receiver_forward_instance, -1,
  /* DiagArray731 */ diag::ext_member_redeclared, -1,
  /* DiagArray732 */ diag::warn_consteval_if_always_true, -1,
  /* DiagArray734 */ diag::warn_redundant_move_on_return, -1,
  /* DiagArray735 */ diag::warn_redundant_parens_around_declarator, -1,
  /* DiagArray736 */ diag::ext_register_storage_class, -1,
  /* DiagArray737 */ diag::warn_reinterpret_different_from_static, -1,
  /* DiagArray738 */ diag::remark_fe_backend_plugin, -1,
  /* DiagArray740 */ diag::warn_initializer_out_of_order, diag::warn_some_initializers_out_of_order, -1,
  /* DiagArray741 */ diag::ext_designated_init_reordered, -1,
  /* DiagArray742 */ diag::warn_objc_requires_super_protocol, -1,
  /* DiagArray744 */ diag::warn_reserved_extern_symbol, -1,
  /* DiagArray745 */ diag::warn_pp_macro_is_reserved_id, -1,
  /* DiagArray746 */ diag::warn_reserved_module_name, -1,
  /* DiagArray747 */ diag::ext_ms_reserved_user_defined_literal, diag::ext_reserved_user_defined_literal, -1,
  /* DiagArray748 */ diag::warn_pragma_restrict_expansion_macro_use, -1,
  /* DiagArray749 */ diag::ext_retained_language_linkage, -1,
  /* DiagArray751 */ diag::warn_ret_addr_label, diag::warn_ret_local_temp_addr_ref, diag::warn_ret_stack_addr_ref, -1,
  /* DiagArray753 */ diag::ext_return_has_expr, diag::ext_return_missing_expr, diag::warn_falloff_nonvoid_coroutine, diag::warn_falloff_nonvoid_function, diag::warn_falloff_nonvoid_lambda, diag::warn_maybe_falloff_nonvoid_coroutine, diag::warn_maybe_falloff_nonvoid_function, diag::warn_maybe_falloff_nonvoid_lambda, diag::warn_return_missing_expr, -1,
  /* DiagArray754 */ diag::warn_return_value_udt, diag::warn_return_value_udt_incomplete, -1,
  /* DiagArray755 */ diag::ext_ovl_rewrite_equalequal_not_bool, -1,
  /* DiagArray756 */ diag::remark_cc1_round_trip_generated, -1,
  /* DiagArray757 */ diag::warn_no_dynamic_cast_with_rtti_disabled, diag::warn_no_typeid_with_rtti_disabled, -1,
  /* DiagArray758 */ diag::remark_sanitize_address_insert_extra_padding_accepted, diag::remark_sanitize_address_insert_extra_padding_rejected, -1,
  /* DiagArray759 */ diag::warn_drv_sarif_format_unstable, -1,
  /* DiagArray760 */ diag::remark_pp_search_path_usage, -1,
  /* DiagArray761 */ diag::warn_attribute_section_on_redeclaration, diag::warn_duplicate_codeseg_attribute, diag::warn_mismatched_section, -1,
  /* DiagArray762 */ diag::warn_unimplemented_selector, -1,
  /* DiagArray763 */ diag::warn_multiple_selectors, -1,
  /* DiagArray764 */ diag::warn_self_assignment_builtin, -1,
  /* DiagArray765 */ diag::warn_identity_field_assign, -1,
  /* DiagArray766 */ diag::warn_self_assignment_overloaded, -1,
  /* DiagArray767 */ diag::warn_self_move, -1,
  /* DiagArray768 */ diag::warn_semicolon_before_method_body, -1,
  /* DiagArray769 */ diag::warn_missing_sentinel, diag::warn_not_enough_argument, -1,
  /* DiagArray771 */ diag::warn_fe_serialized_diag_failure, diag::warn_fe_serialized_diag_failure_during_finalisation, diag::warn_fe_serialized_diag_merge_failure, -1,
  /* DiagArray772 */ diag::warn_decl_shadow, -1,
  /* DiagArray774 */ diag::warn_shadow_field, -1,
  /* DiagArray775 */ diag::warn_ctor_parm_shadows_field, -1,
  /* DiagArray776 */ diag::warn_modifying_shadowing_decl, -1,
  /* DiagArray777 */ diag::warn_ivar_use_hidden, -1,
  /* DiagArray778 */ diag::warn_decl_shadow_uncaptured_local, -1,
  /* DiagArray779 */ diag::warn_shift_negative, -1,
  /* DiagArray780 */ diag::warn_shift_gt_typewidth, -1,
  /* DiagArray781 */ diag::warn_shift_lhs_negative, -1,
  /* DiagArray782 */ diag::warn_addition_in_bitshift, -1,
  /* DiagArray783 */ diag::warn_shift_result_gt_typewidth, -1,
  /* DiagArray784 */ diag::warn_shift_result_sets_sign_bit, -1,
  /* DiagArray785 */ diag::warn_impcast_integer_64_32, -1,
  /* DiagArray786 */ diag::warn_mixed_sign_comparison, -1,
  /* DiagArray787 */ diag::warn_impcast_integer_sign, diag::warn_impcast_integer_sign_conditional, diag::warn_impcast_nonnegative_result, -1,
  /* DiagArray789 */ diag::warn_no_underlying_type_specified_for_enum_bitfield, -1,
  /* DiagArray790 */ diag::ext_wchar_t_sign_spec, -1,
  /* DiagArray791 */ diag::warn_impcast_single_bit_bitield_precision_constant, -1,
  /* DiagArray792 */ diag::warn_sizeof_array_param, -1,
  /* DiagArray793 */ diag::warn_sizeof_array_decay, -1,
  /* DiagArray794 */ diag::warn_division_sizeof_array, -1,
  /* DiagArray795 */ diag::warn_division_sizeof_ptr, -1,
  /* DiagArray796 */ diag::warn_sizeof_pointer_expr_memaccess, diag::warn_sizeof_pointer_type_memaccess, -1,
  /* DiagArray797 */ diag::warn_slash_u_filename, -1,
  /* DiagArray798 */ diag::warn_slh_does_not_support_asm_goto, -1,
  /* DiagArray799 */ diag::remark_sloc_usage, -1,
  /* DiagArray800 */ diag::warn_sometimes_uninit_var, -1,
  /* DiagArray801 */ diag::warn_fe_source_mgr, -1,
  /* DiagArray802 */ diag::warn_omp_declare_variant_after_emitted, diag::warn_omp_declare_variant_after_used, diag::warn_omp_declare_variant_marked_as_declare_variant, diag::warn_omp_declare_variant_score_not_constant, diag::warn_omp_nesting_simd, diag::warn_omp_unterminated_declare_target, diag::warn_pragma_omp_ignored, diag::warn_unknown_declare_variant_isa_trait, -1,
  /* DiagArray803 */ diag::warn_sampler_initializer_invalid_bits, -1,
  /* DiagArray805 */ diag::warn_stack_exhausted, -1,
  /* DiagArray806 */ diag::warn_stack_clash_protection_inline_asm, -1,
  /* DiagArray807 */ diag::ext_in_class_initializer_float_type_cxx11, -1,
  /* DiagArray808 */ diag::ext_internal_in_extern_inline, diag::ext_internal_in_extern_inline_quiet, -1,
  /* DiagArray809 */ diag::warn_static_inline_explicit_inst_ignored, -1,
  /* DiagArray810 */ diag::warn_static_local_in_extern_inline, -1,
  /* DiagArray811 */ diag::warn_static_self_reference_in_init, -1,
  /* DiagArray812 */ diag::warn_drv_libstdcxx_not_found, -1,
  /* DiagArray824 */ diag::warn_strict_potentially_direct_selector_expression, -1,
  /* DiagArray825 */ diag::warn_strict_prototypes, -1,
  /* DiagArray826 */ diag::warn_strict_multiple_method_decl, -1,
  /* DiagArray827 */ diag::warn_stringcompare, -1,
  /* DiagArray828 */ diag::warn_concatenated_literal_array_init, -1,
  /* DiagArray829 */ diag::warn_impcast_string_literal_to_bool, -1,
  /* DiagArray830 */ diag::warn_string_plus_char, -1,
  /* DiagArray831 */ diag::warn_string_plus_int, -1,
  /* DiagArray832 */ diag::warn_strlcpycat_wrong_size, -1,
  /* DiagArray833 */ diag::warn_strncat_large_size, diag::warn_strncat_src_size, diag::warn_strncat_wrong_size, -1,
  /* DiagArray834 */ diag::warn_suggest_destructor_marked_not_override_overriding, -1,
  /* DiagArray835 */ diag::warn_suggest_function_marked_not_override_overriding, -1,
  /* DiagArray836 */ diag::ext_typecheck_base_super, -1,
  /* DiagArray837 */ diag::warn_suspicious_bzero_size, -1,
  /* DiagArray839 */ diag::warn_attr_swift_name_decl_kind, diag::warn_attr_swift_name_decl_missing_params, diag::warn_attr_swift_name_function, diag::warn_attr_swift_name_getter_parameters, diag::warn_attr_swift_name_invalid_identifier, diag::warn_attr_swift_name_missing_parameters, diag::warn_attr_swift_name_multiple_selfs, diag::warn_attr_swift_name_num_params, diag::warn_attr_swift_name_setter_parameters, diag::warn_attr_swift_name_subscript_getter_newValue, diag::warn_attr_swift_name_subscript_invalid_parameter, diag::warn_attr_swift_name_subscript_setter_multiple_newValues, diag::warn_attr_swift_name_subscript_setter_no_newValue, -1,
  /* DiagArray840 */ diag::warn_case_value_overflow, diag::warn_missing_case, diag::warn_not_in_enum, -1,
  /* DiagArray841 */ diag::warn_bool_switch_condition, -1,
  /* DiagArray843 */ diag::warn_def_missing_case, -1,
  /* DiagArray844 */ diag::warn_sync_op_misaligned, -1,
  /* DiagArray845 */ diag::warn_sync_fetch_and_nand_semantics_change, -1,
  /* DiagArray847 */ diag::warn_target_clone_mixed_values, -1,
  /* DiagArray848 */ diag::warn_comparison_bitwise_always, diag::warn_comparison_bitwise_or, -1,
  /* DiagArray849 */ diag::warn_alignment_builtin_useless, diag::warn_comparison_always, -1,
  /* DiagArray850 */ diag::warn_integer_constants_in_conditional_always_true, diag::warn_left_shift_always, diag::warn_tautological_bool_compare, -1,
  /* DiagArray852 */ diag::warn_out_of_range_compare, -1,
  /* DiagArray853 */ diag::warn_tautological_compare_objc_bool, -1,
  /* DiagArray854 */ diag::warn_tautological_overlap_comparison, -1,
  /* DiagArray855 */ diag::warn_nonnull_expr_compare, diag::warn_null_pointer_compare, -1,
  /* DiagArray856 */ diag::warn_tautological_constant_compare, -1,
  /* DiagArray857 */ diag::warn_address_of_reference_null_compare, diag::warn_this_null_compare, -1,
  /* DiagArray858 */ diag::warn_unsigned_char_always_true_comparison, -1,
  /* DiagArray859 */ diag::warn_unsigned_enum_always_true_comparison, -1,
  /* DiagArray860 */ diag::warn_unsigned_always_true_comparison, -1,
  /* DiagArray861 */ diag::warn_tautological_compare_value_range, -1,
  /* DiagArray862 */ diag::warn_tcb_enforcement_violation, -1,
  /* DiagArray863 */ diag::ext_typecheck_decl_incomplete_type, -1,
  /* DiagArray865 */ diag::warn_acquired_before, diag::warn_acquired_before_after_cycle, diag::warn_cannot_resolve_lock, diag::warn_double_lock, diag::warn_expecting_lock_held_on_loop, diag::warn_expecting_locked, diag::warn_fun_excludes_mutex, diag::warn_fun_requires_lock, diag::warn_fun_requires_negative_cap, diag::warn_lock_exclusive_and_shared, diag::warn_lock_some_predecessors, diag::warn_no_unlock, diag::warn_unlock_but_no_lock, diag::warn_unlock_kind_mismatch, diag::warn_var_deref_requires_any_lock, diag::warn_var_deref_requires_lock, diag::warn_variable_requires_any_lock, diag::warn_variable_requires_lock, -1,
  /* DiagArray866 */ diag::warn_thread_attribute_argument_not_lockable, diag::warn_thread_attribute_decl_not_lockable, diag::warn_thread_attribute_decl_not_pointer, diag::warn_thread_attribute_ignored, diag::warn_thread_attribute_not_on_capability_member, diag::warn_thread_attribute_not_on_non_static_member, -1,
  /* DiagArray867 */ diag::warn_thread_safety_beta, -1,
  /* DiagArray868 */ diag::warn_acquire_requires_negative_cap, -1,
  /* DiagArray869 */ diag::warn_fun_requires_lock_precise, diag::warn_var_deref_requires_lock_precise, diag::warn_variable_requires_lock_precise, -1,
  /* DiagArray870 */ diag::warn_guarded_pass_by_reference, diag::warn_pt_guarded_pass_by_reference, -1,
  /* DiagArray871 */ diag::warn_thread_safety_verbose, -1,
  /* DiagArray872 */ diag::trigraph_converted, diag::trigraph_ends_block_comment, diag::trigraph_ignored, diag::trigraph_ignored_block_comment, -1,
  /* DiagArray874 */ diag::warn_type_safety_null_pointer_required, diag::warn_type_safety_type_mismatch, diag::warn_type_tag_for_datatype_wrong_kind, -1,
  /* DiagArray875 */ diag::ext_redefinition_of_typedef, -1,
  /* DiagArray876 */ diag::ext_typename_missing, -1,
  /* DiagArray877 */ diag::warn_fe_unable_to_open_stats_file, -1,
  /* DiagArray878 */ diag::warn_unaligned_access, -1,
  /* DiagArray879 */ diag::warn_imp_cast_drops_unaligned, -1,
  /* DiagArray880 */ diag::warn_unavailable_fwdclass_message, -1,
  /* DiagArray881 */ diag::warn_undeclared_selector, diag::warn_undeclared_selector_with_typo, -1,
  /* DiagArray882 */ diag::warn_pp_undef_identifier, -1,
  /* DiagArray883 */ diag::warn_pp_undef_prefix, -1,
  /* DiagArray884 */ diag::warn_address_of_reference_bool_conversion, diag::warn_this_bool_conversion, -1,
  /* DiagArray885 */ diag::warn_func_template_missing, -1,
  /* DiagArray886 */ diag::warn_undefined_inline, -1,
  /* DiagArray887 */ diag::warn_undefined_internal, -1,
  /* DiagArray888 */ diag::ext_undefined_internal_type, -1,
  /* DiagArray889 */ diag::warn_pointer_indirection_from_incompatible_type, diag::warn_undefined_reinterpret_cast, -1,
  /* DiagArray890 */ diag::warn_var_template_missing, -1,
  /* DiagArray891 */ diag::warn_throw_underaligned_obj, -1,
  /* DiagArray892 */ diag::warn_side_effects_unevaluated_context, -1,
  /* DiagArray893 */ diag::warn_unguarded_availability, -1,
  /* DiagArray894 */ diag::warn_unguarded_availability_new, -1,
  /* DiagArray895 */ diag::warn_delimited_ucn_empty, diag::warn_delimited_ucn_incomplete, diag::warn_ucn_escape_incomplete, diag::warn_ucn_escape_no_digits, diag::warn_ucn_escape_surrogate, diag::warn_ucn_not_valid_in_c89, diag::warn_ucn_not_valid_in_c89_literal, -1,
  /* DiagArray896 */ diag::warn_utf8_symbol_homoglyph, -1,
  /* DiagArray897 */ diag::ext_unicode_whitespace, -1,
  /* DiagArray898 */ diag::warn_utf8_symbol_zero_width, -1,
  /* DiagArray899 */ diag::warn_base_class_is_uninit, diag::warn_field_is_uninit, diag::warn_reference_field_is_uninit, diag::warn_uninit_byref_blockvar_captured_by_block, diag::warn_uninit_self_reference_in_init, diag::warn_uninit_self_reference_in_reference_init, diag::warn_uninit_var, -1,
  /* DiagArray900 */ diag::warn_uninit_const_reference, -1,
  /* DiagArray901 */ diag::warn_drv_potentially_misspelled_joined_argument, diag::warn_drv_unknown_argument_clang_cl, diag::warn_drv_unknown_argument_clang_cl_with_suggestion, -1,
  /* DiagArray902 */ diag::warn_assume_attribute_string_unknown, -1,
  /* DiagArray903 */ diag::warn_unknown_attribute_ignored, -1,
  /* DiagArray904 */ diag::warn_drv_new_cuda_version, diag::warn_drv_partially_supported_cuda_version, -1,
  /* DiagArray905 */ diag::warn_pp_invalid_directive, -1,
  /* DiagArray906 */ diag::ext_unknown_escape, -1,
  /* DiagArray907 */ diag::ext_on_off_switch_syntax, diag::ext_pragma_syntax_eod, diag::ext_stdc_pragma_ignored, diag::warn_pragma_diagnostic_cannot_pop, diag::warn_pragma_diagnostic_invalid, diag::warn_pragma_diagnostic_invalid_option, diag::warn_pragma_diagnostic_invalid_token, diag::warn_pragma_exec_charset_expected, diag::warn_pragma_exec_charset_push_invalid, diag::warn_pragma_exec_charset_spec_invalid, diag::warn_pragma_ignored, diag::warn_pragma_include_alias_expected, diag::warn_pragma_include_alias_expected_filename, diag::warn_pragma_include_alias_mismatch_angle, diag::warn_pragma_include_alias_mismatch_quote, diag::warn_pragma_warning_expected, diag::warn_pragma_warning_expected_number, diag::warn_pragma_warning_push_level, diag::warn_pragma_warning_spec_invalid, diag::warn_stdc_fenv_round_not_supported, -1,
  /* DiagArray908 */ diag::warn_unknown_sanitizer_ignored, -1,
  /* DiagArray909 */ diag::warn_pragma_diagnostic_unknown_warning, diag::warn_unknown_diag_option, diag::warn_unknown_warning_specifier, -1,
  /* DiagArray910 */ diag::ext_template_arg_unnamed_type, -1,
  /* DiagArray911 */ diag::warn_unneeded_internal_decl, diag::warn_unneeded_static_internal_decl, -1,
  /* DiagArray912 */ diag::warn_unneeded_member_function, -1,
  /* DiagArray913 */ diag::warn_unqualified_call_to_std_cast_function, -1,
  /* DiagArray914 */ diag::warn_unreachable, -1,
  /* DiagArray916 */ diag::warn_unreachable_break, -1,
  /* DiagArray917 */ diag::warn_unreachable_fallthrough_attr, -1,
  /* DiagArray918 */ diag::warn_unreachable_association, -1,
  /* DiagArray919 */ diag::warn_unreachable_loop_increment, -1,
  /* DiagArray920 */ diag::warn_unreachable_return, -1,
  /* DiagArray921 */ diag::warn_unsafe_buffer_operation, diag::warn_unsafe_buffer_variable, -1,
  /* DiagArray922 */ diag::warn_unsequenced_mod_mod, diag::warn_unsequenced_mod_use, -1,
  /* DiagArray923 */ diag::warn_drv_no_floating_point_registers, diag::warn_drv_unsupported_float_abi_by_lib, -1,
  /* DiagArray924 */ diag::warn_target_unsupported_abs2008, diag::warn_target_unsupported_abslegacy, -1,
  /* DiagArray925 */ diag::warn_at_available_unchecked_use, -1,
  /* DiagArray926 */ diag::warn_target_unsupported_compact_branches, -1,
  /* DiagArray927 */ diag::warn_attribute_dll_instantiated_base_class, -1,
  /* DiagArray928 */ diag::warn_fe_backend_unsupported_fp_exceptions, diag::warn_fe_backend_unsupported_fp_rounding, -1,
  /* DiagArray929 */ diag::warn_template_qualified_friend_ignored, diag::warn_template_qualified_friend_unsupported, -1,
  /* DiagArray930 */ diag::warn_drv_unsupported_gpopt, -1,
  /* DiagArray931 */ diag::warn_target_unsupported_nan2008, diag::warn_target_unsupported_nanlegacy, -1,
  /* DiagArray932 */ diag::warn_drv_dwarf_version_limited_by_target, diag::warn_drv_unsupported_debug_info_opt_for_target, -1,
  /* DiagArray933 */ diag::warn_attribute_protected_visibility, -1,
  /* DiagArray934 */ diag::ext_partial_specs_not_deducible, -1,
  /* DiagArray937 */ diag::warn_unused_but_set_parameter, -1,
  /* DiagArray938 */ diag::warn_unused_but_set_variable, -1,
  /* DiagArray939 */ diag::warn_drv_diagnostics_hotness_requires_pgo, diag::warn_drv_diagnostics_misexpect_requires_pgo, diag::warn_drv_empty_joined_argument, diag::warn_drv_input_file_unused, diag::warn_drv_input_file_unused_by_cpp, diag::warn_drv_invalid_arch_name_with_suggestion, diag::warn_drv_preprocessed_input_file_unused, diag::warn_drv_unused_argument, diag::warn_drv_unused_x, diag::warn_ignored_clang_option, diag::warn_ignoring_fdiscard_for_bitcode, diag::warn_ignoring_verify_debuginfo_preserve_export, -1,
  /* DiagArray940 */ diag::warn_unused_comparison, -1,
  /* DiagArray941 */ diag::warn_unused_const_variable, -1,
  /* DiagArray942 */ diag::warn_unused_exception_param, -1,
  /* DiagArray943 */ diag::warn_unused_function, -1,
  /* DiagArray944 */ diag::warn_unused_property_expr, -1,
  /* DiagArray945 */ diag::warn_unused_label, -1,
  /* DiagArray946 */ diag::warn_unused_lambda_capture, -1,
  /* DiagArray947 */ diag::warn_unused_local_typedef, -1,
  /* DiagArray949 */ diag::pp_macro_not_used, -1,
  /* DiagArray950 */ diag::warn_unused_member_function, -1,
  /* DiagArray951 */ diag::warn_unused_parameter, -1,
  /* DiagArray952 */ diag::warn_unused_private_field, -1,
  /* DiagArray953 */ diag::warn_unused_property_backing_ivar, -1,
  /* DiagArray954 */ diag::warn_unused_result, diag::warn_unused_result_msg, -1,
  /* DiagArray955 */ diag::warn_unused_template, -1,
  /* DiagArray956 */ diag::warn_unused_call, diag::warn_unused_comma_left_operand, diag::warn_unused_constructor, diag::warn_unused_constructor_msg, diag::warn_unused_container_subscript_expr, diag::warn_unused_expr, diag::warn_unused_voidptr, -1,
  /* DiagArray957 */ diag::warn_unused_variable, -1,
  /* DiagArray958 */ diag::warn_unused_volatile, -1,
  /* DiagArray959 */ diag::warn_used_but_marked_unused, -1,
  /* DiagArray960 */ diag::warn_user_literal_reserved, -1,
  /* DiagArray961 */ diag::warn_diagnose_if_succeeded, -1,
  /* DiagArray962 */ diag::warn_second_arg_of_va_start_not_last_named_param, diag::warn_second_parameter_to_va_arg_never_compatible, diag::warn_va_start_type_is_undefined, -1,
  /* DiagArray963 */ diag::ext_named_variadic_macro, diag::ext_pp_bad_vaopt_use, diag::ext_variadic_macro, -1,
  /* DiagArray964 */ diag::warn_typecheck_vector_element_sizes_not_equal, -1,
  /* DiagArray965 */ diag::warn_incompatible_vectors, -1,
  /* DiagArray967 */ diag::warn_empty_parens_are_function_decl, diag::warn_parens_disambiguated_as_function_declaration, diag::warn_parens_disambiguated_as_variable_declaration, -1,
  /* DiagArray968 */ diag::warn_decl_in_param_list, diag::warn_redefinition_in_param_list, -1,
  /* DiagArray969 */ diag::warn_vla_used, -1,
  /* DiagArray970 */ diag::ext_vla, -1,
  /* DiagArray971 */ diag::warn_void_pointer_to_enum_cast, -1,
  /* DiagArray972 */ diag::warn_void_pointer_to_int_cast, -1,
  /* DiagArray973 */ diag::ext_typecheck_indirection_through_void_pointer, -1,
  /* DiagArray975 */ diag::warn_wasm_dynamic_exception_spec_ignored, -1,
  /* DiagArray976 */ diag::warn_weak_template_vtable, -1,
  /* DiagArray977 */ diag::warn_weak_vtable, -1,
  /* DiagArray978 */ diag::ext_deprecated_string_literal_conversion, -1,
  /* DiagArray980 */ diag::warn_xor_used_as_pow, diag::warn_xor_used_as_pow_base, diag::warn_xor_used_as_pow_base_extra, -1,
  /* DiagArray981 */ diag::warn_zero_as_null_pointer_constant, -1,
  /* DiagArray982 */ diag::ext_typecheck_zero_array_size, -1,
};

static const int16_t DiagSubGroups[] = {
  /* Empty */ -1,
  /* DiagSubGroup0 */ 300, -1,
  /* DiagSubGroup4 */ 17, 300, -1,
  /* DiagSubGroup11 */ 678, 827, 855, -1,
  /* DiagSubGroup17 */ 556, 665, 840, 841, 524, 663, -1,
  /* DiagSubGroup27 */ 212, -1,
  /* DiagSubGroup29 */ 36, 35, 32, -1,
  /* DiagSubGroup34 */ 31, -1,
  /* DiagSubGroup42 */ 43, -1,
  /* DiagSubGroup52 */ 393, 190, -1,
  /* DiagSubGroup56 */ 903, 384, -1,
  /* DiagSubGroup66 */ 101, 132, 349, -1,
  /* DiagSubGroup67 */ 135, -1,
  /* DiagSubGroup70 */ 791, -1,
  /* DiagSubGroup77 */ 678, 884, -1,
  /* DiagSubGroup78 */ 77, -1,
  /* DiagSubGroup79 */ 74, -1,
  /* DiagSubGroup88 */ 91, -1,
  /* DiagSubGroup89 */ 95, -1,
  /* DiagSubGroup90 */ 99, -1,
  /* DiagSubGroup91 */ 99, 94, 92, 694, 696, 698, 700, -1,
  /* DiagSubGroup93 */ 91, 695, 697, 699, 701, -1,
  /* DiagSubGroup95 */ 96, 97, 98, -1,
  /* DiagSubGroup102 */ 696, 698, 700, -1,
  /* DiagSubGroup103 */ 102, 697, 699, 701, -1,
  /* DiagSubGroup104 */ 101, 100, -1,
  /* DiagSubGroup106 */ 238, 230, 107, 698, 700, -1,
  /* DiagSubGroup108 */ 106, 699, 701, -1,
  /* DiagSubGroup109 */ 105, -1,
  /* DiagSubGroup110 */ 104, -1,
  /* DiagSubGroup111 */ 106, -1,
  /* DiagSubGroup112 */ 107, -1,
  /* DiagSubGroup113 */ 109, -1,
  /* DiagSubGroup115 */ 700, -1,
  /* DiagSubGroup116 */ 115, 701, -1,
  /* DiagSubGroup118 */ 117, 114, -1,
  /* DiagSubGroup122 */ 115, -1,
  /* DiagSubGroup123 */ 116, -1,
  /* DiagSubGroup124 */ 118, -1,
  /* DiagSubGroup125 */ 120, -1,
  /* DiagSubGroup126 */ 121, -1,
  /* DiagSubGroup127 */ 698, -1,
  /* DiagSubGroup128 */ 699, -1,
  /* DiagSubGroup129 */ 696, -1,
  /* DiagSubGroup130 */ 697, -1,
  /* DiagSubGroup131 */ 694, -1,
  /* DiagSubGroup133 */ 695, -1,
  /* DiagSubGroup134 */ 137, 139, 694, 696, 698, 700, -1,
  /* DiagSubGroup138 */ 134, 135, 136, 695, 697, 699, 701, -1,
  /* DiagSubGroup144 */ 117, -1,
  /* DiagSubGroup145 */ 144, -1,
  /* DiagSubGroup147 */ 165, -1,
  /* DiagSubGroup150 */ 151, -1,
  /* DiagSubGroup159 */ 575, -1,
  /* DiagSubGroup163 */ 162, -1,
  /* DiagSubGroup167 */ 168, 169, -1,
  /* DiagSubGroup173 */ 70, 600, -1,
  /* DiagSubGroup178 */ 77, 173, 286, 71, 311, 785, 439, 403, 400, 471, 572, 588, 611, 787, 829, -1,
  /* DiagSubGroup179 */ 588, -1,
  /* DiagSubGroup181 */ 182, 222, 20, 180, -1,
  /* DiagSubGroup184 */ 2, -1,
  /* DiagSubGroup192 */ 194, 196, 195, 751, -1,
  /* DiagSubGroup207 */ 206, 204, -1,
  /* DiagSubGroup210 */ 212, 213, 214, 216, 217, 219, 223, 224, 225, 226, 227, 228, 215, 230, 231, 236, 238, 240, 241, 242, 243, 237, -1,
  /* DiagSubGroup217 */ 220, -1,
  /* DiagSubGroup218 */ 219, -1,
  /* DiagSubGroup219 */ 221, -1,
  /* DiagSubGroup234 */ 235, -1,
  /* DiagSubGroup243 */ 92, -1,
  /* DiagSubGroup249 */ 250, -1,
  /* DiagSubGroup254 */ 256, 255, -1,
  /* DiagSubGroup257 */ 258, -1,
  /* DiagSubGroup270 */ 224, -1,
  /* DiagSubGroup272 */ 577, -1,
  /* DiagSubGroup281 */ 304, -1,
  /* DiagSubGroup282 */ 284, 225, -1,
  /* DiagSubGroup283 */ 226, -1,
  /* DiagSubGroup286 */ 287, 288, 283, -1,
  /* DiagSubGroup287 */ 227, -1,
  /* DiagSubGroup288 */ 228, -1,
  /* DiagSubGroup300 */ 217, 533, 390, 432, 768, 536, 786, 951, 937, 590, 591, 278, 828, 337, -1,
  /* DiagSubGroup302 */ 136, 96, -1,
  /* DiagSubGroup303 */ 278, -1,
  /* DiagSubGroup311 */ 313, 314, -1,
  /* DiagSubGroup316 */ 317, 326, 578, 323, 325, 319, 318, -1,
  /* DiagSubGroup327 */ 321, 323, 325, -1,
  /* DiagSubGroup332 */ 331, -1,
  /* DiagSubGroup336 */ 847, -1,
  /* DiagSubGroup338 */ 100, 105, 114, -1,
  /* DiagSubGroup344 */ 345, 346, 348, 349, 350, 351, 352, 353, 354, 356, 970, 357, 358, 359, 360, 361, 363, 364, 365, 366, 367, 731, 368, 369, 371, 372, 373, 374, 982, 375, 376, -1,
  /* DiagSubGroup369 */ 370, -1,
  /* DiagSubGroup389 */ 387, 388, -1,
  /* DiagSubGroup390 */ 391, -1,
  /* DiagSubGroup392 */ 401, 402, -1,
  /* DiagSubGroup397 */ 398, -1,
  /* DiagSubGroup400 */ 404, 634, -1,
  /* DiagSubGroup403 */ 635, -1,
  /* DiagSubGroup404 */ 394, -1,
  /* DiagSubGroup417 */ 418, 413, -1,
  /* DiagSubGroup423 */ 425, 574, -1,
  /* DiagSubGroup429 */ 230, -1,
  /* DiagSubGroup440 */ 439, -1,
  /* DiagSubGroup442 */ 443, -1,
  /* DiagSubGroup446 */ 386, -1,
  /* DiagSubGroup473 */ 137, -1,
  /* DiagSubGroup476 */ 98, -1,
  /* DiagSubGroup477 */ 315, 723, -1,
  /* DiagSubGroup489 */ 493, 498, 510, 496, 506, 515, 490, 520, 502, 521, 512, 513, 519, 504, 501, 497, 517, 514, 500, 508, 507, 505, 492, 495, 522, 491, 494, 499, 516, 511, 426, -1,
  /* DiagSubGroup517 */ 518, -1,
  /* DiagSubGroup556 */ 41, 79, 156, 162, 207, 316, 315, 330, 392, 430, 441, 528, 529, 557, 561, 725, 739, 753, 764, 767, 792, 793, 831, 849, 872, 899, 907, 935, 974, 616, 604, 607, 657, 710, 152, 298, 961, -1,
  /* DiagSubGroup557 */ 676, 734, 752, 767, -1,
  /* DiagSubGroup558 */ 510, -1,
  /* DiagSubGroup563 */ 99, -1,
  /* DiagSubGroup569 */ 107, -1,
  /* DiagSubGroup571 */ 786, 178, 472, -1,
  /* DiagSubGroup574 */ 573, -1,
  /* DiagSubGroup590 */ 365, -1,
  /* DiagSubGroup593 */ 594, -1,
  /* DiagSubGroup603 */ 630, -1,
  /* DiagSubGroup610 */ 636, -1,
  /* DiagSubGroup630 */ 631, -1,
  /* DiagSubGroup633 */ 635, 634, 600, 853, -1,
  /* DiagSubGroup643 */ 802, 645, 646, 648, 647, 644, -1,
  /* DiagSubGroup648 */ 647, -1,
  /* DiagSubGroup658 */ 432, -1,
  /* DiagSubGroup662 */ 663, -1,
  /* DiagSubGroup665 */ 475, 474, 73, 75, 782, 656, 666, 193, -1,
  /* DiagSubGroup667 */ 893, -1,
  /* DiagSubGroup673 */ 140, 96, 98, 100, 101, 105, 114, 117, 310, 338, 346, 348, 349, 350, 351, 352, 353, 356, 357, 358, 360, 361, 363, 364, 365, 366, 367, 368, 369, 373, 375, 376, 465, 476, 493, 494, 496, 499, 501, 506, 507, 514, 655, 970, 982, 259, 467, 462, 208, 408, 275, 279, 596, 307, 341, 69, 888, 749, 166, 564, 119, -1,
  /* DiagSubGroup675 */ 236, 478, 84, 748, 306, -1,
  /* DiagSubGroup677 */ 367, -1,
  /* DiagSubGroup682 */ 971, -1,
  /* DiagSubGroup683 */ 682, 972, -1,
  /* DiagSubGroup690 */ 691, -1,
  /* DiagSubGroup693 */ 907, 389, 688, 690, -1,
  /* DiagSubGroup695 */ 694, 132, -1,
  /* DiagSubGroup697 */ 696, -1,
  /* DiagSubGroup699 */ 698, -1,
  /* DiagSubGroup701 */ 700, -1,
  /* DiagSubGroup703 */ 702, -1,
  /* DiagSubGroup704 */ 702, -1,
  /* DiagSubGroup705 */ 703, -1,
  /* DiagSubGroup707 */ 706, -1,
  /* DiagSubGroup723 */ 725, 724, -1,
  /* DiagSubGroup736 */ 238, -1,
  /* DiagSubGroup739 */ 740, 741, -1,
  /* DiagSubGroup743 */ 745, -1,
  /* DiagSubGroup744 */ 745, 746, 960, -1,
  /* DiagSubGroup747 */ 94, -1,
  /* DiagSubGroup750 */ 751, -1,
  /* DiagSubGroup753 */ 754, -1,
  /* DiagSubGroup762 */ 763, -1,
  /* DiagSubGroup764 */ 766, 765, -1,
  /* DiagSubGroup770 */ 922, -1,
  /* DiagSubGroup772 */ 776, 777, -1,
  /* DiagSubGroup773 */ 772, 775, 778, 774, -1,
  /* DiagSubGroup775 */ 776, -1,
  /* DiagSubGroup804 */ 803, -1,
  /* DiagSubGroup807 */ 371, -1,
  /* DiagSubGroup824 */ 686, -1,
  /* DiagSubGroup825 */ 232, -1,
  /* DiagSubGroup838 */ 796, 269, 583, 486, 837, -1,
  /* DiagSubGroup849 */ 850, 855, 854, 848, 857, 853, -1,
  /* DiagSubGroup850 */ 852, -1,
  /* DiagSubGroup851 */ 873, 861, -1,
  /* DiagSubGroup864 */ 866, 865, 869, 870, -1,
  /* DiagSubGroup873 */ 856, 860, 858, 859, -1,
  /* DiagSubGroup892 */ 687, -1,
  /* DiagSubGroup893 */ 894, -1,
  /* DiagSubGroup899 */ 800, 811, 900, -1,
  /* DiagSubGroup910 */ 139, -1,
  /* DiagSubGroup914 */ 919, 917, 918, -1,
  /* DiagSubGroup915 */ 914, 916, 920, -1,
  /* DiagSubGroup935 */ 936, 943, 945, 952, 946, 947, 956, 957, 938, 953, -1,
  /* DiagSubGroup943 */ 911, -1,
  /* DiagSubGroup948 */ 947, -1,
  /* DiagSubGroup950 */ 912, -1,
  /* DiagSubGroup955 */ 911, -1,
  /* DiagSubGroup956 */ 940, 954, 892, -1,
  /* DiagSubGroup957 */ 941, -1,
  /* DiagSubGroup966 */ 965, -1,
  /* DiagSubGroup969 */ 970, -1,
  /* DiagSubGroup972 */ 971, -1,
  /* DiagSubGroup978 */ 243, -1,
  /* DiagSubGroup979 */ 978, -1,
};

static const char DiagGroupNames[] = {
    "\000\020#pragma-messages\t#warnings\020CFString-literal\003CL4\032Indep"
    "endentClass-attribute\022NSObject-attribute\003abi\016absolute-value\024"
    "abstract-final-class\023abstract-vbase-init\007address\030address-of-pa"
    "cked-member\024address-of-temporary\020aggregate-return\naix-compat\016"
    "align-mismatch\003all\006alloca\031alloca-with-align-alignof\027always-"
    "inline-coroutine\020ambiguous-delete\022ambiguous-ellipsis\017ambiguous"
    "-macro\031ambiguous-member-template\033ambiguous-reversed-operator\034a"
    "nalyzer-incompatible-plugin\031anon-enum-enum-conversion\025anonymous-p"
    "ack-parens\003arc%arc-bridge-casts-disallowed-in-nonarc\036arc-maybe-re"
    "peated-use-of-weak\025arc-non-pod-memaccess\031arc-performSelector-leak"
    "s\030arc-repeated-use-of-weak\021arc-retain-cycles\032arc-unsafe-retain"
    "ed-assign\026argument-outside-range\034argument-undefined-behaviour\014"
    "array-bounds\037array-bounds-pointer-arithmetic\017array-parameter\003a"
    "sm\022asm-operand-widths\013assign-enum\006assume\013at-protocol\034ati"
    "mport-in-framework-header\015atomic-access\020atomic-alignment\027atomi"
    "c-implicit-seq-cst\026atomic-memory-ordering\021atomic-properties*atomi"
    "c-property-with-user-defined-accessor\035attribute-packed-for-bitfield\021"
    "attribute-warning\nattributes\033auto-disable-vptr-sanitizer\013auto-im"
    "port\022auto-storage-class\013auto-var-id\014availability\030avr-rtlib-"
    "linking-quirks\016backend-plugin\030backslash-newline-escape\021bad-fun"
    "ction-cast\016binary-literal\026bind-to-temporary-copy\024binding-in-co"
    "ndition\021bit-int-extension\034bitfield-constant-conversion\030bitfiel"
    "d-enum-conversion\016bitfield-width\037bitwise-conditional-parentheses\032"
    "bitwise-instead-of-logical\026bitwise-op-parentheses\033block-capture-a"
    "utoreleasing\017bool-conversion\020bool-conversions\016bool-operation\022"
    "braced-scalar-init\021branch-protection\013bridge-cast builtin-assume-a"
    "ligned-alignment\027builtin-macro-redefined\027builtin-memcpy-chk-size\027"
    "builtin-requires-header\nc++-compat\014c++0x-compat\020c++0x-extensions"
    "\017c++0x-narrowing\014c++11-compat(c++11-compat-deprecated-writable-st"
    "rings\025c++11-compat-pedantic*c++11-compat-reserved-user-defined-liter"
    "al\020c++11-extensions\020c++11-extra-semi\026c++11-inline-namespace\017"
    "c++11-long-long\017c++11-narrowing\032c++14-attribute-extensions\024c++"
    "14-binary-literal\014c++14-compat\025c++14-compat-pedantic\020c++14-ext"
    "ensions\032c++17-attribute-extensions\014c++17-compat\025c++17-compat-m"
    "angling\025c++17-compat-pedantic\020c++17-extensions\020c++1y-extension"
    "s\014c++1z-compat\025c++1z-compat-mangling\020c++1z-extensions\032c++20"
    "-attribute-extensions\014c++20-compat\025c++20-compat-pedantic\020c++20"
    "-designator\020c++20-extensions$c++23-default-comp-relaxed-constexpr\020"
    "c++23-extensions\020c++26-extensions\014c++2a-compat\025c++2a-compat-pe"
    "dantic\020c++2a-extensions\020c++2b-extensions\020c++2c-extensions\036c"
    "++98-c++11-c++14-c++17-compat'c++98-c++11-c++14-c++17-compat-pedantic\030"
    "c++98-c++11-c++14-compat!c++98-c++11-c++14-compat-pedantic\022c++98-c++"
    "11-compat!c++98-c++11-compat-binary-literal\033c++98-c++11-compat-pedan"
    "tic\014c++98-compat#c++98-compat-bind-to-temporary-copy\027c++98-compat"
    "-extra-semi%c++98-compat-local-type-template-args\025c++98-compat-pedan"
    "tic'c++98-compat-unnamed-type-template-args\016c11-extensions\nc2x-comp"
    "at\016c2x-extensions\nc99-compat\016c99-designator\016c99-extensions#ca"
    "ll-to-pure-virtual-from-ctor-dtor\025called-once-parameter\ncast-align\027"
    "cast-calling-convention\022cast-function-type\031cast-function-type-str"
    "ict\020cast-of-sel-type\tcast-qual\023cast-qual-unrelated\nchar-align\017"
    "char-subscripts\014clang-cl-pch\020class-conversion\015class-varargs\017"
    "cmse-union-leak\005comma\007comment\010comments\036compare-distinct-poi"
    "nter-types\022completion-handler\026complex-component-init\024compound-"
    "token-split\035compound-token-split-by-macro\035compound-token-split-by"
    "-space\031conditional-type-mismatch\031conditional-uninitialized\015con"
    "fig-macros\023constant-conversion\022constant-evaluated\030constant-log"
    "ical-operand\023constexpr-not-const\010consumed\nconversion\017conversi"
    "on-null$coro-non-aligned-allocation-function\tcoroutine%coroutine-missi"
    "ng-unhandled-exception\026covered-switch-default\003cpp\030cstring-form"
    "at-directive\026ctad-maybe-unsupported\021ctor-dtor-privacy\003ctu\013c"
    "uda-compat\030custom-atomic-properties\027cxx-attribute-extension\010da"
    "ngling\015dangling-else\016dangling-field\014dangling-gsl\031dangling-i"
    "nitializer-list\023darwin-sdk-settings\tdate-time\023dealloc-in-categor"
    "y\035debug-compression-unavailable\033declaration-after-statement\032de"
    "faulted-function-deleted\026delegating-ctor-cycles delete-abstract-non-"
    "virtual-dtor\021delete-incomplete$delete-non-abstract-non-virtual-dtor\027"
    "delete-non-virtual-dtor#delimited-escape-sequence-extension\032deprecat"
    "e-lax-vec-conv-all\ndeprecated\035deprecated-altivec-src-compat$depreca"
    "ted-anon-enum-enum-conversion\030deprecated-array-compare\025deprecated"
    "-attributes\023deprecated-builtins\032deprecated-comma-subscript\017dep"
    "recated-copy\024deprecated-copy-dtor\031deprecated-copy-with-dtor'depre"
    "cated-copy-with-user-provided-copy'deprecated-copy-with-user-provided-d"
    "tor\024deprecated-coroutine\027deprecated-declarations!deprecated-dynam"
    "ic-exception-spec\027deprecated-enum-compare#deprecated-enum-compare-co"
    "nditional\037deprecated-enum-enum-conversion deprecated-enum-float-conv"
    "ersion\032deprecated-implementations\031deprecated-increment-bool\033de"
    "precated-literal-operator\030deprecated-non-prototype\031deprecated-obj"
    "c-isa-usage%deprecated-objc-pointer-introspection5deprecated-objc-point"
    "er-introspection-performSelector\021deprecated-pragma)deprecated-redund"
    "ant-constexpr-static-def\023deprecated-register\037deprecated-static-an"
    "alyzer-flag\027deprecated-this-capture\017deprecated-type\023deprecated"
    "-volatile\033deprecated-writable-strings\022direct-ivar-access\030disab"
    "led-macro-expansion\025disabled-optimization\014discard-qual\034distrib"
    "uted-object-modifiers\013div-by-zero\020division-by-zero\036dll-attribu"
    "te-on-redeclaration%dllexport-explicit-instantiation-decl\032dllimport-"
    "static-field-def\015documentation\035documentation-deprecated-sync\022d"
    "ocumentation-html\026documentation-pedantic\035documentation-unknown-co"
    "mmand\036dollar-in-identifier-extension\020double-promotion\tdtor-name\014"
    "dtor-typedef\030duplicate-decl-specifier\016duplicate-enum\024duplicate"
    "-method-arg\026duplicate-method-match\022duplicate-protocol\017dxil-val"
    "idation\027dynamic-class-memaccess\026dynamic-exception-spec\034eager-l"
    "oad-cxx-named-modules\006effc++\024elaborated-enum-base\025elaborated-e"
    "num-class\022embedded-directive\nempty-body\023empty-decomposition\017e"
    "mpty-init-stmt\026empty-translation-unit\013encode-type\014endif-labels"
    "\014enum-compare\030enum-compare-conditional\023enum-compare-switch\031"
    "enum-constexpr-conversion\017enum-conversion\024enum-enum-conversion\025"
    "enum-float-conversion\016enum-too-large\nexceptions\023excess-initializ"
    "ers\025exit-time-destructors\024expansion-to-defined\031experimental-he"
    "ader-units\030explicit-initialize-call\027explicit-ownership-type\016ex"
    "port-unnamed\017extern-c-compat\022extern-initializer\005extra\023extra"
    "-qualification\nextra-semi\017extra-semi-stmt\014extra-tokens\032final-"
    "dtor-non-final-class\013final-macro\024fixed-enum-extension\024fixed-po"
    "int-overflow\tflag-enum\031flexible-array-extensions\020float-conversio"
    "n\013float-equal\031float-overflow-conversion\025float-zero-conversion\021"
    "for-loop-analysis\006format\021format-extra-args\030format-insufficient"
    "-args\030format-invalid-specifier\016format-non-iso\021format-nonlitera"
    "l\017format-pedantic\017format-security\025format-type-confusion\nforma"
    "t-y2k\022format-zero-length\010format=2\016fortify-source\023four-char-"
    "constants\015frame-address\021frame-larger-than\022frame-larger-than=%f"
    "ramework-include-private-from-public\023free-nonheap-object\036function"
    "-def-in-objc-container\025function-multiversion\014fuse-ld-path\033futu"
    "re-attribute-extensions\015future-compat\ngcc-compat\026generic-type-ex"
    "tension\023global-constructors\013global-isel\003gnu\026gnu-alignof-exp"
    "ression\024gnu-anonymous-struct\033gnu-array-member-paren-init\015gnu-a"
    "uto-type\022gnu-binary-literal\016gnu-case-range\023gnu-complex-integer"
    " gnu-compound-literal-initializer\037gnu-conditional-omitted-operand\016"
    "gnu-designator\025gnu-empty-initializer\020gnu-empty-struct\036gnu-flex"
    "ible-array-initializer\037gnu-flexible-array-union-member\024gnu-foldin"
    "g-constant\026gnu-imaginary-constant\020gnu-include-next\035gnu-inline-"
    "cpp-without-extern\022gnu-label-as-value\017gnu-line-marker\033gnu-null"
    "-pointer-arithmetic\027gnu-offsetof-extensions\021gnu-pointer-arith\023"
    "gnu-redeclared-enum\030gnu-statement-expression-gnu-statement-expressio"
    "n-from-macro-expansion\025gnu-static-float-init$gnu-string-literal-oper"
    "ator-template\016gnu-union-cast\"gnu-variable-sized-type-not-at-end\027"
    "gnu-zero-line-directive!gnu-zero-variadic-macro-arguments\024gpu-maybe-"
    "wrong-side\014header-guard\016header-hygiene\031hip-omp-target-directiv"
    "es\010hip-only\017hlsl-extensions\025idiomatic-parentheses\022ignored-a"
    "ttributes)ignored-availability-without-sdk-settings\035ignored-optimiza"
    "tion-argument\030ignored-pragma-intrinsic\027ignored-pragma-optimize\017"
    "ignored-pragmas\022ignored-qualifiers\034ignored-reference-qualifiers\010"
    "implicit\032implicit-atomic-properties#implicit-const-int-float-convers"
    "ion*implicit-conversion-floating-point-to-bool implicit-exception-spec-"
    "mismatch\024implicit-fallthrough!implicit-fallthrough-per-function\037i"
    "mplicit-fixed-point-conversion\031implicit-float-conversion\035implicit"
    "-function-declaration\014implicit-int\027implicit-int-conversion\035imp"
    "licit-int-float-conversion\024implicit-retain-self\033implicitly-unsign"
    "ed-literal\006import&import-preprocessor-directive-pedantic\021inaccess"
    "ible-base\032include-next-absolute-path\033include-next-outside-header\033"
    "incompatible-exception-spec#incompatible-function-pointer-types*incompa"
    "tible-function-pointer-types-strict\"incompatible-library-redeclaration"
    "\026incompatible-ms-struct\032incompatible-pointer-types.incompatible-p"
    "ointer-types-discards-qualifiers\032incompatible-property-type\024incom"
    "patible-sysroot'incomplete-framework-module-declaration\031incomplete-i"
    "mplementation\021incomplete-module\035incomplete-setjmp-declaration\023"
    "incomplete-umbrella\026inconsistent-dllimport(inconsistent-missing-dest"
    "ructor-override\035inconsistent-missing-override\016increment-bool\022i"
    "nfinite-recursion\tinit-self\025initializer-overrides\023injected-class"
    "-name\006inline\ninline-asm#inline-namespace-reopened-noninline\021inli"
    "ne-new-delete\"instantiation-after-specialization\016int-conversion\017"
    "int-conversions\023int-in-bool-context\023int-to-pointer-cast\030int-to"
    "-void-pointer-cast\020integer-overflow\031interrupt-service-routine\035"
    "invalid-command-line-argument\021invalid-constexpr\020invalid-iboutlet&"
    "invalid-initializer-from-system-header\035invalid-ios-deployment-target"
    "\030invalid-no-builtin-names\020invalid-noreturn\020invalid-offsetof in"
    "valid-or-nonexistent-directory\036invalid-partial-specialization\013inv"
    "alid-pch\020invalid-pp-token\027invalid-source-encoding\035invalid-stat"
    "ic-assert-message\023invalid-token-paste\032invalid-unevaluated-string\014"
    "invalid-utf8\020jump-seh-finally\016keyword-compat\015keyword-macro\026"
    "knr-promoted-parameter\030language-extension-token\023large-by-value-co"
    "py\006liblto\017linker-warnings\022literal-conversion\015literal-range\030"
    "local-type-template-args\027logical-not-parentheses\026logical-op-paren"
    "theses\tlong-long\015loop-analysis\017macro-redefined\004main\020main-r"
    "eturn-type\027malformed-warning-check\036many-braces-around-scalar-init"
    "*mathematical-notation-identifier-extension\nmax-tokens\021max-unsigned"
    "-zero\026memset-transposed-args\022memsize-comparison\021method-signatu"
    "res\tmicrosoft\022microsoft-abstract\022microsoft-anon-tag\016microsoft"
    "-cast\021microsoft-charize\027microsoft-comment-paste\024microsoft-cons"
    "t-init\023microsoft-cpp-macro\"microsoft-default-arg-redefinition\031mi"
    "crosoft-drectve-section\025microsoft-end-of-file microsoft-enum-forward"
    "-reference\024microsoft-enum-value\030microsoft-exception-spec\020micro"
    "soft-exists#microsoft-explicit-constructor-call\035microsoft-extra-qual"
    "ification\024microsoft-fixed-enum\030microsoft-flexible-array\016micros"
    "oft-goto\033microsoft-inaccessible-base\021microsoft-include\036microso"
    "ft-init-from-predefined\033microsoft-mutable-reference\031microsoft-pur"
    "e-definition\032microsoft-redeclare-static\020microsoft-sealed\027micro"
    "soft-static-assert\022microsoft-template\031microsoft-template-shadow m"
    "icrosoft-union-member-reference\034microsoft-unqualified-friend\024micr"
    "osoft-using-decl\032microsoft-void-pseudo-dtor\tmisexpect\026misleading"
    "-indentation\025mismatched-new-delete\032mismatched-parameter-types\027"
    "mismatched-return-types\017mismatched-tags\016missing-braces\021missing"
    "-constinit\024missing-declarations\026missing-exception-spec\032missing"
    "-field-initializers\030missing-format-attribute\024missing-include-dirs"
    "\032missing-method-return-type\020missing-multilib\020missing-noescape\020"
    "missing-noreturn\030missing-prototype-for-cc\022missing-prototypes\025m"
    "issing-selector-name\017missing-sysroot\035missing-variable-declaration"
    "s\025misspelled-assumption\014module-build\017module-conflict\033module"
    "-file-config-mismatch\025module-file-extension\015module-import\031modu"
    "le-import-in-extern-c\032module-include-translation\013module-lock\"mod"
    "ules-ambiguous-internal-linkage\037modules-import-nested-redundant\004m"
    "ost\004move\014msvc-include\016msvc-not-found\tmulti-gpu\tmultichar\023"
    "multiple-move-vbase\tnarrowing\021nested-anon-types\016nested-externs\020"
    "new-returns-null\013newline-eof\007noderef\015noexcept-type\031non-c-ty"
    "pedef-for-linkage\007non-gcc\033non-literal-null-conversion'non-modular"
    "-include-in-framework-module\035non-modular-include-in-module\017non-po"
    "d-varargs\032non-power-of-two-alignment\020non-virtual-dtor\007nonnull\025"
    "nonportable-cfstrings\030nonportable-include-path\037nonportable-system"
    "-include-path!nonportable-vector-initialization\024nontrivial-memaccess"
    "\023nsconsumed-mismatch\022nsreturns-mismatch\017null-arithmetic\016nul"
    "l-character\017null-conversion\020null-dereference\027null-pointer-arit"
    "hmetic\030null-pointer-subtraction\013nullability\030nullability-comple"
    "teness\"nullability-completeness-on-arrays\024nullability-declspec\025n"
    "ullability-extension#nullability-inferred-on-nested-type\036nullable-to"
    "-nonnull-conversion+objc-autosynthesis-property-ivar-name-match\035objc"
    "-bool-constant-conversion\013objc-boxing\027objc-circular-container\016"
    "objc-cocoa-api\034objc-designated-initializers\036objc-dictionary-dupli"
    "cate-keys\"objc-duplicate-category-definition\023objc-flexible-array\037"
    "objc-forward-class-redefinition\024objc-interface-ivars\024objc-literal"
    "-compare\027objc-literal-conversion\027objc-macro-redefinition\021objc-"
    "messaging-id\022objc-method-access\037objc-missing-property-synthesis\030"
    "objc-missing-super-calls\032objc-multiple-method-names\"objc-noncopy-re"
    "tain-block-property\032objc-nonunified-exceptions#objc-property-assign-"
    "on-object-type\034objc-property-implementation\037objc-property-implici"
    "t-mismatch*objc-property-matches-cocoa-ownership-rule\032objc-property-"
    "no-attribute\027objc-property-synthesis#objc-protocol-method-implementa"
    "tion objc-protocol-property-synthesis\030objc-protocol-qualifiers\"objc"
    "-readonly-with-setter-property\026objc-redundant-api-use\032objc-redund"
    "ant-literal-use\017objc-root-class\025objc-signed-char-bool/objc-signed"
    "-char-bool-implicit-float-conversion-objc-signed-char-bool-implicit-int"
    "-conversion\023objc-string-compare\031objc-string-concatenation\034objc"
    "-unsafe-perform-selector\003odr\016old-style-cast\024old-style-definiti"
    "on\027opencl-unsupported-rgba\006openmp\024openmp-51-extensions\016open"
    "mp-clauses\020openmp-loop-form\016openmp-mapping\015openmp-target\016op"
    "tion-ignored!ordered-compare-function-pointers\027out-of-line-declarati"
    "on\025out-of-scope-function\014over-aligned\010overflow\022overlength-s"
    "trings\037overloaded-shift-op-parentheses\022overloaded-virtual\015over"
    "ride-init\017override-module\032overriding-method-mismatch\023overridin"
    "g-t-option\006packed\016packed-non-pod\006padded\013parentheses\024pare"
    "ntheses-equality\024partial-availability\004pass\015pass-analysis\013pa"
    "ss-failed\013pass-missed\015pch-date-time\010pedantic\026pedantic-core-"
    "features\017pedantic-macros\020pessimizing-move\015pointer-arith\027poi"
    "nter-bool-conversion\017pointer-compare\027pointer-integer-compare\014p"
    "ointer-sign\024pointer-to-enum-cast\023pointer-to-int-cast\025pointer-t"
    "ype-mismatch\031poison-system-directories\033potentially-direct-selecto"
    "r potentially-evaluated-expression\026pragma-clang-attribute\032pragma-"
    "once-outside-header\013pragma-pack\036pragma-pack-suspicious-include#pr"
    "agma-system-header-outside-header\007pragmas\020pre-c++14-compat\031pre"
    "-c++14-compat-pedantic\020pre-c++17-compat\031pre-c++17-compat-pedantic"
    "\020pre-c++20-compat\031pre-c++20-compat-pedantic\020pre-c++23-compat\031"
    "pre-c++23-compat-pedantic\020pre-c++26-compat\031pre-c++26-compat-pedan"
    "tic\020pre-c++2c-compat\031pre-c++2c-compat-pedantic\016pre-c2x-compat\027"
    "pre-c2x-compat-pedantic\024pre-openmp-51-compat&predefined-identifier-o"
    "utside-function\016private-extern\016private-header\016private-module\025"
    "profile-instr-missing\031profile-instr-out-of-date\030profile-instr-unp"
    "rofiled\032property-access-dot-syntax\033property-attribute-mismatch\010"
    "protocol%protocol-property-synthesis-ambiguity\005psabi\032qualified-vo"
    "id-return-type\"quoted-include-in-framework-header\023range-loop-analys"
    "is\031range-loop-bind-reference\024range-loop-construct\027read-modules"
    "-implicitly\017read-only-types\032readonly-iboutlet-property\015receive"
    "r-expr\026receiver-forward-class\027redeclared-class-member\026redundan"
    "t-consteval-if\017redundant-decls\016redundant-move\020redundant-parens"
    "\010register\026reinterpret-base-class\025remark-backend-plugin\007reor"
    "der\014reorder-ctor\021reorder-init-list\030requires-super-attribute\021"
    "reserved-id-macro\023reserved-identifier\031reserved-macro-identifier\032"
    "reserved-module-identifier\035reserved-user-defined-literal\022restrict"
    "-expansion\031retained-language-linkage\021return-local-addr\024return-"
    "stack-address\017return-std-move\013return-type\025return-type-c-linkag"
    "e\020rewrite-not-bool\023round-trip-cc1-args\004rtti\020sanitize-addres"
    "s\025sarif-format-unstable\021search-path-usage\007section\010selector\026"
    "selector-type-mismatch\013self-assign\021self-assign-field\026self-assi"
    "gn-overloaded\tself-move\034semicolon-before-method-body\010sentinel\016"
    "sequence-point\026serialized-diagnostics\006shadow\nshadow-all\014shado"
    "w-field\033shadow-field-in-constructor$shadow-field-in-constructor-modi"
    "fied\013shadow-ivar\027shadow-uncaptured-local\024shift-count-negative\024"
    "shift-count-overflow\024shift-negative-value\024shift-op-parentheses\016"
    "shift-overflow\023shift-sign-overflow\020shorten-64-to-32\014sign-compa"
    "re\017sign-conversion\nsign-promo\024signed-enum-bitfield\025signed-uns"
    "igned-wchar'single-bit-bitfield-constant-conversion\025sizeof-array-arg"
    "ument\022sizeof-array-decay\020sizeof-array-div\022sizeof-pointer-div\030"
    "sizeof-pointer-memaccess\020slash-u-filename\014slh-asm-goto\nsloc-usag"
    "e\027sometimes-uninitialized\nsource-mgr\022source-uses-openmp\013spir-"
    "compat\014spirv-compat\017stack-exhausted\017stack-protector\021static-"
    "float-init\020static-in-inline$static-inline-explicit-instantiation\026"
    "static-local-in-inline\020static-self-init\023stdlibcxx-not-found\017st"
    "rict-aliasing\021strict-aliasing=0\021strict-aliasing=1\021strict-alias"
    "ing=2\017strict-overflow\021strict-overflow=0\021strict-overflow=1\021s"
    "trict-overflow=2\021strict-overflow=3\021strict-overflow=4\021strict-ov"
    "erflow=5\"strict-potentially-direct-selector\021strict-prototypes\025st"
    "rict-selector-match\016string-compare\024string-concatenation\021string"
    "-conversion\020string-plus-char\017string-plus-int\024strlcpy-strlcat-s"
    "ize\014strncat-size\033suggest-destructor-override\020suggest-override\033"
    "super-class-method-mismatch\020suspicious-bzero\024suspicious-memaccess"
    "\024swift-name-attribute\006switch\013switch-bool\016switch-default\013"
    "switch-enum\016sync-alignment%sync-fetch-and-nand-semantics-changed\005"
    "synth\036target-clones-mixed-specifiers\034tautological-bitwise-compare"
    "\024tautological-compare\035tautological-constant-compare&tautological-"
    "constant-in-range-compare*tautological-constant-out-of-range-compare\036"
    "tautological-objc-bool-compare\034tautological-overlap-compare\034tauto"
    "logical-pointer-compare\037tautological-type-limit-compare\036tautologi"
    "cal-undefined-compare'tautological-unsigned-char-zero-compare'tautologi"
    "cal-unsigned-enum-zero-compare\"tautological-unsigned-zero-compare taut"
    "ological-value-range-compare\017tcb-enforcement$tentative-definition-in"
    "complete-type\015thread-safety\026thread-safety-analysis\030thread-safe"
    "ty-attributes\022thread-safety-beta\026thread-safety-negative\025thread"
    "-safety-precise\027thread-safety-reference\025thread-safety-verbose\ttr"
    "igraphs\013type-limits\013type-safety\024typedef-redefinition\020typena"
    "me-missing\031unable-to-open-stats-file\020unaligned-access!unaligned-q"
    "ualifier-implicit-cast\030unavailable-declarations\023undeclared-select"
    "or\005undef\014undef-prefix\031undefined-bool-conversion\027undefined-f"
    "unc-template\020undefined-inline\022undefined-internal\027undefined-int"
    "ernal-type\032undefined-reinterpret-cast\026undefined-var-template\035u"
    "nderaligned-exception-object\026unevaluated-expression\026unguarded-ava"
    "ilability\032unguarded-availability-new\007unicode\021unicode-homoglyph"
    "\022unicode-whitespace\022unicode-zero-width\015uninitialized\035uninit"
    "ialized-const-reference\020unknown-argument\022unknown-assumption\022un"
    "known-attributes\024unknown-cuda-version\022unknown-directives\027unkno"
    "wn-escape-sequence\017unknown-pragmas\022unknown-sanitizers\026unknown-"
    "warning-option\032unnamed-type-template-args\035unneeded-internal-decla"
    "ration\030unneeded-member-function\031unqualified-std-cast-call\020unre"
    "achable-code\033unreachable-code-aggressive\026unreachable-code-break\034"
    "unreachable-code-fallthrough\036unreachable-code-generic-assoc\037unrea"
    "chable-code-loop-increment\027unreachable-code-return\023unsafe-buffer-"
    "usage\013unsequenced\017unsupported-abi\017unsupported-abs\036unsupport"
    "ed-availability-guard\016unsupported-cb#unsupported-dll-base-class-temp"
    "late\036unsupported-floating-point-opt\022unsupported-friend\021unsuppo"
    "rted-gpopt\017unsupported-nan\026unsupported-target-opt\026unsupported-"
    "visibility\037unusable-partial-specialization\006unused\017unused-argum"
    "ent\030unused-but-set-parameter\027unused-but-set-variable\034unused-co"
    "mmand-line-argument\021unused-comparison\025unused-const-variable\032un"
    "used-exception-parameter\017unused-function\032unused-getter-return-val"
    "ue\014unused-label\025unused-lambda-capture\024unused-local-typedef\025"
    "unused-local-typedefs\015unused-macros\026unused-member-function\020unu"
    "sed-parameter\024unused-private-field\024unused-property-ivar\015unused"
    "-result\017unused-template\014unused-value\017unused-variable\026unused"
    "-volatile-lvalue\026used-but-marked-unused\025user-defined-literals\025"
    "user-defined-warnings\007varargs\017variadic-macros\015vec-elem-size\021"
    "vector-conversion\022vector-conversions\014vexing-parse\nvisibility\003"
    "vla\015vla-extension\031void-pointer-to-enum-cast\030void-pointer-to-in"
    "t-cast\024void-ptr-dereference\025volatile-register-var\023wasm-excepti"
    "on-spec\025weak-template-vtables\014weak-vtables\020writable-strings\015"
    "write-strings\017xor-used-as-pow\035zero-as-null-pointer-constant\021ze"
    "ro-length-array"};

#endif // GET_DIAG_ARRAYS


#ifdef DIAG_ENTRY
DIAG_ENTRY(anonymous_58 /*  */, 0, 0, /* DiagSubGroup0 */ 1, R"()")
DIAG_ENTRY(PoundPragmaMessage /* #pragma-messages */, 1, /* DiagArray1 */ 1, 0, R"()")
DIAG_ENTRY(PoundWarning /* #warnings */, 18, /* DiagArray2 */ 3, 0, R"()")
DIAG_ENTRY(anonymous_269 /* CFString-literal */, 28, /* DiagArray3 */ 5, 0, R"()")
DIAG_ENTRY(anonymous_57 /* CL4 */, 45, 0, /* DiagSubGroup4 */ 3, R"()")
DIAG_ENTRY(IndependentClassAttribute /* IndependentClass-attribute */, 49, /* DiagArray5 */ 7, 0, R"()")
DIAG_ENTRY(NSobjectAttribute /* NSObject-attribute */, 76, /* DiagArray6 */ 10, 0, R"()")
DIAG_ENTRY(anonymous_0 /* abi */, 95, 0, 0, R"()")
DIAG_ENTRY(AbsoluteValue /* absolute-value */, 99, /* DiagArray8 */ 12, 0, R"()")
DIAG_ENTRY(AbstractFinalClass /* abstract-final-class */, 114, /* DiagArray9 */ 17, 0, R"()")
DIAG_ENTRY(anonymous_262 /* abstract-vbase-init */, 135, /* DiagArray10 */ 19, 0, R"()")
DIAG_ENTRY(anonymous_56 /* address */, 155, 0, /* DiagSubGroup11 */ 6, R"()")
DIAG_ENTRY(anonymous_240 /* address-of-packed-member */, 163, /* DiagArray12 */ 21, 0, R"()")
DIAG_ENTRY(AddressOfTemporary /* address-of-temporary */, 188, /* DiagArray13 */ 23, 0, R"()")
DIAG_ENTRY(anonymous_2 /* aggregate-return */, 209, 0, 0, R"()")
DIAG_ENTRY(AIXCompat /* aix-compat */, 226, /* DiagArray15 */ 25, 0, R"()")
DIAG_ENTRY(anonymous_241 /* align-mismatch */, 237, /* DiagArray16 */ 28, 0, R"()")
DIAG_ENTRY(All /* all */, 252, 0, /* DiagSubGroup17 */ 10, R"()")
DIAG_ENTRY(anonymous_186 /* alloca */, 256, /* DiagArray18 */ 30, 0, R"()")
DIAG_ENTRY(anonymous_187 /* alloca-with-align-alignof */, 263, /* DiagArray19 */ 32, 0, R"()")
DIAG_ENTRY(AlwaysInlineCoroutine /* always-inline-coroutine */, 289, /* DiagArray20 */ 34, 0, R"()")
DIAG_ENTRY(anonymous_247 /* ambiguous-delete */, 313, /* DiagArray21 */ 36, 0, R"()")
DIAG_ENTRY(anonymous_141 /* ambiguous-ellipsis */, 330, /* DiagArray22 */ 38, 0, R"()")
DIAG_ENTRY(AmbiguousMacro /* ambiguous-macro */, 349, /* DiagArray23 */ 40, 0, R"()")
DIAG_ENTRY(AmbigMemberTemplate /* ambiguous-member-template */, 365, /* DiagArray24 */ 42, 0, R"()")
DIAG_ENTRY(anonymous_207 /* ambiguous-reversed-operator */, 391, /* DiagArray25 */ 44, 0, R"()")
DIAG_ENTRY(anonymous_98 /* analyzer-incompatible-plugin */, 419, /* DiagArray26 */ 46, 0, R"()")
DIAG_ENTRY(AnonEnumEnumConversion /* anon-enum-enum-conversion */, 448, /* DiagArray27 */ 48, /* DiagSubGroup27 */ 17, R"()")
DIAG_ENTRY(anonymous_142 /* anonymous-pack-parens */, 474, /* DiagArray28 */ 50, 0, R"()")
DIAG_ENTRY(AutomaticReferenceCounting /* arc */, 496, 0, /* DiagSubGroup29 */ 19, R"()")
DIAG_ENTRY(anonymous_140 /* arc-bridge-casts-disallowed-in-nonarc */, 500, /* DiagArray30 */ 52, 0, R"()")
DIAG_ENTRY(ARCRepeatedUseOfWeakMaybe /* arc-maybe-repeated-use-of-weak */, 538, /* DiagArray31 */ 54, 0, R"()")
DIAG_ENTRY(ARCNonPodMemAccess /* arc-non-pod-memaccess */, 569, /* DiagArray32 */ 56, 0, R"()")
DIAG_ENTRY(anonymous_170 /* arc-performSelector-leaks */, 591, /* DiagArray33 */ 58, 0, R"()")
DIAG_ENTRY(ARCRepeatedUseOfWeak /* arc-repeated-use-of-weak */, 617, /* DiagArray34 */ 60, /* DiagSubGroup34 */ 23, R"()")
DIAG_ENTRY(ARCRetainCycles /* arc-retain-cycles */, 642, /* DiagArray35 */ 62, 0, R"()")
DIAG_ENTRY(ARCUnsafeRetainedAssign /* arc-unsafe-retained-assign */, 660, /* DiagArray36 */ 64, 0, R"()")
DIAG_ENTRY(anonymous_271 /* argument-outside-range */, 687, /* DiagArray37 */ 68, 0, R"()")
DIAG_ENTRY(anonymous_272 /* argument-undefined-behaviour */, 710, /* DiagArray38 */ 70, 0, R"()")
DIAG_ENTRY(ArrayBounds /* array-bounds */, 739, /* DiagArray39 */ 72, 0, R"()")
DIAG_ENTRY(ArrayBoundsPointerArithmetic /* array-bounds-pointer-arithmetic */, 752, /* DiagArray40 */ 78, 0, R"()")
DIAG_ENTRY(ArrayParameter /* array-parameter */, 784, /* DiagArray41 */ 81, 0, R"()")
DIAG_ENTRY(ASM /* asm */, 800, 0, /* DiagSubGroup42 */ 25, R"()")
DIAG_ENTRY(ASMOperandWidths /* asm-operand-widths */, 804, /* DiagArray43 */ 83, 0, R"()")
DIAG_ENTRY(anonymous_270 /* assign-enum */, 823, /* DiagArray44 */ 85, 0, R"()")
DIAG_ENTRY(anonymous_157 /* assume */, 835, /* DiagArray45 */ 87, 0, R"()")
DIAG_ENTRY(anonymous_55 /* at-protocol */, 842, 0, 0, R"()")
DIAG_ENTRY(FrameworkHdrAtImport /* atimport-in-framework-header */, 854, /* DiagArray47 */ 89, 0, R"()")
DIAG_ENTRY(anonymous_229 /* atomic-access */, 883, /* DiagArray48 */ 91, 0, R"()")
DIAG_ENTRY(AtomicAlignment /* atomic-alignment */, 897, /* DiagArray49 */ 93, 0, R"()")
DIAG_ENTRY(anonymous_255 /* atomic-implicit-seq-cst */, 914, /* DiagArray50 */ 96, 0, R"()")
DIAG_ENTRY(anonymous_254 /* atomic-memory-ordering */, 938, /* DiagArray51 */ 98, 0, R"()")
DIAG_ENTRY(AtomicProperties /* atomic-properties */, 961, 0, /* DiagSubGroup52 */ 27, R"()")
DIAG_ENTRY(anonymous_165 /* atomic-property-with-user-defined-accessor */, 979, /* DiagArray53 */ 100, 0, R"()")
DIAG_ENTRY(anonymous_203 /* attribute-packed-for-bitfield */, 1022, /* DiagArray54 */ 102, 0, R"()")
DIAG_ENTRY(BackendWarningAttributes /* attribute-warning */, 1052, /* DiagArray55 */ 104, 0, R"()")
DIAG_ENTRY(Attributes /* attributes */, 1070, 0, /* DiagSubGroup56 */ 30, R"()")
DIAG_ENTRY(AutoDisableVptrSanitizer /* auto-disable-vptr-sanitizer */, 1081, /* DiagArray57 */ 106, 0, R"()")
DIAG_ENTRY(anonymous_3 /* auto-import */, 1109, 0, 0, R"()")
DIAG_ENTRY(anonymous_138 /* auto-storage-class */, 1121, /* DiagArray59 */ 108, 0, R"()")
DIAG_ENTRY(anonymous_183 /* auto-var-id */, 1140, /* DiagArray60 */ 110, 0, R"()")
DIAG_ENTRY(Availability /* availability */, 1152, /* DiagArray61 */ 112, 0, R"()")
DIAG_ENTRY(AVRRtlibLinkingQuirks /* avr-rtlib-linking-quirks */, 1165, /* DiagArray62 */ 123, 0, R"()")
DIAG_ENTRY(BackendPlugin /* backend-plugin */, 1190, /* DiagArray63 */ 129, 0, R"()")
DIAG_ENTRY(anonymous_101 /* backslash-newline-escape */, 1205, /* DiagArray64 */ 132, 0, R"()")
DIAG_ENTRY(BadFunctionCast /* bad-function-cast */, 1230, /* DiagArray65 */ 134, 0, R"()")
DIAG_ENTRY(BinaryLiteral /* binary-literal */, 1248, 0, /* DiagSubGroup66 */ 33, R"()")
DIAG_ENTRY(BindToTemporaryCopy /* bind-to-temporary-copy */, 1263, /* DiagArray67 */ 136, /* DiagSubGroup67 */ 37, R"()")
DIAG_ENTRY(anonymous_152 /* binding-in-condition */, 1286, /* DiagArray68 */ 139, 0, R"()")
DIAG_ENTRY(anonymous_145 /* bit-int-extension */, 1307, /* DiagArray69 */ 141, 0, R"()")
DIAG_ENTRY(BitFieldConstantConversion /* bitfield-constant-conversion */, 1325, /* DiagArray70 */ 143, /* DiagSubGroup70 */ 39, R"()")
DIAG_ENTRY(BitFieldEnumConversion /* bitfield-enum-conversion */, 1354, /* DiagArray71 */ 145, 0, R"()")
DIAG_ENTRY(BitFieldWidth /* bitfield-width */, 1379, /* DiagArray72 */ 149, 0, R"()")
DIAG_ENTRY(BitwiseConditionalParentheses /* bitwise-conditional-parentheses */, 1394, /* DiagArray73 */ 151, 0, R"()")
DIAG_ENTRY(BitwiseInsteadOfLogical /* bitwise-instead-of-logical */, 1426, /* DiagArray74 */ 153, 0, R"()")
DIAG_ENTRY(BitwiseOpParentheses /* bitwise-op-parentheses */, 1453, /* DiagArray75 */ 155, 0, R"()")
DIAG_ENTRY(BlockCaptureAutoReleasing /* block-capture-autoreleasing */, 1476, /* DiagArray76 */ 157, 0, R"()")
DIAG_ENTRY(BoolConversion /* bool-conversion */, 1504, /* DiagArray77 */ 159, /* DiagSubGroup77 */ 41, R"()")
DIAG_ENTRY(anonymous_63 /* bool-conversions */, 1520, 0, /* DiagSubGroup78 */ 44, R"()")
DIAG_ENTRY(BoolOperation /* bool-operation */, 1537, /* DiagArray79 */ 161, /* DiagSubGroup79 */ 46, R"()")
DIAG_ENTRY(anonymous_224 /* braced-scalar-init */, 1552, /* DiagArray80 */ 163, 0, R"()")
DIAG_ENTRY(BranchProtection /* branch-protection */, 1571, /* DiagArray81 */ 165, 0, R"()")
DIAG_ENTRY(ObjCBridge /* bridge-cast */, 1589, /* DiagArray82 */ 170, 0, R"()")
DIAG_ENTRY(anonymous_189 /* builtin-assume-aligned-alignment */, 1601, /* DiagArray83 */ 173, 0, R"()")
DIAG_ENTRY(BuiltinMacroRedefined /* builtin-macro-redefined */, 1634, /* DiagArray84 */ 175, 0, R"()")
DIAG_ENTRY(anonymous_158 /* builtin-memcpy-chk-size */, 1658, /* DiagArray85 */ 178, 0, R"()")
DIAG_ENTRY(BuiltinRequiresHeader /* builtin-requires-header */, 1682, /* DiagArray86 */ 180, 0, R"()")
DIAG_ENTRY(CXXCompat /* c++-compat */, 1706, /* DiagArray87 */ 182, 0, R"()")
DIAG_ENTRY(anonymous_22 /* c++0x-compat */, 1717, 0, /* DiagSubGroup88 */ 48, R"()")
DIAG_ENTRY(anonymous_67 /* c++0x-extensions */, 1730, 0, /* DiagSubGroup89 */ 50, R"()")
DIAG_ENTRY(anonymous_20 /* c++0x-narrowing */, 1747, 0, /* DiagSubGroup90 */ 52, R"()")
DIAG_ENTRY(CXX11Compat /* c++11-compat */, 1763, /* DiagArray91 */ 184, /* DiagSubGroup91 */ 54, R"()")
DIAG_ENTRY(CXX11CompatDeprecatedWritableStr /* c++11-compat-deprecated-writable-strings */, 1776, /* DiagArray92 */ 195, 0, R"()")
DIAG_ENTRY(CXX11CompatPedantic /* c++11-compat-pedantic */, 1817, 0, /* DiagSubGroup93 */ 62, R"()")
DIAG_ENTRY(CXX11CompatReservedUserDefinedLiteral /* c++11-compat-reserved-user-defined-literal */, 1839, /* DiagArray94 */ 197, 0, R"()")
DIAG_ENTRY(CXX11 /* c++11-extensions */, 1882, /* DiagArray95 */ 199, /* DiagSubGroup95 */ 68, R"()")
DIAG_ENTRY(CXX11ExtraSemi /* c++11-extra-semi */, 1899, /* DiagArray96 */ 226, 0, R"()")
DIAG_ENTRY(CXX11InlineNamespace /* c++11-inline-namespace */, 1916, /* DiagArray97 */ 228, 0, R"()")
DIAG_ENTRY(CXX11LongLong /* c++11-long-long */, 1939, /* DiagArray98 */ 230, 0, R"()")
DIAG_ENTRY(CXX11Narrowing /* c++11-narrowing */, 1955, /* DiagArray99 */ 232, 0, R"()")
DIAG_ENTRY(CXX14Attrs /* c++14-attribute-extensions */, 1971, /* DiagArray100 */ 240, 0, R"()")
DIAG_ENTRY(CXX14BinaryLiteral /* c++14-binary-literal */, 1998, /* DiagArray101 */ 242, 0, R"()")
DIAG_ENTRY(CXX14Compat /* c++14-compat */, 2019, 0, /* DiagSubGroup102 */ 72, R"()")
DIAG_ENTRY(CXX14CompatPedantic /* c++14-compat-pedantic */, 2032, 0, /* DiagSubGroup103 */ 76, R"()")
DIAG_ENTRY(CXX14 /* c++14-extensions */, 2054, /* DiagArray104 */ 244, /* DiagSubGroup104 */ 81, R"()")
DIAG_ENTRY(CXX17Attrs /* c++17-attribute-extensions */, 2071, /* DiagArray105 */ 252, 0, R"()")
DIAG_ENTRY(CXX17Compat /* c++17-compat */, 2098, 0, /* DiagSubGroup106 */ 84, R"()")
DIAG_ENTRY(CXX17CompatMangling /* c++17-compat-mangling */, 2111, /* DiagArray107 */ 254, 0, R"()")
DIAG_ENTRY(CXX17CompatPedantic /* c++17-compat-pedantic */, 2133, 0, /* DiagSubGroup108 */ 90, R"()")
DIAG_ENTRY(CXX17 /* c++17-extensions */, 2155, /* DiagArray109 */ 256, /* DiagSubGroup109 */ 94, R"()")
DIAG_ENTRY(anonymous_68 /* c++1y-extensions */, 2172, 0, /* DiagSubGroup110 */ 96, R"()")
DIAG_ENTRY(anonymous_23 /* c++1z-compat */, 2189, 0, /* DiagSubGroup111 */ 98, R"()")
DIAG_ENTRY(anonymous_11 /* c++1z-compat-mangling */, 2202, 0, /* DiagSubGroup112 */ 100, R"()")
DIAG_ENTRY(anonymous_69 /* c++1z-extensions */, 2224, 0, /* DiagSubGroup113 */ 102, R"()")
DIAG_ENTRY(CXX20Attrs /* c++20-attribute-extensions */, 2241, /* DiagArray114 */ 274, 0, R"()")
DIAG_ENTRY(CXX20Compat /* c++20-compat */, 2268, /* DiagArray115 */ 276, /* DiagSubGroup115 */ 104, R"()")
DIAG_ENTRY(CXX20CompatPedantic /* c++20-compat-pedantic */, 2281, 0, /* DiagSubGroup116 */ 106, R"()")
DIAG_ENTRY(CXX20Designator /* c++20-designator */, 2303, /* DiagArray117 */ 286, 0, R"()")
DIAG_ENTRY(CXX20 /* c++20-extensions */, 2320, /* DiagArray118 */ 288, /* DiagSubGroup118 */ 109, R"()")
DIAG_ENTRY(anonymous_267 /* c++23-default-comp-relaxed-constexpr */, 2337, /* DiagArray119 */ 310, 0, R"()")
DIAG_ENTRY(CXX23 /* c++23-extensions */, 2374, /* DiagArray120 */ 312, 0, R"()")
DIAG_ENTRY(CXX26 /* c++26-extensions */, 2391, 0, 0, R"()")
DIAG_ENTRY(anonymous_24 /* c++2a-compat */, 2408, 0, /* DiagSubGroup122 */ 112, R"()")
DIAG_ENTRY(anonymous_25 /* c++2a-compat-pedantic */, 2421, 0, /* DiagSubGroup123 */ 114, R"()")
DIAG_ENTRY(anonymous_70 /* c++2a-extensions */, 2443, 0, /* DiagSubGroup124 */ 116, R"()")
DIAG_ENTRY(anonymous_71 /* c++2b-extensions */, 2460, 0, /* DiagSubGroup125 */ 118, R"()")
DIAG_ENTRY(anonymous_72 /* c++2c-extensions */, 2477, 0, /* DiagSubGroup126 */ 120, R"()")
DIAG_ENTRY(anonymous_16 /* c++98-c++11-c++14-c++17-compat */, 2494, 0, /* DiagSubGroup127 */ 122, R"()")
DIAG_ENTRY(anonymous_17 /* c++98-c++11-c++14-c++17-compat-pedantic */, 2525, 0, /* DiagSubGroup128 */ 124, R"()")
DIAG_ENTRY(anonymous_14 /* c++98-c++11-c++14-compat */, 2565, 0, /* DiagSubGroup129 */ 126, R"()")
DIAG_ENTRY(anonymous_15 /* c++98-c++11-c++14-compat-pedantic */, 2590, 0, /* DiagSubGroup130 */ 128, R"()")
DIAG_ENTRY(anonymous_12 /* c++98-c++11-compat */, 2624, 0, /* DiagSubGroup131 */ 130, R"()")
DIAG_ENTRY(CXXPre14CompatBinaryLiteral /* c++98-c++11-compat-binary-literal */, 2643, /* DiagArray132 */ 324, 0, R"()")
DIAG_ENTRY(anonymous_13 /* c++98-c++11-compat-pedantic */, 2677, 0, /* DiagSubGroup133 */ 132, R"()")
DIAG_ENTRY(CXX98Compat /* c++98-compat */, 2705, /* DiagArray134 */ 326, /* DiagSubGroup134 */ 134, R"()")
DIAG_ENTRY(CXX98CompatBindToTemporaryCopy /* c++98-compat-bind-to-temporary-copy */, 2718, /* DiagArray135 */ 386, 0, R"()")
DIAG_ENTRY(CXX98CompatExtraSemi /* c++98-compat-extra-semi */, 2754, /* DiagArray136 */ 388, 0, R"()")
DIAG_ENTRY(CXX98CompatLocalTypeTemplateArgs /* c++98-compat-local-type-template-args */, 2778, /* DiagArray137 */ 390, 0, R"()")
DIAG_ENTRY(CXX98CompatPedantic /* c++98-compat-pedantic */, 2816, /* DiagArray138 */ 392, /* DiagSubGroup138 */ 141, R"()")
DIAG_ENTRY(CXX98CompatUnnamedTypeTemplateArgs /* c++98-compat-unnamed-type-template-args */, 2838, /* DiagArray139 */ 402, 0, R"()")
DIAG_ENTRY(C11 /* c11-extensions */, 2878, /* DiagArray140 */ 404, 0, R"()")
DIAG_ENTRY(C2xCompat /* c2x-compat */, 2893, /* DiagArray141 */ 409, 0, R"()")
DIAG_ENTRY(C2x /* c2x-extensions */, 2904, /* DiagArray142 */ 411, 0, R"()")
DIAG_ENTRY(C99Compat /* c99-compat */, 2919, /* DiagArray143 */ 420, 0, R"()")
DIAG_ENTRY(C99Designator /* c99-designator */, 2930, /* DiagArray144 */ 425, /* DiagSubGroup144 */ 149, R"()")
DIAG_ENTRY(C99 /* c99-extensions */, 2945, /* DiagArray145 */ 431, /* DiagSubGroup145 */ 151, R"()")
DIAG_ENTRY(PureVirtualCallFromCtorDtor /* call-to-pure-virtual-from-ctor-dtor */, 2960, /* DiagArray146 */ 442, 0, R"()")
DIAG_ENTRY(CalledOnceParameter /* called-once-parameter */, 2996, /* DiagArray147 */ 444, /* DiagSubGroup147 */ 153, R"()")
DIAG_ENTRY(CastAlign /* cast-align */, 3018, /* DiagArray148 */ 448, 0, R"()")
DIAG_ENTRY(anonymous_257 /* cast-calling-convention */, 3029, /* DiagArray149 */ 450, 0, R"()")
DIAG_ENTRY(CastFunctionType /* cast-function-type */, 3053, /* DiagArray150 */ 452, /* DiagSubGroup150 */ 155, R"()")
DIAG_ENTRY(CastFunctionTypeStrict /* cast-function-type-strict */, 3072, /* DiagArray151 */ 454, 0, R"()")
DIAG_ENTRY(SelTypeCast /* cast-of-sel-type */, 3098, /* DiagArray152 */ 456, 0, R"()")
DIAG_ENTRY(CastQual /* cast-qual */, 3115, /* DiagArray153 */ 458, 0, R"()")
DIAG_ENTRY(anonymous_245 /* cast-qual-unrelated */, 3125, /* DiagArray154 */ 461, 0, R"()")
DIAG_ENTRY(anonymous_4 /* char-align */, 3145, 0, 0, R"()")
DIAG_ENTRY(CharSubscript /* char-subscripts */, 3156, /* DiagArray156 */ 463, 0, R"()")
DIAG_ENTRY(ClangClPch /* clang-cl-pch */, 3172, /* DiagArray157 */ 466, 0, R"()")
DIAG_ENTRY(ClassConversion /* class-conversion */, 3185, /* DiagArray158 */ 471, 0, R"()")
DIAG_ENTRY(ClassVarargs /* class-varargs */, 3202, /* DiagArray159 */ 475, /* DiagSubGroup159 */ 157, R"()")
DIAG_ENTRY(anonymous_190 /* cmse-union-leak */, 3216, /* DiagArray160 */ 477, 0, R"()")
DIAG_ENTRY(anonymous_147 /* comma */, 3232, /* DiagArray161 */ 479, 0, R"()")
DIAG_ENTRY(Comment /* comment */, 3238, /* DiagArray162 */ 481, 0, R"()")
DIAG_ENTRY(anonymous_61 /* comments */, 3246, 0, /* DiagSubGroup163 */ 159, R"()")
DIAG_ENTRY(CompareDistinctPointerType /* compare-distinct-pointer-types */, 3255, /* DiagArray164 */ 486, 0, R"()")
DIAG_ENTRY(CompletionHandler /* completion-handler */, 3286, /* DiagArray165 */ 488, 0, R"()")
DIAG_ENTRY(anonymous_226 /* complex-component-init */, 3305, /* DiagArray166 */ 492, 0, R"()")
DIAG_ENTRY(CompoundTokenSplit /* compound-token-split */, 3328, 0, /* DiagSubGroup167 */ 161, R"()")
DIAG_ENTRY(CompoundTokenSplitByMacro /* compound-token-split-by-macro */, 3349, /* DiagArray168 */ 494, 0, R"()")
DIAG_ENTRY(CompoundTokenSplitBySpace /* compound-token-split-by-space */, 3379, /* DiagArray169 */ 496, 0, R"()")
DIAG_ENTRY(anonymous_259 /* conditional-type-mismatch */, 3409, /* DiagArray170 */ 498, 0, R"()")
DIAG_ENTRY(UninitializedMaybe /* conditional-uninitialized */, 3435, /* DiagArray171 */ 500, 0, R"()")
DIAG_ENTRY(ConfigMacros /* config-macros */, 3461, /* DiagArray172 */ 502, 0, R"()")
DIAG_ENTRY(ConstantConversion /* constant-conversion */, 3475, /* DiagArray173 */ 504, /* DiagSubGroup173 */ 164, R"()")
DIAG_ENTRY(anonymous_79 /* constant-evaluated */, 3495, /* DiagArray174 */ 506, 0, R"()")
DIAG_ENTRY(anonymous_236 /* constant-logical-operand */, 3514, /* DiagArray175 */ 508, 0, R"()")
DIAG_ENTRY(anonymous_181 /* constexpr-not-const */, 3539, /* DiagArray176 */ 510, 0, R"()")
DIAG_ENTRY(Consumed /* consumed */, 3559, /* DiagArray177 */ 512, 0, R"()")
DIAG_ENTRY(Conversion /* conversion */, 3568, /* DiagArray178 */ 521, /* DiagSubGroup178 */ 167, R"()")
DIAG_ENTRY(anonymous_62 /* conversion-null */, 3579, 0, /* DiagSubGroup179 */ 183, R"()")
DIAG_ENTRY(CoroNonAlignedAllocationFunction /* coro-non-aligned-allocation-function */, 3595, /* DiagArray180 */ 527, 0, R"()")
DIAG_ENTRY(Coroutine /* coroutine */, 3632, /* DiagArray181 */ 529, /* DiagSubGroup181 */ 185, R"()")
DIAG_ENTRY(CoroutineMissingUnhandledException /* coroutine-missing-unhandled-exception */, 3642, /* DiagArray182 */ 531, 0, R"()")
DIAG_ENTRY(CoveredSwitchDefault /* covered-switch-default */, 3680, /* DiagArray183 */ 533, 0, R"()")
DIAG_ENTRY(anonymous_60 /* cpp */, 3703, 0, /* DiagSubGroup184 */ 190, R"()")
DIAG_ENTRY(ObjCCStringFormat /* cstring-format-directive */, 3707, /* DiagArray185 */ 535, 0, R"()")
DIAG_ENTRY(CTADMaybeUnsupported /* ctad-maybe-unsupported */, 3732, /* DiagArray186 */ 537, 0, R"()")
DIAG_ENTRY(anonymous_5 /* ctor-dtor-privacy */, 3755, 0, 0, R"()")
DIAG_ENTRY(CrossTU /* ctu */, 3773, /* DiagArray188 */ 539, 0, R"()")
DIAG_ENTRY(CudaCompat /* cuda-compat */, 3777, /* DiagArray189 */ 541, 0, R"()")
DIAG_ENTRY(CustomAtomic /* custom-atomic-properties */, 3789, /* DiagArray190 */ 547, 0, R"()")
DIAG_ENTRY(anonymous_143 /* cxx-attribute-extension */, 3814, /* DiagArray191 */ 549, 0, R"()")
DIAG_ENTRY(Dangling /* dangling */, 3838, /* DiagArray192 */ 551, /* DiagSubGroup192 */ 192, R"()")
DIAG_ENTRY(DanglingElse /* dangling-else */, 3847, /* DiagArray193 */ 554, 0, R"()")
DIAG_ENTRY(DanglingField /* dangling-field */, 3861, /* DiagArray194 */ 556, 0, R"()")
DIAG_ENTRY(DanglingGsl /* dangling-gsl */, 3876, /* DiagArray195 */ 561, 0, R"()")
DIAG_ENTRY(DanglingInitializerList /* dangling-initializer-list */, 3889, /* DiagArray196 */ 564, 0, R"()")
DIAG_ENTRY(anonymous_92 /* darwin-sdk-settings */, 3915, /* DiagArray197 */ 566, 0, R"()")
DIAG_ENTRY(anonymous_127 /* date-time */, 3935, /* DiagArray198 */ 568, 0, R"()")
DIAG_ENTRY(DeallocInCategory /* dealloc-in-category */, 3945, /* DiagArray199 */ 570, 0, R"()")
DIAG_ENTRY(anonymous_89 /* debug-compression-unavailable */, 3965, /* DiagArray200 */ 572, 0, R"()")
DIAG_ENTRY(DeclarationAfterStatement /* declaration-after-statement */, 3995, /* DiagArray201 */ 574, 0, R"()")
DIAG_ENTRY(DefaultedFunctionDeleted /* defaulted-function-deleted */, 4023, /* DiagArray202 */ 577, 0, R"()")
DIAG_ENTRY(DelegatingCtorCycles /* delegating-ctor-cycles */, 4050, /* DiagArray203 */ 580, 0, R"()")
DIAG_ENTRY(DeleteAbstractNonVirtualDtor /* delete-abstract-non-virtual-dtor */, 4073, /* DiagArray204 */ 582, 0, R"()")
DIAG_ENTRY(DeleteIncomplete /* delete-incomplete */, 4106, /* DiagArray205 */ 584, 0, R"()")
DIAG_ENTRY(DeleteNonAbstractNonVirtualDtor /* delete-non-abstract-non-virtual-dtor */, 4124, /* DiagArray206 */ 587, 0, R"()")
DIAG_ENTRY(DeleteNonVirtualDtor /* delete-non-virtual-dtor */, 4161, 0, /* DiagSubGroup207 */ 197, R"()")
DIAG_ENTRY(anonymous_109 /* delimited-escape-sequence-extension */, 4185, /* DiagArray208 */ 589, 0, R"()")
DIAG_ENTRY(anonymous_249 /* deprecate-lax-vec-conv-all */, 4221, /* DiagArray209 */ 591, 0, R"()")
DIAG_ENTRY(Deprecated /* deprecated */, 4248, /* DiagArray210 */ 593, /* DiagSubGroup210 */ 200, R"()")
DIAG_ENTRY(anonymous_248 /* deprecated-altivec-src-compat */, 4259, /* DiagArray211 */ 602, 0, R"()")
DIAG_ENTRY(DeprecatedAnonEnumEnumConversion /* deprecated-anon-enum-enum-conversion */, 4289, /* DiagArray212 */ 604, 0, R"()")
DIAG_ENTRY(DeprecatedArrayCompare /* deprecated-array-compare */, 4326, /* DiagArray213 */ 606, 0, R"()")
DIAG_ENTRY(DeprecatedAttributes /* deprecated-attributes */, 4351, /* DiagArray214 */ 608, 0, R"()")
DIAG_ENTRY(DeprecatedBuiltins /* deprecated-builtins */, 4373, /* DiagArray215 */ 612, 0, R"()")
DIAG_ENTRY(DeprecatedCommaSubscript /* deprecated-comma-subscript */, 4393, /* DiagArray216 */ 614, 0, R"()")
DIAG_ENTRY(DeprecatedCopy /* deprecated-copy */, 4420, /* DiagArray217 */ 616, /* DiagSubGroup217 */ 223, R"()")
DIAG_ENTRY(anonymous_6 /* deprecated-copy-dtor */, 4436, 0, /* DiagSubGroup218 */ 225, R"()")
DIAG_ENTRY(DeprecatedCopyWithDtor /* deprecated-copy-with-dtor */, 4457, /* DiagArray219 */ 618, /* DiagSubGroup219 */ 227, R"()")
DIAG_ENTRY(DeprecatedCopyWithUserProvidedCopy /* deprecated-copy-with-user-provided-copy */, 4483, /* DiagArray220 */ 620, 0, R"()")
DIAG_ENTRY(DeprecatedCopyWithUserProvidedDtor /* deprecated-copy-with-user-provided-dtor */, 4523, /* DiagArray221 */ 622, 0, R"()")
DIAG_ENTRY(DeprecatedCoroutine /* deprecated-coroutine */, 4563, /* DiagArray222 */ 624, 0, R"()")
DIAG_ENTRY(DeprecatedDeclarations /* deprecated-declarations */, 4584, /* DiagArray223 */ 626, 0, R"()")
DIAG_ENTRY(DeprecatedDynamicExceptionSpec /* deprecated-dynamic-exception-spec */, 4608, /* DiagArray224 */ 633, 0, R"()")
DIAG_ENTRY(DeprecatedEnumCompare /* deprecated-enum-compare */, 4642, /* DiagArray225 */ 635, 0, R"()")
DIAG_ENTRY(DeprecatedEnumCompareConditional /* deprecated-enum-compare-conditional */, 4666, /* DiagArray226 */ 637, 0, R"()")
DIAG_ENTRY(DeprecatedEnumEnumConversion /* deprecated-enum-enum-conversion */, 4702, /* DiagArray227 */ 639, 0, R"()")
DIAG_ENTRY(DeprecatedEnumFloatConversion /* deprecated-enum-float-conversion */, 4734, /* DiagArray228 */ 641, 0, R"()")
DIAG_ENTRY(DeprecatedImplementations /* deprecated-implementations */, 4767, /* DiagArray229 */ 643, 0, R"()")
DIAG_ENTRY(DeprecatedIncrementBool /* deprecated-increment-bool */, 4794, /* DiagArray230 */ 646, 0, R"()")
DIAG_ENTRY(DeprecatedLiteralOperator /* deprecated-literal-operator */, 4820, /* DiagArray231 */ 648, 0, R"()")
DIAG_ENTRY(DeprecatedNonPrototype /* deprecated-non-prototype */, 4848, /* DiagArray232 */ 650, 0, R"()")
DIAG_ENTRY(DeprecatedObjCIsaUsage /* deprecated-objc-isa-usage */, 4873, /* DiagArray233 */ 653, 0, R"()")
DIAG_ENTRY(ObjCPointerIntrospect /* deprecated-objc-pointer-introspection */, 4899, /* DiagArray234 */ 656, /* DiagSubGroup234 */ 229, R"()")
DIAG_ENTRY(ObjCPointerIntrospectPerformSelector /* deprecated-objc-pointer-introspection-performSelector */, 4937, /* DiagArray235 */ 658, 0, R"()")
DIAG_ENTRY(DeprecatedPragma /* deprecated-pragma */, 4991, /* DiagArray236 */ 660, 0, R"()")
DIAG_ENTRY(DeprecatedRedundantConstexprStaticDef /* deprecated-redundant-constexpr-static-def */, 5009, /* DiagArray237 */ 662, 0, R"()")
DIAG_ENTRY(DeprecatedRegister /* deprecated-register */, 5051, /* DiagArray238 */ 664, 0, R"()")
DIAG_ENTRY(DeprecatedStaticAnalyzerFlag /* deprecated-static-analyzer-flag */, 5071, /* DiagArray239 */ 666, 0, R"()")
DIAG_ENTRY(DeprecatedThisCapture /* deprecated-this-capture */, 5103, /* DiagArray240 */ 669, 0, R"()")
DIAG_ENTRY(DeprecatedType /* deprecated-type */, 5127, /* DiagArray241 */ 671, 0, R"()")
DIAG_ENTRY(DeprecatedVolatile /* deprecated-volatile */, 5143, /* DiagArray242 */ 673, 0, R"()")
DIAG_ENTRY(DeprecatedWritableStr /* deprecated-writable-strings */, 5163, 0, /* DiagSubGroup243 */ 231, R"()")
DIAG_ENTRY(anonymous_276 /* direct-ivar-access */, 5191, /* DiagArray244 */ 679, 0, R"()")
DIAG_ENTRY(anonymous_118 /* disabled-macro-expansion */, 5210, /* DiagArray245 */ 681, 0, R"()")
DIAG_ENTRY(anonymous_8 /* disabled-optimization */, 5235, 0, 0, R"()")
DIAG_ENTRY(anonymous_9 /* discard-qual */, 5257, 0, 0, R"()")
DIAG_ENTRY(DistributedObjectModifiers /* distributed-object-modifiers */, 5270, /* DiagArray248 */ 683, 0, R"()")
DIAG_ENTRY(anonymous_10 /* div-by-zero */, 5299, 0, /* DiagSubGroup249 */ 233, R"()")
DIAG_ENTRY(DivZero /* division-by-zero */, 5311, /* DiagArray250 */ 686, 0, R"()")
DIAG_ENTRY(anonymous_191 /* dll-attribute-on-redeclaration */, 5328, /* DiagArray251 */ 688, 0, R"()")
DIAG_ENTRY(DllexportExplicitInstantiationDecl /* dllexport-explicit-instantiation-decl */, 5359, /* DiagArray252 */ 690, 0, R"()")
DIAG_ENTRY(anonymous_192 /* dllimport-static-field-def */, 5397, /* DiagArray253 */ 692, 0, R"()")
DIAG_ENTRY(Documentation /* documentation */, 5424, /* DiagArray254 */ 694, /* DiagSubGroup254 */ 235, R"()")
DIAG_ENTRY(DocumentationDeprecatedSync /* documentation-deprecated-sync */, 5438, /* DiagArray255 */ 715, 0, R"()")
DIAG_ENTRY(DocumentationHTML /* documentation-html */, 5468, /* DiagArray256 */ 717, 0, R"()")
DIAG_ENTRY(DocumentationPedantic /* documentation-pedantic */, 5487, /* DiagArray257 */ 722, /* DiagSubGroup257 */ 238, R"()")
DIAG_ENTRY(DocumentationUnknownCommand /* documentation-unknown-command */, 5510, /* DiagArray258 */ 724, 0, R"()")
DIAG_ENTRY(anonymous_102 /* dollar-in-identifier-extension */, 5540, /* DiagArray259 */ 727, 0, R"()")
DIAG_ENTRY(DoublePromotion /* double-promotion */, 5571, /* DiagArray260 */ 729, 0, R"()")
DIAG_ENTRY(DtorName /* dtor-name */, 5588, /* DiagArray261 */ 731, 0, R"()")
DIAG_ENTRY(anonymous_180 /* dtor-typedef */, 5598, /* DiagArray262 */ 735, 0, R"()")
DIAG_ENTRY(DuplicateDeclSpecifier /* duplicate-decl-specifier */, 5611, /* DiagArray263 */ 737, 0, R"()")
DIAG_ENTRY(anonymous_146 /* duplicate-enum */, 5636, /* DiagArray264 */ 742, 0, R"()")
DIAG_ENTRY(DuplicateArgDecl /* duplicate-method-arg */, 5651, /* DiagArray265 */ 744, 0, R"()")
DIAG_ENTRY(MethodDuplicate /* duplicate-method-match */, 5672, /* DiagArray266 */ 746, 0, R"()")
DIAG_ENTRY(anonymous_160 /* duplicate-protocol */, 5695, /* DiagArray267 */ 748, 0, R"()")
DIAG_ENTRY(DXILValidation /* dxil-validation */, 5714, /* DiagArray268 */ 750, 0, R"()")
DIAG_ENTRY(DynamicClassMemaccess /* dynamic-class-memaccess */, 5730, /* DiagArray269 */ 752, 0, R"()")
DIAG_ENTRY(DynamicExceptionSpec /* dynamic-exception-spec */, 5754, /* DiagArray270 */ 754, /* DiagSubGroup270 */ 240, R"()")
DIAG_ENTRY(anonymous_284 /* eager-load-cxx-named-modules */, 5777, /* DiagArray271 */ 756, 0, R"()")
DIAG_ENTRY(anonymous_36 /* effc++ */, 5806, 0, /* DiagSubGroup272 */ 242, R"()")
DIAG_ENTRY(anonymous_133 /* elaborated-enum-base */, 5813, /* DiagArray273 */ 758, 0, R"()")
DIAG_ENTRY(anonymous_134 /* elaborated-enum-class */, 5834, /* DiagArray274 */ 760, 0, R"()")
DIAG_ENTRY(anonymous_124 /* embedded-directive */, 5856, /* DiagArray275 */ 762, 0, R"()")
DIAG_ENTRY(EmptyBody /* empty-body */, 5875, /* DiagArray276 */ 764, 0, R"()")
DIAG_ENTRY(anonymous_139 /* empty-decomposition */, 5886, /* DiagArray277 */ 770, 0, R"()")
DIAG_ENTRY(EmptyInitStatement /* empty-init-stmt */, 5906, /* DiagArray278 */ 772, 0, R"()")
DIAG_ENTRY(anonymous_130 /* empty-translation-unit */, 5922, /* DiagArray279 */ 774, 0, R"()")
DIAG_ENTRY(anonymous_195 /* encode-type */, 5945, /* DiagArray280 */ 776, 0, R"()")
DIAG_ENTRY(anonymous_59 /* endif-labels */, 5957, 0, /* DiagSubGroup281 */ 244, R"()")
DIAG_ENTRY(EnumCompare /* enum-compare */, 5970, /* DiagArray282 */ 778, /* DiagSubGroup282 */ 246, R"()")
DIAG_ENTRY(EnumCompareConditional /* enum-compare-conditional */, 5983, /* DiagArray283 */ 780, /* DiagSubGroup283 */ 249, R"()")
DIAG_ENTRY(EnumCompareSwitch /* enum-compare-switch */, 6008, /* DiagArray284 */ 782, 0, R"()")
DIAG_ENTRY(anonymous_78 /* enum-constexpr-conversion */, 6028, /* DiagArray285 */ 784, 0, R"()")
DIAG_ENTRY(EnumConversion /* enum-conversion */, 6054, /* DiagArray286 */ 786, /* DiagSubGroup286 */ 251, R"()")
DIAG_ENTRY(EnumEnumConversion /* enum-enum-conversion */, 6070, /* DiagArray287 */ 788, /* DiagSubGroup287 */ 255, R"()")
DIAG_ENTRY(EnumFloatConversion /* enum-float-conversion */, 6091, /* DiagArray288 */ 790, /* DiagSubGroup288 */ 257, R"()")
DIAG_ENTRY(EnumTooLarge /* enum-too-large */, 6113, /* DiagArray289 */ 792, 0, R"()")
DIAG_ENTRY(Exceptions /* exceptions */, 6128, /* DiagArray290 */ 795, 0, R"()")
DIAG_ENTRY(ExcessInitializers /* excess-initializers */, 6139, /* DiagArray291 */ 799, 0, R"()")
DIAG_ENTRY(ExitTimeDestructors /* exit-time-destructors */, 6159, /* DiagArray292 */ 804, 0, R"()")
DIAG_ENTRY(ExpansionToDefined /* expansion-to-defined */, 6181, /* DiagArray293 */ 806, 0, R"()")
DIAG_ENTRY(anonymous_280 /* experimental-header-units */, 6202, /* DiagArray294 */ 809, 0, R"()")
DIAG_ENTRY(ExplicitInitializeCall /* explicit-initialize-call */, 6228, /* DiagArray295 */ 811, 0, R"()")
DIAG_ENTRY(anonymous_228 /* explicit-ownership-type */, 6253, /* DiagArray296 */ 814, 0, R"()")
DIAG_ENTRY(ExportUnnamed /* export-unnamed */, 6277, 0, 0, R"()")
DIAG_ENTRY(ExternCCompat /* extern-c-compat */, 6292, /* DiagArray298 */ 816, 0, R"()")
DIAG_ENTRY(anonymous_223 /* extern-initializer */, 6308, /* DiagArray299 */ 818, 0, R"()")
DIAG_ENTRY(Extra /* extra */, 6327, /* DiagArray300 */ 820, /* DiagSubGroup300 */ 259, R"()")
DIAG_ENTRY(anonymous_237 /* extra-qualification */, 6333, /* DiagArray301 */ 822, 0, R"()")
DIAG_ENTRY(ExtraSemi /* extra-semi */, 6353, /* DiagArray302 */ 824, /* DiagSubGroup302 */ 274, R"()")
DIAG_ENTRY(ExtraSemiStmt /* extra-semi-stmt */, 6364, /* DiagArray303 */ 827, /* DiagSubGroup303 */ 277, R"()")
DIAG_ENTRY(ExtraTokens /* extra-tokens */, 6380, /* DiagArray304 */ 829, 0, R"()")
DIAG_ENTRY(FinalDtorNonFinalClass /* final-dtor-non-final-class */, 6393, /* DiagArray305 */ 832, 0, R"()")
DIAG_ENTRY(FinalMacro /* final-macro */, 6420, /* DiagArray306 */ 834, 0, R"()")
DIAG_ENTRY(anonymous_132 /* fixed-enum-extension */, 6432, /* DiagArray307 */ 836, 0, R"()")
DIAG_ENTRY(anonymous_77 /* fixed-point-overflow */, 6453, /* DiagArray308 */ 838, 0, R"()")
DIAG_ENTRY(FlagEnum /* flag-enum */, 6474, /* DiagArray309 */ 840, 0, R"()")
DIAG_ENTRY(FlexibleArrayExtensions /* flexible-array-extensions */, 6484, /* DiagArray310 */ 842, 0, R"()")
DIAG_ENTRY(FloatConversion /* float-conversion */, 6510, /* DiagArray311 */ 845, /* DiagSubGroup311 */ 279, R"()")
DIAG_ENTRY(anonymous_230 /* float-equal */, 6527, /* DiagArray312 */ 847, 0, R"()")
DIAG_ENTRY(FloatOverflowConversion /* float-overflow-conversion */, 6539, /* DiagArray313 */ 849, 0, R"()")
DIAG_ENTRY(FloatZeroConversion /* float-zero-conversion */, 6565, /* DiagArray314 */ 852, 0, R"()")
DIAG_ENTRY(ForLoopAnalysis /* for-loop-analysis */, 6587, /* DiagArray315 */ 854, 0, R"()")
DIAG_ENTRY(Format /* format */, 6605, /* DiagArray316 */ 857, /* DiagSubGroup316 */ 282, R"()")
DIAG_ENTRY(FormatExtraArgs /* format-extra-args */, 6612, /* DiagArray317 */ 884, 0, R"()")
DIAG_ENTRY(FormatInsufficientArgs /* format-insufficient-args */, 6630, /* DiagArray318 */ 886, 0, R"()")
DIAG_ENTRY(FormatInvalidSpecifier /* format-invalid-specifier */, 6655, /* DiagArray319 */ 888, 0, R"()")
DIAG_ENTRY(FormatNonStandard /* format-non-iso */, 6680, /* DiagArray320 */ 890, 0, R"()")
DIAG_ENTRY(FormatNonLiteral /* format-nonliteral */, 6695, /* DiagArray321 */ 894, 0, R"()")
DIAG_ENTRY(FormatPedantic /* format-pedantic */, 6713, /* DiagArray322 */ 896, 0, R"()")
DIAG_ENTRY(FormatSecurity /* format-security */, 6729, /* DiagArray323 */ 899, 0, R"()")
DIAG_ENTRY(FormatTypeConfusion /* format-type-confusion */, 6745, /* DiagArray324 */ 901, 0, R"()")
DIAG_ENTRY(FormatY2K /* format-y2k */, 6767, 0, 0, R"()")
DIAG_ENTRY(FormatZeroLength /* format-zero-length */, 6778, /* DiagArray326 */ 903, 0, R"()")
DIAG_ENTRY(Format2 /* format=2 */, 6797, 0, /* DiagSubGroup327 */ 290, R"()")
DIAG_ENTRY(FortifySource /* fortify-source */, 6806, /* DiagArray328 */ 905, 0, R"()")
DIAG_ENTRY(FourByteMultiChar /* four-char-constants */, 6821, /* DiagArray329 */ 911, 0, R"()")
DIAG_ENTRY(FrameAddress /* frame-address */, 6841, /* DiagArray330 */ 913, 0, R"()")
DIAG_ENTRY(BackendFrameLargerThan /* frame-larger-than */, 6855, /* DiagArray331 */ 915, 0, R"(More fine grained information about the stack layout is available by adding the
`-Rpass-analysis=stack-frame-layout` command-line flag to the compiler
invocation.

The diagnostic information can be saved to a file in a machine readable format,
like YAML by adding the `-foptimization-record-file=<file>` command-line flag.

Results can be filtered by function name by passing
`-mllvm -filter-print-funcs=foo`, where `foo` is the target function's name.

   .. code-block: console
      clang -c a.cpp -Rpass-analysis=stack-frame-layout -mllvm -filter-print-funcs=foo

   .. code-block: console
      clang -c a.cpp -Rpass-analysis=stack-frame-layout -foptimization-record-file=<file>)")
DIAG_ENTRY(anonymous_74 /* frame-larger-than= */, 6873, 0, /* DiagSubGroup332 */ 294, R"()")
DIAG_ENTRY(FrameworkIncludePrivateFromPublic /* framework-include-private-from-public */, 6892, /* DiagArray333 */ 918, 0, R"()")
DIAG_ENTRY(FreeNonHeapObject /* free-nonheap-object */, 6930, /* DiagArray334 */ 920, 0, R"()")
DIAG_ENTRY(FunctionDefInObjCContainer /* function-def-in-objc-container */, 6950, /* DiagArray335 */ 922, 0, R"()")
DIAG_ENTRY(FunctionMultiVersioning /* function-multiversion */, 6981, /* DiagArray336 */ 924, /* DiagSubGroup336 */ 296, R"()")
DIAG_ENTRY(FUseLdPath /* fuse-ld-path */, 7003, /* DiagArray337 */ 929, 0, R"()")
DIAG_ENTRY(FutureAttrs /* future-attribute-extensions */, 7016, 0, /* DiagSubGroup338 */ 298, R"()")
DIAG_ENTRY(FutureCompat /* future-compat */, 7044, 0, 0, R"()")
DIAG_ENTRY(GccCompat /* gcc-compat */, 7058, /* DiagArray340 */ 931, 0, R"()")
DIAG_ENTRY(anonymous_136 /* generic-type-extension */, 7069, /* DiagArray341 */ 943, 0, R"()")
DIAG_ENTRY(GlobalConstructors /* global-constructors */, 7092, /* DiagArray342 */ 945, 0, R"()")
DIAG_ENTRY(GlobalISel /* global-isel */, 7112, /* DiagArray343 */ 948, 0, R"()")
DIAG_ENTRY(GNU /* gnu */, 7124, 0, /* DiagSubGroup344 */ 302, R"()")
DIAG_ENTRY(GNUAlignofExpression /* gnu-alignof-expression */, 7128, /* DiagArray345 */ 951, 0, R"()")
DIAG_ENTRY(GNUAnonymousStruct /* gnu-anonymous-struct */, 7151, /* DiagArray346 */ 953, 0, R"()")
DIAG_ENTRY(anonymous_239 /* gnu-array-member-paren-init */, 7172, /* DiagArray347 */ 955, 0, R"()")
DIAG_ENTRY(GNUAutoType /* gnu-auto-type */, 7200, /* DiagArray348 */ 957, 0, R"()")
DIAG_ENTRY(GNUBinaryLiteral /* gnu-binary-literal */, 7214, /* DiagArray349 */ 959, 0, R"()")
DIAG_ENTRY(GNUCaseRange /* gnu-case-range */, 7233, /* DiagArray350 */ 961, 0, R"()")
DIAG_ENTRY(GNUComplexInteger /* gnu-complex-integer */, 7248, /* DiagArray351 */ 963, 0, R"()")
DIAG_ENTRY(GNUCompoundLiteralInitializer /* gnu-compound-literal-initializer */, 7268, /* DiagArray352 */ 965, 0, R"()")
DIAG_ENTRY(GNUConditionalOmittedOperand /* gnu-conditional-omitted-operand */, 7301, /* DiagArray353 */ 967, 0, R"()")
DIAG_ENTRY(GNUDesignator /* gnu-designator */, 7333, /* DiagArray354 */ 969, 0, R"()")
DIAG_ENTRY(anonymous_1 /* gnu-empty-initializer */, 7348, 0, 0, R"()")
DIAG_ENTRY(GNUEmptyStruct /* gnu-empty-struct */, 7370, /* DiagArray356 */ 973, 0, R"()")
DIAG_ENTRY(GNUFlexibleArrayInitializer /* gnu-flexible-array-initializer */, 7387, /* DiagArray357 */ 977, 0, R"()")
DIAG_ENTRY(GNUFlexibleArrayUnionMember /* gnu-flexible-array-union-member */, 7418, /* DiagArray358 */ 979, 0, R"()")
DIAG_ENTRY(GNUFoldingConstant /* gnu-folding-constant */, 7450, /* DiagArray359 */ 981, 0, R"()")
DIAG_ENTRY(GNUImaginaryConstant /* gnu-imaginary-constant */, 7471, /* DiagArray360 */ 985, 0, R"()")
DIAG_ENTRY(GNUIncludeNext /* gnu-include-next */, 7494, /* DiagArray361 */ 987, 0, R"()")
DIAG_ENTRY(anonymous_196 /* gnu-inline-cpp-without-extern */, 7511, /* DiagArray362 */ 989, 0, R"()")
DIAG_ENTRY(GNULabelsAsValue /* gnu-label-as-value */, 7541, /* DiagArray363 */ 991, 0, R"()")
DIAG_ENTRY(GNULineMarker /* gnu-line-marker */, 7560, /* DiagArray364 */ 994, 0, R"()")
DIAG_ENTRY(GNUNullPointerArithmetic /* gnu-null-pointer-arithmetic */, 7576, /* DiagArray365 */ 996, 0, R"()")
DIAG_ENTRY(GNUOffsetofExtensions /* gnu-offsetof-extensions */, 7604, /* DiagArray366 */ 998, 0, R"()")
DIAG_ENTRY(GNUPointerArith /* gnu-pointer-arith */, 7628, /* DiagArray367 */ 1000, 0, R"()")
DIAG_ENTRY(GNURedeclaredEnum /* gnu-redeclared-enum */, 7646, /* DiagArray368 */ 1004, 0, R"()")
DIAG_ENTRY(GNUStatementExpression /* gnu-statement-expression */, 7666, /* DiagArray369 */ 1006, /* DiagSubGroup369 */ 334, R"()")
DIAG_ENTRY(GNUStatementExpressionFromMacroExpansion /* gnu-statement-expression-from-macro-expansion */, 7691, /* DiagArray370 */ 1008, 0, R"()")
DIAG_ENTRY(GNUStaticFloatInit /* gnu-static-float-init */, 7737, /* DiagArray371 */ 1010, 0, R"()")
DIAG_ENTRY(GNUStringLiteralOperatorTemplate /* gnu-string-literal-operator-template */, 7759, /* DiagArray372 */ 1012, 0, R"()")
DIAG_ENTRY(GNUUnionCast /* gnu-union-cast */, 7796, /* DiagArray373 */ 1014, 0, R"()")
DIAG_ENTRY(GNUVariableSizedTypeNotAtEnd /* gnu-variable-sized-type-not-at-end */, 7811, /* DiagArray374 */ 1016, 0, R"()")
DIAG_ENTRY(GNUZeroLineDirective /* gnu-zero-line-directive */, 7846, /* DiagArray375 */ 1018, 0, R"()")
DIAG_ENTRY(GNUZeroVariadicMacroArguments /* gnu-zero-variadic-macro-arguments */, 7870, /* DiagArray376 */ 1020, 0, R"()")
DIAG_ENTRY(anonymous_256 /* gpu-maybe-wrong-side */, 7904, /* DiagArray377 */ 1023, 0, R"()")
DIAG_ENTRY(anonymous_129 /* header-guard */, 7925, /* DiagArray378 */ 1025, 0, R"()")
DIAG_ENTRY(HeaderHygiene /* header-hygiene */, 7938, /* DiagArray379 */ 1027, 0, R"()")
DIAG_ENTRY(HIPOpenMPOffloading /* hip-omp-target-directives */, 7953, /* DiagArray380 */ 1029, 0, R"()")
DIAG_ENTRY(HIPOnly /* hip-only */, 7979, /* DiagArray381 */ 1031, 0, R"()")
DIAG_ENTRY(HLSLExtension /* hlsl-extensions */, 7988, /* DiagArray382 */ 1033, 0, R"()")
DIAG_ENTRY(anonymous_251 /* idiomatic-parentheses */, 8004, /* DiagArray383 */ 1035, 0, R"()")
DIAG_ENTRY(IgnoredAttributes /* ignored-attributes */, 8026, /* DiagArray384 */ 1037, 0, R"()")
DIAG_ENTRY(anonymous_199 /* ignored-availability-without-sdk-settings */, 8045, /* DiagArray385 */ 1122, 0, R"()")
DIAG_ENTRY(IgnoredOptimizationArgument /* ignored-optimization-argument */, 8087, /* DiagArray386 */ 1124, 0, R"()")
DIAG_ENTRY(IgnoredPragmaIntrinsic /* ignored-pragma-intrinsic */, 8117, /* DiagArray387 */ 1127, 0, R"()")
DIAG_ENTRY(IgnoredPragmaOptimize /* ignored-pragma-optimize */, 8142, 0, 0, R"()")
DIAG_ENTRY(IgnoredPragmas /* ignored-pragmas */, 8166, /* DiagArray389 */ 1129, /* DiagSubGroup389 */ 336, R"()")
DIAG_ENTRY(IgnoredQualifiers /* ignored-qualifiers */, 8182, /* DiagArray390 */ 1179, /* DiagSubGroup390 */ 339, R"()")
DIAG_ENTRY(IgnoredReferenceQualifiers /* ignored-reference-qualifiers */, 8201, /* DiagArray391 */ 1184, 0, R"()")
DIAG_ENTRY(Implicit /* implicit */, 8230, 0, /* DiagSubGroup392 */ 341, R"()")
DIAG_ENTRY(ImplicitAtomic /* implicit-atomic-properties */, 8239, /* DiagArray393 */ 1186, 0, R"()")
DIAG_ENTRY(ImplicitConstIntFloatConversion /* implicit-const-int-float-conversion */, 8266, /* DiagArray394 */ 1189, 0, R"()")
DIAG_ENTRY(ImplicitConversionFloatingPointToBool /* implicit-conversion-floating-point-to-bool */, 8302, /* DiagArray395 */ 1191, 0, R"()")
DIAG_ENTRY(anonymous_268 /* implicit-exception-spec-mismatch */, 8345, /* DiagArray396 */ 1193, 0, R"()")
DIAG_ENTRY(ImplicitFallthrough /* implicit-fallthrough */, 8378, /* DiagArray397 */ 1195, /* DiagSubGroup397 */ 344, R"()")
DIAG_ENTRY(ImplicitFallthroughPerFunction /* implicit-fallthrough-per-function */, 8399, /* DiagArray398 */ 1197, 0, R"()")
DIAG_ENTRY(ImplicitFixedPointConversion /* implicit-fixed-point-conversion */, 8433, /* DiagArray399 */ 1199, 0, R"()")
DIAG_ENTRY(ImplicitFloatConversion /* implicit-float-conversion */, 8465, /* DiagArray400 */ 1201, /* DiagSubGroup400 */ 346, R"()")
DIAG_ENTRY(ImplicitFunctionDeclare /* implicit-function-declaration */, 8491, /* DiagArray401 */ 1204, 0, R"()")
DIAG_ENTRY(ImplicitInt /* implicit-int */, 8521, /* DiagArray402 */ 1210, 0, R"()")
DIAG_ENTRY(ImplicitIntConversion /* implicit-int-conversion */, 8534, /* DiagArray403 */ 1214, /* DiagSubGroup403 */ 349, R"()")
DIAG_ENTRY(ImplicitIntFloatConversion /* implicit-int-float-conversion */, 8558, /* DiagArray404 */ 1217, /* DiagSubGroup404 */ 351, R"()")
DIAG_ENTRY(anonymous_171 /* implicit-retain-self */, 8588, /* DiagArray405 */ 1219, 0, R"()")
DIAG_ENTRY(ImplicitlyUnsignedLiteral /* implicitly-unsigned-literal */, 8609, /* DiagArray406 */ 1221, 0, R"()")
DIAG_ENTRY(anonymous_27 /* import */, 8637, 0, 0, R"()")
DIAG_ENTRY(anonymous_123 /* import-preprocessor-directive-pedantic */, 8644, /* DiagArray408 */ 1223, 0, R"()")
DIAG_ENTRY(anonymous_264 /* inaccessible-base */, 8683, /* DiagArray409 */ 1225, 0, R"()")
DIAG_ENTRY(anonymous_113 /* include-next-absolute-path */, 8701, /* DiagArray410 */ 1227, 0, R"()")
DIAG_ENTRY(anonymous_112 /* include-next-outside-header */, 8728, /* DiagArray411 */ 1229, 0, R"()")
DIAG_ENTRY(IncompatibleExceptionSpec /* incompatible-exception-spec */, 8756, /* DiagArray412 */ 1231, 0, R"()")
DIAG_ENTRY(IncompatibleFunctionPointerTypes /* incompatible-function-pointer-types */, 8784, /* DiagArray413 */ 1234, 0, R"()")
DIAG_ENTRY(anonymous_253 /* incompatible-function-pointer-types-strict */, 8820, /* DiagArray414 */ 1236, 0, R"()")
DIAG_ENTRY(anonymous_154 /* incompatible-library-redeclaration */, 8863, /* DiagArray415 */ 1238, 0, R"()")
DIAG_ENTRY(IncompatibleMSStruct /* incompatible-ms-struct */, 8898, /* DiagArray416 */ 1240, 0, R"()")
DIAG_ENTRY(IncompatiblePointerTypes /* incompatible-pointer-types */, 8921, /* DiagArray417 */ 1243, /* DiagSubGroup417 */ 353, R"()")
DIAG_ENTRY(IncompatiblePointerTypesDiscardsQualifiers /* incompatible-pointer-types-discards-qualifiers */, 8948, /* DiagArray418 */ 1245, 0, R"()")
DIAG_ENTRY(anonymous_161 /* incompatible-property-type */, 8995, /* DiagArray419 */ 1249, 0, R"()")
DIAG_ENTRY(anonymous_88 /* incompatible-sysroot */, 9022, /* DiagArray420 */ 1251, 0, R"()")
DIAG_ENTRY(IncompleteFrameworkModuleDeclaration /* incomplete-framework-module-declaration */, 9043, /* DiagArray421 */ 1253, 0, R"()")
DIAG_ENTRY(anonymous_163 /* incomplete-implementation */, 9083, /* DiagArray422 */ 1255, 0, R"()")
DIAG_ENTRY(IncompleteModule /* incomplete-module */, 9109, 0, /* DiagSubGroup423 */ 356, R"()")
DIAG_ENTRY(anonymous_153 /* incomplete-setjmp-declaration */, 9127, /* DiagArray424 */ 1257, 0, R"()")
DIAG_ENTRY(IncompleteUmbrella /* incomplete-umbrella */, 9157, /* DiagArray425 */ 1259, 0, R"()")
DIAG_ENTRY(MicrosoftInconsistentDllImport /* inconsistent-dllimport */, 9177, /* DiagArray426 */ 1263, 0, R"()")
DIAG_ENTRY(CXX11WarnInconsistentOverrideDestructor /* inconsistent-missing-destructor-override */, 9200, /* DiagArray427 */ 1266, 0, R"()")
DIAG_ENTRY(CXX11WarnInconsistentOverrideMethod /* inconsistent-missing-override */, 9241, /* DiagArray428 */ 1268, 0, R"()")
DIAG_ENTRY(IncrementBool /* increment-bool */, 9271, /* DiagArray429 */ 1270, /* DiagSubGroup429 */ 359, R"()")
DIAG_ENTRY(InfiniteRecursion /* infinite-recursion */, 9286, /* DiagArray430 */ 1272, 0, R"()")
DIAG_ENTRY(anonymous_28 /* init-self */, 9305, 0, 0, R"()")
DIAG_ENTRY(InitializerOverrides /* initializer-overrides */, 9315, /* DiagArray432 */ 1274, 0, R"()")
DIAG_ENTRY(anonymous_179 /* injected-class-name */, 9337, /* DiagArray433 */ 1278, 0, R"()")
DIAG_ENTRY(anonymous_29 /* inline */, 9357, 0, 0, R"()")
DIAG_ENTRY(BackendInlineAsm /* inline-asm */, 9364, /* DiagArray435 */ 1280, 0, R"()")
DIAG_ENTRY(InlineNamespaceReopenedNoninline /* inline-namespace-reopened-noninline */, 9375, /* DiagArray436 */ 1282, 0, R"()")
DIAG_ENTRY(anonymous_265 /* inline-new-delete */, 9411, /* DiagArray437 */ 1284, 0, R"()")
DIAG_ENTRY(anonymous_212 /* instantiation-after-specialization */, 9429, /* DiagArray438 */ 1286, 0, R"()")
DIAG_ENTRY(IntConversion /* int-conversion */, 9464, /* DiagArray439 */ 1288, 0, R"()")
DIAG_ENTRY(anonymous_64 /* int-conversions */, 9479, 0, /* DiagSubGroup440 */ 361, R"()")
DIAG_ENTRY(IntInBoolContext /* int-in-bool-context */, 9495, /* DiagArray441 */ 1291, 0, R"()")
DIAG_ENTRY(IntToPointerCast /* int-to-pointer-cast */, 9515, /* DiagArray442 */ 1294, /* DiagSubGroup442 */ 363, R"()")
DIAG_ENTRY(IntToVoidPointerCast /* int-to-void-pointer-cast */, 9535, /* DiagArray443 */ 1296, 0, R"()")
DIAG_ENTRY(anonymous_76 /* integer-overflow */, 9560, /* DiagArray444 */ 1298, 0, R"()")
DIAG_ENTRY(anonymous_149 /* interrupt-service-routine */, 9577, /* DiagArray445 */ 1300, 0, R"()")
DIAG_ENTRY(InvalidCommandLineArgument /* invalid-command-line-argument */, 9603, /* DiagArray446 */ 1302, /* DiagSubGroup446 */ 365, R"()")
DIAG_ENTRY(anonymous_182 /* invalid-constexpr */, 9633, /* DiagArray447 */ 1314, 0, R"()")
DIAG_ENTRY(ObjCInvalidIBOutletProperty /* invalid-iboutlet */, 9651, /* DiagArray448 */ 1316, 0, R"()")
DIAG_ENTRY(anonymous_193 /* invalid-initializer-from-system-header */, 9668, /* DiagArray449 */ 1319, 0, R"()")
DIAG_ENTRY(InvalidIOSDeploymentTarget /* invalid-ios-deployment-target */, 9707, /* DiagArray450 */ 1321, 0, R"()")
DIAG_ENTRY(anonymous_205 /* invalid-no-builtin-names */, 9737, /* DiagArray451 */ 1323, 0, R"()")
DIAG_ENTRY(InvalidNoreturn /* invalid-noreturn */, 9762, /* DiagArray452 */ 1325, 0, R"()")
DIAG_ENTRY(InvalidOffsetof /* invalid-offsetof */, 9779, /* DiagArray453 */ 1328, 0, R"()")
DIAG_ENTRY(InvalidOrNonExistentDirectory /* invalid-or-nonexistent-directory */, 9796, /* DiagArray454 */ 1331, 0, R"()")
DIAG_ENTRY(anonymous_210 /* invalid-partial-specialization */, 9829, /* DiagArray455 */ 1333, 0, R"()")
DIAG_ENTRY(anonymous_30 /* invalid-pch */, 9860, 0, 0, R"()")
DIAG_ENTRY(InvalidPPToken /* invalid-pp-token */, 9872, /* DiagArray457 */ 1335, 0, R"()")
DIAG_ENTRY(InvalidSourceEncoding /* invalid-source-encoding */, 9889, /* DiagArray458 */ 1338, 0, R"()")
DIAG_ENTRY(anonymous_174 /* invalid-static-assert-message */, 9913, /* DiagArray459 */ 1341, 0, R"()")
DIAG_ENTRY(anonymous_126 /* invalid-token-paste */, 9943, /* DiagArray460 */ 1343, 0, R"()")
DIAG_ENTRY(anonymous_111 /* invalid-unevaluated-string */, 9963, /* DiagArray461 */ 1345, 0, R"()")
DIAG_ENTRY(anonymous_104 /* invalid-utf8 */, 9990, /* DiagArray462 */ 1347, 0, R"()")
DIAG_ENTRY(anonymous_250 /* jump-seh-finally */, 10003, /* DiagArray463 */ 1349, 0, R"()")
DIAG_ENTRY(KeywordCompat /* keyword-compat */, 10020, /* DiagArray464 */ 1351, 0, R"()")
DIAG_ENTRY(KeywordAsMacro /* keyword-macro */, 10035, /* DiagArray465 */ 1353, 0, R"()")
DIAG_ENTRY(KNRPromotedParameter /* knr-promoted-parameter */, 10049, /* DiagArray466 */ 1355, 0, R"()")
DIAG_ENTRY(anonymous_103 /* language-extension-token */, 10072, /* DiagArray467 */ 1357, 0, R"()")
DIAG_ENTRY(LargeByValueCopy /* large-by-value-copy */, 10097, /* DiagArray468 */ 1359, 0, R"()")
DIAG_ENTRY(LibLTO /* liblto */, 10117, 0, 0, R"()")
DIAG_ENTRY(LinkerWarnings /* linker-warnings */, 10124, /* DiagArray470 */ 1362, 0, R"()")
DIAG_ENTRY(LiteralConversion /* literal-conversion */, 10140, /* DiagArray471 */ 1364, 0, R"()")
DIAG_ENTRY(LiteralRange /* literal-range */, 10159, /* DiagArray472 */ 1367, 0, R"()")
DIAG_ENTRY(LocalTypeTemplateArgs /* local-type-template-args */, 10173, /* DiagArray473 */ 1371, /* DiagSubGroup473 */ 367, R"()")
DIAG_ENTRY(LogicalNotParentheses /* logical-not-parentheses */, 10198, /* DiagArray474 */ 1373, 0, R"()")
DIAG_ENTRY(LogicalOpParentheses /* logical-op-parentheses */, 10222, /* DiagArray475 */ 1375, 0, R"()")
DIAG_ENTRY(LongLong /* long-long */, 10245, /* DiagArray476 */ 1377, /* DiagSubGroup476 */ 369, R"()")
DIAG_ENTRY(LoopAnalysis /* loop-analysis */, 10255, 0, /* DiagSubGroup477 */ 371, R"()")
DIAG_ENTRY(MacroRedefined /* macro-redefined */, 10269, /* DiagArray478 */ 1379, 0, R"()")
DIAG_ENTRY(Main /* main */, 10285, /* DiagArray479 */ 1381, 0, R"()")
DIAG_ENTRY(MainReturnType /* main-return-type */, 10290, /* DiagArray480 */ 1389, 0, R"()")
DIAG_ENTRY(MalformedWarningCheck /* malformed-warning-check */, 10307, /* DiagArray481 */ 1391, 0, R"()")
DIAG_ENTRY(anonymous_225 /* many-braces-around-scalar-init */, 10331, /* DiagArray482 */ 1393, 0, R"()")
DIAG_ENTRY(anonymous_108 /* mathematical-notation-identifier-extension */, 10362, /* DiagArray483 */ 1395, 0, R"()")
DIAG_ENTRY(MaxTokens /* max-tokens */, 10405, /* DiagArray484 */ 1397, 0, R"(The warning is issued if the number of pre-processor tokens exceeds
the token limit, which can be set in three ways:

1. As a limit at a specific point in a file, using the ``clang max_tokens_here``
   pragma:

   .. code-block: c++
      #pragma clang max_tokens_here 1234

2. As a per-translation unit limit, using the ``-fmax-tokens=`` command-line
   flag:

   .. code-block: console
      clang -c a.cpp -fmax-tokens=1234

3. As a per-translation unit limit using the ``clang max_tokens_total`` pragma,
   which works like and overrides the ``-fmax-tokens=`` flag:

   .. code-block: c++
      #pragma clang max_tokens_total 1234

These limits can be helpful in limiting code growth through included files.

Setting a token limit of zero means no limit.

Note that the warning is disabled by default, so -Wmax-tokens must be used
in addition with the pragmas or -fmax-tokens flag to get any warnings.)")
DIAG_ENTRY(MaxUnsignedZero /* max-unsigned-zero */, 10416, /* DiagArray485 */ 1400, 0, R"()")
DIAG_ENTRY(MemsetTransposedArgs /* memset-transposed-args */, 10434, /* DiagArray486 */ 1402, 0, R"()")
DIAG_ENTRY(anonymous_156 /* memsize-comparison */, 10457, /* DiagArray487 */ 1404, 0, R"()")
DIAG_ENTRY(MethodSignatures /* method-signatures */, 10476, /* DiagArray488 */ 1406, 0, R"()")
DIAG_ENTRY(Microsoft /* microsoft */, 10494, 0, /* DiagSubGroup489 */ 374, R"()")
DIAG_ENTRY(MicrosoftAbstract /* microsoft-abstract */, 10504, /* DiagArray490 */ 1409, 0, R"()")
DIAG_ENTRY(MicrosoftAnonTag /* microsoft-anon-tag */, 10523, /* DiagArray491 */ 1411, 0, R"()")
DIAG_ENTRY(MicrosoftCast /* microsoft-cast */, 10542, /* DiagArray492 */ 1414, 0, R"()")
DIAG_ENTRY(MicrosoftCharize /* microsoft-charize */, 10557, /* DiagArray493 */ 1417, 0, R"()")
DIAG_ENTRY(MicrosoftCommentPaste /* microsoft-comment-paste */, 10575, /* DiagArray494 */ 1419, 0, R"()")
DIAG_ENTRY(MicrosoftConstInit /* microsoft-const-init */, 10599, /* DiagArray495 */ 1421, 0, R"()")
DIAG_ENTRY(MicrosoftCppMacro /* microsoft-cpp-macro */, 10620, /* DiagArray496 */ 1423, 0, R"()")
DIAG_ENTRY(MicrosoftDefaultArgRedefinition /* microsoft-default-arg-redefinition */, 10640, /* DiagArray497 */ 1425, 0, R"()")
DIAG_ENTRY(MicrosoftDrectveSection /* microsoft-drectve-section */, 10675, /* DiagArray498 */ 1427, 0, R"()")
DIAG_ENTRY(MicrosoftEndOfFile /* microsoft-end-of-file */, 10701, /* DiagArray499 */ 1429, 0, R"()")
DIAG_ENTRY(MicrosoftEnumForwardReference /* microsoft-enum-forward-reference */, 10723, /* DiagArray500 */ 1431, 0, R"()")
DIAG_ENTRY(MicrosoftEnumValue /* microsoft-enum-value */, 10756, /* DiagArray501 */ 1433, 0, R"()")
DIAG_ENTRY(MicrosoftExceptionSpec /* microsoft-exception-spec */, 10777, /* DiagArray502 */ 1435, 0, R"()")
DIAG_ENTRY(anonymous_135 /* microsoft-exists */, 10802, /* DiagArray503 */ 1441, 0, R"()")
DIAG_ENTRY(MicrosoftExplicitConstructorCall /* microsoft-explicit-constructor-call */, 10819, /* DiagArray504 */ 1443, 0, R"()")
DIAG_ENTRY(MicrosoftExtraQualification /* microsoft-extra-qualification */, 10855, /* DiagArray505 */ 1445, 0, R"()")
DIAG_ENTRY(MicrosoftFixedEnum /* microsoft-fixed-enum */, 10885, /* DiagArray506 */ 1447, 0, R"()")
DIAG_ENTRY(MicrosoftFlexibleArray /* microsoft-flexible-array */, 10906, /* DiagArray507 */ 1449, 0, R"()")
DIAG_ENTRY(MicrosoftGoto /* microsoft-goto */, 10931, /* DiagArray508 */ 1452, 0, R"()")
DIAG_ENTRY(MicrosoftInaccessibleBase /* microsoft-inaccessible-base */, 10946, /* DiagArray509 */ 1454, 0, R"()")
DIAG_ENTRY(MicrosoftInclude /* microsoft-include */, 10974, /* DiagArray510 */ 1456, 0, R"()")
DIAG_ENTRY(MicrosoftInitFromPredefined /* microsoft-init-from-predefined */, 10992, /* DiagArray511 */ 1458, 0, R"()")
DIAG_ENTRY(MicrosoftMutableReference /* microsoft-mutable-reference */, 11023, /* DiagArray512 */ 1460, 0, R"()")
DIAG_ENTRY(MicrosoftPureDefinition /* microsoft-pure-definition */, 11051, /* DiagArray513 */ 1462, 0, R"()")
DIAG_ENTRY(MicrosoftRedeclareStatic /* microsoft-redeclare-static */, 11077, /* DiagArray514 */ 1464, 0, R"()")
DIAG_ENTRY(MicrosoftSealed /* microsoft-sealed */, 11104, /* DiagArray515 */ 1466, 0, R"()")
DIAG_ENTRY(MicrosoftStaticAssert /* microsoft-static-assert */, 11121, /* DiagArray516 */ 1468, 0, R"()")
DIAG_ENTRY(MicrosoftTemplate /* microsoft-template */, 11145, /* DiagArray517 */ 1470, /* DiagSubGroup517 */ 406, R"()")
DIAG_ENTRY(MicrosoftTemplateShadow /* microsoft-template-shadow */, 11164, /* DiagArray518 */ 1481, 0, R"()")
DIAG_ENTRY(MicrosoftUnionMemberReference /* microsoft-union-member-reference */, 11190, /* DiagArray519 */ 1483, 0, R"()")
DIAG_ENTRY(MicrosoftUnqualifiedFriend /* microsoft-unqualified-friend */, 11223, /* DiagArray520 */ 1485, 0, R"()")
DIAG_ENTRY(MicrosoftUsingDecl /* microsoft-using-decl */, 11252, /* DiagArray521 */ 1487, 0, R"()")
DIAG_ENTRY(MicrosoftVoidPseudoDtor /* microsoft-void-pseudo-dtor */, 11273, /* DiagArray522 */ 1489, 0, R"()")
DIAG_ENTRY(MisExpect /* misexpect */, 11300, /* DiagArray523 */ 1491, 0, R"()")
DIAG_ENTRY(MisleadingIndentation /* misleading-indentation */, 11310, /* DiagArray524 */ 1493, 0, R"()")
DIAG_ENTRY(anonymous_246 /* mismatched-new-delete */, 11333, /* DiagArray525 */ 1495, 0, R"()")
DIAG_ENTRY(MismatchedParameterTypes /* mismatched-parameter-types */, 11355, /* DiagArray526 */ 1497, 0, R"()")
DIAG_ENTRY(MismatchedReturnTypes /* mismatched-return-types */, 11382, /* DiagArray527 */ 1499, 0, R"()")
DIAG_ENTRY(MismatchedTags /* mismatched-tags */, 11406, /* DiagArray528 */ 1501, 0, R"()")
DIAG_ENTRY(MissingBraces /* missing-braces */, 11422, /* DiagArray529 */ 1504, 0, R"()")
DIAG_ENTRY(anonymous_261 /* missing-constinit */, 11437, /* DiagArray530 */ 1506, 0, R"()")
DIAG_ENTRY(MissingDeclarations /* missing-declarations */, 11455, /* DiagArray531 */ 1508, 0, R"()")
DIAG_ENTRY(anonymous_178 /* missing-exception-spec */, 11476, /* DiagArray532 */ 1513, 0, R"()")
DIAG_ENTRY(MissingFieldInitializers /* missing-field-initializers */, 11499, /* DiagArray533 */ 1515, 0, R"()")
DIAG_ENTRY(anonymous_31 /* missing-format-attribute */, 11526, 0, 0, R"()")
DIAG_ENTRY(anonymous_32 /* missing-include-dirs */, 11551, 0, 0, R"()")
DIAG_ENTRY(MissingMethodReturnType /* missing-method-return-type */, 11572, /* DiagArray536 */ 1517, 0, R"()")
DIAG_ENTRY(anonymous_95 /* missing-multilib */, 11599, /* DiagArray537 */ 1519, 0, R"()")
DIAG_ENTRY(MissingNoEscape /* missing-noescape */, 11616, /* DiagArray538 */ 1521, 0, R"()")
DIAG_ENTRY(MissingNoreturn /* missing-noreturn */, 11633, /* DiagArray539 */ 1523, 0, R"()")
DIAG_ENTRY(anonymous_197 /* missing-prototype-for-cc */, 11650, /* DiagArray540 */ 1526, 0, R"()")
DIAG_ENTRY(anonymous_214 /* missing-prototypes */, 11675, /* DiagArray541 */ 1528, 0, R"()")
DIAG_ENTRY(anonymous_137 /* missing-selector-name */, 11694, /* DiagArray542 */ 1530, 0, R"()")
DIAG_ENTRY(anonymous_87 /* missing-sysroot */, 11716, /* DiagArray543 */ 1532, 0, R"()")
DIAG_ENTRY(anonymous_215 /* missing-variable-declarations */, 11732, /* DiagArray544 */ 1534, 0, R"()")
DIAG_ENTRY(MisspelledAssumption /* misspelled-assumption */, 11762, /* DiagArray545 */ 1536, 0, R"()")
DIAG_ENTRY(ModuleBuild /* module-build */, 11784, /* DiagArray546 */ 1538, 0, R"()")
DIAG_ENTRY(ModuleConflict /* module-conflict */, 11797, /* DiagArray547 */ 1543, 0, R"()")
DIAG_ENTRY(anonymous_99 /* module-file-config-mismatch */, 11813, /* DiagArray548 */ 1546, 0, R"()")
DIAG_ENTRY(ModuleFileExtension /* module-file-extension */, 11841, /* DiagArray549 */ 1548, 0, R"()")
DIAG_ENTRY(ModuleImport /* module-import */, 11863, /* DiagArray550 */ 1550, 0, R"()")
DIAG_ENTRY(anonymous_278 /* module-import-in-extern-c */, 11877, /* DiagArray551 */ 1552, 0, R"()")
DIAG_ENTRY(ModuleIncludeDirectiveTranslation /* module-include-translation */, 11903, /* DiagArray552 */ 1554, 0, R"()")
DIAG_ENTRY(ModuleLock /* module-lock */, 11930, /* DiagArray553 */ 1556, 0, R"()")
DIAG_ENTRY(anonymous_281 /* modules-ambiguous-internal-linkage */, 11942, /* DiagArray554 */ 1558, 0, R"()")
DIAG_ENTRY(anonymous_279 /* modules-import-nested-redundant */, 11977, /* DiagArray555 */ 1560, 0, R"()")
DIAG_ENTRY(Most /* most */, 12009, 0, /* DiagSubGroup556 */ 408, R"()")
DIAG_ENTRY(Move /* move */, 12014, 0, /* DiagSubGroup557 */ 446, R"()")
DIAG_ENTRY(anonymous_73 /* msvc-include */, 12019, 0, /* DiagSubGroup558 */ 451, R"()")
DIAG_ENTRY(anonymous_91 /* msvc-not-found */, 12032, /* DiagArray559 */ 1562, 0, R"()")
DIAG_ENTRY(MultiGPU /* multi-gpu */, 12047, /* DiagArray560 */ 1564, 0, R"()")
DIAG_ENTRY(MultiChar /* multichar */, 12057, /* DiagArray561 */ 1566, 0, R"()")
DIAG_ENTRY(anonymous_266 /* multiple-move-vbase */, 12067, /* DiagArray562 */ 1568, 0, R"()")
DIAG_ENTRY(anonymous_21 /* narrowing */, 12087, 0, /* DiagSubGroup563 */ 453, R"()")
DIAG_ENTRY(anonymous_263 /* nested-anon-types */, 12097, /* DiagArray564 */ 1570, 0, R"()")
DIAG_ENTRY(anonymous_33 /* nested-externs */, 12115, 0, 0, R"()")
DIAG_ENTRY(OperatorNewReturnsNull /* new-returns-null */, 12130, /* DiagArray566 */ 1572, 0, R"()")
DIAG_ENTRY(NewlineEOF /* newline-eof */, 12147, /* DiagArray567 */ 1574, 0, R"()")
DIAG_ENTRY(NoDeref /* noderef */, 12159, /* DiagArray568 */ 1577, 0, R"()")
DIAG_ENTRY(NoexceptType /* noexcept-type */, 12167, 0, /* DiagSubGroup569 */ 455, R"()")
DIAG_ENTRY(anonymous_159 /* non-c-typedef-for-linkage */, 12181, /* DiagArray570 */ 1581, 0, R"()")
DIAG_ENTRY(NonGCC /* non-gcc */, 12207, 0, /* DiagSubGroup571 */ 457, R"()")
DIAG_ENTRY(NonLiteralNullConversion /* non-literal-null-conversion */, 12215, /* DiagArray572 */ 1583, 0, R"()")
DIAG_ENTRY(NonModularIncludeInFrameworkModule /* non-modular-include-in-framework-module */, 12243, /* DiagArray573 */ 1585, 0, R"()")
DIAG_ENTRY(NonModularIncludeInModule /* non-modular-include-in-module */, 12283, /* DiagArray574 */ 1587, /* DiagSubGroup574 */ 461, R"()")
DIAG_ENTRY(NonPODVarargs /* non-pod-varargs */, 12313, /* DiagArray575 */ 1589, 0, R"()")
DIAG_ENTRY(anonymous_188 /* non-power-of-two-alignment */, 12329, /* DiagArray576 */ 1594, 0, R"()")
DIAG_ENTRY(NonVirtualDtor /* non-virtual-dtor */, 12356, /* DiagArray577 */ 1596, 0, R"()")
DIAG_ENTRY(NonNull /* nonnull */, 12373, /* DiagArray578 */ 1598, 0, R"()")
DIAG_ENTRY(anonymous_35 /* nonportable-cfstrings */, 12381, 0, 0, R"()")
DIAG_ENTRY(anonymous_114 /* nonportable-include-path */, 12403, /* DiagArray580 */ 1601, 0, R"()")
DIAG_ENTRY(anonymous_115 /* nonportable-system-include-path */, 12428, /* DiagArray581 */ 1603, 0, R"()")
DIAG_ENTRY(anonymous_273 /* nonportable-vector-initialization */, 12460, /* DiagArray582 */ 1605, 0, R"()")
DIAG_ENTRY(NonTrivialMemaccess /* nontrivial-memaccess */, 12494, /* DiagArray583 */ 1607, 0, R"()")
DIAG_ENTRY(NSConsumedMismatch /* nsconsumed-mismatch */, 12515, /* DiagArray584 */ 1609, 0, R"()")
DIAG_ENTRY(NSReturnsMismatch /* nsreturns-mismatch */, 12535, /* DiagArray585 */ 1611, 0, R"()")
DIAG_ENTRY(NullArithmetic /* null-arithmetic */, 12554, /* DiagArray586 */ 1613, 0, R"()")
DIAG_ENTRY(NullCharacter /* null-character */, 12570, /* DiagArray587 */ 1616, 0, R"()")
DIAG_ENTRY(NullConversion /* null-conversion */, 12585, /* DiagArray588 */ 1619, 0, R"()")
DIAG_ENTRY(NullDereference /* null-dereference */, 12601, /* DiagArray589 */ 1621, 0, R"()")
DIAG_ENTRY(NullPointerArithmetic /* null-pointer-arithmetic */, 12618, /* DiagArray590 */ 1624, /* DiagSubGroup590 */ 463, R"()")
DIAG_ENTRY(NullPointerSubtraction /* null-pointer-subtraction */, 12642, /* DiagArray591 */ 1626, 0, R"()")
DIAG_ENTRY(Nullability /* nullability */, 12667, /* DiagArray592 */ 1628, 0, R"()")
DIAG_ENTRY(NullabilityCompleteness /* nullability-completeness */, 12679, /* DiagArray593 */ 1634, /* DiagSubGroup593 */ 465, R"()")
DIAG_ENTRY(NullabilityCompletenessOnArrays /* nullability-completeness-on-arrays */, 12704, /* DiagArray594 */ 1636, 0, R"()")
DIAG_ENTRY(NullabilityDeclSpec /* nullability-declspec */, 12739, /* DiagArray595 */ 1638, 0, R"()")
DIAG_ENTRY(anonymous_131 /* nullability-extension */, 12760, /* DiagArray596 */ 1640, 0, R"()")
DIAG_ENTRY(NullabilityInferredOnNestedType /* nullability-inferred-on-nested-type */, 12782, /* DiagArray597 */ 1642, 0, R"()")
DIAG_ENTRY(NullableToNonNullConversion /* nullable-to-nonnull-conversion */, 12818, /* DiagArray598 */ 1644, 0, R"()")
DIAG_ENTRY(anonymous_168 /* objc-autosynthesis-property-ivar-name-match */, 12849, /* DiagArray599 */ 1646, 0, R"()")
DIAG_ENTRY(ObjCBoolConstantConversion /* objc-bool-constant-conversion */, 12893, /* DiagArray600 */ 1648, 0, R"()")
DIAG_ENTRY(ObjCBoxing /* objc-boxing */, 12923, /* DiagArray601 */ 1650, 0, R"()")
DIAG_ENTRY(anonymous_243 /* objc-circular-container */, 12935, /* DiagArray602 */ 1652, 0, R"()")
DIAG_ENTRY(ObjCCocoaAPI /* objc-cocoa-api */, 12959, 0, /* DiagSubGroup603 */ 467, R"()")
DIAG_ENTRY(ObjCDesignatedInit /* objc-designated-initializers */, 12974, /* DiagArray604 */ 1654, 0, R"()")
DIAG_ENTRY(anonymous_185 /* objc-dictionary-duplicate-keys */, 13003, /* DiagArray605 */ 1661, 0, R"()")
DIAG_ENTRY(anonymous_83 /* objc-duplicate-category-definition */, 13034, /* DiagArray606 */ 1663, 0, R"()")
DIAG_ENTRY(ObjCFlexibleArray /* objc-flexible-array */, 13069, /* DiagArray607 */ 1665, 0, R"()")
DIAG_ENTRY(anonymous_221 /* objc-forward-class-redefinition */, 13089, /* DiagArray608 */ 1668, 0, R"()")
DIAG_ENTRY(anonymous_222 /* objc-interface-ivars */, 13121, /* DiagArray609 */ 1670, 0, R"()")
DIAG_ENTRY(ObjCLiteralComparison /* objc-literal-compare */, 13142, /* DiagArray610 */ 1672, /* DiagSubGroup610 */ 469, R"()")
DIAG_ENTRY(ObjCLiteralConversion /* objc-literal-conversion */, 13163, /* DiagArray611 */ 1674, 0, R"()")
DIAG_ENTRY(anonymous_122 /* objc-macro-redefinition */, 13187, /* DiagArray612 */ 1677, 0, R"()")
DIAG_ENTRY(anonymous_173 /* objc-messaging-id */, 13211, /* DiagArray613 */ 1679, 0, R"()")
DIAG_ENTRY(MethodAccess /* objc-method-access */, 13229, /* DiagArray614 */ 1681, 0, R"()")
DIAG_ENTRY(anonymous_169 /* objc-missing-property-synthesis */, 13248, /* DiagArray615 */ 1688, 0, R"()")
DIAG_ENTRY(ObjCMissingSuperCalls /* objc-missing-super-calls */, 13280, /* DiagArray616 */ 1690, 0, R"()")
DIAG_ENTRY(ObjCMultipleMethodNames /* objc-multiple-method-names */, 13305, /* DiagArray617 */ 1692, 0, R"()")
DIAG_ENTRY(ObjCRetainBlockProperty /* objc-noncopy-retain-block-property */, 13332, /* DiagArray618 */ 1694, 0, R"()")
DIAG_ENTRY(ObjCNonUnifiedException /* objc-nonunified-exceptions */, 13367, /* DiagArray619 */ 1696, 0, R"()")
DIAG_ENTRY(ObjCPropertyAssignOnObjectType /* objc-property-assign-on-object-type */, 13394, /* DiagArray620 */ 1698, 0, R"()")
DIAG_ENTRY(ObjCPropertyImpl /* objc-property-implementation */, 13430, /* DiagArray621 */ 1700, 0, R"()")
DIAG_ENTRY(anonymous_164 /* objc-property-implicit-mismatch */, 13459, /* DiagArray622 */ 1705, 0, R"()")
DIAG_ENTRY(anonymous_166 /* objc-property-matches-cocoa-ownership-rule */, 13491, /* DiagArray623 */ 1707, 0, R"()")
DIAG_ENTRY(ObjCPropertyNoAttribute /* objc-property-no-attribute */, 13534, /* DiagArray624 */ 1709, 0, R"()")
DIAG_ENTRY(ObjCNoPropertyAutoSynthesis /* objc-property-synthesis */, 13561, /* DiagArray625 */ 1712, 0, R"()")
DIAG_ENTRY(ObjCProtocolMethodImpl /* objc-protocol-method-implementation */, 13585, /* DiagArray626 */ 1716, 0, R"()")
DIAG_ENTRY(anonymous_167 /* objc-protocol-property-synthesis */, 13621, /* DiagArray627 */ 1718, 0, R"()")
DIAG_ENTRY(ObjCProtocolQualifiers /* objc-protocol-qualifiers */, 13654, /* DiagArray628 */ 1720, 0, R"()")
DIAG_ENTRY(ObjCReadonlyPropertyHasSetter /* objc-readonly-with-setter-property */, 13679, /* DiagArray629 */ 1722, 0, R"()")
DIAG_ENTRY(ObjCRedundantAPIUse /* objc-redundant-api-use */, 13714, 0, /* DiagSubGroup630 */ 471, R"()")
DIAG_ENTRY(ObjCRedundantLiteralUse /* objc-redundant-literal-use */, 13737, /* DiagArray631 */ 1724, 0, R"()")
DIAG_ENTRY(ObjCRootClass /* objc-root-class */, 13764, /* DiagArray632 */ 1726, 0, R"()")
DIAG_ENTRY(ObjCSignedCharBool /* objc-signed-char-bool */, 13780, 0, /* DiagSubGroup633 */ 473, R"()")
DIAG_ENTRY(ObjCSignedCharBoolImplicitFloatConversion /* objc-signed-char-bool-implicit-float-conversion */, 13802, /* DiagArray634 */ 1728, 0, R"()")
DIAG_ENTRY(ObjCSignedCharBoolImplicitIntConversion /* objc-signed-char-bool-implicit-int-conversion */, 13850, /* DiagArray635 */ 1730, 0, R"()")
DIAG_ENTRY(ObjCStringComparison /* objc-string-compare */, 13896, /* DiagArray636 */ 1732, 0, R"()")
DIAG_ENTRY(ObjCStringConcatenation /* objc-string-concatenation */, 13916, /* DiagArray637 */ 1734, 0, R"()")
DIAG_ENTRY(anonymous_244 /* objc-unsafe-perform-selector */, 13942, /* DiagArray638 */ 1736, 0, R"()")
DIAG_ENTRY(ODR /* odr */, 13971, /* DiagArray639 */ 1738, 0, R"()")
DIAG_ENTRY(OldStyleCast /* old-style-cast */, 13975, /* DiagArray640 */ 1757, 0, R"()")
DIAG_ENTRY(anonymous_37 /* old-style-definition */, 13990, 0, 0, R"()")
DIAG_ENTRY(OpenCLUnsupportedRGBA /* opencl-unsupported-rgba */, 14011, /* DiagArray642 */ 1759, 0, R"()")
DIAG_ENTRY(OpenMP /* openmp */, 14035, 0, /* DiagSubGroup643 */ 478, R"()")
DIAG_ENTRY(OpenMP51Ext /* openmp-51-extensions */, 14042, /* DiagArray644 */ 1761, 0, R"()")
DIAG_ENTRY(OpenMPClauses /* openmp-clauses */, 14063, /* DiagArray645 */ 1763, 0, R"()")
DIAG_ENTRY(OpenMPLoopForm /* openmp-loop-form */, 14078, /* DiagArray646 */ 1783, 0, R"()")
DIAG_ENTRY(OpenMPMapping /* openmp-mapping */, 14095, /* DiagArray647 */ 1786, 0, R"()")
DIAG_ENTRY(OpenMPTarget /* openmp-target */, 14110, /* DiagArray648 */ 1788, /* DiagSubGroup648 */ 485, R"()")
DIAG_ENTRY(OptionIgnored /* option-ignored */, 14124, /* DiagArray649 */ 1792, 0, R"()")
DIAG_ENTRY(OrderedCompareFunctionPointers /* ordered-compare-function-pointers */, 14139, /* DiagArray650 */ 1810, 0, R"()")
DIAG_ENTRY(OutOfLineDeclaration /* out-of-line-declaration */, 14173, /* DiagArray651 */ 1813, 0, R"()")
DIAG_ENTRY(anonymous_151 /* out-of-scope-function */, 14197, /* DiagArray652 */ 1815, 0, R"()")
DIAG_ENTRY(OveralignedType /* over-aligned */, 14219, /* DiagArray653 */ 1817, 0, R"()")
DIAG_ENTRY(anonymous_38 /* overflow */, 14232, 0, 0, R"()")
DIAG_ENTRY(OverlengthStrings /* overlength-strings */, 14241, /* DiagArray655 */ 1819, 0, R"()")
DIAG_ENTRY(OverloadedShiftOpParentheses /* overloaded-shift-op-parentheses */, 14260, /* DiagArray656 */ 1821, 0, R"()")
DIAG_ENTRY(OverloadedVirtual /* overloaded-virtual */, 14292, /* DiagArray657 */ 1823, 0, R"()")
DIAG_ENTRY(anonymous_34 /* override-init */, 14311, 0, /* DiagSubGroup658 */ 487, R"()")
DIAG_ENTRY(anonymous_96 /* override-module */, 14325, /* DiagArray659 */ 1825, 0, R"()")
DIAG_ENTRY(OverridingMethodMismatch /* overriding-method-mismatch */, 14341, /* DiagArray660 */ 1827, 0, R"()")
DIAG_ENTRY(anonymous_86 /* overriding-t-option */, 14368, /* DiagArray661 */ 1835, 0, R"()")
DIAG_ENTRY(Packed /* packed */, 14388, /* DiagArray662 */ 1837, /* DiagSubGroup662 */ 489, R"()")
DIAG_ENTRY(PackedNonPod /* packed-non-pod */, 14395, /* DiagArray663 */ 1839, 0, R"()")
DIAG_ENTRY(Padded /* padded */, 14410, /* DiagArray664 */ 1841, 0, R"()")
DIAG_ENTRY(Parentheses /* parentheses */, 14417, /* DiagArray665 */ 1845, /* DiagSubGroup665 */ 491, R"()")
DIAG_ENTRY(ParenthesesOnEquality /* parentheses-equality */, 14429, /* DiagArray666 */ 1849, 0, R"()")
DIAG_ENTRY(anonymous_7 /* partial-availability */, 14450, 0, /* DiagSubGroup667 */ 500, R"()")
DIAG_ENTRY(BackendOptimizationRemark /* pass */, 14471, /* DiagArray668 */ 1851, 0, R"()")
DIAG_ENTRY(BackendOptimizationRemarkAnalysis /* pass-analysis */, 14476, /* DiagArray669 */ 1853, 0, R"()")
DIAG_ENTRY(BackendOptimizationFailure /* pass-failed */, 14490, /* DiagArray670 */ 1857, 0, R"()")
DIAG_ENTRY(BackendOptimizationRemarkMissed /* pass-missed */, 14502, /* DiagArray671 */ 1859, 0, R"()")
DIAG_ENTRY(anonymous_286 /* pch-date-time */, 14514, /* DiagArray672 */ 1861, 0, R"()")
DIAG_ENTRY(Pedantic /* pedantic */, 14528, /* DiagArray673 */ 1863, /* DiagSubGroup673 */ 502, R"()")
DIAG_ENTRY(OpenCLCoreFeaturesDiagGroup /* pedantic-core-features */, 14537, /* DiagArray674 */ 1939, 0, R"()")
DIAG_ENTRY(PedanticMacros /* pedantic-macros */, 14560, 0, /* DiagSubGroup675 */ 564, R"()")
DIAG_ENTRY(PessimizingMove /* pessimizing-move */, 14576, /* DiagArray676 */ 1942, 0, R"()")
DIAG_ENTRY(PointerArith /* pointer-arith */, 14593, /* DiagArray677 */ 1945, /* DiagSubGroup677 */ 570, R"()")
DIAG_ENTRY(PointerBoolConversion /* pointer-bool-conversion */, 14607, /* DiagArray678 */ 1949, 0, R"()")
DIAG_ENTRY(anonymous_200 /* pointer-compare */, 14631, /* DiagArray679 */ 1952, 0, R"()")
DIAG_ENTRY(anonymous_242 /* pointer-integer-compare */, 14647, /* DiagArray680 */ 1954, 0, R"()")
DIAG_ENTRY(anonymous_252 /* pointer-sign */, 14671, /* DiagArray681 */ 1956, 0, R"()")
DIAG_ENTRY(PointerToEnumCast /* pointer-to-enum-cast */, 14684, /* DiagArray682 */ 1958, /* DiagSubGroup682 */ 572, R"()")
DIAG_ENTRY(PointerToIntCast /* pointer-to-int-cast */, 14705, /* DiagArray683 */ 1960, /* DiagSubGroup683 */ 574, R"()")
DIAG_ENTRY(anonymous_258 /* pointer-type-mismatch */, 14725, /* DiagArray684 */ 1962, 0, R"()")
DIAG_ENTRY(anonymous_85 /* poison-system-directories */, 14747, /* DiagArray685 */ 1964, 0, R"()")
DIAG_ENTRY(ObjCPotentiallyDirectSelector /* potentially-direct-selector */, 14773, /* DiagArray686 */ 1966, 0, R"()")
DIAG_ENTRY(PotentiallyEvaluatedExpression /* potentially-evaluated-expression */, 14801, /* DiagArray687 */ 1968, 0, R"()")
DIAG_ENTRY(PragmaClangAttribute /* pragma-clang-attribute */, 14834, /* DiagArray688 */ 1970, 0, R"()")
DIAG_ENTRY(anonymous_116 /* pragma-once-outside-header */, 14857, /* DiagArray689 */ 1972, 0, R"()")
DIAG_ENTRY(PragmaPack /* pragma-pack */, 14884, /* DiagArray690 */ 1974, /* DiagSubGroup690 */ 577, R"()")
DIAG_ENTRY(PragmaPackSuspiciousInclude /* pragma-pack-suspicious-include */, 14896, /* DiagArray691 */ 1977, 0, R"()")
DIAG_ENTRY(anonymous_117 /* pragma-system-header-outside-header */, 14927, /* DiagArray692 */ 1979, 0, R"()")
DIAG_ENTRY(Pragmas /* pragmas */, 14963, /* DiagArray693 */ 1981, /* DiagSubGroup693 */ 579, R"()")
DIAG_ENTRY(CXXPre14Compat /* pre-c++14-compat */, 14971, /* DiagArray694 */ 1984, 0, R"()")
DIAG_ENTRY(CXXPre14CompatPedantic /* pre-c++14-compat-pedantic */, 14988, 0, /* DiagSubGroup695 */ 584, R"()")
DIAG_ENTRY(CXXPre17Compat /* pre-c++17-compat */, 15014, /* DiagArray696 */ 1996, 0, R"()")
DIAG_ENTRY(CXXPre17CompatPedantic /* pre-c++17-compat-pedantic */, 15031, /* DiagArray697 */ 2014, /* DiagSubGroup697 */ 587, R"()")
DIAG_ENTRY(CXXPre20Compat /* pre-c++20-compat */, 15057, /* DiagArray698 */ 2017, 0, R"()")
DIAG_ENTRY(CXXPre20CompatPedantic /* pre-c++20-compat-pedantic */, 15074, /* DiagArray699 */ 2045, /* DiagSubGroup699 */ 589, R"()")
DIAG_ENTRY(CXXPre23Compat /* pre-c++23-compat */, 15100, /* DiagArray700 */ 2048, 0, R"()")
DIAG_ENTRY(CXXPre23CompatPedantic /* pre-c++23-compat-pedantic */, 15117, 0, /* DiagSubGroup701 */ 591, R"()")
DIAG_ENTRY(CXXPre26Compat /* pre-c++26-compat */, 15143, 0, 0, R"()")
DIAG_ENTRY(CXXPre26CompatPedantic /* pre-c++26-compat-pedantic */, 15160, 0, /* DiagSubGroup703 */ 593, R"()")
DIAG_ENTRY(anonymous_18 /* pre-c++2c-compat */, 15186, 0, /* DiagSubGroup704 */ 595, R"()")
DIAG_ENTRY(anonymous_19 /* pre-c++2c-compat-pedantic */, 15203, 0, /* DiagSubGroup705 */ 597, R"()")
DIAG_ENTRY(CPre2xCompat /* pre-c2x-compat */, 15229, /* DiagArray706 */ 2064, 0, R"()")
DIAG_ENTRY(CPre2xCompatPedantic /* pre-c2x-compat-pedantic */, 15244, 0, /* DiagSubGroup707 */ 599, R"()")
DIAG_ENTRY(OpenMPPre51Compat /* pre-openmp-51-compat */, 15268, /* DiagArray708 */ 2077, 0, R"()")
DIAG_ENTRY(anonymous_148 /* predefined-identifier-outside-function */, 15289, /* DiagArray709 */ 2079, 0, R"()")
DIAG_ENTRY(PrivateExtern /* private-extern */, 15328, /* DiagArray710 */ 2081, 0, R"()")
DIAG_ENTRY(anonymous_128 /* private-header */, 15343, /* DiagArray711 */ 2083, 0, R"()")
DIAG_ENTRY(PrivateModule /* private-module */, 15358, /* DiagArray712 */ 2085, 0, R"()")
DIAG_ENTRY(ProfileInstrMissing /* profile-instr-missing */, 15373, /* DiagArray713 */ 2090, 0, R"()")
DIAG_ENTRY(ProfileInstrOutOfDate /* profile-instr-out-of-date */, 15395, /* DiagArray714 */ 2092, 0, R"()")
DIAG_ENTRY(ProfileInstrUnprofiled /* profile-instr-unprofiled */, 15421, /* DiagArray715 */ 2094, 0, R"()")
DIAG_ENTRY(PropertyAccessDotSyntax /* property-access-dot-syntax */, 15446, /* DiagArray716 */ 2096, 0, R"()")
DIAG_ENTRY(PropertyAttr /* property-attribute-mismatch */, 15473, /* DiagArray717 */ 2098, 0, R"()")
DIAG_ENTRY(Protocol /* protocol */, 15501, /* DiagArray718 */ 2103, 0, R"()")
DIAG_ENTRY(anonymous_162 /* protocol-property-synthesis-ambiguity */, 15510, /* DiagArray719 */ 2105, 0, R"()")
DIAG_ENTRY(anonymous_100 /* psabi */, 15548, /* DiagArray720 */ 2107, 0, R"()")
DIAG_ENTRY(anonymous_227 /* qualified-void-return-type */, 15554, /* DiagArray721 */ 2109, 0, R"()")
DIAG_ENTRY(FrameworkHdrQuotedInclude /* quoted-include-in-framework-header */, 15581, /* DiagArray722 */ 2111, 0, R"()")
DIAG_ENTRY(RangeLoopAnalysis /* range-loop-analysis */, 15616, 0, /* DiagSubGroup723 */ 601, R"()")
DIAG_ENTRY(RangeLoopBindReference /* range-loop-bind-reference */, 15636, /* DiagArray724 */ 2113, 0, R"()")
DIAG_ENTRY(RangeLoopConstruct /* range-loop-construct */, 15662, /* DiagArray725 */ 2115, 0, R"()")
DIAG_ENTRY(anonymous_285 /* read-modules-implicitly */, 15683, /* DiagArray726 */ 2118, 0, R"()")
DIAG_ENTRY(ReadOnlyPlacementChecks /* read-only-types */, 15707, /* DiagArray727 */ 2120, 0, R"()")
DIAG_ENTRY(anonymous_172 /* readonly-iboutlet-property */, 15723, /* DiagArray728 */ 2122, 0, R"()")
DIAG_ENTRY(ObjCReceiver /* receiver-expr */, 15750, /* DiagArray729 */ 2124, 0, R"()")
DIAG_ENTRY(ForwardClassReceiver /* receiver-forward-class */, 15764, /* DiagArray730 */ 2126, 0, R"()")
DIAG_ENTRY(RedeclaredClassMember /* redeclared-class-member */, 15787, /* DiagArray731 */ 2129, 0, R"()")
DIAG_ENTRY(anonymous_175 /* redundant-consteval-if */, 15811, /* DiagArray732 */ 2131, 0, R"()")
DIAG_ENTRY(anonymous_39 /* redundant-decls */, 15834, 0, 0, R"()")
DIAG_ENTRY(RedundantMove /* redundant-move */, 15850, /* DiagArray734 */ 2133, 0, R"()")
DIAG_ENTRY(anonymous_150 /* redundant-parens */, 15865, /* DiagArray735 */ 2135, 0, R"()")
DIAG_ENTRY(Register /* register */, 15882, /* DiagArray736 */ 2137, /* DiagSubGroup736 */ 604, R"()")
DIAG_ENTRY(ReinterpretBaseClass /* reinterpret-base-class */, 15891, /* DiagArray737 */ 2139, 0, R"()")
DIAG_ENTRY(RemarkBackendPlugin /* remark-backend-plugin */, 15914, /* DiagArray738 */ 2141, 0, R"()")
DIAG_ENTRY(Reorder /* reorder */, 15936, 0, /* DiagSubGroup739 */ 606, R"()")
DIAG_ENTRY(ReorderCtor /* reorder-ctor */, 15944, /* DiagArray740 */ 2143, 0, R"()")
DIAG_ENTRY(ReorderInitList /* reorder-init-list */, 15957, /* DiagArray741 */ 2146, 0, R"()")
DIAG_ENTRY(anonymous_206 /* requires-super-attribute */, 15975, /* DiagArray742 */ 2148, 0, R"()")
DIAG_ENTRY(ReservedIdAsMacroAlias /* reserved-id-macro */, 16000, 0, /* DiagSubGroup743 */ 609, R"()")
DIAG_ENTRY(ReservedIdentifier /* reserved-identifier */, 16018, /* DiagArray744 */ 2150, /* DiagSubGroup744 */ 611, R"()")
DIAG_ENTRY(ReservedIdAsMacro /* reserved-macro-identifier */, 16038, /* DiagArray745 */ 2152, 0, R"()")
DIAG_ENTRY(ReservedModuleIdentifier /* reserved-module-identifier */, 16064, /* DiagArray746 */ 2154, 0, R"()")
DIAG_ENTRY(ReservedUserDefinedLiteral /* reserved-user-defined-literal */, 16091, /* DiagArray747 */ 2156, /* DiagSubGroup747 */ 615, R"()")
DIAG_ENTRY(RestrictExpansionMacro /* restrict-expansion */, 16121, /* DiagArray748 */ 2159, 0, R"()")
DIAG_ENTRY(anonymous_220 /* retained-language-linkage */, 16140, /* DiagArray749 */ 2161, 0, R"()")
DIAG_ENTRY(anonymous_26 /* return-local-addr */, 16166, 0, /* DiagSubGroup750 */ 617, R"()")
DIAG_ENTRY(ReturnStackAddress /* return-stack-address */, 16184, /* DiagArray751 */ 2163, 0, R"()")
DIAG_ENTRY(ReturnStdMove /* return-std-move */, 16205, 0, 0, R"()")
DIAG_ENTRY(ReturnType /* return-type */, 16221, /* DiagArray753 */ 2167, /* DiagSubGroup753 */ 619, R"()")
DIAG_ENTRY(ReturnTypeCLinkage /* return-type-c-linkage */, 16233, /* DiagArray754 */ 2177, 0, R"()")
DIAG_ENTRY(anonymous_208 /* rewrite-not-bool */, 16255, /* DiagArray755 */ 2180, 0, R"()")
DIAG_ENTRY(RoundTripCC1Args /* round-trip-cc1-args */, 16272, /* DiagArray756 */ 2182, 0, R"()")
DIAG_ENTRY(RTTI /* rtti */, 16292, /* DiagArray757 */ 2184, 0, R"()")
DIAG_ENTRY(SanitizeAddressRemarks /* sanitize-address */, 16297, /* DiagArray758 */ 2187, 0, R"()")
DIAG_ENTRY(anonymous_94 /* sarif-format-unstable */, 16314, /* DiagArray759 */ 2190, 0, R"()")
DIAG_ENTRY(UsedSearchPath /* search-path-usage */, 16336, /* DiagArray760 */ 2192, 0, R"()")
DIAG_ENTRY(Section /* section */, 16354, /* DiagArray761 */ 2194, 0, R"()")
DIAG_ENTRY(Selector /* selector */, 16362, /* DiagArray762 */ 2198, /* DiagSubGroup762 */ 621, R"()")
DIAG_ENTRY(SelectorTypeMismatch /* selector-type-mismatch */, 16371, /* DiagArray763 */ 2200, 0, R"()")
DIAG_ENTRY(SelfAssignment /* self-assign */, 16394, /* DiagArray764 */ 2202, /* DiagSubGroup764 */ 623, R"()")
DIAG_ENTRY(SelfAssignmentField /* self-assign-field */, 16406, /* DiagArray765 */ 2204, 0, R"()")
DIAG_ENTRY(SelfAssignmentOverloaded /* self-assign-overloaded */, 16424, /* DiagArray766 */ 2206, 0, R"()")
DIAG_ENTRY(SelfMove /* self-move */, 16447, /* DiagArray767 */ 2208, 0, R"()")
DIAG_ENTRY(SemiBeforeMethodBody /* semicolon-before-method-body */, 16457, /* DiagArray768 */ 2210, 0, R"()")
DIAG_ENTRY(Sentinel /* sentinel */, 16486, /* DiagArray769 */ 2212, 0, R"()")
DIAG_ENTRY(anonymous_43 /* sequence-point */, 16495, 0, /* DiagSubGroup770 */ 626, R"()")
DIAG_ENTRY(SerializedDiagnostics /* serialized-diagnostics */, 16510, /* DiagArray771 */ 2215, 0, R"()")
DIAG_ENTRY(Shadow /* shadow */, 16533, /* DiagArray772 */ 2219, /* DiagSubGroup772 */ 628, R"()")
DIAG_ENTRY(ShadowAll /* shadow-all */, 16540, 0, /* DiagSubGroup773 */ 631, R"()")
DIAG_ENTRY(ShadowField /* shadow-field */, 16551, /* DiagArray774 */ 2221, 0, R"()")
DIAG_ENTRY(ShadowFieldInConstructor /* shadow-field-in-constructor */, 16564, /* DiagArray775 */ 2223, /* DiagSubGroup775 */ 636, R"()")
DIAG_ENTRY(ShadowFieldInConstructorModified /* shadow-field-in-constructor-modified */, 16592, /* DiagArray776 */ 2225, 0, R"()")
DIAG_ENTRY(ShadowIvar /* shadow-ivar */, 16629, /* DiagArray777 */ 2227, 0, R"()")
DIAG_ENTRY(ShadowUncapturedLocal /* shadow-uncaptured-local */, 16641, /* DiagArray778 */ 2229, 0, R"()")
DIAG_ENTRY(anonymous_232 /* shift-count-negative */, 16665, /* DiagArray779 */ 2231, 0, R"()")
DIAG_ENTRY(anonymous_233 /* shift-count-overflow */, 16686, /* DiagArray780 */ 2233, 0, R"()")
DIAG_ENTRY(anonymous_231 /* shift-negative-value */, 16707, /* DiagArray781 */ 2235, 0, R"()")
DIAG_ENTRY(ShiftOpParentheses /* shift-op-parentheses */, 16728, /* DiagArray782 */ 2237, 0, R"()")
DIAG_ENTRY(anonymous_234 /* shift-overflow */, 16749, /* DiagArray783 */ 2239, 0, R"()")
DIAG_ENTRY(anonymous_235 /* shift-sign-overflow */, 16764, /* DiagArray784 */ 2241, 0, R"()")
DIAG_ENTRY(Shorten64To32 /* shorten-64-to-32 */, 16784, /* DiagArray785 */ 2243, 0, R"()")
DIAG_ENTRY(SignCompare /* sign-compare */, 16801, /* DiagArray786 */ 2245, 0, R"()")
DIAG_ENTRY(SignConversion /* sign-conversion */, 16814, /* DiagArray787 */ 2247, 0, R"()")
DIAG_ENTRY(anonymous_40 /* sign-promo */, 16830, 0, 0, R"()")
DIAG_ENTRY(SignedEnumBitfield /* signed-enum-bitfield */, 16841, /* DiagArray789 */ 2251, 0, R"()")
DIAG_ENTRY(anonymous_275 /* signed-unsigned-wchar */, 16862, /* DiagArray790 */ 2253, 0, R"()")
DIAG_ENTRY(SingleBitBitFieldConstantConversion /* single-bit-bitfield-constant-conversion */, 16884, /* DiagArray791 */ 2255, 0, R"()")
DIAG_ENTRY(SizeofArrayArgument /* sizeof-array-argument */, 16924, /* DiagArray792 */ 2257, 0, R"()")
DIAG_ENTRY(SizeofArrayDecay /* sizeof-array-decay */, 16946, /* DiagArray793 */ 2259, 0, R"()")
DIAG_ENTRY(anonymous_202 /* sizeof-array-div */, 16965, /* DiagArray794 */ 2261, 0, R"()")
DIAG_ENTRY(anonymous_201 /* sizeof-pointer-div */, 16982, /* DiagArray795 */ 2263, 0, R"()")
DIAG_ENTRY(SizeofPointerMemaccess /* sizeof-pointer-memaccess */, 17001, /* DiagArray796 */ 2265, 0, R"()")
DIAG_ENTRY(anonymous_90 /* slash-u-filename */, 17026, /* DiagArray797 */ 2268, 0, R"()")
DIAG_ENTRY(anonymous_82 /* slh-asm-goto */, 17043, /* DiagArray798 */ 2270, 0, R"()")
DIAG_ENTRY(anonymous_84 /* sloc-usage */, 17056, /* DiagArray799 */ 2272, 0, R"()")
DIAG_ENTRY(UninitializedSometimes /* sometimes-uninitialized */, 17067, /* DiagArray800 */ 2274, 0, R"()")
DIAG_ENTRY(BackendSourceMgr /* source-mgr */, 17091, /* DiagArray801 */ 2276, 0, R"()")
DIAG_ENTRY(SourceUsesOpenMP /* source-uses-openmp */, 17102, /* DiagArray802 */ 2278, 0, R"()")
DIAG_ENTRY(SpirCompat /* spir-compat */, 17121, /* DiagArray803 */ 2287, 0, R"()")
DIAG_ENTRY(anonymous_75 /* spirv-compat */, 17133, 0, /* DiagSubGroup804 */ 638, R"()")
DIAG_ENTRY(anonymous_80 /* stack-exhausted */, 17146, /* DiagArray805 */ 2289, 0, R"()")
DIAG_ENTRY(anonymous_81 /* stack-protector */, 17162, /* DiagArray806 */ 2291, 0, R"()")
DIAG_ENTRY(StaticFloatInit /* static-float-init */, 17178, /* DiagArray807 */ 2293, /* DiagSubGroup807 */ 640, R"()")
DIAG_ENTRY(StaticInInline /* static-in-inline */, 17196, /* DiagArray808 */ 2295, 0, R"()")
DIAG_ENTRY(anonymous_144 /* static-inline-explicit-instantiation */, 17213, /* DiagArray809 */ 2298, 0, R"()")
DIAG_ENTRY(StaticLocalInInline /* static-local-in-inline */, 17250, /* DiagArray810 */ 2300, 0, R"()")
DIAG_ENTRY(UninitializedStaticSelfInit /* static-self-init */, 17273, /* DiagArray811 */ 2302, 0, R"()")
DIAG_ENTRY(anonymous_93 /* stdlibcxx-not-found */, 17290, /* DiagArray812 */ 2304, 0, R"()")
DIAG_ENTRY(anonymous_47 /* strict-aliasing */, 17310, 0, 0, R"()")
DIAG_ENTRY(anonymous_44 /* strict-aliasing=0 */, 17326, 0, 0, R"()")
DIAG_ENTRY(anonymous_45 /* strict-aliasing=1 */, 17344, 0, 0, R"()")
DIAG_ENTRY(anonymous_46 /* strict-aliasing=2 */, 17362, 0, 0, R"()")
DIAG_ENTRY(anonymous_54 /* strict-overflow */, 17380, 0, 0, R"()")
DIAG_ENTRY(anonymous_48 /* strict-overflow=0 */, 17396, 0, 0, R"()")
DIAG_ENTRY(anonymous_49 /* strict-overflow=1 */, 17414, 0, 0, R"()")
DIAG_ENTRY(anonymous_50 /* strict-overflow=2 */, 17432, 0, 0, R"()")
DIAG_ENTRY(anonymous_51 /* strict-overflow=3 */, 17450, 0, 0, R"()")
DIAG_ENTRY(anonymous_52 /* strict-overflow=4 */, 17468, 0, 0, R"()")
DIAG_ENTRY(anonymous_53 /* strict-overflow=5 */, 17486, 0, 0, R"()")
DIAG_ENTRY(ObjCStrictPotentiallyDirectSelector /* strict-potentially-direct-selector */, 17504, /* DiagArray824 */ 2306, /* DiagSubGroup824 */ 642, R"()")
DIAG_ENTRY(StrictPrototypes /* strict-prototypes */, 17539, /* DiagArray825 */ 2308, /* DiagSubGroup825 */ 644, R"()")
DIAG_ENTRY(StrictSelector /* strict-selector-match */, 17557, /* DiagArray826 */ 2310, 0, R"()")
DIAG_ENTRY(StringCompare /* string-compare */, 17579, /* DiagArray827 */ 2312, 0, R"()")
DIAG_ENTRY(StringConcatation /* string-concatenation */, 17594, /* DiagArray828 */ 2314, 0, R"()")
DIAG_ENTRY(StringConversion /* string-conversion */, 17615, /* DiagArray829 */ 2316, 0, R"()")
DIAG_ENTRY(StringPlusChar /* string-plus-char */, 17633, /* DiagArray830 */ 2318, 0, R"()")
DIAG_ENTRY(StringPlusInt /* string-plus-int */, 17650, /* DiagArray831 */ 2320, 0, R"()")
DIAG_ENTRY(anonymous_155 /* strlcpy-strlcat-size */, 17666, /* DiagArray832 */ 2322, 0, R"()")
DIAG_ENTRY(StrncatSize /* strncat-size */, 17687, /* DiagArray833 */ 2324, 0, R"()")
DIAG_ENTRY(CXX11WarnSuggestOverrideDestructor /* suggest-destructor-override */, 17700, /* DiagArray834 */ 2328, 0, R"()")
DIAG_ENTRY(CXX11WarnSuggestOverride /* suggest-override */, 17728, /* DiagArray835 */ 2330, 0, R"()")
DIAG_ENTRY(SuperSubClassMismatch /* super-class-method-mismatch */, 17745, /* DiagArray836 */ 2332, 0, R"()")
DIAG_ENTRY(SuspiciousBzero /* suspicious-bzero */, 17773, /* DiagArray837 */ 2334, 0, R"()")
DIAG_ENTRY(SuspiciousMemaccess /* suspicious-memaccess */, 17790, 0, /* DiagSubGroup838 */ 646, R"()")
DIAG_ENTRY(SwiftNameAttribute /* swift-name-attribute */, 17811, /* DiagArray839 */ 2336, 0, R"()")
DIAG_ENTRY(Switch /* switch */, 17832, /* DiagArray840 */ 2350, 0, R"()")
DIAG_ENTRY(SwitchBool /* switch-bool */, 17839, /* DiagArray841 */ 2354, 0, R"()")
DIAG_ENTRY(anonymous_41 /* switch-default */, 17851, 0, 0, R"()")
DIAG_ENTRY(SwitchEnum /* switch-enum */, 17866, /* DiagArray843 */ 2356, 0, R"()")
DIAG_ENTRY(SyncAlignment /* sync-alignment */, 17878, /* DiagArray844 */ 2358, 0, R"()")
DIAG_ENTRY(anonymous_274 /* sync-fetch-and-nand-semantics-changed */, 17893, /* DiagArray845 */ 2360, 0, R"()")
DIAG_ENTRY(anonymous_42 /* synth */, 17931, 0, 0, R"()")
DIAG_ENTRY(TargetClonesMixedSpecifiers /* target-clones-mixed-specifiers */, 17937, /* DiagArray847 */ 2362, 0, R"()")
DIAG_ENTRY(TautologicalBitwiseCompare /* tautological-bitwise-compare */, 17968, /* DiagArray848 */ 2364, 0, R"()")
DIAG_ENTRY(TautologicalCompare /* tautological-compare */, 17997, /* DiagArray849 */ 2367, /* DiagSubGroup849 */ 652, R"()")
DIAG_ENTRY(TautologicalConstantCompare /* tautological-constant-compare */, 18018, /* DiagArray850 */ 2370, /* DiagSubGroup850 */ 659, R"()")
DIAG_ENTRY(TautologicalInRangeCompare /* tautological-constant-in-range-compare */, 18048, 0, /* DiagSubGroup851 */ 661, R"()")
DIAG_ENTRY(TautologicalOutOfRangeCompare /* tautological-constant-out-of-range-compare */, 18087, /* DiagArray852 */ 2374, 0, R"()")
DIAG_ENTRY(TautologicalObjCBoolCompare /* tautological-objc-bool-compare */, 18130, /* DiagArray853 */ 2376, 0, R"()")
DIAG_ENTRY(TautologicalOverlapCompare /* tautological-overlap-compare */, 18161, /* DiagArray854 */ 2378, 0, R"()")
DIAG_ENTRY(TautologicalPointerCompare /* tautological-pointer-compare */, 18190, /* DiagArray855 */ 2380, 0, R"()")
DIAG_ENTRY(TautologicalTypeLimitCompare /* tautological-type-limit-compare */, 18219, /* DiagArray856 */ 2383, 0, R"()")
DIAG_ENTRY(TautologicalUndefinedCompare /* tautological-undefined-compare */, 18251, /* DiagArray857 */ 2385, 0, R"()")
DIAG_ENTRY(TautologicalUnsignedCharZeroCompare /* tautological-unsigned-char-zero-compare */, 18282, /* DiagArray858 */ 2388, 0, R"()")
DIAG_ENTRY(TautologicalUnsignedEnumZeroCompare /* tautological-unsigned-enum-zero-compare */, 18322, /* DiagArray859 */ 2390, 0, R"()")
DIAG_ENTRY(TautologicalUnsignedZeroCompare /* tautological-unsigned-zero-compare */, 18362, /* DiagArray860 */ 2392, 0, R"()")
DIAG_ENTRY(TautologicalValueRangeCompare /* tautological-value-range-compare */, 18397, /* DiagArray861 */ 2394, 0, R"()")
DIAG_ENTRY(anonymous_283 /* tcb-enforcement */, 18430, /* DiagArray862 */ 2396, 0, R"()")
DIAG_ENTRY(anonymous_238 /* tentative-definition-incomplete-type */, 18446, /* DiagArray863 */ 2398, 0, R"()")
DIAG_ENTRY(ThreadSafety /* thread-safety */, 18483, 0, /* DiagSubGroup864 */ 664, R"()")
DIAG_ENTRY(ThreadSafetyAnalysis /* thread-safety-analysis */, 18497, /* DiagArray865 */ 2400, 0, R"()")
DIAG_ENTRY(ThreadSafetyAttributes /* thread-safety-attributes */, 18520, /* DiagArray866 */ 2419, 0, R"()")
DIAG_ENTRY(ThreadSafetyBeta /* thread-safety-beta */, 18545, /* DiagArray867 */ 2426, 0, R"()")
DIAG_ENTRY(ThreadSafetyNegative /* thread-safety-negative */, 18564, /* DiagArray868 */ 2428, 0, R"()")
DIAG_ENTRY(ThreadSafetyPrecise /* thread-safety-precise */, 18587, /* DiagArray869 */ 2430, 0, R"()")
DIAG_ENTRY(ThreadSafetyReference /* thread-safety-reference */, 18609, /* DiagArray870 */ 2434, 0, R"()")
DIAG_ENTRY(ThreadSafetyVerbose /* thread-safety-verbose */, 18633, /* DiagArray871 */ 2437, 0, R"()")
DIAG_ENTRY(Trigraphs /* trigraphs */, 18655, /* DiagArray872 */ 2439, 0, R"()")
DIAG_ENTRY(TypeLimits /* type-limits */, 18665, 0, /* DiagSubGroup873 */ 669, R"()")
DIAG_ENTRY(TypeSafety /* type-safety */, 18677, /* DiagArray874 */ 2444, 0, R"()")
DIAG_ENTRY(anonymous_219 /* typedef-redefinition */, 18689, /* DiagArray875 */ 2448, 0, R"()")
DIAG_ENTRY(anonymous_213 /* typename-missing */, 18710, /* DiagArray876 */ 2450, 0, R"()")
DIAG_ENTRY(anonymous_97 /* unable-to-open-stats-file */, 18727, /* DiagArray877 */ 2452, 0, R"()")
DIAG_ENTRY(UnalignedAccess /* unaligned-access */, 18753, /* DiagArray878 */ 2454, 0, R"()")
DIAG_ENTRY(anonymous_277 /* unaligned-qualifier-implicit-cast */, 18770, /* DiagArray879 */ 2456, 0, R"()")
DIAG_ENTRY(UnavailableDeclarations /* unavailable-declarations */, 18804, /* DiagArray880 */ 2458, 0, R"()")
DIAG_ENTRY(UndeclaredSelector /* undeclared-selector */, 18829, /* DiagArray881 */ 2460, 0, R"()")
DIAG_ENTRY(anonymous_120 /* undef */, 18849, /* DiagArray882 */ 2463, 0, R"()")
DIAG_ENTRY(anonymous_121 /* undef-prefix */, 18855, /* DiagArray883 */ 2465, 0, R"()")
DIAG_ENTRY(UndefinedBoolConversion /* undefined-bool-conversion */, 18868, /* DiagArray884 */ 2467, 0, R"()")
DIAG_ENTRY(UndefinedFuncTemplate /* undefined-func-template */, 18894, /* DiagArray885 */ 2470, 0, R"()")
DIAG_ENTRY(anonymous_218 /* undefined-inline */, 18918, /* DiagArray886 */ 2472, 0, R"()")
DIAG_ENTRY(anonymous_216 /* undefined-internal */, 18935, /* DiagArray887 */ 2474, 0, R"()")
DIAG_ENTRY(anonymous_217 /* undefined-internal-type */, 18954, /* DiagArray888 */ 2476, 0, R"()")
DIAG_ENTRY(UndefinedReinterpretCast /* undefined-reinterpret-cast */, 18978, /* DiagArray889 */ 2478, 0, R"()")
DIAG_ENTRY(UndefinedVarTemplate /* undefined-var-template */, 19005, /* DiagArray890 */ 2481, 0, R"()")
DIAG_ENTRY(UnderalignedExceptionObject /* underaligned-exception-object */, 19028, /* DiagArray891 */ 2483, 0, R"()")
DIAG_ENTRY(UnevaluatedExpression /* unevaluated-expression */, 19058, /* DiagArray892 */ 2485, /* DiagSubGroup892 */ 674, R"()")
DIAG_ENTRY(UnguardedAvailability /* unguarded-availability */, 19081, /* DiagArray893 */ 2487, /* DiagSubGroup893 */ 676, R"()")
DIAG_ENTRY(UnguardedAvailabilityNew /* unguarded-availability-new */, 19104, /* DiagArray894 */ 2489, 0, R"()")
DIAG_ENTRY(Unicode /* unicode */, 19131, /* DiagArray895 */ 2491, 0, R"()")
DIAG_ENTRY(anonymous_106 /* unicode-homoglyph */, 19139, /* DiagArray896 */ 2499, 0, R"()")
DIAG_ENTRY(anonymous_105 /* unicode-whitespace */, 19157, /* DiagArray897 */ 2501, 0, R"()")
DIAG_ENTRY(anonymous_107 /* unicode-zero-width */, 19176, /* DiagArray898 */ 2503, 0, R"()")
DIAG_ENTRY(Uninitialized /* uninitialized */, 19195, /* DiagArray899 */ 2505, /* DiagSubGroup899 */ 678, R"()")
DIAG_ENTRY(UninitializedConstReference /* uninitialized-const-reference */, 19209, /* DiagArray900 */ 2513, 0, R"()")
DIAG_ENTRY(UnknownArgument /* unknown-argument */, 19239, /* DiagArray901 */ 2515, 0, R"()")
DIAG_ENTRY(UnknownAssumption /* unknown-assumption */, 19256, /* DiagArray902 */ 2519, 0, R"()")
DIAG_ENTRY(UnknownAttributes /* unknown-attributes */, 19275, /* DiagArray903 */ 2521, 0, R"()")
DIAG_ENTRY(CudaUnknownVersion /* unknown-cuda-version */, 19294, /* DiagArray904 */ 2523, 0, R"()")
DIAG_ENTRY(anonymous_125 /* unknown-directives */, 19315, /* DiagArray905 */ 2526, 0, R"()")
DIAG_ENTRY(anonymous_110 /* unknown-escape-sequence */, 19334, /* DiagArray906 */ 2528, 0, R"()")
DIAG_ENTRY(UnknownPragmas /* unknown-pragmas */, 19358, /* DiagArray907 */ 2530, 0, R"()")
DIAG_ENTRY(UnknownSanitizers /* unknown-sanitizers */, 19374, /* DiagArray908 */ 2551, 0, R"()")
DIAG_ENTRY(UnknownWarningOption /* unknown-warning-option */, 19393, /* DiagArray909 */ 2553, 0, R"()")
DIAG_ENTRY(UnnamedTypeTemplateArgs /* unnamed-type-template-args */, 19416, /* DiagArray910 */ 2557, /* DiagSubGroup910 */ 682, R"()")
DIAG_ENTRY(UnneededInternalDecl /* unneeded-internal-declaration */, 19443, /* DiagArray911 */ 2559, 0, R"()")
DIAG_ENTRY(UnneededMemberFunction /* unneeded-member-function */, 19473, /* DiagArray912 */ 2562, 0, R"()")
DIAG_ENTRY(anonymous_209 /* unqualified-std-cast-call */, 19498, /* DiagArray913 */ 2564, 0, R"()")
DIAG_ENTRY(UnreachableCode /* unreachable-code */, 19524, /* DiagArray914 */ 2566, /* DiagSubGroup914 */ 684, R"()")
DIAG_ENTRY(UnreachableCodeAggressive /* unreachable-code-aggressive */, 19541, 0, /* DiagSubGroup915 */ 688, R"()")
DIAG_ENTRY(UnreachableCodeBreak /* unreachable-code-break */, 19569, /* DiagArray916 */ 2568, 0, R"()")
DIAG_ENTRY(UnreachableCodeFallthrough /* unreachable-code-fallthrough */, 19592, /* DiagArray917 */ 2570, 0, R"()")
DIAG_ENTRY(UnreachableCodeGenericAssoc /* unreachable-code-generic-assoc */, 19621, /* DiagArray918 */ 2572, 0, R"()")
DIAG_ENTRY(UnreachableCodeLoopIncrement /* unreachable-code-loop-increment */, 19652, /* DiagArray919 */ 2574, 0, R"()")
DIAG_ENTRY(UnreachableCodeReturn /* unreachable-code-return */, 19684, /* DiagArray920 */ 2576, 0, R"()")
DIAG_ENTRY(UnsafeBufferUsage /* unsafe-buffer-usage */, 19708, /* DiagArray921 */ 2578, 0, R"()")
DIAG_ENTRY(Unsequenced /* unsequenced */, 19728, /* DiagArray922 */ 2581, 0, R"()")
DIAG_ENTRY(UnsupportedABI /* unsupported-abi */, 19740, /* DiagArray923 */ 2584, 0, R"()")
DIAG_ENTRY(UnsupportedAbs /* unsupported-abs */, 19756, /* DiagArray924 */ 2587, 0, R"()")
DIAG_ENTRY(anonymous_198 /* unsupported-availability-guard */, 19772, /* DiagArray925 */ 2590, 0, R"()")
DIAG_ENTRY(UnsupportedCB /* unsupported-cb */, 19803, /* DiagArray926 */ 2592, 0, R"()")
DIAG_ENTRY(anonymous_194 /* unsupported-dll-base-class-template */, 19818, /* DiagArray927 */ 2594, 0, R"()")
DIAG_ENTRY(UnsupportedFPOpt /* unsupported-floating-point-opt */, 19854, /* DiagArray928 */ 2596, 0, R"()")
DIAG_ENTRY(UnsupportedFriend /* unsupported-friend */, 19885, /* DiagArray929 */ 2599, 0, R"()")
DIAG_ENTRY(UnsupportedGPOpt /* unsupported-gpopt */, 19904, /* DiagArray930 */ 2602, 0, R"()")
DIAG_ENTRY(UnsupportedNan /* unsupported-nan */, 19922, /* DiagArray931 */ 2604, 0, R"()")
DIAG_ENTRY(UnsupportedTargetOpt /* unsupported-target-opt */, 19938, /* DiagArray932 */ 2607, 0, R"()")
DIAG_ENTRY(anonymous_204 /* unsupported-visibility */, 19961, /* DiagArray933 */ 2610, 0, R"()")
DIAG_ENTRY(anonymous_211 /* unusable-partial-specialization */, 19984, /* DiagArray934 */ 2612, 0, R"()")
DIAG_ENTRY(Unused /* unused */, 20016, 0, /* DiagSubGroup935 */ 692, R"()")
DIAG_ENTRY(UnusedArgument /* unused-argument */, 20023, 0, 0, R"()")
DIAG_ENTRY(UnusedButSetParameter /* unused-but-set-parameter */, 20039, /* DiagArray937 */ 2614, 0, R"()")
DIAG_ENTRY(UnusedButSetVariable /* unused-but-set-variable */, 20064, /* DiagArray938 */ 2616, 0, R"()")
DIAG_ENTRY(UnusedCommandLineArgument /* unused-command-line-argument */, 20088, /* DiagArray939 */ 2618, 0, R"()")
DIAG_ENTRY(UnusedComparison /* unused-comparison */, 20117, /* DiagArray940 */ 2631, 0, R"()")
DIAG_ENTRY(UnusedConstVariable /* unused-const-variable */, 20135, /* DiagArray941 */ 2633, 0, R"()")
DIAG_ENTRY(UnusedExceptionParameter /* unused-exception-parameter */, 20157, /* DiagArray942 */ 2635, 0, R"()")
DIAG_ENTRY(UnusedFunction /* unused-function */, 20184, /* DiagArray943 */ 2637, /* DiagSubGroup943 */ 703, R"()")
DIAG_ENTRY(UnusedGetterReturnValue /* unused-getter-return-value */, 20200, /* DiagArray944 */ 2639, 0, R"()")
DIAG_ENTRY(UnusedLabel /* unused-label */, 20227, /* DiagArray945 */ 2641, 0, R"()")
DIAG_ENTRY(UnusedLambdaCapture /* unused-lambda-capture */, 20240, /* DiagArray946 */ 2643, 0, R"()")
DIAG_ENTRY(UnusedLocalTypedef /* unused-local-typedef */, 20262, /* DiagArray947 */ 2645, 0, R"()")
DIAG_ENTRY(anonymous_66 /* unused-local-typedefs */, 20283, 0, /* DiagSubGroup948 */ 705, R"()")
DIAG_ENTRY(anonymous_119 /* unused-macros */, 20305, /* DiagArray949 */ 2647, 0, R"()")
DIAG_ENTRY(UnusedMemberFunction /* unused-member-function */, 20319, /* DiagArray950 */ 2649, /* DiagSubGroup950 */ 707, R"()")
DIAG_ENTRY(UnusedParameter /* unused-parameter */, 20342, /* DiagArray951 */ 2651, 0, R"()")
DIAG_ENTRY(UnusedPrivateField /* unused-private-field */, 20359, /* DiagArray952 */ 2653, 0, R"()")
DIAG_ENTRY(UnusedPropertyIvar /* unused-property-ivar */, 20380, /* DiagArray953 */ 2655, 0, R"()")
DIAG_ENTRY(UnusedResult /* unused-result */, 20401, /* DiagArray954 */ 2657, 0, R"()")
DIAG_ENTRY(UnusedTemplate /* unused-template */, 20415, /* DiagArray955 */ 2660, /* DiagSubGroup955 */ 709, R"()")
DIAG_ENTRY(UnusedValue /* unused-value */, 20431, /* DiagArray956 */ 2662, /* DiagSubGroup956 */ 711, R"()")
DIAG_ENTRY(UnusedVariable /* unused-variable */, 20444, /* DiagArray957 */ 2670, /* DiagSubGroup957 */ 715, R"()")
DIAG_ENTRY(anonymous_260 /* unused-volatile-lvalue */, 20460, /* DiagArray958 */ 2672, 0, R"()")
DIAG_ENTRY(UsedButMarkedUnused /* used-but-marked-unused */, 20483, /* DiagArray959 */ 2674, 0, R"()")
DIAG_ENTRY(UserDefinedLiterals /* user-defined-literals */, 20506, /* DiagArray960 */ 2676, 0, R"()")
DIAG_ENTRY(UserDefinedWarnings /* user-defined-warnings */, 20528, /* DiagArray961 */ 2678, 0, R"()")
DIAG_ENTRY(Varargs /* varargs */, 20550, /* DiagArray962 */ 2680, 0, R"()")
DIAG_ENTRY(VariadicMacros /* variadic-macros */, 20558, /* DiagArray963 */ 2684, 0, R"()")
DIAG_ENTRY(anonymous_184 /* vec-elem-size */, 20574, /* DiagArray964 */ 2688, 0, R"()")
DIAG_ENTRY(VectorConversion /* vector-conversion */, 20588, /* DiagArray965 */ 2690, 0, R"()")
DIAG_ENTRY(anonymous_65 /* vector-conversions */, 20606, 0, /* DiagSubGroup966 */ 717, R"()")
DIAG_ENTRY(VexingParse /* vexing-parse */, 20625, /* DiagArray967 */ 2692, 0, R"()")
DIAG_ENTRY(Visibility /* visibility */, 20638, /* DiagArray968 */ 2696, 0, R"()")
DIAG_ENTRY(VLA /* vla */, 20649, /* DiagArray969 */ 2699, /* DiagSubGroup969 */ 719, R"()")
DIAG_ENTRY(VLAExtension /* vla-extension */, 20653, /* DiagArray970 */ 2701, 0, R"()")
DIAG_ENTRY(VoidPointerToEnumCast /* void-pointer-to-enum-cast */, 20667, /* DiagArray971 */ 2703, 0, R"()")
DIAG_ENTRY(VoidPointerToIntCast /* void-pointer-to-int-cast */, 20693, /* DiagArray972 */ 2705, /* DiagSubGroup972 */ 721, R"()")
DIAG_ENTRY(VoidPointerDeref /* void-ptr-dereference */, 20718, /* DiagArray973 */ 2707, 0, R"()")
DIAG_ENTRY(VolatileRegisterVar /* volatile-register-var */, 20739, 0, 0, R"()")
DIAG_ENTRY(WebAssemblyExceptionSpec /* wasm-exception-spec */, 20761, /* DiagArray975 */ 2709, 0, R"()")
DIAG_ENTRY(anonymous_177 /* weak-template-vtables */, 20781, /* DiagArray976 */ 2711, 0, R"()")
DIAG_ENTRY(anonymous_176 /* weak-vtables */, 20803, /* DiagArray977 */ 2713, 0, R"()")
DIAG_ENTRY(WritableStrings /* writable-strings */, 20816, /* DiagArray978 */ 2715, /* DiagSubGroup978 */ 723, R"()")
DIAG_ENTRY(GCCWriteStrings /* write-strings */, 20833, 0, /* DiagSubGroup979 */ 725, R"(**Note:** enabling this warning in C will change the semantic behavior of the
program by treating all string literals as having type ``const char *``
instead of ``char *``. This can cause unexpected behaviors with type-sensitive
constructs like ``_Generic``.)")
DIAG_ENTRY(XorUsedAsPow /* xor-used-as-pow */, 20847, /* DiagArray980 */ 2717, 0, R"()")
DIAG_ENTRY(anonymous_282 /* zero-as-null-pointer-constant */, 20863, /* DiagArray981 */ 2721, 0, R"()")
DIAG_ENTRY(ZeroLengthArray /* zero-length-array */, 20893, /* DiagArray982 */ 2723, 0, R"()")
#endif // DIAG_ENTRY


#ifdef GET_CATEGORY_TABLE
CATEGORY("", DiagCat_None)
CATEGORY("Lexical or Preprocessor Issue", DiagCat_Lexical_or_Preprocessor_Issue)
CATEGORY("Semantic Issue", DiagCat_Semantic_Issue)
CATEGORY("Lambda Issue", DiagCat_Lambda_Issue)
CATEGORY("Parse Issue", DiagCat_Parse_Issue)
CATEGORY("ARC Semantic Issue", DiagCat_ARC_Semantic_Issue)
CATEGORY("ARC and @properties", DiagCat_ARC_and__properties)
CATEGORY("ARC Casting Rules", DiagCat_ARC_Casting_Rules)
CATEGORY("ARC Parse Issue", DiagCat_ARC_Parse_Issue)
CATEGORY("ARC Weak References", DiagCat_ARC_Weak_References)
CATEGORY("ARC Restrictions", DiagCat_ARC_Restrictions)
CATEGORY("OpenMP Issue", DiagCat_OpenMP_Issue)
CATEGORY("Inline Assembly Issue", DiagCat_Inline_Assembly_Issue)
CATEGORY("AST Deserialization Issue", DiagCat_AST_Deserialization_Issue)
CATEGORY("Modules Issue", DiagCat_Modules_Issue)
CATEGORY("Coroutines Issue", DiagCat_Coroutines_Issue)
CATEGORY("Concepts Issue", DiagCat_Concepts_Issue)
CATEGORY("Dependency Directive Source Scanner Issue", DiagCat_Dependency_Directive_Source_Scanner_Issue)
CATEGORY("Backend Issue", DiagCat_Backend_Issue)
CATEGORY("SourceMgr Reported Issue", DiagCat_SourceMgr_Reported_Issue)
CATEGORY("Related Result Type Issue", DiagCat_Related_Result_Type_Issue)
CATEGORY("AST Serialization Issue", DiagCat_AST_Serialization_Issue)
CATEGORY("Nullability Issue", DiagCat_Nullability_Issue)
CATEGORY("Generics Issue", DiagCat_Generics_Issue)
CATEGORY("User-Defined Issue", DiagCat_User_Defined_Issue)
CATEGORY("Refactoring Invocation Issue", DiagCat_Refactoring_Invocation_Issue)
CATEGORY("VTable ABI Issue", DiagCat_VTable_ABI_Issue)
CATEGORY("Value Conversion Issue", DiagCat_Value_Conversion_Issue)
CATEGORY("Documentation Issue", DiagCat_Documentation_Issue)
CATEGORY("ARC Retain Cycle", DiagCat_ARC_Retain_Cycle)
CATEGORY("Deprecations", DiagCat_Deprecations)
CATEGORY("Format String Issue", DiagCat_Format_String_Issue)
CATEGORY("Cocoa API Issue", DiagCat_Cocoa_API_Issue)
CATEGORY("#pragma message Directive", DiagCat__pragma_message_Directive)
CATEGORY("Instrumentation Issue", DiagCat_Instrumentation_Issue)
CATEGORY("Unused Entity Issue", DiagCat_Unused_Entity_Issue)
#endif // GET_CATEGORY_TABLE

