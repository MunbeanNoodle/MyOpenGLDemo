#include "Material.h"
#include <iostream>

Material::Material(const GLchar* path)
{
	data = stbi_load(path, &width, &height, &nrChannels, 0);
}

void Material::genTexture(GLenum s_wrap, GLenum t_wrap, GLenum min_filter, GLenum mag_filter)
{
	if (!data)
	{
		std::cout << "No data, failed to load texture" << std::endl;
		return;
	}
	else
	{
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s_wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t_wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}
}



