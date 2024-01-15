
/* A friendly warning from bake.test
 * ----------------------------------------------------------------------------
 * This file is generated. To add/remove testcases modify the 'project.json' of
 * the test project. ANY CHANGE TO THIS FILE IS LOST AFTER (RE)BUILDING!
 * ----------------------------------------------------------------------------
 */

#include <query.h>

// Testsuite 'Validator'
void Validator_validate_1_term(void);
void Validator_validate_1_term_component(void);
void Validator_validate_2_terms(void);
void Validator_validate_3_terms(void);
void Validator_validate_3_terms_w_or(void);
void Validator_validate_4_terms_w_or_at_1(void);
void Validator_validate_1_term_wildcard(void);
void Validator_validate_1_term_any(void);
void Validator_validate_1_term_same_subj_obj(void);
void Validator_validate_1_term_acyclic_same_subj_obj(void);
void Validator_validate_1_term_acyclic_reflexive_same_subj_obj(void);
void Validator_validate_1_term_same_subj_obj_var(void);
void Validator_validate_1_term_acyclic_same_subj_obj_var(void);
void Validator_validate_1_term_acyclic_reflexive_same_subj_obj_var(void);
void Validator_validate_1_term_non_acyclic_superset(void);
void Validator_validate_1_term_dont_inherit_default_set(void);
void Validator_validate_1_term_dont_inherit_pair_default_set(void);
void Validator_validate_1_term_cascade_implicit_trav(void);
void Validator_validate_1_term_cascade_isa(void);
void Validator_validate_1_term_cascade_childof(void);
void Validator_validate_1_term_cascade_down(void);
void Validator_validate_1_term_optional_only(void);
void Validator_validate_1_term_transitive_pair(void);
void Validator_validate_1_variable_as_pred_only(void);
void Validator_validate_1_variable_as_pred_w_subj(void);
void Validator_validate_1_variable_as_pred_w_pair(void);
void Validator_validate_1_variable_as_subj(void);
void Validator_validate_1_variable_as_obj(void);
void Validator_validate_2_terms_or_w_dontinherit(void);
void Validator_validate_2_terms_or_w_both_dontinherit(void);
void Validator_validate_w_pair_id(void);
void Validator_validate_w_pred_obj(void);
void Validator_validate_w_pair_id_and_subj(void);
void Validator_validate_1_w_pred_name(void);
void Validator_validate_1_w_final_pred_name(void);
void Validator_validate_1_w_subj_name(void);
void Validator_validate_1_w_obj_name(void);
void Validator_validate_w_this_implicit_variable(void);
void Validator_validate_w_this_explicit_entity(void);
void Validator_validate_w_first_this_implicit_variable(void);
void Validator_validate_w_first_this_explicit_entity(void);
void Validator_validate_w_second_this_implicit_variable(void);
void Validator_validate_w_second_this_explicit_entity(void);
void Validator_validate_w_this_variable_name(void);
void Validator_validate_w_src_var(void);
void Validator_validate_w_first_var(void);
void Validator_validate_w_second_var(void);
void Validator_validate_w_0_source(void);
void Validator_validate_w_0_target(void);
void Validator_validate_2_terms_w_or(void);
void Validator_validate_2_terms_w_or_mixed_src_flags(void);
void Validator_validate_2_terms_w_or_mixed_src_id(void);
void Validator_validate_2_terms_w_or_mixed_src_name(void);
void Validator_validate_2_terms_w_or_same_src_w_id_and_name(void);
void Validator_validate_w_and_flag(void);
void Validator_validate_w_or_flag(void);
void Validator_validate_w_not_flag(void);
void Validator_validate_filter(void);
void Validator_validate_double_init(void);
void Validator_validate_double_init_w_expr(void);
void Validator_validate_double_init_w_expr_optional(void);
void Validator_validate_w_tag_term_is_no_data(void);
void Validator_validate_w_inout_none_term_is_no_data(void);
void Validator_validate_w_tag_and_inout_none_term_is_no_data(void);
void Validator_validate_w_not_term_is_no_data(void);
void Validator_validate_w_no_transitive_pair(void);
void Validator_validate_w_transitive_pair_any_src(void);
void Validator_validate_w_transitive_pair(void);
void Validator_validate_w_transitive_tag_no_pair(void);
void Validator_validate_w_transitive_tag_self_tgt(void);
void Validator_validate_w_transitive_tag_any_tgt(void);
void Validator_validate_w_pair_same_vars(void);
void Validator_validate_w_pair_not_same_vars(void);
void Validator_validate_w_pair_no_vars_not_same_vars(void);
void Validator_validate_w_pair_wildcard_not_same_vars(void);
void Validator_validate_w_pair_any_not_same_vars(void);
void Validator_validate_w_no_pair_not_same_vars(void);
void Validator_validate_not_childof_any(void);
void Validator_validate_w_inherited_id(void);
void Validator_validate_w_inherited_pair(void);
void Validator_validate_w_non_inherited_id(void);
void Validator_validate_w_non_inherited_pair(void);
void Validator_validate_w_first_wildcard_inout_none(void);
void Validator_validate_w_first_var_inout_none(void);
void Validator_validate_w_pair_wildcard_inout_none(void);
void Validator_validate_w_pair_var_inout_none(void);
void Validator_validate_w_unresolved_by_name(void);
void Validator_validate_w_unresolved_by_name_eq(void);
void Validator_validate_childof_this(void);
void Validator_validate_childof_this_entity(void);
void Validator_validate_childof_this_by_id(void);
void Validator_validate_filter_flag(void);

// Testsuite 'Parser'
void Parser_resolve_this(void);
void Parser_resolve_wildcard(void);
void Parser_resolve_any(void);
void Parser_resolve_is_a(void);
void Parser_0(void);
void Parser_component_implicit_subject(void);
void Parser_component_explicit_subject(void);
void Parser_component_explicit_subject_this(void);
void Parser_component_explicit_subject_this_by_name(void);
void Parser_component_explicit_subject_this_by_var_name(void);
void Parser_component_explicit_subject_wildcard(void);
void Parser_component_explicit_subject_any(void);
void Parser_component_explicit_subject_0(void);
void Parser_this_as_predicate(void);
void Parser_this_var_as_predicate(void);
void Parser_this_lowercase_var_as_predicate(void);
void Parser_this_as_object(void);
void Parser_this_var_as_object(void);
void Parser_pair_implicit_subject(void);
void Parser_pair_implicit_subject_wildcard_pred(void);
void Parser_pair_implicit_subject_wildcard_obj(void);
void Parser_pair_implicit_subject_any_pred(void);
void Parser_pair_implicit_subject_any_obj(void);
void Parser_pair_implicit_subject_this_pred(void);
void Parser_pair_implicit_subject_this_obj(void);
void Parser_pair_implicit_subject_pred_w_self(void);
void Parser_pair_implicit_subject_obj_w_self(void);
void Parser_pair_implicit_subject_pred_w_up(void);
void Parser_pair_implicit_subject_obj_w_up(void);
void Parser_pair_implicit_subject_pred_w_self_up(void);
void Parser_pair_implicit_subject_obj_w_self_up(void);
void Parser_pair_implicit_subject_pred_w_invalid_flags(void);
void Parser_pair_implicit_subject_obj_w_invalid_flags(void);
void Parser_pair_explicit_subject(void);
void Parser_pair_explicit_subject_this(void);
void Parser_pair_explicit_subject_this_by_name(void);
void Parser_pair_explicit_subject_this_by_var_name(void);
void Parser_pair_explicit_subject_wildcard_pred(void);
void Parser_pair_explicit_subject_wildcard_subj(void);
void Parser_pair_explicit_subject_wildcard_obj(void);
void Parser_pair_implicit_subject_0_object(void);
void Parser_pair_explicit_subject_0_object(void);
void Parser_pair_explicit_subject_0(void);
void Parser_in_component_implicit_subject(void);
void Parser_in_component_explicit_subject(void);
void Parser_in_pair_implicit_subject(void);
void Parser_in_pair_explicit_subject(void);
void Parser_inout_component_implicit_subject(void);
void Parser_inout_component_explicit_subject(void);
void Parser_inout_pair_implicit_subject(void);
void Parser_inout_pair_explicit_subject(void);
void Parser_out_component_implicit_subject(void);
void Parser_out_component_explicit_subject(void);
void Parser_out_pair_implicit_subject(void);
void Parser_out_pair_explicit_subject(void);
void Parser_inout_filter_component(void);
void Parser_component_singleton(void);
void Parser_this_singleton(void);
void Parser_component_implicit_no_subject(void);
void Parser_component_explicit_no_subject(void);
void Parser_pair_no_subject(void);
void Parser_variable_single_char(void);
void Parser_variable_multi_char(void);
void Parser_variable_multi_char_w_underscore(void);
void Parser_variable_multi_char_w_number(void);
void Parser_variable_multi_char_not_allcaps(void);
void Parser_pred_var(void);
void Parser_obj_var(void);
void Parser_component_not(void);
void Parser_pair_implicit_subject_not(void);
void Parser_pair_explicit_subject_not(void);
void Parser_2_component_not(void);
void Parser_2_component_not_no_space(void);
void Parser_component_optional(void);
void Parser_2_component_optional(void);
void Parser_2_component_optional_no_space(void);
void Parser_from_and(void);
void Parser_from_or(void);
void Parser_from_not(void);
void Parser_pair_implicit_subject_optional(void);
void Parser_pair_explicit_subject_optional(void);
void Parser_pred_implicit_subject_w_role(void);
void Parser_pred_explicit_subject_w_role(void);
void Parser_pred_no_subject_w_role(void);
void Parser_pair_implicit_subject_w_role(void);
void Parser_pair_explicit_subject_w_role(void);
void Parser_inout_role_pred_implicit_subject(void);
void Parser_inout_role_pred_no_subject(void);
void Parser_inout_role_pred_explicit_subject(void);
void Parser_inout_role_pair_implicit_subject(void);
void Parser_inout_role_pair_explicit_subject(void);
void Parser_2_pred_implicit_subject(void);
void Parser_2_pred_no_subject(void);
void Parser_2_pred_explicit_subject(void);
void Parser_2_pair_implicit_subject(void);
void Parser_2_pair_explicit_subject(void);
void Parser_2_pred_role(void);
void Parser_2_pair_implicit_subj_role(void);
void Parser_2_pair_explicit_subj_role(void);
void Parser_2_or_pred_implicit_subj(void);
void Parser_2_or_pred_explicit_subj(void);
void Parser_2_or_pair_implicit_subj(void);
void Parser_2_or_pair_explicit_subj(void);
void Parser_2_or_pred_inout(void);
void Parser_1_digit_pred_implicit_subj(void);
void Parser_1_digit_pred_no_subj(void);
void Parser_1_digit_pred_explicit_subj(void);
void Parser_1_digit_pair_implicit_subj(void);
void Parser_1_digit_pair_explicit_subj(void);
void Parser_pred_implicit_subject_self(void);
void Parser_pred_implicit_subject_superset(void);
void Parser_pred_implicit_subject_superset_inclusive(void);
void Parser_pred_implicit_subject_superset_cascade(void);
void Parser_pred_implicit_subject_superset_inclusive_cascade(void);
void Parser_pred_implicit_subject_implicit_superset_cascade(void);
void Parser_pred_implicit_subject_implicit_superset_inclusive_cascade(void);
void Parser_pred_implicit_subject_implicit_superset_cascade_w_rel(void);
void Parser_pred_implicit_subject_implicit_superset_inclusive_cascade_w_rel(void);
void Parser_pred_implicit_subject_superset_childof(void);
void Parser_pred_implicit_subject_cascade_superset_childof(void);
void Parser_pred_implicit_subject_superset_cascade_childof(void);
void Parser_pred_implicit_subject_superset_cascade_childof_optional(void);
void Parser_expr_w_symbol(void);
void Parser_expr_w_newline(void);
void Parser_subj_entity_w_explicit_self(void);
void Parser_subj_entity_w_explicit_self_superset(void);
void Parser_subj_entity_w_explicit_superset_relation(void);
void Parser_subj_entity_w_explicit_self_superset_relation(void);
void Parser_obj_entity_w_explicit_self(void);
void Parser_obj_entity_w_explicit_self_superset(void);
void Parser_obj_entity_w_explicit_superset_relation(void);
void Parser_obj_entity_w_explicit_self_superset_relation(void);
void Parser_pred_entity_w_explicit_self(void);
void Parser_pred_entity_w_explicit_self_superset(void);
void Parser_pred_entity_no_args_w_explicit_self(void);
void Parser_pred_entity_no_args_w_explicit_self_superset(void);
void Parser_pred_entity_no_args_2_terms_w_explicit_self(void);
void Parser_pred_entity_no_args_2_terms_w_explicit_self_superset(void);
void Parser_newline(void);
void Parser_2_newlines(void);
void Parser_3_newlines(void);
void Parser_space(void);
void Parser_2_spaces(void);
void Parser_trailing_newline(void);
void Parser_2_trailing_newlines(void);
void Parser_trailing_space(void);
void Parser_2_trailing_spaces(void);
void Parser_template_type(void);
void Parser_predicate_w_parens(void);
void Parser_not_alive_pred(void);
void Parser_not_alive_subj(void);
void Parser_not_alive_obj(void);
void Parser_this_subj_var_kind(void);
void Parser_this_obj_var_kind(void);
void Parser_this_subj_obj_var_kind(void);
void Parser_var_w_name(void);
void Parser_entity_pred_no_name(void);
void Parser_entity_subj_no_name(void);
void Parser_entity_obj_no_name(void);
void Parser_this_pred_no_name(void);
void Parser_this_subj_no_name(void);
void Parser_this_obj_no_name(void);
void Parser_auto_object_variable(void);
void Parser_auto_object_variable_w_subj(void);
void Parser_auto_scoped_variable(void);
void Parser_invalid_variable_only(void);
void Parser_oneof_self_pred_w_relative_obj(void);
void Parser_oneof_other_pred_w_relative_obj(void);
void Parser_oneof_self_pred_w_invalid_obj(void);
void Parser_oneof_other_pred_w_invalid_obj(void);
void Parser_pair_implicit_src_missing_rel(void);
void Parser_pair_implicit_src_missing_obj(void);
void Parser_pair_explicit_src_missing_src(void);
void Parser_pair_explicit_src_missing_obj(void);
void Parser_eq_id(void);
void Parser_eq_id_var(void);
void Parser_eq_var_id(void);
void Parser_eq_var_table(void);
void Parser_eq_var(void);
void Parser_neq_id(void);
void Parser_neq_id_var(void);
void Parser_neq_var_id(void);
void Parser_neq_var_table(void);
void Parser_neq_var(void);
void Parser_eq_name(void);
void Parser_eq_name_var(void);
void Parser_eq_var_name(void);
void Parser_neq_name(void);
void Parser_neq_name_var(void);
void Parser_neq_var_name(void);
void Parser_match_name(void);
void Parser_match_name_var(void);
void Parser_match_var_name(void);
void Parser_match_var(void);
void Parser_nmatch_name(void);
void Parser_nmatch_name_var(void);
void Parser_nmatch_var_name(void);
void Parser_eq_same_var(void);
void Parser_neq_same_var(void);
void Parser_eq_same_var_this(void);
void Parser_neq_same_var_this(void);
void Parser_eq_w_optional(void);
void Parser_neq_w_optional(void);
void Parser_match_w_optional(void);
void Parser_query_scope_1_term(void);
void Parser_query_scope_1_term_spaces(void);
void Parser_query_scope_2_terms(void);
void Parser_query_nested_scope(void);
void Parser_query_nested_scope_spaces(void);
void Parser_query_scope_unbalanced(void);
void Parser_query_not_scope(void);
void Parser_query_empty_scope(void);
void Parser_query_scope_newline_after_open(void);
void Parser_query_scope_newline_after_close(void);
void Parser_override_tag(void);
void Parser_override_pair(void);
void Parser_pair_3_args(void);
void Parser_pair_3_args_implicit_this(void);
void Parser_pair_4_args(void);
void Parser_pair_4_args_implicit_this(void);
void Parser_pair_3_args_2_terms(void);
void Parser_pair_3_args_this_tgt(void);
void Parser_pair_3_args_2_terms_this_tgt(void);
void Parser_pair_3_args_2_terms_this_tgt_implicit_this(void);
void Parser_cascade_desc(void);
void Parser_pair_3_or_args(void);
void Parser_pair_3_or_args_implicit_this(void);
void Parser_pair_4_or_args(void);
void Parser_pair_4_or_args_implicit_this(void);
void Parser_pair_or_before_and_oper(void);
void Parser_pair_and_before_or_oper(void);
void Parser_cascade_desc(void);
void Parser_newline_after_inout(void);
void Parser_newline_after_term_open(void);
void Parser_newline_after_term_src(void);
void Parser_newline_after_term_src_pair(void);
void Parser_newline_after_term_pair_comma(void);
void Parser_newline_after_term_pair_second(void);

// Testsuite 'Basic'
void Basic_setup(void);
void Basic_0_query(void);
void Basic_1_fact_w_tag(void);
void Basic_1_fact_w_component(void);
void Basic_1_fact_w_tag_pair(void);
void Basic_1_fact_w_component_pair(void);
void Basic_2_facts_same_src_w_tag(void);
void Basic_2_facts_same_src_w_component(void);
void Basic_2_facts_same_src_w_tag_pair(void);
void Basic_2_facts_same_src_w_component_pair(void);
void Basic_2_facts_other_src_w_tag(void);
void Basic_2_facts_other_src_w_component(void);
void Basic_2_facts_other_src_w_tag_pair(void);
void Basic_2_facts_other_src_w_component_pair(void);
void Basic_1_fact_w_any(void);
void Basic_1_fact_w_pair_any_tgt(void);
void Basic_1_fact_w_pair_any_rel(void);
void Basic_1_fact_w_pair_any_rel_tgt(void);
void Basic_2_facts_same_src_w_any(void);
void Basic_2_facts_same_src_w_pair_any_tgt(void);
void Basic_2_facts_same_src_w_pair_any_rel(void);
void Basic_2_facts_same_src_w_pair_any_rel_tgt(void);
void Basic_2_facts_other_src_w_any(void);
void Basic_2_facts_other_src_w_pair_any_tgt(void);
void Basic_2_facts_other_src_w_pair_any_rel(void);
void Basic_2_facts_other_src_w_pair_any_rel_tgt(void);
void Basic_1_this_src_w_tag(void);
void Basic_1_this_src_w_component(void);
void Basic_1_this_src_w_tag_pair(void);
void Basic_1_this_src_w_component_pair(void);
void Basic_1_this_src_w_tag_2_tables(void);
void Basic_1_this_src_w_component_2_tables(void);
void Basic_1_this_src_w_tag_pair_2_tables(void);
void Basic_1_this_src_w_component_pair_2_tables(void);
void Basic_2_this_src_w_tag(void);
void Basic_2_this_src_w_component(void);
void Basic_2_this_src_ent_src_w_tag(void);
void Basic_2_this_src_ent_src_w_component(void);
void Basic_2_ent_src_this_src_w_tag(void);
void Basic_2_ent_src_this_src_w_component(void);
void Basic_recycled_tag(void);
void Basic_recycled_src(void);
void Basic_recycled_pair_rel(void);
void Basic_recycled_pair_tgt(void);
void Basic_this_src_w_wildcard(void);
void Basic_this_src_w_pair_rel_wildcard(void);
void Basic_this_src_w_pair_tgt_wildcard(void);
void Basic_this_src_w_pair_rel_tgt_wildcard(void);
void Basic_this_src_w_any(void);
void Basic_this_src_w_any_written(void);
void Basic_this_src_w_pair_rel_any(void);
void Basic_this_src_w_pair_tgt_any(void);
void Basic_this_src_w_pair_rel_tgt_any(void);
void Basic_ent_src_w_wildcard(void);
void Basic_ent_src_w_pair_rel_wildcard(void);
void Basic_ent_src_w_pair_tgt_wildcard(void);
void Basic_ent_src_w_pair_rel_tgt_wildcard(void);
void Basic_1_wildcard_src(void);
void Basic_1_wildcard_src_w_pair(void);
void Basic_2_wildcard_src(void);
void Basic_2_wildcard_src_w_pair(void);
void Basic_1_wildcard_src_w_pair_tgt_var(void);
void Basic_1_wildcard_src_w_pair_rel_var(void);
void Basic_1_wildcard_src_w_pair_tgt_this(void);
void Basic_1_wildcard_src_w_pair_rel_this(void);
void Basic_1_any_src(void);
void Basic_1_any_src_w_pair(void);
void Basic_2_any_src(void);
void Basic_2_any_src_w_pair(void);
void Basic_1_any_src_w_pair_tgt_var(void);
void Basic_1_any_src_w_pair_rel_var(void);
void Basic_1_any_src_w_pair_tgt_this(void);
void Basic_1_any_src_w_pair_rel_this(void);
void Basic_not_any(void);
void Basic_rule_w_iter_next(void);
void Basic_empty_rule(void);
void Basic_invalid_rule(void);
void Basic_not_instanced_table_src(void);
void Basic_not_instanced_entity_src(void);
void Basic_not_instanced_mixed_src(void);
void Basic_not_instanced_inherited(void);
void Basic_instanced_table_src(void);
void Basic_instanced_entity_src(void);
void Basic_instanced_mixed_src(void);
void Basic_instanced_inherited(void);
void Basic_in_term(void);
void Basic_out_term(void);
void Basic_inout_term(void);
void Basic_nodata_term(void);
void Basic_find_this_lowercase(void);
void Basic_find_this_uppercase(void);
void Basic_find_this_tgt_lowercase(void);
void Basic_find_this_tgt_uppercase(void);
void Basic_get_filter(void);
void Basic_iter_empty_source(void);
void Basic_iter_empty_source_2_terms(void);
void Basic_iter_empty_source_wildcard(void);
void Basic_iter_empty_source_pair(void);
void Basic_iter_empty_source_pair_wildcard(void);
void Basic_iter_empty_source_2_terms_pair(void);
void Basic_iter_empty_source_2_terms_mixed(void);
void Basic_iter_empty_source_2_terms_mixed_pair(void);
void Basic_iter_empty_source_2_terms_mixed_pair_wildcard(void);
void Basic_this_var_w_empty_entity(void);
void Basic_match_disabled(void);
void Basic_match_prefab(void);
void Basic_match_disabled_prefab(void);
void Basic_match_disabled_this_tgt(void);
void Basic_match_prefab_this_tgt(void);
void Basic_match_disabled_prefab_this_tgt(void);
void Basic_match_self_disabled(void);
void Basic_match_self_prefab(void);
void Basic_match_self_disabled_prefab(void);
void Basic_inout_none_first_term(void);
void Basic_inout_none_second_term(void);
void Basic_inout_none_singleton(void);
void Basic_inout_none_singleton_w_or(void);
void Basic_inout_none_component_w_or(void);
void Basic_no_data_rule(void);
void Basic_frame_offset(void);
void Basic_frame_offset_no_data(void);
void Basic_match_empty_tables(void);
void Basic_match_empty_tables_no_data(void);
void Basic_match_empty_tables_w_not(void);
void Basic_match_empty_tables_w_wildcard(void);
void Basic_match_empty_tables_w_no_empty_tables(void);
void Basic_match_empty_tables_trivial(void);
void Basic_oneof_wildcard(void);
void Basic_oneof_any(void);
void Basic_instanced_w_singleton(void);
void Basic_instanced_w_base(void);
void Basic_not_instanced_w_singleton(void);
void Basic_not_instanced_w_base(void);
void Basic_unknown_before_known(void);
void Basic_unknown_before_known_after_or(void);
void Basic_unknown_before_known_after_not(void);
void Basic_unknown_before_known_after_optional(void);
void Basic_unknown_before_known_after_scope(void);
void Basic_2_trivial_mixed_2_tables(void);
void Basic_2_trivial_mixed_2_tables_component(void);
void Basic_2_trivial_mixed_2_tables_wildcard(void);
void Basic_2_this_w_fixed_src(void);
void Basic_2_fixed_src_w_this(void);
void Basic_2_this_w_fixed_src_no_match_fixed(void);
void Basic_2_fixed_src_w_this_no_match_fixed(void);
void Basic_2_this_w_fixed_src_no_match_this(void);
void Basic_2_fixed_src_w_this_no_match_this(void);
void Basic_query_count_results(void);
void Basic_query_count_entities(void);
void Basic_query_is_true(void);
void Basic_implicit_cleanup_1_term(void);
void Basic_implicit_cleanup_2_terms(void);
void Basic_implicit_cleanup_1_term_w_up(void);
void Basic_implicit_cleanup_2_terms_w_up(void);
void Basic_implicit_cleanup_2_queries(void);
void Basic_implicit_cleanup_2_queries_1_cleanup(void);
void Basic_iter_valid(void);
void Basic_iter_frame_offset(void);
void Basic_iter_nested_1(void);
void Basic_iter_nested_2(void);
void Basic_iter_interleaved(void);
void Basic_set_get_context(void);
void Basic_set_get_binding_context(void);
void Basic_set_get_context_w_free(void);
void Basic_set_get_binding_context_w_free(void);
void Basic_create_query_w_existing_entity(void);

