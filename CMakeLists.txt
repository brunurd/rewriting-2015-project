cmake_minimum_required(VERSION 3.12.3)

project(TicTacToe)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/vendor/bgi/include)
link_directories(${CMAKE_SOURCE_DIR}/vendor/bgi/lib)

add_executable(TicTacToe src/main.cpp)

target_link_libraries(TicTacToe bgi)