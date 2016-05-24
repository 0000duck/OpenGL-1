#ifndef __QT_CALLBACKS_H
#define __QT_CALLBACKS_H

#include <QtWidgets\qopenglwidget.h>
#include <QtGui\QKeyEvent>
#include <QtGui\QMouseEvent>

class QtCallbacks : public QOpenGLWidget
{
public:
	QtCallbacks();

private:
	void paintGL(void);
	void keyPressEvent(QKeyEvent *evt);
	void mousePressEvent(QMouseEvent *evt);
	void mouseReleaseEvent(QMouseEvent* evt);
	void mouseMoveEvent(QMouseEvent *evt);

private:
	QPoint point;

	bool leftPressed;
	bool rightPressed;
	bool middlePressed;
};

#endif