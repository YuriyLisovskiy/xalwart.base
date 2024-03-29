/**
 * interfaces/render.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Interfaces related to rendering templates.
 */

#pragma once

// C++ libraries.
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <optional>

// Module definitions.
#include "../_def_.h"

// Base libraries.
#include "../object/object.h"


__RENDER_BEGIN__

// TODO: docs for 'IContext'
class IContext
{
public:
	using Scope = std::map<std::string, std::shared_ptr<const obj::Object>>;

	virtual ~IContext() = default;

	[[nodiscard]]
	virtual std::shared_ptr<const obj::Object> find_var(const std::string& key) const = 0;

	virtual void push_var(const std::string& key, const std::shared_ptr<const obj::Object>& val) = 0;

	virtual void push_scope(const Scope& scope) = 0;

	virtual void pop_scope() = 0;
};

// TODO: docs for 'ITemplate'
class ITemplate
{
public:
	virtual ~ITemplate() = default;

	// Renders template code using given context.
	[[nodiscard]]
	virtual std::string render(IContext* context) const = 0;
};

// TODO: docs for 'IEngine'
class IEngine
{
public:
	virtual ~IEngine() = default;

	// Return a pointer to compiled BaseTemplate object for the given template code,
	// handling template inheritance recursively.
	[[nodiscard]]
	virtual std::shared_ptr<ITemplate> from_string(const std::string& template_code) const = 0;

	// Return a pointer to compiled BaseTemplate object for the given template name,
	// handling template inheritance recursively.
	[[nodiscard]]
	virtual std::shared_ptr<ITemplate> get_template(const std::string& template_name) const = 0;

	virtual void load_libraries() = 0;

	[[nodiscard]]
	virtual std::string name() const = 0;
};

// TODO: docs for 'ILoader'
class ILoader
{
public:
	virtual ~ILoader() = default;

	[[nodiscard]]
	virtual std::shared_ptr<ITemplate> get_template(
		const std::string& template_path, const std::vector<std::string>& dirs, const IEngine* engine
	) const = 0;

	[[nodiscard]]
	virtual std::map<std::string, std::shared_ptr<ITemplate>> cache_templates(
		const std::vector<std::string>& dirs, const IEngine* engine
	) const = 0;

	[[nodiscard]]
	virtual std::string name() const = 0;
};

// TODO: docs for 'ILibrary'
class ILibrary
{
public:
	using Filter = std::function<std::shared_ptr<const obj::Object>(
		const std::shared_ptr<const obj::Object>&, const std::map<std::string, std::shared_ptr<const obj::Object>>&
	)>;

	using Argument = std::shared_ptr<const obj::Object>;

	// `var_name` is non-empty string when the result of `Function` should be
	// written to a variable and pushed to context.
	using Function = std::function<std::string(
		IContext*, const std::vector<Argument>&,
		const std::optional<std::string>& /* var_name */,
		size_t /* function_call_line */
	)>;

	virtual ~ILibrary() = default;

	[[nodiscard]]
	virtual std::map<std::string, Filter> get_filters() const = 0;

	[[nodiscard]]
	virtual std::map<std::string, Function> get_functions() const = 0;

	[[nodiscard]]
	virtual std::string name() const = 0;
};

template <typename T>
concept engine_type = std::is_base_of_v<IEngine, T>;

template <typename T>
concept library_type = std::is_base_of_v<ILibrary, T>;

template <typename T>
concept loader_type = std::is_base_of_v<ILoader, T>;

__RENDER_END__
