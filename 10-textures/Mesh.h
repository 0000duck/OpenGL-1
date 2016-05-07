#ifndef __MESH_H
#define __MESH_H

#include "Vertex.h"
#include <vector>
#include "math_3d.h"

class Mesh
{
public:
	Mesh(int numVertices, Vector3f* vertices, Vector3f* colors, Vector2f* textureCoordinates, Vector3f* normals, int numFaces, unsigned int* indices);
	Vertex* getVertices(void);
	unsigned int getNumVertices(void);

	unsigned int* getIndices();
	unsigned int getNumIndices(void);
private:
	std::vector<Vertex> _vertices;
	std::vector<unsigned int> _indices;
};

#endif