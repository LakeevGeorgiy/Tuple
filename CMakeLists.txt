cmake_minimum_required(VERSION 3.24)
project(Tuple)

set(CMAKE_CXX_STANDARD 20)
add_executable(Tuple main.cpp)

add_subdirectory(TupleLib)
add_subdirectory(Tests)

target_link_libraries(${PROJECT_NAME} PUBLIC TupleLib)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

enable_testing()