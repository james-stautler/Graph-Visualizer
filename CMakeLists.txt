cmake_minimum_required(VERSION 3.28)
project(GraphVisualizer LANGUAGES CXX)

enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

include(GoogleTest)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)


add_executable(gv
        src/gv.cpp
        src/Node.h
        src/Node.cpp
        src/Window.h
        src/Window.cpp
        src/Edge.h
        src/Edge.cpp
        src/Graph.h
        src/Graph.cpp
        src/Button.h
        src/Button.cpp)

add_executable(Tests
        test/NodeTest.cpp
        test/EdgeTest.cpp
        test/GraphTest.cpp
        test/ButtonTest.cpp
        test/AlgorithmTest.cpp)

target_compile_features(gv PRIVATE cxx_std_17)
target_link_libraries(gv PRIVATE SFML::Graphics)

target_compile_features(Tests PRIVATE cxx_std_17)
target_link_libraries(Tests PRIVATE SFML::Graphics)
target_link_libraries(Tests PRIVATE GTest::gtest_main)
target_link_libraries(Tests PRIVATE GTest::gmock_main)

gtest_discover_tests(Tests)

function(copy_runtime_dependencies target_name)
    if(WIN32)
        set(DLL_COPY_EXPRESSION "$<TARGET_RUNTIME_DLLS:${target_name}>")

        add_custom_command(TARGET ${target_name} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${DLL_COPY_EXPRESSION}
                $<TARGET_FILE_DIR:${target_name}>
                COMMENT "Copying runtime dependencies for ${target_name}"
                VERBATIM
        )
    endif()
endfunction()

copy_runtime_dependencies(gv)
copy_runtime_dependencies(Tests)
