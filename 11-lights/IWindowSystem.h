#ifndef __IWINDOWSYSTEM_H
#define __IWINDOWSYSTEM_H

#include <string>

class IWindowSystem 
{
public:
	virtual void initWindow(int argc, char **argv) = 0;
	virtual void redisplay(void) = 0;
	virtual void loop(void) = 0;
};

#endif