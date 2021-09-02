/**
 * unicode/_def_.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Definitions of 'unicode' module.
 */

#pragma once

#include "../_def_.h"

// xw::unicode
#define __UNICODE_BEGIN__ __MAIN_NAMESPACE_BEGIN__ namespace unicode {
#define __UNICODE_END__ } __MAIN_NAMESPACE_END__

__UNICODE_BEGIN__

// Characters below RuneSelf are represented as themselves in a single byte.
static inline constexpr const uint32_t BYTE_SELF = 0x80;

static inline constexpr const int32_t MAX_WCHAR_T = 0x10ffff;

static inline constexpr const int32_t UPPER_LOWER = MAX_WCHAR_T + 1;

static inline constexpr const int32_t MAX_ASCII = 0x7f;

static inline constexpr const uint32_t MAX_LATIN_1 = 0x00FF;

static inline constexpr const int32_t REPLACEMENT_CHAR = 0xfffd;

enum class Case
{
	Upper = 0, Lower, Title, Max
};

using Delta = wchar_t[(int)Case::Max];

// Represents a range of Unicode code points for simple (one
// code point to one code point) case conversion.
// The range runs from `lo` to `hi` inclusive, with a fixed `stride` of 1. Deltas
// are the number to add to the code point to reach the code point for a
// different case for that character. They may be negative. If zero, it
// means the character is in the corresponding case. There is a special
// case representing sequences of alternating corresponding Upper and Lower
// pairs. It appears with a fixed Delta of
//	{UPPER_LOWER, UPPER_LOWER, UPPER_LOWER}
// The constant UPPER_LOWER has an otherwise impossible delta value.
//
// The original implementation is in Golang 1.15.8: unicode/letter.go
struct CaseRange
{
	uint32_t lo;
	uint32_t hi;
	Delta delta;
};

// Represents of a range of 16-bit Unicode code points.
// The range runs from `lo` to `hi` inclusive and has the specified `stride`.
//
// The original implementation is in Golang 1.15.8: unicode/letter.go
struct Range16
{
	uint16_t lo;
	uint16_t hi;
	uint16_t stride;
};

// Represents of a range of Unicode code points and is used when one or
// more of the values will not fit in 16 bits. The range runs from `lo` to `hi`
// inclusive and has the specified `stride`. `lo` and `hi` must always be >= 1<<16.
//
// The original implementation is in Golang 1.15.8: unicode/letter.go
struct Range32
{
	uint32_t lo;
	uint32_t hi;
	uint32_t stride;
};

// Defines a set of Unicode code points by listing the ranges of
// code points within the set. The ranges are listed in two vectors
// to save space: a slice of 16-bit ranges and a slice of 32-bit ranges.
// The two vectors must be in sorted order and non-overlapping.
// Also, R32 should contain only values >= 0x10000 (1<<16).
//
// The original implementation is in Golang 1.15.8: unicode/letter.go
struct RangeTable
{
	std::vector<Range16> r16;
	std::vector<Range32> r32;
	int latin_offset;
};

__UNICODE_END__
