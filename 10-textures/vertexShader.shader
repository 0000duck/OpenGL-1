//VERTEX SHADER
#version 330

//NON-UNIFORM VARIABLES: vertex specific.....they are reloaded with a new value every time a new vertex is processed
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Color;
layout (location = 2) in vec2 TexCoord;

out vec2 texCoord;
out vec3 color;

//UNIFORM VARIABLES: variables that remains constant through the whole draw call...very similar top the global variable concept
uniform mat4 gWorld;

void main()
{
	gl_Position = gWorld * vec4(Position, 1.0);
	color = Color;
	texCoord = TexCoord;
}