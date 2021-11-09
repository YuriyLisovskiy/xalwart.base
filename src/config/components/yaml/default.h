/**
 * config/components/yaml/default.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Purpose: TODO
 */

#pragma once

// C++ libraries.
#include <memory>
#include <functional>

// Module definitions.
#include "../../_def_.h"

// Base libraries.
#include "../../component.h"
#include "../../../exceptions.h"
#include "../../../vendor/yaml/yaml-cpp/yaml.h"


__CONFIG_BEGIN__

using YAMLComponent = AbstractComponent<YAML::Node>;

// TESTME: YAMLMapComponent
// TODO: docs for 'YAMLMapComponent'
class YAMLMapComponent : public YAMLComponent
{
public:
	explicit inline YAMLMapComponent(bool overwrite_all=false) : overwrite_all(overwrite_all)
	{
	}

	inline void initialize(const YAML::Node& node) const override
	{
		if (node && node.IsMap())
		{
			for (const auto& component : this->components)
			{
				component.second->initialize(node[component.first]);
			}
		}
	}

	void overwrite(const YAML::Node& from_node, YAML::Node& to_node) const override;

	inline void register_component(std::string name, std::unique_ptr<YAMLComponent> component)
	{
		this->components.template emplace_back(std::move(name), std::move(component));
	}

protected:
	bool overwrite_all;

	std::list<std::pair<std::string, std::unique_ptr<YAMLComponent>>> components;
};

// TESTME: YAMLSequenceComponent
// TODO: docs for 'YAMLSequenceComponent'
class YAMLSequenceComponent : public YAMLComponent
{
public:
	explicit inline YAMLSequenceComponent(
		std::function<void(const YAML::Node& /* sequence_node */)> handler
	) : handler(std::move(handler))
	{
		if (!this->handler)
		{
			throw NullPointerException("handler of sequence component should be instantiated", _ERROR_DETAILS_);
		}
	}

	void initialize(const YAML::Node& node) const override;

	inline void overwrite(const YAML::Node& from_node, YAML::Node& to_node) const override
	{
		if (from_node && from_node.IsSequence())
		{
			to_node = from_node;
		}
	}

protected:
	std::function<void(const YAML::Node& /* sequence_node */)> handler;
};

// TESTME: YAMLScalarComponent
// TODO: docs for 'YAMLScalarComponent'
class YAMLScalarComponent : public YAMLComponent
{
public:
	explicit inline YAMLScalarComponent(
		std::function<void(const YAML::Node& /* scalar_node */)> handler
	) : handler(std::move(handler))
	{
		if (!this->handler)
		{
			throw NullPointerException("scalar handler should not be nullptr", _ERROR_DETAILS_);
		}
	}

	template <typename ScalarType>
	explicit inline YAMLScalarComponent(ScalarType& value)
	{
		this->handler = [&](const YAML::Node& node) mutable -> void
		{
			value = node.as<ScalarType>(value);
		};
	}

	inline void initialize(const YAML::Node& node) const override
	{
		if (node && node.IsScalar())
		{
			this->handler(node);
		}
	}

	inline void overwrite(const YAML::Node& from_node, YAML::Node& to_node) const override
	{
		if (from_node && from_node.IsScalar())
		{
			to_node = from_node;
		}
	}

protected:
	std::function<void(const YAML::Node& /* scalar_node */)> handler;
};

__CONFIG_END__
