cmake_minimum_required(VERSION 3.20)
project(Jelly)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
        src/utils/Logger.cpp
        src/utils/Logger.h
        src/utils/IOManager.cpp
        src/utils/IOManager.h
        src/utils/Palette.cpp
        src/utils/Palette.h
        src/graphics/Sprite.cpp
        src/graphics/Sprite.h
        src/graphics/GLSLProgram.cpp
        src/graphics/GLSLProgram.h
        src/graphics/Vertex.h
        src/vendors/picoPNG.h
        src/vendors/picoPNG.cpp
        src/graphics/GLTexture.h
        src/utils/ImageLoader.cpp
        src/utils/ImageLoader.h
        src/utils/ResourceManager.cpp
        src/utils/ResourceManager.h
        src/graphics/TextureCache.cpp
        src/graphics/TextureCache.h
        src/graphics/Window.cpp
        src/graphics/Window.h
        src/Jelly.cpp
        src/Jelly.h
        )

find_package(fmt CONFIG REQUIRED)
find_package(sdl2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)
find_package(GLEW REQUIRED)

add_library(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt SDL2::SDL2 SDL2::SDL2_image SDL2::SDL2_ttf GLEW::GLEW)