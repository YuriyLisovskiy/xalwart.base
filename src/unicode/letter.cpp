/**
 * unicode/letter.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include "./letter.h"

// Base libraries.
#include "./tables.h"
#include "../string_utils.h"


__UNICODE_BEGIN__

wchar_t simple_fold(wchar_t c)
{
	if (c < 0 || c > MAX_WCHAR_T)
	{
		return c;
	}

	if ((int)c < ASCII_FOLD.size())
	{
		return ASCII_FOLD[c];
	}

	// Consult CASE_ORBIT table for special cases.
	size_t lo = 0;
	auto hi = CASE_ORBIT.size();

	while (lo < hi)
	{
		auto m = lo + (hi - lo) / 2;
		if (CASE_ORBIT[m].from < c)
		{
			lo = m + 1;
		}
		else
		{
			hi = m;
		}
	}

	if (lo < CASE_ORBIT.size() && CASE_ORBIT[lo].from == c)
	{
		return CASE_ORBIT[lo].to;
	}

	// No folding specified. This is a one- or two-element
	// equivalence class containing rune and to_lower(wchar_t)
	// and to_upper(wchar_t) if they are different from rune.
	auto l = to_lower(c);
	if (l != c)
	{
		return l;
	}

	return to_upper(c);
}

std::pair<wchar_t, bool> _to(Case case_, wchar_t c, const std::vector<CaseRange>& case_range)
{
	if ((int)case_ < 0 || Case::Max <= case_)
	{
		return {REPLACEMENT_CHAR, false};
	}

	// binary search over ranges
	size_t lo = 0;
	auto hi = case_range.size();
	while (lo < hi)
	{
		auto m = lo + (hi - lo) / 2;
		auto cr = case_range[m];
		if (cr.lo <= c && c <= cr.hi)
		{
			auto delta = cr.delta[(int)case_];
			if (delta > MAX_WCHAR_T)
			{
				// In an Upper-Lower sequence, which always starts with
				// an Upper letter, the real deltas always look like:
				//	{0, 1, 0}    Upper (Lower is next)
				//	{-1, 0, -1}  Lower (Upper, Title are previous)
				// The characters at even offsets from the beginning of the
				// sequence are upper case; the ones at odd offsets are lower.
				// The correct mapping can be done by clearing or setting the low
				// bit in the sequence offset.
				// The constants Upper and Title are even while Lower
				// is odd so we take the low bit from `case_`.
				return {cr.lo + ((c - cr.lo) & ~1 | (int)case_ & 1), true};
			}

			return {c + delta, true};
		}

		if (c < cr.lo)
		{
			hi = m;
		}
		else
		{
			lo = m + 1;
		}
	}

	return {c, false};
}

wchar_t to(Case case_, wchar_t c)
{
	auto [r, _] = _to(case_, c, CASE_RANGES);
	return r;
}

wchar_t to_upper(wchar_t c)
{
	if (c <= MAX_ASCII)
	{
		if ('a' <= c && c <= 'z')
		{
			c -= 'a' - 'A';
		}

		return c;
	}

	return to(Case::Upper, c);
}

wchar_t to_lower(wchar_t c)
{
	if (c <= MAX_ASCII)
	{
		if ('A' <= c && c <= 'Z')
		{
			c += 'a' - 'A';
		}

		return c;
	}

	return to(Case::Lower, c);
}

__UNICODE_END__
