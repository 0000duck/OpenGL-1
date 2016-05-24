#ifndef __WINDOW_SYSTEM_FACTORY_H
#define __WINDOW_SYSTEM_FACTORY_H

#include "IWindowSystem.h"
#include <string>
#include <memory>

class WindowSystemFactory
{
public:
	static std::unique_ptr<IWindowSystem> makeWindowSystem(std::string type);
};

#endif