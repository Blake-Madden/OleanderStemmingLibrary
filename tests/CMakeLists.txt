#############################################################################
# Name:        CMakeListst.txt
# Purpose:     Unit test runner for Oleander Stemming Library
# Author:      Blake Madden
# Created:     2022-11-08
# Copyright:   (c) 2022 Blake Madden
# Licence:     3-Clause BSD licence
#############################################################################

cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(OleanderStemTestRunner)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# https://github.com/bilke/cmake-modules/blob/master/CodeCoverage.cmake
if(CMAKE_COMPILER_IS_GNUCXX)
    LIST(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules")
    INCLUDE(CodeCoverage)
    APPEND_COVERAGE_COMPILER_FLAGS()
    SETUP_TARGET_FOR_COVERAGE_LCOV(NAME ${CMAKE_PROJECT_NAME}_coverage
                                   EXECUTABLE ${CMAKE_PROJECT_NAME}
                                   DEPENDENCIES ${CMAKE_PROJECT_NAME})
endif()

# place Catch2 at the same folder level as this repo if it isn't installed
# (you will need to do this on Windows or macOS or if version 3 of Catch2 isn't installed)
get_filename_component(_fullpath "${_dir}" REALPATH)
if(EXISTS "${_fullpath}" AND EXISTS "${_fullpath}/../../Catch2")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../Catch2 ${CMAKE_CURRENT_BINARY_DIR}/Catch2)
else()
    # ...otherwise, see if it is installed
    find_package(Catch2 3 REQUIRED)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(${CMAKE_PROJECT_NAME} stemmingtests.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Catch2::Catch2WithMain)

# Set definitions, warnings, and optimizations
if(MSVC)
    # /Zc:__cplusplus tells MSVC to set the C++ version what we are
    # actually compiling as. (This is needed for UTF8CPP.)

    # /MP enables multi-core build support, speeding up compilation time.

    # /W3 cranks up the warning level, /WX treats all warnings as error.
    # Note that simply using /W4 causes a warning that it is overriding
    # /W3, and then that turns into an error because of /W4. So /W3 is the
    # highest you can go with /WX.
    target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC /Zc:__cplusplus /MP /W3 /WX
                           $<$<CONFIG:Debug>:/Od> $<$<CONFIG:Release>:/O2>)
endif()

# load the test cases into the runner
include(CTest)
include(Catch)
catch_discover_tests(${CMAKE_PROJECT_NAME})

message(STATUS "Copying test files...")
add_custom_command(TARGET ${CMAKE_PROJECT_NAME}
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/snowball-data $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>)
