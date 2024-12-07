#ifndef TEXTURE_H
#define TEXTURE_H


#include <glad/glad.h>
#include <iostream>

#include "Types.h"





namespace sushi {
	class Texture
	{
	public:
		#define NEAREST 21
		#define LINEAR 12



		Texture(const char* imgPath, const unsigned char* imgVal, int size, bool flipped, bool glNeeded, float* atlasData);
		~Texture();
		void freeTexture();
		void deleteTexture();
		int width;
		int height;
		int nr_channels;
		unsigned char* data;
		GLuint txId;
	private:
		void loadImage(const char* path);
		void loadImageFMem(const unsigned char* imageData, int size);
		void textureLoad(TextureDesc* texSrc, int FLAG);

		bool gl_needed;

	};
}
#endif // ! TEXTURE_H
