set(LIB_DIRECTORY ${PROJECT_SOURCE_DIR}/src)
file(GLOB_RECURSE LIB_SOURCES LIST_DIRECTORIES true ${LIB_DIRECTORY}/*.h ${LIB_DIRECTORY}/*.cpp)
remove_dirs(SOURCES)

set(CMAKE_CXX_FLAGS "-pthread")

set(BINARY unittests)

function(add_tests SUB_DIR SUB_NAME)
    set(TESTS_DIR ${PROJECT_SOURCE_DIR}/tests/${SUB_DIR})
    file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true ${TESTS_DIR}*.cpp)
    remove_dirs(SOURCES)
    list(FILTER SOURCES EXCLUDE REGEX ".*main.cpp$")
    set(FULL_BIN ${BINARY}-${SUB_NAME})
    add_executable(${FULL_BIN} ${LIB_SOURCES} ${SOURCES} ${TESTS_DIR}/main.cpp)
    target_link_libraries(${FULL_BIN} PUBLIC gtest stdc++fs)
endfunction()

function(add_sub_tests SUB_NAME)
    add_tests(${SUB_NAME}/ ${SUB_NAME})
endfunction(add_sub_tests)

add_tests("" all)
add_sub_tests(collections)
add_sub_tests(exceptions)
add_sub_tests(object)
add_sub_tests(types)
