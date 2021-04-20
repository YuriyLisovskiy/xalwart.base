/**
 * error.cpp
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 */

#include "./error.h"


__MAIN_NAMESPACE_BEGIN__

std::string to_string(error_type et)
{
	const char *repr;
	switch (et)
	{
		case error_type::None:
			repr = "None";
			break;
		case error_type::HttpError:
			repr = "HttpError";
			break;
		case error_type::DisallowedHost:
			repr = "DisallowedHost";
			break;
		case error_type::DisallowedRedirect:
			repr = "DisallowedRedirect";
			break;
		case error_type::EntityTooLargeError:
			repr = "EntityTooLargeError";
			break;
		case error_type::FileDoesNotExistError:
			repr = "FileDoesNotExistError";
			break;
		case error_type::PermissionDenied:
			repr = "PermissionDenied";
			break;
		case error_type::NotFound:
			repr = "NotFound";
			break;
		case error_type::InternalServerError:
			repr = "InternalServerError";
			break;
		case error_type::RequestTimeout:
			repr = "RequestTimeout";
			break;
		case error_type::SuspiciousOperation:
			repr = "SuspiciousOperation";
			break;
		default:
			repr = "Unknown";
			break;
	}

	return repr;
}

__MAIN_NAMESPACE_END__
