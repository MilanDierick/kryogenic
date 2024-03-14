cmake_minimum_required(VERSION 3.5)
project(kryogenic.engine LANGUAGES CXX)

find_package(GLM REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(spdlog REQUIRED)

file(GLOB_RECURSE KRYOGENIC_ENGINE_SOURCES
        "*.cpp"
        "*.hpp"
)

add_library(kryogenic.engine SHARED ${KRYOGENIC_ENGINE_SOURCES})

set_target_properties(kryogenic.engine PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

target_include_directories(kryogenic.engine PUBLIC
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
        "."
)

target_link_libraries(kryogenic.engine
        ${SDL2_LIBRARIES}
        SDL2_image::SDL2_image
        spdlog::spdlog
)

target_compile_options(kryogenic.engine PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:-Wall -Wextra -Wpedantic>
)

target_precompile_headers(kryogenic.engine PRIVATE
        "pch.cpp"
        "pch.hpp"
)