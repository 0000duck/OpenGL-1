#ifndef __TEXTURE_H
#define __TEXTURE_H

#include <string>

class Texture
{
public:
	Texture(std::string filename = std::string(""));
	bool load(std::string filename);

	unsigned char *image;
	int width;
	int height;
	unsigned int size;
};

#endif