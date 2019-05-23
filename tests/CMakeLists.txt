message(STATUS "Preparing tests")

# Enable construction of test target
enable_testing()

# Create and link the test executables
add_executable(olestem.test_stemming src/test_stemming.cpp)
target_link_libraries(olestem.test_stemming oleanderstemminglibrary)

# Test definitions
macro(create_test target)
    add_test(NAME ${target} COMMAND $<TARGET_FILE:${target}>)
endmacro(create_test)

create_test(olestem.test_stemming)

message(STATUS "Preparing tests - done")

# -----------------------------------------------------------------------------
# Code Coverage report
# -----------------------------------------------------------------------------
# cmake .. -DENABLE_CODECOV=ON
# cmake --build .
# cmake --build target
if (ENABLE_CODECOV)
    set(COVERAGE_LCOV_EXCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/libs/*")
    include(CodeCoverage)

    APPEND_COVERAGE_COMPILER_FLAGS()

    SETUP_TARGET_FOR_COVERAGE_LCOV(
        NAME olestem.coverage_stemming
        EXECUTABLE $<TARGET_FILE:olestem.test_stemming>
        DEPENDENCIES oleanderstemminglibrary
    )
endif()
