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
#include "../../../logger.h"
#include "../../../yaml/yaml-cpp/yaml.h"


__CONFIG_BEGIN__

// TESTME: LoggerComponent
// TODO: docs for 'LoggerComponent'
class YAMLLoggerComponent : public AbstractComponent<YAML::Node>
{
public:
	explicit YAMLLoggerComponent(
		std::string base_directory, std::shared_ptr<log::ILogger>& logger
	) : base_directory(std::move(base_directory)), logger(logger)
	{
	}

	void initialize(const YAML::Node& logger) const override;

	void overwrite(const YAML::Node& from_component, YAML::Node& to_component) const override;

protected:
	std::string base_directory;
	std::shared_ptr<log::ILogger>& logger;

	virtual void initialize_levels(log::Config& logger_config, const YAML::Node& levels) const;

	virtual void initialize_out_files(log::Config& config, const YAML::Node& files, const std::string& base_dir) const;

	virtual void initialize_out(log::Config& config, const YAML::Node& out, const std::string& base_dir) const;

	virtual void overwrite_out(const YAML::Node& from_out, YAML::Node& to_out) const;
};

__CONFIG_END__
