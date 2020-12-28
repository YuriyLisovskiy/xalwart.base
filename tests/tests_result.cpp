/**
 * tests_result.cpp
 *
 * Copyright (c) 2020 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../src/result.h"

using namespace xw;


TEST(FuncResult_TestCase, ConstructFromValue)
{
	auto result = core::Result<int>(2020);
	ASSERT_FALSE(result.err);
	ASSERT_EQ(result.value, 2020);
}

TEST(FuncResult_TestCase, RaiseException)
{
	using core::error_type;
	auto result = core::raise<error_type::HttpError, int>("an error");

	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(error_type::HttpError));

	ASSERT_FALSE(result.catch_(error_type::None));
	ASSERT_FALSE(result.catch_(error_type::EntityTooLargeError));
	ASSERT_FALSE(result.catch_(error_type::FileDoesNotExistError));
	ASSERT_FALSE(result.catch_(error_type::PermissionDenied));
	ASSERT_FALSE(result.catch_(error_type::SuspiciousOperation));
	ASSERT_FALSE(result.catch_(error_type::DisallowedHost));
	ASSERT_FALSE(result.catch_(error_type::DisallowedRedirect));
}

TEST(FuncResult_TestCase, RaiseEntityTooLargeError)
{
	using core::error_type;
	auto result = core::raise<error_type::EntityTooLargeError, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(error_type::EntityTooLargeError));
	ASSERT_TRUE(result.catch_(error_type::HttpError));
}

TEST(FuncResult_TestCase, RaiseFileDoesNotExistError)
{
	using core::error_type;
	auto result = core::raise<error_type::FileDoesNotExistError, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(error_type::FileDoesNotExistError));
	ASSERT_TRUE(result.catch_(error_type::HttpError));
}

TEST(FuncResult_TestCase, RaisePermissionDenied)
{
	using core::error_type;
	auto result = core::raise<error_type::PermissionDenied, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(error_type::PermissionDenied));
	ASSERT_TRUE(result.catch_(error_type::HttpError));
}

TEST(FuncResult_TestCase, RaiseSuspiciousOperation)
{
	using core::error_type;
	auto result = core::raise<error_type::SuspiciousOperation, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(error_type::SuspiciousOperation));
	ASSERT_TRUE(result.catch_(error_type::HttpError));
}

TEST(FuncResult_TestCase, RaiseDisallowedHost)
{
	using core::error_type;
	auto result = core::raise<error_type::DisallowedHost, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(error_type::DisallowedHost));
	ASSERT_TRUE(result.catch_(error_type::SuspiciousOperation));
	ASSERT_TRUE(result.catch_(error_type::HttpError));
}

TEST(FuncResult_TestCase, RaiseDisallowedRedirect)
{
	using core::error_type;
	auto result = core::raise<error_type::DisallowedRedirect, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(error_type::DisallowedRedirect));
	ASSERT_TRUE(result.catch_(error_type::SuspiciousOperation));
	ASSERT_TRUE(result.catch_(error_type::HttpError));
}
