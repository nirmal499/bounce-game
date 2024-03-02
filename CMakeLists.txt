cmake_minimum_required(VERSION 3.22.1)

project(cpp_game_dev_packt)

add_subdirectory(external/glfw)

set(BULLET_ROOT "/home/nbaskey/my_opt/bulletphysics_libs/") # where to find Bullet
find_package(Bullet REQUIRED)

add_executable(main 
    app/main.cpp
    app/Mesh.cpp
    app/LightRenderer.cpp
    app/MeshRenderer.cpp
    app/ShaderLoader.cpp
    app/TextureLoader.cpp
    app/TextRenderer.cpp
    app/Camera.cpp
    glad/src/glad.c
)

set(BULLET_INCLUDE_DIR "/home/nbaskey/my_opt/bulletphysics_libs/include/bullet/")
set(FREETYPE_INCLUDE_DIR "/home/nbaskey/my_opt/freefont_libs/include/freetype2")

target_include_directories(main
    PRIVATE include
    PRIVATE external/glfw/include
    PRIVATE external/glm
    PRIVATE glad/include
    PRIVATE ${BULLET_INCLUDE_DIR}
    PRIVATE ${FREETYPE_INCLUDE_DIR}
)

link_directories(/home/nbaskey/my_opt/freefont_libs) # It has libfreetype.a

target_link_libraries(main
    PRIVATE glfw
    PRIVATE ${BULLET_LIBRARIES}
    PRIVATE freetype
)