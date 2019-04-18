add_executable(olestem.test_example src/example.cpp)

target_link_libraries(olestem.test_example oleanderstemminglibrary)

enable_testing()
add_test(test_example olestem.text_example)
