#include "GlutWindowSystem.h"
#include "glut.h"

void GlutWindowSystem::initWindow(int argc, char **argv)
{
	glutInit(&argc, argv);
}

void GlutWindowSystem::setWindowMode(unsigned int mode)
{
	glutInitDisplayMode(mode);
}

void GlutWindowSystem::setWindowSize(unsigned int width, unsigned int height)
{
	glutInitWindowSize(width, height);
}

void GlutWindowSystem::setWindowPosition(unsigned int x, unsigned int y)
{
	glutInitWindowPosition(x,y);
}

void GlutWindowSystem::dispatchWindow(std::string title)
{
	glutCreateWindow(title.c_str());
}

void GlutWindowSystem::setDisplayFunction(void (func()))
{
	glutDisplayFunc(func);
}

void GlutWindowSystem::setIdleFunction(void (func()))
{
	glutIdleFunc(func);
}

void GlutWindowSystem::registerKeyboardCallback(void (func(unsigned char key, int x, int y)))
{
	glutKeyboardFunc(func);
}

void GlutWindowSystem::registerKeyboardSpecialCallback(void (func(int key, int x, int y)))
{
	glutSpecialFunc(func);
}

void GlutWindowSystem::registerMouseCallback(void (func(int button, int state, int x, int y)))
{
	glutMouseFunc(func);
}

void GlutWindowSystem::registerMotionCallback(void (func(int x, int y)))
{
	glutMotionFunc(func);
}

void GlutWindowSystem::swapBuffers(void)
{
	glutSwapBuffers();
}

void GlutWindowSystem::redisplay(void)
{
	glutPostRedisplay();
}

void GlutWindowSystem::loop(void)
{
	glutMainLoop();
}