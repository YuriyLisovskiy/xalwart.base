/*
 * Copyright (c) 2020 Yuriy Lisovskiy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>

#include "../../../src/object/object.h"

using namespace xw;

namespace test_namespace
{
	class EmptyObject : public core::object::Object
	{
	};
}

TEST(ObjectTestsCase, EmptyObjectTypeTest)
{
	auto obj = test_namespace::EmptyObject();
	auto type = obj.__type__();

	ASSERT_EQ(type.name(), "EmptyObject");
	ASSERT_EQ(type.namespace_(), "test_namespace");
}
