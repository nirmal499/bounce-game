#ifndef __MESHRENDER_HPP_
#define __MESHRENDER_HPP_

#include <vector>

#include "Camera.h"
#include "LightRenderer.h"

// #include <GL/glew.h>
#include <glad/glad.h> // used to call OPENGL function

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <btBulletDynamicsCommon.h>
#include <string>

/*  For drawing regular game objects, we will create a separate class from the LightRenderer
    class by adding texture, and we will also add motion to the object by adding physical
    properties. 
*/
class MeshRenderer{
    public:

        /*  For each object to be lit, we also need to pass in the light color, diffuse, and specular strength */
        MeshRenderer(MeshType meshType, Camera* camera, btRigidBody* _rigidBody, std::string _name, LightRenderer* _light, float _specularStrength, float _ambientStrength);
        ~MeshRenderer();

        void draw();

        void setPosition(glm::vec3 _position);
        void setScale(glm::vec3 _scale);
        void setProgram(GLuint _program);
        /* This textureID function , which we will be using to set the texture on the object. */
        void setTexture(GLuint _textureID);
        
        btRigidBody* rigidBody;
        std::string name = "";

    private:
        Camera* camera;

        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        glm::mat4 modelMatrix;

        glm::vec3 position, scale;
        GLuint vao, vbo, ebo, texture, program;

        LightRenderer* light;
        float ambientStrength, specularStrength;
};

#endif