// Testsuite 'Plan'
void Plan_reordered_plan_1(void);
void Plan_reordered_plan_2(void);
void Plan_1_trivial_plan(void);
void Plan_2_trivial_plan(void);
void Plan_1_trivial_plan_component(void);
void Plan_2_trivial_plan_component(void);
void Plan_3_trivial_plan_w_pair(void);
void Plan_3_trivial_plan_w_wildcard(void);
void Plan_3_trivial_plan_w_any(void);
void Plan_3_trivial_plan_w_pair_component(void);
void Plan_3_trivial_plan_w_wildcard_component(void);
void Plan_3_trivial_plan_w_any_component(void);
void Plan_1_trivial_component_w_none(void);
void Plan_2_trivial_component_w_none(void);
void Plan_2_trivial_plan_w_wildcard(void);
void Plan_this_before_fixed_src(void);
void Plan_fixed_src_before_this(void);
void Plan_var_before_fixed_src(void);
void Plan_fixed_src_before_var(void);
void Plan_this_before_fixed_src_w_not(void);
void Plan_this_before_fixed_src_w_first_var(void);
void Plan_this_before_fixed_src_w_first_var_w_not(void);
void Plan_this_before_fixed_src_w_second_var(void);
void Plan_this_before_fixed_src_w_second_var_w_not(void);
void Plan_populate_1_fixed(void);
void Plan_populate_2_fixed(void);
void Plan_populate_1_fixed_1_this_self(void);
void Plan_populate_2_fixed_2_this_self(void);
void Plan_populate_2_fixed_2_this_self_interleaved(void);
void Plan_populate_2_this_self_2_fixed(void);
void Plan_populate_1_fixed_1_this_up(void);
void Plan_populate_2_fixed_2_this_up(void);
void Plan_populate_2_fixed_2_this_up_interleaved(void);
void Plan_populate_2_this_up_2_fixed(void);
void Plan_populate_1_fixed_1_this_self_cached(void);
void Plan_populate_2_fixed_2_this_self_cached(void);
void Plan_populate_2_fixed_2_this_self_interleaved_cached(void);
void Plan_populate_2_this_self_2_fixed_cached(void);
void Plan_populate_1_fixed_1_this_up_cached(void);
void Plan_populate_2_fixed_2_this_up_cached(void);
void Plan_populate_2_fixed_2_this_up_interleaved_cached(void);
void Plan_populate_2_this_up_2_fixed_cached(void);
void Plan_populate_1_fixed_1_var_self(void);
void Plan_populate_2_fixed_2_var_self(void);
void Plan_populate_2_fixed_2_var_self_interleaved(void);
void Plan_populate_2_var_self_2_fixed(void);
void Plan_populate_1_fixed_1_var_up(void);
void Plan_populate_2_fixed_2_var_up(void);
void Plan_populate_2_fixed_2_var_up_interleaved(void);
void Plan_populate_2_var_up_2_fixed(void);
void Plan_cache_2_or(void);
void Plan_cache_2_or_w_not(void);

// Testsuite 'Variables'
void Variables_setup(void);
void Variables_1_ent_src_w_var(void);
void Variables_1_ent_src_w_pair_rel_var(void);
void Variables_1_ent_src_w_pair_tgt_var(void);
void Variables_1_ent_src_w_pair_rel_tgt_var(void);
void Variables_1_ent_src_w_pair_rel_tgt_same_var(void);
void Variables_1_ent_src_w_pair_rel_tgt_same_var_after_write(void);
void Variables_1_this_src_w_var(void);
void Variables_1_this_src_w_pair_rel_var(void);
void Variables_1_this_src_w_pair_tgt_var(void);
void Variables_1_this_src_w_pair_rel_tgt_var(void);
void Variables_1_this_src_w_pair_rel_tgt_same_var(void);
void Variables_1_this_src_w_pair_rel_tgt_same_var_after_write(void);
void Variables_1_src_id_same_var(void);
void Variables_1_src_pair_first_same_var(void);
void Variables_1_src_pair_second_same_var(void);
void Variables_1_src_pair_first_and_second_same_var(void);
void Variables_1_src_id_same_var_after_write(void);
void Variables_1_src_pair_first_same_var_after_write(void);
void Variables_1_src_pair_second_same_var_after_write(void);
void Variables_1_src_pair_first_and_second_same_var_after_write(void);
void Variables_1_src_pair_first_same_var_this(void);
void Variables_1_src_pair_second_same_var_this(void);
void Variables_1_src_pair_first_and_second_same_var_this(void);
void Variables_1_src_id_same_var_this_after_write(void);
void Variables_1_src_pair_first_same_var_this_after_write(void);
void Variables_1_src_pair_second_same_var_this_after_write(void);
void Variables_1_src_pair_first_and_second_same_var_this_after_write(void);
void Variables_1_ent_src_w_this_var(void);
void Variables_1_ent_src_w_pair_this_rel(void);
void Variables_1_ent_src_w_pair_this_tgt(void);
void Variables_1_ent_src_w_pair_this_rel_tgt(void);
void Variables_1_this_src_w_this(void);
void Variables_1_this_src_w_pair_this_rel_tgt(void);
void Variables_1_this_src_w_this_after_write(void);
void Variables_1_this_src_w_pair_this_rel_tgt_after_write(void);
void Variables_2_constrain_src_from_src(void);
void Variables_2_constrain_rel_from_src_w_ent(void);
void Variables_2_constrain_rel_from_src_w_var(void);
void Variables_2_constrain_rel_from_src_w_this(void);
void Variables_2_constrain_pair_rel_from_src_w_ent(void);
void Variables_2_constrain_pair_rel_from_src_w_var(void);
void Variables_2_constrain_pair_rel_from_src_w_this(void);
void Variables_2_constrain_pair_tgt_from_src_w_ent(void);
void Variables_2_constrain_pair_tgt_from_src_w_var(void);
void Variables_2_constrain_pair_tgt_from_src_w_this(void);
void Variables_2_constrain_pair_rel_tgt_from_src_w_ent(void);
void Variables_2_constrain_pair_rel_tgt_from_src_w_var(void);
void Variables_2_constrain_pair_rel_tgt_from_src_w_this(void);
void Variables_1_ent_src_set_rel_var(void);
void Variables_1_ent_src_set_pair_rel_var(void);
void Variables_1_ent_src_set_pair_tgt_var(void);
void Variables_1_set_src_var(void);
void Variables_1_set_src_var_w_pair(void);
void Variables_1_set_src_var_w_pair_set_rel(void);
void Variables_1_set_src_var_w_pair_set_tgt(void);
void Variables_1_set_src_var_w_pair_set_rel_tgt(void);
void Variables_1_set_src_this(void);
void Variables_1_set_src_this_w_pair(void);
void Variables_1_set_src_this_w_pair_set_rel(void);
void Variables_1_set_src_this_w_pair_set_tgt(void);
void Variables_1_set_src_this_w_pair_set_rel_tgt(void);
void Variables_1_set_src_this_to_empty_table(void);
void Variables_1_set_src_this_to_empty_table_w_component(void);
void Variables_1_set_src_this_to_empty_table_w_component_self(void);
void Variables_1_set_src_this_to_entiy_in_table(void);
void Variables_1_set_src_this_to_entiy_in_table_self(void);
void Variables_2_set_src_this(void);
void Variables_2_set_src_this_self(void);
void Variables_2_set_src_this_component(void);
void Variables_2_set_src_this_self_component(void);
void Variables_2_set_src_this_w_up(void);
void Variables_2_set_src_this_self_w_up(void);
void Variables_2_set_src_this_component_w_up(void);
void Variables_2_set_src_this_self_component_w_up(void);
void Variables_2_set_src_this_w_exclusive_wildcard(void);
void Variables_2_set_src_this_self_w_exclusive_wildcard(void);
void Variables_2_set_src_this_self_w_exclusive_wildcard_w_up(void);
void Variables_1_set_src_this_is_true(void);
void Variables_2_set_src_this_w_wildcard(void);
void Variables_1_src_this_var_as_entity(void);
void Variables_1_src_this_var_as_table(void);
void Variables_1_src_this_var_as_table_range(void);
void Variables_2_join_by_rel_var(void);
void Variables_2_join_by_pair_rel_var(void);
void Variables_2_join_by_pair_tgt_var(void);
void Variables_2_cycle_w_var(void);
void Variables_2_cycle_w_this_var(void);
void Variables_2_cycle_w_var_this(void);
void Variables_2_cycle_pair_w_var(void);
void Variables_2_cycle_pair_w_this_var_var(void);
void Variables_2_cycle_pair_w_var_this_var(void);
void Variables_2_cycle_pair_w_var_var_this(void);
void Variables_2_cycle_pair_ent_var_var(void);
void Variables_2_cycle_pair_ent_this_var(void);
void Variables_2_cycle_pair_ent_var_this(void);
void Variables_parse_0_var(void);
void Variables_parse_1_var(void);
void Variables_parse_2_vars(void);
void Variables_parse_0_var_paren(void);
void Variables_parse_1_var_paren(void);
void Variables_parse_2_vars_paren(void);
void Variables_parse_1_vars_w_path(void);
void Variables_parse_missing_close_paren(void);
void Variables_parse_missing_open_paren(void);
void Variables_parse_missing_value(void);
void Variables_parse_0_var_w_spaces(void);
void Variables_parse_1_var_w_spaces(void);
void Variables_parse_2_vars_w_spaces(void);
void Variables_parse_0_var_paren_w_spaces(void);
void Variables_parse_1_var_paren_w_spaces(void);
void Variables_parse_2_vars_paren_w_spaces(void);
void Variables_var_count(void);
void Variables_var_name(void);
void Variables_var_is_entity(void);
void Variables_no_this_anonymous_src(void);
void Variables_no_this_anonymous_src_w_pair(void);
void Variables_no_this_anonymous_component_src(void);
void Variables_no_this_anonymous_component_src_w_pair(void);
void Variables_lookup_from_table_this(void);
void Variables_lookup_from_entity_this(void);
void Variables_lookup_from_table(void);
void Variables_lookup_from_entity(void);
void Variables_lookup_from_not_written(void);
void Variables_lookup_from_table_this_component(void);
void Variables_lookup_from_entity_this_component(void);
void Variables_lookup_from_table_component(void);
void Variables_lookup_from_entity_component(void);
void Variables_lookup_from_table_two_children(void);
void Variables_lookup_from_entity_two_children(void);
void Variables_lookup_from_table_same_child_twice(void);
void Variables_lookup_from_entity_same_child_twice(void);
void Variables_lookup_from_table_not(void);
void Variables_lookup_from_entity_not(void);
void Variables_lookup_from_table_w_any_component(void);
void Variables_lookup_from_entity_w_any_component(void);
void Variables_lookup_as_tag(void);
void Variables_lookup_as_relationship(void);
void Variables_lookup_as_target(void);
void Variables_lookup_assign_var(void);
void Variables_lookup_eq_var(void);
void Variables_lookup_neq_var(void);
void Variables_check_vars_this(void);
void Variables_check_vars_var(void);
void Variables_check_vars_wildcard(void);
void Variables_check_vars_any(void);
void Variables_check_vars_var_as_tgt(void);
void Variables_check_vars_this_as_tgt(void);
void Variables_check_vars_anonymous_var_as_tgt(void);
void Variables_check_vars_wildcard_as_tgt(void);
void Variables_check_vars_any_as_tgt(void);
void Variables_check_vars_this_w_lookup_var(void);
void Variables_check_vars_var_w_lookup_var(void);
void Variables_1_trivial_1_var(void);
void Variables_2_trivial_1_var(void);
void Variables_1_trivial_1_var_component(void);
void Variables_2_trivial_1_var_component(void);
void Variables_1_trivial_1_wildcard(void);
void Variables_2_trivial_1_wildcard(void);
void Variables_1_trivial_1_wildcard_component(void);
void Variables_2_trivial_1_wildcard_component(void);
void Variables_1_trivial_1_any(void);
void Variables_2_trivial_1_any(void);
void Variables_1_trivial_1_any_component(void);
void Variables_2_trivial_1_any_component(void);

// Testsuite 'Operators'
void Operators_setup(void);
void Operators_2_and_not(void);
void Operators_2_and_not_component(void);
void Operators_2_and_out_not(void);
void Operators_2_and_out_not_component(void);
void Operators_3_and_not_not(void);
void Operators_2_and_not_pair_rel_wildcard(void);
void Operators_2_and_not_pair_tgt_wildcard(void);
void Operators_2_and_not_pair_rel_tgt_wildcard(void);
void Operators_2_and_not_pair_rel_var(void);
void Operators_2_and_not_pair_tgt_var(void);
void Operators_2_and_not_pair_rel_tgt_var(void);
void Operators_2_and_not_pair_rel_tgt_same_var(void);
void Operators_2_and_not_pair_rel_var_written(void);
void Operators_2_and_not_pair_tgt_var_written(void);
void Operators_2_and_not_pair_rel_tgt_var_written(void);
void Operators_2_and_not_pair_rel_tgt_same_var_written(void);
void Operators_2_and_not_pair_rel_src_tgt_same_var_written(void);
void Operators_2_and_not_pair_any_rel(void);
void Operators_2_and_not_pair_any_tgt(void);
void Operators_2_and_not_pair_any_src(void);
void Operators_2_and_optional(void);
void Operators_3_and_optional_optional(void);
void Operators_2_and_optional_pair_rel_wildcard(void);
void Operators_2_and_optional_pair_tgt_wildcard(void);
void Operators_2_and_optional_pair_rel_var(void);
void Operators_2_and_optional_pair_tgt_var(void);
void Operators_2_and_optional_pair_rel_tgt_var(void);
void Operators_2_and_optional_pair_rel_tgt_same_var(void);
void Operators_2_and_optional_pair_rel_var_written(void);
void Operators_2_and_optional_pair_tgt_var_written(void);
void Operators_2_and_optional_pair_rel_tgt_var_written(void);
void Operators_2_and_optional_pair_rel_tgt_same_var_written(void);
void Operators_2_and_optional_pair_rel_src_tgt_same_var_written(void);
void Operators_3_and_optional_optional_pair_w_var(void);
void Operators_2_and_optional_pair_any_rel(void);
void Operators_2_and_optional_pair_any_tgt(void);
void Operators_2_and_optional_pair_any_src(void);
void Operators_3_and_optional_dependent_and_pair_rel(void);
void Operators_3_and_optional_dependent_and_pair_tgt(void);
void Operators_3_and_optional_dependent_and_pair_rel_tgt(void);
void Operators_3_and_optional_dependent_and_pair_rel_tgt_same_var(void);
void Operators_3_and_optional_dependent_and_pair_rel_tgt_same_other_var(void);
void Operators_3_and_optional_dependent_and_pair_src(void);
void Operators_3_and_optional_dependent_optional_pair_rel(void);
void Operators_3_and_optional_dependent_optional_pair_tgt(void);
void Operators_3_and_optional_dependent_optional_pair_src(void);
void Operators_3_and_optional_dependent_not_pair_rel(void);
void Operators_3_and_optional_dependent_not_pair_tgt(void);
void Operators_3_and_optional_dependent_not_pair_src(void);
void Operators_2_or(void);
void Operators_3_or(void);
void Operators_2_or_w_and(void);
void Operators_3_or_w_and(void);
void Operators_2_or_written(void);
void Operators_3_or_written(void);
void Operators_2_or_written_w_rel_var(void);
void Operators_3_or_written_w_rel_var(void);
void Operators_2_or_written_w_tgt_var(void);
void Operators_2_or_written_w_rel_tgt_var(void);
void Operators_2_or_written_w_rel_tgt_same_var(void);
void Operators_3_or_written_w_tgt_var(void);
void Operators_2_or_chains(void);
void Operators_2_or_chains_written(void);
void Operators_2_or_dependent(void);
void Operators_2_or_dependent_reverse(void);
void Operators_2_or_dependent_2_vars(void);
void Operators_2_or_written_dependent(void);
void Operators_2_or_written_dependent_2_vars(void);
void Operators_2_or_w_dependent(void);
void Operators_2_or_w_both(void);
void Operators_3_or_w_both(void);
void Operators_2_or_w_not(void);
void Operators_2_or_w_not_component(void);
void Operators_2_or_w_not_out_component(void);
void Operators_2_or_w_not_out_all_components(void);
void Operators_2_not_first(void);
void Operators_2_optional_first(void);
void Operators_only_not(void);
void Operators_only_not_component(void);
void Operators_only_not_out_component(void);
void Operators_only_optional(void);
void Operators_only_optional_component(void);
void Operators_not_after_fixed_src(void);
void Operators_optional_after_fixed_src(void);
void Operators_root_entities_empty(void);
void Operators_root_entities(void);
void Operators_root_entities_w_children(void);
void Operators_root_entities_w_optional_children(void);
void Operators_core_entities_w_optional_children(void);
void Operators_root_entities_w_not_children(void);
void Operators_core_entities_w_not_children(void);
void Operators_1_ent_src_not(void);
void Operators_1_ent_src_not_pair(void);
void Operators_1_ent_src_not_pair_rel_wildcard(void);
void Operators_1_ent_src_not_pair_tgt_wildcard(void);
void Operators_1_ent_src_not_pair_rel_tgt_wildcard(void);
void Operators_1_ent_src_not_pair_rel_any(void);
void Operators_1_ent_src_not_pair_tgt_any(void);
void Operators_1_ent_src_not_pair_rel_tgt_any(void);
void Operators_1_ent_src_not_pair_rel_var(void);
void Operators_1_ent_src_not_pair_tgt_var(void);
void Operators_1_ent_src_not_pair_rel_tgt_var(void);
void Operators_1_ent_src_not_pair_rel_tgt_same_var(void);
void Operators_1_this_src_not_pair_rel_var(void);
void Operators_1_this_src_not_pair_tgt_var(void);
void Operators_1_this_src_not_pair_rel_tgt_var(void);
void Operators_1_this_src_not_pair_rel_tgt_same_var(void);
void Operators_1_ent_src_not_pair_rel_var_written(void);
void Operators_1_ent_src_not_pair_tgt_var_written(void);
void Operators_1_ent_src_not_pair_rel_tgt_var_written(void);
void Operators_1_ent_src_not_pair_rel_tgt_same_var_written(void);
void Operators_and_from_fixed_src(void);
void Operators_not_from_fixed_src(void);
void Operators_or_from_fixed_src(void);
void Operators_and_from_this(void);
void Operators_not_from_this(void);
void Operators_or_from_this(void);
void Operators_and_from_this_written(void);
void Operators_not_from_this_written(void);
void Operators_or_from_this_written(void);

// Testsuite 'Transitive'
void Transitive_1_fact_0_lvl_true(void);
void Transitive_1_fact_1_lvl_true(void);
void Transitive_1_fact_2_lvl_true(void);
void Transitive_1_fact_0_lvl_false(void);
void Transitive_1_fact_1_lvl_false(void);
void Transitive_1_fact_2_lvl_false(void);
void Transitive_1_fact_reflexive(void);
void Transitive_1_isa(void);
void Transitive_1_childof(void);
void Transitive_1_this_src_written_0_lvl(void);
void Transitive_1_this_src_written_1_lvl(void);
void Transitive_1_this_src_written_2_lvl(void);
void Transitive_1_this_src_written_reflexive(void);
void Transitive_1_this_src_0_lvl(void);
void Transitive_1_this_src_1_lvl(void);
void Transitive_1_this_src_2_lvl(void);
void Transitive_1_this_src_reflexive(void);
void Transitive_1_ent_src_tgt_var_0_lvl(void);
void Transitive_1_ent_src_tgt_var_1_lvl(void);
void Transitive_1_ent_src_tgt_var_2_lvl(void);
void Transitive_1_ent_src_tgt_var_reflexive(void);
void Transitive_1_this_src_tgt_var(void);
void Transitive_1_this_src_tgt_var_reflexive(void);
void Transitive_1_var_src_written_0_lvl(void);
void Transitive_1_var_src_written_1_lvl(void);
void Transitive_1_var_src_written_2_lvl(void);
void Transitive_1_var_src_written_reflexive(void);
void Transitive_1_var_src_0_lvl(void);
void Transitive_1_var_src_1_lvl(void);
void Transitive_1_var_src_2_lvl(void);
void Transitive_1_var_src_reflexive(void);
void Transitive_1_var_src_tgt_var(void);
void Transitive_1_var_src_tgt_var_reflexive(void);
void Transitive_1_ent_src_tgt_this_0_lvl(void);
void Transitive_1_ent_src_tgt_this_1_lvl(void);
void Transitive_1_ent_src_tgt_this_2_lvl(void);
void Transitive_1_ent_src_tgt_this_reflexive(void);
void Transitive_1_var_src_tgt_this(void);
void Transitive_1_var_src_tgt_this_reflexive(void);
void Transitive_2_ent_src_constrain_tgt_var_before_0_lvl(void);
void Transitive_2_ent_src_constrain_tgt_var_before_1_lvl(void);
void Transitive_2_ent_src_constrain_tgt_var_before_2_lvl(void);
void Transitive_2_ent_src_constrain_tgt_var_after_0_lvl(void);
void Transitive_2_ent_src_constrain_tgt_var_after_1_lvl(void);
void Transitive_2_ent_src_constrain_tgt_var_after_2_lvl(void);
void Transitive_2_this_src_constrain_tgt_var_before_0_lvl(void);
void Transitive_2_this_src_constrain_tgt_var_before_1_lvl(void);
void Transitive_2_this_src_constrain_tgt_var_before_2_lvl(void);
void Transitive_2_this_src_constrain_tgt_var_after_0_lvl(void);
void Transitive_2_this_src_constrain_tgt_var_after_1_lvl(void);
void Transitive_2_this_src_constrain_tgt_var_after_2_lvl(void);
void Transitive_1_src_tgt_same_var(void);
void Transitive_1_src_tgt_same_var_reflexive(void);
void Transitive_1_src_tgt_same_this_var_reflexive(void);
void Transitive_1_any_src_tgt_var(void);
void Transitive_not_transitive_ent_tgt(void);
void Transitive_not_transitive_var_tgt(void);
void Transitive_not_transitive_ent_tgt_written(void);
void Transitive_not_transitive_var_tgt_written(void);
void Transitive_optional_transitive_ent_tgt(void);
void Transitive_optional_transitive_var_tgt(void);
void Transitive_optional_transitive_ent_tgt_written(void);
void Transitive_optional_transitive_var_tgt_written(void);
void Transitive_2_var_src_w_same_tgt_ent(void);
void Transitive_self_target(void);
void Transitive_any_target(void);

// Testsuite 'ComponentInheritance'
void ComponentInheritance_1_ent_0_lvl(void);
void ComponentInheritance_1_ent_1_lvl(void);
void ComponentInheritance_1_ent_2_lvl(void);
void ComponentInheritance_1_ent_3_lvl(void);
void ComponentInheritance_1_this_0_lvl(void);
void ComponentInheritance_1_this_1_lvl(void);
void ComponentInheritance_1_this_2_lvl(void);
void ComponentInheritance_1_this_3_lvl(void);
void ComponentInheritance_1_this_0_lvl_written(void);
void ComponentInheritance_1_this_1_lvl_written(void);
void ComponentInheritance_1_this_2_lvl_written(void);
void ComponentInheritance_1_this_3_lvl_written(void);
void ComponentInheritance_1_var_0_lvl(void);
void ComponentInheritance_1_var_1_lvl(void);
void ComponentInheritance_1_var_2_lvl(void);
void ComponentInheritance_1_var_3_lvl(void);
void ComponentInheritance_1_var_0_lvl_written(void);
void ComponentInheritance_1_var_1_lvl_written(void);
void ComponentInheritance_1_var_2_lvl_written(void);
void ComponentInheritance_1_var_3_lvl_written(void);
void ComponentInheritance_1_ent_1_lvl_self(void);
void ComponentInheritance_1_this_1_lvl_self(void);
void ComponentInheritance_1_this_1_lvl_written_self(void);
void ComponentInheritance_1_var_1_lvl_self(void);
void ComponentInheritance_1_var_1_lvl_written_self(void);
void ComponentInheritance_1_ent_src_not(void);
void ComponentInheritance_1_this_src_not(void);
void ComponentInheritance_1_var_src_not(void);
void ComponentInheritance_1_this_src_not_written(void);
void ComponentInheritance_1_var_src_not_written(void);
void ComponentInheritance_first_self(void);

// Testsuite 'Recycled'
void Recycled_setup(void);
void Recycled_recycled_vars(void);
void Recycled_recycled_pair_vars(void);
void Recycled_recycled_this_ent_var(void);
void Recycled_has_recycled_id_from_pair(void);
void Recycled_recycled_pair(void);
void Recycled_recycled_component_id(void);

