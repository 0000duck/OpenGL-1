#ifndef __TEXTURE_H
#define __TEXTURE_H

class Texture
{
public:
	Texture();
	bool load(void);
	void bind(void);
	void setID(unsigned int ID);

	unsigned char *image;
	int width;
	int height;
	unsigned int size;
};

#endif