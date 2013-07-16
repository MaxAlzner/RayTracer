#include "../GameCore.h"

/*CORE::Texture::Texture()
{
	this->video = NULL;
	this->name = "";
	this->width = 0;
	this->height = 0;
	this->id = 0;
}
CORE::Texture::Texture(char* name, int id)
{
	this->video = NULL;
	this->name = name;
	this->width = 0;
	this->height = 0;
	this->id = id;
}
CORE::Texture::~Texture()
{
	if (this->video != NULL) delete this->video;
}

void CORE::Texture::extract(int** pixelBuffer, int* width, int* height)
{
	*pixelBuffer = this->video;
	*width = this->width;
	*height = this->height;
}
void CORE::Texture::setBitmap(int** image, int width, int height)
{
	if (this->video != NULL) delete this->video;
	this->video = *image;
	this->width = width;
	this->height = height;
}*/

/*CORE::Texture* CORE::CreateTexture(char* name, int id, int width, int height)
{
	Texture* newTexture = new Texture(name, id);
	int* buffer = new int[width * height];
	newTexture->setBitmap(&buffer, width, height);
	return newTexture;
}
void CORE::DestroyTexture(CORE::Texture* texture)
{
	if (texture == NULL) return;
	delete texture;
}*/