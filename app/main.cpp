#include <iostream>

// GLAD needs to be included first
#include <glad/glad.h>

// GLFW is included next
#include <GLFW/glfw3.h>

#include "ShaderLoader.h"
#include "Camera.h"
#include "Renderer.h"

Camera* camera;
Renderer* renderer;

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

    delete camera;
    delete renderer;

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

	GLuint flatShaderProgram = shader.createProgram("/home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/assets/FlatModel.vs", "/home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/assets/FlatModel.fs");
	
	camera = new Camera(45.0f, 800, 600, 0.1f, 100.0f, glm::vec3(0.0f, 4.0f, 6.0f));

	renderer = new Renderer(MeshType::kTriangle, camera);
	renderer->setProgram(flatShaderProgram);
	renderer->setPosition(glm::vec3(0.0f, 0.0f, 0.0f)); // Position of the MESH(triangle)

    /*  
        Position of MESH(triangle) 
        [Right Hand Coordinate System] 
        [+z is coming out the screen]
        [+y is upward]
        [+x is right]

        As we go towards positive z [INCREMENTING z value from 0], then the triangle gets bigger as MESH is coming nearer to the camera
        As we go towards negative z [DECREMENTING z value from 0], then the triangle gets smaller as MESH is going far away from the camera
    */

}

void renderScene(){

    glClearColor(0.3, 0.6, 0.4, 1.0);   // sets the color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen

    renderer->draw();
}