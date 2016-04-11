//VERTEX SHADER: simple scaling effect centered on 0 (no intrinsic translation)
#version 330

//NON-UNIFORM VARIABLES: vertex specific.....they are reloaded with a new value every time a new vertex is processed
in vec3 Position;

//UNIFORM VARIABLES: variables that remains constant through the whole draw call...very similar top the global variable concept
uniform float gScale;

void main()
{
	gl_Position = vec4(gScale * Position.x, gScale * Position.y, Position.z, 1.0);
}