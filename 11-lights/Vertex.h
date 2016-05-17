#ifndef __VERTEX_H
#define __VERTEX_H

#include "math_3d.h"

enum Attributes
{
	POSITION = 0,
	COLOR = 1,
	TEXTURE_COORDINATE = 2,
	NORMAL = 3
};

class Vertex
{
public:
	Vertex(Vector3f position, Vector3f color, Vector2f texture, Vector3f normal);

	void setTextureCoordinate(Vector2f texture);
	void setNormal(Vector3f normal);
	Vector3f getPosition(void);
	Vector3f getColor(void);

private:
	Vector3f _position;
	Vector3f _color;	
	Vector2f _texture;
	Vector3f _normal;
};

#endif