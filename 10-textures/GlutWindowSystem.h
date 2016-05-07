#ifndef __GLUT_WINDOW_SYSTEM_H
#define __GLUT_WINDOW_SYSTEM_H

#include "IWindowSystem.h"

class GlutWindowSystem : public IWindowSystem
{
public:
	void initWindow(int argc, char **argv);
	void setWindowMode(unsigned int mode);
	void setWindowSize(unsigned int width, unsigned int height);
	void setWindowPosition(unsigned int x, unsigned int y);
	void dispatchWindow(std::string title);
	void setDisplayFunction(void (func()));
	void setIdleFunction(void (func()));
	void registerKeyboardCallback(void (func(unsigned char key, int x, int y)));
	void registerKeyboardSpecialCallback(void (func(int key, int x, int y)));
	void registerMouseCallback(void (func(int button, int state, int x, int y)));
	void registerMotionCallback(void (func(int x, int y)));
	void swapBuffers(void);
	void redisplay(void);
	void loop(void);
};

#endif