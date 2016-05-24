#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")

#include "GLRenderer.h"
#include <gl\GL.h>
#include "GLProgram.h"
#include "Configuration.h"
#include "SceneLoaderFactory.h"

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
	program->eyeIndex = glGetUniformLocation(program->getID(), "eyeWorldSpace");
	program->materialIndex = glGetUniformBlockIndex(program->getID(),"material");

	_root = std::unique_ptr<Node>(new Node);

	/* Setup the scene */
	std::unique_ptr<ISceneLoader> loader = SceneLoaderFactory::makeLoader(Configuration::getInstance()->getConfiguration("SCENE_LOADER"));
	Scene scene;
	loader->load(scene);

	_root->numMeshes = scene.meshes.size();

	for(unsigned int i = 0; i < scene.meshes.size(); ++i) {
		setupMesh(scene.meshes[i]);
		
		setupMaterial(scene.materials[i]);
	}

	if(scene.textures.size() > 0)
		setupTexture(scene.textures[0], 1);
}
	
void GLRenderer::setupMesh(Mesh& mesh)
{
	unsigned int tmpVBO;

	glGenBuffers(1, &tmpVBO);								// let's generate a buffer to bind at our VBO inside the GPU

	glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);					// and let's bind it...the option GL_ARRAY_BUFFER says that the array will contain only vertices
	glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), mesh.vertices.data() , GL_STATIC_DRAW);	// let's fill the buffer with data
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	_root->setVBO(tmpVBO);
	setupIndices(mesh.indices);
}

void GLRenderer::setupIndices(std::vector<unsigned int>& indices) 
{
	unsigned int tmpIBO;

	glGenBuffers(1, &tmpIBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tmpIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	_root->setIBO(tmpIBO);
	_root->setNumIndices(indices.size());

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_RGBA);
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
	glBindTexture(GL_TEXTURE_2D, 0);
	_root->setTBO(tmpTBO);
}

void GLRenderer::setupMaterial(Material& material)
{
	int blockSize;
	unsigned int tmpUBO;

	glGetActiveUniformBlockiv(program->getID(), program->materialIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);

	std::vector<char> blockBuffer(blockSize);

	// Query for the offsets of each block variable
	const char *names[] = { "material.lightColorAmbient", "material.lightColorDiffuse", "material.direction", "material.lightspecularColor", "material.specularPower" };

	unsigned int indices[5];
	glGetUniformIndices(program->getID(), 5, names, indices);

	int offset[5];
	glGetActiveUniformsiv(program->getID(), 5, indices,GL_UNIFORM_OFFSET, offset);

	memcpy(&blockBuffer[offset[0]], &material._light._lightColorAmbient, sizeof(Vector4f));
	memcpy(&blockBuffer[offset[1]], &material._light._lightColorDiffuse, sizeof(Vector4f));
	memcpy(&blockBuffer[offset[2]], &material._light._direction, sizeof(Vector3f));
	memcpy(&blockBuffer[offset[3]], &material._specularColor, sizeof(Vector4f));
	memcpy(&blockBuffer[offset[4]], &material._specularPower,sizeof(float));

	glGenBuffers( 1, &tmpUBO );
	glBindBuffer( GL_UNIFORM_BUFFER, tmpUBO);
	glBufferData( GL_UNIFORM_BUFFER, blockSize, &blockBuffer[0], GL_STATIC_DRAW );

	glUniformBlockBinding( GL_UNIFORM_BUFFER, program->materialIndex, tmpUBO);

	_root->setUBO(tmpUBO);
}


void GLRenderer::setupLight(Light& light, unsigned int size)
{
}

void GLRenderer::drawCallback(void)
{
	GLRenderer* r = GLRenderer::getInstance();
	r->draw();
}

void GLRenderer::draw()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);			// use the color specified by glClearColor

	_root->setRotation(0.0f, 0.2f, 0.0f);

	glUniformMatrix4fv(program->transformObjIndex, 1, GL_TRUE, (const GLfloat*) _root->getMatrix());
	glUniformMatrix4fv(program->transformCamIndex, 1, GL_TRUE, (const GLfloat*) _root->getCamera());

	glEnableVertexAttribArray(POSITION);
	glEnableVertexAttribArray(COLOR);
	glEnableVertexAttribArray(TEXTURE_COORDINATE);
	glEnableVertexAttribArray(NORMAL);

	//glUniform3f(program->eyeIndex,1,2,0);	//where to point
	glUniform3f(program->eyeIndex, 1,_root->_camera.getCameraPosition().getY(),1);

	for(int i = 0; i < _root->numMeshes; ++i){
		glBindBuffer(GL_ARRAY_BUFFER, _root->getVBO(i));	// let's bind it again to prepare for draw
	
		glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)sizeof(Vector3f));	
		glVertexAttribPointer(TEXTURE_COORDINATE, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(2 * sizeof(Vector3f)));
		glVertexAttribPointer(NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)((2 * sizeof(Vector3f)) + sizeof(Vector2f)));
		
		glBindBufferBase(GL_UNIFORM_BUFFER, program->materialIndex, _root->getUBO(i));
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _root->getIBO(i));

		if(_root->getTBO(i) > 0){
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _root->getTBO(i));
		}

		glDrawElements(GL_TRIANGLES, _root->getNumIndices(i), GL_UNSIGNED_INT, 0);
	}

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

