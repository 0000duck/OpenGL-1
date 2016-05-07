#ifndef __SHADER_H
#define __SHADER_H
#define VERTEX_SHADER_FILE	"vertexShader.shader"
#define FRAGMENT_SHADER_FILE	"fragmentShader.shader"

#include "glew.h"
#include "glut.h"
#include <gl\GL.h>
#include <string>

class Shader
{
public:
	Shader(GLenum type);
	bool compile(std::string fileName);
	bool checkErrors(void);
	unsigned int getID(void);
private:
	int readSrc(const char *fileName, char *buffer);
	unsigned int ID;
	GLenum shaderType;
};






	//----compileShaders-----
	// Prepare the GL pipeline and attach the shaders to it
	//GLuint compileShaders(void);

#endif