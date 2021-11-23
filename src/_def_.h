/**
 * _def_.h
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 *
 * Definitions of the main module.
 */

#pragma once

// C++ libraries.
#include <string>
#include <iterator>

// Base libraries.
#include "./exceptions.h"

// xw
#define __MAIN_NAMESPACE_BEGIN__ namespace xw {
#define __MAIN_NAMESPACE_END__ }

// xw::orm
#define __ORM_BEGIN__ __MAIN_NAMESPACE_BEGIN__ namespace orm {
#define __ORM_END__ } __MAIN_NAMESPACE_END__

// xw::render
#define __RENDER_BEGIN__ __MAIN_NAMESPACE_BEGIN__ namespace render {
#define __RENDER_END__ } __MAIN_NAMESPACE_END__

// xw::server
#define __SERVER_BEGIN__ __MAIN_NAMESPACE_BEGIN__ namespace server {
#define __SERVER_END__ } __MAIN_NAMESPACE_END__

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

using uint = unsigned int;


__MAIN_NAMESPACE_BEGIN__

template <typename T>
using iterator_v_type = typename std::iterator_traits<T>::value_type;

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
static inline const auto version = Version("0.0.0");
}

// Converts type name to full name.
//
// `name`: result of 'typeid(...).name()' call.
//
// Returns full name.
extern std::string demangle(const char* name);

template <typename T>
inline T* require_non_null(T* p, const char* message, int line=0, const char* function="", const char* file="")
{
	if (p == nullptr)
	{
		throw NullPointerException(message, line, function, file);
	}

	return p;
}

template <typename T>
inline T* require_non_null(T* p, const std::string& message, int line=0, const char* function="", const char* file="")
{
	return require_non_null(p, message.c_str(), line, function, file);
}

template <typename T>
inline T* require_non_null(T* p, int line=0, const char* function="", const char* file="")
{
	return require_non_null<T>(
		p, ("pointer to object of type '" + demangle(typeid(T).name()) + "' is nullptr").c_str(),
		line, function, file
	);
}

template <class T>
concept integral = std::is_integral_v<T>;

__MAIN_NAMESPACE_END__
