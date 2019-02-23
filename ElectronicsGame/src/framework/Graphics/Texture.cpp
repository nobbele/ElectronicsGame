#include <Graphics/Texture.h>

#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <IO/eg_error.h>

Texture::Texture(const char *path) 
	: size(0, 0)
{
	glGenTextures(1, &this->m_texture);
	glBindTexture(GL_TEXTURE_2D, this->m_texture);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int nrChannels;
	unsigned char *data = stbi_load(path, &this->size.x, &this->size.y, &nrChannels, STBI_rgb_alpha);

	if (!data) {
		EG_ERROR(
			fprintf(stderr, "Failed to load texture '%s'\n", stbi_failure_reason());
			getchar();
			exit(-1);
		);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->size.x, this->size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
}

void Texture::Bind() const {
	glBindTexture(GL_TEXTURE_2D, this->m_texture);
}