/**
 * error.cpp
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
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
		case xw::core::error_type::RequestTimeout:
			repr = "RequestTimeout";
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

__CORE_END__
