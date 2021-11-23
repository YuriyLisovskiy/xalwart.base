/**
 * settings/components/yaml/default.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include "./default.h"


__CONFIG_BEGIN__

void YAMLMapComponent::overwrite(const YAML::Node& from_node, YAML::Node& to_node) const
{
	if (this->overwrite_all && from_node.IsMap())
	{
		to_node = from_node;
		return;
	}

	if (!to_node)
	{
		to_node = YAML::Node(YAML::NodeType::Map);
	}

	if (from_node.IsMap())
	{
		for (const auto& component : this->components)
		{
			auto to_overwrite = to_node[component.first];
			component.second->overwrite(from_node[component.first], to_overwrite);
			to_node[component.first] = to_overwrite;
		}
	}
}

void YAMLSequenceComponent::initialize(const YAML::Node& node) const
{
	if (node && node.IsSequence())
	{
		for (auto it = node.begin(); it != node.end(); it++)
		{
			auto item_node = *it;
			if (item_node)
			{
				this->handler(item_node);
			}
		}
	}
}

__CONFIG_END__
