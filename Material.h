#ifndef MATERIAL_H
#define MATERIAL_H

#include <glad/glad.h>
#include "stb_image.h"

class Material
{
public:
	Material(const GLchar* path);

	int width;
	int height;
	int nrChannels;
	unsigned char* data;

	unsigned int ID;

	void genTexture(GLenum s_wrap = GL_REPEAT,
		GLenum t_wrap = GL_REPEAT,
		GLenum min_filter = GL_LINEAR,
		GLenum mag_filter = GL_LINEAR);
};

#endif

