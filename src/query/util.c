 /**
 * @file query/util.c
 * @brief Query utilities.
 */

#include "../private_api.h"

ecs_query_lbl_t flecs_itolbl(int64_t val) {
    return flecs_ito(int16_t, val);
}

ecs_var_id_t flecs_itovar(int64_t val) {
    return flecs_ito(uint8_t, val);
}

ecs_var_id_t flecs_utovar(uint64_t val) {
    return flecs_uto(uint8_t, val);
}

bool flecs_term_is_builtin_pred(
    ecs_term_t *term)
{
    if (term->first.id & EcsIsEntity) {
        ecs_entity_t id = ECS_TERM_REF_ID(&term->first);
        if (id == EcsPredEq || id == EcsPredMatch || id == EcsPredLookup) {
            return true;
        }
    }
    return false;
}

const char* flecs_term_ref_var_name(
    ecs_term_ref_t *ref)
{
    if (!(ref->id & EcsIsVariable)) {
        return NULL;
    }

    if (ECS_TERM_REF_ID(ref) == EcsThis) {
        return EcsThisName;
    }

    return ref->name;
}

bool flecs_term_ref_is_wildcard(
    ecs_term_ref_t *ref)
{
    if ((ref->id & EcsIsVariable) && 
        ((ECS_TERM_REF_ID(ref) == EcsWildcard) || (ECS_TERM_REF_ID(ref) == EcsAny))) 
    {
        return true;
    }
    return false;
}

bool flecs_term_is_fixed_id(
    ecs_query_t *q,
    ecs_term_t *term)
{
    /* Transitive/inherited terms have variable ids */
    if (term->flags & (EcsTermTransitive|EcsTermIdInherited)) {
        return false;
    }

    /* Or terms can match different ids */
    if (term->oper == EcsOr) {
        return false;
    }
    if ((term != q->terms) && term[-1].oper == EcsOr) {
        return false;
    }

    /* Wildcards can assume different ids */
    if (ecs_id_is_wildcard(term->id)) {
        return false;
    }

    /* Any terms can have fixed ids, but they require special handling */
    if (term->flags & (EcsTermMatchAny|EcsTermMatchAnySrc)) {
        return false;
    }

    /* First terms that are Not or Optional require special handling */
    if (term->oper == EcsNot || term->oper == EcsOptional) {
        if (term == q->terms) {
            return false;
        }
    }

    return true;
}

bool flecs_term_is_or(
    const ecs_query_t *q,
    const ecs_term_t *term)
{
    bool first_term = term == q->terms;
    return (term->oper == EcsOr) || (!first_term && term[-1].oper == EcsOr);
}

ecs_flags16_t flecs_query_ref_flags(
    ecs_flags16_t flags,
    ecs_flags16_t kind)
{
    return (flags >> kind) & (EcsRuleIsVar | EcsRuleIsEntity);
}

bool flecs_query_is_written(
    ecs_var_id_t var_id,
    uint64_t written)
{
    if (var_id == EcsVarNone) {
        return true;
    }

    ecs_assert(var_id < EcsRuleMaxVarCount, ECS_INTERNAL_ERROR, NULL);
    return (written & (1ull << var_id)) != 0;
}

void flecs_query_write(
    ecs_var_id_t var_id,
    uint64_t *written)
{
    ecs_assert(var_id < EcsRuleMaxVarCount, ECS_INTERNAL_ERROR, NULL);
    *written |= (1ull << var_id);
}

void flecs_query_write_ctx(
    ecs_var_id_t var_id,
    ecs_query_compile_ctx_t *ctx,
    bool cond_write)
{
    bool is_written = flecs_query_is_written(var_id, ctx->written);
    flecs_query_write(var_id, &ctx->written);
    if (!is_written) {
        if (cond_write) {
            flecs_query_write(var_id, &ctx->cond_written);
        }
    }
}

