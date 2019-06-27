message(STATUS "Generating samples")

add_executable(pstem.example src/example.cpp)
target_link_libraries(pstem.example pstem)

message(STATUS "Generating samples - done")
