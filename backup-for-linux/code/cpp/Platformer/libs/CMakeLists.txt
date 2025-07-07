cmake_minimum_required(VERSION 3.10)
project(PlatformerRewind)

set(CMAKE_CXX_STANDARD 17)

# Подключаем исходники
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/core/*.cpp"
    "src/entities/*.cpp"
    "src/levels/*.cpp"
    "src/utils/*.cpp"
    "src/menu/*.cpp"
)

# Создаём исполняемый файл
add_executable(PlatformerRewind ${SOURCES})

# Линковка библиотек для Windows
target_link_libraries(PlatformerRewind 
    raylib 
    opengl32 
    gdi32 
    winmm
)

add_custom_command(TARGET PlatformerRewind POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${RAYLIB_WINDOWS_PATH}/lib/raylib.dll"
        $<TARGET_FILE_DIR:PlatformerRewind>
)
message(STATUS "RAYLIB INCLUDE DIR: ${RAYLIB_INCLUDE_DIR}")
message(STATUS "RAYLIB LIBRARY: ${RAYLIB_LIBRARY}")
include_directories(${RAYLIB_INCLUDE_DIR} src)
