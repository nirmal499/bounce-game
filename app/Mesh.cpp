#include "Mesh.h"

void Mesh::setTriData(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {

	std::vector<Vertex> _vertices = {
          // Position           // Normal           // Color             // Texture Coordinates
		{ { 0.0f, -1.0f, 0.0f },{ 0.0f, 0.0f, 1.0 },{ 1.0f, 0.0f, 0.0 },{ 0.0, 1.0 } }, // Vertex 0
		{ { 1.0f, 1.0f, 0.0f },{ 0.0f, 0.0f, 1.0 },{ 0.0f, 1.0f, 0.0 },{ 0.0, 0.0 } },  // Vertex 1
		{ { -1.0f, 1.0f, 0.0f },{ 0.0f, 0.0f, 1.0 },{ 0.0f, 0.0f, 1.0 },{ 1.0, 0.0 } }, // Vertex 2
	};


	std::vector<uint32_t> _indices = {
		0, 1, 2,
	};

	vertices.clear(); indices.clear();

	vertices = _vertices;
	indices = _indices;
}

void Mesh::setQuadData(std::vector<Vertex>& vertices, std::vector<uint32_t>&indices){}
void Mesh::setCubeData(std::vector<Vertex>& vertices, std::vector<uint32_t>&indices){}
void Mesh::setSphereData(std::vector<Vertex>& vertices, std::vector<uint32_t>&indices){}