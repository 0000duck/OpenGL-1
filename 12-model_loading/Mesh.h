#ifndef __MESH_H
#define __MESH_H

#include "Vertex.h"
#include <vector>
#include "Texture.h"
#include "math_3d.h"

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	unsigned int materialIndex;
};

#endif