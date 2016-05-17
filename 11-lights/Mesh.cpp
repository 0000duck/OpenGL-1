#include "Mesh.h"
#include "math_3d.h"
#include "Vertex.h"

Mesh::Mesh(int numVertices, Vector3f* vertices, Vector3f* colors, Vector2f* textureCoordinates, Vector3f* normals, int numFaces, unsigned int* indices)
{
	for(int i = 0; i < numVertices; ++i) {
		_vertices.push_back(Vertex(vertices[i],colors[i],textureCoordinates[i],normals[i]));
	}

	for(int j = 0; j < numFaces * 3; ++j) {
		_indices.push_back(indices[j]);
	}
}

Vertex* Mesh::getVertices()
{
	return &_vertices[0];
}

unsigned int* Mesh::getIndices()
{
	return &_indices[0];
}

unsigned int Mesh::getNumVertices()
{
	return _vertices.size();
}

unsigned int Mesh::getNumIndices(void)
{
	return _indices.size();
}