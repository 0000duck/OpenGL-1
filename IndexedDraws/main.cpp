#include <iostream>
#include "glew.h"
#include "glut.h"
#include <gl\GL.h>
#include "math_3d.h"
#include "shader.h"

typedef enum {
	POSITION,
	COLOR
}ATTRIB;

int const winWidth = 480;
int const winHeight = 320;

GLuint VBO_Handle[2];					// this buffer will store the handle of the actual VBO; it REPRESENTS the VBO in this program, but it's not the VBO
GLuint IBO_Handle;					// this handle will point the the indexed buffer in the GPU memory

static GLuint gWorldLocation;

static void initScene(void)
{
	Vector3f v[] = {									// to draw a pyramid we only need 5 vertices that must be shared among the primitives
		Vector3f(-1.0f, -1.0f, 0.0f),
		Vector3f(0.0f, -1.0f, 1.0f),
		Vector3f(1.0f, -1.0f, 0.0f),
		Vector3f(0.0f, 1.0f, 0.0f)
	};

	Vector3f c[] = {
		Vector3f(0.0f, 0.0f, 1.0f),	//blue
		Vector3f(0.0f, 1.0f, 0.0f),	//green
		Vector3f(1.0f, 0.0f, 0.0f),	//red
		Vector3f(1.0f, 1.0f, 1.0f),	//white
	};

	GLuint indices[] = {0, 3, 1,
						1, 3, 2,
						2, 3, 0,
						0, 2, 1,
	};
						

	glGenBuffers(2, VBO_Handle);								// let's generate a buffer to bind at our VBO inside the GPU

	// bind positions buffer and insert vertex positions
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Handle[POSITION]);					
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), &v, GL_STATIC_DRAW);	

	// bind colors buffer and insert vertex colors
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Handle[COLOR]);					
	glBufferData(GL_ARRAY_BUFFER, sizeof(c), &c, GL_STATIC_DRAW);

	// a buffer of indexes must be bound too
	glGenBuffers(1, &IBO_Handle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_Handle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);
}

static void RenderScene(void)
{
	static float angle = 0.0f;
	Matrix4f world;

	glClear(GL_COLOR_BUFFER_BIT);						// use the color specified by glClearColor

	angle += 0.01f;

	world.m[0][0] = cosf(angle);
	world.m[0][1] = 0.0f;
	world.m[0][2] = -sinf(angle);
	world.m[0][3] = 0.0f;
	world.m[1][0] = 0.0f;
	world.m[1][1] = 1.0f;
	world.m[1][2] = 0.0f;
	world.m[1][3] = 0.0f;
	world.m[2][0] = sinf(angle);
	world.m[2][1] = 0.0f;
	world.m[2][2] = cosf(angle);
	world.m[2][3] = 0.0f;
	world.m[3][0] = 0.0f;
	world.m[3][1] = 0.0f;
	world.m[3][2] = 0.0f;
	world.m[3][3] = 1.0f;
	glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &world.m[0][0]);					// update vertex shader's gScale variable with a new value

	glEnableVertexAttribArray(POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Handle[POSITION]);					// let's bind it again to prepare for draw
	glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(COLOR);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Handle[COLOR]);					// let's bind it again to prepare for draw
	glVertexAttribPointer(COLOR, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_Handle);

	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(POSITION);
	glDisableVertexAttribArray(COLOR);
	glutSwapBuffers();									// swap the 2 buffers so the current buffer will go in background, 
														// whereas the old background buffer will be shown

	glutPostRedisplay();								// call the openGL render function (otherwise the window won't be rendered again but only redrawn);
}

int main(int argc, char **argv) 
{
	GLuint program;

	glutInit (&argc, argv);								// initialize GLUT

	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);		// initialize the display to support double buffering and RGBA colors
	glutInitWindowSize (winWidth, winHeight);			// set initial size of the window
	glutInitWindowPosition (0, 0);						// set initial position of the window
	glutCreateWindow("OpenGL tutorial");				// create a window with OpenGL tutorial as title

	glutDisplayFunc(RenderScene);						// define the render function
	glutIdleFunc(RenderScene);

	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return -1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// set the clear Display state to the black color; the windows will use this setting during the whole execution

	initScene();

	program = compileShaders();

	gWorldLocation = glGetUniformLocation(program,"gWorld"); // get the index of the vertex shader where to find the gScale uniform variable
															//knowing the index we can change this value from our application and see the shape moving

	glutMainLoop();

	return 0;
}