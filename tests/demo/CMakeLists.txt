#############################################################################
# Name:        CMakeListst.txt
# Purpose:     Demo for Oleander Stemming
# Author:      Blake Madden
# Created:     2023-06-04
# Copyright:   (c) 2023 Blake Madden
# Licence:     3-Clause BSD licence
#############################################################################

cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(OleanDemo)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(${CMAKE_PROJECT_NAME} stemdemo.cpp)
