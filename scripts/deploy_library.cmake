# Required parameters:
#   PROJECT_SOURCE_DIR
#   CMAKE_BINARY_DIR
#   FRAMEWORK_NAME
#   LIBRARY_NAME
#   LIBRARY_VERSION
#   DEPLOY_DIR

# Check if arguments were defined.
if (NOT DEFINED PROJECT_SOURCE_DIR)
    message(SEND_ERROR "Missing PROJECT_SOURCE_DIR")
endif()
if (NOT DEFINED CMAKE_BINARY_DIR)
    message(SEND_ERROR "Missing CMAKE_BINARY_DIR")
endif()
if (NOT DEFINED FRAMEWORK_NAME)
    message(SEND_ERROR "Missing FRAMEWORK_NAME")
endif()
if (NOT DEFINED LIBRARY_NAME)
    message(SEND_ERROR "Missing LIBRARY_NAME")
endif()
if (NOT DEFINED LIBRARY_VERSION)
    message(SEND_ERROR "Missing LIBRARY_VERSION")
endif()
if (NOT DEFINED DEPLOY_DIR)
    message(SEND_ERROR "Missing DEPLOY_DIR")
endif()

function(recreate_dir DIR_NAME)
    if (EXISTS ${DIR_NAME})
        file(REMOVE_RECURSE ${DIR_NAME})
    endif()
    file(MAKE_DIRECTORY ${DIR_NAME})
endfunction(recreate_dir)

set(LIB_DIR ${DEPLOY_DIR}/lib/${FRAMEWORK_NAME})
set(INCLUDE_DIR ${DEPLOY_DIR}/include/${LIBRARY_NAME})

# Clean deploy directories if exists and recreate them.
if (NOT EXISTS ${LIB_DIR})
    file(MAKE_DIRECTORY ${LIB_DIR})
endif()
recreate_dir(INCLUDE_DIR)

# Copy framework's files.
file(GLOB LIB_SRC LIST_DIRECTORIES true ${PROJECT_SOURCE_DIR}/src/*)
file(
    COPY ${LIB_SRC}
    DESTINATION ${INCLUDE_DIR}
)

# Remove all .cpp and .txt files.
file(
    GLOB_RECURSE FILES_TO_REMOVE
    LIST_DIRECTORIES true
    ${INCLUDE_DIR}/*.txt ${INCLUDE_DIR}/*.cpp
)
if (FILES_TO_REMOVE)
    file(REMOVE ${FILES_TO_REMOVE})
endif()

# Get library file according to current OS.
if (WIN32)
    set(LIB_FILE ${LIBRARY_NAME}-${LIBRARY_VERSION}.lib)
else()
    set(LIB_FILE lib${LIBRARY_NAME}-${LIBRARY_VERSION}.so)
endif()

# Copy library.
file(
    COPY ${CMAKE_BINARY_DIR}/${LIB_FILE}
    DESTINATION ${LIB_DIR}
)
