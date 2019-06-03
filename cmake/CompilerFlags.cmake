# - Sets the compiler flags for the build system
# Creates the function 'add_target_compiler_flags' which should be called on
#   any targets.

# Compiler IDs
# ------------------------
# CMAKE_<LANG>_COMPILER_ID
#
# Absoft                = Absoft Fortran (absoft.com)
# ADSP                  = Analog VisualDSP++ (analog.com)
# AppleClang            = Apple Clang (apple.com)
# Clang                 = LLVM Clang (clang.llvm.org)
# Cray                  = Cray Compiler (cray.com)
# Embarcadero, Borland  = Embarcadero (embarcadero.com)
# G95                   = G95 Fortran (g95.org)
# GNU                   = GNU Compiler Collection (gcc.gnu.org)
# HP                    = Hewlett-Packard Compiler (hp.com)
# Intel                 = Intel Compiler (intel.com)
# MIPSpro               = SGI MIPSpro (sgi.com)
# MSVC                  = Microsoft Visual Studio (microsoft.com)
# OpenWatcom            = Open Watcom (openwatcom.org)
# PGI                   = The Portland Group (pgroup.com)
# PathScale             = PathScale (pathscale.com)
# SDCC                  = Small Device C Compiler (sdcc.sourceforge.net)
# SunPro                = Oracle Solaris Studio (oracle.com)
# TI                    = Texas Instruments (ti.com)
# TinyCC                = Tiny C Compiler (tinycc.org)
# XL, VisualAge, zOS    = IBM XL (ibm.com)
# ------------------------

# Passing flags to the compiler or linker
# -----------------------------------------------------------------------------
# CMAKE_C_FLAGS / CMAKE_CXX_FLAGS   Used by the compiler
# CMAKE_EXE_LINKER_FLAGS            Used by linker when linking executables
# CMAKE_SHARED_LINKER_FLAGS         Used by linker when linking shared obj libs
# CMAKE_MODULE_LINKER_FLAGS         Used by linker when linking modules
# CMAKE_STATIC_LINKER_FLAGS         Used by linker when linking static obj libs
# -----------------------------------------------------------------------------

# Toggle to treat warnings as errors
OPTION(WERROR "Treat warnings as errors" ON)

# Ensure latest compiler versions
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "7")
        message(FATAL_ERROR "Insufficient gcc version")
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.9")
        message(FATAL_ERROR "Insufficient Clang version")
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "AppleClang")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "8.1.0")
        message(FATAL_ERROR "Insufficient AppleClang version")
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    if(MSVC_VERSION LESS 1920)
        message(FATAL_ERROR "Insufficient MSVC version")
    endif()
endif()

# OS specific flags
# -----------------
# Shared libraries
if(IOS OR ANDROID)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries")
#else()
#    set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries")
endif()

# Tests and samples
if(IOS OR ANDROID OR WINDOWS_STORE OR WINDOWS_PHONE)
    set(BUILD_TESTS OFF CACHE BOOL "Build tests")
    set(BUILD_SAMPLES OFF CACHE BOOL "Build sample applications")
#else()
    #set(BUILD_TESTS ON CACHE BOOL "Build tests")
    #set(BUILD_SAMPLES ON CACHE BOOL "Build sample applications")
endif()

# Compiler specific flags
# -----------------------
# Set global compiler flags
# It defines the following variables
#   - CMAKE_CXX_FLAGS
#   - WARNINGS: To be added to the target with target_compile_options
#   - LINUX_SUPPRESSIONS (conditional)
#   - OSX_SUPPRESSIONS (conditional)
#   - CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY (conditional)
#   - CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD (conditional)
#   - CMAKE_STATIC_LINKER_FLAGS (conditional)
#   - CMAKE_CXX_FLAGS_DEBUG (conditional)
#   - CMAKE_CXX_FLAGS_MINSIZEREL (conditional)
#   - CMAKE_CXX_FLAGS_RELEASE (conditional)
#   - CMAKE_CXX_FLAGS_RELWITHDEBINFO (conditional)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR IOS)
    message(STATUS "Setting clang compiler flags")

    if(ANDROID)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-pedantic -Wno-attributes -Wno-pointer-arith")
    elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
        set(WARNINGS -Wall -Wextra -Wcast-qual -Wconversion -Wformat=2 -Winit-self -Winvalid-pch -Wmissing-format-attribute -Wmissing-include-dirs -Wpacked -Wredundant-decls)
        set(LINUX_SUPPRESSIONS -Wno-overloaded-virtual -Wno-sign-conversion -Wno-deprecated -Wno-unknown-pragmas -Wno-reorder -Wno-char-subscripts -Wno-switch -Wno-unused-parameter -Wno-unused-variable -Wno-deprecated -Wno-unused-value -Wno-unknown-warning-option -Wno-return-type-c-linkage -Wno-unused-function -Wno-sign-compare -Wno-shorten-64-to-32 -Wno-unused-local-typedefs)
        set(WARNINGS ${WARNINGS} ${LINUX_SUPPRESSIONS})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-return-type-c-linkage -Wno-unneeded-internal-declaration")
    else()
        set(WARNINGS -Wall -Wextra -Wcast-qual -Wconversion -Wformat=2 -Winit-self -Winvalid-pch -Wmissing-format-attribute -Wmissing-include-dirs -Wpacked -Wredundant-decls)
        set(OSX_SUPPRESSIONS -Wno-overloaded-virtual -Wno-sign-conversion -Wno-deprecated -Wno-unknown-pragmas -Wno-reorder -Wno-char-subscripts -Wno-switch -Wno-unused-parameter -Wno-unused-variable -Wno-deprecated -Wno-unused-value -Wno-unknown-warning-option -Wno-return-type-c-linkage -Wno-unused-function -Wno-sign-compare -Wno-shorten-64-to-32 -Wno-unused-local-typedefs)
        set(WARNINGS ${WARNINGS} ${OSX_SUPPRESSIONS})

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -Wno-return-type-c-linkage -Wno-unneeded-internal-declaration")
        set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
        set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++${CMAKE_CXX_STANDARD}")
    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++${CMAKE_CXX_STANDARD} -fno-strict-aliasing")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message(STATUS "Setting GCC options")

    set(WARNINGS -Wall -Wextra -Wunused-parameter -Wcast-align -Wcast-qual -Wconversion -Wformat=2 -Winit-self -Winvalid-pch -Wmissing-format-attribute -Wmissing-include-dirs -Wpacked -Wredundant-decls -Wunreachable-code)
    set(LD_FLAGS "${LD_FLAGS} -Wl,-z,defs")  # For linker
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    message(STATUS "Setting MSVC options")

    set(WARNINGS)
    set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} /ignore:4264")
    add_compile_options(/bigobj)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MP")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /MP /profile /OPT:REF /OPT:ICF")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MP /profile /OPT:REF /OPT:ICF")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MP")

    if (WINDOWS_STORE OR WINDOWS_PHONE)
        add_compile_options(/ZW)
    endif()
else()
    message(FATAL_ERROR "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

# Function to add ${WARNINGS} to the target
function(add_target_compiler_flags TARGET)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        target_compile_options(${TARGET} INTERFACE -pedantic ${WARNINGS})

        if(WERROR)
            target_compile_options(${TARGET} INTERFACE -Werror)
        endif()
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        if(WERROR)
            target_compile_options(${TARGET} INTERFACE /WX ${WARNINGS})
        endif()
    else()
        message(FATAL_ERROR "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
    endif()
endfunction()
