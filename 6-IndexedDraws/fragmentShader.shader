//FRAGMENT SHADER: set red color to each fragment

#version 330
//vertexColor is passed from the vertex shader to the rasterizer and then, to the fragment shader
in vec4 vertexColor;
out vec4 fragmentColor;

void main()
{
	fragmentColor = vertexColor;
}