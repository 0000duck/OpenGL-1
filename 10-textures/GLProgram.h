#ifndef __GLPROGRAM_H
#define __GLPROGRAM_H

#include <vector>
#include "shader.h"
#include "glew.h"

class GLProgram
{
public:
	GLProgram(void);
	void run(void);
	unsigned int getID(void);
private:
	void getShaders();
	void addShader(std::string fileName, GLenum type);
	void linkShaders(void);
	bool checkErrors(void);

private:
	std::vector<Shader> shaders;
	unsigned int ID;
};

#endif