// Testsuite 'BuiltinPredicates'
void BuiltinPredicates_this_eq_id(void);
void BuiltinPredicates_this_eq_name(void);
void BuiltinPredicates_this_eq_var(void);
void BuiltinPredicates_this_eq_id_written(void);
void BuiltinPredicates_this_eq_id_written_no_match(void);
void BuiltinPredicates_this_eq_name_written(void);
void BuiltinPredicates_this_eq_name_written_no_match(void);
void BuiltinPredicates_this_eq_var_written(void);
void BuiltinPredicates_var_eq_id(void);
void BuiltinPredicates_var_eq_name(void);
void BuiltinPredicates_var_eq_var(void);
void BuiltinPredicates_var_eq_id_written(void);
void BuiltinPredicates_var_eq_id_written_no_match(void);
void BuiltinPredicates_var_eq_name_written(void);
void BuiltinPredicates_var_eq_name_written_no_match(void);
void BuiltinPredicates_var_eq_var_written(void);
void BuiltinPredicates_var_eq_this(void);
void BuiltinPredicates_this_neq_id(void);
void BuiltinPredicates_this_neq_name(void);
void BuiltinPredicates_this_neq_var(void);
void BuiltinPredicates_this_neq_id_written(void);
void BuiltinPredicates_this_neq_id_written_no_match(void);
void BuiltinPredicates_this_neq_name_written(void);
void BuiltinPredicates_this_neq_name_written_no_match(void);
void BuiltinPredicates_this_neq_var_written(void);
void BuiltinPredicates_var_neq_id(void);
void BuiltinPredicates_var_neq_name(void);
void BuiltinPredicates_var_neq_var(void);
void BuiltinPredicates_var_neq_id_written(void);
void BuiltinPredicates_var_neq_id_written_no_match(void);
void BuiltinPredicates_var_neq_name_written(void);
void BuiltinPredicates_var_neq_name_written_no_match(void);
void BuiltinPredicates_var_neq_var_written(void);
void BuiltinPredicates_var_neq_this(void);
void BuiltinPredicates_this_2_neq_id(void);
void BuiltinPredicates_this_2_neq_name(void);
void BuiltinPredicates_var_2_neq_id(void);
void BuiltinPredicates_var_2_neq_name(void);
void BuiltinPredicates_this_2_neq_id_written(void);
void BuiltinPredicates_this_2_neq_name_written(void);
void BuiltinPredicates_var_2_neq_id_written(void);
void BuiltinPredicates_var_2_neq_name_written(void);
void BuiltinPredicates_this_2_or_id(void);
void BuiltinPredicates_this_2_or_name(void);
void BuiltinPredicates_var_2_or_id(void);
void BuiltinPredicates_var_2_or_name(void);
void BuiltinPredicates_this_2_or_id_written(void);
void BuiltinPredicates_this_2_or_name_written(void);
void BuiltinPredicates_var_2_or_id_written(void);
void BuiltinPredicates_var_2_or_name_written(void);
void BuiltinPredicates_this_match_eq(void);
void BuiltinPredicates_var_match_eq(void);
void BuiltinPredicates_this_match_eq_written(void);
void BuiltinPredicates_var_match_eq_written(void);
void BuiltinPredicates_this_match_neq(void);
void BuiltinPredicates_var_match_neq(void);
void BuiltinPredicates_this_match_neq_written(void);
void BuiltinPredicates_var_match_neq_written(void);
void BuiltinPredicates_this_match_2_neq(void);
void BuiltinPredicates_var_match_2_neq(void);
void BuiltinPredicates_this_match_2_neq_written(void);
void BuiltinPredicates_var_match_2_neq_written(void);
void BuiltinPredicates_this_match_2_or(void);
void BuiltinPredicates_this_match_2_or_written(void);
void BuiltinPredicates_this_match_3_or(void);
void BuiltinPredicates_this_match_3_or_written(void);
void BuiltinPredicates_unresolved_by_name(void);
void BuiltinPredicates_var_eq_wildcard(void);
void BuiltinPredicates_var_eq_any(void);
void BuiltinPredicates_var_eq_wildcard_after_write(void);
void BuiltinPredicates_var_eq_any_after_write(void);
void BuiltinPredicates_var_eq_after_var_0_src(void);
void BuiltinPredicates_2_or_w_eq_this(void);
void BuiltinPredicates_2_or_w_eq_lookup_var(void);
void BuiltinPredicates_3_or_w_eq_lookup_var(void);

// Testsuite 'Scopes'
void Scopes_term_w_not_scope_1_term(void);
void Scopes_term_w_not_scope_2_terms(void);
void Scopes_term_w_not_scope_1_term_w_not(void);
void Scopes_term_w_not_scope_2_terms_w_not(void);
void Scopes_term_w_not_scope_1_term_w_var(void);
void Scopes_term_w_not_scope_2_terms_w_var(void);
void Scopes_term_w_not_scope_1_term_w_not_w_var(void);
void Scopes_term_w_not_scope_2_terms_w_not_w_var(void);
void Scopes_term_w_not_scope_2_terms_w_or(void);
void Scopes_term_w_not_scope_3_terms_w_or(void);

// Testsuite 'Traversal'
void Traversal_setup(void);
void Traversal_this_self_up_childof(void);
void Traversal_this_up_childof(void);
void Traversal_this_written_self_up_childof(void);
void Traversal_this_written_up_childof(void);
void Traversal_var_self_up_childof(void);
void Traversal_var_up_childof(void);
void Traversal_var_written_self_up_childof(void);
void Traversal_var_written_up_childof(void);
void Traversal_set_var_self_up_childof(void);
void Traversal_set_var_up_childof(void);
void Traversal_set_var_written_self_up_childof(void);
void Traversal_set_var_written_up_childof(void);
void Traversal_ent_self_up_childof(void);
void Traversal_ent_up_childof(void);
void Traversal_implicit_this_self_up_isa(void);
void Traversal_implicit_this_up_isa(void);
void Traversal_implicit_var_self_up_isa(void);
void Traversal_implicit_var_up_isa(void);
void Traversal_implicit_ent_self_up_isa(void);
void Traversal_implicit_ent_up_isa(void);
void Traversal_self_up_2_targets(void);
void Traversal_up_2_targets(void);
void Traversal_self_up_2_targets_diamond(void);
void Traversal_up_2_targets_diamond(void);
void Traversal_written_self_up_2_targets(void);
void Traversal_written_up_2_targets(void);
void Traversal_written_self_up_2_targets_diamond(void);
void Traversal_written_up_2_targets_diamond(void);
void Traversal_2_self_up_terms(void);
void Traversal_2_self_up_terms_2_targets(void);
void Traversal_self_up_empty_table(void);
void Traversal_up_empty_table(void);
void Traversal_self_up_all_owned(void);
void Traversal_up_all_owned(void);
void Traversal_this_self_up_childof_inherited(void);
void Traversal_this_up_childof_inherited(void);
void Traversal_this_written_self_up_childof_inherited(void);
void Traversal_this_written_up_childof_inherited(void);
void Traversal_var_self_up_childof_inherited(void);
void Traversal_var_up_childof_inherited(void);
void Traversal_var_written_self_up_childof_inherited(void);
void Traversal_var_written_up_childof_inherited(void);
void Traversal_ent_self_up_childof_inherited(void);
void Traversal_ent_up_childof_inherited(void);
void Traversal_ent_written_self_up_childof_inherited(void);
void Traversal_ent_written_up_childof_inherited(void);
void Traversal_this_self_up_childof_component(void);
void Traversal_this_up_childof_component(void);
void Traversal_this_written_self_up_childof_component(void);
void Traversal_this_written_up_childof_component(void);
void Traversal_var_self_up_childof_component(void);
void Traversal_var_up_childof_component(void);
void Traversal_var_written_self_up_childof_component(void);
void Traversal_var_written_up_childof_component(void);
void Traversal_this_self_up_childof_recycled_parent(void);
void Traversal_this_up_childof_recycled_parent(void);
void Traversal_this_written_self_up_childof_recycled_parent(void);
void Traversal_this_written_up_childof_recycled_parent(void);
void Traversal_this_self_up_childof_recycled_parent_component(void);
void Traversal_this_up_childof_recycled_parent_component(void);
void Traversal_this_written_self_up_childof_recycled_parent_component(void);
void Traversal_this_written_up_childof_recycled_parent_component(void);
void Traversal_this_self_up_childof_pair(void);
void Traversal_this_up_childof_pair(void);
void Traversal_this_written_self_up_childof_pair(void);
void Traversal_this_written_up_childof_pair(void);
void Traversal_this_self_up_childof_pair_wildcard(void);
void Traversal_this_up_childof_pair_wildcard(void);
void Traversal_this_written_self_up_childof_pair_wildcard(void);
void Traversal_this_written_up_childof_pair_wildcard(void);
void Traversal_this_self_up_childof_pair_tgt_var(void);
void Traversal_this_written_self_up_childof_pair_tgt_var(void);
void Traversal_this_self_up_childof_pair_rel_var(void);
void Traversal_this_written_self_up_childof_pair_rel_var(void);
void Traversal_this_self_up_childof_pair_for_var_written(void);
void Traversal_this_up_childof_pair_for_var_written(void);
void Traversal_this_written_self_up_childof_pair_for_var_written(void);
void Traversal_this_self_up_childof_pair_for_var_written_n_targets(void);
void Traversal_this_written_self_up_childof_pair_for_var_written_n_targets(void);
void Traversal_self_up_2_levels(void);
void Traversal_not_up_disabled(void);
void Traversal_up_2_rel_instances(void);
void Traversal_up_2_rel_instances_match_2nd(void);
void Traversal_up_only_w_owned(void);
void Traversal_this_up_trav_unused_rel(void);
void Traversal_this_optional_self(void);
void Traversal_this_optional_up(void);
void Traversal_this_optional_self_up(void);
void Traversal_this_written_optional_self(void);
void Traversal_this_written_optional_up(void);
void Traversal_this_written_optional_self_up(void);
void Traversal_fixed_src_w_up(void);
void Traversal_match_empty_table_up(void);
void Traversal_match_empty_table_up_written(void);
void Traversal_match_empty_table_up_implicit_isa(void);
void Traversal_match_empty_table_up_written_implicit_isa(void);
void Traversal_match_empty_table_up_isa(void);
void Traversal_match_empty_table_up_written_isa(void);

// Testsuite 'Cascade'
void Cascade_this_self_cascade_childof_uncached(void);
void Cascade_this_cascade_childof_uncached(void);
void Cascade_this_written_self_cascade_childof_uncached(void);
void Cascade_this_written_cascade_childof_uncached(void);
void Cascade_this_self_cascade_childof_w_parent_flag_uncached(void);
void Cascade_this_cascade_childof_w_parent_flag_uncached(void);
void Cascade_this_written_self_cascade_childof_w_parent_flag_uncached(void);
void Cascade_this_written_cascade_childof_w_parent_flag_uncached(void);
void Cascade_parent_cascade(void);
void Cascade_existing_custom_rel_cascade(void);
void Cascade_new_custom_rel_cascade(void);
void Cascade_cascade_w_2_depths(void);
void Cascade_cascade_w_3_depths(void);
void Cascade_cascade_w_2_depths_desc(void);
void Cascade_cascade_w_3_depths_desc(void);
void Cascade_existing_isa_cascade(void);
void Cascade_new_isa_cascade(void);
void Cascade_childof_cascade(void);
void Cascade_cascade_rematch_2_lvls(void);
void Cascade_cascade_rematch_2_lvls_2_relations(void);
void Cascade_cascade_topological(void);
void Cascade_cascade_desc_rematch_2_lvls(void);
void Cascade_cascade_desc_rematch_2_lvls_2_relations(void);
void Cascade_cascade_desc_topological(void);

// Testsuite 'Cached'
void Cached_simple_query_existing_table(void);
void Cached_simple_query_2_existing_tables(void);
void Cached_simple_query_new_table(void);
void Cached_simple_query_2_new_tables(void);
void Cached_simple_query_existing_and_new_table(void);
void Cached_wildcard_query_existing_table(void);
void Cached_wildcard_query_new_table(void);
void Cached_wildcard_query_existing_table_2_results_p_table(void);
void Cached_wildcard_query_new_table_2_results_p_table(void);
void Cached_wildcard_query_2nd_term(void);
void Cached_wildcard_query_2nd_term_self(void);
void Cached_simple_query_existing_empty_table(void);
void Cached_simple_query_existing_empty_type(void);
void Cached_simple_query_new_empty_table(void);
void Cached_component_query_existing_table(void);
void Cached_component_query_new_table(void);
void Cached_component_query_existing_empty_table(void);
void Cached_2_component_query_existing_empty_table(void);
void Cached_2_component_query_existing_empty_type(void);
void Cached_only_optional(void);
void Cached_only_optional_new_empty_table(void);
void Cached_only_optional_new_empty_non_empty_table(void);
void Cached_only_optional_new_unset_tables(void);
void Cached_singleton_w_optional_new_empty_table(void);
void Cached_singleton_w_optional_new_empty_non_empty_table(void);
void Cached_singleton_w_optional_new_unset_tables(void);
void Cached_query_w_from_entity_match_after(void);
void Cached_query_w_from_singleton_match_after(void);
void Cached_query_rematch_optional_after_add(void);
void Cached_get_owned_tag(void);
void Cached_get_shared_tag(void);
void Cached_explicit_delete(void);
void Cached_get_column_size(void);
void Cached_stresstest_query_free(void);
void Cached_query_optional_tag(void);
void Cached_query_optional_shared_tag(void);
void Cached_query_iter_10_tags(void);
void Cached_query_iter_10_components(void);
void Cached_iter_type_set(void);
void Cached_filter_term(void);
void Cached_2_terms_1_filter(void);
void Cached_3_terms_2_filter(void);
void Cached_no_instancing_w_singleton(void);
void Cached_add_singleton_after_query(void);
void Cached_query_w_component_from_parent_from_non_this(void);
void Cached_create_query_while_pending(void);
void Cached_empty_query(void);
void Cached_not_pair_relation_wildcard(void);
void Cached_not_pair_object_wildcard(void);
void Cached_two_pair_wildcards_one_not(void);
void Cached_two_pair_wildcards_one_not_any(void);
void Cached_implicit_existing_isa_superset(void);
void Cached_implicit_new_isa_superset(void);
void Cached_isa_superset(void);
void Cached_isa_superset_2_lvls(void);
void Cached_isa_superset_3_lvls(void);
void Cached_isa_superset_2_lvls_owned(void);
void Cached_isa_superset_3_lvls_owned(void);
void Cached_isa_superset_owned_empty_table_after_match(void);
void Cached_isa_self_superset(void);
void Cached_childof_superset(void);
void Cached_superset_2_targets(void);
void Cached_superset_2_relations(void);
void Cached_superset_2_relations_instanced(void);
void Cached_superset_2_relations_w_component(void);
void Cached_superset_2_relations_instanced_w_component(void);
void Cached_parent(void);
void Cached_isa_rematch(void);
void Cached_childof_rematch(void);
void Cached_isa_unmatch(void);
void Cached_childof_unmatch(void);
void Cached_isa_rematch_2_lvls(void);
void Cached_childof_rematch_2_lvls(void);
void Cached_childof_rematch_from_isa(void);
void Cached_rematch_optional_ref(void);
void Cached_rematch_optional_ref_w_2_refs(void);
void Cached_rematch_optional_ref_tag_w_ref_component(void);
void Cached_match_query_expr_from_scope(void);
void Cached_query_long_or_w_ref(void);
void Cached_query_w_pair_id_and_subj(void);
void Cached_rematch_after_delete_inherited_tag(void);
void Cached_rematch_after_delete_rel_of_inherited_pair(void);
void Cached_rematch_after_delete_obj_of_inherited_pair(void);
void Cached_rematch_empty_table_w_superset(void);
void Cached_2_self_up_terms_new_tables(void);
void Cached_this_self_up_childof_pair_new_tables(void);

// Testsuite 'ChangeDetection'
void ChangeDetection_query_changed_after_new(void);
void ChangeDetection_query_changed_after_delete(void);
void ChangeDetection_query_changed_after_add(void);
void ChangeDetection_query_changed_after_remove(void);
void ChangeDetection_query_changed_after_set(void);
void ChangeDetection_query_change_after_modified(void);
void ChangeDetection_query_change_after_out_system(void);
void ChangeDetection_query_change_after_in_system(void);
void ChangeDetection_query_change_after_modified_out_term(void);
void ChangeDetection_query_change_check_iter(void);
void ChangeDetection_query_change_check_iter_after_skip_read(void);
void ChangeDetection_query_change_check_iter_after_skip_write(void);
void ChangeDetection_query_change_parent_term(void);
void ChangeDetection_query_change_prefab_term(void);
void ChangeDetection_query_change_parent_term_w_tag(void);
void ChangeDetection_query_change_prefab_term_w_tag(void);
void ChangeDetection_query_change_skip_non_instanced(void);
void ChangeDetection_query_changed_w_or(void);
void ChangeDetection_query_changed_or(void);
void ChangeDetection_query_changed_w_singleton(void);
void ChangeDetection_query_changed_w_only_singleton(void);
void ChangeDetection_query_changed_w_only_singleton_after_set(void);
void ChangeDetection_query_changed_w_only_singleton_after_out_term(void);
void ChangeDetection_query_changed_w_only_singleton_after_singleton_out_term(void);
void ChangeDetection_query_changed_w_only_parent(void);
void ChangeDetection_query_changed_w_only_parent_after_set(void);
void ChangeDetection_query_changed_w_only_parent_after_out_term(void);
void ChangeDetection_query_changed_w_only_parent_after_parent_out_term(void);
void ChangeDetection_query_changed_tag(void);
void ChangeDetection_query_changed_no_source(void);
void ChangeDetection_query_changed_no_source_component(void);
void ChangeDetection_query_changed_w_not_out(void);

// Testsuite 'GroupBy'
void GroupBy_group_by(void);
void GroupBy_group_by_w_ctx(void);
void GroupBy_group_by_w_sort_reverse_group_creation(void);
void GroupBy_group_by_iter_one(void);
void GroupBy_group_by_iter_one_all_groups(void);
void GroupBy_group_by_iter_one_empty(void);
void GroupBy_group_by_iter_one_empty_query(void);
void GroupBy_group_by_iter_one_empty_table(void);
void GroupBy_group_by_w_deleted_group_id(void);
void GroupBy_group_by_callbacks(void);
void GroupBy_group_by_default_action(void);
void GroupBy_group_table_count(void);

// Testsuite 'MemberTarget'
void MemberTarget_setup(void);
void MemberTarget_this_member_eq_1(void);
void MemberTarget_this_member_eq_2(void);
void MemberTarget_this_member_eq_no_matches(void);
void MemberTarget_this_member_eq_all_matches(void);
void MemberTarget_this_member_wildcard(void);
void MemberTarget_this_member_var(void);
void MemberTarget_this_member_var_written(void);
void MemberTarget_this_member_var_read(void);
void MemberTarget_this_member_eq_1_2nd_member(void);
void MemberTarget_this_member_eq_2_2nd_member(void);
void MemberTarget_this_member_var_same_1(void);
void MemberTarget_this_member_var_same_2(void);
void MemberTarget_this_written_member_eq_1(void);
void MemberTarget_this_written_member_eq_2(void);
void MemberTarget_this_written_member_wildcard(void);
void MemberTarget_this_written_member_var(void);
void MemberTarget_this_member_neq_1(void);
void MemberTarget_this_member_neq_2(void);
void MemberTarget_this_member_neq_no_matches(void);
void MemberTarget_this_member_neq_all_matches(void);
void MemberTarget_this_member_neq_wildcard(void);
void MemberTarget_this_written_member_neq_1(void);
void MemberTarget_this_written_member_neq_2(void);
void MemberTarget_this_written_member_neq_no_matches(void);
void MemberTarget_this_written_member_neq_all_matches(void);
void MemberTarget_this_written_member_neq_wildcard(void);
void MemberTarget_this_member_eq_optional(void);
void MemberTarget_this_member_eq_optional_wildcard(void);
void MemberTarget_this_written_member_eq_optional(void);
void MemberTarget_this_written_member_eq_optional_wildcard(void);
void MemberTarget_this_2_or(void);
void MemberTarget_this_3_or(void);
void MemberTarget_this_written_2_or(void);
void MemberTarget_this_written_3_or(void);
void MemberTarget_var_member_eq(void);
void MemberTarget_var_member_eq_no_matches(void);
void MemberTarget_var_member_eq_all_matches(void);
void MemberTarget_var_member_wildcard(void);
void MemberTarget_var_member_neq(void);
void MemberTarget_var_member_neq_no_matches(void);
void MemberTarget_var_member_neq_all_matches(void);
void MemberTarget_var_written_member_eq(void);
void MemberTarget_var_written_member_eq_no_matches(void);
void MemberTarget_var_written_member_eq_all_matches(void);
void MemberTarget_var_written_member_wildcard(void);
void MemberTarget_var_written_member_neq(void);
void MemberTarget_var_written_member_neq_no_matches(void);
void MemberTarget_var_written_member_neq_all_matches(void);

// Testsuite 'Toggle'
void Toggle_query_disabled_from_nothing(void);

bake_test_case Validator_testcases[] = {
    {
        "validate_1_term",
        Validator_validate_1_term
    },
    {
        "validate_1_term_component",
        Validator_validate_1_term_component
    },
    {
        "validate_2_terms",
        Validator_validate_2_terms
    },
    {
        "validate_3_terms",
        Validator_validate_3_terms
    },
    {
        "validate_3_terms_w_or",
        Validator_validate_3_terms_w_or
    },
    {
        "validate_4_terms_w_or_at_1",
        Validator_validate_4_terms_w_or_at_1
    },
    {
        "validate_1_term_wildcard",
        Validator_validate_1_term_wildcard
    },
    {
        "validate_1_term_any",
        Validator_validate_1_term_any
    },
    {
        "validate_1_term_same_subj_obj",
        Validator_validate_1_term_same_subj_obj
    },
    {
        "validate_1_term_acyclic_same_subj_obj",
        Validator_validate_1_term_acyclic_same_subj_obj
    },
    {
        "validate_1_term_acyclic_reflexive_same_subj_obj",
        Validator_validate_1_term_acyclic_reflexive_same_subj_obj
    },
    {
        "validate_1_term_same_subj_obj_var",
        Validator_validate_1_term_same_subj_obj_var
    },
    {
        "validate_1_term_acyclic_same_subj_obj_var",
        Validator_validate_1_term_acyclic_same_subj_obj_var
    },
    {
        "validate_1_term_acyclic_reflexive_same_subj_obj_var",
        Validator_validate_1_term_acyclic_reflexive_same_subj_obj_var
    },
    {
        "validate_1_term_non_acyclic_superset",
        Validator_validate_1_term_non_acyclic_superset
    },
    {
        "validate_1_term_dont_inherit_default_set",
        Validator_validate_1_term_dont_inherit_default_set
    },
    {
        "validate_1_term_dont_inherit_pair_default_set",
        Validator_validate_1_term_dont_inherit_pair_default_set
    },
    {
        "validate_1_term_cascade_implicit_trav",
        Validator_validate_1_term_cascade_implicit_trav
    },
    {
        "validate_1_term_cascade_isa",
        Validator_validate_1_term_cascade_isa
    },
    {
        "validate_1_term_cascade_childof",
        Validator_validate_1_term_cascade_childof
    },
    {
        "validate_1_term_cascade_down",
        Validator_validate_1_term_cascade_down
    },
    {
        "validate_1_term_optional_only",
        Validator_validate_1_term_optional_only
    },
    {
        "validate_1_term_transitive_pair",
        Validator_validate_1_term_transitive_pair
    },
    {
        "validate_1_variable_as_pred_only",
        Validator_validate_1_variable_as_pred_only
    },
    {
        "validate_1_variable_as_pred_w_subj",
        Validator_validate_1_variable_as_pred_w_subj
    },
    {
        "validate_1_variable_as_pred_w_pair",
        Validator_validate_1_variable_as_pred_w_pair
    },
    {
        "validate_1_variable_as_subj",
        Validator_validate_1_variable_as_subj
    },
    {
        "validate_1_variable_as_obj",
        Validator_validate_1_variable_as_obj
    },
    {
        "validate_2_terms_or_w_dontinherit",
        Validator_validate_2_terms_or_w_dontinherit
    },
    {
        "validate_2_terms_or_w_both_dontinherit",
        Validator_validate_2_terms_or_w_both_dontinherit
    },
    {
        "validate_w_pair_id",
        Validator_validate_w_pair_id
    },
    {
        "validate_w_pred_obj",
        Validator_validate_w_pred_obj
    },
    {
        "validate_w_pair_id_and_subj",
        Validator_validate_w_pair_id_and_subj
    },
    {
        "validate_1_w_pred_name",
        Validator_validate_1_w_pred_name
    },
    {
        "validate_1_w_final_pred_name",
        Validator_validate_1_w_final_pred_name
    },
    {
        "validate_1_w_subj_name",
        Validator_validate_1_w_subj_name
    },
    {
        "validate_1_w_obj_name",
        Validator_validate_1_w_obj_name
    },
    {
        "validate_w_this_implicit_variable",
        Validator_validate_w_this_implicit_variable
    },
    {
        "validate_w_this_explicit_entity",
        Validator_validate_w_this_explicit_entity
    },
    {
        "validate_w_first_this_implicit_variable",
        Validator_validate_w_first_this_implicit_variable
    },
    {
        "validate_w_first_this_explicit_entity",
        Validator_validate_w_first_this_explicit_entity
    },
    {
        "validate_w_second_this_implicit_variable",
        Validator_validate_w_second_this_implicit_variable
    },
    {
        "validate_w_second_this_explicit_entity",
        Validator_validate_w_second_this_explicit_entity
    },
    {
        "validate_w_this_variable_name",
        Validator_validate_w_this_variable_name
    },
    {
        "validate_w_src_var",
        Validator_validate_w_src_var
    },
    {
        "validate_w_first_var",
        Validator_validate_w_first_var
    },
    {
        "validate_w_second_var",
        Validator_validate_w_second_var
    },
    {
        "validate_w_0_source",
        Validator_validate_w_0_source
    },
    {
        "validate_w_0_target",
        Validator_validate_w_0_target
    },
    {
        "validate_2_terms_w_or",
        Validator_validate_2_terms_w_or
    },
    {
        "validate_2_terms_w_or_mixed_src_flags",
        Validator_validate_2_terms_w_or_mixed_src_flags
    },
    {
        "validate_2_terms_w_or_mixed_src_id",
        Validator_validate_2_terms_w_or_mixed_src_id
    },
    {
        "validate_2_terms_w_or_mixed_src_name",
        Validator_validate_2_terms_w_or_mixed_src_name
    },
    {
        "validate_2_terms_w_or_same_src_w_id_and_name",
        Validator_validate_2_terms_w_or_same_src_w_id_and_name
    },
    {
        "validate_w_and_flag",
        Validator_validate_w_and_flag
    },
    {
        "validate_w_or_flag",
        Validator_validate_w_or_flag
    },
    {
        "validate_w_not_flag",
        Validator_validate_w_not_flag
    },
    {
        "validate_filter",
        Validator_validate_filter
    },
    {
        "validate_double_init",
        Validator_validate_double_init
    },
    {
        "validate_double_init_w_expr",
        Validator_validate_double_init_w_expr
    },
    {
        "validate_double_init_w_expr_optional",
        Validator_validate_double_init_w_expr_optional
    },
    {
        "validate_w_tag_term_is_no_data",
        Validator_validate_w_tag_term_is_no_data
    },
    {
        "validate_w_inout_none_term_is_no_data",
        Validator_validate_w_inout_none_term_is_no_data
    },
    {
        "validate_w_tag_and_inout_none_term_is_no_data",
        Validator_validate_w_tag_and_inout_none_term_is_no_data
    },
    {
        "validate_w_not_term_is_no_data",
        Validator_validate_w_not_term_is_no_data
    },
    {
        "validate_w_no_transitive_pair",
        Validator_validate_w_no_transitive_pair
    },
    {
        "validate_w_transitive_pair_any_src",
        Validator_validate_w_transitive_pair_any_src
    },
    {
        "validate_w_transitive_pair",
        Validator_validate_w_transitive_pair
    },
    {
        "validate_w_transitive_tag_no_pair",
        Validator_validate_w_transitive_tag_no_pair
    },
    {
        "validate_w_transitive_tag_self_tgt",
        Validator_validate_w_transitive_tag_self_tgt
    },
    {
        "validate_w_transitive_tag_any_tgt",
        Validator_validate_w_transitive_tag_any_tgt
    },
    {
        "validate_w_pair_same_vars",
        Validator_validate_w_pair_same_vars
    },
    {
        "validate_w_pair_not_same_vars",
        Validator_validate_w_pair_not_same_vars
    },
    {
        "validate_w_pair_no_vars_not_same_vars",
        Validator_validate_w_pair_no_vars_not_same_vars
    },
    {
        "validate_w_pair_wildcard_not_same_vars",
        Validator_validate_w_pair_wildcard_not_same_vars
    },
    {
        "validate_w_pair_any_not_same_vars",
        Validator_validate_w_pair_any_not_same_vars
    },
    {
        "validate_w_no_pair_not_same_vars",
        Validator_validate_w_no_pair_not_same_vars
    },
    {
        "validate_not_childof_any",
        Validator_validate_not_childof_any
    },
    {
        "validate_w_inherited_id",
        Validator_validate_w_inherited_id
    },
    {
        "validate_w_inherited_pair",
        Validator_validate_w_inherited_pair
    },
    {
        "validate_w_non_inherited_id",
        Validator_validate_w_non_inherited_id
    },
    {
        "validate_w_non_inherited_pair",
        Validator_validate_w_non_inherited_pair
    },
    {
        "validate_w_first_wildcard_inout_none",
        Validator_validate_w_first_wildcard_inout_none
    },
    {
        "validate_w_first_var_inout_none",
        Validator_validate_w_first_var_inout_none
    },
    {
        "validate_w_pair_wildcard_inout_none",
        Validator_validate_w_pair_wildcard_inout_none
    },
    {
        "validate_w_pair_var_inout_none",
        Validator_validate_w_pair_var_inout_none
    },
    {
        "validate_w_unresolved_by_name",
        Validator_validate_w_unresolved_by_name
    },
    {
        "validate_w_unresolved_by_name_eq",
        Validator_validate_w_unresolved_by_name_eq
    },
    {
        "validate_childof_this",
        Validator_validate_childof_this
    },
    {
        "validate_childof_this_entity",
        Validator_validate_childof_this_entity
    },
    {
        "validate_childof_this_by_id",
        Validator_validate_childof_this_by_id
    },
    {
        "validate_filter_flag",
        Validator_validate_filter_flag
    }
};

