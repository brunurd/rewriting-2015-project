cmake_minimum_required(VERSION 3.12.3)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/vendor/bgi/include ${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/vendor/bgi/lib)

add_library(BGIGame
        src/BGIGame/Application.cpp
        src/BGIGame/Input.cpp
        src/BGIGame/GameObject.cpp
        src/BGIGame/Input.cpp
        src/BGIGame/Timer.cpp
        src/BGIGame/Rect.cpp
        )

add_executable(TicTacToe
        src/TicTacToe/main.cpp
        src/TicTacToe/scenes/IntroScene.hpp
        src/TicTacToe/elements/TestElement.hpp
        )

add_executable(TicTacToeLegacy src/TicTacToe/main_legacy.cpp)

set_target_properties(BGIGame PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(TicTacToeLegacy bgi)
target_link_libraries(BGIGame bgi)
target_link_libraries(TicTacToe BGIGame)