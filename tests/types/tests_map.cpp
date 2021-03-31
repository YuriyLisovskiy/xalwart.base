/**
 * types/tests_map.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/types/string.h"
#include "../../src/types/map.h"
#include "../../src/types/fundamental.h"

using namespace xw;


TEST(TestCase_Map, Test_IsMap)
{
	types::Map<obj::Object, types::String> map;
	map.value()[std::make_shared<types::Fundamental<int>>(1)] = std::make_shared<types::String>("Pes");
	map.value()[std::make_shared<types::String>("Hello")] = std::make_shared<types::String>("World");
}
