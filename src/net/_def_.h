/**
 * net/_def_.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Purpose: net module's definitions.
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
