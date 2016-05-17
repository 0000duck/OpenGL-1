#ifndef __RAW_SCENE_LOADER_H
#define __RAW_SCENE_LOADER_H

#include "ISceneLoader.h"
#include "Scene.h"
#include <string>

class RawSceneLoader : public ISceneLoader<Scene>
{
public:
	void load(Scene& scene, const std::string fileName = "");
	
};

#endif