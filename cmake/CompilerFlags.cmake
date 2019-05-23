# - Sets the compiler flags for the build system
# It defines the following variables:
#    - CMAKE_CXX_FLAGS
#    - conditional
#        - CMAKE_CXX_FLAGS_WARN
#        - CMAKE_CXX_FLAGS_ERROR
#        - CMAKE_SHARED_LINKER_FLAGS
#        - CMAKE_MODULE_LINKER_FLAGS
#        - CMAKE_EXE_LINKER_FLAGS
#        - CMAKE_CXX_FLAGS_RELWITHDEBINFO
#        - CMAKE_CXX_FLAGS_DEBUG

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

# Ensure latest compiler versions
if($<CXX_COMPILER_ID:"GNU">)
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "7")
        message(FATAL_ERROR "Insufficient gcc version")
    endif()
elseif($<CXX_COMPILER_ID:"Clang">)
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.9")
        message(FATAL_ERROR "Insufficient Clang version")
    endif()
elseif($<CXX_COMPILER_ID:"AppleClang">)
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "8.1.0")
        message(FATAL_ERROR "Insufficient AppleClang version")
    endif()
elseif($<CXX_COMPILER_ID:"MSVC")
    if(MSVC_VERSION LESS 1920)
        message(FATAL_ERROR "Insufficient MSVC version")
    endif()
endif()

# Compiler specific flags
if(
    $<CXX_COMPILER_ID:"GNU">
    OR $<CXX_COMPILER_ID:"Clang">
    OR $<CXX_COMPILER_ID:"AppleClang">
)
    include(CheckCXXCompilerFlag)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wextra")
    #target_compile_options(${PROJECT_NAME_L} PRIVATE -Wall -pedantic -Wextra)

    # Additional warnings for GCC
    set(CMAKE_CXX_FLAGS_WARN
        "-Wnon-virtual-dtor -Wno-long-long -Wcast-align -Wchar-subscripts -Wall -Wpointer-arith -Wformat-security -Woverloaded-virtual -fno-check-new -fno-common")

    # This flag is useful as not returning from a non-void function is an error with MSVC, but it is not supported on all GCC compiler versions
    check_cxx_compiler_flag("-Werror=return-type" HAVE_GCC_ERROR_RETURN_TYPE)
    if(HAVE_GCC_ERROR_RETURN_TYPE)
        set(CMAKE_CXX_FLAGS_ERROR "-Werror=return-type")
    endif()

    # If we are compiling on Linux then set some extra linker flags too
    if(CMAKE_SYSTEM_NAME MATCHES Linux)
        set(CMAKE_SHARED_LINKER_FLAGS
            "-Wl,--fatal-warnings -Wl,--no-undefined -lc ${CMAKE_SHARED_LINKER_FLAGS}")
        set(CMAKE_MODULE_LINKER_FLAGS
            "-Wl,--fatal-warnings -Wl,--no-undefined -lc ${CMAKE_MODULE_LINKER_FLAGS}")
        set(CMAKE_EXE_LINKER_FLAGS
            "-Wl,--fatal-warnings -Wl,--no-undefined -lc ${CMAKE_EXE_LINKER_FLAGS}")
    endif()

    # Set up the debug CXX_FLAGS for extra warnings
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO
        "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${CMAKE_CXX_FLAGS_WARN}")
    set(CMAKE_CXX_FLAGS_DEBUG
        "${CMAKE_CXX_FLAGS_DEBUG} ${CMAKE_CXX_FLAGS_WARN} ${CMAKE_CXX_FLAGS_ERROR}")

elseif(MSVC)
    #target_compile_options(${PROJECT_NAME_L} PRIVATE /W2 /W4 /WX)

    set(variables
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_MINSIZEREL
        CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_RELWITHDEBINFO
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_MINSIZEREL
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_RELWITHDEBINFO
    )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /O2 /Ob2 /Oi /Ot /Oy /GL /MP")

endif()
