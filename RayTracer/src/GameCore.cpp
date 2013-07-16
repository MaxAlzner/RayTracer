#include "GameCore.h"

using namespace CORE;

namespace GameCore
{
	Scene* scene = NULL;
	AnaglyphCamera* anaglyphCam = NULL;

	TEXTURE* UV_Layout_Grid = NULL;
	TEXTURE* BrickWall = NULL;
	TEXTURE* Pebbles = NULL;
	TEXTURE* WoodWall = NULL;
	TEXTURE* Marble = NULL;
	
	TEXTURE* BrickWall_Specular = NULL;
	TEXTURE* WoodWall_Specular = NULL;
	
	TEXTURE* BrickWall_Normal = NULL;
	TEXTURE* WoodWall_Normal = NULL;
	TEXTURE* Stone_Normal = NULL;
	TEXTURE* Krinkle_Normal = NULL;
	
	void GameClass::_OnInitialize()
	{
		srand(time(NULL));

		UV_Layout_Grid = new TEXTURE("UV_Layout_Grid", 0, &Resources::UV_Layout_Grid_1024x1024, 1024, 1024);
		BrickWall = new TEXTURE("BrickWall", 1, &Resources::BrickWall_512x512, 512, 512);
		Pebbles = new TEXTURE("Pebbles", 2, &Resources::Pebbles_1400x1400, 1400, 1400);
		WoodWall = new TEXTURE("WoodWall", 3, &Resources::WoodWall_1024x1024, 1024, 1024);
		Marble = new TEXTURE("Marble", 3, &Resources::Marble_1024x1024, 1024, 1024);
		
		BrickWall_Specular = new TEXTURE("BrickWall_Specular", 3, &Resources::BrickWall_Specular_512x512, 512, 512);
		WoodWall_Specular = new TEXTURE("WoodWall_Specular", 3, &Resources::WoodWall_Specular_1024x1024, 1024, 1024);
		
		BrickWall_Normal = new TEXTURE("BrickWall_Normal", 3, &Resources::BrickWall_Normal_512x512, 512, 512);
		WoodWall_Normal = new TEXTURE("WoodWall_Normal", 3, &Resources::WoodWall_Normal_1024x1024, 1024, 1024);
		Stone_Normal = new TEXTURE("Stone_Normal", 3, &Resources::Stone_Normal_512x512, 512, 512);
		Krinkle_Normal = new TEXTURE("Krinkle_Normal", 3, &Resources::Krinkle_Normal_428x428, 428, 428);

		scene = new Scene();
		anaglyphCam = new AnaglyphCamera;
		scene->setCamera(anaglyphCam);
		
		scene->actors.push_back(new Sphere());
		scene->actors.push_back(new Diamond());
		scene->actors.push_back(new Sphere());
		scene->actors.push_back(new Cube());

		scene->actors.push_back(new Plane());
		scene->actors.push_back(new Plane());
		scene->actors.push_back(new Plane());
		scene->actors.push_back(new Plane());
		scene->actors.push_back(new Plane());
		scene->actors.push_back(new Plane());

		int i = 0;

		scene->actors[i]->initialize(VECTOR(0, 80, 0, 0), 64);
		scene->actors[i]->material.reflect = COLOR(0);
		scene->actors[i]->material.setDiffuseMap(Pebbles);
		scene->actors[i]->material.setNormalMap(Krinkle_Normal);
		i++;
		
		scene->actors[i]->initialize(VECTOR(0, -80, 0, 0), 80);
		scene->actors[i]->material.reflect = COLOR(RGB_GRAY_LIGHT);
		scene->actors[i]->material.reflect.a = 0.2;
		scene->actors[i]->material.setDiffuseMap(UV_Layout_Grid);
		scene->actors[i]->mesh.freeze();
		i++;

		scene->actors[i]->initialize(VECTOR(128, 0, 0, 0), 64);
		scene->actors[i]->material.reflect = COLOR(RGB_GRAY_LIGHT);
		scene->actors[i]->material.reflect.a = 0.2;
		scene->actors[i]->material.setDiffuseMap(BrickWall);
		scene->actors[i]->material.setNormalMap(Krinkle_Normal);
		i++;
		
		scene->actors[i]->initialize(VECTOR(-132, -64, -64, 0), 48);
		scene->actors[i]->material.reflect = COLOR(RGB_WHITE);
		scene->actors[i]->material.reflect.a = 0.25;
		scene->actors[i]->material.setDiffuseMap(Marble);
		scene->actors[i]->mesh.freeze();
		i++;
		
		VALUE planeRadius = 240;
		
		scene->actors[i]->initialize(VECTOR(planeRadius, 0, 0, 0), planeRadius);
		scene->actors[i]->material.reflect = COLOR(RGB_GRAY_DARK);
		scene->actors[i]->material.reflect.a = 0.2;
		scene->actors[i]->material.setDiffuseMap(WoodWall);
		scene->actors[i]->material.setSpecularMap(WoodWall_Specular);
		scene->actors[i]->material.setNormalMap(Stone_Normal);
		scene->actors[i]->mesh.rotate(0, 90, 0);
		scene->actors[i]->mesh.freeze();
		i++;
		
		scene->actors[i]->initialize(VECTOR(-planeRadius, 0, 0, 0), planeRadius);
		scene->actors[i]->material.reflect = COLOR(RGB_GRAY_DARK);
		scene->actors[i]->material.reflect.a = 0.2;
		scene->actors[i]->material.setDiffuseMap(WoodWall);
		scene->actors[i]->material.setSpecularMap(WoodWall_Specular);
		scene->actors[i]->material.setNormalMap(Stone_Normal);
		scene->actors[i]->mesh.rotate(0, -90, 0);
		scene->actors[i]->mesh.freeze();
		i++;

		scene->actors[i]->initialize(VECTOR(0, -planeRadius, 0, 0), planeRadius);
		scene->actors[i]->material.reflect = COLOR(RGB_GRAY_DARK);
		scene->actors[i]->material.reflect.a = 0.2;
		scene->actors[i]->material.setDiffuseMap(Marble);
		scene->actors[i]->material.setSpecularMap(BrickWall_Specular);
		scene->actors[i]->material.setNormalMap(Stone_Normal);
		scene->actors[i]->mesh.rotate(90, 0, 0);
		scene->actors[i]->mesh.freeze();
		i++;
		
		scene->actors[i]->initialize(VECTOR(0, planeRadius, 0, 0), planeRadius);
		scene->actors[i]->material.reflect = COLOR(RGB_GRAY_DARK);
		scene->actors[i]->material.reflect.a = 0.2;
		scene->actors[i]->material.setDiffuseMap(BrickWall);
		scene->actors[i]->material.setSpecularMap(BrickWall_Specular);
		scene->actors[i]->material.setNormalMap(Stone_Normal);
		scene->actors[i]->mesh.rotate(-90, 0, 0);
		scene->actors[i]->mesh.freeze();
		i++;
		
		scene->actors[i]->initialize(VECTOR(0, 0, planeRadius, 0), planeRadius);
		scene->actors[i]->material.reflect = COLOR(RGB_GRAY_DARK);
		scene->actors[i]->material.reflect.a = 0.2;
		scene->actors[i]->material.setDiffuseMap(WoodWall);
		scene->actors[i]->material.setSpecularMap(WoodWall_Specular);
		scene->actors[i]->material.setNormalMap(Stone_Normal);
		scene->actors[i]->mesh.freeze();
		i++;
		
		scene->actors[i]->initialize(VECTOR(0, 0, -planeRadius, 0), planeRadius);
		scene->actors[i]->material.reflect = COLOR(RGB_GRAY_DARK);
		scene->actors[i]->material.reflect.a = 0.2;
		scene->actors[i]->material.setDiffuseMap(WoodWall);
		scene->actors[i]->material.setSpecularMap(WoodWall_Specular);
		scene->actors[i]->material.setNormalMap(Stone_Normal);
		scene->actors[i]->mesh.rotate(0, 180, 0);
		scene->actors[i]->mesh.freeze();
		i++;

		scene->lights.push_back(new Light(VECTOR(0, 0, 0, 0), 0, COLOR(1.0, 1.0, 1.0, 1.0)));
		scene->lights[0]->shadowIntensity = 0.6;
		
		scene->onInitialize();
	}

