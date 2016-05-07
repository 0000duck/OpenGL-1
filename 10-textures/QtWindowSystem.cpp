#include "QtWindowSystem.h"

void QtWindowSystem::initWindow(int argc, char **argv)
{
	app = std::unique_ptr<QApplication>(new QApplication(argc,argv));
	window = std::unique_ptr<QOpenGLWidget>(new QOpenGLWidget);
	app->exec();
}

void QtWindowSystem::setWindowMode(unsigned int mode)
{
}

void QtWindowSystem::setWindowSize(unsigned int width, unsigned int height)
{
	window->resize(width, height);
}

void QtWindowSystem::setWindowPosition(unsigned int x, unsigned int y)
{
	window->move(x,y);
}

void QtWindowSystem::dispatchWindow(std::string title)
{
	window->setWindowTitle(QString(title.c_str()));
	window->show();
}

void QtWindowSystem::setDisplayFunction(void (func()))
{
}

void QtWindowSystem::setIdleFunction(void (func()))
{
}

void QtWindowSystem::registerKeyboardCallback(void (func(unsigned char key, int x, int y)))
{
	//glutKeyboardFunc(func);
}

void QtWindowSystem::registerKeyboardSpecialCallback(void (func(int key, int x, int y)))
{
	//glutSpecialFunc(func);
}

void QtWindowSystem::registerMouseCallback(void (func(int button, int state, int x, int y)))
{
	//glutMouseFunc(func);
}

void QtWindowSystem::swapBuffers(void)
{
}

void QtWindowSystem::redisplay(void)
{
	//glutPostRedisplay();
}

void QtWindowSystem::loop(void)
{
	//glutMainLoop();
}