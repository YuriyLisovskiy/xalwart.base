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
	auto result = Result<int>(2020);
	ASSERT_FALSE(result.err);
	ASSERT_EQ(result.value, 2020);
}

TEST(TestCase_Result, ConstructFromPointerToValue)
{
	auto result = Result(new float(10.1f));
	ASSERT_FALSE(result.err);
	ASSERT_EQ(*result.value, 10.1f);
	delete result.value;
}

TEST(TestCase_Result, operator_bool_ValueTrue)
{
	ASSERT_TRUE(Result<int>(10).operator bool());
}

TEST(TestCase_Result, operator_not_ErrorFalse)
{
	ASSERT_FALSE(!Result<int>(Error(HttpError, "msg")));
}

TEST(TestCase_Result, operator_not_ValueFalse)
{
	ASSERT_FALSE(!Result<int>(10).operator bool());
}

TEST(TestCase_Result, operator_bool_ErrorTrue)
{
	ASSERT_TRUE(Result<int>(Error(HttpError, "msg")));
}

TEST(TestCase_Result, catch_Error)
{
	auto error = Result<int>(Error(HttpError, "an error"));

	ASSERT_TRUE(error.err);
	ASSERT_TRUE(error.catch_(HttpError));

	ASSERT_FALSE(error.catch_(None));
	ASSERT_FALSE(error.catch_(EntityTooLargeError));
	ASSERT_FALSE(error.catch_(FileDoesNotExistError));
	ASSERT_FALSE(error.catch_(PermissionDenied));
	ASSERT_FALSE(error.catch_(NotFound));
	ASSERT_FALSE(error.catch_(InternalServerError));
	ASSERT_FALSE(error.catch_(RequestTimeout));
	ASSERT_FALSE(error.catch_(SuspiciousOperation));
	ASSERT_FALSE(error.catch_(DisallowedHost));
	ASSERT_FALSE(error.catch_(DisallowedRedirect));
}

TEST(TestCase_Result, catch_EntityTooLargeErrorFromHttpErrorGroup)
{
	auto result = raise<EntityTooLargeError, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(EntityTooLargeError));
	ASSERT_TRUE(result.catch_(HttpError));
}

TEST(TestCase_Result, catch_FileDoesNotExistErrorFromHttpErrorGroup)
{
	auto result = raise<FileDoesNotExistError, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(FileDoesNotExistError));
	ASSERT_TRUE(result.catch_(HttpError));
}

TEST(TestCase_Result, catch_PermissionDeniedFromHttpErrorGroup)
{
	auto result = raise<PermissionDenied, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(PermissionDenied));
	ASSERT_TRUE(result.catch_(HttpError));
}

TEST(TestCase_Result, catch_NotFoundFromHttpErrorGroup)
{
	auto result = raise<NotFound, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(NotFound));
	ASSERT_TRUE(result.catch_(HttpError));
}

TEST(TestCase_Result, catch_InternalServerErrorFromHttpErrorGroup)
{
	auto result = raise<InternalServerError, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(InternalServerError));
	ASSERT_TRUE(result.catch_(HttpError));
}

TEST(TestCase_Result, catch_RequestTimeoutFromHttpErrorGroup)
{
	auto result = raise<RequestTimeout, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(RequestTimeout));
	ASSERT_TRUE(result.catch_(HttpError));
}

TEST(TestCase_Result, catch_SuspiciousOperationFromHttpErrorGroup)
{
	auto result = raise<SuspiciousOperation, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(SuspiciousOperation));
	ASSERT_TRUE(result.catch_(HttpError));
}

TEST(TestCase_Result, catch_DisallowedHostFromHttpErrorGroup)
{
	auto result = raise<DisallowedHost, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(DisallowedHost));
	ASSERT_TRUE(result.catch_(HttpError));
}

TEST(TestCase_Result, catch_DisallowedRedirectFromHttpErrorGroup)
{
	auto result = raise<DisallowedRedirect, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(DisallowedRedirect));
	ASSERT_TRUE(result.catch_(HttpError));
}

TEST(TestCase_Result, catch_DisallowedHostFromSuspiciousOperationGroup)
{
	auto result = raise<DisallowedHost, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(DisallowedHost));
	ASSERT_TRUE(result.catch_(SuspiciousOperation));
	ASSERT_TRUE(result.catch_(HttpError));
}

TEST(TestCase_Result, catch_DisallowedRedirectFromSuspiciousOperationGroup)
{
	auto result = raise<DisallowedRedirect, int>("an error");
	ASSERT_TRUE(result.err);
	ASSERT_TRUE(result.catch_(DisallowedRedirect));
	ASSERT_TRUE(result.catch_(SuspiciousOperation));
	ASSERT_TRUE(result.catch_(HttpError));
}

TEST(TestCase_Result, forward_err)
{
	auto line_no = __LINE__;
	auto result = Result<int>(
		Error(HttpError, "an error", line_no, __FUNCTION__, __FILE__)
	);

	ASSERT_EQ(result.err.type, HttpError);
	ASSERT_EQ(result.err.msg, "an error");
	ASSERT_EQ(result.err.line, line_no);
	ASSERT_EQ(result.err.func, __FUNCTION__ );
	ASSERT_EQ(result.err.file, __FILE__);

	auto forwarded = result.forward_err<double>();
	ASSERT_EQ(forwarded.err.type, HttpError);
	ASSERT_EQ(forwarded.err.msg, "an error");
	ASSERT_EQ(forwarded.err.line, line_no);
	ASSERT_EQ(forwarded.err.func, __FUNCTION__ );
	ASSERT_EQ(forwarded.err.file, __FILE__);
}

TEST(TestCase_Result, forward_err_WithPoinerType)
{
	auto line_no = __LINE__;
	auto result = Result<int*>(
		Error(HttpError, "an error", line_no, __FUNCTION__, __FILE__)
	);

	auto forwarded = result.forward_err<double>();
	ASSERT_EQ(forwarded.err.type, HttpError);
	ASSERT_EQ(forwarded.err.msg, "an error");
	ASSERT_EQ(forwarded.err.line, line_no);
	ASSERT_EQ(forwarded.err.func, __FUNCTION__ );
	ASSERT_EQ(forwarded.err.file, __FILE__);
}

TEST(TestCase_Result, null_OperatorBoolFalse)
{
	ASSERT_FALSE(Result<int>::null().operator bool());
}

TEST(TestCase_Result, null_OperatorNotTrue)
{
	ASSERT_TRUE(!Result<int>::null());
}

TEST(TestCase_raise, WithMessageOnly)
{
	auto result = raise<HttpError, int>("an error");

	ASSERT_TRUE(result.err);
	ASSERT_EQ(result.err.type, HttpError);
	ASSERT_EQ(result.err.msg, "an error");
}

TEST(TestCase_raise, Full)
{
	auto line_no = __LINE__;
	auto result = raise<HttpError, int>(
		"an error", line_no, __FUNCTION__, __FILE__
	);

	ASSERT_EQ(result.err.type, HttpError);
	ASSERT_EQ(result.err.msg, "an error");
	ASSERT_EQ(result.err.line, line_no);
	ASSERT_EQ(result.err.func, __FUNCTION__ );
	ASSERT_EQ(result.err.file, __FILE__);
}
