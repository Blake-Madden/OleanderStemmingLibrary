# - Sets the build type for the project
# It defines the following variables:
#   - default_build_type
#   - CMAKE_BUILD_TYPE

# Build types
# ---------------------------------------------------------------------------
# CMAKE_BUILD_TYPE
#
# None (empty)                                      /DWIN32 /D_WINDOWS /W3
#                                                   /GR /EHsc
# Debug             Not optimized   -g              /MDd /Zi /Ob0 /Od /RTC1
# Release           Optimized       -O3 -DNDEBUG    /MD /O2 /Ob2 /DNDEBUG
# RelWithDebInfo    Optimized       -O2 -g          /MD /Zi /O2 /Ob1 /DNDEBUG
#                   Debug symbols   -DNDEBUG
# MinSizeRel        Small binary    -Os -DNDEBUG    /MD /O1 /Ob1 /DNDEBUG
# ---------------------------------------------------------------------------

# Set a default build type if none was specified
if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
    set(default_build_type "Debug")
else()
    set(default_build_type "Release")
endif()

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}"
        CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif()
