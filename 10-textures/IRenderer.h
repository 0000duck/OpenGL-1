#ifndef __I_RENDERER_H
#define __I_RENDERER_H

#include "Texture.h"
#include "Mesh.h"

class IRenderer
{
public:
	virtual void draw(void) = 0;
	virtual void setupMesh(Mesh& mesh, unsigned int size) = 0;
	virtual void setupTexture(Texture& texture, unsigned int size) = 0;
	virtual void setDisplayFunc(void(f())) = 0;
	virtual void setIdleFunc(void(f())) = 0;
	virtual void Redisplay(void) = 0;
	virtual void loop(void) = 0;
	virtual ~IRenderer(void) { };
};

#endif
