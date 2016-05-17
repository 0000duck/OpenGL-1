//VERTEX SHADER
#version 330

//NON-UNIFORM VARIABLES: vertex specific.....they are reloaded with a new value every time a new vertex is processed
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Color;
layout (location = 2) in vec2 TexCoord;
layout (location = 3) in vec3 Normal;

out vec2 texCoord;
out vec3 color;
out vec3 normal;
out vec3 worldSpacePos;

//UNIFORM VARIABLES: variables that remains constant through the whole draw call...very similar top the global variable concept
uniform mat4 gWorld;
uniform mat4 gObjectTransform;
uniform mat4 gCamera;

void main()
{
	worldSpacePos = (gObjectTransform * vec4(Position, 1.0)).xyz;		//position of the vertex in world space
	gl_Position = gCamera * vec4(worldSpacePos, 1.0);					//position of the vertex in screen space
	color = Color;
	normal = (gObjectTransform * vec4(Normal, 0.0)).xyz;                //normal of the vertex in world space
	texCoord = TexCoord;
}