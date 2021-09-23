/**
 * config/components/yaml/logger.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include "./logger.h"

// Base libraries.
#include "../../../path.h"


__CONFIG_BEGIN__

void YAMLLoggerComponent::initialize(const YAML::Node& node) const
{
	log::Config logger_config{};
	logger_config.enable_all_levels();
	bool use_colors = true;
	if (node && node.IsMap())
	{
		this->initialize_levels(logger_config, node["levels"]);
		this->initialize_out(logger_config, node["out"], this->base_directory);
		use_colors = node["use_colors"].as<bool>(use_colors);
	}

	logger_config.use_colors = use_colors;
	this->logger = std::make_shared<log::Logger>(logger_config);
}

void YAMLLoggerComponent::overwrite(const YAML::Node& from_component, YAML::Node& to_component) const
{
	if (!to_component)
	{
		to_component = YAML::Node(YAML::NodeType::Map);
	}

	if (from_component && from_component.IsMap())
	{
		auto from_levels = from_component["levels"];
		if (from_levels && (from_levels.IsScalar() || from_levels.IsMap()))
		{
			to_component["levels"] = from_levels;
		}

		auto to_out = to_component["out"];
		this->overwrite_out(from_component["out"], to_out);
		to_component["out"] = to_out;

		auto from_use_colors = from_component["use_colors"];
		if (from_use_colors && from_use_colors.IsScalar())
		{
			to_component["use_colors"] = from_use_colors;
		}
	}
}

void YAMLLoggerComponent::initialize_levels(log::Config& config, const YAML::Node& levels) const
{
	if (levels)
	{
		if (levels.as<std::string>("") == "*")
		{
			config.enable_all_levels();
		}
		else if (levels.IsMap())
		{
			this->initialize_level(config, levels["info"], log::Level::Info);
			this->initialize_level(config, levels["debug"], log::Level::Debug);
			this->initialize_level(config, levels["warning"], log::Level::Warning);
			this->initialize_level(config, levels["error"], log::Level::Error);
			this->initialize_level(config, levels["trace"], log::Level::Trace);
			this->initialize_level(config, levels["print"], log::Level::Print);
		}
	}
}

void YAMLLoggerComponent::initialize_level(log::Config& config, const YAML::Node& node, log::Level level) const
{
	if (node.as<bool>(config.is_enabled(level)))
	{
		config.enable(level);
	}
	else
	{
		config.disable(level);
	}
}

void YAMLLoggerComponent::initialize_out_files(
	log::Config& config, const YAML::Node& files, const std::string& base_dir
) const
{
	if (files && files.IsSequence())
	{
		for (auto it = files.begin(); it != files.end(); it++)
		{
			auto node = *it;
			if (node)
			{
				auto file_path = node.as<std::string>("");
				if (!file_path.empty())
				{
					auto full_path = path::is_absolute(file_path) ? file_path : path::join(base_dir, file_path);
					config.add_file_stream(full_path);
				}
			}
		}
	}
}

void YAMLLoggerComponent::initialize_out(log::Config& config, const YAML::Node& out, const std::string& base_dir) const
{
	if (out && out.IsMap())
	{
		if (out["console"].as<bool>(true))
		{
			config.add_console_stream();
		}

		this->initialize_out_files(config, out["files"], base_dir);
	}
	else
	{
		config.add_console_stream();
	}
}

void YAMLLoggerComponent::overwrite_out(const YAML::Node& from_out, YAML::Node& to_out) const
{
	if (!to_out)
	{
		to_out = YAML::Node(YAML::NodeType::Map);
	}

	if (from_out && from_out.IsMap())
	{
		auto from_console = from_out["console"];
		if (from_console && from_console.IsScalar())
		{
			to_out["console"] = from_console;
		}

		auto from_files = from_out["files"];
		if (from_files && from_files.IsSequence())
		{
			to_out["files"] = from_files;
		}
	}
}

__CONFIG_END__
