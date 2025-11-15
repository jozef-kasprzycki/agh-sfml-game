cmake_minimum_required(VERSION 3.16) # Wersja CMake
project(agh-sfml-game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17) # Standard C++
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system) # SFML v. 2.6 (nie 3.0!)

include_directories(include) # Folder plików nagłówkowych

file(GLOB SOURCES src/*.cpp) # Głowny folder

add_executable(agh-sfml-game ${SOURCES})
target_link_libraries(agh-sfml-game PRIVATE sfml-graphics sfml-window sfml-system)
