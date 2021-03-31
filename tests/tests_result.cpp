/**
 * tests_result.cpp
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../src/result.h"

using namespace xw;


TEST(TestCase_Result, ConstructFromValue)
{
	auto result = core::Result<int>(2020);
	ASSERT_FALSE(result.err);
	ASSERT_EQ(result.value, 2020);
}

TEST(TestCase_Result, ConstructFromPointerToValue)
{
	auto result = core::Result(new float(10.1f));
	ASSERT_FALSE(result.err);
	ASSERT_EQ(*result.value, 10.1f);
	delete result.value;
}

TEST(TestCase_Result, operator_bool_ValueTrue)
{
	ASSERT_TRUE(core::Result<int>(10).operator bool());
}

TEST(TestCase_Result, operator_not_ErrorFalse)
{
	ASSERT_FALSE(!core::Result<int>(core::Error(core::HttpError, "msg")));
}

TEST(TestCase_Result, operator_not_ValueFalse)
{
	ASSERT_FALSE(!core::Result<int>(10).operator bool());
}

TEST(TestCase_Result, operator_bool_ErrorTrue)
{
	ASSERT_TRUE(core::Result<int>(core::Error(core::HttpError, "msg")));
}

TEST(TestCase_Result, catch_Error)
{
	auto error = core::Result<int>(core::Error(core::HttpError, "an error"));

	ASSERT_TRUE(error.err);
	ASSERT_TRUE(error.catch_(core::HttpError));

	ASSERT_FALSE(error.catch_(core::None));
	ASSERT_FALSE(error.catch_(core::EntityTooLargeError));
	ASSERT_FALSE(error.catch_(core::FileDoesNotExistError));
	ASSERT_FALSE(error.catch_(core::PermissionDenied));
	ASSERT_FALSE(error.catch_(core::NotFound));
	ASSERT_FALSE(error.catch_(core::InternalServerError));
	ASSERT_FALSE(error.catch_(core::RequestTimeout));
	ASSERT_FALSE(error.catch_(core::SuspiciousOperation));
	ASSERT_FALSE(error.catch_(core::DisallowedHost));
	ASSERT_FALSE(error.catch_(core::DisallowedRedirect));
}

TEST(TestCase_Result, catch_EntityTooLargeErrorFromHttpErrorGroup)
{
	auto result = core::raise<core::EntityTooLargeError, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(core::EntityTooLargeError));
	ASSERT_TRUE(result.catch_(core::HttpError));
}

TEST(TestCase_Result, catch_FileDoesNotExistErrorFromHttpErrorGroup)
{
	auto result = core::raise<core::FileDoesNotExistError, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(core::FileDoesNotExistError));
	ASSERT_TRUE(result.catch_(core::HttpError));
}

TEST(TestCase_Result, catch_PermissionDeniedFromHttpErrorGroup)
{
	auto result = core::raise<core::PermissionDenied, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(core::PermissionDenied));
	ASSERT_TRUE(result.catch_(core::HttpError));
}

TEST(TestCase_Result, catch_NotFoundFromHttpErrorGroup)
{
	auto result = core::raise<core::NotFound, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(core::NotFound));
	ASSERT_TRUE(result.catch_(core::HttpError));
}

TEST(TestCase_Result, catch_InternalServerErrorFromHttpErrorGroup)
{
	auto result = core::raise<core::InternalServerError, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(core::InternalServerError));
	ASSERT_TRUE(result.catch_(core::HttpError));
}

TEST(TestCase_Result, catch_RequestTimeoutFromHttpErrorGroup)
{
	auto result = core::raise<core::RequestTimeout, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(core::RequestTimeout));
	ASSERT_TRUE(result.catch_(core::HttpError));
}

TEST(TestCase_Result, catch_SuspiciousOperationFromHttpErrorGroup)
{
	auto result = core::raise<core::SuspiciousOperation, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(core::SuspiciousOperation));
	ASSERT_TRUE(result.catch_(core::HttpError));
}

TEST(TestCase_Result, catch_DisallowedHostFromHttpErrorGroup)
{
	auto result = core::raise<core::DisallowedHost, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(core::DisallowedHost));
	ASSERT_TRUE(result.catch_(core::HttpError));
}

TEST(TestCase_Result, catch_DisallowedRedirectFromHttpErrorGroup)
{
	auto result = core::raise<core::DisallowedRedirect, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(core::DisallowedRedirect));
	ASSERT_TRUE(result.catch_(core::HttpError));
}

TEST(TestCase_Result, catch_DisallowedHostFromSuspiciousOperationGroup)
{
	auto result = core::raise<core::DisallowedHost, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(core::DisallowedHost));
	ASSERT_TRUE(result.catch_(core::SuspiciousOperation));
	ASSERT_TRUE(result.catch_(core::HttpError));
}

TEST(TestCase_Result, catch_DisallowedRedirectFromSuspiciousOperationGroup)
{
	auto result = core::raise<core::DisallowedRedirect, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(core::DisallowedRedirect));
	ASSERT_TRUE(result.catch_(core::SuspiciousOperation));
	ASSERT_TRUE(result.catch_(core::HttpError));
}

TEST(TestCase_Result, forward_err)
{
	auto line_no = __LINE__;
	auto result = core::Result<int>(
		core::Error(core::HttpError, "an error", line_no, __FUNCTION__, __FILE__)
	);

	ASSERT_EQ(result.err.type, core::HttpError);
	ASSERT_EQ(result.err.msg, "an error");
	ASSERT_EQ(result.err.line, line_no);
	ASSERT_EQ(result.err.func, __FUNCTION__ );
	ASSERT_EQ(result.err.file, __FILE__);

	auto forwarded = result.forward_err<double>();
	ASSERT_EQ(forwarded.err.type, core::HttpError);
	ASSERT_EQ(forwarded.err.msg, "an error");
	ASSERT_EQ(forwarded.err.line, line_no);
	ASSERT_EQ(forwarded.err.func, __FUNCTION__ );
	ASSERT_EQ(forwarded.err.file, __FILE__);
}

TEST(TestCase_Result, forward_err_WithPoinerType)
{
	auto line_no = __LINE__;
	auto result = core::Result<int*>(
		core::Error(core::HttpError, "an error", line_no, __FUNCTION__, __FILE__)
	);

	auto forwarded = result.forward_err<double>();
	ASSERT_EQ(forwarded.err.type, core::HttpError);
	ASSERT_EQ(forwarded.err.msg, "an error");
	ASSERT_EQ(forwarded.err.line, line_no);
	ASSERT_EQ(forwarded.err.func, __FUNCTION__ );
	ASSERT_EQ(forwarded.err.file, __FILE__);
}

TEST(TestCase_Result, null_OperatorBoolFalse)
{
	ASSERT_FALSE(core::Result<int>::null().operator bool());
}

TEST(TestCase_Result, null_OperatorNotTrue)
{
	ASSERT_TRUE(!core::Result<int>::null());
}

TEST(TestCase_raise, WithMessageOnly)
{
	auto result = core::raise<core::HttpError, int>("an error");

	ASSERT_TRUE(result.err);
	ASSERT_EQ(result.err.type, core::HttpError);
	ASSERT_EQ(result.err.msg, "an error");
}

TEST(TestCase_raise, Full)
{
	auto line_no = __LINE__;
	auto result = core::raise<core::HttpError, int>(
		"an error", line_no, __FUNCTION__, __FILE__
	);

	ASSERT_EQ(result.err.type, core::HttpError);
	ASSERT_EQ(result.err.msg, "an error");
	ASSERT_EQ(result.err.line, line_no);
	ASSERT_EQ(result.err.func, __FUNCTION__ );
	ASSERT_EQ(result.err.file, __FILE__);
}
