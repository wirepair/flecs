 /**
 * @file query/util.c
 * @brief Query utilities.
 */

#include "rules.h"

const char* flecs_rule_op_str(
    uint16_t kind)
{
    switch(kind) {
    case EcsRuleAnd:           return "and     ";
    case EcsRuleAndId:         return "andid   ";
    case EcsRuleAndAny:        return "andany  ";
    case EcsRuleTriv:          return "triv    ";
    case EcsRuleTrivData:      return "trivpop ";
    case EcsRuleTrivWildcard:  return "trivwc  ";
    case EcsRuleSelectAny:     return "any     ";
    case EcsRuleUp:            return "up      ";
    case EcsRuleUpId:          return "upid    ";
    case EcsRuleSelfUp:        return "selfup  ";
    case EcsRuleSelfUpId:      return "selfupid";
    case EcsRuleWith:          return "with    ";
    case EcsRuleTrav:          return "trav    ";
    case EcsRuleIdsRight:      return "idsr    ";
    case EcsRuleIdsLeft:       return "idsl    ";
    case EcsRuleEach:          return "each    ";
    case EcsRuleStore:         return "store   ";
    case EcsRuleReset:         return "reset   ";
    case EcsRuleOr:            return "or      ";
    case EcsRuleOptional:      return "option  ";
    case EcsRuleIf:            return "if      ";
    case EcsRuleEnd:           return "end     ";
    case EcsRuleNot:           return "not     ";
    case EcsRulePredEq:        return "eq      ";
    case EcsRulePredNeq:       return "neq     ";
    case EcsRulePredEqName:    return "eq_nm   ";
    case EcsRulePredNeqName:   return "neq_nm  ";
    case EcsRulePredEqMatch:   return "eq_m    ";
    case EcsRulePredNeqMatch:  return "neq_m   ";
    case EcsRuleLookup:        return "lookup  ";
    case EcsRuleSetVars:       return "setvars ";
    case EcsRuleSetThis:       return "setthis ";
    case EcsRuleSetFixed:      return "setfix  ";
    case EcsRuleSetIds:        return "setids  ";
    case EcsRuleSetId:         return "setid   ";
    case EcsRuleContain:       return "contain ";
    case EcsRulePairEq:        return "pair_eq ";
    case EcsRulePopulate:      return "pop     ";
    case EcsRulePopulateSelf:  return "popself ";
    case EcsRuleYield:         return "yield   ";
    case EcsRuleNothing:       return "nothing ";
    default:                   return "!invalid";
    }
}

static
int32_t flecs_rule_op_ref_str(
    const ecs_rule_t *rule,
    ecs_rule_ref_t *ref,
    ecs_flags16_t flags,
    ecs_strbuf_t *buf)
{
    int32_t color_chars = 0;
    if (flags & EcsRuleIsVar) {
        ecs_assert(ref->var < rule->var_count, ECS_INTERNAL_ERROR, NULL);
        ecs_rule_var_t *var = &rule->vars[ref->var];
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
        char *path = ecs_get_fullpath(rule->filter.world, ref->entity);
        ecs_strbuf_appendlit(buf, "#[blue]");
        ecs_strbuf_appendstr(buf, path);
        ecs_strbuf_appendlit(buf, "#[reset]");
        ecs_os_free(path);
        color_chars = ecs_os_strlen("#[blue]#[reset]");
    }
    return color_chars;
}

char* ecs_rule_str_w_profile(
    const ecs_filter_t *q,
    const ecs_iter_t *it)
{
    ecs_poly_assert(q, ecs_rule_t);
    ecs_rule_t *impl = flecs_rule(q);

    ecs_strbuf_t buf = ECS_STRBUF_INIT;
    ecs_rule_op_t *ops = impl->ops;
    int32_t i, count = impl->op_count, indent = 0;
    for (i = 0; i < count; i ++) {
        ecs_rule_op_t *op = &ops[i];
        ecs_flags16_t flags = op->flags;
        ecs_flags16_t src_flags = flecs_rule_ref_flags(flags, EcsRuleSrc);
        ecs_flags16_t first_flags = flecs_rule_ref_flags(flags, EcsRuleFirst);
        ecs_flags16_t second_flags = flecs_rule_ref_flags(flags, EcsRuleSecond);

        if (it) {
#ifdef FLECS_DEBUG
            const ecs_rule_iter_t *rit = &it->priv.iter.rule;
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
        ecs_strbuf_appendstr(&buf, flecs_rule_op_str(op->kind));
        ecs_strbuf_appendstr(&buf, " ");

        int32_t written = ecs_strbuf_written(&buf);
        for (int32_t j = 0; j < (12 - (written - start)); j ++) {
            ecs_strbuf_appendch(&buf, ' ');
        }
    
        hidden_chars = flecs_rule_op_ref_str(impl, &op->src, src_flags, &buf);

        if (op->kind == EcsRuleNot || 
            op->kind == EcsRuleOr || 
            op->kind == EcsRuleOptional || 
            op->kind == EcsRuleIf) 
        {
            indent ++;
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
        flecs_rule_op_ref_str(impl, &op->first, first_flags, &buf);

        if (second_flags) {
            ecs_strbuf_appendstr(&buf, ", ");
            flecs_rule_op_ref_str(impl, &op->second, second_flags, &buf);
        } else {
            switch (op->kind) {
            case EcsRulePredEqName:
            case EcsRulePredNeqName:
            case EcsRulePredEqMatch:
            case EcsRulePredNeqMatch: {
                int8_t term_index = op->term_index;
                ecs_strbuf_appendstr(&buf, ", #[yellow]\"");
                ecs_strbuf_appendstr(&buf, impl->filter.terms[term_index].second.name);
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

char* ecs_rule_str(
    const ecs_filter_t *q)
{
    return ecs_rule_str_w_profile(q, NULL);
}

const char* ecs_rule_parse_vars(
    ecs_filter_t *q,
    ecs_iter_t *it,
    const char *expr)
{
    ecs_poly_assert(q, ecs_rule_t);
    ecs_rule_t *impl = flecs_rule(q);

    ecs_check(it != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_check(expr != NULL, ECS_INVALID_PARAMETER, NULL)
    char token[ECS_MAX_TOKEN_SIZE];
    const char *ptr = expr;
    bool paren = false;

    const char *name = NULL;
    if (impl->filter.entity) {
        name = ecs_get_name(impl->filter.world, impl->filter.entity);
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

        int var = ecs_rule_find_var(q, token);
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
