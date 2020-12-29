/**
 * _def_.h
 *
 * Copyright (c) 2019-2020 Yuriy Lisovskiy
 *
 * Purpose: core module's definitions.
 */

#pragma once


// xw
#define __MAIN_NAMESPACE_BEGIN__ namespace xw {
#define __MAIN_NAMESPACE_END__ }


// Required parameters for built-in logger.
#ifdef _MSC_VER
#define _ERROR_DETAILS_ __LINE__, __FUNCTION__, __FILE__
#else
#define _ERROR_DETAILS_ __LINE__, __PRETTY_FUNCTION__, __FILE__
#endif

#if defined(_WIN32) || defined(_WIN64)
typedef unsigned int uint;
#endif


// core
#define __CORE_BEGIN__ __MAIN_NAMESPACE_BEGIN__ namespace core {
#define __CORE_END__ } __MAIN_NAMESPACE_END__

// core::internal
#define __CORE_INTERNAL_BEGIN__ __CORE_BEGIN__ namespace internal {
#define __CORE_INTERNAL_END__ } __CORE_END__

// xw::path
#define __PATH_BEGIN__ __MAIN_NAMESPACE_BEGIN__ namespace path {
#define __PATH_END__ } __MAIN_NAMESPACE_END__

// xw::path::internal
#define __PATH_INTERNAL_BEGIN__ __PATH_BEGIN__ namespace internal {
#define __PATH_INTERNAL_END__ } __PATH_END__

// xw::dt
#define __DATETIME_BEGIN__ __MAIN_NAMESPACE_BEGIN__ namespace dt {
#define __DATETIME_END__ } __MAIN_NAMESPACE_END__

// xw::dt::internal
#define __DATETIME_INTERNAL_BEGIN__ __DATETIME_BEGIN__ namespace internal {
#define __DATETIME_INTERNAL_END__ } __DATETIME_END__

// xw::rgx
#define __RGX_BEGIN__ __MAIN_NAMESPACE_BEGIN__ namespace rgx {
#define __RGX_END__ } __MAIN_NAMESPACE_END__

// xw::str
#define __STR_BEGIN__ __MAIN_NAMESPACE_BEGIN__ namespace str {
#define __STR_END__ } __MAIN_NAMESPACE_END__

// xw::str::internal
#define __STR_INTERNAL_BEGIN__ __STR_BEGIN__ namespace internal {
#define __STR_INTERNAL_END__ } __STR_END__

// xw::utility
#define __UTILITY_BEGIN__ __MAIN_NAMESPACE_BEGIN__ namespace utility {
#define __UTILITY_END__ } __MAIN_NAMESPACE_END__

// xw::utility::internal
#define __UTILITY_INTERNAL_BEGIN__ __UTILITY_BEGIN__ namespace internal {
#define __UTILITY_INTERNAL_END__ } __UTILITY_END__

// Declares exception's class with given base.
#define DEF_EXCEPTION_WITH_BASE(name, base, default_message)\
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
		int line = 0, const char* function = "", const char* file = ""\
	)\
		: name(message, line, function, file, #name)\
	{\
	}\
\
	explicit name(\
		const std::string& message = default_message,\
		int line = 0, const char* function = "", const char* file = ""\
	)\
		: name(message.c_str(), line, function, file)\
	{\
	}\
}
