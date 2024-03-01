#include <iostream>

// GLAD needs to be included first
#include <glad/glad.h>

// GLFW is included next
#include <GLFW/glfw3.h>

#include "ShaderLoader.h"
#include "Camera.h"
#include "LightRenderer.h"
#include "MeshRenderer.h"
#include "TextureLoader.h"

#define ASSEST_FOLDER_PATH "/home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/assets"

#define SAFE_DELETE(p) \
    do { \
        if (p != nullptr) { \
            delete p; \
            p = nullptr; \
        } \
    } while (false)

Camera* camera = nullptr;
LightRenderer* light_renderer = nullptr;
MeshRenderer* sphere = nullptr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

void initGame();
void renderScene();

static void glfwError(int id, const char* description)
{
	std::cout << description << std::endl;
}

int main(){

    glfwSetErrorCallback(&glfwError);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    initGame();
    while(!glfwWindowShouldClose(window))
    {

        processInput(window);

        renderScene();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    SAFE_DELETE(camera);
    SAFE_DELETE(light_renderer);
    SAFE_DELETE(sphere);

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true); 
    }
}

void initGame() {
	
	// Enable the depth testing
	glEnable(GL_DEPTH_TEST); 

	ShaderLoader shader;
    TextureLoader tLoader;

    GLuint sphereTexture = tLoader.getTextureID(ASSEST_FOLDER_PATH "/textures/globe.jpg");

	GLuint flatShaderProgram = shader.createProgram(ASSEST_FOLDER_PATH "/shader/FlatModel.vs",ASSEST_FOLDER_PATH "/shader/FlatModel.fs");
	GLuint texturedShaderProgram = shader.createProgram(ASSEST_FOLDER_PATH "/shader/TexturedModel.vs", ASSEST_FOLDER_PATH "/shader/TexturedModel.fs");
	
	camera = new Camera(45.0f, 800, 600, 0.1f, 100.0f, glm::vec3(0.0f, 0.0f, 4.0f));

	// light_renderer = new LightRenderer(MeshType::kSphere, camera);
    // light_renderer->setProgram(flatShaderProgram);
    // light_renderer->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	sphere = new MeshRenderer(MeshType::kSphere, camera);
	sphere->setProgram(texturedShaderProgram);
    sphere->setTexture(sphereTexture);
	sphere->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    sphere->setScale(glm::vec3(1.0f, 1.0f, 1.0f));

    /*  
        Position of MESH
        [Right Hand Coordinate System] 
        [+z is coming out the screen]
        [+y is upward]
        [+x is right]
    */

}

void renderScene(){

    glClearColor(0.0, 0.0, 0.0, 1.0);   // sets the color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen

    sphere->draw();
    // light_renderer->draw();
}