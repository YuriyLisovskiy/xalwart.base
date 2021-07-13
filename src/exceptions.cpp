/**
 * exceptions.cpp
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 */

#include "./exceptions.h"

// C++ libraries.
#include <csignal>


__MAIN_NAMESPACE_BEGIN__

void InterruptException::initialize()
{
#if defined(_WIN32) || defined(_WIN64)
	signal(SIGINT, &InterruptException::handle_signal);
	signal(SIGTERM, &InterruptException::handle_signal);
#elif defined(__unix__) || defined(__linux__)
	struct sigaction sig_int_handler{};
	sig_int_handler.sa_handler = InterruptException::handle_signal;
	sigemptyset(&sig_int_handler.sa_mask);
	sig_int_handler.sa_flags = 0;
	sigaction(SIGINT, &sig_int_handler, nullptr);
	sigaction(SIGTERM, &sig_int_handler, nullptr);
//	sigaction(SIGKILL, &sig_int_handler, nullptr);
#else
#error Library is not supported on this platform
#endif
}

__MAIN_NAMESPACE_END__
