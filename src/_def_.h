/**
 * _def_.h
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 *
 * Definitions of the main module.
 */

#pragma once

// C++ libraries.
#include <iterator>

#ifdef _MSC_VER
#include <string>
#endif

using uint = unsigned int;

// xw
#define __MAIN_NAMESPACE_BEGIN__ namespace xw {
#define __MAIN_NAMESPACE_END__ }

__MAIN_NAMESPACE_BEGIN__

struct Version
{
	uint major;
	uint minor;
	uint patch;

	explicit Version(const std::string& v);
	Version(uint major, uint minor, uint patch);

	[[nodiscard]]
	std::string to_string() const;

	bool operator< (const Version& other) const;
	bool operator<= (const Version& other) const;
	bool operator> (const Version& other) const;
	bool operator>= (const Version& other) const;
	bool operator== (const Version& other) const;
	bool operator!= (const Version& other) const;

	bool operator< (const char* v) const;
	bool operator<= (const char* v) const;
	bool operator> (const char* v) const;
	bool operator>= (const char* v) const;
	bool operator== (const char* v) const;
	bool operator!= (const char* v) const;

	friend std::ostream& operator<< (std::ostream& stream, const Version& v);
};

namespace base::v
{
inline const auto version = Version("0.0.0");
}

__MAIN_NAMESPACE_END__

// xw::abc
#define __ABC_BEGIN__ __MAIN_NAMESPACE_BEGIN__ namespace abc {
#define __ABC_END__ } __MAIN_NAMESPACE_END__

// xw::path
#define __PATH_BEGIN__ __MAIN_NAMESPACE_BEGIN__ namespace path {
#define __PATH_END__ } __MAIN_NAMESPACE_END__

// xw::dt
#define __DATETIME_BEGIN__ __MAIN_NAMESPACE_BEGIN__ namespace dt {
#define __DATETIME_END__ } __MAIN_NAMESPACE_END__

// xw::encoding
#define __ENCODING_BEGIN__ __MAIN_NAMESPACE_BEGIN__ namespace encoding {
#define __ENCODING_END__ } __MAIN_NAMESPACE_END__

// xw::text
#define __TEXT_BEGIN__ __MAIN_NAMESPACE_BEGIN__ namespace text {
#define __TEXT_END__ } __MAIN_NAMESPACE_END__

// xw::str
#define __STR_BEGIN__ __MAIN_NAMESPACE_BEGIN__ namespace str {
#define __STR_END__ } __MAIN_NAMESPACE_END__

// xw::util
#define __UTILITY_BEGIN__ __MAIN_NAMESPACE_BEGIN__ namespace util {
#define __UTILITY_END__ } __MAIN_NAMESPACE_END__

// xw::sys
#define __SYS_BEGIN__ __MAIN_NAMESPACE_BEGIN__ namespace sys {
#define __SYS_END__ } __MAIN_NAMESPACE_END__

// xw::html
#define __HTML_BEGIN__ __MAIN_NAMESPACE_BEGIN__ namespace html {
#define __HTML_END__ } __MAIN_NAMESPACE_END__

// xw::log
#define __LOG_BEGIN__ __MAIN_NAMESPACE_BEGIN__ namespace log {
#define __LOG_END__ } __MAIN_NAMESPACE_END__

// xw::io
#define __IO_BEGIN__ __MAIN_NAMESPACE_BEGIN__ namespace io {
#define __IO_END__ } __MAIN_NAMESPACE_END__

// Required parameters for built-in logger.
#ifdef _MSC_VER
#define _ERROR_DETAILS_ __LINE__, __FUNCTION__, __FILE__
#else
#define _ERROR_DETAILS_ __LINE__, __PRETTY_FUNCTION__, __FILE__
#endif

// Declares exception's class with given base.
#define DEF_EXCEPTION_WITH_BASE(name, base, default_message, additional_namespace_name)\
class name : public base\
{\
protected:\
	name(\
		const char* message, int line, const char* function, const char* file, const char* type\
	)\
		: base(message, line, function, file, type)\
	{\
	}\
\
public:\
	explicit name(\
		const char* message = default_message,\
		int line=0, const char* function="", const char* file=""\
	) : name(\
		message, line, function, file, ("xw::" + std::string(additional_namespace_name) + std::string(#name)).c_str() \
	)\
	{\
	}\
\
	explicit name(\
		const std::string& message = default_message,\
		int line=0, const char* function="", const char* file=""\
	)\
		: name(message.c_str(), line, function, file)\
	{\
	}\
}

__MAIN_NAMESPACE_BEGIN__

template <typename T>
using iterator_v_type = typename std::iterator_traits<T>::value_type;

__MAIN_NAMESPACE_END__
