add_executable(olestem.test_main src/test_main.cpp)

target_link_libraries(olestem.test_main oleanderstemminglibrary)

enable_testing()
add_test(test_main olestem.text_main)
