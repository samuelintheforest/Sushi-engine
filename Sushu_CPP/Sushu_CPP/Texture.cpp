#include "stb_image.h"
#include "Texture.h"

Sushi::Texture::Texture(char* imgPath, const stbi_uc* imgVal, int size, bool flipped, bool glNeeded, float* atlasData)
{
	data = NULL;
	width = 0;
	height = 0;
	nr_channels = 0;
	this->txId = 0;
	// Set if image would be flipped horizotnaly
	stbi_set_flip_vertically_on_load(flipped);
	if (imgPath == NULL && imgVal != NULL) {
		loadImageFMem(imgVal, size);
	}
	else if (imgPath != NULL && imgVal == NULL) {
		loadImage(imgPath);
	}
	else
	{
		std::cout << "ERROR:: Please specify only one possible source: either memory or path please!" << std::endl;
	}
	if (glNeeded == true) 
	{
		TextureDesc temp;
		temp.width = width;
		temp.height = height;
		temp.nrChannels = nr_channels;
		temp.data = data;
		textureLoad(&temp, NEAREST);
	}
}

Sushi::Texture::~Texture()
{
}

void Sushi::Texture::freeTexture()
{
	stbi_image_free(data);
}

void Sushi::Texture::deleteTexture()
{
	glDeleteTextures(1, &txId);
}

void Sushi::Texture::loadImage(const char* path)
{
	data = stbi_load(path, &width, &height, &nr_channels, 0);
}

void Sushi::Texture::loadImageFMem(const stbi_uc *imageData, int size)
{
	data = stbi_load_from_memory(imageData, size, &width, &height, &nr_channels, 0);
}

void Sushi::Texture::textureLoad(TextureDesc* texSrc, int FLAG)
{
		int tmpFilter = 0;
		
		glGenTextures(1, &txId);
		glBindTexture(GL_TEXTURE_2D, txId);
		if (FLAG == NEAREST)
		{
			tmpFilter = GL_NEAREST;
		}
		else if (FLAG == LINEAR)
		{
			tmpFilter = GL_LINEAR;
		}
		else
		{
			std::cout << "Error, please specify a valid texture filterer" << std::endl;
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tmpFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tmpFilter);

		int flag = GL_RGB;
		if (texSrc->nrChannels == 4)
		{
			flag = GL_RGBA;
		}

		if (texSrc->data != NULL)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, flag, texSrc->width, texSrc->height, 0, flag, GL_UNSIGNED_BYTE, texSrc->data);
		}
		//freeTexture();
	
}