	void GameClass::_OnUninitialize()
	{
		scene->onUninitialize();
	}

	void GameClass::_OnFrame(IntPtr surface, int width, int height)
	{
		int* video = (int*)surface.ToPointer();
		if (video == NULL) return;

		CORE::Drawing::ClearBitmap(video, width, height, RGB_BLACK);
		scene->camera->focalLength = GameCore::DataCore::focalLength;
		scene->camera->sampleSize = GameCore::DataCore::sampleSize;
		scene->camera->position.x = GameCore::DataCore::cameraPositionX;
		scene->camera->position.y = GameCore::DataCore::cameraPositionY;
		scene->camera->position.z = GameCore::DataCore::cameraPositionZ;
		scene->camera->direction.x = GameCore::DataCore::cameraRotationX;
		scene->camera->direction.y = GameCore::DataCore::cameraRotationY;
		scene->camera->direction.z = GameCore::DataCore::cameraRotationZ;

		scene->lights[0]->intensity = GameCore::DataCore::lightIntensity;
		scene->lights[0]->position.x = GameCore::DataCore::lightPositionX;
		scene->lights[0]->position.y = GameCore::DataCore::lightPositionY;
		scene->lights[0]->position.z = GameCore::DataCore::lightPositionZ;
		scene->lights[0]->color.r = VALUE(GameCore::DataCore::lightColorR) / 255.0;
		scene->lights[0]->color.g = VALUE(GameCore::DataCore::lightColorG) / 255.0;
		scene->lights[0]->color.b = VALUE(GameCore::DataCore::lightColorB) / 255.0;

#if 1
		CORE::Drawing::DrawBox(video, width, height, 0, 0, width, height, RGB_GRAY_LIGHT);
		CORE::Drawing::DrawLine(video, width, height, 0, 0, width, height, RGB_GRAY_DARK);
		CORE::Drawing::DrawLine(video, width, height, width, 0, 0, height, RGB_GRAY_DARK);
		CORE::Drawing::DrawLine(video, width, height, 0, height / 2, width, height / 2, RGB_GRAY_DARK);
		CORE::Drawing::DrawLine(video, width, height, width / 2, 0, width / 2, height, RGB_GRAY_DARK);
#endif

		if (scene == NULL) return;
		if (scene->camera == NULL) return;

		if (GameCore::DataCore::enable3D)
		{
			anaglyphCam->castRays(video, width, height, COLOR(RGB_MAGENTA), COLOR(RGB_GREEN), 8);
		}
		else scene->camera->castRays(video, width, height);
	}
}