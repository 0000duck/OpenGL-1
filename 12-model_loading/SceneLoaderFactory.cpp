#include "SceneLoaderFactory.h"
#include "RawSceneLoader.h"
#include "AssimpSceneLoader.h"

std::unique_ptr<ISceneLoader> SceneLoaderFactory::makeLoader(std::string type)
{
	if(type == "raw")
		return std::unique_ptr<RawSceneLoader>(new RawSceneLoader);
	else if(type == "assimp")
		return std::unique_ptr<AssimpSceneLoader>(new AssimpSceneLoader);
	return std::unique_ptr<RawSceneLoader>(new RawSceneLoader);
}