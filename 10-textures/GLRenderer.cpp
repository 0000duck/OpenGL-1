#include "GLRenderer.h"
#include "glew.h"
#include "glut.h"
#include <gl\GL.h>
#include "GLProgram.h"
#include "Configuration.h"
#include "WindowSystemFactory.h"
#include "RawSceneLoader.h"
#include "GlutCallbacks.h"
#include "Texture.h"

GLRenderer* GLRenderer::getInstance(void)
{
	static GLRenderer instance;
	return &instance;
}

Node* GLRenderer::getTree(void)
{
	return _root.get();
}

GLRenderer::GLRenderer(void)
{
	char *myargv [1];
	int myargc=1;
	myargv [0]="Myappname";

	window = WindowSystemFactory::makeWindowSystem(Configuration::getInstance()->getConfiguration("WINSYS"));
	window->initWindow(myargc, myargv);
	window->setWindowMode(GLUT_DOUBLE | GLUT_RGBA);
	
	Configuration *c = Configuration::getInstance();
	int w = std::stoi(c->getConfiguration("WIDTH"));
	int h = std::stoi(c->getConfiguration("HEIGHT"));
	window->setWindowSize(w, h);
	window->setWindowPosition(0,0);
	window->dispatchWindow("3D Graphics Tutorial");

	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// set the clear Display state to the black color; the windows will use this setting during the whole execution

	window->setDisplayFunction(GLRenderer::drawCallback);
	window->setIdleFunction(GLRenderer::drawCallback);

	program = std::unique_ptr<GLProgram>(new GLProgram());
	program->run();
	transformIndex = glGetUniformLocation(program->getID(),"gWorld");

	_root = std::unique_ptr<Node>(new Node);

	RawSceneLoader loader;
	Scene scene;
	loader.load(scene);

	setupMesh(scene.meshes[0],1);

	Texture texture;

	setupTexture(texture,1);

	GlutCallbacks::getInstance();

	window->registerKeyboardCallback(GlutCallbacks::key);
	window->registerKeyboardSpecialCallback(GlutCallbacks::keySpecial);
	window->registerMouseCallback(GlutCallbacks::mouse);
	window->registerMotionCallback(GlutCallbacks::mouseMove);
}
	
void GLRenderer::setupMesh(Mesh& mesh, unsigned int size)
{
	unsigned int tmpVBO;
	unsigned int tmpIBO;

	glGenBuffers(1, &tmpVBO);								// let's generate a buffer to bind at our VBO inside the GPU

	glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);					// and let's bind it...the option GL_ARRAY_BUFFER says that the array will contain only vertices
	glBufferData(GL_ARRAY_BUFFER, size * mesh.getNumVertices() * sizeof(Vertex), mesh.getVertices() , GL_STATIC_DRAW);	// let's fill the buffer with data

	_root->setVBO(tmpVBO);

	glGenBuffers(1, &tmpIBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tmpIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * mesh.getNumIndices() * sizeof(unsigned int), mesh.getIndices(), GL_STATIC_DRAW);

	_root->setIBO(tmpIBO);
	_root->setNumIndices(mesh.getNumIndices());

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	_root->setTranslation(0.0f,0.0f,5.0f);
}

void GLRenderer::setupTexture(Texture& texture, unsigned int size)
{
	unsigned int tmpTBO;

	glGenTextures(1, &tmpTBO);			     //generate a buffer
	glBindTexture(GL_TEXTURE_2D, tmpTBO);     // and bind it to the GL_TEXTURE_2D binding point

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.image);   // finally send the data of the image

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// minification filter = linear
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//magnification filter = linear

	_root->setTBO(tmpTBO);
}

void GLRenderer::drawCallback(void)
{
	GLRenderer* r = GLRenderer::getInstance();
	r->draw();
}

void GLRenderer::draw()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);			// use the color specified by glClearColor

	glEnableVertexAttribArray(POSITION);
	glEnableVertexAttribArray(COLOR);
	glEnableVertexAttribArray(TEXTURE_COORDINATE);

	glBindBuffer(GL_ARRAY_BUFFER, _root->getVBO());	// let's bind it again to prepare for draw
	
	glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);	// index = 0, num components = 3 (X, Y, Z), data type of the components = float	
	glVertexAttribPointer(COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)sizeof(Vector3f));	// index = 0, num components = 3 (X, Y, Z), data type of the components = float
	glVertexAttribPointer(TEXTURE_COORDINATE, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(2 * sizeof(Vector3f)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _root->getIBO());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _root->getTBO());

	glDrawElements(GL_TRIANGLES, _root->getNumIndices(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(TEXTURE_COORDINATE);
	glDisableVertexAttribArray(COLOR);
	glDisableVertexAttribArray(POSITION);

	glUniformMatrix4fv(transformIndex, 1, GL_TRUE, (const GLfloat*) _root->getMatrix());

	Redisplay();
}

void GLRenderer::Redisplay(void)
{
	window->swapBuffers();
	window->redisplay();
}

void GLRenderer::setDisplayFunc(void(f()))
{
	window->setDisplayFunction(f);
}

void GLRenderer::setIdleFunc(void(f()))
{
	window->setIdleFunction(f);
}

void GLRenderer::loop(void)
{
	window->loop();
}

