#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(MeshType meshType, Camera* camera) {

	this->camera = camera;
	this->scale =  glm::vec3(1.0f, 1.0f, 1.0f);
	this->position = glm::vec3(0.0, 0.0, 0.0);

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

    /* "sizeof(Vertex)" is the stride */
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void MeshRenderer::draw() {

	glm::mat4 TranslationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

	modelMatrix = glm::mat4(1.0f); // Identity 4*4 Matrix
	/* 	We initialize the modelMatrix variable and the multiply scale and
		translation matrix and assign them to the modelMatrix variable.
	*/
	modelMatrix = TranslationMatrix * scaleMatrix;

	glm::mat4 view = camera->getViewMatrix();
	glm::mat4 proj = camera->getProjectionMatrix();

	/* 	The order in which the view and projection matrices are multiplied
		matters and cannot be reversed 
	*/
	glm::mat4 vp = proj * view;
	
	glUseProgram(this->program);

		GLint vpLoc = glGetUniformLocation(program, "vp");
        glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));

        GLint modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		/* 	You might be wondering why we aren't using glUniformMatrix4fv or
			something similar while setting the texture location, as we did for the matrices.
			Well, since we have just the one texture, the program sets the uniform location as
			the 0th index by default so we don't have to worry about it. This all that we
			require to bind the texture.
		*/
		glBindTexture(GL_TEXTURE_2D, this->texture);

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