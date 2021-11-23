/**
 * tests_path.cpp
 *
 * Copyright (c) 2019, 2021 Yuriy Lisovskiy
 */

#include <fstream>

#include <gtest/gtest.h>

#include "../src/path.h"

using namespace xw;


TEST(TestCase_path, exists_False)
{
	ASSERT_FALSE(path::Path(
		std::string(1, path::current_dir) + std::string(1, path::path_sep) + "some-file.txt"
	).exists());
}

TEST(TestCase_path, exists_True)
{
	std::string fp = std::string(1, path::current_dir) + std::string(1, path::path_sep) + "some-file.txt";
	std::ofstream fs(fp);
	if (fs.is_open())
	{
		fs.close();
	}

	ASSERT_TRUE(path::Path(fp).exists());

	std::remove(fp.c_str());
}

TEST(TestCase_path, basename_EmptyInput)
{
	auto actual = path::Path("").basename();
	ASSERT_EQ("", actual);
}

TEST(TestCase_path, basename_WithoutBaseDir)
{
	std::string expected = "file.txt";
	auto actual = path::Path("file.txt").basename();
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_path, basename_WithCurrentDir)
{
	auto file_name = "file.txt";
	auto actual = path::Path(
		std::string(1, path::current_dir) + std::string(1, path::path_sep) + file_name
	).basename();
	ASSERT_EQ(file_name, actual);
}

TEST(TestCase_path, basename_WithDir)
{
	auto str_sep = std::string(1, path::path_sep);
	auto file_name = "file.txt";
	auto actual = path::Path("hello" + str_sep + "dir" + str_sep + file_name).basename();
	ASSERT_EQ(file_name, actual);
}

TEST(TestCase_path, dirname_EmptyInput)
{
	auto actual = path::Path("").dirname();
	ASSERT_EQ("", actual);
}

TEST(TestCase_path, dirname_WithoutBaseDir)
{
	auto actual = path::Path("file.txt").dirname();
	ASSERT_EQ("", actual);
}

TEST(TestCase_path, dirname_WithCurrentDir)
{
	auto dir_name = std::string(1, path::current_dir);
	auto actual = path::Path(dir_name + std::string(1, path::path_sep) + "file.txt").dirname();
	ASSERT_EQ(dir_name, actual);
}

TEST(TestCase_path, dirname_WithDir)
{
	auto str_sep = std::string(1, path::path_sep);
	auto dir_name = "hello" + str_sep + "dir";
	auto actual = path::Path(dir_name + str_sep + "file.txt").dirname();
	ASSERT_EQ(dir_name, actual);
}

TEST(TestCase_path, get_size_ZeroSize)
{
	std::string fp = "some-file.txt";
	std::ofstream fs(fp);
	if (fs.is_open())
	{
		fs.close();
	}

	ASSERT_EQ(path::get_size(fp), 0);

	std::remove(fp.c_str());
}

TEST(TestCase_path, get_size_PositiveIntSize)
{
	std::vector<unsigned char> bytes = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
	std::string fp = "some-file.txt";
	std::ofstream fs(fp, std::ios_base::binary);
	if (fs.is_open())
	{
		fs.write((char*)bytes.data(), bytes.size());
		fs.close();
	}

	ASSERT_EQ(path::get_size(fp), bytes.size());

	std::remove(fp.c_str());
}

TEST(TestCase_path, join_Single)
{
	std::string expected = "mydir";
	auto actual = path::join("mydir");
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_path, join_Double)
{
	std::string expected = "hello" + std::string(1, path::path_sep) + "dir";
	auto actual = path::join("hello", "dir");
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_path, join_SeveralParts)
{
	auto str_sep = std::string(1, path::path_sep);
	std::string expected = "some" + str_sep + "dir" + str_sep + "to" + str_sep + "secret.file";
	auto actual = path::join("some", "dir", "to", "secret.file");
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_path, join_WithMiddleAbsolutePath)
{
	auto str_sep = std::string(1, path::path_sep);
	std::string expected = str_sep + "dir" + str_sep + "file.txt";
	auto actual = path::join("some", str_sep + "dir", "file.txt");
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_path, join_WithLastEmptyPart)
{
	auto str_sep = std::string(1, path::path_sep);
	std::string expected = "some" + str_sep + "dir" + str_sep;
	auto actual = path::join("some", "dir", "");
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_path, is_absolute_True)
{
	auto str_sep = std::string(1, path::path_sep);
	ASSERT_TRUE(path::Path(str_sep + "some" + str_sep + "location").is_absolute());
}

TEST(TestCase_path, is_absolute_False)
{
	auto str_sep = std::string(1, path::path_sep);
	ASSERT_FALSE(path::Path("some" + str_sep + "location").is_absolute());
}
