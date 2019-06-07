# -----------------------------------------------------------------------------
# Google Sanitizers
# -----------------------------------------------------------------------------
OPTION(ENABLE_ASAN "Enable Google AddressSanitizer" OFF)
OPTION(ENABLE_USAN "Enable Google UndefinedBehaviorSanitizer" OFF)
OPTION(ENABLE_TSAN "Enable Google ThreadSanitizer" OFF)

# AddressSanitizer
#   Detects addressability issues
if(ENABLE_ASAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
endif()

# UndefinedBehaviorSanitizer
#
if(ENABLE_USAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
endif()

# ThreadSanitizer
#   Detects data races and deadlocks
if(ENABLE_TSAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
endif()

# -----------------------------------------------------------------------------
# Valgrind
# -----------------------------------------------------------------------------
OPTION(ENABLE_VALGRIND "Enable Valgrind")

# Valgrind
#   Provides leak detection
if(ENABLE_VALGRIND)
    set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --leak-check=full")
    set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --track-fds=yes")
    set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --trace-children=yes")
    set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --error-exitcode=1")
endif()
