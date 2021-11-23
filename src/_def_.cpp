/**
 * _def_.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include "./_def_.h"

// C++ libraries.
#include <memory>
#include <ostream>

#ifndef _MSC_VER
#include <cxxabi.h>
#endif

// Base libraries.
#include "./string_utils.h"


__MAIN_NAMESPACE_BEGIN__

int compare_numbers(uint l, uint r)
{
	if (l == r)
	{
		return 0;
	}

	if (l > r)
	{
		return 1;
	}

	return -1;
}

int compare_versions(const Version& l, const Version& r)
{
	auto ret = compare_numbers(l.major, r.major);
	if (ret == 0)
	{
		ret = compare_numbers(l.minor, r.minor);
		if (ret == 0)
		{
			ret = compare_numbers(l.patch, r.patch);
		}
	}

	return ret;
}

Version::Version(const std::string& v)
{
	auto parts = str::split(v, '.');
	this->major = std::stoi(parts[0]);
	this->minor = std::stoi(parts[1]);
	this->patch = std::stoi(parts[2]);
}

Version::Version(uint major, uint minor, uint patch)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
}

std::string Version::to_string() const
{
	return std::to_string(this->major) + "." + std::to_string(this->minor) + "." + std::to_string(this->patch);
}

bool Version::operator< (const Version& other) const
{
	return compare_versions(*this, other) == -1;
}

bool Version::operator<= (const Version& other) const
{
	auto ret = compare_versions(*this, other);
	return ret == 0 || ret == -1;
}

bool Version::operator> (const Version& other) const
{
	return compare_versions(*this, other) == 1;
}

bool Version::operator>= (const Version& other) const
{
	auto ret = compare_versions(*this, other);
	return ret == 0 || ret == 1;
}

bool Version::operator== (const Version& other) const
{
	return compare_versions(*this, other) == 0;
}

bool Version::operator!= (const Version& other) const
{
	return compare_versions(*this, other) != 0;
}

bool Version::operator< (const char* v) const
{
	return compare_versions(*this, Version(v)) == -1;
}

bool Version::operator<= (const char* v) const
{
	auto ret = compare_versions(*this, Version(v));
	return ret == 0 || ret == -1;
}

bool Version::operator> (const char* v) const
{
	return compare_versions(*this, Version(v)) == 1;
}

bool Version::operator>= (const char* v) const
{
	auto ret = compare_versions(*this, Version(v));
	return ret == 0 || ret == 1;
}

bool Version::operator== (const char* v) const
{
	return compare_versions(*this, Version(v)) == 0;
}

bool Version::operator!= (const char* v) const
{
	return compare_versions(*this, Version(v)) != 0;
}

std::ostream& operator<< (std::ostream& stream, const Version& v)
{
	stream << v.major << "." << v.minor << "." << v.patch;
	return stream;
}

// Statuses:
// 0 - operation succeeded
// 1 - a memory allocation failure occurred
// 2 - mangled_name is not a valid name under the C++ ABI mangling rules
// 3 - one of the arguments is invalid
std::string demangle(const char* name)
{
#ifdef _MSC_VER
	return str::ltrim(name, "class");
#else
	int status = -4;
	std::unique_ptr<char, void(*)(void*)> res {
		abi::__cxa_demangle(name, nullptr, nullptr, &status), std::free
	};

	return status == 0 ? res.get() : name;
#endif
}

__MAIN_NAMESPACE_END__