bool flecs_ref_is_written(
    const ecs_query_op_t *op,
    const ecs_query_ref_t *ref,
    ecs_flags16_t kind,
    uint64_t written)
{
    ecs_flags16_t flags = flecs_query_ref_flags(op->flags, kind);
    if (flags & EcsRuleIsEntity) {
        ecs_assert(!(flags & EcsRuleIsVar), ECS_INTERNAL_ERROR, NULL);
        if (ref->entity) {
            return true;
        }
    } else if (flags & EcsRuleIsVar) {
        return flecs_query_is_written(ref->var, written);
    }
    return false;
}

ecs_allocator_t* flecs_query_get_allocator(
    const ecs_iter_t *it)
{
    ecs_world_t *world = it->world;
    if (ecs_poly_is(world, ecs_world_t)) {
        return &world->allocator;
    } else {
        ecs_assert(ecs_poly_is(world, ecs_stage_t), ECS_INTERNAL_ERROR, NULL);
        return &((ecs_stage_t*)world)->allocator;
    }
}

const char* flecs_query_op_str(
    uint16_t kind)
{
    switch(kind) {
    case EcsRuleAnd:           return "and       ";
    case EcsRuleAndId:         return "andid     ";
    case EcsRuleAndAny:        return "andany    ";
    case EcsRuleTriv:          return "triv      ";
    case EcsRuleTrivData:      return "trivpop   ";
    case EcsRuleTrivWildcard:  return "trivwc    ";
    case EcsRuleCache:         return "cache     ";
    case EcsRuleCacheData:     return "cachepop  ";
    case EcsRuleIsCache:       return "xcache    ";
    case EcsRuleIsCacheData:   return "xcachepop ";
    case EcsRuleSelectAny:     return "any       ";
    case EcsRuleUp:            return "up        ";
    case EcsRuleUpId:          return "upid      ";
    case EcsRuleSelfUp:        return "selfup    ";
    case EcsRuleSelfUpId:      return "selfupid  ";
    case EcsRuleWith:          return "with      ";
    case EcsRuleTrav:          return "trav      ";
    case EcsRuleAndFrom:       return "andfrom   ";
    case EcsRuleOrFrom:        return "orfrom    ";
    case EcsRuleNotFrom:       return "notfrom   ";
    case EcsRuleIdsRight:      return "idsr      ";
    case EcsRuleIdsLeft:       return "idsl      ";
    case EcsRuleEach:          return "each      ";
    case EcsRuleStore:         return "store     ";
    case EcsRuleReset:         return "reset     ";
    case EcsRuleOr:            return "or        ";
    case EcsRuleOptional:      return "option    ";
    case EcsRuleIf:            return "if        ";
    case EcsRuleEnd:           return "end       ";
    case EcsRuleNot:           return "not       ";
    case EcsRulePredEq:        return "eq        ";
    case EcsRulePredNeq:       return "neq       ";
    case EcsRulePredEqName:    return "eq_nm     ";
    case EcsRulePredNeqName:   return "neq_nm    ";
    case EcsRulePredEqMatch:   return "eq_m      ";
    case EcsRulePredNeqMatch:  return "neq_m     ";
    case EcsRuleMemberEq:      return "membereq  ";
    case EcsRuleLookup:        return "lookup    ";
    case EcsRuleSetVars:       return "setvars   ";
    case EcsRuleSetThis:       return "setthis   ";
    case EcsRuleSetFixed:      return "setfix    ";
    case EcsRuleSetIds:        return "setids    ";
    case EcsRuleSetId:         return "setid     ";
    case EcsRuleContain:       return "contain   ";
    case EcsRulePairEq:        return "pair_eq   ";
    case EcsRulePopulate:      return "pop       ";
    case EcsRulePopulateSelf:  return "popself   ";
    case EcsRuleYield:         return "yield     ";
    case EcsRuleNothing:       return "nothing   ";
    default:                   return "!invalid  ";
    }
}

