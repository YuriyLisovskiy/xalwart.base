cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 20)

set(FRAMEWORK_NAME "xalwart")
set(LIBRARY_NAME "${FRAMEWORK_NAME}.base")
set(LIBRARY_VERSION "0.1.0")

project(${LIBRARY_NAME})

set(GNU_INCLUDE_DIR /usr/local/include)
set(GNU_LIB_DIR /usr/local/lib)

if (NOT DEFINED BUILD_LIB)
    set(BUILD_LIB on)
endif()

if (${BUILD_LIB})
    add_subdirectory(src)
endif()

if (NOT DEFINED BUILD_TESTS)
    set(BUILD_TESTS off)
endif()

if (${BUILD_TESTS})
    enable_testing()
    add_subdirectory(tests)
endif()
