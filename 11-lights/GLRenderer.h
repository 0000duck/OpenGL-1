#ifndef __GLRENDERER_H
#define __GLRENDERER_H

#include "IRenderer.h"
#include "GLProgram.h"
#include "IWindowSystem.h"
#include <memory>
#include "Node.h"

/* SINGLETON....i need a static callback which refers to the draw function */
class GLRenderer : public IRenderer
{
public:
	void setupMesh(Mesh& mesh, unsigned int size);
	void setupTexture(Texture& texture, unsigned int size);
	void setupLight(Light& light, unsigned int size);
	void setupMaterial(Material& material, unsigned int size);
	static GLRenderer* getInstance(void);
	Node* getTree(void);
	static void drawCallback(void);
	void draw(void);
	void setWindowManager(IWindowSystem* win);
	void Redisplay(void);

private:
	GLRenderer(void);
	std::unique_ptr<GLProgram> program;

	std::shared_ptr<Node> _root;
};

#endif