static
int32_t flecs_query_op_ref_str(
    const ecs_query_impl_t *rule,
    ecs_query_ref_t *ref,
    ecs_flags16_t flags,
    ecs_strbuf_t *buf)
{
    int32_t color_chars = 0;
    if (flags & EcsRuleIsVar) {
        ecs_assert(ref->var < rule->var_count, ECS_INTERNAL_ERROR, NULL);
        ecs_query_var_t *var = &rule->vars[ref->var];
        ecs_strbuf_appendlit(buf, "#[green]$#[reset]");
        if (var->kind == EcsVarTable) {
            ecs_strbuf_appendch(buf, '[');
        }
        ecs_strbuf_appendlit(buf, "#[green]");
        if (var->name) {
            ecs_strbuf_appendstr(buf, var->name);
        } else {
            if (var->id) {
#ifdef FLECS_DEBUG
                if (var->label) {
                    ecs_strbuf_appendstr(buf, var->label);
                    ecs_strbuf_appendch(buf, '\'');
                }
#endif
                ecs_strbuf_append(buf, "%d", var->id);
            } else {
                ecs_strbuf_appendlit(buf, "this");
            }
        }
        ecs_strbuf_appendlit(buf, "#[reset]");
        if (var->kind == EcsVarTable) {
            ecs_strbuf_appendch(buf, ']');
        }
        color_chars = ecs_os_strlen("#[green]#[reset]#[green]#[reset]");
    } else if (flags & EcsRuleIsEntity) {
        char *path = ecs_get_fullpath(rule->pub.world, ref->entity);
        ecs_strbuf_appendlit(buf, "#[blue]");
        ecs_strbuf_appendstr(buf, path);
        ecs_strbuf_appendlit(buf, "#[reset]");
        ecs_os_free(path);
        color_chars = ecs_os_strlen("#[blue]#[reset]");
    }
    return color_chars;
}

