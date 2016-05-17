#include "Vertex.h"


Vertex::Vertex(Vector3f position, Vector3f color, Vector2f texture, Vector3f normal):
	_position(position), _color(color), _texture(texture), _normal(normal)
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
