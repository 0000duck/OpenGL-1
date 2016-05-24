#include <iostream>
#include "shader.h"
#include <fstream>

#define BUFFER_SIZE 2000

Shader::Shader(GLenum type)
{
	shaderType = type;
	ID = glCreateShader(type);
}

int Shader::readSrc(const char *fileName, char *buffer)
{
	unsigned int size = 0;
	std::string str;
	std::ifstream file(fileName);
	file.seekg(0, std::ios::end);   
	size = file.tellg();
	file.seekg(0, std::ios::beg);
	if (size > BUFFER_SIZE)
		size = BUFFER_SIZE;
	file.read(buffer, size);
	file.close();

	return size;
}

bool Shader::compile(std::string fileName)
{
	char shader[BUFFER_SIZE] = {0};
	int size = 0;
	if ((size = readSrc(fileName.c_str(), shader)) < 0) {
		return false;
	}

	const GLchar* p[1];
	p[0] = shader;
	GLint Lengths[1];
	Lengths[0]= size;

	//get the shader source...
	glShaderSource(ID, 1, p, Lengths);
	//...and compile it
	glCompileShader(ID);

	return checkErrors();
}

bool Shader::checkErrors(void)
{
	GLint success;
	glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
	if(!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ID, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", shaderType, InfoLog);
		return false;
	}
	return true;
}

unsigned int Shader::getID(void)
{
	return ID;
}



//-----addShader------
// Given a shader type, it creates a shader object and attaches it to the GL pipeline
// Inputs:  program (id of the pipeline)
//			shadertype
//
// Outputs: true if success, false otherwise


//----compileShaders-----
// Prepare the GL pipeline and attach the shaders to it
// Outputs: program generated