char* ecs_query_str_w_profile(
    const ecs_query_t *q,
    const ecs_iter_t *it)
{
    ecs_poly_assert(q, ecs_query_impl_t);
    ecs_query_impl_t *impl = flecs_query_impl(q);

    ecs_strbuf_t buf = ECS_STRBUF_INIT;
    ecs_query_op_t *ops = impl->ops;
    int32_t i, count = impl->op_count, indent = 0;
    for (i = 0; i < count; i ++) {
        ecs_query_op_t *op = &ops[i];
        ecs_flags16_t flags = op->flags;
        ecs_flags16_t src_flags = flecs_query_ref_flags(flags, EcsRuleSrc);
        ecs_flags16_t first_flags = flecs_query_ref_flags(flags, EcsRuleFirst);
        ecs_flags16_t second_flags = flecs_query_ref_flags(flags, EcsRuleSecond);

        if (it) {
#ifdef FLECS_DEBUG
            const ecs_query_iter_t *rit = &it->priv.iter.rule;
            ecs_strbuf_append(&buf, 
                "#[green]%4d -> #[red]%4d <- #[grey]  |   ",
                rit->profile[i].count[0],
                rit->profile[i].count[1]);
#endif
        }

        ecs_strbuf_append(&buf, 
            "#[normal]%2d. [#[grey]%2d#[reset], #[green]%2d#[reset]]  ", 
                i, op->prev, op->next);
        int32_t hidden_chars, start = ecs_strbuf_written(&buf);
        if (op->kind == EcsRuleEnd) {
            indent --;
        }

        ecs_strbuf_append(&buf, "%*s", indent, "");
        ecs_strbuf_appendstr(&buf, flecs_query_op_str(op->kind));
        ecs_strbuf_appendstr(&buf, " ");

        int32_t written = ecs_strbuf_written(&buf);
        for (int32_t j = 0; j < (12 - (written - start)); j ++) {
            ecs_strbuf_appendch(&buf, ' ');
        }
    
        hidden_chars = flecs_query_op_ref_str(impl, &op->src, src_flags, &buf);

        if (op->kind == EcsRuleNot || 
            op->kind == EcsRuleOr || 
            op->kind == EcsRuleOptional || 
            op->kind == EcsRuleIf) 
        {
            indent ++;
        }

        if (op->kind == EcsRulePopulate || 
            op->kind == EcsRulePopulateSelf ||
            op->kind == EcsRuleTriv ||
            op->kind == EcsRuleTrivData ||
            op->kind == EcsRuleTrivWildcard) 
        {
            ecs_flags64_t fieldset = op->src.entity;
            int32_t f;

            ecs_strbuf_list_push(&buf, "[", ",");
            for (f = 0; f < q->field_count; f ++) {
                if (fieldset & (1llu << f)) {
                    ecs_strbuf_list_append(&buf, "%d", f);
                }
            }
            ecs_strbuf_list_pop(&buf, "]");
        }

        if (!first_flags && !second_flags) {
            ecs_strbuf_appendstr(&buf, "\n");
            continue;
        }

        written = ecs_strbuf_written(&buf) - hidden_chars;
        for (int32_t j = 0; j < (30 - (written - start)); j ++) {
            ecs_strbuf_appendch(&buf, ' ');
        }

        if (!first_flags && !second_flags) {
            ecs_strbuf_appendstr(&buf, "\n");
            continue;
        }

        ecs_strbuf_appendstr(&buf, "(");
        flecs_query_op_ref_str(impl, &op->first, first_flags, &buf);

        if (second_flags) {
            ecs_strbuf_appendstr(&buf, ", ");
            flecs_query_op_ref_str(impl, &op->second, second_flags, &buf);
        } else {
            switch (op->kind) {
            case EcsRulePredEqName:
            case EcsRulePredNeqName:
            case EcsRulePredEqMatch:
            case EcsRulePredNeqMatch: {
                int8_t term_index = op->term_index;
                ecs_strbuf_appendstr(&buf, ", #[yellow]\"");
                ecs_strbuf_appendstr(&buf, q->terms[term_index].second.name);
                ecs_strbuf_appendstr(&buf, "\"#[reset]");
                break;
            }
            case EcsRuleLookup: {
                ecs_var_id_t src_id = op->src.var;
                ecs_strbuf_appendstr(&buf, ", #[yellow]\"");
                ecs_strbuf_appendstr(&buf, impl->vars[src_id].lookup);
                ecs_strbuf_appendstr(&buf, "\"#[reset]");
                break;
            }
            default:
                break;
            }
        }

        ecs_strbuf_appendch(&buf, ')');

        ecs_strbuf_appendch(&buf, '\n');
    }

#ifdef FLECS_LOG    
    char *str = ecs_strbuf_get(&buf);
    flecs_colorize_buf(str, ecs_os_api.flags_ & EcsOsApiLogWithColors, &buf);
    ecs_os_free(str);
#endif
    return ecs_strbuf_get(&buf);
}

char* ecs_query_plan(
    const ecs_query_t *q)
{
    return ecs_query_str_w_profile(q, NULL);
}

