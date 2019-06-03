message(STATUS "Generating samples")

add_executable(olestem.example src/example.cpp)
target_link_libraries(olestem.example olestem)

message(STATUS "Generating samples - done")
