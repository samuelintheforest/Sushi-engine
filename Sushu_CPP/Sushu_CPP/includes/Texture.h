#ifndef TEXTURE_H
#define TEXTURE_H


#include <glad/glad.h>
#include <iostream>
namespace sushi {
	class Texture
	{
	public:
		#define NEAREST 21
		#define LINEAR 12

		struct TextureDesc
		{
			short width;
			short height;
			short nrChannels;
			stbi_uc* data;
		};

		Texture(char* imgPath, const stbi_uc* imgVal, int size, bool flipped, bool glNeeded, float* atlasData);
		~Texture();
		void freeTexture();
		void deleteTexture();
		int width;
		int height;
		int nr_channels;
		stbi_uc* data;
		GLuint txId;
	private:
		void loadImage(const char* path);
		void loadImageFMem(const stbi_uc* imageData, int size);
		void textureLoad(TextureDesc* texSrc, int FLAG);

		bool gl_needed;

	};
}
#endif // ! TEXTURE_H
