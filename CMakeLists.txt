cmake_minimum_required(VERSION 3.20)
project(Jelly)

set(JELLY_MAJOR_VERSION 0)
set(JELLY_MINOR_VERSION 1)
set(JELLY_PATCH_VERSION 0)
set(JELLY_VERSION
        ${JELLY_MAJOR_VERSION}.${JELLY_MINOR_VERSION}.${JELLY_PATCH_VERSION})

set(CMAKE_CXX_STANDARD 20)

set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")

if(WIN32 AND NOT CYGWIN)
    set(DEF_INSTALL_CMAKE_DIR CMake)
else()
    set(DEF_INSTALL_CMAKE_DIR lib/CMake/Jelly)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")


# Make relative paths absolute
foreach(p LIB BIN INCLUDE CMAKE)
    set(var INSTALL_${p}_DIR)
    if(NOT IS_ABSOLUTE "${${var}}")
        set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
    endif()
endforeach()

include_directories(
        "${PROJECT_SOURCE_DIR}"
        "${PROJECT_BINARY_DIR}")

add_subdirectory(jelly)
add_subdirectory(jelly_example)

export(TARGETS jelly jelly_example
        FILE ${PROJECT_BINARY_DIR}/JellyTargets.cmake)

export(PACKAGE Jelly)

message("${INSTALL_CMAKE_DIR}")

file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
        "${INSTALL_INCLUDE_DIR}")

set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(JellyConfig.cmake.in
        "${PROJECT_BINARY_DIR}/JellyConfig.cmake" @ONLY)

set(CONF_INCLUDE_DIRS "\${JELLY_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(JellyConfig.cmake.in
        "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/JellyConfig.cmake" @ONLY)

configure_file(JellyConfigVersion.cmake.in
        "${PROJECT_BINARY_DIR}/JellyConfigVersion.cmake" @ONLY)

install(FILES
        "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/JellyConfig.cmake"
        "${PROJECT_BINARY_DIR}/JellyConfigVersion.cmake"
        DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

install(
        EXPORT JellyTargets
        DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)