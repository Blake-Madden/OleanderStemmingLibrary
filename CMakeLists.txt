cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(OleanderStemmingLibrary VERSION 0.1 LANGUAGES CXX)
set(PROJECT_NAME_L oleanderstemminglibrary)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

# Options
OPTION(BUILD_SHARED_LIBS "Build ${PROJECT_NAME}.a rather than ${PROJECT_NAME}.so" OFF)

# -----------------------------------------------------------------------------
# Build settings
# -----------------------------------------------------------------------------

# C++ requirements
# ----------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_COLOR_MAKEFILE ON)

include_directories("${CMAKE_SOURCE_DIR}")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message("-- Configuring clang options")
    set(CMAKE_CXX_FLAGS "-arch x86_64 -std=c++17 -stdlib=libc++ -Wno-deprecated-declarations")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message("-- Configuring gcc options")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")
endif()

# -----------------------------------------------------------------------------
# Create and set target properties
# -----------------------------------------------------------------------------

# Add the library
# ---------------
add_library(${PROJECT_NAME_L} INTERFACE)

# Create an alias
add_library(${PROJECT_NAME}::${PROJECT_NAME_L} ALIAS ${PROJECT_NAME_L})

# Include project directories in target
# -------------------------------------
target_include_directories(${PROJECT_NAME_L}
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# -----------------------------------------------------------------------------
# Installation instructions
# -----------------------------------------------------------------------------
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

install(
    TARGETS
        ${PROJECT_NAME_L}
    EXPORT
        ${PROJECT_NAME_L}-targets
    LIBRARY DESTINATION
        ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION
        ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}
)

set_target_properties(${PROJECT_NAME_L} PROPERTIES EXPORT_NAME ${PROJECT_NAME})

install(
    DIRECTORY
        include/
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR})

# Export the targets to a script
install(EXPORT ${PROJECT_NAME_L}-targets
    FILE
        ${PROJECT_NAME}Targets.cmake
    NAMESPACE
        ${PROJECT_NAME}::
    DESTINATION
        ${INSTALL_CONFIGDIR}
)

# Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION
        ${INSTALL_CONFIGDIR}
)

# Install the config
install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION
        ${INSTALL_CONFIGDIR}
)

# -----------------------------------------------------------------------------
# Export from the build tree
# -----------------------------------------------------------------------------
message(STATUS "Exporting project")

# Allow use of find_package(MyLib)
export(
    EXPORT
        ${PROJECT_NAME_L}-targets
    FILE
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake
    NAMESPACE
        ${PROJECT_NAME}
)

# Register package
export(PACKAGE ${PROJECT_NAME})

message(STATUS "Exporting project - done")

# Testing
add_subdirectory(tests)
