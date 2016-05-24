#ifndef __GLPROGRAM_H
#define __GLPROGRAM_H

#include <vector>
#include "shader.h"
#include <GL\glew.h>

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

public:
	//here are all the uniform variables!
	unsigned int transformObjIndex;
	unsigned int transformCamIndex;
	unsigned int lightColorAmbientIndex;
	unsigned int lightColorDiffuseIndex;
	unsigned int ambientIntensityIndex;
	unsigned int diffuseIntensityIndex;
	unsigned int directionIndex;
	unsigned int specularColorIndex;
	unsigned int eyeIndex;
	unsigned int specularIntensityIndex;
	unsigned int specularPowerIndex;
	unsigned int materialIndex;

private:
	std::vector<Shader> shaders;
	unsigned int ID;
};

#endif