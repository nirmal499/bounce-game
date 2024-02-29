#ifndef __CAMERA_HPP_
#define __CAMERA_HPP_

// #include <GL/glew.h>
#include <glad/glad.h> // used to call OPENGL function

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera{
    public:
        Camera(GLfloat FOV, GLfloat width, GLfloat height, GLfloat nearPlane, GLfloat farPlane, glm::vec3 camPos);
        ~Camera();

        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix();
        glm::vec3 getCameraPosition();

    private:
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        glm::vec3 cameraPos;
};


#endif