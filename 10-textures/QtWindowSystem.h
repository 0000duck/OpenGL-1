#ifndef __QT_WINDOW_SYSTEM_H
#define __QT_WINDOW_SYSTEM_H

#include "IWindowSystem.h"
#include "QtWidgets\qopenglwidget.h"
#include "QtWidgets\qapplication.h"
#include <memory>

class QtWindowSystem : public IWindowSystem
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
	void swapBuffers(void);
	void redisplay(void);
	void loop(void);

private:
	std::unique_ptr<QOpenGLWidget> window;
	std::unique_ptr<QApplication> app;
};

#endif