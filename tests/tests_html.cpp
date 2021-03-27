/**
 * tests_html.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../src/html.h"

using namespace xw;


TEST(TestCase_html, escape_NotEscapeQuotes)
{
	auto expected = R"('&lt;class "Ha&amp;"&gt;')";
	auto actual = html::escape(R"('<class "Ha&">')", false);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_html, escape_EscapeQuotes)
{
	auto expected = R"(&#x27;&lt;class &quot;Ha&amp;&quot;&gt;&#x27;)";
	auto actual = html::escape(R"('<class "Ha&">')");
	ASSERT_EQ(expected, actual);
}
