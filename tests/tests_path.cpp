/**
 * tests_path.cpp
 *
 * Copyright (c) 2019, 2021 Yuriy Lisovskiy
 */

#include <fstream>

#include <gtest/gtest.h>

#include "../src/path.h"

using namespace xw;


TEST(TestCase_path, _split_text_WithoutRoot)
{
	std::string expected_root = ".file";
	std::string actual_root, actual_ext;
	path::_split_text(".file", '!', '\0', '.', actual_root, actual_ext);
	ASSERT_EQ(expected_root, actual_root);
	ASSERT_EQ("", actual_ext);
}

TEST(TestCase_path, _split_text_WithoutExt)
{
	std::string expected_root = "!hello!world!file";
	std::string actual_root, actual_ext;
	path::_split_text("!hello!world!file", '!', '\0', '.', actual_root, actual_ext);
	ASSERT_EQ(expected_root, actual_root);
	ASSERT_EQ("", actual_ext);
}

TEST(TestCase_path, _split_text_RootAndExt)
{
	std::string expected_root = "!hello!world";
	std::string expected_ext = ".file";
	std::string actual_root, actual_ext;
	path::_split_text("!hello!world.file", '!', '\0', '.', actual_root, actual_ext);
	ASSERT_EQ(expected_root, actual_root);
	ASSERT_EQ(expected_ext, actual_ext);
}

TEST(TestCase_path, _split_text_RootAndExtWithAltSeparatorAfterSeparator)
{
	std::string expected_root = "!hello!worl~d";
	std::string expected_ext = ".file";
	std::string actual_root, actual_ext;
	path::_split_text("!hello!worl~d.file", '!', '~', '.', actual_root, actual_ext);
	ASSERT_EQ(expected_root, actual_root);
	ASSERT_EQ(expected_ext, actual_ext);
}

TEST(TestCase_path, _split_text_RootAndExtWithAltSeparatorBeforeSeparator)
{
	std::string expected_root = "!hello~!world";
	std::string expected_ext = ".file";
	std::string actual_root, actual_ext;
	path::_split_text("!hello~!world.file", '!', '~', '.', actual_root, actual_ext);
	ASSERT_EQ(expected_root, actual_root);
	ASSERT_EQ(expected_ext, actual_ext);
}

TEST(TestCase_path, _split_text_RootAndExtWithAltSeparatorAfterExt)
{
	std::string expected_root = "!hello!world.f~ile";
	std::string actual_root, actual_ext;
	path::_split_text("!hello!world.f~ile", '!', '~', '.', actual_root, actual_ext);
	ASSERT_EQ(expected_root, actual_root);
	ASSERT_EQ("", actual_ext);
}

TEST(TestCase_path, split_text_WithoutRoot)
{
	auto str_ext_sep = std::string(1, path::ext_sep);
	std::string expected_root = str_ext_sep + "file";
	std::string actual_root, actual_ext;
	path::split_text(str_ext_sep + "file", actual_root, actual_ext);
	ASSERT_EQ(expected_root, actual_root);
	ASSERT_EQ("", actual_ext);
}

TEST(TestCase_path, split_text_WithoutExt)
{
	std::string str_sep = std::string(1, path::sep);
	std::string expected_root = "hello" + str_sep + "world" + str_sep + "file";
	std::string actual_root, actual_ext;
	path::split_text("hello" + str_sep + "world" + str_sep + "file", actual_root, actual_ext);
	ASSERT_EQ(expected_root, actual_root);
	ASSERT_EQ("", actual_ext);
}

TEST(TestCase_path, split_text_RootAndExt)
{
	auto str_sep = std::string(1, path::sep);
	auto str_ext_sep = std::string(1, path::ext_sep);
	std::string expected_root = "hello" + str_sep + "world";
	std::string expected_ext = str_ext_sep + "file";
	std::string actual_root, actual_ext;
	path::split_text("hello" + str_sep + "world" + str_ext_sep + "file", actual_root, actual_ext);
	ASSERT_EQ(expected_root, actual_root);
	ASSERT_EQ(expected_ext, actual_ext);
}

