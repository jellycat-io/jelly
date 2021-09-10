find_package(fmt CONFIG REQUIRED)
find_package(sdl2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)

set(SOURCE_FILES
        utils/Logger.cpp
        utils/IOManager.cpp
        utils/Palette.cpp
        utils/ImageLoader.cpp
        utils/ResourceManager.cpp
        graphics/Sprite.cpp
        graphics/GLSLProgram.cpp
        graphics/TextureCache.cpp
        graphics/Window.cpp
        graphics/Camera2D.cpp
        graphics/SpriteBatch.cpp
        vendors/picoPNG.cpp
        Jelly.cpp)

set(HEADER_FILES
        utils/Logger.h
        utils/IOManager.h
        utils/Palette.h
        utils/ImageLoader.h
        utils/ResourceManager.h
        graphics/Sprite.h
        graphics/GLSLProgram.h
        graphics/Vertex.h
        graphics/GLTexture.h
        graphics/TextureCache.h
        graphics/Window.h
        graphics/Camera2D.h
        graphics/SpriteBatch.h
        graphics/Color.h
        vendors/picoPNG.h
        Jelly.h)

add_library(jelly SHARED ${SOURCE_FILES})

target_link_libraries(jelly PRIVATE
        fmt::fmt
        SDL2::SDL2
        SDL2::SDL2_image
        SDL2::SDL2_ttf
        GLEW::GLEW
        glm::glm)

set_target_properties(jelly PROPERTIES
        PUBLIC_HEADER "${HEADER_FILES}")


install(TARGETS jelly
        EXPORT JellyTargets
        RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
        LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
        PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/jelly"
        COMPONENT dev)
