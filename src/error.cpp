/**
 * error.cpp
 *
 * Copyright (c) 2020 Yuriy Lisovskiy
 */

#include "./error.h"


__CORE_BEGIN__

std::string to_string(error_type et)
{
	const char *repr;
	switch (et)
	{
		case xw::core::error_type::None:
			repr = "None";
			break;
		case xw::core::error_type::HttpError:
			repr = "HttpError";
			break;
		case xw::core::error_type::DisallowedHost:
			repr = "DisallowedHost";
			break;
		case xw::core::error_type::DisallowedRedirect:
			repr = "DisallowedRedirect";
			break;
		case xw::core::error_type::EntityTooLargeError:
			repr = "EntityTooLargeError";
			break;
		case xw::core::error_type::FileDoesNotExistError:
			repr = "FileDoesNotExistError";
			break;
		case xw::core::error_type::PermissionDenied:
			repr = "PermissionDenied";
			break;
		case xw::core::error_type::NotFound:
			repr = "NotFound";
			break;
		case xw::core::error_type::SuspiciousOperation:
			repr = "SuspiciousOperation";
			break;
		default:
			repr = "Unknown";
			break;
	}

	return repr;
}

Error::Error(
	error_type type, const char* msg, int line, const char* func, const char* file
) : type(type), msg(msg), line(line), func(func), file(file)
{
}

Error::Error(
	error_type type, const std::string& msg, int line, const char* func, const char* file
) : type(type), msg(msg.c_str()), line(line), func(func), file(file)
{
}

Error::Error(error_type type, const char* msg) : Error(type, msg, 0, "", "")
{
}

Error::Error(error_type type, const std::string& msg) : Error(type, msg, 0, "", "")
{
}

Error::Error() : Error(None, "", 0, "", "")
{
}

Error Error::none()
{
	return Error();
}

Error::operator bool() const
{
	return this->type != None;
}

std::string Error::get_message() const
{
	return to_string(this->type) + ": " + this->msg;
}

__CORE_END__

std::ostream& operator<<(std::ostream& os, const xw::core::error_type& type)
{
	return os << to_string(type);
}

std::ostream& operator<<(std::ostream& os, const xw::core::Error& err)
{
	return os << "\nFile \"" << err.file << "\", line " << err.line << ", in " << err.func << '\n' << err.msg;
}