TEST(TestCase_path, split_text_RootAndExtWithAltSeparatorAfterSeparator)
{
	auto str_sep = std::string(1, path::sep);
	auto str_ext_sep = std::string(1, path::ext_sep);
	std::string expected_root = "hello" + str_sep + "worl~d";
	std::string expected_ext = str_ext_sep + "file";
	std::string actual_root, actual_ext;
	path::split_text("hello" + str_sep + "worl~d" + str_ext_sep + "file", actual_root, actual_ext);
	ASSERT_EQ(expected_root, actual_root);
	ASSERT_EQ(expected_ext, actual_ext);
}

TEST(TestCase_path, split_text_RootAndExtWithAltSeparatorBeforeSeparator)
{
	auto str_sep = std::string(1, path::sep);
	auto str_ext_sep = std::string(1, path::ext_sep);
	std::string expected_root = "hello~" + str_sep + "world";
	std::string expected_ext = str_ext_sep + "file";
	std::string actual_root, actual_ext;
	path::split_text("hello~" + str_sep + "world" + str_ext_sep + "file", actual_root, actual_ext);
	ASSERT_EQ(expected_root, actual_root);
	ASSERT_EQ(expected_ext, actual_ext);
}

TEST(TestCase_path, split_text_RootAndExtWithAltSeparatorAfterExt)
{
	auto str_sep = std::string(1, path::sep);
	auto str_ext_sep = std::string(1, path::ext_sep);
	std::string expected_root = "hello" + str_sep + "world";
	std::string expected_ext = str_ext_sep + "f~ile";
	std::string actual_root, actual_ext;
	path::split_text("hello" + str_sep + "world" + str_ext_sep + "f~ile", actual_root, actual_ext);
	ASSERT_EQ(expected_root, actual_root);
	ASSERT_EQ(expected_ext, actual_ext);
}

TEST(TestCase_path, exists_False)
{
	ASSERT_FALSE(path::exists(
		std::string(1, path::current_dir) + std::string(1, path::sep) + "some-file.txt"
	));
}

TEST(TestCase_path, exists_True)
{
	std::string fp = std::string(1, path::current_dir) + std::string(1, path::sep) + "some-file.txt";
	std::ofstream fs(fp);
	if (fs.is_open())
	{
		fs.close();
	}

	ASSERT_TRUE(path::exists(fp));

	std::remove(fp.c_str());
}

TEST(TestCase_path, basename_EmptyInput)
{
	auto actual = path::basename("");
	ASSERT_EQ("", actual);
}

TEST(TestCase_path, basename_WithoutBaseDir)
{
	std::string expected = "file.txt";
	auto actual = path::basename("file.txt");
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_path, basename_WithCurrentDir)
{
	auto file_name = "file.txt";
	auto actual = path::basename(std::string(1, path::current_dir) + std::string(1, path::sep) + file_name);
	ASSERT_EQ(file_name, actual);
}

TEST(TestCase_path, basename_WithDir)
{
	auto str_sep = std::string(1, path::sep);
	auto file_name = "file.txt";
	auto actual = path::basename("hello" + str_sep + "dir" + str_sep + file_name);
	ASSERT_EQ(file_name, actual);
}

TEST(TestCase_path, dirname_EmptyInput)
{
	auto actual = path::dirname("");
	ASSERT_EQ("", actual);
}

TEST(TestCase_path, dirname_WithoutBaseDir)
{
	auto actual = path::dirname("file.txt");
	ASSERT_EQ("", actual);
}

TEST(TestCase_path, dirname_WithCurrentDir)
{
	auto dir_name = std::string(1, path::current_dir);
	auto actual = path::dirname(dir_name + std::string(1, path::sep) + "file.txt");
	ASSERT_EQ(dir_name, actual);
}

TEST(TestCase_path, dirname_WithDir)
{
	auto str_sep = std::string(1, path::sep);
	auto dir_name = "hello" + str_sep + "dir";
	auto actual = path::dirname(dir_name + str_sep + "file.txt");
	ASSERT_EQ(dir_name, actual);
}
