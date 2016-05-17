#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")

#include "GLRenderer.h"
#include <gl\GL.h>
#include "GLProgram.h"
#include "Configuration.h"
#include "RawSceneLoader.h"

GLRenderer* GLRenderer::getInstance(void)
{
	static GLRenderer instance;
	return &instance;
}

Node* GLRenderer::getTree(void)
{
	return _root.get();
}

void GLRenderer::setWindowManager(IWindowSystem *win)
{
	window = win;
}

GLRenderer::GLRenderer(void)
{
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// set the clear Display state to the black color; the windows will use this setting during the whole execution

	program = std::unique_ptr<GLProgram>(new GLProgram());
	program->run();
	program->transformObjIndex = glGetUniformLocation(program->getID(),"gObjectTransform");
	program->transformCamIndex = glGetUniformLocation(program->getID(),"gCamera");
	program->lightColorIndex = glGetUniformLocation(program->getID(), "light.lightColor");
	program->ambientIntensityIndex = glGetUniformLocation(program->getID(), "light.intensityAmbient");
	program->diffuseIntensityIndex = glGetUniformLocation(program->getID(), "light.intensityDiffuse");
	program->directionIndex = glGetUniformLocation(program->getID(), "light.direction");
	program->eyeIndex = glGetUniformLocation(program->getID(), "eyeWorldSpace");
	program->specularIntensityIndex = glGetUniformLocation(program->getID(), "specularIntensity");
	program->specularPowerIndex = glGetUniformLocation(program->getID(), "specularPower");

	_root = std::unique_ptr<Node>(new Node);

	/* Setup the scene */

	RawSceneLoader loader;
	Scene scene;
	loader.load(scene);

	setupMesh(scene.meshes[0],1);
	setupTexture(scene.textures[0],1);
	setupLight(scene.lights[0], 1);
	setupMaterial(scene.materials[0],1);
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

	//_root->setTranslation(0.0f,0.0f,5.0f);
}

void GLRenderer::setupTexture(Texture& texture, unsigned int size)
{
	unsigned int tmpTBO;

	glGenTextures(1, &tmpTBO);			     //generate a buffer
	glBindTexture(GL_TEXTURE_2D, tmpTBO);     // and bind it to the GL_TEXTURE_2D binding point

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.image);   // finally send the data of the image

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// minification filter = linear
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//magnification filter = linear

	glEnable(GL_TEXTURE_2D);

	_root->setTBO(tmpTBO);
}

void GLRenderer::setupLight(Light& light, unsigned int size)
{
	light._direction.Normalize();
	glUniform3f(program->lightColorIndex, light._lightColor.getX(), light._lightColor.getY(), light._lightColor.getZ());
	glUniform1fv(program->ambientIntensityIndex,1, &light._intensityAmbient);
    glUniform1f(program->diffuseIntensityIndex, light._intensityDiffuse);
	glUniform3f(program->directionIndex, light._direction.getX(), light._direction.getY(), light._direction.getZ());
}

void GLRenderer::setupMaterial(Material& material, unsigned int size)
{
	glUniform3f(program->eyeIndex, _root->_camera.getCameraPosition().getX(),_root->_camera.getCameraPosition().getY(),_root->_camera.getCameraPosition().getZ());			
	glUniform1fv(program->specularIntensityIndex,1, &material._specularIntensity);
	glUniform1fv(program->specularPowerIndex,1, &material._specularPower);
}

void GLRenderer::drawCallback(void)
{
	GLRenderer* r = GLRenderer::getInstance();
	r->draw();
}

void GLRenderer::draw()
{
	static float tmp = 0.5;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);			// use the color specified by glClearColor

	_root->setRotation(0.0f, tmp, 0.0f);
	glUniformMatrix4fv(program->transformObjIndex, 1, GL_TRUE, (const GLfloat*) _root->getMatrix());
	glUniformMatrix4fv(program->transformCamIndex, 1, GL_TRUE, (const GLfloat*) _root->getCamera());

	glUniform3f(program->eyeIndex, 0.0f, 0.0f,0.0f);	

	glEnableVertexAttribArray(POSITION);
	glEnableVertexAttribArray(COLOR);
	glEnableVertexAttribArray(TEXTURE_COORDINATE);
	glEnableVertexAttribArray(NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, _root->getVBO());	// let's bind it again to prepare for draw
	
	glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)sizeof(Vector3f));	
	glVertexAttribPointer(TEXTURE_COORDINATE, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(2 * sizeof(Vector3f)));
	glVertexAttribPointer(NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)((2 * sizeof(Vector3f)) + sizeof(Vector2f)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _root->getIBO());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _root->getTBO());

	glDrawElements(GL_TRIANGLES, _root->getNumIndices(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(NORMAL);
	glDisableVertexAttribArray(TEXTURE_COORDINATE);
	glDisableVertexAttribArray(COLOR);
	glDisableVertexAttribArray(POSITION);

	Redisplay();
}

void GLRenderer::Redisplay(void)
{
	if(window)
		window->redisplay();
}

