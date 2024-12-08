#include "Image.h"

#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

sushi::Image::Image(const std::string& path, bool flipped)
{
	/* Initialize members */
	this->imageWidth = 0;
	this->imageHeight = 0;
	this->imageColorCh = 0;
	this->imageData = nullptr;

	/* Set STB IMAGE LOADER state (image flipped or not) */
	setImageFlipped(flipped);

	/* Check if file exist */
	if (fileExists(path))
	{
		/* Load the image from disk */
		loadImage(path);
	}
}

sushi::Image::Image(const unsigned char* data, int data_size, bool flipped)
{
	/* Initialize members */
	this->imageWidth = 0;
	this->imageHeight = 0;
	this->imageColorCh = 0;
	this->imageData = nullptr;

	/* Set STB IMAGE LOADER state (image flipped or not) */
	setImageFlipped(flipped);

	/* Load the image from memory */
	loadImageFMem(data, data_size);
}

sushi::Image::~Image()
{
	this->freeImage();
}

void sushi::Image::loadImage(const std::string& filename)
{
	this->imageData = stbi_load(filename.c_str(), (int*)&this->imageWidth, (int*)&this->imageHeight, (int*)&this->imageColorCh, 0);
}

void sushi::Image::loadImageFMem(const unsigned char* imageData, int size)
{
	this->imageData = stbi_load_from_memory(imageData, size, (int*)&this->imageWidth, (int*)&this->imageHeight, (int*)&this->imageColorCh, 0);
}

void sushi::Image::setImageFlipped(bool flipped)
{
	stbi_set_flip_vertically_on_load(flipped);
}

void sushi::Image::freeImage()
{
	if (this->imageData != nullptr)
	{
		stbi_image_free(this->imageData);
		this->imageData = nullptr;
		std::cout << "Image freed" << std::endl;
	}
}

bool sushi::Image::fileExists(const std::string& filename)
{
	try {
		std::ifstream file(filename);
		if (!file.is_open()) {
			throw std::runtime_error("File does not exist or could not be opened.");
		}
		return true;
	}
	catch (const std::runtime_error& error) {
		std::cerr << "Error: " << error.what() << std::endl;
		return false;
	}
}
