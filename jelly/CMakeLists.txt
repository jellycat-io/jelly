find_package(fmt CONFIG REQUIRED)
find_package(sdl2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)
find_package(GLEW REQUIRED)

set(SOURCE_FILES
        src/utils/Logger.cpp
        src/utils/IOManager.cpp
        src/utils/Palette.cpp
        src/graphics/Sprite.cpp
        src/graphics/GLSLProgram.cpp
        src/vendors/picoPNG.cpp
        src/utils/ImageLoader.cpp
        src/utils/ResourceManager.cpp
        src/graphics/TextureCache.cpp
        src/graphics/Window.cpp
        src/Jelly.cpp
        )

set(HEADER_FILES
        src/utils/Logger.h
        src/utils/IOManager.h
        src/utils/ImageLoader.h
        src/utils/ResourceManager.h
        src/utils/Palette.h
        src/graphics/Sprite.h
        src/graphics/GLSLProgram.h
        src/graphics/Vertex.h
        src/graphics/GLTexture.h
        src/graphics/TextureCache.h
        src/graphics/Window.h
        src/vendors/picoPNG.h
        src/Jelly.h
        )

add_library(jelly SHARED ${SOURCE_FILES})

target_link_libraries(jelly PRIVATE
        fmt::fmt
        SDL2::SDL2
        SDL2::SDL2_image
        SDL2::SDL2_ttf
        GLEW::GLEW)

set_target_properties(jelly PROPERTIES
        PUBLIC_HEADER "${HEADER_FILES}")


install(TARGETS jelly
        EXPORT JellyTargets
        RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
        LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
        PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/jelly"
        COMPONENT dev)
