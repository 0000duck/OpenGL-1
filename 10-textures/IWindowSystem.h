#ifndef __IWINDOWSYSTEM_H
#define __IWINDOWSYSTEM_H

#include <string>

class IWindowSystem 
{
public:
	virtual void initWindow(int argc, char **argv) = 0;
	virtual void setWindowMode(unsigned int mode) = 0;
	virtual void setWindowSize(unsigned int width, unsigned int height) = 0;
	virtual void setWindowPosition(unsigned int x, unsigned int y) = 0;
	virtual void dispatchWindow(std::string title) = 0;
	virtual void setDisplayFunction(void (func())) = 0;
	virtual void setIdleFunction(void (func())) = 0;
	virtual void registerKeyboardCallback(void (func(unsigned char key, int x, int y))) = 0;
	virtual void registerKeyboardSpecialCallback(void (func(int key, int x, int y))) = 0;
	virtual void registerMouseCallback(void (func(int button, int state, int x, int y))) = 0;
	virtual void registerMotionCallback(void (func(int x, int y))) = 0;
	virtual void swapBuffers(void) = 0;
	virtual void redisplay(void) = 0;
	virtual void loop(void) = 0;
};

#endif