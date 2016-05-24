#ifndef __SCENE_LOADER_FACTORY_H
#define __SCENE_LOADER_FACTORY_H

#include "ISceneLoader.h"
#include <memory>

class SceneLoaderFactory
{
public:
	static std::unique_ptr<ISceneLoader> makeLoader(std::string type);
};

#endif
