# Platformer
 
The platformer game. Version 0.1

```i686-w64-mingw32-g++ -std=c++17 -I./src -I./libs/raylib-win32/include \
$(find src -name "*.cpp") \
-L./libs/raylib-win32/lib -lraylib \
-lopengl32 -lgdi32 -lwinmm \
-static -o PlatformerRewind_32bit.exe```

```x86_64-w64-mingw32-g++ -std=c++17 -I./src -I./libs/raylib-windows/include \
$(find src -name "*.cpp") \
-L./libs/raylib-windows/lib -lraylib \
-lopengl32 -lgdi32 -lwinmm \
-static -o PlatformerRewind.exe

cp ./libs/raylib-windows/lib/raylib.dll ./```