bake_test_case Parser_testcases[] = {
    {
        "resolve_this",
        Parser_resolve_this
    },
    {
        "resolve_wildcard",
        Parser_resolve_wildcard
    },
    {
        "resolve_any",
        Parser_resolve_any
    },
    {
        "resolve_is_a",
        Parser_resolve_is_a
    },
    {
        "0",
        Parser_0
    },
    {
        "component_implicit_subject",
        Parser_component_implicit_subject
    },
    {
        "component_explicit_subject",
        Parser_component_explicit_subject
    },
    {
        "component_explicit_subject_this",
        Parser_component_explicit_subject_this
    },
    {
        "component_explicit_subject_this_by_name",
        Parser_component_explicit_subject_this_by_name
    },
    {
        "component_explicit_subject_this_by_var_name",
        Parser_component_explicit_subject_this_by_var_name
    },
    {
        "component_explicit_subject_wildcard",
        Parser_component_explicit_subject_wildcard
    },
    {
        "component_explicit_subject_any",
        Parser_component_explicit_subject_any
    },
    {
        "component_explicit_subject_0",
        Parser_component_explicit_subject_0
    },
    {
        "this_as_predicate",
        Parser_this_as_predicate
    },
    {
        "this_var_as_predicate",
        Parser_this_var_as_predicate
    },
    {
        "this_lowercase_var_as_predicate",
        Parser_this_lowercase_var_as_predicate
    },
    {
        "this_as_object",
        Parser_this_as_object
    },
    {
        "this_var_as_object",
        Parser_this_var_as_object
    },
    {
        "pair_implicit_subject",
        Parser_pair_implicit_subject
    },
    {
        "pair_implicit_subject_wildcard_pred",
        Parser_pair_implicit_subject_wildcard_pred
    },
    {
        "pair_implicit_subject_wildcard_obj",
        Parser_pair_implicit_subject_wildcard_obj
    },
    {
        "pair_implicit_subject_any_pred",
        Parser_pair_implicit_subject_any_pred
    },
    {
        "pair_implicit_subject_any_obj",
        Parser_pair_implicit_subject_any_obj
    },
    {
        "pair_implicit_subject_this_pred",
        Parser_pair_implicit_subject_this_pred
    },
    {
        "pair_implicit_subject_this_obj",
        Parser_pair_implicit_subject_this_obj
    },
    {
        "pair_implicit_subject_pred_w_self",
        Parser_pair_implicit_subject_pred_w_self
    },
    {
        "pair_implicit_subject_obj_w_self",
        Parser_pair_implicit_subject_obj_w_self
    },
    {
        "pair_implicit_subject_pred_w_up",
        Parser_pair_implicit_subject_pred_w_up
    },
    {
        "pair_implicit_subject_obj_w_up",
        Parser_pair_implicit_subject_obj_w_up
    },
    {
        "pair_implicit_subject_pred_w_self_up",
        Parser_pair_implicit_subject_pred_w_self_up
    },
    {
        "pair_implicit_subject_obj_w_self_up",
        Parser_pair_implicit_subject_obj_w_self_up
    },
    {
        "pair_implicit_subject_pred_w_invalid_flags",
        Parser_pair_implicit_subject_pred_w_invalid_flags
    },
    {
        "pair_implicit_subject_obj_w_invalid_flags",
        Parser_pair_implicit_subject_obj_w_invalid_flags
    },
    {
        "pair_explicit_subject",
        Parser_pair_explicit_subject
    },
    {
        "pair_explicit_subject_this",
        Parser_pair_explicit_subject_this
    },
    {
        "pair_explicit_subject_this_by_name",
        Parser_pair_explicit_subject_this_by_name
    },
    {
        "pair_explicit_subject_this_by_var_name",
        Parser_pair_explicit_subject_this_by_var_name
    },
    {
        "pair_explicit_subject_wildcard_pred",
        Parser_pair_explicit_subject_wildcard_pred
    },
    {
        "pair_explicit_subject_wildcard_subj",
        Parser_pair_explicit_subject_wildcard_subj
    },
    {
        "pair_explicit_subject_wildcard_obj",
        Parser_pair_explicit_subject_wildcard_obj
    },
    {
        "pair_implicit_subject_0_object",
        Parser_pair_implicit_subject_0_object
    },
    {
        "pair_explicit_subject_0_object",
        Parser_pair_explicit_subject_0_object
    },
    {
        "pair_explicit_subject_0",
        Parser_pair_explicit_subject_0
    },
    {
        "in_component_implicit_subject",
        Parser_in_component_implicit_subject
    },
    {
        "in_component_explicit_subject",
        Parser_in_component_explicit_subject
    },
    {
        "in_pair_implicit_subject",
        Parser_in_pair_implicit_subject
    },
    {
        "in_pair_explicit_subject",
        Parser_in_pair_explicit_subject
    },
    {
        "inout_component_implicit_subject",
        Parser_inout_component_implicit_subject
    },
    {
        "inout_component_explicit_subject",
        Parser_inout_component_explicit_subject
    },
    {
        "inout_pair_implicit_subject",
        Parser_inout_pair_implicit_subject
    },
    {
        "inout_pair_explicit_subject",
        Parser_inout_pair_explicit_subject
    },
    {
        "out_component_implicit_subject",
        Parser_out_component_implicit_subject
    },
    {
        "out_component_explicit_subject",
        Parser_out_component_explicit_subject
    },
    {
        "out_pair_implicit_subject",
        Parser_out_pair_implicit_subject
    },
    {
        "out_pair_explicit_subject",
        Parser_out_pair_explicit_subject
    },
    {
        "inout_filter_component",
        Parser_inout_filter_component
    },
    {
        "component_singleton",
        Parser_component_singleton
    },
    {
        "this_singleton",
        Parser_this_singleton
    },
    {
        "component_implicit_no_subject",
        Parser_component_implicit_no_subject
    },
    {
        "component_explicit_no_subject",
        Parser_component_explicit_no_subject
    },
    {
        "pair_no_subject",
        Parser_pair_no_subject
    },
    {
        "variable_single_char",
        Parser_variable_single_char
    },
    {
        "variable_multi_char",
        Parser_variable_multi_char
    },
    {
        "variable_multi_char_w_underscore",
        Parser_variable_multi_char_w_underscore
    },
    {
        "variable_multi_char_w_number",
        Parser_variable_multi_char_w_number
    },
    {
        "variable_multi_char_not_allcaps",
        Parser_variable_multi_char_not_allcaps
    },
    {
        "pred_var",
        Parser_pred_var
    },
    {
        "obj_var",
        Parser_obj_var
    },
    {
        "component_not",
        Parser_component_not
    },
    {
        "pair_implicit_subject_not",
        Parser_pair_implicit_subject_not
    },
    {
        "pair_explicit_subject_not",
        Parser_pair_explicit_subject_not
    },
    {
        "2_component_not",
        Parser_2_component_not
    },
    {
        "2_component_not_no_space",
        Parser_2_component_not_no_space
    },
    {
        "component_optional",
        Parser_component_optional
    },
    {
        "2_component_optional",
        Parser_2_component_optional
    },
    {
        "2_component_optional_no_space",
        Parser_2_component_optional_no_space
    },
    {
        "from_and",
        Parser_from_and
    },
    {
        "from_or",
        Parser_from_or
    },
    {
        "from_not",
        Parser_from_not
    },
    {
        "pair_implicit_subject_optional",
        Parser_pair_implicit_subject_optional
    },
    {
        "pair_explicit_subject_optional",
        Parser_pair_explicit_subject_optional
    },
    {
        "pred_implicit_subject_w_role",
        Parser_pred_implicit_subject_w_role
    },
    {
        "pred_explicit_subject_w_role",
        Parser_pred_explicit_subject_w_role
    },
    {
        "pred_no_subject_w_role",
        Parser_pred_no_subject_w_role
    },
    {
        "pair_implicit_subject_w_role",
        Parser_pair_implicit_subject_w_role
    },
    {
        "pair_explicit_subject_w_role",
        Parser_pair_explicit_subject_w_role
    },
    {
        "inout_role_pred_implicit_subject",
        Parser_inout_role_pred_implicit_subject
    },
    {
        "inout_role_pred_no_subject",
        Parser_inout_role_pred_no_subject
    },
    {
        "inout_role_pred_explicit_subject",
        Parser_inout_role_pred_explicit_subject
    },
    {
        "inout_role_pair_implicit_subject",
        Parser_inout_role_pair_implicit_subject
    },
    {
        "inout_role_pair_explicit_subject",
        Parser_inout_role_pair_explicit_subject
    },
    {
        "2_pred_implicit_subject",
        Parser_2_pred_implicit_subject
    },
    {
        "2_pred_no_subject",
        Parser_2_pred_no_subject
    },
    {
        "2_pred_explicit_subject",
        Parser_2_pred_explicit_subject
    },
    {
        "2_pair_implicit_subject",
        Parser_2_pair_implicit_subject
    },
    {
        "2_pair_explicit_subject",
        Parser_2_pair_explicit_subject
    },
    {
        "2_pred_role",
        Parser_2_pred_role
    },
    {
        "2_pair_implicit_subj_role",
        Parser_2_pair_implicit_subj_role
    },
    {
        "2_pair_explicit_subj_role",
        Parser_2_pair_explicit_subj_role
    },
    {
        "2_or_pred_implicit_subj",
        Parser_2_or_pred_implicit_subj
    },
    {
        "2_or_pred_explicit_subj",
        Parser_2_or_pred_explicit_subj
    },
    {
        "2_or_pair_implicit_subj",
        Parser_2_or_pair_implicit_subj
    },
    {
        "2_or_pair_explicit_subj",
        Parser_2_or_pair_explicit_subj
    },
    {
        "2_or_pred_inout",
        Parser_2_or_pred_inout
    },
    {
        "1_digit_pred_implicit_subj",
        Parser_1_digit_pred_implicit_subj
    },
    {
        "1_digit_pred_no_subj",
        Parser_1_digit_pred_no_subj
    },
    {
        "1_digit_pred_explicit_subj",
        Parser_1_digit_pred_explicit_subj
    },
    {
        "1_digit_pair_implicit_subj",
        Parser_1_digit_pair_implicit_subj
    },
    {
        "1_digit_pair_explicit_subj",
        Parser_1_digit_pair_explicit_subj
    },
    {
        "pred_implicit_subject_self",
        Parser_pred_implicit_subject_self
    },
    {
        "pred_implicit_subject_superset",
        Parser_pred_implicit_subject_superset
    },
    {
        "pred_implicit_subject_superset_inclusive",
        Parser_pred_implicit_subject_superset_inclusive
    },
    {
        "pred_implicit_subject_superset_cascade",
        Parser_pred_implicit_subject_superset_cascade
    },
    {
        "pred_implicit_subject_superset_inclusive_cascade",
        Parser_pred_implicit_subject_superset_inclusive_cascade
    },
    {
        "pred_implicit_subject_implicit_superset_cascade",
        Parser_pred_implicit_subject_implicit_superset_cascade
    },
    {
        "pred_implicit_subject_implicit_superset_inclusive_cascade",
        Parser_pred_implicit_subject_implicit_superset_inclusive_cascade
    },
    {
        "pred_implicit_subject_implicit_superset_cascade_w_rel",
        Parser_pred_implicit_subject_implicit_superset_cascade_w_rel
    },
    {
        "pred_implicit_subject_implicit_superset_inclusive_cascade_w_rel",
        Parser_pred_implicit_subject_implicit_superset_inclusive_cascade_w_rel
    },
    {
        "pred_implicit_subject_superset_childof",
        Parser_pred_implicit_subject_superset_childof
    },
    {
        "pred_implicit_subject_cascade_superset_childof",
        Parser_pred_implicit_subject_cascade_superset_childof
    },
    {
        "pred_implicit_subject_superset_cascade_childof",
        Parser_pred_implicit_subject_superset_cascade_childof
    },
    {
        "pred_implicit_subject_superset_cascade_childof_optional",
        Parser_pred_implicit_subject_superset_cascade_childof_optional
    },
    {
        "expr_w_symbol",
        Parser_expr_w_symbol
    },
    {
        "expr_w_newline",
        Parser_expr_w_newline
    },
    {
        "subj_entity_w_explicit_self",
        Parser_subj_entity_w_explicit_self
    },
    {
        "subj_entity_w_explicit_self_superset",
        Parser_subj_entity_w_explicit_self_superset
    },
    {
        "subj_entity_w_explicit_superset_relation",
        Parser_subj_entity_w_explicit_superset_relation
    },
    {
        "subj_entity_w_explicit_self_superset_relation",
        Parser_subj_entity_w_explicit_self_superset_relation
    },
    {
        "obj_entity_w_explicit_self",
        Parser_obj_entity_w_explicit_self
    },
    {
        "obj_entity_w_explicit_self_superset",
        Parser_obj_entity_w_explicit_self_superset
    },
    {
        "obj_entity_w_explicit_superset_relation",
        Parser_obj_entity_w_explicit_superset_relation
    },
    {
        "obj_entity_w_explicit_self_superset_relation",
        Parser_obj_entity_w_explicit_self_superset_relation
    },
    {
        "pred_entity_w_explicit_self",
        Parser_pred_entity_w_explicit_self
    },
    {
        "pred_entity_w_explicit_self_superset",
        Parser_pred_entity_w_explicit_self_superset
    },
    {
        "pred_entity_no_args_w_explicit_self",
        Parser_pred_entity_no_args_w_explicit_self
    },
    {
        "pred_entity_no_args_w_explicit_self_superset",
        Parser_pred_entity_no_args_w_explicit_self_superset
    },
    {
        "pred_entity_no_args_2_terms_w_explicit_self",
        Parser_pred_entity_no_args_2_terms_w_explicit_self
    },
    {
        "pred_entity_no_args_2_terms_w_explicit_self_superset",
        Parser_pred_entity_no_args_2_terms_w_explicit_self_superset
    },
    {
        "newline",
        Parser_newline
    },
    {
        "2_newlines",
        Parser_2_newlines
    },
    {
        "3_newlines",
        Parser_3_newlines
    },
    {
        "space",
        Parser_space
    },
    {
        "2_spaces",
        Parser_2_spaces
    },
    {
        "trailing_newline",
        Parser_trailing_newline
    },
    {
        "2_trailing_newlines",
        Parser_2_trailing_newlines
    },
    {
        "trailing_space",
        Parser_trailing_space
    },
    {
        "2_trailing_spaces",
        Parser_2_trailing_spaces
    },
    {
        "template_type",
        Parser_template_type
    },
    {
        "predicate_w_parens",
        Parser_predicate_w_parens
    },
    {
        "not_alive_pred",
        Parser_not_alive_pred
    },
    {
        "not_alive_subj",
        Parser_not_alive_subj
    },
    {
        "not_alive_obj",
        Parser_not_alive_obj
    },
    {
        "this_subj_var_kind",
        Parser_this_subj_var_kind
    },
    {
        "this_obj_var_kind",
        Parser_this_obj_var_kind
    },
    {
        "this_subj_obj_var_kind",
        Parser_this_subj_obj_var_kind
    },
    {
        "var_w_name",
        Parser_var_w_name
    },
    {
        "entity_pred_no_name",
        Parser_entity_pred_no_name
    },
    {
        "entity_subj_no_name",
        Parser_entity_subj_no_name
    },
    {
        "entity_obj_no_name",
        Parser_entity_obj_no_name
    },
    {
        "this_pred_no_name",
        Parser_this_pred_no_name
    },
    {
        "this_subj_no_name",
        Parser_this_subj_no_name
    },
    {
        "this_obj_no_name",
        Parser_this_obj_no_name
    },
    {
        "auto_object_variable",
        Parser_auto_object_variable
    },
    {
        "auto_object_variable_w_subj",
        Parser_auto_object_variable_w_subj
    },
    {
        "auto_scoped_variable",
        Parser_auto_scoped_variable
    },
    {
        "invalid_variable_only",
        Parser_invalid_variable_only
    },
    {
        "oneof_self_pred_w_relative_obj",
        Parser_oneof_self_pred_w_relative_obj
    },
    {
        "oneof_other_pred_w_relative_obj",
        Parser_oneof_other_pred_w_relative_obj
    },
    {
        "oneof_self_pred_w_invalid_obj",
        Parser_oneof_self_pred_w_invalid_obj
    },
    {
        "oneof_other_pred_w_invalid_obj",
        Parser_oneof_other_pred_w_invalid_obj
    },
    {
        "pair_implicit_src_missing_rel",
        Parser_pair_implicit_src_missing_rel
    },
    {
        "pair_implicit_src_missing_obj",
        Parser_pair_implicit_src_missing_obj
    },
    {
        "pair_explicit_src_missing_src",
        Parser_pair_explicit_src_missing_src
    },
    {
        "pair_explicit_src_missing_obj",
        Parser_pair_explicit_src_missing_obj
    },
    {
        "eq_id",
        Parser_eq_id
    },
    {
        "eq_id_var",
        Parser_eq_id_var
    },
    {
        "eq_var_id",
        Parser_eq_var_id
    },
    {
        "eq_var_table",
        Parser_eq_var_table
    },
    {
        "eq_var",
        Parser_eq_var
    },
    {
        "neq_id",
        Parser_neq_id
    },
    {
        "neq_id_var",
        Parser_neq_id_var
    },
    {
        "neq_var_id",
        Parser_neq_var_id
    },
    {
        "neq_var_table",
        Parser_neq_var_table
    },
    {
        "neq_var",
        Parser_neq_var
    },
    {
        "eq_name",
        Parser_eq_name
    },
    {
        "eq_name_var",
        Parser_eq_name_var
    },
    {
        "eq_var_name",
        Parser_eq_var_name
    },
    {
        "neq_name",
        Parser_neq_name
    },
    {
        "neq_name_var",
        Parser_neq_name_var
    },
    {
        "neq_var_name",
        Parser_neq_var_name
    },
    {
        "match_name",
        Parser_match_name
    },
    {
        "match_name_var",
        Parser_match_name_var
    },
    {
        "match_var_name",
        Parser_match_var_name
    },
    {
        "match_var",
        Parser_match_var
    },
    {
        "nmatch_name",
        Parser_nmatch_name
    },
    {
        "nmatch_name_var",
        Parser_nmatch_name_var
    },
    {
        "nmatch_var_name",
        Parser_nmatch_var_name
    },
    {
        "eq_same_var",
        Parser_eq_same_var
    },
    {
        "neq_same_var",
        Parser_neq_same_var
    },
    {
        "eq_same_var_this",
        Parser_eq_same_var_this
    },
    {
        "neq_same_var_this",
        Parser_neq_same_var_this
    },
    {
        "eq_w_optional",
        Parser_eq_w_optional
    },
    {
        "neq_w_optional",
        Parser_neq_w_optional
    },
    {
        "match_w_optional",
        Parser_match_w_optional
    },
    {
        "query_scope_1_term",
        Parser_query_scope_1_term
    },
    {
        "query_scope_1_term_spaces",
        Parser_query_scope_1_term_spaces
    },
    {
        "query_scope_2_terms",
        Parser_query_scope_2_terms
    },
    {
        "query_nested_scope",
        Parser_query_nested_scope
    },
    {
        "query_nested_scope_spaces",
        Parser_query_nested_scope_spaces
    },
    {
        "query_scope_unbalanced",
        Parser_query_scope_unbalanced
    },
    {
        "query_not_scope",
        Parser_query_not_scope
    },
    {
        "query_empty_scope",
        Parser_query_empty_scope
    },
    {
        "query_scope_newline_after_open",
        Parser_query_scope_newline_after_open
    },
    {
        "query_scope_newline_after_close",
        Parser_query_scope_newline_after_close
    },
    {
        "override_tag",
        Parser_override_tag
    },
    {
        "override_pair",
        Parser_override_pair
    },
    {
        "pair_3_args",
        Parser_pair_3_args
    },
    {
        "pair_3_args_implicit_this",
        Parser_pair_3_args_implicit_this
    },
    {
        "pair_4_args",
        Parser_pair_4_args
    },
    {
        "pair_4_args_implicit_this",
        Parser_pair_4_args_implicit_this
    },
    {
        "pair_3_args_2_terms",
        Parser_pair_3_args_2_terms
    },
    {
        "pair_3_args_this_tgt",
        Parser_pair_3_args_this_tgt
    },
    {
        "pair_3_args_2_terms_this_tgt",
        Parser_pair_3_args_2_terms_this_tgt
    },
    {
        "pair_3_args_2_terms_this_tgt_implicit_this",
        Parser_pair_3_args_2_terms_this_tgt_implicit_this
    },
    {
        "cascade_desc",
        Parser_cascade_desc
    },
    {
        "pair_3_or_args",
        Parser_pair_3_or_args
    },
    {
        "pair_3_or_args_implicit_this",
        Parser_pair_3_or_args_implicit_this
    },
    {
        "pair_4_or_args",
        Parser_pair_4_or_args
    },
    {
        "pair_4_or_args_implicit_this",
        Parser_pair_4_or_args_implicit_this
    },
    {
        "pair_or_before_and_oper",
        Parser_pair_or_before_and_oper
    },
    {
        "pair_and_before_or_oper",
        Parser_pair_and_before_or_oper
    },
    {
        "cascade_desc",
        Parser_cascade_desc
    },
    {
        "newline_after_inout",
        Parser_newline_after_inout
    },
    {
        "newline_after_term_open",
        Parser_newline_after_term_open
    },
    {
        "newline_after_term_src",
        Parser_newline_after_term_src
    },
    {
        "newline_after_term_src_pair",
        Parser_newline_after_term_src_pair
    },
    {
        "newline_after_term_pair_comma",
        Parser_newline_after_term_pair_comma
    },
    {
        "newline_after_term_pair_second",
        Parser_newline_after_term_pair_second
    }
};

