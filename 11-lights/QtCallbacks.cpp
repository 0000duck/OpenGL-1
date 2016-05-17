#include "GLRenderer.h"
#include "QtCallbacks.h"

QtCallbacks::QtCallbacks()
{
	leftPressed = false;
	rightPressed = false;
	middlePressed = false;
}

void QtCallbacks::paintGL()
{
	GLRenderer::getInstance()->draw();
}

void QtCallbacks::keyPressEvent(QKeyEvent* evt)
{
	Node *_root = (GLRenderer::getInstance()->getTree());
	switch(evt->key()){
	case 'W':
		_root->setRotation(1.0f, 0.0f, 0.0f);
		break;
	case 'Q':
		_root->setRotation(-1.0f, 0.0f, 0.0f);
		break;
	case 'S':
		_root->setRotation(0.0f, 1.0f, 0.0f);
		break;
	case 'A':
		_root->setRotation(0.0f, -1.0f, 0.0f);
		break;
	case 'X':
		_root->setRotation(0.0f, 0.0f, 1.0f);
		break;
	case 'Z':
		_root->setRotation(0.0f, 0.0f, -1.0f);
		break;
	case 'E':
		_root->setTranslation(0.1f, 0.0f, 0.0f);
		break;
	case 'R':
		_root->setTranslation(-0.1f, 0.0f, 0.0f);
		break;
	case 'F':
		_root->setTranslation(0.0f, 0.1f, 0.0f);
		break;
	case 'D':
		_root->setTranslation(0.0f, -0.1f, 0.0f);
		break;
	case 'C':
		_root->setTranslation(0.0f, 0.0f, 0.1f);
		break;
	case 'V':
		_root->setTranslation(0.0f, 0.0f, -0.1f);
		break;
	case 'Y':
		_root->setScaling(0.1f, 0.0f, 0.0f);
		break;
	case 'T':
		_root->setScaling(-0.1f, 0.0f, 0.0f);
		break;
	case 'H':
		_root->setScaling(0.0f, 0.1f, 0.0f);
		break;
	case 'G':
		_root->setScaling(0.0f, -0.1f, 0.0f);
		break;
	case 'N':
		_root->setScaling(0.0f, 0.0f, 0.1f);
		break;
	case 'B':
		_root->setScaling(0.0f, 0.0f, -0.1f);
		break;
	case Qt::Key_Up:
		_root->setCameraPosition(0.0f, 1.0f, 0.0f);
		break;
	case Qt::Key_Down:
		_root->setCameraPosition(0.0f, -1.0f, 0.0f);
		break;
	case Qt::Key_Right:
		_root->setCameraPosition(1.0f, 0.0f, 0.0f);
		break;
	case Qt::Key_Left:
		_root->setCameraPosition(-1.0f, 0.0f, 0.0f);
		break;
	/*case ' ':
		_root->changeWireframeView();*/
		
	}
}

void QtCallbacks::mousePressEvent(QMouseEvent *evt)
{
	switch(evt->button()){
	case Qt::LeftButton:
		leftPressed = true;
		point = evt->pos();
		break;
	
	case Qt::RightButton:
		rightPressed = true;
		point = evt->pos();
		break;
	}
}

void QtCallbacks::mouseReleaseEvent(QMouseEvent* evt)
{
	switch(evt->button()){
	case Qt::LeftButton:
		leftPressed = false;
		point = QPoint(0,0);
		break;
	
	case Qt::RightButton:
		rightPressed = false;
		point = QPoint(0,0);
		break;
	}
}

void QtCallbacks::mouseMoveEvent(QMouseEvent *evt)
{
	Node *_root = (GLRenderer::getInstance()->getTree());
	if(rightPressed) {
		_root->setCameraPosition(point.x() - evt->pos().x(), point.y() - evt->pos().y(), 0.0f);
		point = evt->pos();
	} else if(leftPressed) {
		_root->setCameraTarget(evt->pos().x() - point.x(), evt->pos().y() - point.y(), 0.0f);
		point = evt->pos();
	}
}

