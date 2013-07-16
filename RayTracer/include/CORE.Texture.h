#ifndef __CORE_TEXTURE_H_
#define __CORE_TEXTURE_H_

namespace CORE
{
	/*class Texture
	{
	public:
		Texture();
		Texture(char* name, int id);
		~Texture();

		void extract(int** pixelBuffer, int* width, int* height);
		void setBitmap(int** image, int width, int height);
	private:
		int* video;
		char* name;
		int width, height, id;
	};*/
	struct TEXTURE
	{
		TEXTURE()
		{
		this->video = NULL;
		this->name = "";
		this->width = 0;
		this->height = 0;
		this->id = 0;
		}
		TEXTURE(char* name, int id, int** image, int imageWidth, int imageHeight)
		{
		this->video = *image;
		this->name = name;
		this->width = imageWidth;
		this->height = imageHeight;
		this->id = id;
		}
		TEXTURE(char* name, int id, int imageWidth, int imageHeight)
		{
		this->video = new int[width * height];
		this->name = name;
		this->width = imageWidth;
		this->height = imageHeight;
		this->id = id;
		}
		int* video;
		char* name;
		int width, height, widthPadding, id;
	};

	/*Texture* CreateTexture(char* name, int id, int width, int height);
	void DestroyTexture(Texture* texture);*/
}

#endif