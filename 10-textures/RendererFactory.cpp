#include "RendererFactory.h"
#include "GLRenderer.h"

IRenderer* RendererFactory::makeRenderer(std::string type)
{
	if(type == "openGL"){
		return GLRenderer::getInstance();
	}
	return nullptr;
}