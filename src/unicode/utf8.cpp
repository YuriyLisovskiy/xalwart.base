/**
 * unicode/utf8.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include "./utf8.h"


__UNICODE_UTF8_BEGIN__

inline const uint8_t maskx = 0b00111111;
inline const uint8_t mask2 = 0b00011111;
inline const uint8_t mask3 = 0b00001111;
inline const uint8_t mask4 = 0b00000111;

// The default lowest and highest continuation byte.
inline const uint8_t locb = 0b10000000;
inline const uint8_t hicb = 0b10111111;

// These names of these constants are chosen to give nice alignment in the
// table below. The first nibble is an index into acceptRanges or F for
// special one-byte cases. The second nibble is the unsigned char length or the
// Status for the special one-byte case.
inline const uint8_t xx = 0xF1; // invalid: size 1
inline const uint8_t as = 0xF0; // ASCII: size 1
inline const uint8_t s1 = 0x02; // accept 0, size 2
inline const uint8_t s2 = 0x13; // accept 1, size 3
inline const uint8_t s3 = 0x03; // accept 0, size 3
inline const uint8_t s4 = 0x23; // accept 2, size 3
inline const uint8_t s5 = 0x34; // accept 3, size 4
inline const uint8_t s6 = 0x04; // accept 0, size 4
inline const uint8_t s7 = 0x44; // accept 4, size 4

// first is information about the first byte in a UTF-8 sequence.
inline const uint8_t first[256] = {
	//   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
	as, as, as, as, as, as, as, as, as, as, as, as, as, as, as, as, // 0x00-0x0F
	as, as, as, as, as, as, as, as, as, as, as, as, as, as, as, as, // 0x10-0x1F
	as, as, as, as, as, as, as, as, as, as, as, as, as, as, as, as, // 0x20-0x2F
	as, as, as, as, as, as, as, as, as, as, as, as, as, as, as, as, // 0x30-0x3F
	as, as, as, as, as, as, as, as, as, as, as, as, as, as, as, as, // 0x40-0x4F
	as, as, as, as, as, as, as, as, as, as, as, as, as, as, as, as, // 0x50-0x5F
	as, as, as, as, as, as, as, as, as, as, as, as, as, as, as, as, // 0x60-0x6F
	as, as, as, as, as, as, as, as, as, as, as, as, as, as, as, as, // 0x70-0x7F
	//   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
	xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, // 0x80-0x8F
	xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, // 0x90-0x9F
	xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, // 0xA0-0xAF
	xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, // 0xB0-0xBF
	xx, xx, s1, s1, s1, s1, s1, s1, s1, s1, s1, s1, s1, s1, s1, s1, // 0xC0-0xCF
	s1, s1, s1, s1, s1, s1, s1, s1, s1, s1, s1, s1, s1, s1, s1, s1, // 0xD0-0xDF
	s2, s3, s3, s3, s3, s3, s3, s3, s3, s3, s3, s3, s3, s4, s3, s3, // 0xE0-0xEF
	s5, s6, s6, s6, s7, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, // 0xF0-0xFF
};

// acceptRange gives the range of valid values for the second byte in a UTF-8
// sequence.
struct acceptRange
{
	uint8_t lo; // lowest value for second byte.
	uint8_t hi; // highest value for second byte.
};

// acceptRanges has size 16 to avoid bounds checks in the code that uses it.
inline const acceptRange acceptRanges[16] = {
	{locb, hicb},
	{0xA0, hicb},
	{locb, 0x9F},
	{0x90, hicb},
	{locb, 0x8F}
};

// 'decode_byte' unpacks the first UTF-8 encoding in 'string' and returns
// unsigned character and its width in bytes. If 'string' is empty it returns
// \0 character and 0 as a size.
// Otherwise, if the encoding is invalid, it throws 'EncodingError'.
std::tuple<uint32_t, size_t> decode_symbol(const std::string& s)
{
	auto n = s.size();
	if (n < 1)
	{
		return {'\0', 0};
	}

	auto s0_ = (uint8_t)s[0];
	auto x = first[s0_];
	if (x >= as)
	{
		// The following code simulates an additional check for x == xx and
		// handling the ASCII and invalid cases accordingly. This mask-and-or
		// approach prevents an additional branch.
		auto mask = x << 31 >> 31; // Create 0x0000 or 0xFFFF.
		auto left = s[0] & ~mask;
		auto right = UNICODE_ERROR & mask;
		return {left | right, 1};
	}

	auto sz = (int)(x & 7);
	auto accept = acceptRanges[x >> 4];
	if (n < sz)
	{
		return {UNICODE_ERROR, 1};
	}

	auto s1_ = (uint8_t)s[1];
	if (s1_ < accept.lo || accept.hi < s1_)
	{
		return {UNICODE_ERROR, 1};
	}

	if (sz <= 2) // <= instead of == to help the compiler eliminate some bounds checks
	{
		return {(s0_ & mask2) << 6 | (s1_ & maskx), 2};
	}

	auto s2_ = (uint8_t)s[2];
	if (s2_ < locb || hicb < s2_)
	{
		return {UNICODE_ERROR, 1};
	}

	if (sz <= 3)
	{
		return {(s0_ & mask3) << 12 | (s1_ & maskx)<<6 | (s2_ & maskx), 3};
	}

	auto s3_ = (uint8_t)s[3];
	if (s3_ < locb || hicb < s3_)
	{
		return {UNICODE_ERROR, 1};
	}

	return {(s0_ & mask4) << 18 | (s1_ & maskx) << 12 | (s2_ & maskx) << 6 | (s3_ & maskx), 4};
}

__UNICODE_UTF8_END__
