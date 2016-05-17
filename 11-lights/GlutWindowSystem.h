#ifndef __GLUT_WINDOW_SYSTEM_H
#define __GLUT_WINDOW_SYSTEM_H

#include "IWindowSystem.h"

class GlutWindowSystem : public IWindowSystem
{
public:
	void initWindow(int argc, char **argv);
	void redisplay(void);
	void loop(void);
};

#endif