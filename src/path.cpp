#include "./path.h"

// STL libraries.
#include <filesystem>
#include <random>

// Base libraries.
#include "./string_utils.h"
#include "./datetime.h"


__PATH_BEGIN__

std::pair<std::string, std::string> prefix_and_suffix(const std::string& pattern)
{
	if (str::contains(pattern, path_sep))
	{
		throw ArgumentError("pattern contains path separator", _ERROR_DETAILS_);
	}

	std::string prefix, suffix;
	auto pos = pattern.find_last_of('*');
	if (pos != std::string::npos)
	{
		prefix = pattern.substr(0, pos);
		suffix = pattern.substr(pos + 1);
	}
	else
	{
		prefix = pattern;
	}

	return {prefix, suffix};
}

int reseed()
{
	return (int)(dt::Datetime::utc_now().timestamp() * 1000 + ::getpid());
}

std::string next_random()
{
	auto r = std::mt19937(reseed())();
	r = r * 1664525 + 1013904223;
	return std::to_string((uint32_t)(1e9 + (uint32_t)r % (uint32_t)1e9)).substr(1);
}

std::unique_ptr<File> temp_file(std::string dir, const std::string& pattern, bool is_binary)
{
	if (dir.empty())
	{
		dir = std::filesystem::temp_directory_path().string();
	}

	auto [prefix, suffix] = prefix_and_suffix(pattern);
	std::unique_ptr<File> file = nullptr;
	for (size_t i = 0; i < 100000; i++)
	{
		auto file_path = join(dir, prefix.append(next_random()).append(suffix));
		if (std::filesystem::exists(file_path))
		{
			continue;
		}

		file = std::make_unique<File>(
			file_path, is_binary ? File::OpenMode::ReadWriteBinary : File::OpenMode::ReadWrite
		);
		break;
	}

	return file;
}

__PATH_END__
