
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "GameLogic.h"

sushi::Texture::Texture(const char* imgPath, const unsigned char* imgVal, int size, bool flipped, bool glNeeded, float* atlasData)
{
	data = NULL;
	width = 0;
	height = 0;
	nr_channels = 0;
	this->txId = 0;
	gl_needed = glNeeded;
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
		std::cout << "ERROR:: Please specify only one possible source: either memory or path!" << std::endl;
	}
	if (glNeeded == true) 
	{
		TextureDesc temp;
		temp.width = width;
		temp.height = height;
		temp.nrChannels = nr_channels;
		temp.data = data;
		textureLoad(&temp, NEAREST);

		sushi::GameLogic::GraphicsManager->textureSlot.push_back(this->txId);
	}
}

sushi::Texture::~Texture()
{
	if (data != NULL)
	{
		freeTexture();
	}
	if (gl_needed == true)
	{
		deleteTexture();
	}
}

void sushi::Texture::freeTexture()
{
	stbi_image_free(data);
	data = NULL;
}

void sushi::Texture::deleteTexture()
{
	glDeleteTextures(1, &txId);
}

void sushi::Texture::loadImage(const char* path)
{
	data = stbi_load(path, &width, &height, &nr_channels, 0);
}

void sushi::Texture::loadImageFMem(const unsigned char*imageData, int size)
{
	data = stbi_load_from_memory(imageData, size, &width, &height, &nr_channels, 0);
}

void sushi::Texture::textureLoad(TextureDesc* texSrc, int FLAG)
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
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		//freeTexture();
	
}