bake_test_case Basic_testcases[] = {
    {
        "0_query",
        Basic_0_query
    },
    {
        "1_fact_w_tag",
        Basic_1_fact_w_tag
    },
    {
        "1_fact_w_component",
        Basic_1_fact_w_component
    },
    {
        "1_fact_w_tag_pair",
        Basic_1_fact_w_tag_pair
    },
    {
        "1_fact_w_component_pair",
        Basic_1_fact_w_component_pair
    },
    {
        "2_facts_same_src_w_tag",
        Basic_2_facts_same_src_w_tag
    },
    {
        "2_facts_same_src_w_component",
        Basic_2_facts_same_src_w_component
    },
    {
        "2_facts_same_src_w_tag_pair",
        Basic_2_facts_same_src_w_tag_pair
    },
    {
        "2_facts_same_src_w_component_pair",
        Basic_2_facts_same_src_w_component_pair
    },
    {
        "2_facts_other_src_w_tag",
        Basic_2_facts_other_src_w_tag
    },
    {
        "2_facts_other_src_w_component",
        Basic_2_facts_other_src_w_component
    },
    {
        "2_facts_other_src_w_tag_pair",
        Basic_2_facts_other_src_w_tag_pair
    },
    {
        "2_facts_other_src_w_component_pair",
        Basic_2_facts_other_src_w_component_pair
    },
    {
        "1_fact_w_any",
        Basic_1_fact_w_any
    },
    {
        "1_fact_w_pair_any_tgt",
        Basic_1_fact_w_pair_any_tgt
    },
    {
        "1_fact_w_pair_any_rel",
        Basic_1_fact_w_pair_any_rel
    },
    {
        "1_fact_w_pair_any_rel_tgt",
        Basic_1_fact_w_pair_any_rel_tgt
    },
    {
        "2_facts_same_src_w_any",
        Basic_2_facts_same_src_w_any
    },
    {
        "2_facts_same_src_w_pair_any_tgt",
        Basic_2_facts_same_src_w_pair_any_tgt
    },
    {
        "2_facts_same_src_w_pair_any_rel",
        Basic_2_facts_same_src_w_pair_any_rel
    },
    {
        "2_facts_same_src_w_pair_any_rel_tgt",
        Basic_2_facts_same_src_w_pair_any_rel_tgt
    },
    {
        "2_facts_other_src_w_any",
        Basic_2_facts_other_src_w_any
    },
    {
        "2_facts_other_src_w_pair_any_tgt",
        Basic_2_facts_other_src_w_pair_any_tgt
    },
    {
        "2_facts_other_src_w_pair_any_rel",
        Basic_2_facts_other_src_w_pair_any_rel
    },
    {
        "2_facts_other_src_w_pair_any_rel_tgt",
        Basic_2_facts_other_src_w_pair_any_rel_tgt
    },
    {
        "1_this_src_w_tag",
        Basic_1_this_src_w_tag
    },
    {
        "1_this_src_w_component",
        Basic_1_this_src_w_component
    },
    {
        "1_this_src_w_tag_pair",
        Basic_1_this_src_w_tag_pair
    },
    {
        "1_this_src_w_component_pair",
        Basic_1_this_src_w_component_pair
    },
    {
        "1_this_src_w_tag_2_tables",
        Basic_1_this_src_w_tag_2_tables
    },
    {
        "1_this_src_w_component_2_tables",
        Basic_1_this_src_w_component_2_tables
    },
    {
        "1_this_src_w_tag_pair_2_tables",
        Basic_1_this_src_w_tag_pair_2_tables
    },
    {
        "1_this_src_w_component_pair_2_tables",
        Basic_1_this_src_w_component_pair_2_tables
    },
    {
        "2_this_src_w_tag",
        Basic_2_this_src_w_tag
    },
    {
        "2_this_src_w_component",
        Basic_2_this_src_w_component
    },
    {
        "2_this_src_ent_src_w_tag",
        Basic_2_this_src_ent_src_w_tag
    },
    {
        "2_this_src_ent_src_w_component",
        Basic_2_this_src_ent_src_w_component
    },
    {
        "2_ent_src_this_src_w_tag",
        Basic_2_ent_src_this_src_w_tag
    },
    {
        "2_ent_src_this_src_w_component",
        Basic_2_ent_src_this_src_w_component
    },
    {
        "recycled_tag",
        Basic_recycled_tag
    },
    {
        "recycled_src",
        Basic_recycled_src
    },
    {
        "recycled_pair_rel",
        Basic_recycled_pair_rel
    },
    {
        "recycled_pair_tgt",
        Basic_recycled_pair_tgt
    },
    {
        "this_src_w_wildcard",
        Basic_this_src_w_wildcard
    },
    {
        "this_src_w_pair_rel_wildcard",
        Basic_this_src_w_pair_rel_wildcard
    },
    {
        "this_src_w_pair_tgt_wildcard",
        Basic_this_src_w_pair_tgt_wildcard
    },
    {
        "this_src_w_pair_rel_tgt_wildcard",
        Basic_this_src_w_pair_rel_tgt_wildcard
    },
    {
        "this_src_w_any",
        Basic_this_src_w_any
    },
    {
        "this_src_w_any_written",
        Basic_this_src_w_any_written
    },
    {
        "this_src_w_pair_rel_any",
        Basic_this_src_w_pair_rel_any
    },
    {
        "this_src_w_pair_tgt_any",
        Basic_this_src_w_pair_tgt_any
    },
    {
        "this_src_w_pair_rel_tgt_any",
        Basic_this_src_w_pair_rel_tgt_any
    },
    {
        "ent_src_w_wildcard",
        Basic_ent_src_w_wildcard
    },
    {
        "ent_src_w_pair_rel_wildcard",
        Basic_ent_src_w_pair_rel_wildcard
    },
    {
        "ent_src_w_pair_tgt_wildcard",
        Basic_ent_src_w_pair_tgt_wildcard
    },
    {
        "ent_src_w_pair_rel_tgt_wildcard",
        Basic_ent_src_w_pair_rel_tgt_wildcard
    },
    {
        "1_wildcard_src",
        Basic_1_wildcard_src
    },
    {
        "1_wildcard_src_w_pair",
        Basic_1_wildcard_src_w_pair
    },
    {
        "2_wildcard_src",
        Basic_2_wildcard_src
    },
    {
        "2_wildcard_src_w_pair",
        Basic_2_wildcard_src_w_pair
    },
    {
        "1_wildcard_src_w_pair_tgt_var",
        Basic_1_wildcard_src_w_pair_tgt_var
    },
    {
        "1_wildcard_src_w_pair_rel_var",
        Basic_1_wildcard_src_w_pair_rel_var
    },
    {
        "1_wildcard_src_w_pair_tgt_this",
        Basic_1_wildcard_src_w_pair_tgt_this
    },
    {
        "1_wildcard_src_w_pair_rel_this",
        Basic_1_wildcard_src_w_pair_rel_this
    },
    {
        "1_any_src",
        Basic_1_any_src
    },
    {
        "1_any_src_w_pair",
        Basic_1_any_src_w_pair
    },
    {
        "2_any_src",
        Basic_2_any_src
    },
    {
        "2_any_src_w_pair",
        Basic_2_any_src_w_pair
    },
    {
        "1_any_src_w_pair_tgt_var",
        Basic_1_any_src_w_pair_tgt_var
    },
    {
        "1_any_src_w_pair_rel_var",
        Basic_1_any_src_w_pair_rel_var
    },
    {
        "1_any_src_w_pair_tgt_this",
        Basic_1_any_src_w_pair_tgt_this
    },
    {
        "1_any_src_w_pair_rel_this",
        Basic_1_any_src_w_pair_rel_this
    },
    {
        "not_any",
        Basic_not_any
    },
    {
        "rule_w_iter_next",
        Basic_rule_w_iter_next
    },
    {
        "empty_rule",
        Basic_empty_rule
    },
    {
        "invalid_rule",
        Basic_invalid_rule
    },
    {
        "not_instanced_table_src",
        Basic_not_instanced_table_src
    },
    {
        "not_instanced_entity_src",
        Basic_not_instanced_entity_src
    },
    {
        "not_instanced_mixed_src",
        Basic_not_instanced_mixed_src
    },
    {
        "not_instanced_inherited",
        Basic_not_instanced_inherited
    },
    {
        "instanced_table_src",
        Basic_instanced_table_src
    },
    {
        "instanced_entity_src",
        Basic_instanced_entity_src
    },
    {
        "instanced_mixed_src",
        Basic_instanced_mixed_src
    },
    {
        "instanced_inherited",
        Basic_instanced_inherited
    },
    {
        "in_term",
        Basic_in_term
    },
    {
        "out_term",
        Basic_out_term
    },
    {
        "inout_term",
        Basic_inout_term
    },
    {
        "nodata_term",
        Basic_nodata_term
    },
    {
        "find_this_lowercase",
        Basic_find_this_lowercase
    },
    {
        "find_this_uppercase",
        Basic_find_this_uppercase
    },
    {
        "find_this_tgt_lowercase",
        Basic_find_this_tgt_lowercase
    },
    {
        "find_this_tgt_uppercase",
        Basic_find_this_tgt_uppercase
    },
    {
        "get_filter",
        Basic_get_filter
    },
    {
        "iter_empty_source",
        Basic_iter_empty_source
    },
    {
        "iter_empty_source_2_terms",
        Basic_iter_empty_source_2_terms
    },
    {
        "iter_empty_source_wildcard",
        Basic_iter_empty_source_wildcard
    },
    {
        "iter_empty_source_pair",
        Basic_iter_empty_source_pair
    },
    {
        "iter_empty_source_pair_wildcard",
        Basic_iter_empty_source_pair_wildcard
    },
    {
        "iter_empty_source_2_terms_pair",
        Basic_iter_empty_source_2_terms_pair
    },
    {
        "iter_empty_source_2_terms_mixed",
        Basic_iter_empty_source_2_terms_mixed
    },
    {
        "iter_empty_source_2_terms_mixed_pair",
        Basic_iter_empty_source_2_terms_mixed_pair
    },
    {
        "iter_empty_source_2_terms_mixed_pair_wildcard",
        Basic_iter_empty_source_2_terms_mixed_pair_wildcard
    },
    {
        "this_var_w_empty_entity",
        Basic_this_var_w_empty_entity
    },
    {
        "match_disabled",
        Basic_match_disabled
    },
    {
        "match_prefab",
        Basic_match_prefab
    },
    {
        "match_disabled_prefab",
        Basic_match_disabled_prefab
    },
    {
        "match_disabled_this_tgt",
        Basic_match_disabled_this_tgt
    },
    {
        "match_prefab_this_tgt",
        Basic_match_prefab_this_tgt
    },
    {
        "match_disabled_prefab_this_tgt",
        Basic_match_disabled_prefab_this_tgt
    },
    {
        "match_self_disabled",
        Basic_match_self_disabled
    },
    {
        "match_self_prefab",
        Basic_match_self_prefab
    },
    {
        "match_self_disabled_prefab",
        Basic_match_self_disabled_prefab
    },
    {
        "inout_none_first_term",
        Basic_inout_none_first_term
    },
    {
        "inout_none_second_term",
        Basic_inout_none_second_term
    },
    {
        "inout_none_singleton",
        Basic_inout_none_singleton
    },
    {
        "inout_none_singleton_w_or",
        Basic_inout_none_singleton_w_or
    },
    {
        "inout_none_component_w_or",
        Basic_inout_none_component_w_or
    },
    {
        "no_data_rule",
        Basic_no_data_rule
    },
    {
        "frame_offset",
        Basic_frame_offset
    },
    {
        "frame_offset_no_data",
        Basic_frame_offset_no_data
    },
    {
        "match_empty_tables",
        Basic_match_empty_tables
    },
    {
        "match_empty_tables_no_data",
        Basic_match_empty_tables_no_data
    },
    {
        "match_empty_tables_w_not",
        Basic_match_empty_tables_w_not
    },
    {
        "match_empty_tables_w_wildcard",
        Basic_match_empty_tables_w_wildcard
    },
    {
        "match_empty_tables_w_no_empty_tables",
        Basic_match_empty_tables_w_no_empty_tables
    },
    {
        "match_empty_tables_trivial",
        Basic_match_empty_tables_trivial
    },
    {
        "oneof_wildcard",
        Basic_oneof_wildcard
    },
    {
        "oneof_any",
        Basic_oneof_any
    },
    {
        "instanced_w_singleton",
        Basic_instanced_w_singleton
    },
    {
        "instanced_w_base",
        Basic_instanced_w_base
    },
    {
        "not_instanced_w_singleton",
        Basic_not_instanced_w_singleton
    },
    {
        "not_instanced_w_base",
        Basic_not_instanced_w_base
    },
    {
        "unknown_before_known",
        Basic_unknown_before_known
    },
    {
        "unknown_before_known_after_or",
        Basic_unknown_before_known_after_or
    },
    {
        "unknown_before_known_after_not",
        Basic_unknown_before_known_after_not
    },
    {
        "unknown_before_known_after_optional",
        Basic_unknown_before_known_after_optional
    },
    {
        "unknown_before_known_after_scope",
        Basic_unknown_before_known_after_scope
    },
    {
        "2_trivial_mixed_2_tables",
        Basic_2_trivial_mixed_2_tables
    },
    {
        "2_trivial_mixed_2_tables_component",
        Basic_2_trivial_mixed_2_tables_component
    },
    {
        "2_trivial_mixed_2_tables_wildcard",
        Basic_2_trivial_mixed_2_tables_wildcard
    },
    {
        "2_this_w_fixed_src",
        Basic_2_this_w_fixed_src
    },
    {
        "2_fixed_src_w_this",
        Basic_2_fixed_src_w_this
    },
    {
        "2_this_w_fixed_src_no_match_fixed",
        Basic_2_this_w_fixed_src_no_match_fixed
    },
    {
        "2_fixed_src_w_this_no_match_fixed",
        Basic_2_fixed_src_w_this_no_match_fixed
    },
    {
        "2_this_w_fixed_src_no_match_this",
        Basic_2_this_w_fixed_src_no_match_this
    },
    {
        "2_fixed_src_w_this_no_match_this",
        Basic_2_fixed_src_w_this_no_match_this
    },
    {
        "query_count_results",
        Basic_query_count_results
    },
    {
        "query_count_entities",
        Basic_query_count_entities
    },
    {
        "query_is_true",
        Basic_query_is_true
    },
    {
        "implicit_cleanup_1_term",
        Basic_implicit_cleanup_1_term
    },
    {
        "implicit_cleanup_2_terms",
        Basic_implicit_cleanup_2_terms
    },
    {
        "implicit_cleanup_1_term_w_up",
        Basic_implicit_cleanup_1_term_w_up
    },
    {
        "implicit_cleanup_2_terms_w_up",
        Basic_implicit_cleanup_2_terms_w_up
    },
    {
        "implicit_cleanup_2_queries",
        Basic_implicit_cleanup_2_queries
    },
    {
        "implicit_cleanup_2_queries_1_cleanup",
        Basic_implicit_cleanup_2_queries_1_cleanup
    },
    {
        "iter_valid",
        Basic_iter_valid
    },
    {
        "iter_frame_offset",
        Basic_iter_frame_offset
    },
    {
        "iter_nested_1",
        Basic_iter_nested_1
    },
    {
        "iter_nested_2",
        Basic_iter_nested_2
    },
    {
        "iter_interleaved",
        Basic_iter_interleaved
    },
    {
        "set_get_context",
        Basic_set_get_context
    },
    {
        "set_get_binding_context",
        Basic_set_get_binding_context
    },
    {
        "set_get_context_w_free",
        Basic_set_get_context_w_free
    },
    {
        "set_get_binding_context_w_free",
        Basic_set_get_binding_context_w_free
    },
    {
        "create_query_w_existing_entity",
        Basic_create_query_w_existing_entity
    }
};

bake_test_case Plan_testcases[] = {
    {
        "reordered_plan_1",
        Plan_reordered_plan_1
    },
    {
        "reordered_plan_2",
        Plan_reordered_plan_2
    },
    {
        "1_trivial_plan",
        Plan_1_trivial_plan
    },
    {
        "2_trivial_plan",
        Plan_2_trivial_plan
    },
    {
        "1_trivial_plan_component",
        Plan_1_trivial_plan_component
    },
    {
        "2_trivial_plan_component",
        Plan_2_trivial_plan_component
    },
    {
        "3_trivial_plan_w_pair",
        Plan_3_trivial_plan_w_pair
    },
    {
        "3_trivial_plan_w_wildcard",
        Plan_3_trivial_plan_w_wildcard
    },
    {
        "3_trivial_plan_w_any",
        Plan_3_trivial_plan_w_any
    },
    {
        "3_trivial_plan_w_pair_component",
        Plan_3_trivial_plan_w_pair_component
    },
    {
        "3_trivial_plan_w_wildcard_component",
        Plan_3_trivial_plan_w_wildcard_component
    },
    {
        "3_trivial_plan_w_any_component",
        Plan_3_trivial_plan_w_any_component
    },
    {
        "1_trivial_component_w_none",
        Plan_1_trivial_component_w_none
    },
    {
        "2_trivial_component_w_none",
        Plan_2_trivial_component_w_none
    },
    {
        "2_trivial_plan_w_wildcard",
        Plan_2_trivial_plan_w_wildcard
    },
    {
        "this_before_fixed_src",
        Plan_this_before_fixed_src
    },
    {
        "fixed_src_before_this",
        Plan_fixed_src_before_this
    },
    {
        "var_before_fixed_src",
        Plan_var_before_fixed_src
    },
    {
        "fixed_src_before_var",
        Plan_fixed_src_before_var
    },
    {
        "this_before_fixed_src_w_not",
        Plan_this_before_fixed_src_w_not
    },
    {
        "this_before_fixed_src_w_first_var",
        Plan_this_before_fixed_src_w_first_var
    },
    {
        "this_before_fixed_src_w_first_var_w_not",
        Plan_this_before_fixed_src_w_first_var_w_not
    },
    {
        "this_before_fixed_src_w_second_var",
        Plan_this_before_fixed_src_w_second_var
    },
    {
        "this_before_fixed_src_w_second_var_w_not",
        Plan_this_before_fixed_src_w_second_var_w_not
    },
    {
        "populate_1_fixed",
        Plan_populate_1_fixed
    },
    {
        "populate_2_fixed",
        Plan_populate_2_fixed
    },
    {
        "populate_1_fixed_1_this_self",
        Plan_populate_1_fixed_1_this_self
    },
    {
        "populate_2_fixed_2_this_self",
        Plan_populate_2_fixed_2_this_self
    },
    {
        "populate_2_fixed_2_this_self_interleaved",
        Plan_populate_2_fixed_2_this_self_interleaved
    },
    {
        "populate_2_this_self_2_fixed",
        Plan_populate_2_this_self_2_fixed
    },
    {
        "populate_1_fixed_1_this_up",
        Plan_populate_1_fixed_1_this_up
    },
    {
        "populate_2_fixed_2_this_up",
        Plan_populate_2_fixed_2_this_up
    },
    {
        "populate_2_fixed_2_this_up_interleaved",
        Plan_populate_2_fixed_2_this_up_interleaved
    },
    {
        "populate_2_this_up_2_fixed",
        Plan_populate_2_this_up_2_fixed
    },
    {
        "populate_1_fixed_1_this_self_cached",
        Plan_populate_1_fixed_1_this_self_cached
    },
    {
        "populate_2_fixed_2_this_self_cached",
        Plan_populate_2_fixed_2_this_self_cached
    },
    {
        "populate_2_fixed_2_this_self_interleaved_cached",
        Plan_populate_2_fixed_2_this_self_interleaved_cached
    },
    {
        "populate_2_this_self_2_fixed_cached",
        Plan_populate_2_this_self_2_fixed_cached
    },
    {
        "populate_1_fixed_1_this_up_cached",
        Plan_populate_1_fixed_1_this_up_cached
    },
    {
        "populate_2_fixed_2_this_up_cached",
        Plan_populate_2_fixed_2_this_up_cached
    },
    {
        "populate_2_fixed_2_this_up_interleaved_cached",
        Plan_populate_2_fixed_2_this_up_interleaved_cached
    },
    {
        "populate_2_this_up_2_fixed_cached",
        Plan_populate_2_this_up_2_fixed_cached
    },
    {
        "populate_1_fixed_1_var_self",
        Plan_populate_1_fixed_1_var_self
    },
    {
        "populate_2_fixed_2_var_self",
        Plan_populate_2_fixed_2_var_self
    },
    {
        "populate_2_fixed_2_var_self_interleaved",
        Plan_populate_2_fixed_2_var_self_interleaved
    },
    {
        "populate_2_var_self_2_fixed",
        Plan_populate_2_var_self_2_fixed
    },
    {
        "populate_1_fixed_1_var_up",
        Plan_populate_1_fixed_1_var_up
    },
    {
        "populate_2_fixed_2_var_up",
        Plan_populate_2_fixed_2_var_up
    },
    {
        "populate_2_fixed_2_var_up_interleaved",
        Plan_populate_2_fixed_2_var_up_interleaved
    },
    {
        "populate_2_var_up_2_fixed",
        Plan_populate_2_var_up_2_fixed
    },
    {
        "cache_2_or",
        Plan_cache_2_or
    },
    {
        "cache_2_or_w_not",
        Plan_cache_2_or_w_not
    }
};

