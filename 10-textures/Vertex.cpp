#include "Vertex.h"


Vertex::Vertex(Vector3f position, Vector3f color,Vector2f texture):
	_position(position), _color(color), _texture(texture)
{
}

Vector3f Vertex::getPosition(void)
{
	return _position;
}

Vector3f Vertex::getColor(void)
{
	return _color;
}
