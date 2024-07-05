cmake_minimum_required(VERSION 3.28)
project(2D_Up_Down_Shooter)

set(OpenGlLinkers -lglfw -lglut -lGLU -lGL -lGLEW -lm -lX11 -lpthread -lXi -lXrandr -ldl)

add_executable(2D_Up_Down_Shooter
        core/main.cpp
        core/glad.c
        core/stb_image.h
        shader/shader.cpp
        shader/shader.h
        resources/resource_manager.cpp
        resources/resource_manager.h
        texture/texture.cpp
        texture/texture.h
        core/game_object.cpp
        core/game_object.h
        resources/sprite_renderer.cpp
        resources/sprite_renderer.h
        core/game.cpp
        core/game.h
        core/player_object.cpp
        core/player_object.h
        core/game_level.cpp
        core/game_level.h
        core/enemy_object.cpp
        core/enemy_object.h
)

target_link_libraries(2D_Up_Down_Shooter ${OpenGlLinkers})