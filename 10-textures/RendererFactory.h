#ifndef __RENDERER_FACTORY_H
#define __RENDERER_FACTORY_H

#include "IRenderer.h"
#include <string>
#include <memory>

class RendererFactory
{
public:
	static IRenderer* makeRenderer(std::string type);
};

#endif