#ifndef __TEXTURE_H
#define __TEXTURE_H

class Texture
{
public:
	Texture();
	bool load(void);

	unsigned char *image;
	int width;
	int height;
	unsigned int size;
};

#endif