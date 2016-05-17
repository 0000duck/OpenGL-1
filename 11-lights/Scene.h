#ifndef __SCENE_H
#define __SCENE_H

#include <vector>
#include "Mesh.h"
#include "Light.h"
#include "Texture.h"
#include "Material.h"

class Scene
{
public:
	Scene();
	~Scene();

	std::vector<Mesh> meshes;
	std::vector<Texture> textures;
	//std::vector<Camera> cameras;
	std::vector<Light> lights;
	std::vector<Material> materials;
};

#endif