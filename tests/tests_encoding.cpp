/**
 * core/tests_encoding.cpp
 *
 * Copyright (c) 2019, 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../src/encoding.h"

using namespace xw;


TEST(TestCase_encode_url, encode)
{
	std::string expected("https://hostName/deepLinkAction.do?userName=peter%40nable.com&password=Hello%25There&method=defaultDashboard");
	std::string toEncode("https://hostName/deepLinkAction.do?userName=peter@nable.com&password=Hello%There&method=defaultDashboard");
	ASSERT_EQ(encoding::encode_url(toEncode), expected);

	expected = "https://www.google.com/?q=%E3%83%95%E3%82%A9%E3%83%BC%E3%83%87%E3%82%A3%E3%83%BC";
	toEncode = "https://www.google.com/?q=フォーディー";
	ASSERT_EQ(encoding::encode_url(toEncode), expected);
}
