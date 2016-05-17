#ifndef __I_RENDERER_H
#define __I_RENDERER_H

#include "Texture.h"
#include "Mesh.h"
#include "Light.h"
#include "Material.h"
#include "IWindowSystem.h"

class IRenderer
{
public:
	virtual void draw(void) = 0;
	virtual void setupMesh(Mesh& mesh, unsigned int size) = 0;
	virtual void setupTexture(Texture& texture, unsigned int size) = 0;
	virtual void setupLight(Light& light, unsigned int size) = 0;
	virtual void setupMaterial(Material& material, unsigned int size) = 0;
	virtual void Redisplay(void) = 0;
	virtual void setWindowManager(IWindowSystem* win) = 0;
	virtual ~IRenderer(void) { };

protected:
		IWindowSystem *window;
};

#endif
