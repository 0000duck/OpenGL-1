#ifndef __ASSIMP_SCENE_LOADER_H
#define __ASSIMP_SCENE_LOADER_H

#include "ISceneLoader.h"
#include "Scene.h"
#include <assimp\scene.h>

class AssimpSceneLoader : public ISceneLoader
{
public:
	bool load(Scene& scene);
private:
	void processNode(aiNode* node, const aiScene* pScene, Scene& sceneDst);

	bool initMeshes(aiMesh* pMesh, const aiScene* pScene, Scene& scene);
	bool initMaterials(aiMaterial* material, const aiScene* pScene, Scene& scene);
};

#endif