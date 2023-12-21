/**
 * @file addons/cpp/mixins/filter/decl.hpp
 * @brief Query declarations.
 */

#pragma once

namespace flecs {

/**
 * @defgroup cpp_core_filters Querys
 * @brief Querys are cheaper to create, but slower to iterate than flecs::query.
 * 
 * \ingroup cpp_core
 * @{
 */

struct filter_base;

template<typename ... Components>
struct filter;

template<typename ... Components>
struct filter_builder;

/** @} */

}
