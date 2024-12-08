#include <glad/glad.h>
#include "Texture.h"
#include "GameLogic.h"


sushi::SGXTexture::SGXTexture(const std::string& imgPath, bool flipped) : Image(imgPath, flipped)
{
	this->textureID = 0;
	loadTexture();
}

sushi::SGXTexture::SGXTexture(const unsigned char* imageData, int dataSize, bool flipped) : Image(imageData, dataSize, flipped)
{
	this->textureID = 0;
	loadTexture();
}

sushi::SGXTexture::~SGXTexture()
{
	glDeleteTextures(1, &this->textureID);
	std::cout << "Deleted texture" << std::endl;
}

uint32_t sushi::SGXTexture::getTextureID() const
{
	return this->textureID;
}

uint32_t sushi::SGXTexture::getTextureWidth() const
{
	return this->imageWidth;
}

uint32_t sushi::SGXTexture::getTextureHeight() const
{
	return this->imageHeight;
}

uint32_t sushi::SGXTexture::getTextureColorCh() const
{
	return this->imageColorCh;
}

void sushi::SGXTexture::loadTexture()
{
	glGenTextures(1, &this->textureID);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int flag = GL_RGB;
	if (this->imageColorCh == 4)
	{
		flag = GL_RGBA;
	}

	if (this->imageData != nullptr)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, flag, this->imageWidth, this->imageHeight, 0, flag, GL_UNSIGNED_BYTE, this->imageData);
	}

	sushi::GameLogic::GraphicsManager->textureSlot.push_back(this->textureID);

}




