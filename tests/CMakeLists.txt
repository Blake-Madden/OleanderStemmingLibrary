message(STATUS "Preparing tests")

# Enable construction of test target
enable_testing()

# Create and link the test executables
add_executable(olestem.test_main src/test_main.cpp)
target_link_libraries(olestem.test_main oleanderstemminglibrary)

# Test definitions
macro(create_test target)
    add_test(NAME ${target} COMMAND $<TARGET_FILE:${target}>)
endmacro(create_test)

create_test(olestem.test_main)

message(STATUS "Preparing tests - done")
