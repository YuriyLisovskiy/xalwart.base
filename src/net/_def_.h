/**
 * net/_def_.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Definitions of `net` module.
 */

#pragma once

// Module definitions.
#include "../_def_.h"

// xw::net
#define __NET_BEGIN__ __MAIN_NAMESPACE_BEGIN__ namespace net {
#define __NET_END__ } __MAIN_NAMESPACE_END__

// xw::net::meta
#define __NET_META_BEGIN__ __NET_BEGIN__ namespace meta {
#define __NET_META_END__ } __NET_END__

// xw::net::abc
#define __NET_ABC_BEGIN__ __NET_BEGIN__ namespace abc {
#define __NET_ABC_END__ } __NET_END__
