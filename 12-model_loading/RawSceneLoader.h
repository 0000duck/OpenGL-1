#ifndef __RAW_SCENE_LOADER_H
#define __RAW_SCENE_LOADER_H

#include "ISceneLoader.h"

class RawSceneLoader : public ISceneLoader
{
public:
	bool load(Scene& scene);
	
};

#endif