cmake_minimum_required(VERSION 3.5)
project(kryogenic.sandbox LANGUAGES CXX)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(spdlog REQUIRED)

file(GLOB_RECURSE KRYOGENIC_SANDBOX_SOURCES
        "*.cpp"
        "*.hpp"
)

add_executable(kryogenic.sandbox ${KRYOGENIC_SANDBOX_SOURCES})

set_target_properties(kryogenic.sandbox PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

target_include_directories(kryogenic.sandbox PUBLIC
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        "."
)

target_link_libraries(kryogenic.sandbox
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        kryogenic.engine
        spdlog::spdlog
)

target_compile_options(kryogenic.sandbox PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:-Wall -Wextra -Wpedantic>
)
