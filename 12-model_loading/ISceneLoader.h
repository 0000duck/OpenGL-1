#ifndef __ISCENE_LOADER_H
#define __ISCENE_LOADER_H

#include "Scene.h"

class ISceneLoader 
{
public:
	virtual bool load(Scene& scene) = 0;
};

#endif