#ifndef __VERTEX_H
#define __VERTEX_H

#include "math_3d.h"

enum Attributes
{
	POSITION = 0,
	COLOR = 1,
	TEXTURE_COORDINATE = 2
};

class Vertex
{
public:
	Vertex(
		Vector3f position = Vector3f(0.0f, 0.0f, 0.0f), 
		Vector3f color = Vector3f(1.0f, 1.0f, 1.0f), 
		Vector2f texture = Vector2f(0.0f, 0.0f)
		);

	void setTextureCoordinate(Vector2f texture);
	void setNormal(Vector3f normal);
	Vector3f getPosition(void);
	Vector3f getColor(void);

private:
	Vector3f _position;
	Vector3f _color;	
	Vector2f _texture;
};

#endif