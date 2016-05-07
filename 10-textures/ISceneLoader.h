#ifndef __ISCENE_LOADER_H
#define __ISCENELOADER_H

#include <string>

template <typename T>
class ISceneLoader 
{
	virtual void load(T& r, const std::string fileName) = 0;
};

#endif