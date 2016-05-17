#pragma comment(lib, "Qt5Cored.lib")
#pragma comment(lib, "Qt5Guid.lib")
#pragma comment(lib, "Qt5OpenGLd.lib")
#pragma comment(lib, "Qt5Widgetsd.lib")

#include "GLRenderer.h"
#include "QtWindowSystem.h"
#include "Configuration.h"
#include <iostream>
#include "QtCallbacks.h"

void QtWindowSystem::initWindow(int argc, char **argv)
{
	app = std::unique_ptr<QApplication>(new QApplication(argc,argv));
	window = std::unique_ptr<QtCallbacks>(new QtCallbacks);
	Configuration *c = Configuration::getInstance();
	int w = std::stoi(c->getConfiguration("WIDTH"));
	int h = std::stoi(c->getConfiguration("HEIGHT"));
	window->resize(w, h);
	window->move(0, 0);
	window->setWindowTitle(QString("3D Graphics Tutorial"));
	window->show();
}

void QtWindowSystem::redisplay(void)
{
	window->update();
}

void QtWindowSystem::loop(void)
{
	app->exec();
}
