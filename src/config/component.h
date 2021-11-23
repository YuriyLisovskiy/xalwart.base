/**
 * config/component.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Purpose: TODO
 */

#pragma once

// Module definitions.
#include "./_def_.h"


__CONFIG_BEGIN__

// TODO: docs for 'ComponentLoader'
// Load the single component from configuration file.
//
// Example:
//  static:
//    url: 'https://example.com/static'
//    root: 'static/'
//
// `settings->STATIC` structure can be initialized with YAML the component shown above.
template <typename NodeType>
class AbstractComponent
{
public:
	virtual ~AbstractComponent() = default;

	// Initializes setting from final configuration.
	virtual void initialize(const NodeType& node) const = 0;

	// Overwrites setting from `from_node` to `to_node`.
	virtual void overwrite(const NodeType& from_node, NodeType& to_node) const = 0;
};

__CONFIG_END__
