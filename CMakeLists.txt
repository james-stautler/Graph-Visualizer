cmake_minimum_required(VERSION 3.28)
project(GraphVisualizer LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(gv src/gv.cpp
        src/Node.h
        src/Node.cpp
        src/Window.h
        src/Window.cpp
        src/Edge.h
        src/Edge.cpp)
target_compile_features(gv PRIVATE cxx_std_17)
target_link_libraries(gv PRIVATE SFML::Graphics)
