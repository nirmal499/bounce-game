#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(MeshType meshType, Camera* camera, btRigidBody* _rigidBody, std::string _name, LightRenderer* _light, float _specularStrength, float _ambientStrength) {

	this->rigidBody = _rigidBody;
	this->camera = camera;
	this->scale =  glm::vec3(1.0f, 1.0f, 1.0f);
	this->position = glm::vec3(0.0, 0.0, 0.0);
	this->name = _name;

	light = _light;
	ambientStrength = _ambientStrength;
	specularStrength = _specularStrength;

	switch (meshType) {

		case kTriangle: Mesh::setTriData(vertices, indices); break;
		case kQuad: Mesh::setQuadData(vertices, indices); break;
		case kCube: Mesh::setCubeData(vertices, indices); break;
		case kSphere: Mesh::setSphereData(vertices, indices); break;
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

	//Attributes
	glEnableVertexAttribArray(0); // Position(vec3) attribute of the vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

    /* "(void*)(offsetof(Vertex, Vertex::texCoords)" is the offset of the  attribute of the texCoords */
	glEnableVertexAttribArray(1); // texCoords(vec2) attribute of the vertex
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::texCoords)));

	glEnableVertexAttribArray(2); // normal(vec2) attribute of the vertex
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::normal)));

    /* "sizeof(Vertex)" is the stride */
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void MeshRenderer::draw() {

	btTransform t;
	rigidBody->getMotionState()->getWorldTransform(t);
	btQuaternion rotation = t.getRotation();
	btVector3 translate = t.getOrigin();

	glm::mat4 RotationMatrix = glm::rotate(glm::mat4(1.0f), rotation.getAngle(),
		glm::vec3(rotation.getAxis().getX(),rotation.getAxis().getY(), rotation.getAxis().getZ()));

	glm::mat4 TranslationMatrix = glm::translate(glm::mat4(1.0f),
		glm::vec3(translate.getX(), translate.getY(), translate.getZ()));

	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

	/* The new modelMatrix variable will be the multiplication of the scale, rotation, and translation matrices in that order */
	modelMatrix = TranslationMatrix * RotationMatrix * scaleMatrix;
	
	/*
	glm::mat4 TranslationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

	modelMatrix = glm::mat4(1.0f); // Identity 4*4 Matrix
	modelMatrix = TranslationMatrix * scaleMatrix;
	*/

	glm::mat4 view = camera->getViewMatrix();
	glm::mat4 proj = camera->getProjectionMatrix();
	/* 	The order in which the view and projection matrices are multiplied matters and cannot be reversed  */
	glm::mat4 vp = proj * view;
	
	glUseProgram(this->program);

		GLint vpLoc = glGetUniformLocation(program, "vp"); // vertex shader
        glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));

        GLint modelLoc = glGetUniformLocation(program, "model"); // vertex shader
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		/* 	You might be wondering why we aren't using glUniformMatrix4fv or
			something similar while setting the texture location, as we did for the matrices.
			Well, since we have just the one texture, the program sets the uniform location as
			the 0th index by default so we don't have to worry about it. This all that we
			require to bind the texture.
		*/
		glBindTexture(GL_TEXTURE_2D, this->texture);

		/* Set Lighting: we pass the camera position, light position, light color, specular strength, and ambient strength as uniforms to the shader */
		GLuint cameraPosLoc = glGetUniformLocation(program, "cameraPos"); // fragment shader
		glUniform3f(cameraPosLoc, camera->getCameraPosition().x, camera->getCameraPosition().y, camera->getCameraPosition().z);

		GLuint lightPosLoc = glGetUniformLocation(program, "lightPos"); // fragment shader
		glUniform3f(lightPosLoc, this->light->getPosition().x, this->light->getPosition().y, this->light->getPosition().z);

		GLuint lightColorLoc = glGetUniformLocation(program, "lightColor"); // fragment shader
		glUniform3f(lightColorLoc, this->light->getColor().x, this->light->getColor().y, this->light->getColor().z);

		GLuint specularStrengthLoc = glGetUniformLocation(program, "specularStrength"); // fragment shader
		glUniform1f(specularStrengthLoc, specularStrength);

		GLuint ambientStrengthLoc = glGetUniformLocation(program, "ambientStrength"); // fragment shader
		glUniform1f(ambientStrengthLoc, ambientStrength);

        glBindVertexArray(vao);
        
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0);

	glUseProgram(0);
	
}

MeshRenderer::~MeshRenderer() {}

/* setters for Position of MESH to render*/
void MeshRenderer::setPosition(glm::vec3 _position) {

	this->position = _position;
}

void MeshRenderer::setTexture(GLuint textureID) {

	this->texture = textureID;
}

void MeshRenderer::setScale(glm::vec3 _scale) {

	this->scale = _scale;
}

/* setters for Vertex and Fragment shader*/
void MeshRenderer::setProgram(GLuint _program) {

	this->program = _program;
}