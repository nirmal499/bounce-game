cmake_minimum_required(VERSION 3.22.1)

project(cpp_game_dev_packt)

add_subdirectory(external/glfw)

add_executable(main 
    app/main.cpp
    app/Mesh.cpp
    app/Renderer.cpp
    app/ShaderLoader.cpp
    app/Camera.cpp
    glad/src/glad.c
)

target_include_directories(main
    PRIVATE external/glfw/include
    PRIVATE external/glm
    PRIVATE glad/include
)

target_link_libraries(main
    PRIVATE glfw
)