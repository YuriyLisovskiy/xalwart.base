/**
 * config/components/yaml/logger.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Purpose: TODO
 */

#pragma once

// C++ libraries.
#include <string>

// Module definitions.
#include "../../_def_.h"

// Base libraries.
#include "../../component.h"
#include "../../../interfaces/base.h"
#include "../../../vendor/yaml/yaml-cpp/yaml.h"


__CONFIG_BEGIN__

// TESTME: LoggerComponent
// TODO: docs for 'LoggerComponent'
class YAMLLoggerComponent : public AbstractComponent<YAML::Node>
{
public:
	explicit YAMLLoggerComponent(
		std::string base_directory, std::shared_ptr<ILogger>& logger
	) : base_directory(std::move(base_directory)), logger(logger)
	{
	}

	void initialize(const YAML::Node& logger) const override;

	void overwrite(const YAML::Node& from_component, YAML::Node& to_component) const override;

protected:
	std::string base_directory;
	std::shared_ptr<ILogger>& logger;
};

__CONFIG_END__
