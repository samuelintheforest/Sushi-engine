#ifndef TEXTURE_H
#define TEXTURE_H

#include "Image.h"
#include <string>

namespace sushi {

	class SGXTexture : Image
	{
	public:

		SGXTexture(const std::string& imgPath, bool flipped);
		SGXTexture(const unsigned char* imageData, int dataSize, bool flipped);
		~SGXTexture();


		/* Getter methods */
		uint32_t getTextureID() const;
		uint32_t getTextureWidth() const;
		uint32_t getTextureHeight() const;
		uint32_t getTextureColorCh() const;
		
	private:

		/* members */
		void loadTexture();
		uint32_t textureID;

	};
}
#endif // ! TEXTURE_H
