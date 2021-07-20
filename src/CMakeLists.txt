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
add_library(${LIBRARY_NAME} ${SOURCES})

# Install library.
install(
    TARGETS ${LIBRARY_NAME}
    ARCHIVE DESTINATION ${GNU_LIB_DIR}
    LIBRARY DESTINATION ${GNU_LIB_DIR}
)

install(
    DIRECTORY "${LIB_SRC_DIR}/"
    DESTINATION ${GNU_INCLUDE_DIR}/${LIBRARY_NAME}
    FILES_MATCHING
    PATTERN "*.h"
)
