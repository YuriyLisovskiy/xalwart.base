/**
 * unicode/letter.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Unicode utilities.
 *
 * Implementation is based on Golang 1.15.8: unicode/letter.go
 */

#pragma once

// C++ libraries.
#include <vector>

// Module definitions.
#include "./_def_.h"


__UNICODE_BEGIN__

// TESTME: simple_fold
//
// Iterates over Unicode code points equivalent under
// the Unicode-defined simple case folding. Among the code points
// equivalent to wide char (including wide char itself), `simple_fold` returns the
// smallest wide char > `c` if one exists, or else the smallest wide char >= 0.
// If `c` is not a valid Unicode code point, `simple_fold(c)` returns `c`.
//
// For example:
//	simple_fold('A') = 'a'
//	simple_fold('a') = 'A'
//
//	simple_fold('K') = 'k'
//	simple_fold('k') = '\u212A' (Kelvin symbol, K)
//	simple_fold('\u212A') = 'K'
//
//	simple_fold('1') = '1'
//
//	simple_fold(-2) = -2
//
extern uint32_t simple_fold(uint32_t c);

// TESTME: _to
extern std::pair<uint32_t, bool> _to(Case case_, uint32_t c, const std::vector<CaseRange>& case_range);

// TESTME: to
extern uint32_t to(Case case_, uint32_t c);

// TESTME: to_upper
// Maps the wide char to upper case.
extern uint32_t to_upper(uint32_t c);

// TESTME: to_lower
// Maps the wide char to lower case.
extern uint32_t to_lower(uint32_t c);

__UNICODE_END__
