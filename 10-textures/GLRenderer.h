#ifndef __GLRENDERER_H
#define __GLRENDERER_H

#include "IRenderer.h"
#include "GLProgram.h"
#include "IWindowSystem.h"
#include <memory>
#include "Node.h"

/* SINGLETON....i need a static callback which refers to the callbacks (glut needs it.....is there a better way????*/
class GLRenderer : public IRenderer
{
public:
	void setupMesh(Mesh& mesh, unsigned int size);
	void setupTexture(Texture& texture, unsigned int size);
	static GLRenderer* getInstance(void);
	Node* getTree(void);
	static void drawCallback(void);
	void draw(void);
	void setDisplayFunc(void(f()));
	void setIdleFunc(void(f()));
	void Redisplay(void);
	void loop(void);

private:
	GLRenderer(void);
	std::unique_ptr<GLProgram> program;
	std::unique_ptr<IWindowSystem> window;

	std::shared_ptr<Node> _root;

	//here are all the uniform variables!
	unsigned int transformIndex;
};

#endif