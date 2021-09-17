/**
 * _def_.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Definitions of the 'abc' module.
 */

#pragma once

// Module definitions.
#include "../_def_.h"

// xw::abc
#define __ABC_BEGIN__ __MAIN_NAMESPACE_BEGIN__ namespace abc {
#define __ABC_END__ } __MAIN_NAMESPACE_END__

// xw::abc::base
#define __ABC_BASE_BEGIN__ __ABC_BEGIN__ namespace base {
#define __ABC_BASE_END__ } __ABC_END__

// xw::abc::render
#define __ABC_RENDER_BEGIN__ __ABC_BEGIN__ namespace render {
#define __ABC_RENDER_END__ } __ABC_END__
