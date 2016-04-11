//VERTEX SHADER: simple color changing effect. The color usually is given through the vertex buffer from the user application or is taken from a texture given by the user application
#version 330

//NON-UNIFORM VARIABLES: vertex specific.....they are reloaded with a new value every time a new vertex is processed
in vec3 Position;	// in parameters are received from the user application 
out vec4 vertexColor;		// out parameters are sent to the rasterizer and then to the fragment shader

//UNIFORM VARIABLES: variables that remains constant through the whole draw call...very similar top the global variable concept
uniform mat4 gWorld;

void main()
{
	gl_Position = gWorld * vec4(Position, 1.0);
	vertexColor = vec4(clamp(Position, 0.0, 1.0), 1.0);	//clamp makes sure that the values stay in the range [0.0, 1.0];
}