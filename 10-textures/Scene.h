#ifndef __SCENE_H
#define __SCENE_H

#include <vector>
#include "Mesh.h"

class Scene
{
public:
	Scene();
	~Scene();

	std::vector<Mesh> meshes;
};

#endif