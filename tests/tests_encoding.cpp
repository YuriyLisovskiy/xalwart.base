/**
 * tests_encoding.cpp
 *
 * Copyright (c) 2019, 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../src/encoding.h"
#include "../src/exceptions.h"

using namespace xw;


TEST(TestCase_encoding, _escape_char_NotReserved)
{
	std::ostringstream ss;
	encoding::escape_char(ss, 'A');
	encoding::escape_char(ss, 'b');
	encoding::escape_char(ss, '7');
	encoding::escape_char(ss, '-');
	encoding::escape_char(ss, '_');
	encoding::escape_char(ss, '.');
	encoding::escape_char(ss, '!');
	encoding::escape_char(ss, '~');
	encoding::escape_char(ss, '*');
	encoding::escape_char(ss, '\'');
	encoding::escape_char(ss, '(');
	encoding::escape_char(ss, ')');
	std::string expected = "Ab7-_.!~*'()";
	auto actual = ss.str();
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_encoding, _escape_char_Reserved)
{
	std::ostringstream ss;
	encoding::escape_char(ss, ';');
	encoding::escape_char(ss, ':');
	encoding::escape_char(ss, '@');
	encoding::escape_char(ss, '&');
	encoding::escape_char(ss, '=');
	encoding::escape_char(ss, '+');
	encoding::escape_char(ss, '$');
	encoding::escape_char(ss, ',');
	encoding::escape_char(ss, '/');
	encoding::escape_char(ss, '?');
	encoding::escape_char(ss, '#');
	encoding::escape_char(ss, '[');
	encoding::escape_char(ss, ']');
	std::string expected = "%3B%3A%40%26%3D%2B%24%2C%2F%3F%23%5B%5D";
	auto actual = ss.str();
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_encoding, _escape_char_Safe)
{
	std::string safe = "$";
	std::ostringstream ss;
	encoding::escape_char(ss, ';', safe);
	encoding::escape_char(ss, '$', safe);
	std::string expected = "%3B$";
	auto actual = ss.str();
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_encoding, quote)
{
	std::string expected = "%C5%A0";
	auto actual = encoding::quote("Š");
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_encoding, quote_Safe)
{
	std::string safe = "Š";
	std::string expected = "Š%C2%8F";
	auto actual = encoding::quote("Š\u008F", safe);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_encoding, encode_ascii_StrictMode)
{
	std::string expected;
	for (long i = 0; i <= 127; i++)
	{
		expected += (char)i;
	}

	auto actual = encoding::encode_ascii(expected, encoding::Mode::Strict);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_encoding, encode_ascii_StrictModeThrowEncodingErrorCharIsGreaterThan127)
{
	ASSERT_THROW(
		encoding::encode_ascii(std::string(1, (char)128), encoding::Mode::Strict),
		EncodingError
	);
}

TEST(TestCase_encoding, encode_ascii_StrictModeThrowEncodingErrorCharIsLessThan0)
{
	ASSERT_THROW(
		encoding::encode_ascii(std::string(1, (char)-1), encoding::Mode::Strict),
		EncodingError
	);
}

TEST(TestCase_encoding, encode_ascii_IgnoreMode)
{
	std::string expected;
	for (long i = 0; i <= 127; i++)
	{
		expected += (char)i;
	}

	auto actual = encoding::encode_ascii(expected, encoding::Mode::Ignore);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_encoding, encode_ascii_IgnoreModeCharIsGreaterThan127)
{
	auto actual = encoding::encode_ascii(std::string(1, (char)128), encoding::Mode::Ignore);
	ASSERT_EQ("", actual);
}

TEST(TestCase_encoding, encode_ascii_IgnoreModeCharIsLessThan0)
{
	auto actual = encoding::encode_ascii(std::string(1, (char)-1), encoding::Mode::Ignore);
	ASSERT_EQ("", actual);
}

TEST(TestCase_encoding, encode_ascii_ReplaceMode)
{
	std::string expected;
	for (long i = 0; i <= 127; i++)
	{
		expected += (char)i;
	}

	auto actual = encoding::encode_ascii(expected, encoding::Mode::Replace);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_encoding, encode_ascii_ReplaceModeCharIsGreaterThan127)
{
	auto actual = encoding::encode_ascii(std::string(1, (char)128), encoding::Mode::Replace);
	ASSERT_EQ("?", actual);
}

TEST(TestCase_encoding, encode_ascii_ReplaceModeCharIsLessThan0)
{
	auto actual = encoding::encode_ascii(std::string(1, (char)-1), encoding::Mode::Replace);
	ASSERT_EQ("?", actual);
}

TEST(TestCase_encoding, encode_iso_8859_1_StrictMode)
{
	std::string input = "¡¢£¤¥¦§¨©ª«¬®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ";
	std::string expected = "\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff";
	input = "\x01\x02\x03\x04\x05\x06\x07\x08\t\n\x0b\x0c\r\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~" + input;
	expected = "\x01\x02\x03\x04\x05\x06\x07\x08\t\n\x0b\x0c\r\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~" + expected;

	auto actual = encoding::encode_iso_8859_1(input, encoding::Mode::Strict);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_encoding, encode_iso_8859_1_StrictModeThrowEncodingErrorCharIsGreaterThan255)
{
	ASSERT_THROW(
		encoding::encode_iso_8859_1("Ž", encoding::Mode::Strict),
		EncodingError
	);
}

TEST(TestCase_encoding, encode_iso_8859_1_IgnoreMode)
{
	std::string input = "¡¢£¤¥¦§¨©ª«¬®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ";
	std::string expected = "\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff";
	input = "\x01\x02\x03\x04\x05\x06\x07\x08\t\n\x0b\x0c\r\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~" + input;
	expected = "\x01\x02\x03\x04\x05\x06\x07\x08\t\n\x0b\x0c\r\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~" + expected;

	auto actual = encoding::encode_iso_8859_1(input, encoding::Mode::Ignore);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_encoding, encode_iso_8859_1_IgnoreModeCharIsGreaterThan255)
{
	auto actual = encoding::encode_iso_8859_1("Ž", encoding::Mode::Ignore);
	ASSERT_EQ("", actual);
}

TEST(TestCase_encoding, encode_iso_8859_1_ReplaceMode)
{
	std::string input = "¡¢£¤¥¦§¨©ª«¬®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ";
	std::string expected = "\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff";
	input = "\x01\x02\x03\x04\x05\x06\x07\x08\t\n\x0b\x0c\r\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~" + input;
	expected = "\x01\x02\x03\x04\x05\x06\x07\x08\t\n\x0b\x0c\r\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~" + expected;

	auto actual = encoding::encode_iso_8859_1(input, encoding::Mode::Replace);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_encoding, encode_iso_8859_1_ReplaceModeCharIsGreaterThan255)
{
	auto actual = encoding::encode_iso_8859_1("Ž", encoding::Mode::Replace);
	ASSERT_EQ("?", actual);
}

TEST(TestCase_encoding, encode_iso_8859_1_StrictModeZeroChar)
{
	auto actual = encoding::encode_iso_8859_1("\0", encoding::Mode::Strict);
	ASSERT_EQ("", actual);
}

TEST(TestCase_encoding, encode_iso_8859_1_IgnoreModeZeroChar)
{
	auto actual = encoding::encode_iso_8859_1("\0", encoding::Mode::Ignore);
	ASSERT_EQ("", actual);
}

TEST(TestCase_encoding, encode_iso_8859_1_ReplaceModeZeroChar)
{
	auto actual = encoding::encode_iso_8859_1("\0", encoding::Mode::Replace);
	ASSERT_EQ("", actual);
}
