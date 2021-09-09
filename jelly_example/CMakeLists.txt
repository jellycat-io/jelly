find_package(fmt CONFIG REQUIRED)
find_package(sdl2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)

set(SOURCE_FILES
        src/core/Engine.cpp
        src/core/Engine.h
        src/main.cpp)

file(COPY shaders textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(jelly_example ${SOURCE_FILES})

target_link_libraries(jelly_example
        jelly
        fmt::fmt
        SDL2::SDL2
        SDL2::SDL2_image
        SDL2::SDL2_ttf
        GLEW::GLEW
        glm::glm)

install(TARGETS jelly_example
        EXPORT JellyTargets
        RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)