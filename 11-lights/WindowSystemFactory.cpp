#include "WindowSystemFactory.h"
#include "GlutWindowSystem.h"
#include "QtWindowSystem.h"

std::unique_ptr<IWindowSystem> WindowSystemFactory::makeWindowSystem(std::string type)
{
	if(type == "glut")
		return std::unique_ptr<GlutWindowSystem>(new GlutWindowSystem);
	else if(type == "qt")
		return std::unique_ptr<QtWindowSystem>(new QtWindowSystem);
	return std::unique_ptr<GlutWindowSystem>(new GlutWindowSystem);
}