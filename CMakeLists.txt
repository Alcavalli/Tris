cmake_minimum_required(VERSION 3.10)        # versione minima necessaria di CMake

project(Tic-Tac-Toe)

set(CMAKE_CXX_STANDARD 17)                  # usa C++17
set(CMAKE_CXX_STANDARD_REQUIRED True)       # non degradare a versioni precedenti

include_directories(include)                # cerca gli header in include/

add_executable(main                         # crea main.exe a partire dai file indicati
    src/main.cpp
    src/Game.cpp
    src/Grid.cpp
    src/Renderer.cpp
    src/AI.cpp
    src/Button.cpp
)

find_package(SFML 3 COMPONENTS Graphics REQUIRED)       # cerca SFML (già installato)
target_link_libraries(main PRIVATE SFML::Graphics)      # collega SFML

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})       # copia la cartella assets/ in build/ ad ogni esecuzione