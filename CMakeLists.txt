cmake_minimum_required(VERSION 3.20)
project(Jelly)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 20)

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

find_package(fmt CONFIG REQUIRED)
find_package(sdl2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)
find_package(GLEW REQUIRED)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        fmt::fmt
        SDL2::SDL2
        SDL2::SDL2_image
        SDL2::SDL2_ttf
        GLEW::GLEW
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

install(
        TARGETS Jelly
        EXPORT JellyTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
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

install(FILES ${HEADER_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(
        EXPORT JellyTargets
        FILE JellyTargets.cmake
        NAMESPACE Jelly::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Jelly
)

include(CMakeFindDependencyMacro)
find_dependency(fmt)
find_dependency(sdl2)
find_dependency(sdl2-image)
find_dependency(sdl2-ttf)
find_dependency(GLEW)

include(CMakePackageConfigHelpers)

set(version 0.0.1)

set_property(TARGET Jelly PROPERTY VERSION ${version})
set_property(TARGET Jelly PROPERTY SOVERSION 0)
set_property(TARGET Jelly PROPERTY INTERFACE_Jelly_MAJOR_VERSION 0)
set_property(TARGET Jelly APPEND PROPERTY COMPATIBLE_INTERFACE_STRING Jelly_MAJOR_VERSION)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/JellyConfigVersion.cmake"
        VERSION "${version}"
        COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/JellyConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Jelly
)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/JellyConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/JellyConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Jelly
)

export(
        EXPORT JellyTargets
        FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/JellyTargets.cmake"
        NAMESPACE Jelly::
)