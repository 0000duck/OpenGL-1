#include "GLProgram.h"
#include "Configuration.h"
#include <iostream>
#include <fstream>
#include <sstream>

GLProgram::GLProgram(void)
{
	ID = glCreateProgram();

	if(!ID) {
		fprintf(stderr, "Error creating shader Program\n");
    }

	getShaders();
}

void GLProgram::getShaders(void)
{
	Configuration *c = Configuration::getInstance();
	std::string str = c->getConfiguration("VERTEX_SHADER");
	addShader(str, GL_VERTEX_SHADER);
	str = c->getConfiguration("FRAGMENT_SHADER");
	addShader(str, GL_FRAGMENT_SHADER);
	linkShaders();
}

void GLProgram::addShader(std::string fileName, GLenum type)
{
	shaders.push_back(Shader(type));
	if(type == GL_VERTEX_SHADER) {
		fprintf(stderr,"VERTEX: ");
	} else if (type == GL_FRAGMENT_SHADER) {
		fprintf(stderr,"FRAGMENT: ");
	}

	if (!shaders.back().compile(fileName)) {
		shaders.pop_back();
	} else {
		glAttachShader(ID,shaders.back().getID());
		fprintf(stderr,"OK\n");
	}
}

void GLProgram::linkShaders(void)
{
	glLinkProgram(ID);							// everything will be linked together

	if(!checkErrors()) {
		return;
	} else {
		//given the current pipeline state, can the shaders be executed? (this should be done before every draw call.......)
		glValidateProgram(ID);
	}
}

void GLProgram::run(void)
{
	glUseProgram(ID);
}

bool GLProgram::checkErrors(void)
{
	GLint success;
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar ErrorLog[1024];
		glGetProgramInfoLog(ID, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader Program: '%s'\n", ErrorLog);
		return false;
	}
	return true;
}

unsigned int GLProgram::getID(void)
{
	return ID;
}