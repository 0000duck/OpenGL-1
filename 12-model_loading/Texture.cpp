#pragma comment(lib, "SOIL.lib")

#include "Texture.h"
#include "SOIL.h"
#include "Configuration.h"
#include <string>

Texture::Texture(std::string filename)
{
	load(filename);
}

bool Texture::load(std::string filename)
{
	if(filename.empty())
		image = SOIL_load_image(Configuration::getInstance()->getConfiguration("TEXTURE").c_str() ,&width,&height,0,SOIL_LOAD_RGBA);		//load the image
	else
		image = SOIL_load_image(filename.c_str() ,&width,&height,0,SOIL_LOAD_RGBA);		//load the image
	if(image == nullptr){
		return false;
	}

	return true;
}
