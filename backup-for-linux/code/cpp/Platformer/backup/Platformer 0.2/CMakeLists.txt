cmake_minimum_required(VERSION 3.10)
project(PlatformerRewind)

set(CMAKE_CXX_STANDARD 17)

find_package(raylib REQUIRED)

file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/core/*.cpp"
    "src/entities/*.cpp"
    "src/levels/*.cpp"
    "src/utils/*.cpp"
    "src/menu/*.cpp"
)

add_executable(PlatformerRewind ${SOURCES})

target_include_directories(PlatformerRewind PRIVATE src)
target_link_libraries(PlatformerRewind raylib)
