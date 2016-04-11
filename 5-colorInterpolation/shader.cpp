#include <iostream>
#include "shader.h"

#define BUFFER_SIZE 2000

//-----readShader---------
//Read a shader source code and put the text in a pre-allocated buffer
//Inputs: filename
//		  maxCharacters (size of the destination buffer)
//		  buffer (preallocated in the caller function)
//
//Outputs:the size of the file in bytes or -1 if an error occurs
static int readShader(char const *filename, unsigned int maxCharacters, char *buffer)
{
	unsigned int size = 0;
	FILE *fp = NULL;
	fopen_s(&fp,filename,"r");
	if(fp == NULL) {
		fprintf(stderr, "Error reading shader source\n");
        return -1;
    }

	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	fread_s(buffer,BUFFER_SIZE,sizeof(char),size,fp);
	fclose(fp);

	return size;
}

//-----addShader------
// Given a shader type, it creates a shader object and attaches it to the GL pipeline
// Inputs:  program (id of the pipeline)
//			shadertype
//
// Outputs: true if success, false otherwise
static bool addShader(GLuint program, GLenum shaderType)
{
	char vertexShader[BUFFER_SIZE] = {0};
	int size;
	GLint success;
	GLuint shaderObject = glCreateShader(shaderType);
	if(!shaderObject) {
		fprintf(stderr, "Error creating shader object\n");
        return false;
	}

	//Read the right shader depending on the type specified as input
	if(shaderType == GL_VERTEX_SHADER) {
		size = readShader(VERTEX_SHADER_FILE, BUFFER_SIZE, vertexShader);
	} else 	if(shaderType == GL_FRAGMENT_SHADER) {
		size = readShader(FRAGMENT_SHADER_FILE, BUFFER_SIZE, vertexShader);
	}
	
	const GLchar* p[1];
	p[0] = vertexShader;
	GLint Lengths[1];
	Lengths[0]= size;

	//get the shader source...
	glShaderSource(shaderObject, 1, p, Lengths);
	//...and compile it
	glCompileShader(shaderObject);

	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);
	if(!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(shaderObject, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", shaderType, InfoLog);
		return false;
	}

	// and attach the shader object to the program
	glAttachShader(program, shaderObject);
	return true;
}

//----compileShaders-----
// Prepare the GL pipeline and attach the shaders to it
// Outputs: program generated
GLuint compileShaders(void)
{
	GLint success;
	GLuint shaderProgram = glCreateProgram();				// let's create a program object which works as "pipeline"
	if(!shaderProgram) {
		fprintf(stderr, "Error creating shader program\n");
        return false;
    }

	if(!addShader(shaderProgram, GL_VERTEX_SHADER))			// let's create and compile a vertex shader
		return false;
	if(!addShader(shaderProgram, GL_FRAGMENT_SHADER))		// let's create and compile a fragment shader
		return false;

	glLinkProgram(shaderProgram);							// everything will be linked together

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar ErrorLog[1024];
		glGetProgramInfoLog(shaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		return false;
	}



	//given the current pipeline state, can the shaders be executed? (this should be done before every draw call.......)
	glValidateProgram(shaderProgram);

	glUseProgram(shaderProgram);

	return true;
}
