#pragma comment(lib, "glut32.lib")

#include "GlutWindowSystem.h"
#include "GlutCallbacks.h"

#include "RendererFactory.h"
#include "Configuration.h"
#include "GLRenderer.h"
#include "glut.h"

void GlutWindowSystem::initWindow(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	Configuration *c = Configuration::getInstance();
	int w = std::stoi(c->getConfiguration("WIDTH"));
	int h = std::stoi(c->getConfiguration("HEIGHT"));
	glutInitWindowSize(w, h);
	glutInitWindowPosition(0,0);
	glutCreateWindow("3D Graphics Tutorial");

	glutDisplayFunc(GLRenderer::drawCallback);
	glutIdleFunc(GLRenderer::drawCallback);
	
	GlutCallbacks::getInstance();
	glutKeyboardFunc(GlutCallbacks::key);
	glutSpecialFunc(GlutCallbacks::keySpecial);
	glutMouseFunc(GlutCallbacks::mouse);
	glutMotionFunc(GlutCallbacks::mouseMove);
}

void GlutWindowSystem::redisplay(void)
{
	glutSwapBuffers();
	glutPostRedisplay();
}

void GlutWindowSystem::loop(void)
{
	glutMainLoop();
}