static
void flecs_query_str_add_id(
    const ecs_world_t *world,
    ecs_strbuf_t *buf,
    const ecs_term_t *term,
    const ecs_term_ref_t *ref,
    bool is_src,
    ecs_flags64_t default_traverse_flags)
{
    bool is_added = false;
    ecs_entity_t ref_id = ECS_TERM_REF_ID(ref);
    if (!is_src || ref_id != EcsThis) {
        if (ref->id & EcsIsVariable && !ecs_id_is_wildcard(ref_id)){
            ecs_strbuf_appendlit(buf, "$");
        }
        if (ref_id) {
            char *path = ecs_get_fullpath(world, ref_id);
            ecs_strbuf_appendstr(buf, path);
            ecs_os_free(path);
        } else if (ref->name) {
            ecs_strbuf_appendstr(buf, ref->name);
        } else {
            ecs_strbuf_appendlit(buf, "0");
        }
        is_added = true;
    }

    ecs_flags64_t flags = ECS_TERM_REF_FLAGS(ref);
    if (!(flags & EcsTraverseFlags)) {
        /* If flags haven't been set yet, initialize with defaults. This can
         * happen if an error is thrown while the term is being finalized */
        flags |= default_traverse_flags;
    }

    if ((flags & EcsTraverseFlags) != default_traverse_flags) {
        if (is_added) {
            ecs_strbuf_list_push(buf, ":", "|");
        } else {
            ecs_strbuf_list_push(buf, "", "|");
        }
        if (is_src) {
            if (flags & EcsSelf) {
                ecs_strbuf_list_appendstr(buf, "self");
            }

            if (flags & EcsCascade) {
                ecs_strbuf_list_appendstr(buf, "cascade");
            } else if (flags & EcsUp) {
                ecs_strbuf_list_appendstr(buf, "up");
            }

            if (flags & EcsDesc) {
                ecs_strbuf_list_appendstr(buf, "desc");
            }

            if (term->trav && (term->trav != EcsIsA)) {
                ecs_strbuf_list_push(buf, "(", "");

                char *rel_path = ecs_get_fullpath(world, term->trav);
                ecs_strbuf_appendstr(buf, rel_path);
                ecs_os_free(rel_path);

                ecs_strbuf_list_pop(buf, ")");
            }
        }

        ecs_strbuf_list_pop(buf, "");
    }
}

static
void flecs_term_str_w_strbuf(
    const ecs_world_t *world,
    const ecs_term_t *term,
    ecs_strbuf_t *buf,
    int32_t t)
{
    const ecs_term_ref_t *src = &term->src;
    const ecs_term_ref_t *first = &term->first;
    const ecs_term_ref_t *second = &term->second;

    ecs_entity_t src_id = ECS_TERM_REF_ID(src);
    ecs_entity_t first_id = ECS_TERM_REF_ID(first);

    uint64_t def_src_mask = EcsSelf|EcsUp;
    uint64_t def_first_mask = EcsSelf;
    uint64_t def_second_mask = EcsSelf;

    bool src_set = !ecs_term_match_0(term);
    bool first_set = ecs_term_ref_is_set(first);
    bool second_set = ecs_term_ref_is_set(second);

    if (first_id == EcsScopeOpen) {
        ecs_strbuf_appendlit(buf, "{");
        return;
    } else if (first_id == EcsScopeClose) {
        ecs_strbuf_appendlit(buf, "}");
        return;
    }

    if (!t || !(term[-1].oper == EcsOr)) {
        if (term->inout == EcsIn) {
            ecs_strbuf_appendlit(buf, "[in] ");
        } else if (term->inout == EcsInOut) {
            ecs_strbuf_appendlit(buf, "[inout] ");
        } else if (term->inout == EcsOut) {
            ecs_strbuf_appendlit(buf, "[out] ");
        } else if (term->inout == EcsInOutNone && term->oper != EcsNot) {
            ecs_strbuf_appendlit(buf, "[none] ");
        }
    }

    if (term->first.id & EcsIsEntity && first_id) {
        if (ecs_has_id(world, first_id, EcsDontInherit)) {
            def_src_mask = EcsSelf;
        }
    }

    if (term->oper == EcsNot) {
        ecs_strbuf_appendlit(buf, "!");
    } else if (term->oper == EcsOptional) {
        ecs_strbuf_appendlit(buf, "?");
    }

    if (!src_set) {
        flecs_query_str_add_id(world, buf, term, &term->first, false, 
            def_first_mask);
        if (!second_set) {
            ecs_strbuf_appendlit(buf, "()");
        } else {
            ecs_strbuf_appendlit(buf, "(0,");
            flecs_query_str_add_id(world, buf, term, &term->second, false, 
                def_second_mask);
            ecs_strbuf_appendlit(buf, ")");
        }
    } else if (ecs_term_match_this(term) && 
        (src->id & EcsTraverseFlags) == def_src_mask)
    {
        if (first_set) {
            if (second_set) {
                ecs_strbuf_appendlit(buf, "(");
            }
            flecs_query_str_add_id(world, buf, term, &term->first, false, 
                def_first_mask);
            if (second_set) {
                ecs_strbuf_appendlit(buf, ",");
                flecs_query_str_add_id(
                    world, buf, term, &term->second, false, def_second_mask);
                ecs_strbuf_appendlit(buf, ")");
            }
        } else if (term->id) {
            char *str = ecs_id_str(world, term->id);
            ecs_strbuf_appendstr(buf, str);
            ecs_os_free(str);
        }
    } else {
        ecs_id_t flags = term->id & ECS_ID_FLAGS_MASK;
        if (flags && !ECS_HAS_ID_FLAG(flags, PAIR)) {
            ecs_strbuf_appendstr(buf, ecs_id_flag_str(flags));
            ecs_strbuf_appendch(buf, '|');
        }

        flecs_query_str_add_id(world, buf, term, &term->first, false, 
            def_first_mask);
        ecs_strbuf_appendlit(buf, "(");
        if (term->src.id & EcsIsEntity && src_id == first_id) {
            ecs_strbuf_appendlit(buf, "$");
        } else {
            flecs_query_str_add_id(world, buf, term, &term->src, true, 
                def_src_mask);
        }
        if (second_set) {
            ecs_strbuf_appendlit(buf, ",");
            flecs_query_str_add_id(world, buf, term, &term->second, false, 
                def_second_mask);
        }
        ecs_strbuf_appendlit(buf, ")");
    }
}

