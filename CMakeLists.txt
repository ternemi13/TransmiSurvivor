cmake_minimum_required(VERSION 3.16)

project(TransmiSurvivor)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:/Librerias/SFML-2.6.1/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED)

include_directories(include)

add_executable(TransmiSurvivor
    src/main.cpp
    src/Game.cpp
    src/Player.cpp
    src/Enemy.cpp
    src/Room.cpp
    src/Renderer.cpp
)

target_link_libraries(TransmiSurvivor
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)
