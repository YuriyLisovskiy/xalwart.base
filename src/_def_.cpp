/**
 * _def_.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include "./_def_.h"

// C++ libraries.
#include <ostream>

// Base libraries.
#include "./string_utils.h"


__MAIN_NAMESPACE_BEGIN__

namespace base::v
{
version_t::version_t(const std::string& v)
{
	auto parts = str::split(v, '.');
	this->major = std::stoi(parts[0]);
	this->minor = std::stoi(parts[1]);
	this->patch = std::stoi(parts[2]);
}

version_t::version_t(uint major, uint minor, uint patch)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
}

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

int compare_versions(const version_t& l, const version_t& r)
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

bool version_t::operator< (const version_t& other) const
{
	return compare_versions(*this, other) == -1;
}

bool version_t::operator<= (const version_t& other) const
{
	auto ret = compare_versions(*this, other);
	return ret == 0 || ret == -1;
}

bool version_t::operator> (const version_t& other) const
{
	return compare_versions(*this, other) == 1;
}

bool version_t::operator>= (const version_t& other) const
{
	auto ret = compare_versions(*this, other);
	return ret == 0 || ret == 1;
}

bool version_t::operator== (const version_t& other) const
{
	return compare_versions(*this, other) == 0;
}

bool version_t::operator!= (const version_t& other) const
{
	return compare_versions(*this, other) != 1;
}

bool version_t::operator< (const char* v) const
{
	return compare_versions(*this, version_t(v)) == -1;
}

bool version_t::operator<= (const char* v) const
{
	auto ret = compare_versions(*this, version_t(v));
	return ret == 0 || ret == -1;
}

bool version_t::operator> (const char* v) const
{
	return compare_versions(*this, version_t(v)) == 1;
}

bool version_t::operator>= (const char* v) const
{
	auto ret = compare_versions(*this, version_t(v));
	return ret == 0 || ret == 1;
}

bool version_t::operator== (const char* v) const
{
	return compare_versions(*this, version_t(v)) == 0;
}

bool version_t::operator!= (const char* v) const
{
	return compare_versions(*this, version_t(v)) != 1;
}

std::ostream& operator<< (std::ostream& stream, const version_t& v)
{
	stream << v.major << "." << v.minor << "." << v.patch;
	return stream;
}
}

__MAIN_NAMESPACE_END__
