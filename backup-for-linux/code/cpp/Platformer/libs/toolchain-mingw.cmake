set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

# Пути к MinGW (может отличаться в вашей системе)
set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)

# Явное указание путей к raylib
set(RAYLIB_INCLUDE_DIR "/home/modeffz/code/cpp/Platformer/libs/raylib-windows/include")
set(RAYLIB_LIBRARY "/home/modeffz/code/cpp/Platformer/libs/raylib-windows/lib/libraylib.a")

include_directories(${RAYLIB_INCLUDE_DIR})
link_directories(/home/modeffz/code/cpp/Platformer/libs/raylib-windows/lib)
