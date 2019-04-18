add_executable(ExampleTest src/example.cpp)

target_link_libraries(ExampleTest oleanderstemminglibrary)

enable_testing()
add_test(test_example ExampleTest)
