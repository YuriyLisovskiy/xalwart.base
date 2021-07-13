/**
 * tests_error.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../src/error.h"

using namespace xw;


TEST(TestCase_error_type, to_string_None)
{
	std::string expected = "None";
	auto actual = to_string(error_type::None);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_error_type, to_string_HttpError)
{
	std::string expected = "HttpError";
	auto actual = to_string(error_type::HttpError);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_error_type, to_string_EntityTooLargeError)
{
	std::string expected = "EntityTooLargeError";
	auto actual = to_string(error_type::EntityTooLargeError);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_error_type, to_string_FileDoesNotExistError)
{
	std::string expected = "FileDoesNotExistError";
	auto actual = to_string(error_type::FileDoesNotExistError);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_error_type, to_string_PermissionDenied)
{
	std::string expected = "PermissionDenied";
	auto actual = to_string(error_type::PermissionDenied);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_error_type, to_string_NotFound)
{
	std::string expected = "NotFound";
	auto actual = to_string(error_type::NotFound);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_error_type, to_string_InternalServerError)
{
	std::string expected = "InternalServerError";
	auto actual = to_string(error_type::InternalServerError);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_error_type, to_string_RequestTimeout)
{
	std::string expected = "RequestTimeout";
	auto actual = to_string(error_type::RequestTimeout);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_error_type, to_string_SuspiciousOperation)
{
	std::string expected = "SuspiciousOperation";
	auto actual = to_string(error_type::SuspiciousOperation);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_error_type, to_string_DisallowedHost)
{
	std::string expected = "DisallowedHost";
	auto actual = to_string(error_type::DisallowedHost);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_error_type, to_string_DisallowedRedirect)
{
	std::string expected = "DisallowedRedirect";
	auto actual = to_string(error_type::DisallowedRedirect);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_error_type, to_string_Unknown)
{
	std::string expected = "Unknown";
	auto actual = to_string((error_type)-1);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_Error, none)
{
	auto actual = Error::none();
	ASSERT_EQ(actual.line, 0);
	ASSERT_EQ(actual.func, "");
	ASSERT_EQ(actual.file, "");
	ASSERT_EQ(actual.msg, "");
	ASSERT_EQ(actual.type, error_type::None);
}

TEST(TestCase_Error, operator_bool_True)
{
	ASSERT_TRUE(Error(error_type::HttpError, "").operator bool());
}

TEST(TestCase_Error, operator_bool_False)
{
	ASSERT_FALSE(Error::none().operator bool());
}

TEST(TestCase_Error, operator_not_False)
{
	ASSERT_FALSE(!Error(error_type::HttpError, ""));
}

TEST(TestCase_Error, operator_not_True)
{
	ASSERT_TRUE(!Error::none());
}

TEST(TestCase_Error, get_message)
{
	auto actual = Error(error_type::HttpError, "It's an http error!");
	ASSERT_EQ(actual.get_message(), "HttpError: It's an http error!");
}

TEST(TestCase_Error, line_func_file)
{
	auto line_no = __LINE__;
	auto actual = Error(
		error_type::HttpError, "It's an http error!",
		line_no, __FUNCTION__, __FILE__
	);
	ASSERT_EQ(actual.line, line_no);
	ASSERT_EQ(actual.func, __FUNCTION__);
	ASSERT_EQ(actual.file, __FILE__);
}

TEST(TestCase_error_type, operator_ostream)
{
	auto et = error_type::NotFound;
	std::stringstream ss;
	ss << et;
	std::string expected = "NotFound";
	auto actual = ss.str();
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_Error, operator_ostream)
{
	auto line_no = __LINE__;
	auto err = Error(
		error_type::HttpError, "It's an http error!",
		line_no, __FUNCTION__, __FILE__
	);
	std::stringstream ss;
	ss << err;
	std::string expected = "\nFile \"" + std::string(__FILE__) + "\", line " +
		std::to_string(line_no) + ", in " + std::string(__FUNCTION__) + "\n" + "It's an http error!";
	auto actual = ss.str();
	ASSERT_EQ(expected, actual);
}
