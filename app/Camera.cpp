#include "Camera.h"

Camera::Camera(GLfloat FOV, GLfloat width, GLfloat height, GLfloat nearPlane, GLfloat farPlane, glm::vec3 camPos){
    cameraPos = camPos;

    /**
        Our camera is going to be a stationary camera that will always be looking toward the center of the world
        coordinates; the up vector will always be pointing toward the positive y-axis
    */
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    /* To create viewMatrix, we call the glm::lookAt function and pass in the cameraPos, cameraFront, and cameraUp vectors. */
	viewMatrix = glm::lookAt(cameraPos, cameraFront, cameraUp);

    /*  We create the projection matrix by setting the FOV value of the FOV; this is an
        aspect ratio that is given by the width value over the height, nearPlane, and
        farPlane values 
    */
	projectionMatrix = glm::perspective(FOV, width /height, nearPlane, farPlane);
}

Camera::~Camera(){}

glm::mat4 Camera::getViewMatrix() {
    return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() {
    return projectionMatrix;
}

glm::vec3 Camera::getCameraPosition() {
    return cameraPos;
}