char* ecs_term_str(
    const ecs_world_t *world,
    const ecs_term_t *term)
{
    ecs_strbuf_t buf = ECS_STRBUF_INIT;
    flecs_term_str_w_strbuf(world, term, &buf, 0);
    return ecs_strbuf_get(&buf);
}

char* flecs_query_str(
    const ecs_world_t *world,
    const ecs_query_t *filter,
    const ecs_query_validator_ctx_t *ctx,
    int32_t *term_start_out)
{
    ecs_check(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_check(filter != NULL, ECS_INVALID_PARAMETER, NULL);

    ecs_strbuf_t buf = ECS_STRBUF_INIT;
    const ecs_term_t *terms = filter->terms;
    int32_t i, count = filter->term_count;

    for (i = 0; i < count; i ++) {
        const ecs_term_t *term = &terms[i];

        if (term_start_out && ctx) {
            if (ctx->term_index == i) {
                term_start_out[0] = ecs_strbuf_written(&buf);
                if (i) {
                    term_start_out[0] += 2; /* whitespace  + , */
                }
            }
        }

        flecs_term_str_w_strbuf(world, term, &buf, i);

        if (i != (count - 1)) {
            if (term->oper == EcsOr) {
                ecs_strbuf_appendlit(&buf, " || ");
            } else {
                if (ECS_TERM_REF_ID(&term->first) != EcsScopeOpen) {
                    if (ECS_TERM_REF_ID(&term[1].first) != EcsScopeClose) {
                        ecs_strbuf_appendlit(&buf, ", ");
                    }
                }
            }
        }
    }

    return ecs_strbuf_get(&buf);
error:
    return NULL;
}

char* ecs_query_str(
    const ecs_query_t *q)
{
    return flecs_query_str(q->world, q, NULL, NULL);
}

const char* ecs_query_parse_vars(
    ecs_query_t *q,
    ecs_iter_t *it,
    const char *expr)
{
    ecs_poly_assert(q, ecs_query_impl_t);

    ecs_check(it != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_check(expr != NULL, ECS_INVALID_PARAMETER, NULL)
    char token[ECS_MAX_TOKEN_SIZE];
    const char *ptr = expr;
    bool paren = false;

    const char *name = NULL;
    if (q->entity) {
        name = ecs_get_name(q->world, q->entity);
    }

    ptr = ecs_parse_ws_eol(ptr);
    if (!ptr[0]) {
        return ptr;
    }

    if (ptr[0] == '(') {
        paren = true;
        ptr = ecs_parse_ws_eol(ptr + 1);
        if (ptr[0] == ')') {
            return ptr + 1;
        }
    }

    do {
        ptr = ecs_parse_ws_eol(ptr);
        ptr = ecs_parse_identifier(name, expr, ptr, token);
        if (!ptr) {
            return NULL;
        }

        int var = ecs_query_find_var(q, token);
        if (var == -1) {
            ecs_parser_error(name, expr, (ptr - expr), 
                "unknown variable '%s'", token);
            return NULL;
        }

        ptr = ecs_parse_ws_eol(ptr);
        if (ptr[0] != ':') {
            ecs_parser_error(name, expr, (ptr - expr), 
                "missing ':'");
            return NULL;
        }

        ptr = ecs_parse_ws_eol(ptr + 1);
        ptr = ecs_parse_identifier(name, expr, ptr, token);
        if (!ptr) {
            return NULL;
        }

        ecs_entity_t val = ecs_lookup_fullpath(q->world, token);
        if (!val) {
            ecs_parser_error(name, expr, (ptr - expr), 
                "unresolved entity '%s'", token);
            return NULL;
        }

        ecs_iter_set_var(it, var, val);

        ptr = ecs_parse_ws_eol(ptr);
        if (ptr[0] == ')') {
            if (!paren) {
                ecs_parser_error(name, expr, (ptr - expr), 
                    "unexpected closing parenthesis");
                return NULL;
            }

            ptr ++;
            break;
        } else if (ptr[0] == ',') {
            ptr ++;
        } else if (!ptr[0]) {
            if (paren) {
                ecs_parser_error(name, expr, (ptr - expr), 
                    "missing closing parenthesis");
                return NULL;
            }
            break;
        } else {
            ecs_parser_error(name, expr, (ptr - expr), 
                "expected , or end of string");
            return NULL;
        }
    } while (true);

    return ptr;
error:
    return NULL;
}

int32_t flecs_query_pivot_term(
    const ecs_world_t *world,
    const ecs_query_t *filter)
{
    ecs_check(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_check(filter != NULL, ECS_INVALID_PARAMETER, NULL);

    const ecs_term_t *terms = filter->terms;
    int32_t i, term_count = filter->term_count;
    int32_t pivot_term = -1, min_count = -1, self_pivot_term = -1;

    for (i = 0; i < term_count; i ++) {
        const ecs_term_t *term = &terms[i];
        ecs_id_t id = term->id;

        if ((term->oper != EcsAnd) || (i && (term[-1].oper == EcsOr))) {
            continue;
        }

        if (!ecs_term_match_this(term)) {
            continue;
        }

        ecs_id_record_t *idr = flecs_id_record_get(world, id);
        if (!idr) {
            /* If one of the terms does not match with any data, iterator 
             * should not return anything */
            return -2; /* -2 indicates filter doesn't match anything */
        }

        int32_t table_count = flecs_table_cache_count(&idr->cache);
        if (min_count == -1 || table_count < min_count) {
            min_count = table_count;
            pivot_term = i;
            if ((term->src.id & EcsTraverseFlags) == EcsSelf) {
                self_pivot_term = i;
            }
        }
    }

    if (self_pivot_term != -1) {
        pivot_term = self_pivot_term;
    }

    return pivot_term;
error:
    return -2;
}

void flecs_query_apply_iter_flags(
    ecs_iter_t *it,
    const ecs_query_t *filter)
{
    ECS_BIT_COND(it->flags, EcsIterIsInstanced, 
        ECS_BIT_IS_SET(filter->flags, EcsQueryIsInstanced));
    ECS_BIT_COND(it->flags, EcsIterNoData,
        ECS_BIT_IS_SET(filter->flags, EcsQueryNoData));
    ECS_BIT_COND(it->flags, EcsIterHasCondSet, 
        ECS_BIT_IS_SET(filter->flags, EcsQueryHasCondSet));
}
