/**
 * net/status.cpp
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 */

#include "./status.h"


__NET_BEGIN__

collections::Dictionary<unsigned short int, std::pair<std::string, std::string>> HTTP_STATUS(
	std::map<unsigned short int, std::pair<std::string, std::string>>{

		// Informational
		{100, {"Continue", "Request received, please continue"}},
		{101, {"Switching Protocols", "Switching to new protocol; obey Upgrade header"}},
		{102, {"Processing", ""}},
		{103, {"Early Hints", ""}},
		{105, {"Name Not Resolved", ""}},

		// Success
		{200, std::pair("OK", "Request fulfilled, document follows")},
		{201, std::pair("Created", "Document created, URL follows")},
		{202, std::pair("Accepted", "Request accepted, processing continues off-line")},
		{203, std::pair("Non-Authoritative Information", "Request fulfilled from cache")},
		{204, std::pair("No Content", "Request fulfilled, nothing follows")},
		{205, std::pair("Reset Content", "Clear input form for further input")},
		{206, std::pair("Partial Content", "Partial content follows")},
		{207, std::pair("Multi-Status", "")},
		{208, std::pair("Already Reported", "")},
		{226, std::pair("IM Used", "")},

		// Redirection
		{300, std::pair("Multiple Choices", "Object has several resources -- see URI list")},
		{301, std::pair("Moved Permanently", "Object moved permanently -- see URI list")},
		{302, std::pair("Found", "Object moved temporarily -- see URI list")},
		{303, std::pair("See Other", "Object moved -- see Method and URL list")},
		{304, std::pair("Not Modified", "Document has not changed since given time")},
		{305, std::pair("Use Proxy", "You must use proxy specified in Location to access this resource")},
		{306, std::pair("(Unused)", "")},
		{307, std::pair("Temporary Redirect", "Object moved temporarily -- see URI list")},
		{308, std::pair("Permanent Redirect", "Object moved temporarily -- see URI list")},

		// Client error
		{400, std::pair("Bad Request", "Bad request syntax or unsupported method")},
		{401, std::pair("Unauthorized", "No permission -- see authorization schemes")},
		{402, std::pair("Payment Required", "No payment -- see charging schemes")},
		{403, std::pair("Forbidden", "Request forbidden -- authorization will not help")},
		{404, std::pair("Not Found", "Nothing matches the given URI")},
		{405, std::pair("Method Not Allowed", "Specified method is invalid for this resource")},
		{406, std::pair("Not Acceptable", "URI not available in preferred format")},
		{407, std::pair("Proxy Authentication Required", "You must authenticate with this proxy before proceeding")},
		{408, std::pair("Request Timeout", "Request timed out; try again later")},
		{409, std::pair("Conflict", "Request conflict")},
		{410, std::pair("Gone", "URI no longer exists and has been permanently removed")},
		{411, std::pair("Length Required", "Client must specify Content-Length")},
		{412, std::pair("Precondition Failed", "Precondition in headers is false")},
		{413, std::pair("Payload Too Large", "Entity is too large")},
		{414, std::pair("URI Too Long", "URI is too long")},
		{415, std::pair("Unsupported Media Type", "Entity body in unsupported format")},
		{416, std::pair("Range Not Satisfiable", "Cannot satisfy request range")},
		{417, std::pair("Expectation Failed", "Expect condition could not be satisfied")},
		{421, std::pair("Misdirected Request", "")},
		{422, std::pair("Unprocessable Entity", "")},
		{423, std::pair("Locked", "")},
		{425, std::pair("Too Early", "")},
		{424, std::pair("Failed Dependency", "")},
		{426, std::pair("Upgrade Required", "")},
		{428, std::pair("Precondition Required", "The origin server requires the request to be conditional")},
		{429, std::pair("Too Many Requests", "The user has sent too many requests in a given amount of time (\"rate limiting\")")},
		{431, std::pair("Request Header Fields Too Large", "The server is unwilling to process the request because its header fields are too large")},
		{451, std::pair("Unavailable For Legal Reasons", "")},

		// Server error
		{500, std::pair("Internal Server Error", "Server got itself in trouble")},
		{501, std::pair("Not Implemented", "Server does not support this operation")},
		{502, std::pair("Bad Gateway", "Invalid responses from another server/proxy")},
		{503, std::pair("Service Unavailable", "The server cannot process the request due to a high load")},
		{504, std::pair("Gateway Timeout", "The gateway server did not receive a timely response")},
		{505, std::pair("HTTP Version Not Supported", "Cannot fulfill request")},
		{506, std::pair("Variant Also Negotiates", "")},
		{507, std::pair("Insufficient Storage", "")},
		{508, std::pair("Loop Detected", "")},
		{510, std::pair("Not Extended", "")},
		{511, std::pair("Network Authentication Required", "The client needs to authenticate to gain network access")},
	}
);

__NET_END__
