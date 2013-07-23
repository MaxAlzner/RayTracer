
#include "..\include\RayTracer.h"

const uint Width = 720;
const uint Height = 480;
const uint Renders = 480;
const float TurnSpeed = 0.0025f;

float Theta = 0.0f;

ARRAY<Entity*> Entities;
ARRAY<Light*> Lights;
Camera* MainCamera = NULL;

int main(int argc, char **argv)
{
	LOG_Initialize(true);
	RANDOM_Initialize();

	SURFACE* marble_d = NULL;
	SURFACE* marble_n = NULL;
	SURFACE* marble_s = NULL;
	ImportBMPFile("data/marble_d.bmp", &marble_d);
	ImportBMPFile("data/marble_n.bmp", &marble_n);
	ImportBMPFile("data/marble_s.bmp", &marble_s);

	printf("\n");
	printf("INITIALIZING SCENE\n\n");

	VEC4 CameraPosition = VEC4(-1.2f, 1.2f, -4.0f, 1.0);
	MainCamera = new Camera;
	MainCamera->position = CameraPosition;
	MainCamera->dimensions = VEC2(4.0f, 3.0f);
	MainCamera->focalLength = 256.0f;
	MainCamera->sampleSize = 8;

	Entity* diamond1 = new Entity;
	Entities.add(diamond1);
	diamond1->initialize();
	ImportOBJFile("data/topDiamond.obj", &diamond1->mesh);
	diamond1->material->overlay = COLOR(0.05f, 0.4f, 1.0f, 1.0);
	diamond1->material->reflect = COLOR(1.0f, 1.0f, 1.0f, 0.5f);
	/*diamond1->material->setDiffuseMap(marble_d);
	diamond1->material->setNormalMap(marble_n);
	diamond1->material->setSpecularMap(marble_s);*/

	Entity* diamond2 = new Entity;
	Entities.add(diamond2);
	diamond2->initialize();
	ImportOBJFile("data/bottomDiamond.obj", &diamond2->mesh);
	diamond2->material->overlay = COLOR(0.2f, 1.0f, 0.9f, 1.0);
	diamond2->material->reflect = COLOR(1.0f, 1.0f, 1.0f, 0.5f);
	/*diamond2->material->setDiffuseMap(marble_d);
	diamond2->material->setNormalMap(marble_n);
	diamond2->material->setSpecularMap(marble_s);*/

#if 1
	Entity* background = new Entity;
	Entities.add(background);
	background->initialize();
	ImportOBJFile("data/box.obj", &background->mesh);
	background->material->overlay = COLOR(0.7f, 1.0f, 0.9f, 1.0);
	background->material->reflect = COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	background->material->specular = 0.4f;
#else
	Sphere* background = new Sphere;
	Entities.add(background);
	background->initialize(VEC4(0.0f, 0.0f, 0.0f, 1.0f), 3.2f);
	background->material->overlay = COLOR(0.8f, 1.0f, 0.9f, 1.0);
	background->material->reflect = COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	background->material->specular = 0.4f;
#endif

	Light* light1 = new Light(VEC4(1.2f, 0.1f, -2.4f, 0.0f), VEC3(0.001f, 0.04f, 0.12f), COLOR(1.0f, 1.0f, 1.0f, 1.0f));
	Lights.add(light1);

	printf("START RENDERING\n\n");

	SURFACE* render = NULL;
	CreateSurface(&render, "", Width, Height, PIXELFORMAT_RGB);
	char* filename = new char[64];

	for (uint i = 0; i < Renders; i++)
	{
		printf("RENDERING FRAME : %03d ", i);
		ClearBitmap(render, 0x333333);
		memset(filename, 0, sizeof(char) * 64);
		sprintf(filename, "RayTrace.%03d.bmp", i);
		
		Theta = float(i) * TurnSpeed;

		MainCamera->position = VEC4(
			(CameraPosition.x * cos(Theta)) - (CameraPosition.z * sin(Theta)), 
			CameraPosition.y, 
			(CameraPosition.x * sin(Theta)) + (CameraPosition.z * cos(Theta)), 
			1.0f);

		MainCamera->castRays(render);

		ExportBMPFile(filename, render);
		printf("DONE\n");
	}

	delete [] filename;
	FreeSurface(&render);
	
	printf("\n");
	printf("FINISHED RENDERING\n\n");

	LOG_Unitialize();

	return 0;
}