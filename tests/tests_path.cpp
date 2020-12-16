/**
 * tests_path.cpp
 *
 * Copyright (c) 2019 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../src/path.h"

using namespace xw;


TEST(PathTestCase, DirnameTest)
{
	std::string expected("/foo");
	std::string fullPath("/foo/bar");
	ASSERT_EQ(core::path::dirname(fullPath), expected);

	expected = "";
	fullPath = "bar";
	ASSERT_EQ(core::path::dirname(fullPath), expected);

	expected = "/";
	fullPath = "/bar";
	ASSERT_EQ(core::path::dirname(fullPath), expected);
}

TEST(PathTestCase, DirnameTrimDotsTest)
{
	std::string expected("/foo");
	std::string fullPath("/foo/./");
	ASSERT_EQ(core::path::dirname(fullPath), expected);

	expected = "/foo/..";
	fullPath = "/foo/../";
	ASSERT_EQ(core::path::dirname(fullPath), expected);

	expected = "/foo/../..";
	fullPath = "/foo/../../";
	ASSERT_EQ(core::path::dirname(fullPath), expected);

	expected = "/foo/..";
	fullPath = "/foo/.././";
	ASSERT_EQ(core::path::dirname(fullPath), expected);

	expected = "/foo/...";
	fullPath = "/foo/.../";
	ASSERT_EQ(core::path::dirname(fullPath), expected);
}

TEST(PathTestCase, FilenameTest)
{
	std::string expected("bar.txt");
	std::string fullPath("/foo/bar.txt");
	ASSERT_EQ(core::path::basename(fullPath), expected);

	expected = "bar.txt";
	fullPath = "bar.txt";
	ASSERT_EQ(core::path::basename(fullPath), expected);

	expected = "bar.txt";
	fullPath = "/bar.txt";
	ASSERT_EQ(core::path::basename(fullPath), expected);
}

TEST(PathTestCase, JoinTest)
{
	std::string left("/foo/");
	std::string right("//bar/");
	std::string expected("/foo/bar/");
	auto actual = core::path::join(left, right);
	ASSERT_EQ(expected, actual);
}

TEST(PathTestCase, JoinVectorTest)
{
	std::vector<std::string> paths {
		"", "/foo/", "//bar/", "", "/"
	};
	std::string expected("./foo/bar");
	auto actual = core::path::join(paths);
	ASSERT_EQ(expected, actual);
}
