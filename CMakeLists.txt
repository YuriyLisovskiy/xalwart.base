cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 20)

set(FRAMEWORK_NAME "xalwart")
set(LIBRARY_NAME "${FRAMEWORK_NAME}.core")
set(LIBRARY_VERSION "0.0.1")

project(${LIBRARY_NAME})

set(GNU_INCLUDE_DIR /usr/include)
set(GNU_LIB_DIR /usr/lib)

function(print SRC_LIST)
    foreach(entry ${SRC_LIST})
        message(${entry})
    endforeach(entry)
endfunction(print)

set(LIB_SRC_DIR ${PROJECT_SOURCE_DIR}/src)
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true ${LIB_SRC_DIR}/*.h ${LIB_SRC_DIR}/*.cpp)
foreach(entry ${SOURCES})
    if (IS_DIRECTORY ${entry})
        list(REMOVE_ITEM SOURCES ${entry})
    endif()
endforeach()
list(LENGTH SOURCES SOURCES_COUNT)
message(STATUS "[INFO] Sources found: ${SOURCES_COUNT}")

# Build shared library.
set(FULL_LIBRARY_NAME ${LIBRARY_NAME}-${LIBRARY_VERSION})
add_library(${FULL_LIBRARY_NAME} SHARED ${SOURCES})

# Install library.
install(
    TARGETS ${FULL_LIBRARY_NAME}
    ARCHIVE DESTINATION ${GNU_LIB_DIR}
    LIBRARY DESTINATION ${GNU_LIB_DIR}
)

install(
    DIRECTORY "${LIB_SRC_DIR}/"
    DESTINATION ${GNU_INCLUDE_DIR}/${LIBRARY_NAME}
    FILES_MATCHING
    PATTERN "*.h"
)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_subdirectory(tests)
endif()
