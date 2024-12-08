#ifndef IMAGE_H
#define IMAGE_H

#include <string>

namespace sushi
{

	class Image
	{
	public:
		Image(const std::string& path, bool flipped);
		Image(const unsigned char* data, int data_size, bool flipped);
		~Image();

	protected:
		uint32_t imageWidth;
		uint32_t imageHeight;
		uint32_t imageColorCh;
		unsigned char* imageData;
		void freeImage();
	private:

		bool fileExists(const std::string& filename);
		void loadImage(const std::string& filename);
		void loadImageFMem(const unsigned char* imageData, int size);
		void setImageFlipped(bool flipped);

	};
}

#endif 