cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

set(FRAMEWORK_NAME "xalwart")
set(LIBRARY_NAME "${FRAMEWORK_NAME}.core")
set(LIBRARY_VERSION "0.0.1")

project(${LIBRARY_NAME})

function(remove_dirs SRC_LIST)
    foreach(entry ${SRC_LIST})
        if (IS_DIRECTORY ${entry})
            list(REMOVE_ITEM SRC_LIST ${entry})
        endif()
    endforeach()
endfunction(remove_dirs)

function(print SRC_LIST)
    foreach(entry ${SRC_LIST})
        message(${entry})
    endforeach(entry)
endfunction(print)

set(LIB_SRC_DIR ${PROJECT_SOURCE_DIR}/src)
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true ${LIB_SRC_DIR}/*.h ${LIB_SRC_DIR}/*.cpp)
remove_dirs(SOURCES)

# Build shared library.
set(FULL_LIBRARY_NAME ${LIBRARY_NAME}-${LIBRARY_VERSION})
add_library(${FULL_LIBRARY_NAME} SHARED ${SOURCES})

# Install library.
include(GNUInstallDirs)
install(
    TARGETS ${FULL_LIBRARY_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

add_custom_command(
    TARGET ${FULL_LIBRARY_NAME}
    POST_BUILD
    COMMAND XW_ROOT_DIR=${PROJECT_SOURCE_DIR}/src XW_LIB_NAME=${LIBRARY_NAME} bash ${PROJECT_SOURCE_DIR}/scripts/install.sh
)

#file(GLOB FILES_AND_DIRS_TO_DEPLOY LIST_DIRECTORIES true "${LIB_SRC_DIR}/*")
#foreach(ITEM ${FILES_AND_DIRS_TO_DEPLOY})
#    if(IS_DIRECTORY ${ITEM})
#        list(APPEND DIRS_TO_DEPLOY ${ITEM})
#    else()
#        list(APPEND FILES_TO_DEPLOY ${ITEM})
#    endif()
#endforeach()
#
#install(FILES ${FILES_TO_DEPLOY} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_NAME})
#install(DIRECTORY ${DIRS_TO_DEPLOY} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_NAME})

#file(GLOB_RECURSE CPP_FILES_TO_REMOVE ${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_NAME}/*.cpp)
#
#file(REMOVE ${CPP_FILES_TO_REMOVE})

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_subdirectory(tests)
endif()
