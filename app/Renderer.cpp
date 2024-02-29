#include "Renderer.h"

Renderer::Renderer(MeshType meshType, Camera* camera) {

	this->camera = camera;

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

	//Attributes
	glEnableVertexAttribArray(0); // Position(vec3) attribute of the vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

    /* "(void*)(offsetof(Vertex, Vertex::color)" is the offset of the Color attribute of the vertex */
	glEnableVertexAttribArray(1); // Color(vec3) attribute of the vertex
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::color)));

    /* "sizeof(Vertex)" is the stride */


	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Renderer::draw() {

	
	glm::mat4 model = glm::mat4(1.0f); // Identity 4*4 Matrix

    /* Here "position" is the position of the MESH to be rendered */
	model = glm::translate(glm::mat4(1.0), position);
	
	glUseProgram(this->program);

        /*  we need to get the location of this uniform variable by calling glGetUniformLocation, and then passing in
            the program and the variable string in the shader that we set 
        */
        GLint modelLoc = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glm::mat4 view = camera->getViewMatrix();
        GLint vLoc = glGetUniformLocation(program, "view");
        glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 proj = camera->getProjectionMatrix();
        GLint pLoc = glGetUniformLocation(program, "projection");
        glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(proj));


        glBindVertexArray(vao);
        
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0);
	glUseProgram(0);
	
}

Renderer::~Renderer() {}

/* setters for Position of MESH to render*/
void Renderer::setPosition(glm::vec3 _position) {

	position = _position;
}

/* setters for Color of MESH to render*/
void Renderer::setColor(glm::vec3 _color) {

	this->color = _color;
}
/* setters for Vertex and Fragment shader*/
void Renderer::setProgram(GLuint _program) {

	this->program = _program;
}


// GETTERS
glm::vec3 Renderer::getPosition() {

	return position;
}

glm::vec3 Renderer::getColor() {

	return color;
}