#ifndef __RENDER_HPP_
#define __RENDER_HPP_

// #include <GL/glew.h>
#include <glad/glad.h> // used to call OPENGL function

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "ShaderLoader.h"
#include "Camera.h"

class Renderer{
    public:
        /*  We will also need Mesh.h, which allows us to define the shape of the light in thelight source 
            You can use the ShaderLoader class to load in the shaders in order to render the object
            Camera.h to get the camera's location, view, and projection matrices onto the scene
        */
        Renderer(MeshType meshType, Camera* camera);
        ~Renderer();

        /*  In the public section, we create the constructor that we pass MeshType to; this
            will be used to set the shape of the object that we want to render. Then, we have
            the destructor. Here, we have a function called draw, which will be used to draw
            the mesh. Then, we have a couple of setters for setting the position, color, and
            shader program for the object 
        */
        void draw();

        void setPosition(glm::vec3 _position);
        void setColor(glm::vec3 _color);
        void setProgram(GLuint _program);

        glm::vec3 getPosition();
        glm::vec3 getColor();

    private:
        Camera* camera;

        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;

        /*  The program variable will have the shader program that we want to use to draw
            the object. Then, we have vbo, which stands for vertex buffer object; ebo, which
            stands for Element Buffer Object; and vao, which stands for Vertex Array Object. 
        */
        GLuint vbo, ebo, vao, program;

        glm::vec3 position, color;
};

#endif