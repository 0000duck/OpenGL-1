#ifndef __QT_WINDOW_SYSTEM_H
#define __QT_WINDOW_SYSTEM_H

#include "IWindowSystem.h"
#include <QtWidgets\qopenglwidget.h>
#include <QtWidgets\qapplication.h>
#include <memory>

class QtWindowSystem : public IWindowSystem
{
public:
	void initWindow(int argc, char **argv);
	void redisplay(void);
	void loop(void);

private:
	std::unique_ptr<QOpenGLWidget> window;
	std::unique_ptr<QApplication> app;
};

#endif