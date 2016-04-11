//FRAGMENT SHADER: set red color to each fragment

#version 330

in vec4 vertexColor;
out vec4 fragmentColor;

void main()
{
	fragmentColor = vertexColor;
}