bake_test_case Variables_testcases[] = {
    {
        "1_ent_src_w_var",
        Variables_1_ent_src_w_var
    },
    {
        "1_ent_src_w_pair_rel_var",
        Variables_1_ent_src_w_pair_rel_var
    },
    {
        "1_ent_src_w_pair_tgt_var",
        Variables_1_ent_src_w_pair_tgt_var
    },
    {
        "1_ent_src_w_pair_rel_tgt_var",
        Variables_1_ent_src_w_pair_rel_tgt_var
    },
    {
        "1_ent_src_w_pair_rel_tgt_same_var",
        Variables_1_ent_src_w_pair_rel_tgt_same_var
    },
    {
        "1_ent_src_w_pair_rel_tgt_same_var_after_write",
        Variables_1_ent_src_w_pair_rel_tgt_same_var_after_write
    },
    {
        "1_this_src_w_var",
        Variables_1_this_src_w_var
    },
    {
        "1_this_src_w_pair_rel_var",
        Variables_1_this_src_w_pair_rel_var
    },
    {
        "1_this_src_w_pair_tgt_var",
        Variables_1_this_src_w_pair_tgt_var
    },
    {
        "1_this_src_w_pair_rel_tgt_var",
        Variables_1_this_src_w_pair_rel_tgt_var
    },
    {
        "1_this_src_w_pair_rel_tgt_same_var",
        Variables_1_this_src_w_pair_rel_tgt_same_var
    },
    {
        "1_this_src_w_pair_rel_tgt_same_var_after_write",
        Variables_1_this_src_w_pair_rel_tgt_same_var_after_write
    },
    {
        "1_src_id_same_var",
        Variables_1_src_id_same_var
    },
    {
        "1_src_pair_first_same_var",
        Variables_1_src_pair_first_same_var
    },
    {
        "1_src_pair_second_same_var",
        Variables_1_src_pair_second_same_var
    },
    {
        "1_src_pair_first_and_second_same_var",
        Variables_1_src_pair_first_and_second_same_var
    },
    {
        "1_src_id_same_var_after_write",
        Variables_1_src_id_same_var_after_write
    },
    {
        "1_src_pair_first_same_var_after_write",
        Variables_1_src_pair_first_same_var_after_write
    },
    {
        "1_src_pair_second_same_var_after_write",
        Variables_1_src_pair_second_same_var_after_write
    },
    {
        "1_src_pair_first_and_second_same_var_after_write",
        Variables_1_src_pair_first_and_second_same_var_after_write
    },
    {
        "1_src_pair_first_same_var_this",
        Variables_1_src_pair_first_same_var_this
    },
    {
        "1_src_pair_second_same_var_this",
        Variables_1_src_pair_second_same_var_this
    },
    {
        "1_src_pair_first_and_second_same_var_this",
        Variables_1_src_pair_first_and_second_same_var_this
    },
    {
        "1_src_id_same_var_this_after_write",
        Variables_1_src_id_same_var_this_after_write
    },
    {
        "1_src_pair_first_same_var_this_after_write",
        Variables_1_src_pair_first_same_var_this_after_write
    },
    {
        "1_src_pair_second_same_var_this_after_write",
        Variables_1_src_pair_second_same_var_this_after_write
    },
    {
        "1_src_pair_first_and_second_same_var_this_after_write",
        Variables_1_src_pair_first_and_second_same_var_this_after_write
    },
    {
        "1_ent_src_w_this_var",
        Variables_1_ent_src_w_this_var
    },
    {
        "1_ent_src_w_pair_this_rel",
        Variables_1_ent_src_w_pair_this_rel
    },
    {
        "1_ent_src_w_pair_this_tgt",
        Variables_1_ent_src_w_pair_this_tgt
    },
    {
        "1_ent_src_w_pair_this_rel_tgt",
        Variables_1_ent_src_w_pair_this_rel_tgt
    },
    {
        "1_this_src_w_this",
        Variables_1_this_src_w_this
    },
    {
        "1_this_src_w_pair_this_rel_tgt",
        Variables_1_this_src_w_pair_this_rel_tgt
    },
    {
        "1_this_src_w_this_after_write",
        Variables_1_this_src_w_this_after_write
    },
    {
        "1_this_src_w_pair_this_rel_tgt_after_write",
        Variables_1_this_src_w_pair_this_rel_tgt_after_write
    },
    {
        "2_constrain_src_from_src",
        Variables_2_constrain_src_from_src
    },
    {
        "2_constrain_rel_from_src_w_ent",
        Variables_2_constrain_rel_from_src_w_ent
    },
    {
        "2_constrain_rel_from_src_w_var",
        Variables_2_constrain_rel_from_src_w_var
    },
    {
        "2_constrain_rel_from_src_w_this",
        Variables_2_constrain_rel_from_src_w_this
    },
    {
        "2_constrain_pair_rel_from_src_w_ent",
        Variables_2_constrain_pair_rel_from_src_w_ent
    },
    {
        "2_constrain_pair_rel_from_src_w_var",
        Variables_2_constrain_pair_rel_from_src_w_var
    },
    {
        "2_constrain_pair_rel_from_src_w_this",
        Variables_2_constrain_pair_rel_from_src_w_this
    },
    {
        "2_constrain_pair_tgt_from_src_w_ent",
        Variables_2_constrain_pair_tgt_from_src_w_ent
    },
    {
        "2_constrain_pair_tgt_from_src_w_var",
        Variables_2_constrain_pair_tgt_from_src_w_var
    },
    {
        "2_constrain_pair_tgt_from_src_w_this",
        Variables_2_constrain_pair_tgt_from_src_w_this
    },
    {
        "2_constrain_pair_rel_tgt_from_src_w_ent",
        Variables_2_constrain_pair_rel_tgt_from_src_w_ent
    },
    {
        "2_constrain_pair_rel_tgt_from_src_w_var",
        Variables_2_constrain_pair_rel_tgt_from_src_w_var
    },
    {
        "2_constrain_pair_rel_tgt_from_src_w_this",
        Variables_2_constrain_pair_rel_tgt_from_src_w_this
    },
    {
        "1_ent_src_set_rel_var",
        Variables_1_ent_src_set_rel_var
    },
    {
        "1_ent_src_set_pair_rel_var",
        Variables_1_ent_src_set_pair_rel_var
    },
    {
        "1_ent_src_set_pair_tgt_var",
        Variables_1_ent_src_set_pair_tgt_var
    },
    {
        "1_set_src_var",
        Variables_1_set_src_var
    },
    {
        "1_set_src_var_w_pair",
        Variables_1_set_src_var_w_pair
    },
    {
        "1_set_src_var_w_pair_set_rel",
        Variables_1_set_src_var_w_pair_set_rel
    },
    {
        "1_set_src_var_w_pair_set_tgt",
        Variables_1_set_src_var_w_pair_set_tgt
    },
    {
        "1_set_src_var_w_pair_set_rel_tgt",
        Variables_1_set_src_var_w_pair_set_rel_tgt
    },
    {
        "1_set_src_this",
        Variables_1_set_src_this
    },
    {
        "1_set_src_this_w_pair",
        Variables_1_set_src_this_w_pair
    },
    {
        "1_set_src_this_w_pair_set_rel",
        Variables_1_set_src_this_w_pair_set_rel
    },
    {
        "1_set_src_this_w_pair_set_tgt",
        Variables_1_set_src_this_w_pair_set_tgt
    },
    {
        "1_set_src_this_w_pair_set_rel_tgt",
        Variables_1_set_src_this_w_pair_set_rel_tgt
    },
    {
        "1_set_src_this_to_empty_table",
        Variables_1_set_src_this_to_empty_table
    },
    {
        "1_set_src_this_to_empty_table_w_component",
        Variables_1_set_src_this_to_empty_table_w_component
    },
    {
        "1_set_src_this_to_empty_table_w_component_self",
        Variables_1_set_src_this_to_empty_table_w_component_self
    },
    {
        "1_set_src_this_to_entiy_in_table",
        Variables_1_set_src_this_to_entiy_in_table
    },
    {
        "1_set_src_this_to_entiy_in_table_self",
        Variables_1_set_src_this_to_entiy_in_table_self
    },
    {
        "2_set_src_this",
        Variables_2_set_src_this
    },
    {
        "2_set_src_this_self",
        Variables_2_set_src_this_self
    },
    {
        "2_set_src_this_component",
        Variables_2_set_src_this_component
    },
    {
        "2_set_src_this_self_component",
        Variables_2_set_src_this_self_component
    },
    {
        "2_set_src_this_w_up",
        Variables_2_set_src_this_w_up
    },
    {
        "2_set_src_this_self_w_up",
        Variables_2_set_src_this_self_w_up
    },
    {
        "2_set_src_this_component_w_up",
        Variables_2_set_src_this_component_w_up
    },
    {
        "2_set_src_this_self_component_w_up",
        Variables_2_set_src_this_self_component_w_up
    },
    {
        "2_set_src_this_w_exclusive_wildcard",
        Variables_2_set_src_this_w_exclusive_wildcard
    },
    {
        "2_set_src_this_self_w_exclusive_wildcard",
        Variables_2_set_src_this_self_w_exclusive_wildcard
    },
    {
        "2_set_src_this_self_w_exclusive_wildcard_w_up",
        Variables_2_set_src_this_self_w_exclusive_wildcard_w_up
    },
    {
        "1_set_src_this_is_true",
        Variables_1_set_src_this_is_true
    },
    {
        "2_set_src_this_w_wildcard",
        Variables_2_set_src_this_w_wildcard
    },
    {
        "1_src_this_var_as_entity",
        Variables_1_src_this_var_as_entity
    },
    {
        "1_src_this_var_as_table",
        Variables_1_src_this_var_as_table
    },
    {
        "1_src_this_var_as_table_range",
        Variables_1_src_this_var_as_table_range
    },
    {
        "2_join_by_rel_var",
        Variables_2_join_by_rel_var
    },
    {
        "2_join_by_pair_rel_var",
        Variables_2_join_by_pair_rel_var
    },
    {
        "2_join_by_pair_tgt_var",
        Variables_2_join_by_pair_tgt_var
    },
    {
        "2_cycle_w_var",
        Variables_2_cycle_w_var
    },
    {
        "2_cycle_w_this_var",
        Variables_2_cycle_w_this_var
    },
    {
        "2_cycle_w_var_this",
        Variables_2_cycle_w_var_this
    },
    {
        "2_cycle_pair_w_var",
        Variables_2_cycle_pair_w_var
    },
    {
        "2_cycle_pair_w_this_var_var",
        Variables_2_cycle_pair_w_this_var_var
    },
    {
        "2_cycle_pair_w_var_this_var",
        Variables_2_cycle_pair_w_var_this_var
    },
    {
        "2_cycle_pair_w_var_var_this",
        Variables_2_cycle_pair_w_var_var_this
    },
    {
        "2_cycle_pair_ent_var_var",
        Variables_2_cycle_pair_ent_var_var
    },
    {
        "2_cycle_pair_ent_this_var",
        Variables_2_cycle_pair_ent_this_var
    },
    {
        "2_cycle_pair_ent_var_this",
        Variables_2_cycle_pair_ent_var_this
    },
    {
        "parse_0_var",
        Variables_parse_0_var
    },
    {
        "parse_1_var",
        Variables_parse_1_var
    },
    {
        "parse_2_vars",
        Variables_parse_2_vars
    },
    {
        "parse_0_var_paren",
        Variables_parse_0_var_paren
    },
    {
        "parse_1_var_paren",
        Variables_parse_1_var_paren
    },
    {
        "parse_2_vars_paren",
        Variables_parse_2_vars_paren
    },
    {
        "parse_1_vars_w_path",
        Variables_parse_1_vars_w_path
    },
    {
        "parse_missing_close_paren",
        Variables_parse_missing_close_paren
    },
    {
        "parse_missing_open_paren",
        Variables_parse_missing_open_paren
    },
    {
        "parse_missing_value",
        Variables_parse_missing_value
    },
    {
        "parse_0_var_w_spaces",
        Variables_parse_0_var_w_spaces
    },
    {
        "parse_1_var_w_spaces",
        Variables_parse_1_var_w_spaces
    },
    {
        "parse_2_vars_w_spaces",
        Variables_parse_2_vars_w_spaces
    },
    {
        "parse_0_var_paren_w_spaces",
        Variables_parse_0_var_paren_w_spaces
    },
    {
        "parse_1_var_paren_w_spaces",
        Variables_parse_1_var_paren_w_spaces
    },
    {
        "parse_2_vars_paren_w_spaces",
        Variables_parse_2_vars_paren_w_spaces
    },
    {
        "var_count",
        Variables_var_count
    },
    {
        "var_name",
        Variables_var_name
    },
    {
        "var_is_entity",
        Variables_var_is_entity
    },
    {
        "no_this_anonymous_src",
        Variables_no_this_anonymous_src
    },
    {
        "no_this_anonymous_src_w_pair",
        Variables_no_this_anonymous_src_w_pair
    },
    {
        "no_this_anonymous_component_src",
        Variables_no_this_anonymous_component_src
    },
    {
        "no_this_anonymous_component_src_w_pair",
        Variables_no_this_anonymous_component_src_w_pair
    },
    {
        "lookup_from_table_this",
        Variables_lookup_from_table_this
    },
    {
        "lookup_from_entity_this",
        Variables_lookup_from_entity_this
    },
    {
        "lookup_from_table",
        Variables_lookup_from_table
    },
    {
        "lookup_from_entity",
        Variables_lookup_from_entity
    },
    {
        "lookup_from_not_written",
        Variables_lookup_from_not_written
    },
    {
        "lookup_from_table_this_component",
        Variables_lookup_from_table_this_component
    },
    {
        "lookup_from_entity_this_component",
        Variables_lookup_from_entity_this_component
    },
    {
        "lookup_from_table_component",
        Variables_lookup_from_table_component
    },
    {
        "lookup_from_entity_component",
        Variables_lookup_from_entity_component
    },
    {
        "lookup_from_table_two_children",
        Variables_lookup_from_table_two_children
    },
    {
        "lookup_from_entity_two_children",
        Variables_lookup_from_entity_two_children
    },
    {
        "lookup_from_table_same_child_twice",
        Variables_lookup_from_table_same_child_twice
    },
    {
        "lookup_from_entity_same_child_twice",
        Variables_lookup_from_entity_same_child_twice
    },
    {
        "lookup_from_table_not",
        Variables_lookup_from_table_not
    },
    {
        "lookup_from_entity_not",
        Variables_lookup_from_entity_not
    },
    {
        "lookup_from_table_w_any_component",
        Variables_lookup_from_table_w_any_component
    },
    {
        "lookup_from_entity_w_any_component",
        Variables_lookup_from_entity_w_any_component
    },
    {
        "lookup_as_tag",
        Variables_lookup_as_tag
    },
    {
        "lookup_as_relationship",
        Variables_lookup_as_relationship
    },
    {
        "lookup_as_target",
        Variables_lookup_as_target
    },
    {
        "lookup_assign_var",
        Variables_lookup_assign_var
    },
    {
        "lookup_eq_var",
        Variables_lookup_eq_var
    },
    {
        "lookup_neq_var",
        Variables_lookup_neq_var
    },
    {
        "check_vars_this",
        Variables_check_vars_this
    },
    {
        "check_vars_var",
        Variables_check_vars_var
    },
    {
        "check_vars_wildcard",
        Variables_check_vars_wildcard
    },
    {
        "check_vars_any",
        Variables_check_vars_any
    },
    {
        "check_vars_var_as_tgt",
        Variables_check_vars_var_as_tgt
    },
    {
        "check_vars_this_as_tgt",
        Variables_check_vars_this_as_tgt
    },
    {
        "check_vars_anonymous_var_as_tgt",
        Variables_check_vars_anonymous_var_as_tgt
    },
    {
        "check_vars_wildcard_as_tgt",
        Variables_check_vars_wildcard_as_tgt
    },
    {
        "check_vars_any_as_tgt",
        Variables_check_vars_any_as_tgt
    },
    {
        "check_vars_this_w_lookup_var",
        Variables_check_vars_this_w_lookup_var
    },
    {
        "check_vars_var_w_lookup_var",
        Variables_check_vars_var_w_lookup_var
    },
    {
        "1_trivial_1_var",
        Variables_1_trivial_1_var
    },
    {
        "2_trivial_1_var",
        Variables_2_trivial_1_var
    },
    {
        "1_trivial_1_var_component",
        Variables_1_trivial_1_var_component
    },
    {
        "2_trivial_1_var_component",
        Variables_2_trivial_1_var_component
    },
    {
        "1_trivial_1_wildcard",
        Variables_1_trivial_1_wildcard
    },
    {
        "2_trivial_1_wildcard",
        Variables_2_trivial_1_wildcard
    },
    {
        "1_trivial_1_wildcard_component",
        Variables_1_trivial_1_wildcard_component
    },
    {
        "2_trivial_1_wildcard_component",
        Variables_2_trivial_1_wildcard_component
    },
    {
        "1_trivial_1_any",
        Variables_1_trivial_1_any
    },
    {
        "2_trivial_1_any",
        Variables_2_trivial_1_any
    },
    {
        "1_trivial_1_any_component",
        Variables_1_trivial_1_any_component
    },
    {
        "2_trivial_1_any_component",
        Variables_2_trivial_1_any_component
    }
};

bake_test_case Operators_testcases[] = {
    {
        "2_and_not",
        Operators_2_and_not
    },
    {
        "2_and_not_component",
        Operators_2_and_not_component
    },
    {
        "2_and_out_not",
        Operators_2_and_out_not
    },
    {
        "2_and_out_not_component",
        Operators_2_and_out_not_component
    },
    {
        "3_and_not_not",
        Operators_3_and_not_not
    },
    {
        "2_and_not_pair_rel_wildcard",
        Operators_2_and_not_pair_rel_wildcard
    },
    {
        "2_and_not_pair_tgt_wildcard",
        Operators_2_and_not_pair_tgt_wildcard
    },
    {
        "2_and_not_pair_rel_tgt_wildcard",
        Operators_2_and_not_pair_rel_tgt_wildcard
    },
    {
        "2_and_not_pair_rel_var",
        Operators_2_and_not_pair_rel_var
    },
    {
        "2_and_not_pair_tgt_var",
        Operators_2_and_not_pair_tgt_var
    },
    {
        "2_and_not_pair_rel_tgt_var",
        Operators_2_and_not_pair_rel_tgt_var
    },
    {
        "2_and_not_pair_rel_tgt_same_var",
        Operators_2_and_not_pair_rel_tgt_same_var
    },
    {
        "2_and_not_pair_rel_var_written",
        Operators_2_and_not_pair_rel_var_written
    },
    {
        "2_and_not_pair_tgt_var_written",
        Operators_2_and_not_pair_tgt_var_written
    },
    {
        "2_and_not_pair_rel_tgt_var_written",
        Operators_2_and_not_pair_rel_tgt_var_written
    },
    {
        "2_and_not_pair_rel_tgt_same_var_written",
        Operators_2_and_not_pair_rel_tgt_same_var_written
    },
    {
        "2_and_not_pair_rel_src_tgt_same_var_written",
        Operators_2_and_not_pair_rel_src_tgt_same_var_written
    },
    {
        "2_and_not_pair_any_rel",
        Operators_2_and_not_pair_any_rel
    },
    {
        "2_and_not_pair_any_tgt",
        Operators_2_and_not_pair_any_tgt
    },
    {
        "2_and_not_pair_any_src",
        Operators_2_and_not_pair_any_src
    },
    {
        "2_and_optional",
        Operators_2_and_optional
    },
    {
        "3_and_optional_optional",
        Operators_3_and_optional_optional
    },
    {
        "2_and_optional_pair_rel_wildcard",
        Operators_2_and_optional_pair_rel_wildcard
    },
    {
        "2_and_optional_pair_tgt_wildcard",
        Operators_2_and_optional_pair_tgt_wildcard
    },
    {
        "2_and_optional_pair_rel_var",
        Operators_2_and_optional_pair_rel_var
    },
    {
        "2_and_optional_pair_tgt_var",
        Operators_2_and_optional_pair_tgt_var
    },
    {
        "2_and_optional_pair_rel_tgt_var",
        Operators_2_and_optional_pair_rel_tgt_var
    },
    {
        "2_and_optional_pair_rel_tgt_same_var",
        Operators_2_and_optional_pair_rel_tgt_same_var
    },
    {
        "2_and_optional_pair_rel_var_written",
        Operators_2_and_optional_pair_rel_var_written
    },
    {
        "2_and_optional_pair_tgt_var_written",
        Operators_2_and_optional_pair_tgt_var_written
    },
    {
        "2_and_optional_pair_rel_tgt_var_written",
        Operators_2_and_optional_pair_rel_tgt_var_written
    },
    {
        "2_and_optional_pair_rel_tgt_same_var_written",
        Operators_2_and_optional_pair_rel_tgt_same_var_written
    },
    {
        "2_and_optional_pair_rel_src_tgt_same_var_written",
        Operators_2_and_optional_pair_rel_src_tgt_same_var_written
    },
    {
        "3_and_optional_optional_pair_w_var",
        Operators_3_and_optional_optional_pair_w_var
    },
    {
        "2_and_optional_pair_any_rel",
        Operators_2_and_optional_pair_any_rel
    },
    {
        "2_and_optional_pair_any_tgt",
        Operators_2_and_optional_pair_any_tgt
    },
    {
        "2_and_optional_pair_any_src",
        Operators_2_and_optional_pair_any_src
    },
    {
        "3_and_optional_dependent_and_pair_rel",
        Operators_3_and_optional_dependent_and_pair_rel
    },
    {
        "3_and_optional_dependent_and_pair_tgt",
        Operators_3_and_optional_dependent_and_pair_tgt
    },
    {
        "3_and_optional_dependent_and_pair_rel_tgt",
        Operators_3_and_optional_dependent_and_pair_rel_tgt
    },
    {
        "3_and_optional_dependent_and_pair_rel_tgt_same_var",
        Operators_3_and_optional_dependent_and_pair_rel_tgt_same_var
    },
    {
        "3_and_optional_dependent_and_pair_rel_tgt_same_other_var",
        Operators_3_and_optional_dependent_and_pair_rel_tgt_same_other_var
    },
    {
        "3_and_optional_dependent_and_pair_src",
        Operators_3_and_optional_dependent_and_pair_src
    },
    {
        "3_and_optional_dependent_optional_pair_rel",
        Operators_3_and_optional_dependent_optional_pair_rel
    },
    {
        "3_and_optional_dependent_optional_pair_tgt",
        Operators_3_and_optional_dependent_optional_pair_tgt
    },
    {
        "3_and_optional_dependent_optional_pair_src",
        Operators_3_and_optional_dependent_optional_pair_src
    },
    {
        "3_and_optional_dependent_not_pair_rel",
        Operators_3_and_optional_dependent_not_pair_rel
    },
    {
        "3_and_optional_dependent_not_pair_tgt",
        Operators_3_and_optional_dependent_not_pair_tgt
    },
    {
        "3_and_optional_dependent_not_pair_src",
        Operators_3_and_optional_dependent_not_pair_src
    },
    {
        "2_or",
        Operators_2_or
    },
    {
        "3_or",
        Operators_3_or
    },
    {
        "2_or_w_and",
        Operators_2_or_w_and
    },
    {
        "3_or_w_and",
        Operators_3_or_w_and
    },
    {
        "2_or_written",
        Operators_2_or_written
    },
    {
        "3_or_written",
        Operators_3_or_written
    },
    {
        "2_or_written_w_rel_var",
        Operators_2_or_written_w_rel_var
    },
    {
        "3_or_written_w_rel_var",
        Operators_3_or_written_w_rel_var
    },
    {
        "2_or_written_w_tgt_var",
        Operators_2_or_written_w_tgt_var
    },
    {
        "2_or_written_w_rel_tgt_var",
        Operators_2_or_written_w_rel_tgt_var
    },
    {
        "2_or_written_w_rel_tgt_same_var",
        Operators_2_or_written_w_rel_tgt_same_var
    },
    {
        "3_or_written_w_tgt_var",
        Operators_3_or_written_w_tgt_var
    },
    {
        "2_or_chains",
        Operators_2_or_chains
    },
    {
        "2_or_chains_written",
        Operators_2_or_chains_written
    },
    {
        "2_or_dependent",
        Operators_2_or_dependent
    },
    {
        "2_or_dependent_reverse",
        Operators_2_or_dependent_reverse
    },
    {
        "2_or_dependent_2_vars",
        Operators_2_or_dependent_2_vars
    },
    {
        "2_or_written_dependent",
        Operators_2_or_written_dependent
    },
    {
        "2_or_written_dependent_2_vars",
        Operators_2_or_written_dependent_2_vars
    },
    {
        "2_or_w_dependent",
        Operators_2_or_w_dependent
    },
    {
        "2_or_w_both",
        Operators_2_or_w_both
    },
    {
        "3_or_w_both",
        Operators_3_or_w_both
    },
    {
        "2_or_w_not",
        Operators_2_or_w_not
    },
    {
        "2_or_w_not_component",
        Operators_2_or_w_not_component
    },
    {
        "2_or_w_not_out_component",
        Operators_2_or_w_not_out_component
    },
    {
        "2_or_w_not_out_all_components",
        Operators_2_or_w_not_out_all_components
    },
    {
        "2_not_first",
        Operators_2_not_first
    },
    {
        "2_optional_first",
        Operators_2_optional_first
    },
    {
        "only_not",
        Operators_only_not
    },
    {
        "only_not_component",
        Operators_only_not_component
    },
    {
        "only_not_out_component",
        Operators_only_not_out_component
    },
    {
        "only_optional",
        Operators_only_optional
    },
    {
        "only_optional_component",
        Operators_only_optional_component
    },
    {
        "not_after_fixed_src",
        Operators_not_after_fixed_src
    },
    {
        "optional_after_fixed_src",
        Operators_optional_after_fixed_src
    },
    {
        "root_entities_empty",
        Operators_root_entities_empty
    },
    {
        "root_entities",
        Operators_root_entities
    },
    {
        "root_entities_w_children",
        Operators_root_entities_w_children
    },
    {
        "root_entities_w_optional_children",
        Operators_root_entities_w_optional_children
    },
    {
        "core_entities_w_optional_children",
        Operators_core_entities_w_optional_children
    },
    {
        "root_entities_w_not_children",
        Operators_root_entities_w_not_children
    },
    {
        "core_entities_w_not_children",
        Operators_core_entities_w_not_children
    },
    {
        "1_ent_src_not",
        Operators_1_ent_src_not
    },
    {
        "1_ent_src_not_pair",
        Operators_1_ent_src_not_pair
    },
    {
        "1_ent_src_not_pair_rel_wildcard",
        Operators_1_ent_src_not_pair_rel_wildcard
    },
    {
        "1_ent_src_not_pair_tgt_wildcard",
        Operators_1_ent_src_not_pair_tgt_wildcard
    },
    {
        "1_ent_src_not_pair_rel_tgt_wildcard",
        Operators_1_ent_src_not_pair_rel_tgt_wildcard
    },
    {
        "1_ent_src_not_pair_rel_any",
        Operators_1_ent_src_not_pair_rel_any
    },
    {
        "1_ent_src_not_pair_tgt_any",
        Operators_1_ent_src_not_pair_tgt_any
    },
    {
        "1_ent_src_not_pair_rel_tgt_any",
        Operators_1_ent_src_not_pair_rel_tgt_any
    },
    {
        "1_ent_src_not_pair_rel_var",
        Operators_1_ent_src_not_pair_rel_var
    },
    {
        "1_ent_src_not_pair_tgt_var",
        Operators_1_ent_src_not_pair_tgt_var
    },
    {
        "1_ent_src_not_pair_rel_tgt_var",
        Operators_1_ent_src_not_pair_rel_tgt_var
    },
    {
        "1_ent_src_not_pair_rel_tgt_same_var",
        Operators_1_ent_src_not_pair_rel_tgt_same_var
    },
    {
        "1_this_src_not_pair_rel_var",
        Operators_1_this_src_not_pair_rel_var
    },
    {
        "1_this_src_not_pair_tgt_var",
        Operators_1_this_src_not_pair_tgt_var
    },
    {
        "1_this_src_not_pair_rel_tgt_var",
        Operators_1_this_src_not_pair_rel_tgt_var
    },
    {
        "1_this_src_not_pair_rel_tgt_same_var",
        Operators_1_this_src_not_pair_rel_tgt_same_var
    },
    {
        "1_ent_src_not_pair_rel_var_written",
        Operators_1_ent_src_not_pair_rel_var_written
    },
    {
        "1_ent_src_not_pair_tgt_var_written",
        Operators_1_ent_src_not_pair_tgt_var_written
    },
    {
        "1_ent_src_not_pair_rel_tgt_var_written",
        Operators_1_ent_src_not_pair_rel_tgt_var_written
    },
    {
        "1_ent_src_not_pair_rel_tgt_same_var_written",
        Operators_1_ent_src_not_pair_rel_tgt_same_var_written
    },
    {
        "and_from_fixed_src",
        Operators_and_from_fixed_src
    },
    {
        "not_from_fixed_src",
        Operators_not_from_fixed_src
    },
    {
        "or_from_fixed_src",
        Operators_or_from_fixed_src
    },
    {
        "and_from_this",
        Operators_and_from_this
    },
    {
        "not_from_this",
        Operators_not_from_this
    },
    {
        "or_from_this",
        Operators_or_from_this
    },
    {
        "and_from_this_written",
        Operators_and_from_this_written
    },
    {
        "not_from_this_written",
        Operators_not_from_this_written
    },
    {
        "or_from_this_written",
        Operators_or_from_this_written
    }
};

