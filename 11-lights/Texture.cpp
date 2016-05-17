#pragma comment(lib, "SOIL.lib")

#include "Texture.h"
#include "SOIL.h"
#include "Configuration.h"

Texture::Texture()
{
	load();
}

bool Texture::load()
{
	image = SOIL_load_image(Configuration::getInstance()->getConfiguration("TEXTURE").c_str() ,&width,&height,0,SOIL_LOAD_RGBA);		//load the image
	if(image == nullptr){
		return false;
	}

	return true;
}
