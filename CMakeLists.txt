cmake_minimum_required(VERSION 3.12.3)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/vendor/bgi/include ${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/vendor/bgi/lib)

add_library(BGIGame src/BGIGame/Application.cpp)
add_executable(TicTacToe src/TicTacToe/main.cpp)

set_target_properties(BGIGame PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(TicTacToe bgi)
target_link_libraries(TicTacToe BGIGame)