/**
 * tests/net/tests_status.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/net/status.h"

using namespace xw;


TEST(TestCase_HTTP_STATUS, _100)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(100));
	auto status = net::HTTP_STATUS.get(100);
	ASSERT_EQ(status.first, "Continue");
}

TEST(TestCase_HTTP_STATUS, _101)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(101));
	auto status = net::HTTP_STATUS.get(101);
	ASSERT_EQ(status.first, "Switching Protocols");
}

TEST(TestCase_HTTP_STATUS, _102)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(102));
	auto status = net::HTTP_STATUS.get(102);
	ASSERT_EQ(status.first, "Processing");
}

TEST(TestCase_HTTP_STATUS, _103)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(103));
	auto status = net::HTTP_STATUS.get(103);
	ASSERT_EQ(status.first, "Early Hints");
}

TEST(TestCase_HTTP_STATUS, _104_Unassigned)
{
	ASSERT_FALSE(net::HTTP_STATUS.contains(104));
}

TEST(TestCase_HTTP_STATUS, _105)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(105));
	auto status = net::HTTP_STATUS.get(105);
	ASSERT_EQ(status.first, "Name Not Resolved");
}

TEST(TestCase_HTTP_STATUS, from_106_to_199_Unassigned)
{
	for (short status_code = 106; status_code <= 199; status_code++)
	{
		ASSERT_FALSE(net::HTTP_STATUS.contains(status_code));
	}
}

TEST(TestCase_HTTP_STATUS, _200)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(200));
	auto status = net::HTTP_STATUS.get(200);
	ASSERT_EQ(status.first, "OK");
}

TEST(TestCase_HTTP_STATUS, _201)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(201));
	auto status = net::HTTP_STATUS.get(201);
	ASSERT_EQ(status.first, "Created");
}

TEST(TestCase_HTTP_STATUS, _202)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(202));
	auto status = net::HTTP_STATUS.get(202);
	ASSERT_EQ(status.first, "Accepted");
}

TEST(TestCase_HTTP_STATUS, _203)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(203));
	auto status = net::HTTP_STATUS.get(203);
	ASSERT_EQ(status.first, "Non-Authoritative Information");
}

TEST(TestCase_HTTP_STATUS, _204)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(204));
	auto status = net::HTTP_STATUS.get(204);
	ASSERT_EQ(status.first, "No Content");
}

TEST(TestCase_HTTP_STATUS, _205)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(205));
	auto status = net::HTTP_STATUS.get(205);
	ASSERT_EQ(status.first, "Reset Content");
}

TEST(TestCase_HTTP_STATUS, _206)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(206));
	auto status = net::HTTP_STATUS.get(206);
	ASSERT_EQ(status.first, "Partial Content");
}

TEST(TestCase_HTTP_STATUS, _207)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(207));
	auto status = net::HTTP_STATUS.get(207);
	ASSERT_EQ(status.first, "Multi-Status");
}

TEST(TestCase_HTTP_STATUS, _208)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(208));
	auto status = net::HTTP_STATUS.get(208);
	ASSERT_EQ(status.first, "Already Reported");
}

TEST(TestCase_HTTP_STATUS, from_209_to_225_Unassigned)
{
	for (short status_code = 209; status_code <= 225; status_code++)
	{
		ASSERT_FALSE(net::HTTP_STATUS.contains(status_code));
	}
}

TEST(TestCase_HTTP_STATUS, _226)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(226));
	auto status = net::HTTP_STATUS.get(226);
	ASSERT_EQ(status.first, "IM Used");
}

TEST(TestCase_HTTP_STATUS, from_227_to_299_Unassigned)
{
	for (short status_code = 227; status_code <= 299; status_code++)
	{
		ASSERT_FALSE(net::HTTP_STATUS.contains(status_code));
	}
}

TEST(TestCase_HTTP_STATUS, _300)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(300));
	auto status = net::HTTP_STATUS.get(300);
	ASSERT_EQ(status.first, "Multiple Choices");
}

TEST(TestCase_HTTP_STATUS, _301)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(301));
	auto status = net::HTTP_STATUS.get(301);
	ASSERT_EQ(status.first, "Moved Permanently");
}

TEST(TestCase_HTTP_STATUS, _302)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(302));
	auto status = net::HTTP_STATUS.get(302);
	ASSERT_EQ(status.first, "Found");
}

TEST(TestCase_HTTP_STATUS, _303)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(303));
	auto status = net::HTTP_STATUS.get(303);
	ASSERT_EQ(status.first, "See Other");
}

TEST(TestCase_HTTP_STATUS, _304)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(304));
	auto status = net::HTTP_STATUS.get(304);
	ASSERT_EQ(status.first, "Not Modified");
}

TEST(TestCase_HTTP_STATUS, _305)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(305));
	auto status = net::HTTP_STATUS.get(305);
	ASSERT_EQ(status.first, "Use Proxy");
}

TEST(TestCase_HTTP_STATUS, _306)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(306));
	auto status = net::HTTP_STATUS.get(306);
	ASSERT_EQ(status.first, "(Unused)");
}

TEST(TestCase_HTTP_STATUS, _307)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(307));
	auto status = net::HTTP_STATUS.get(307);
	ASSERT_EQ(status.first, "Temporary Redirect");
}

TEST(TestCase_HTTP_STATUS, _308)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(308));
	auto status = net::HTTP_STATUS.get(308);
	ASSERT_EQ(status.first, "Permanent Redirect");
}

TEST(TestCase_HTTP_STATUS, from_309_to_399_Unassigned)
{
	for (short status_code = 309; status_code <= 399; status_code++)
	{
		ASSERT_FALSE(net::HTTP_STATUS.contains(status_code));
	}
}

TEST(TestCase_HTTP_STATUS, _400)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(400));
	auto status = net::HTTP_STATUS.get(400);
	ASSERT_EQ(status.first, "Bad Request");
}

TEST(TestCase_HTTP_STATUS, _401)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(401));
	auto status = net::HTTP_STATUS.get(401);
	ASSERT_EQ(status.first, "Unauthorized");
}

TEST(TestCase_HTTP_STATUS, _402)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(402));
	auto status = net::HTTP_STATUS.get(402);
	ASSERT_EQ(status.first, "Payment Required");
}

TEST(TestCase_HTTP_STATUS, _403)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(403));
	auto status = net::HTTP_STATUS.get(403);
	ASSERT_EQ(status.first, "Forbidden");
}

TEST(TestCase_HTTP_STATUS, _404)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(404));
	auto status = net::HTTP_STATUS.get(404);
	ASSERT_EQ(status.first, "Not Found");
}

TEST(TestCase_HTTP_STATUS, _405)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(405));
	auto status = net::HTTP_STATUS.get(405);
	ASSERT_EQ(status.first, "Method Not Allowed");
}

TEST(TestCase_HTTP_STATUS, _406)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(406));
	auto status = net::HTTP_STATUS.get(406);
	ASSERT_EQ(status.first, "Not Acceptable");
}

TEST(TestCase_HTTP_STATUS, _407)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(407));
	auto status = net::HTTP_STATUS.get(407);
	ASSERT_EQ(status.first, "Proxy Authentication Required");
}

TEST(TestCase_HTTP_STATUS, _408)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(408));
	auto status = net::HTTP_STATUS.get(408);
	ASSERT_EQ(status.first, "Request Timeout");
}

TEST(TestCase_HTTP_STATUS, _409)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(409));
	auto status = net::HTTP_STATUS.get(409);
	ASSERT_EQ(status.first, "Conflict");
}

TEST(TestCase_HTTP_STATUS, _410)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(410));
	auto status = net::HTTP_STATUS.get(410);
	ASSERT_EQ(status.first, "Gone");
}

TEST(TestCase_HTTP_STATUS, _411)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(411));
	auto status = net::HTTP_STATUS.get(411);
	ASSERT_EQ(status.first, "Length Required");
}

TEST(TestCase_HTTP_STATUS, _412)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(412));
	auto status = net::HTTP_STATUS.get(412);
	ASSERT_EQ(status.first, "Precondition Failed");
}

TEST(TestCase_HTTP_STATUS, _413)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(413));
	auto status = net::HTTP_STATUS.get(413);
	ASSERT_EQ(status.first, "Payload Too Large");
}

TEST(TestCase_HTTP_STATUS, _414)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(414));
	auto status = net::HTTP_STATUS.get(414);
	ASSERT_EQ(status.first, "URI Too Long");
}

TEST(TestCase_HTTP_STATUS, _415)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(415));
	auto status = net::HTTP_STATUS.get(415);
	ASSERT_EQ(status.first, "Unsupported Media Type");
}

TEST(TestCase_HTTP_STATUS, _416)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(416));
	auto status = net::HTTP_STATUS.get(416);
	ASSERT_EQ(status.first, "Range Not Satisfiable");
}

TEST(TestCase_HTTP_STATUS, _417)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(417));
	auto status = net::HTTP_STATUS.get(417);
	ASSERT_EQ(status.first, "Expectation Failed");
}

TEST(TestCase_HTTP_STATUS, from_418_to_420_Unassigned)
{
	for (short status_code = 418; status_code <= 420; status_code++)
	{
		ASSERT_FALSE(net::HTTP_STATUS.contains(status_code));
	}
}

TEST(TestCase_HTTP_STATUS, _421)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(421));
	auto status = net::HTTP_STATUS.get(421);
	ASSERT_EQ(status.first, "Misdirected Request");
}

TEST(TestCase_HTTP_STATUS, _422)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(422));
	auto status = net::HTTP_STATUS.get(422);
	ASSERT_EQ(status.first, "Unprocessable Entity");
}

TEST(TestCase_HTTP_STATUS, _423)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(423));
	auto status = net::HTTP_STATUS.get(423);
	ASSERT_EQ(status.first, "Locked");
}

TEST(TestCase_HTTP_STATUS, _424)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(424));
	auto status = net::HTTP_STATUS.get(424);
	ASSERT_EQ(status.first, "Failed Dependency");
}

TEST(TestCase_HTTP_STATUS, _425)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(425));
	auto status = net::HTTP_STATUS.get(425);
	ASSERT_EQ(status.first, "Too Early");
}

TEST(TestCase_HTTP_STATUS, _426)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(426));
	auto status = net::HTTP_STATUS.get(426);
	ASSERT_EQ(status.first, "Upgrade Required");
}

TEST(TestCase_HTTP_STATUS, _427_Unassigned)
{
	ASSERT_FALSE(net::HTTP_STATUS.contains(427));
}

TEST(TestCase_HTTP_STATUS, _428)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(428));
	auto status = net::HTTP_STATUS.get(428);
	ASSERT_EQ(status.first, "Precondition Required");
}

TEST(TestCase_HTTP_STATUS, _429)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(429));
	auto status = net::HTTP_STATUS.get(429);
	ASSERT_EQ(status.first, "Too Many Requests");
}

TEST(TestCase_HTTP_STATUS, _430_Unassigned)
{
	ASSERT_FALSE(net::HTTP_STATUS.contains(430));
}

TEST(TestCase_HTTP_STATUS, _431)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(431));
	auto status = net::HTTP_STATUS.get(431);
	ASSERT_EQ(status.first, "Request Header Fields Too Large");
}

TEST(TestCase_HTTP_STATUS, from_432_to_450_Unassigned)
{
	for (short status_code = 432; status_code <= 450; status_code++)
	{
		ASSERT_FALSE(net::HTTP_STATUS.contains(status_code));
	}
}

TEST(TestCase_HTTP_STATUS, _451)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(451));
	auto status = net::HTTP_STATUS.get(451);
	ASSERT_EQ(status.first, "Unavailable For Legal Reasons");
}

TEST(TestCase_HTTP_STATUS, from_452_to_499_Unassigned)
{
	for (short status_code = 452; status_code <= 499; status_code++)
	{
		ASSERT_FALSE(net::HTTP_STATUS.contains(status_code));
	}
}

TEST(TestCase_HTTP_STATUS, _500)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(500));
	auto status = net::HTTP_STATUS.get(500);
	ASSERT_EQ(status.first, "Internal Server Error");
}

TEST(TestCase_HTTP_STATUS, _501)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(501));
	auto status = net::HTTP_STATUS.get(501);
	ASSERT_EQ(status.first, "Not Implemented");
}

TEST(TestCase_HTTP_STATUS, _502)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(502));
	auto status = net::HTTP_STATUS.get(502);
	ASSERT_EQ(status.first, "Bad Gateway");
}

TEST(TestCase_HTTP_STATUS, _503)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(503));
	auto status = net::HTTP_STATUS.get(503);
	ASSERT_EQ(status.first, "Service Unavailable");
}

TEST(TestCase_HTTP_STATUS, _504)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(504));
	auto status = net::HTTP_STATUS.get(504);
	ASSERT_EQ(status.first, "Gateway Timeout");
}

TEST(TestCase_HTTP_STATUS, _505)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(505));
	auto status = net::HTTP_STATUS.get(505);
	ASSERT_EQ(status.first, "HTTP Version Not Supported");
}

TEST(TestCase_HTTP_STATUS, _506)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(506));
	auto status = net::HTTP_STATUS.get(506);
	ASSERT_EQ(status.first, "Variant Also Negotiates");
}

TEST(TestCase_HTTP_STATUS, _507)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(507));
	auto status = net::HTTP_STATUS.get(507);
	ASSERT_EQ(status.first, "Insufficient Storage");
}

TEST(TestCase_HTTP_STATUS, _508)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(508));
	auto status = net::HTTP_STATUS.get(508);
	ASSERT_EQ(status.first, "Loop Detected");
}

TEST(TestCase_HTTP_STATUS, _509_Unassigned)
{
	ASSERT_FALSE(net::HTTP_STATUS.contains(509));
}

TEST(TestCase_HTTP_STATUS, _510)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(510));
	auto status = net::HTTP_STATUS.get(510);
	ASSERT_EQ(status.first, "Not Extended");
}

TEST(TestCase_HTTP_STATUS, _511)
{
	ASSERT_TRUE(net::HTTP_STATUS.contains(511));
	auto status = net::HTTP_STATUS.get(511);
	ASSERT_EQ(status.first, "Network Authentication Required");
}

TEST(TestCase_HTTP_STATUS, from_512_to_599_Unassigned)
{
	for (short status_code = 512; status_code <= 599; status_code++)
	{
		ASSERT_FALSE(net::HTTP_STATUS.contains(status_code));
	}
}
