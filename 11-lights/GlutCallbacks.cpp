#include "GlutCallbacks.h"
#include "GLRenderer.h"

GlutCallbacks* GlutCallbacks::getInstance()
{
	static GlutCallbacks c;
	return &c;
}

GlutCallbacks::GlutCallbacks()
{
	GLRenderer* r = GLRenderer::getInstance();
	_root = r->getTree();
}

void GlutCallbacks::keySpecial(int key, int x, int y)
{
	Node* _root = (getInstance()->_root);
	switch(key){
	case GLUT_KEY_UP:
		_root->setCameraPosition(0.0f, 1.0f, 0.0f);
		break;
	case GLUT_KEY_DOWN:
		_root->setCameraPosition(0.0f, -1.0f, 0.0f);
		break;
	case GLUT_KEY_RIGHT:
		_root->setCameraPosition(1.0f, 0.0f, 0.0f);
		break;
	case GLUT_KEY_LEFT:
		_root->setCameraPosition(-1.0f, 0.0f, 0.0f);
		break;
	}
}

void GlutCallbacks::key(unsigned char key, int x, int y)
{
	Node *_root = (getInstance()->_root);
	switch(key){
	case 'w':
		_root->setRotation(1.0f, 0.0f, 0.0f);
		break;
	case 'q':
		_root->setRotation(-1.0f, 0.0f, 0.0f);
		break;
	case 's':
		_root->setRotation(0.0f, 1.0f, 0.0f);
		break;
	case 'a':
		_root->setRotation(0.0f, -1.0f, 0.0f);
		break;
	case 'x':
		_root->setRotation(0.0f, 0.0f, 1.0f);
		break;
	case 'z':
		_root->setRotation(0.0f, 0.0f, -1.0f);
		break;
	case 'e':
		_root->setTranslation(0.1f, 0.0f, 0.0f);
		break;
	case 'r':
		_root->setTranslation(-0.1f, 0.0f, 0.0f);
		break;
	case 'f':
		_root->setTranslation(0.0f, 0.1f, 0.0f);
		break;
	case 'd':
		_root->setTranslation(0.0f, -0.1f, 0.0f);
		break;
	case 'c':
		_root->setTranslation(0.0f, 0.0f, 0.1f);
		break;
	case 'v':
		_root->setTranslation(0.0f, 0.0f, -0.1f);
		break;
	case 'y':
		_root->setScaling(0.1f, 0.0f, 0.0f);
		break;
	case 't':
		_root->setScaling(-0.1f, 0.0f, 0.0f);
		break;
	case 'h':
		_root->setScaling(0.0f, 0.1f, 0.0f);
		break;
	case 'g':
		_root->setScaling(0.0f, -0.1f, 0.0f);
		break;
	case 'n':
		_root->setScaling(0.0f, 0.0f, 0.1f);
		break;
	case 'b':
		_root->setScaling(0.0f, 0.0f, -0.1f);
		break;
	/*case ' ':
		_root->changeWireframeView();*/
		break;
	}
}

void GlutCallbacks::mouse(int button, int state, int x, int y)
{
	GlutCallbacks* gc = getInstance();
	if(button == GLUT_LEFT_BUTTON){
		if(state == GLUT_DOWN) {
			gc->leftPressed = GL_TRUE;
			gc->mouseX = x;
			gc->mouseY = y;
		} else if (state == GLUT_UP) {
			gc->leftPressed = GL_FALSE;
			gc->mouseX = 0.0f;
			gc->mouseY = 0.0f;
		}
	} else if(button == GLUT_RIGHT_BUTTON){
		if(state == GLUT_DOWN) {
			gc->rightPressed = GL_TRUE;
			gc->mouseX = x;
			gc->mouseY = y;
		} else if (state == GLUT_UP) {
			gc->rightPressed = GL_FALSE;
			gc->mouseX = 0.0f;
			gc->mouseY = 0.0f;
		}
	} 
}

void GlutCallbacks::mouseMove(int x, int y)
{
	GlutCallbacks* gc = getInstance();
	Node *_root = (getInstance()->_root);
	if(gc->rightPressed == GL_TRUE) {
		_root->setCameraPosition(gc->mouseX -x, gc->mouseY - y, 0.0f);
		gc->mouseX = x;
		gc->mouseY = y;
		glutPostRedisplay();
	} else if(gc->leftPressed == GL_TRUE) {
		_root->setCameraTarget(x - gc->mouseX, y - gc->mouseY, 0.0f);
		gc->mouseX = x;
		gc->mouseY = y;
		glutPostRedisplay();
	}
}