bake_test_case Transitive_testcases[] = {
    {
        "1_fact_0_lvl_true",
        Transitive_1_fact_0_lvl_true
    },
    {
        "1_fact_1_lvl_true",
        Transitive_1_fact_1_lvl_true
    },
    {
        "1_fact_2_lvl_true",
        Transitive_1_fact_2_lvl_true
    },
    {
        "1_fact_0_lvl_false",
        Transitive_1_fact_0_lvl_false
    },
    {
        "1_fact_1_lvl_false",
        Transitive_1_fact_1_lvl_false
    },
    {
        "1_fact_2_lvl_false",
        Transitive_1_fact_2_lvl_false
    },
    {
        "1_fact_reflexive",
        Transitive_1_fact_reflexive
    },
    {
        "1_isa",
        Transitive_1_isa
    },
    {
        "1_childof",
        Transitive_1_childof
    },
    {
        "1_this_src_written_0_lvl",
        Transitive_1_this_src_written_0_lvl
    },
    {
        "1_this_src_written_1_lvl",
        Transitive_1_this_src_written_1_lvl
    },
    {
        "1_this_src_written_2_lvl",
        Transitive_1_this_src_written_2_lvl
    },
    {
        "1_this_src_written_reflexive",
        Transitive_1_this_src_written_reflexive
    },
    {
        "1_this_src_0_lvl",
        Transitive_1_this_src_0_lvl
    },
    {
        "1_this_src_1_lvl",
        Transitive_1_this_src_1_lvl
    },
    {
        "1_this_src_2_lvl",
        Transitive_1_this_src_2_lvl
    },
    {
        "1_this_src_reflexive",
        Transitive_1_this_src_reflexive
    },
    {
        "1_ent_src_tgt_var_0_lvl",
        Transitive_1_ent_src_tgt_var_0_lvl
    },
    {
        "1_ent_src_tgt_var_1_lvl",
        Transitive_1_ent_src_tgt_var_1_lvl
    },
    {
        "1_ent_src_tgt_var_2_lvl",
        Transitive_1_ent_src_tgt_var_2_lvl
    },
    {
        "1_ent_src_tgt_var_reflexive",
        Transitive_1_ent_src_tgt_var_reflexive
    },
    {
        "1_this_src_tgt_var",
        Transitive_1_this_src_tgt_var
    },
    {
        "1_this_src_tgt_var_reflexive",
        Transitive_1_this_src_tgt_var_reflexive
    },
    {
        "1_var_src_written_0_lvl",
        Transitive_1_var_src_written_0_lvl
    },
    {
        "1_var_src_written_1_lvl",
        Transitive_1_var_src_written_1_lvl
    },
    {
        "1_var_src_written_2_lvl",
        Transitive_1_var_src_written_2_lvl
    },
    {
        "1_var_src_written_reflexive",
        Transitive_1_var_src_written_reflexive
    },
    {
        "1_var_src_0_lvl",
        Transitive_1_var_src_0_lvl
    },
    {
        "1_var_src_1_lvl",
        Transitive_1_var_src_1_lvl
    },
    {
        "1_var_src_2_lvl",
        Transitive_1_var_src_2_lvl
    },
    {
        "1_var_src_reflexive",
        Transitive_1_var_src_reflexive
    },
    {
        "1_var_src_tgt_var",
        Transitive_1_var_src_tgt_var
    },
    {
        "1_var_src_tgt_var_reflexive",
        Transitive_1_var_src_tgt_var_reflexive
    },
    {
        "1_ent_src_tgt_this_0_lvl",
        Transitive_1_ent_src_tgt_this_0_lvl
    },
    {
        "1_ent_src_tgt_this_1_lvl",
        Transitive_1_ent_src_tgt_this_1_lvl
    },
    {
        "1_ent_src_tgt_this_2_lvl",
        Transitive_1_ent_src_tgt_this_2_lvl
    },
    {
        "1_ent_src_tgt_this_reflexive",
        Transitive_1_ent_src_tgt_this_reflexive
    },
    {
        "1_var_src_tgt_this",
        Transitive_1_var_src_tgt_this
    },
    {
        "1_var_src_tgt_this_reflexive",
        Transitive_1_var_src_tgt_this_reflexive
    },
    {
        "2_ent_src_constrain_tgt_var_before_0_lvl",
        Transitive_2_ent_src_constrain_tgt_var_before_0_lvl
    },
    {
        "2_ent_src_constrain_tgt_var_before_1_lvl",
        Transitive_2_ent_src_constrain_tgt_var_before_1_lvl
    },
    {
        "2_ent_src_constrain_tgt_var_before_2_lvl",
        Transitive_2_ent_src_constrain_tgt_var_before_2_lvl
    },
    {
        "2_ent_src_constrain_tgt_var_after_0_lvl",
        Transitive_2_ent_src_constrain_tgt_var_after_0_lvl
    },
    {
        "2_ent_src_constrain_tgt_var_after_1_lvl",
        Transitive_2_ent_src_constrain_tgt_var_after_1_lvl
    },
    {
        "2_ent_src_constrain_tgt_var_after_2_lvl",
        Transitive_2_ent_src_constrain_tgt_var_after_2_lvl
    },
    {
        "2_this_src_constrain_tgt_var_before_0_lvl",
        Transitive_2_this_src_constrain_tgt_var_before_0_lvl
    },
    {
        "2_this_src_constrain_tgt_var_before_1_lvl",
        Transitive_2_this_src_constrain_tgt_var_before_1_lvl
    },
    {
        "2_this_src_constrain_tgt_var_before_2_lvl",
        Transitive_2_this_src_constrain_tgt_var_before_2_lvl
    },
    {
        "2_this_src_constrain_tgt_var_after_0_lvl",
        Transitive_2_this_src_constrain_tgt_var_after_0_lvl
    },
    {
        "2_this_src_constrain_tgt_var_after_1_lvl",
        Transitive_2_this_src_constrain_tgt_var_after_1_lvl
    },
    {
        "2_this_src_constrain_tgt_var_after_2_lvl",
        Transitive_2_this_src_constrain_tgt_var_after_2_lvl
    },
    {
        "1_src_tgt_same_var",
        Transitive_1_src_tgt_same_var
    },
    {
        "1_src_tgt_same_var_reflexive",
        Transitive_1_src_tgt_same_var_reflexive
    },
    {
        "1_src_tgt_same_this_var_reflexive",
        Transitive_1_src_tgt_same_this_var_reflexive
    },
    {
        "1_any_src_tgt_var",
        Transitive_1_any_src_tgt_var
    },
    {
        "not_transitive_ent_tgt",
        Transitive_not_transitive_ent_tgt
    },
    {
        "not_transitive_var_tgt",
        Transitive_not_transitive_var_tgt
    },
    {
        "not_transitive_ent_tgt_written",
        Transitive_not_transitive_ent_tgt_written
    },
    {
        "not_transitive_var_tgt_written",
        Transitive_not_transitive_var_tgt_written
    },
    {
        "optional_transitive_ent_tgt",
        Transitive_optional_transitive_ent_tgt
    },
    {
        "optional_transitive_var_tgt",
        Transitive_optional_transitive_var_tgt
    },
    {
        "optional_transitive_ent_tgt_written",
        Transitive_optional_transitive_ent_tgt_written
    },
    {
        "optional_transitive_var_tgt_written",
        Transitive_optional_transitive_var_tgt_written
    },
    {
        "2_var_src_w_same_tgt_ent",
        Transitive_2_var_src_w_same_tgt_ent
    },
    {
        "self_target",
        Transitive_self_target
    },
    {
        "any_target",
        Transitive_any_target
    }
};

bake_test_case ComponentInheritance_testcases[] = {
    {
        "1_ent_0_lvl",
        ComponentInheritance_1_ent_0_lvl
    },
    {
        "1_ent_1_lvl",
        ComponentInheritance_1_ent_1_lvl
    },
    {
        "1_ent_2_lvl",
        ComponentInheritance_1_ent_2_lvl
    },
    {
        "1_ent_3_lvl",
        ComponentInheritance_1_ent_3_lvl
    },
    {
        "1_this_0_lvl",
        ComponentInheritance_1_this_0_lvl
    },
    {
        "1_this_1_lvl",
        ComponentInheritance_1_this_1_lvl
    },
    {
        "1_this_2_lvl",
        ComponentInheritance_1_this_2_lvl
    },
    {
        "1_this_3_lvl",
        ComponentInheritance_1_this_3_lvl
    },
    {
        "1_this_0_lvl_written",
        ComponentInheritance_1_this_0_lvl_written
    },
    {
        "1_this_1_lvl_written",
        ComponentInheritance_1_this_1_lvl_written
    },
    {
        "1_this_2_lvl_written",
        ComponentInheritance_1_this_2_lvl_written
    },
    {
        "1_this_3_lvl_written",
        ComponentInheritance_1_this_3_lvl_written
    },
    {
        "1_var_0_lvl",
        ComponentInheritance_1_var_0_lvl
    },
    {
        "1_var_1_lvl",
        ComponentInheritance_1_var_1_lvl
    },
    {
        "1_var_2_lvl",
        ComponentInheritance_1_var_2_lvl
    },
    {
        "1_var_3_lvl",
        ComponentInheritance_1_var_3_lvl
    },
    {
        "1_var_0_lvl_written",
        ComponentInheritance_1_var_0_lvl_written
    },
    {
        "1_var_1_lvl_written",
        ComponentInheritance_1_var_1_lvl_written
    },
    {
        "1_var_2_lvl_written",
        ComponentInheritance_1_var_2_lvl_written
    },
    {
        "1_var_3_lvl_written",
        ComponentInheritance_1_var_3_lvl_written
    },
    {
        "1_ent_1_lvl_self",
        ComponentInheritance_1_ent_1_lvl_self
    },
    {
        "1_this_1_lvl_self",
        ComponentInheritance_1_this_1_lvl_self
    },
    {
        "1_this_1_lvl_written_self",
        ComponentInheritance_1_this_1_lvl_written_self
    },
    {
        "1_var_1_lvl_self",
        ComponentInheritance_1_var_1_lvl_self
    },
    {
        "1_var_1_lvl_written_self",
        ComponentInheritance_1_var_1_lvl_written_self
    },
    {
        "1_ent_src_not",
        ComponentInheritance_1_ent_src_not
    },
    {
        "1_this_src_not",
        ComponentInheritance_1_this_src_not
    },
    {
        "1_var_src_not",
        ComponentInheritance_1_var_src_not
    },
    {
        "1_this_src_not_written",
        ComponentInheritance_1_this_src_not_written
    },
    {
        "1_var_src_not_written",
        ComponentInheritance_1_var_src_not_written
    },
    {
        "first_self",
        ComponentInheritance_first_self
    }
};

bake_test_case Recycled_testcases[] = {
    {
        "recycled_vars",
        Recycled_recycled_vars
    },
    {
        "recycled_pair_vars",
        Recycled_recycled_pair_vars
    },
    {
        "recycled_this_ent_var",
        Recycled_recycled_this_ent_var
    },
    {
        "has_recycled_id_from_pair",
        Recycled_has_recycled_id_from_pair
    },
    {
        "recycled_pair",
        Recycled_recycled_pair
    },
    {
        "recycled_component_id",
        Recycled_recycled_component_id
    }
};

bake_test_case BuiltinPredicates_testcases[] = {
    {
        "this_eq_id",
        BuiltinPredicates_this_eq_id
    },
    {
        "this_eq_name",
        BuiltinPredicates_this_eq_name
    },
    {
        "this_eq_var",
        BuiltinPredicates_this_eq_var
    },
    {
        "this_eq_id_written",
        BuiltinPredicates_this_eq_id_written
    },
    {
        "this_eq_id_written_no_match",
        BuiltinPredicates_this_eq_id_written_no_match
    },
    {
        "this_eq_name_written",
        BuiltinPredicates_this_eq_name_written
    },
    {
        "this_eq_name_written_no_match",
        BuiltinPredicates_this_eq_name_written_no_match
    },
    {
        "this_eq_var_written",
        BuiltinPredicates_this_eq_var_written
    },
    {
        "var_eq_id",
        BuiltinPredicates_var_eq_id
    },
    {
        "var_eq_name",
        BuiltinPredicates_var_eq_name
    },
    {
        "var_eq_var",
        BuiltinPredicates_var_eq_var
    },
    {
        "var_eq_id_written",
        BuiltinPredicates_var_eq_id_written
    },
    {
        "var_eq_id_written_no_match",
        BuiltinPredicates_var_eq_id_written_no_match
    },
    {
        "var_eq_name_written",
        BuiltinPredicates_var_eq_name_written
    },
    {
        "var_eq_name_written_no_match",
        BuiltinPredicates_var_eq_name_written_no_match
    },
    {
        "var_eq_var_written",
        BuiltinPredicates_var_eq_var_written
    },
    {
        "var_eq_this",
        BuiltinPredicates_var_eq_this
    },
    {
        "this_neq_id",
        BuiltinPredicates_this_neq_id
    },
    {
        "this_neq_name",
        BuiltinPredicates_this_neq_name
    },
    {
        "this_neq_var",
        BuiltinPredicates_this_neq_var
    },
    {
        "this_neq_id_written",
        BuiltinPredicates_this_neq_id_written
    },
    {
        "this_neq_id_written_no_match",
        BuiltinPredicates_this_neq_id_written_no_match
    },
    {
        "this_neq_name_written",
        BuiltinPredicates_this_neq_name_written
    },
    {
        "this_neq_name_written_no_match",
        BuiltinPredicates_this_neq_name_written_no_match
    },
    {
        "this_neq_var_written",
        BuiltinPredicates_this_neq_var_written
    },
    {
        "var_neq_id",
        BuiltinPredicates_var_neq_id
    },
    {
        "var_neq_name",
        BuiltinPredicates_var_neq_name
    },
    {
        "var_neq_var",
        BuiltinPredicates_var_neq_var
    },
    {
        "var_neq_id_written",
        BuiltinPredicates_var_neq_id_written
    },
    {
        "var_neq_id_written_no_match",
        BuiltinPredicates_var_neq_id_written_no_match
    },
    {
        "var_neq_name_written",
        BuiltinPredicates_var_neq_name_written
    },
    {
        "var_neq_name_written_no_match",
        BuiltinPredicates_var_neq_name_written_no_match
    },
    {
        "var_neq_var_written",
        BuiltinPredicates_var_neq_var_written
    },
    {
        "var_neq_this",
        BuiltinPredicates_var_neq_this
    },
    {
        "this_2_neq_id",
        BuiltinPredicates_this_2_neq_id
    },
    {
        "this_2_neq_name",
        BuiltinPredicates_this_2_neq_name
    },
    {
        "var_2_neq_id",
        BuiltinPredicates_var_2_neq_id
    },
    {
        "var_2_neq_name",
        BuiltinPredicates_var_2_neq_name
    },
    {
        "this_2_neq_id_written",
        BuiltinPredicates_this_2_neq_id_written
    },
    {
        "this_2_neq_name_written",
        BuiltinPredicates_this_2_neq_name_written
    },
    {
        "var_2_neq_id_written",
        BuiltinPredicates_var_2_neq_id_written
    },
    {
        "var_2_neq_name_written",
        BuiltinPredicates_var_2_neq_name_written
    },
    {
        "this_2_or_id",
        BuiltinPredicates_this_2_or_id
    },
    {
        "this_2_or_name",
        BuiltinPredicates_this_2_or_name
    },
    {
        "var_2_or_id",
        BuiltinPredicates_var_2_or_id
    },
    {
        "var_2_or_name",
        BuiltinPredicates_var_2_or_name
    },
    {
        "this_2_or_id_written",
        BuiltinPredicates_this_2_or_id_written
    },
    {
        "this_2_or_name_written",
        BuiltinPredicates_this_2_or_name_written
    },
    {
        "var_2_or_id_written",
        BuiltinPredicates_var_2_or_id_written
    },
    {
        "var_2_or_name_written",
        BuiltinPredicates_var_2_or_name_written
    },
    {
        "this_match_eq",
        BuiltinPredicates_this_match_eq
    },
    {
        "var_match_eq",
        BuiltinPredicates_var_match_eq
    },
    {
        "this_match_eq_written",
        BuiltinPredicates_this_match_eq_written
    },
    {
        "var_match_eq_written",
        BuiltinPredicates_var_match_eq_written
    },
    {
        "this_match_neq",
        BuiltinPredicates_this_match_neq
    },
    {
        "var_match_neq",
        BuiltinPredicates_var_match_neq
    },
    {
        "this_match_neq_written",
        BuiltinPredicates_this_match_neq_written
    },
    {
        "var_match_neq_written",
        BuiltinPredicates_var_match_neq_written
    },
    {
        "this_match_2_neq",
        BuiltinPredicates_this_match_2_neq
    },
    {
        "var_match_2_neq",
        BuiltinPredicates_var_match_2_neq
    },
    {
        "this_match_2_neq_written",
        BuiltinPredicates_this_match_2_neq_written
    },
    {
        "var_match_2_neq_written",
        BuiltinPredicates_var_match_2_neq_written
    },
    {
        "this_match_2_or",
        BuiltinPredicates_this_match_2_or
    },
    {
        "this_match_2_or_written",
        BuiltinPredicates_this_match_2_or_written
    },
    {
        "this_match_3_or",
        BuiltinPredicates_this_match_3_or
    },
    {
        "this_match_3_or_written",
        BuiltinPredicates_this_match_3_or_written
    },
    {
        "unresolved_by_name",
        BuiltinPredicates_unresolved_by_name
    },
    {
        "var_eq_wildcard",
        BuiltinPredicates_var_eq_wildcard
    },
    {
        "var_eq_any",
        BuiltinPredicates_var_eq_any
    },
    {
        "var_eq_wildcard_after_write",
        BuiltinPredicates_var_eq_wildcard_after_write
    },
    {
        "var_eq_any_after_write",
        BuiltinPredicates_var_eq_any_after_write
    },
    {
        "var_eq_after_var_0_src",
        BuiltinPredicates_var_eq_after_var_0_src
    },
    {
        "2_or_w_eq_this",
        BuiltinPredicates_2_or_w_eq_this
    },
    {
        "2_or_w_eq_lookup_var",
        BuiltinPredicates_2_or_w_eq_lookup_var
    },
    {
        "3_or_w_eq_lookup_var",
        BuiltinPredicates_3_or_w_eq_lookup_var
    }
};

bake_test_case Scopes_testcases[] = {
    {
        "term_w_not_scope_1_term",
        Scopes_term_w_not_scope_1_term
    },
    {
        "term_w_not_scope_2_terms",
        Scopes_term_w_not_scope_2_terms
    },
    {
        "term_w_not_scope_1_term_w_not",
        Scopes_term_w_not_scope_1_term_w_not
    },
    {
        "term_w_not_scope_2_terms_w_not",
        Scopes_term_w_not_scope_2_terms_w_not
    },
    {
        "term_w_not_scope_1_term_w_var",
        Scopes_term_w_not_scope_1_term_w_var
    },
    {
        "term_w_not_scope_2_terms_w_var",
        Scopes_term_w_not_scope_2_terms_w_var
    },
    {
        "term_w_not_scope_1_term_w_not_w_var",
        Scopes_term_w_not_scope_1_term_w_not_w_var
    },
    {
        "term_w_not_scope_2_terms_w_not_w_var",
        Scopes_term_w_not_scope_2_terms_w_not_w_var
    },
    {
        "term_w_not_scope_2_terms_w_or",
        Scopes_term_w_not_scope_2_terms_w_or
    },
    {
        "term_w_not_scope_3_terms_w_or",
        Scopes_term_w_not_scope_3_terms_w_or
    }
};

bake_test_case Traversal_testcases[] = {
    {
        "this_self_up_childof",
        Traversal_this_self_up_childof
    },
    {
        "this_up_childof",
        Traversal_this_up_childof
    },
    {
        "this_written_self_up_childof",
        Traversal_this_written_self_up_childof
    },
    {
        "this_written_up_childof",
        Traversal_this_written_up_childof
    },
    {
        "var_self_up_childof",
        Traversal_var_self_up_childof
    },
    {
        "var_up_childof",
        Traversal_var_up_childof
    },
    {
        "var_written_self_up_childof",
        Traversal_var_written_self_up_childof
    },
    {
        "var_written_up_childof",
        Traversal_var_written_up_childof
    },
    {
        "set_var_self_up_childof",
        Traversal_set_var_self_up_childof
    },
    {
        "set_var_up_childof",
        Traversal_set_var_up_childof
    },
    {
        "set_var_written_self_up_childof",
        Traversal_set_var_written_self_up_childof
    },
    {
        "set_var_written_up_childof",
        Traversal_set_var_written_up_childof
    },
    {
        "ent_self_up_childof",
        Traversal_ent_self_up_childof
    },
    {
        "ent_up_childof",
        Traversal_ent_up_childof
    },
    {
        "implicit_this_self_up_isa",
        Traversal_implicit_this_self_up_isa
    },
    {
        "implicit_this_up_isa",
        Traversal_implicit_this_up_isa
    },
    {
        "implicit_var_self_up_isa",
        Traversal_implicit_var_self_up_isa
    },
    {
        "implicit_var_up_isa",
        Traversal_implicit_var_up_isa
    },
    {
        "implicit_ent_self_up_isa",
        Traversal_implicit_ent_self_up_isa
    },
    {
        "implicit_ent_up_isa",
        Traversal_implicit_ent_up_isa
    },
    {
        "self_up_2_targets",
        Traversal_self_up_2_targets
    },
    {
        "up_2_targets",
        Traversal_up_2_targets
    },
    {
        "self_up_2_targets_diamond",
        Traversal_self_up_2_targets_diamond
    },
    {
        "up_2_targets_diamond",
        Traversal_up_2_targets_diamond
    },
    {
        "written_self_up_2_targets",
        Traversal_written_self_up_2_targets
    },
    {
        "written_up_2_targets",
        Traversal_written_up_2_targets
    },
    {
        "written_self_up_2_targets_diamond",
        Traversal_written_self_up_2_targets_diamond
    },
    {
        "written_up_2_targets_diamond",
        Traversal_written_up_2_targets_diamond
    },
    {
        "2_self_up_terms",
        Traversal_2_self_up_terms
    },
    {
        "2_self_up_terms_2_targets",
        Traversal_2_self_up_terms_2_targets
    },
    {
        "self_up_empty_table",
        Traversal_self_up_empty_table
    },
    {
        "up_empty_table",
        Traversal_up_empty_table
    },
    {
        "self_up_all_owned",
        Traversal_self_up_all_owned
    },
    {
        "up_all_owned",
        Traversal_up_all_owned
    },
    {
        "this_self_up_childof_inherited",
        Traversal_this_self_up_childof_inherited
    },
    {
        "this_up_childof_inherited",
        Traversal_this_up_childof_inherited
    },
    {
        "this_written_self_up_childof_inherited",
        Traversal_this_written_self_up_childof_inherited
    },
    {
        "this_written_up_childof_inherited",
        Traversal_this_written_up_childof_inherited
    },
    {
        "var_self_up_childof_inherited",
        Traversal_var_self_up_childof_inherited
    },
    {
        "var_up_childof_inherited",
        Traversal_var_up_childof_inherited
    },
    {
        "var_written_self_up_childof_inherited",
        Traversal_var_written_self_up_childof_inherited
    },
    {
        "var_written_up_childof_inherited",
        Traversal_var_written_up_childof_inherited
    },
    {
        "ent_self_up_childof_inherited",
        Traversal_ent_self_up_childof_inherited
    },
    {
        "ent_up_childof_inherited",
        Traversal_ent_up_childof_inherited
    },
    {
        "ent_written_self_up_childof_inherited",
        Traversal_ent_written_self_up_childof_inherited
    },
    {
        "ent_written_up_childof_inherited",
        Traversal_ent_written_up_childof_inherited
    },
    {
        "this_self_up_childof_component",
        Traversal_this_self_up_childof_component
    },
    {
        "this_up_childof_component",
        Traversal_this_up_childof_component
    },
    {
        "this_written_self_up_childof_component",
        Traversal_this_written_self_up_childof_component
    },
    {
        "this_written_up_childof_component",
        Traversal_this_written_up_childof_component
    },
    {
        "var_self_up_childof_component",
        Traversal_var_self_up_childof_component
    },
    {
        "var_up_childof_component",
        Traversal_var_up_childof_component
    },
    {
        "var_written_self_up_childof_component",
        Traversal_var_written_self_up_childof_component
    },
    {
        "var_written_up_childof_component",
        Traversal_var_written_up_childof_component
    },
    {
        "this_self_up_childof_recycled_parent",
        Traversal_this_self_up_childof_recycled_parent
    },
    {
        "this_up_childof_recycled_parent",
        Traversal_this_up_childof_recycled_parent
    },
    {
        "this_written_self_up_childof_recycled_parent",
        Traversal_this_written_self_up_childof_recycled_parent
    },
    {
        "this_written_up_childof_recycled_parent",
        Traversal_this_written_up_childof_recycled_parent
    },
    {
        "this_self_up_childof_recycled_parent_component",
        Traversal_this_self_up_childof_recycled_parent_component
    },
    {
        "this_up_childof_recycled_parent_component",
        Traversal_this_up_childof_recycled_parent_component
    },
    {
        "this_written_self_up_childof_recycled_parent_component",
        Traversal_this_written_self_up_childof_recycled_parent_component
    },
    {
        "this_written_up_childof_recycled_parent_component",
        Traversal_this_written_up_childof_recycled_parent_component
    },
    {
        "this_self_up_childof_pair",
        Traversal_this_self_up_childof_pair
    },
    {
        "this_up_childof_pair",
        Traversal_this_up_childof_pair
    },
    {
        "this_written_self_up_childof_pair",
        Traversal_this_written_self_up_childof_pair
    },
    {
        "this_written_up_childof_pair",
        Traversal_this_written_up_childof_pair
    },
    {
        "this_self_up_childof_pair_wildcard",
        Traversal_this_self_up_childof_pair_wildcard
    },
    {
        "this_up_childof_pair_wildcard",
        Traversal_this_up_childof_pair_wildcard
    },
    {
        "this_written_self_up_childof_pair_wildcard",
        Traversal_this_written_self_up_childof_pair_wildcard
    },
    {
        "this_written_up_childof_pair_wildcard",
        Traversal_this_written_up_childof_pair_wildcard
    },
    {
        "this_self_up_childof_pair_tgt_var",
        Traversal_this_self_up_childof_pair_tgt_var
    },
    {
        "this_written_self_up_childof_pair_tgt_var",
        Traversal_this_written_self_up_childof_pair_tgt_var
    },
    {
        "this_self_up_childof_pair_rel_var",
        Traversal_this_self_up_childof_pair_rel_var
    },
    {
        "this_written_self_up_childof_pair_rel_var",
        Traversal_this_written_self_up_childof_pair_rel_var
    },
    {
        "this_self_up_childof_pair_for_var_written",
        Traversal_this_self_up_childof_pair_for_var_written
    },
    {
        "this_up_childof_pair_for_var_written",
        Traversal_this_up_childof_pair_for_var_written
    },
    {
        "this_written_self_up_childof_pair_for_var_written",
        Traversal_this_written_self_up_childof_pair_for_var_written
    },
    {
        "this_self_up_childof_pair_for_var_written_n_targets",
        Traversal_this_self_up_childof_pair_for_var_written_n_targets
    },
    {
        "this_written_self_up_childof_pair_for_var_written_n_targets",
        Traversal_this_written_self_up_childof_pair_for_var_written_n_targets
    },
    {
        "self_up_2_levels",
        Traversal_self_up_2_levels
    },
    {
        "not_up_disabled",
        Traversal_not_up_disabled
    },
    {
        "up_2_rel_instances",
        Traversal_up_2_rel_instances
    },
    {
        "up_2_rel_instances_match_2nd",
        Traversal_up_2_rel_instances_match_2nd
    },
    {
        "up_only_w_owned",
        Traversal_up_only_w_owned
    },
    {
        "this_up_trav_unused_rel",
        Traversal_this_up_trav_unused_rel
    },
    {
        "this_optional_self",
        Traversal_this_optional_self
    },
    {
        "this_optional_up",
        Traversal_this_optional_up
    },
    {
        "this_optional_self_up",
        Traversal_this_optional_self_up
    },
    {
        "this_written_optional_self",
        Traversal_this_written_optional_self
    },
    {
        "this_written_optional_up",
        Traversal_this_written_optional_up
    },
    {
        "this_written_optional_self_up",
        Traversal_this_written_optional_self_up
    },
    {
        "fixed_src_w_up",
        Traversal_fixed_src_w_up
    },
    {
        "match_empty_table_up",
        Traversal_match_empty_table_up
    },
    {
        "match_empty_table_up_written",
        Traversal_match_empty_table_up_written
    },
    {
        "match_empty_table_up_implicit_isa",
        Traversal_match_empty_table_up_implicit_isa
    },
    {
        "match_empty_table_up_written_implicit_isa",
        Traversal_match_empty_table_up_written_implicit_isa
    },
    {
        "match_empty_table_up_isa",
        Traversal_match_empty_table_up_isa
    },
    {
        "match_empty_table_up_written_isa",
        Traversal_match_empty_table_up_written_isa
    }
};

