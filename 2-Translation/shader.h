#ifndef __SHADER_H
#	define __SHADER_H
#	define VERTEX_SHADER_FILE	"vertexShader.shader"
#	define FRAGMENT_SHADER_FILE	"fragmentShader.shader"

#	include "glew.h"
#	include "glut.h"
#	include <gl\GL.h>
#	include "math_3d.h"

	//----compileShaders-----
	// Prepare the GL pipeline and attach the shaders to it
	GLuint compileShaders(void);

#endif