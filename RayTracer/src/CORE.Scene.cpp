#include "../GameCore.h"

CORE::Scene::Scene()
{
	this->camera = NULL;
	this->mouseHoveringOver = NULL;
}
CORE::Scene::~Scene()
{
	delete this->camera;
	for (int a = 0; a < this->actors.size(); a++) delete this->actors[a];
	for (int l = 0; l < this->lights.size(); l++) delete this->lights[l];
}

void CORE::Scene::onInitialize()
{
	for (int a = 0; a < this->actors.size(); a++) this->actors[a]->scene = this;
	for (int l = 0; l < this->lights.size(); l++) this->lights[l]->scene = this;
}
void CORE::Scene::onUninitialize()
{
	for (int a = 0; a < this->actors.size(); a++) this->actors[a]->uninitialize();
	//for (int l = 0; l < this->lights.size(); l++) this->lights[l]->uninitialize();
}
void CORE::Scene::onFrame(int* video, float* zBuffer, int width, int height, Mesh** onScreen)
{
	for (int a = 0; a < this->actors.size(); a++)
	{
		Entity* entity = this->actors[a];

		entity->draw(video, zBuffer, width, height, this->camera, onScreen);
	}
	VECTOR::Module(this->camera->direction, 360);
}
void CORE::Scene::onTick()
{
	for (int a = 0; a < this->actors.size(); a++) this->actors[a]->update();
}

void CORE::Scene::setCamera(Camera* cam)
{
	if (cam == NULL) return;
	if (this->camera != NULL) delete this->camera;
	this->camera = cam;
	this->camera->entities = &this->actors;
	this->camera->lights = &this->lights;
}