bake_test_case Cascade_testcases[] = {
    {
        "this_self_cascade_childof_uncached",
        Cascade_this_self_cascade_childof_uncached
    },
    {
        "this_cascade_childof_uncached",
        Cascade_this_cascade_childof_uncached
    },
    {
        "this_written_self_cascade_childof_uncached",
        Cascade_this_written_self_cascade_childof_uncached
    },
    {
        "this_written_cascade_childof_uncached",
        Cascade_this_written_cascade_childof_uncached
    },
    {
        "this_self_cascade_childof_w_parent_flag_uncached",
        Cascade_this_self_cascade_childof_w_parent_flag_uncached
    },
    {
        "this_cascade_childof_w_parent_flag_uncached",
        Cascade_this_cascade_childof_w_parent_flag_uncached
    },
    {
        "this_written_self_cascade_childof_w_parent_flag_uncached",
        Cascade_this_written_self_cascade_childof_w_parent_flag_uncached
    },
    {
        "this_written_cascade_childof_w_parent_flag_uncached",
        Cascade_this_written_cascade_childof_w_parent_flag_uncached
    },
    {
        "parent_cascade",
        Cascade_parent_cascade
    },
    {
        "existing_custom_rel_cascade",
        Cascade_existing_custom_rel_cascade
    },
    {
        "new_custom_rel_cascade",
        Cascade_new_custom_rel_cascade
    },
    {
        "cascade_w_2_depths",
        Cascade_cascade_w_2_depths
    },
    {
        "cascade_w_3_depths",
        Cascade_cascade_w_3_depths
    },
    {
        "cascade_w_2_depths_desc",
        Cascade_cascade_w_2_depths_desc
    },
    {
        "cascade_w_3_depths_desc",
        Cascade_cascade_w_3_depths_desc
    },
    {
        "existing_isa_cascade",
        Cascade_existing_isa_cascade
    },
    {
        "new_isa_cascade",
        Cascade_new_isa_cascade
    },
    {
        "childof_cascade",
        Cascade_childof_cascade
    },
    {
        "cascade_rematch_2_lvls",
        Cascade_cascade_rematch_2_lvls
    },
    {
        "cascade_rematch_2_lvls_2_relations",
        Cascade_cascade_rematch_2_lvls_2_relations
    },
    {
        "cascade_topological",
        Cascade_cascade_topological
    },
    {
        "cascade_desc_rematch_2_lvls",
        Cascade_cascade_desc_rematch_2_lvls
    },
    {
        "cascade_desc_rematch_2_lvls_2_relations",
        Cascade_cascade_desc_rematch_2_lvls_2_relations
    },
    {
        "cascade_desc_topological",
        Cascade_cascade_desc_topological
    }
};

bake_test_case Cached_testcases[] = {
    {
        "simple_query_existing_table",
        Cached_simple_query_existing_table
    },
    {
        "simple_query_2_existing_tables",
        Cached_simple_query_2_existing_tables
    },
    {
        "simple_query_new_table",
        Cached_simple_query_new_table
    },
    {
        "simple_query_2_new_tables",
        Cached_simple_query_2_new_tables
    },
    {
        "simple_query_existing_and_new_table",
        Cached_simple_query_existing_and_new_table
    },
    {
        "wildcard_query_existing_table",
        Cached_wildcard_query_existing_table
    },
    {
        "wildcard_query_new_table",
        Cached_wildcard_query_new_table
    },
    {
        "wildcard_query_existing_table_2_results_p_table",
        Cached_wildcard_query_existing_table_2_results_p_table
    },
    {
        "wildcard_query_new_table_2_results_p_table",
        Cached_wildcard_query_new_table_2_results_p_table
    },
    {
        "wildcard_query_2nd_term",
        Cached_wildcard_query_2nd_term
    },
    {
        "wildcard_query_2nd_term_self",
        Cached_wildcard_query_2nd_term_self
    },
    {
        "simple_query_existing_empty_table",
        Cached_simple_query_existing_empty_table
    },
    {
        "simple_query_existing_empty_type",
        Cached_simple_query_existing_empty_type
    },
    {
        "simple_query_new_empty_table",
        Cached_simple_query_new_empty_table
    },
    {
        "component_query_existing_table",
        Cached_component_query_existing_table
    },
    {
        "component_query_new_table",
        Cached_component_query_new_table
    },
    {
        "component_query_existing_empty_table",
        Cached_component_query_existing_empty_table
    },
    {
        "2_component_query_existing_empty_table",
        Cached_2_component_query_existing_empty_table
    },
    {
        "2_component_query_existing_empty_type",
        Cached_2_component_query_existing_empty_type
    },
    {
        "only_optional",
        Cached_only_optional
    },
    {
        "only_optional_new_empty_table",
        Cached_only_optional_new_empty_table
    },
    {
        "only_optional_new_empty_non_empty_table",
        Cached_only_optional_new_empty_non_empty_table
    },
    {
        "only_optional_new_unset_tables",
        Cached_only_optional_new_unset_tables
    },
    {
        "singleton_w_optional_new_empty_table",
        Cached_singleton_w_optional_new_empty_table
    },
    {
        "singleton_w_optional_new_empty_non_empty_table",
        Cached_singleton_w_optional_new_empty_non_empty_table
    },
    {
        "singleton_w_optional_new_unset_tables",
        Cached_singleton_w_optional_new_unset_tables
    },
    {
        "query_w_from_entity_match_after",
        Cached_query_w_from_entity_match_after
    },
    {
        "query_w_from_singleton_match_after",
        Cached_query_w_from_singleton_match_after
    },
    {
        "query_rematch_optional_after_add",
        Cached_query_rematch_optional_after_add
    },
    {
        "get_owned_tag",
        Cached_get_owned_tag
    },
    {
        "get_shared_tag",
        Cached_get_shared_tag
    },
    {
        "explicit_delete",
        Cached_explicit_delete
    },
    {
        "get_column_size",
        Cached_get_column_size
    },
    {
        "stresstest_query_free",
        Cached_stresstest_query_free
    },
    {
        "query_optional_tag",
        Cached_query_optional_tag
    },
    {
        "query_optional_shared_tag",
        Cached_query_optional_shared_tag
    },
    {
        "query_iter_10_tags",
        Cached_query_iter_10_tags
    },
    {
        "query_iter_10_components",
        Cached_query_iter_10_components
    },
    {
        "iter_type_set",
        Cached_iter_type_set
    },
    {
        "filter_term",
        Cached_filter_term
    },
    {
        "2_terms_1_filter",
        Cached_2_terms_1_filter
    },
    {
        "3_terms_2_filter",
        Cached_3_terms_2_filter
    },
    {
        "no_instancing_w_singleton",
        Cached_no_instancing_w_singleton
    },
    {
        "add_singleton_after_query",
        Cached_add_singleton_after_query
    },
    {
        "query_w_component_from_parent_from_non_this",
        Cached_query_w_component_from_parent_from_non_this
    },
    {
        "create_query_while_pending",
        Cached_create_query_while_pending
    },
    {
        "empty_query",
        Cached_empty_query
    },
    {
        "not_pair_relation_wildcard",
        Cached_not_pair_relation_wildcard
    },
    {
        "not_pair_object_wildcard",
        Cached_not_pair_object_wildcard
    },
    {
        "two_pair_wildcards_one_not",
        Cached_two_pair_wildcards_one_not
    },
    {
        "two_pair_wildcards_one_not_any",
        Cached_two_pair_wildcards_one_not_any
    },
    {
        "implicit_existing_isa_superset",
        Cached_implicit_existing_isa_superset
    },
    {
        "implicit_new_isa_superset",
        Cached_implicit_new_isa_superset
    },
    {
        "isa_superset",
        Cached_isa_superset
    },
    {
        "isa_superset_2_lvls",
        Cached_isa_superset_2_lvls
    },
    {
        "isa_superset_3_lvls",
        Cached_isa_superset_3_lvls
    },
    {
        "isa_superset_2_lvls_owned",
        Cached_isa_superset_2_lvls_owned
    },
    {
        "isa_superset_3_lvls_owned",
        Cached_isa_superset_3_lvls_owned
    },
    {
        "isa_superset_owned_empty_table_after_match",
        Cached_isa_superset_owned_empty_table_after_match
    },
    {
        "isa_self_superset",
        Cached_isa_self_superset
    },
    {
        "childof_superset",
        Cached_childof_superset
    },
    {
        "superset_2_targets",
        Cached_superset_2_targets
    },
    {
        "superset_2_relations",
        Cached_superset_2_relations
    },
    {
        "superset_2_relations_instanced",
        Cached_superset_2_relations_instanced
    },
    {
        "superset_2_relations_w_component",
        Cached_superset_2_relations_w_component
    },
    {
        "superset_2_relations_instanced_w_component",
        Cached_superset_2_relations_instanced_w_component
    },
    {
        "parent",
        Cached_parent
    },
    {
        "isa_rematch",
        Cached_isa_rematch
    },
    {
        "childof_rematch",
        Cached_childof_rematch
    },
    {
        "isa_unmatch",
        Cached_isa_unmatch
    },
    {
        "childof_unmatch",
        Cached_childof_unmatch
    },
    {
        "isa_rematch_2_lvls",
        Cached_isa_rematch_2_lvls
    },
    {
        "childof_rematch_2_lvls",
        Cached_childof_rematch_2_lvls
    },
    {
        "childof_rematch_from_isa",
        Cached_childof_rematch_from_isa
    },
    {
        "rematch_optional_ref",
        Cached_rematch_optional_ref
    },
    {
        "rematch_optional_ref_w_2_refs",
        Cached_rematch_optional_ref_w_2_refs
    },
    {
        "rematch_optional_ref_tag_w_ref_component",
        Cached_rematch_optional_ref_tag_w_ref_component
    },
    {
        "match_query_expr_from_scope",
        Cached_match_query_expr_from_scope
    },
    {
        "query_long_or_w_ref",
        Cached_query_long_or_w_ref
    },
    {
        "query_w_pair_id_and_subj",
        Cached_query_w_pair_id_and_subj
    },
    {
        "rematch_after_delete_inherited_tag",
        Cached_rematch_after_delete_inherited_tag
    },
    {
        "rematch_after_delete_rel_of_inherited_pair",
        Cached_rematch_after_delete_rel_of_inherited_pair
    },
    {
        "rematch_after_delete_obj_of_inherited_pair",
        Cached_rematch_after_delete_obj_of_inherited_pair
    },
    {
        "rematch_empty_table_w_superset",
        Cached_rematch_empty_table_w_superset
    },
    {
        "2_self_up_terms_new_tables",
        Cached_2_self_up_terms_new_tables
    },
    {
        "this_self_up_childof_pair_new_tables",
        Cached_this_self_up_childof_pair_new_tables
    }
};

bake_test_case ChangeDetection_testcases[] = {
    {
        "query_changed_after_new",
        ChangeDetection_query_changed_after_new
    },
    {
        "query_changed_after_delete",
        ChangeDetection_query_changed_after_delete
    },
    {
        "query_changed_after_add",
        ChangeDetection_query_changed_after_add
    },
    {
        "query_changed_after_remove",
        ChangeDetection_query_changed_after_remove
    },
    {
        "query_changed_after_set",
        ChangeDetection_query_changed_after_set
    },
    {
        "query_change_after_modified",
        ChangeDetection_query_change_after_modified
    },
    {
        "query_change_after_out_system",
        ChangeDetection_query_change_after_out_system
    },
    {
        "query_change_after_in_system",
        ChangeDetection_query_change_after_in_system
    },
    {
        "query_change_after_modified_out_term",
        ChangeDetection_query_change_after_modified_out_term
    },
    {
        "query_change_check_iter",
        ChangeDetection_query_change_check_iter
    },
    {
        "query_change_check_iter_after_skip_read",
        ChangeDetection_query_change_check_iter_after_skip_read
    },
    {
        "query_change_check_iter_after_skip_write",
        ChangeDetection_query_change_check_iter_after_skip_write
    },
    {
        "query_change_parent_term",
        ChangeDetection_query_change_parent_term
    },
    {
        "query_change_prefab_term",
        ChangeDetection_query_change_prefab_term
    },
    {
        "query_change_parent_term_w_tag",
        ChangeDetection_query_change_parent_term_w_tag
    },
    {
        "query_change_prefab_term_w_tag",
        ChangeDetection_query_change_prefab_term_w_tag
    },
    {
        "query_change_skip_non_instanced",
        ChangeDetection_query_change_skip_non_instanced
    },
    {
        "query_changed_w_or",
        ChangeDetection_query_changed_w_or
    },
    {
        "query_changed_or",
        ChangeDetection_query_changed_or
    },
    {
        "query_changed_w_singleton",
        ChangeDetection_query_changed_w_singleton
    },
    {
        "query_changed_w_only_singleton",
        ChangeDetection_query_changed_w_only_singleton
    },
    {
        "query_changed_w_only_singleton_after_set",
        ChangeDetection_query_changed_w_only_singleton_after_set
    },
    {
        "query_changed_w_only_singleton_after_out_term",
        ChangeDetection_query_changed_w_only_singleton_after_out_term
    },
    {
        "query_changed_w_only_singleton_after_singleton_out_term",
        ChangeDetection_query_changed_w_only_singleton_after_singleton_out_term
    },
    {
        "query_changed_w_only_parent",
        ChangeDetection_query_changed_w_only_parent
    },
    {
        "query_changed_w_only_parent_after_set",
        ChangeDetection_query_changed_w_only_parent_after_set
    },
    {
        "query_changed_w_only_parent_after_out_term",
        ChangeDetection_query_changed_w_only_parent_after_out_term
    },
    {
        "query_changed_w_only_parent_after_parent_out_term",
        ChangeDetection_query_changed_w_only_parent_after_parent_out_term
    },
    {
        "query_changed_tag",
        ChangeDetection_query_changed_tag
    },
    {
        "query_changed_no_source",
        ChangeDetection_query_changed_no_source
    },
    {
        "query_changed_no_source_component",
        ChangeDetection_query_changed_no_source_component
    },
    {
        "query_changed_w_not_out",
        ChangeDetection_query_changed_w_not_out
    }
};

bake_test_case GroupBy_testcases[] = {
    {
        "group_by",
        GroupBy_group_by
    },
    {
        "group_by_w_ctx",
        GroupBy_group_by_w_ctx
    },
    {
        "group_by_w_sort_reverse_group_creation",
        GroupBy_group_by_w_sort_reverse_group_creation
    },
    {
        "group_by_iter_one",
        GroupBy_group_by_iter_one
    },
    {
        "group_by_iter_one_all_groups",
        GroupBy_group_by_iter_one_all_groups
    },
    {
        "group_by_iter_one_empty",
        GroupBy_group_by_iter_one_empty
    },
    {
        "group_by_iter_one_empty_query",
        GroupBy_group_by_iter_one_empty_query
    },
    {
        "group_by_iter_one_empty_table",
        GroupBy_group_by_iter_one_empty_table
    },
    {
        "group_by_w_deleted_group_id",
        GroupBy_group_by_w_deleted_group_id
    },
    {
        "group_by_callbacks",
        GroupBy_group_by_callbacks
    },
    {
        "group_by_default_action",
        GroupBy_group_by_default_action
    },
    {
        "group_table_count",
        GroupBy_group_table_count
    }
};

bake_test_case MemberTarget_testcases[] = {
    {
        "this_member_eq_1",
        MemberTarget_this_member_eq_1
    },
    {
        "this_member_eq_2",
        MemberTarget_this_member_eq_2
    },
    {
        "this_member_eq_no_matches",
        MemberTarget_this_member_eq_no_matches
    },
    {
        "this_member_eq_all_matches",
        MemberTarget_this_member_eq_all_matches
    },
    {
        "this_member_wildcard",
        MemberTarget_this_member_wildcard
    },
    {
        "this_member_var",
        MemberTarget_this_member_var
    },
    {
        "this_member_var_written",
        MemberTarget_this_member_var_written
    },
    {
        "this_member_var_read",
        MemberTarget_this_member_var_read
    },
    {
        "this_member_eq_1_2nd_member",
        MemberTarget_this_member_eq_1_2nd_member
    },
    {
        "this_member_eq_2_2nd_member",
        MemberTarget_this_member_eq_2_2nd_member
    },
    {
        "this_member_var_same_1",
        MemberTarget_this_member_var_same_1
    },
    {
        "this_member_var_same_2",
        MemberTarget_this_member_var_same_2
    },
    {
        "this_written_member_eq_1",
        MemberTarget_this_written_member_eq_1
    },
    {
        "this_written_member_eq_2",
        MemberTarget_this_written_member_eq_2
    },
    {
        "this_written_member_wildcard",
        MemberTarget_this_written_member_wildcard
    },
    {
        "this_written_member_var",
        MemberTarget_this_written_member_var
    },
    {
        "this_member_neq_1",
        MemberTarget_this_member_neq_1
    },
    {
        "this_member_neq_2",
        MemberTarget_this_member_neq_2
    },
    {
        "this_member_neq_no_matches",
        MemberTarget_this_member_neq_no_matches
    },
    {
        "this_member_neq_all_matches",
        MemberTarget_this_member_neq_all_matches
    },
    {
        "this_member_neq_wildcard",
        MemberTarget_this_member_neq_wildcard
    },
    {
        "this_written_member_neq_1",
        MemberTarget_this_written_member_neq_1
    },
    {
        "this_written_member_neq_2",
        MemberTarget_this_written_member_neq_2
    },
    {
        "this_written_member_neq_no_matches",
        MemberTarget_this_written_member_neq_no_matches
    },
    {
        "this_written_member_neq_all_matches",
        MemberTarget_this_written_member_neq_all_matches
    },
    {
        "this_written_member_neq_wildcard",
        MemberTarget_this_written_member_neq_wildcard
    },
    {
        "this_member_eq_optional",
        MemberTarget_this_member_eq_optional
    },
    {
        "this_member_eq_optional_wildcard",
        MemberTarget_this_member_eq_optional_wildcard
    },
    {
        "this_written_member_eq_optional",
        MemberTarget_this_written_member_eq_optional
    },
    {
        "this_written_member_eq_optional_wildcard",
        MemberTarget_this_written_member_eq_optional_wildcard
    },
    {
        "this_2_or",
        MemberTarget_this_2_or
    },
    {
        "this_3_or",
        MemberTarget_this_3_or
    },
    {
        "this_written_2_or",
        MemberTarget_this_written_2_or
    },
    {
        "this_written_3_or",
        MemberTarget_this_written_3_or
    },
    {
        "var_member_eq",
        MemberTarget_var_member_eq
    },
    {
        "var_member_eq_no_matches",
        MemberTarget_var_member_eq_no_matches
    },
    {
        "var_member_eq_all_matches",
        MemberTarget_var_member_eq_all_matches
    },
    {
        "var_member_wildcard",
        MemberTarget_var_member_wildcard
    },
    {
        "var_member_neq",
        MemberTarget_var_member_neq
    },
    {
        "var_member_neq_no_matches",
        MemberTarget_var_member_neq_no_matches
    },
    {
        "var_member_neq_all_matches",
        MemberTarget_var_member_neq_all_matches
    },
    {
        "var_written_member_eq",
        MemberTarget_var_written_member_eq
    },
    {
        "var_written_member_eq_no_matches",
        MemberTarget_var_written_member_eq_no_matches
    },
    {
        "var_written_member_eq_all_matches",
        MemberTarget_var_written_member_eq_all_matches
    },
    {
        "var_written_member_wildcard",
        MemberTarget_var_written_member_wildcard
    },
    {
        "var_written_member_neq",
        MemberTarget_var_written_member_neq
    },
    {
        "var_written_member_neq_no_matches",
        MemberTarget_var_written_member_neq_no_matches
    },
    {
        "var_written_member_neq_all_matches",
        MemberTarget_var_written_member_neq_all_matches
    }
};

bake_test_case Toggle_testcases[] = {
    {
        "query_disabled_from_nothing",
        Toggle_query_disabled_from_nothing
    }
};

bake_test_param Basic_params[] = {
    {"cache_kind", (char*[]){"default", "auto"}, 2}
};
bake_test_param Variables_params[] = {
    {"cache_kind", (char*[]){"default", "auto"}, 2}
};
bake_test_param Operators_params[] = {
    {"cache_kind", (char*[]){"default", "auto"}, 2}
};
bake_test_param Recycled_params[] = {
    {"cache_kind", (char*[]){"default", "auto"}, 2}
};
bake_test_param Traversal_params[] = {
    {"cache_kind", (char*[]){"default", "auto"}, 2}
};
bake_test_param MemberTarget_params[] = {
    {"cache_kind", (char*[]){"default", "auto"}, 2}
};

static bake_test_suite suites[] = {
    {
        "Validator",
        NULL,
        NULL,
        92,
        Validator_testcases
    },
    {
        "Parser",
        NULL,
        NULL,
        238,
        Parser_testcases
    },
    {
        "Basic",
        Basic_setup,
        NULL,
        165,
        Basic_testcases,
        1,
        Basic_params
    },
    {
        "Plan",
        NULL,
        NULL,
        52,
        Plan_testcases
    },
    {
        "Variables",
        Variables_setup,
        NULL,
        164,
        Variables_testcases,
        1,
        Variables_params
    },
    {
        "Operators",
        Operators_setup,
        NULL,
        120,
        Operators_testcases,
        1,
        Operators_params
    },
    {
        "Transitive",
        NULL,
        NULL,
        66,
        Transitive_testcases
    },
    {
        "ComponentInheritance",
        NULL,
        NULL,
        31,
        ComponentInheritance_testcases
    },
    {
        "Recycled",
        Recycled_setup,
        NULL,
        6,
        Recycled_testcases,
        1,
        Recycled_params
    },
    {
        "BuiltinPredicates",
        NULL,
        NULL,
        75,
        BuiltinPredicates_testcases
    },
    {
        "Scopes",
        NULL,
        NULL,
        10,
        Scopes_testcases
    },
    {
        "Traversal",
        Traversal_setup,
        NULL,
        98,
        Traversal_testcases,
        1,
        Traversal_params
    },
    {
        "Cascade",
        NULL,
        NULL,
        24,
        Cascade_testcases
    },
    {
        "Cached",
        NULL,
        NULL,
        86,
        Cached_testcases
    },
    {
        "ChangeDetection",
        NULL,
        NULL,
        32,
        ChangeDetection_testcases
    },
    {
        "GroupBy",
        NULL,
        NULL,
        12,
        GroupBy_testcases
    },
    {
        "MemberTarget",
        MemberTarget_setup,
        NULL,
        48,
        MemberTarget_testcases,
        1,
        MemberTarget_params
    },
    {
        "Toggle",
        NULL,
        NULL,
        1,
        Toggle_testcases
    }
};

int main(int argc, char *argv[]) {
    return bake_test_run("query", argc, argv, suites, 18);
}
