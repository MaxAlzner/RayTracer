
#include "..\include\RayTracer.h"

#if 1
const uint Width = 1280;
const uint Height = 720;
#else
const uint Width = 128;
const uint Height = 72;
#endif
const uint Renders = 240;
const uint Samples = 1;//8;
const float ViewWidth = 3.3f;
const float TurnSpeed = 0.0025f;

float Theta = 0.0f;

ARRAY<Entity*> Entities;
ARRAY<Light*> Lights;
Camera* MainCamera = NULL;

int main(int argc, char **argv)
{
	RANDOM_Initialize();

	uint start = 0;
	uint end = 0;
	printf("  STARTING FRAME : ");
	fflush(stdin);
	scanf("%d", &start);
	printf("  ENDING FRAME : ");
	fflush(stdin);
	scanf("%d", &end);
	fflush(stdin);
	if (start == end || start > end) return 0;

	SURFACE* marble_d = NULL;
	SURFACE* marble_n = NULL;
	SURFACE* marble_s = NULL;
	ImportBMPFile("data/marble_d.bmp", &marble_d);
	ImportBMPFile("data/marble_n.bmp", &marble_n);
	ImportBMPFile("data/marble_s.bmp", &marble_s);

	printf("\n");
	printf("INITIALIZING SCENE\n\n");

	VEC4 CameraPosition = VEC4(1.2f, 0.1f, -3.2f, 1.0);
	MainCamera = new Camera;
	MainCamera->position = CameraPosition;
	MainCamera->dimensions = VEC2(ViewWidth, ViewWidth * 0.75f);
	MainCamera->focalLength = 256.0f;
	MainCamera->sampleSize = Samples;

	Entity* diamond1 = new Entity;
	Entities.add(diamond1);
	diamond1->initialize();
	ImportOBJFile("data/topDiamond.obj", &diamond1->mesh);
	diamond1->material->specular = 0.4f;
	diamond1->material->overlay = COLOR(0.05f, 0.4f, 1.0f, 1.0);
	diamond1->material->reflect = COLOR(1.0f, 1.0f, 1.0f, 0.5f);

	Entity* diamond2 = new Entity;
	Entities.add(diamond2);
	diamond2->initialize();
	ImportOBJFile("data/bottomDiamond.obj", &diamond2->mesh);
	diamond2->material->specular = 0.4f;
	diamond2->material->overlay = COLOR(0.2f, 1.0f, 0.9f, 1.0);
	diamond2->material->reflect = COLOR(1.0f, 1.0f, 1.0f, 0.5f);

	Entity* background = new Entity;
	Entities.add(background);
	background->initialize();
	ImportOBJFile("data/box.obj", &background->mesh);
	background->material->overlay = COLOR(0.7f, 1.0f, 0.9f, 1.0);
	background->material->reflect = COLOR(0.25f, 0.25f, 0.25f, 0.5f);
	background->material->specular = 0.4f;

	Light* light1 = new Light(VEC4(0.8f, 0.2f, -2.4f, 0.0f), VEC3(0.001f, 0.04f, 0.12f), COLOR(1.0f, 1.0f, 1.0f, 1.0f));
	Lights.add(light1);

	printf("START RENDERING\n\n");

	SURFACE* render = NULL;
	CreateSurface(&render, "", Width, Height, PIXELFORMAT_RGB);
	char* filename = new char[128];

	uint t = (uint)time(0);

	for (uint i = start; i < end; i++)
	{
		printf("RENDERING FRAME : %03d ", i);
		ClearBitmap(render, 0x333333);
		memset(filename, 0, sizeof(char) * 128);
		sprintf(filename, "RaySequence03_720p/RayTrace.%03d.bmp", i);
		
		Theta = float(i) * TurnSpeed;

		MainCamera->position = VEC4(
			(CameraPosition.x * cos(Theta)) - (CameraPosition.z * sin(Theta)), 
			CameraPosition.y, 
			(CameraPosition.x * sin(Theta)) + (CameraPosition.z * cos(Theta)), 
			1.0f);
#if 0
		light1->position = VEC4(
			(light1->position.x * cos(-Theta)) - (light1->position.z * sin(-Theta)), 
			light1->position.y, 
			(light1->position.x * sin(-Theta)) + (light1->position.z * cos(-Theta)), 
			1.0f);
#endif

		//MainCamera->castRays(render);
		MainCamera->castRays(render);

		ExportBMPFile(filename, render);
		printf("DONE\n");
	}

	delete [] filename;
	FreeSurface(&render);
	
	printf("\n");
	//printf("FINISHED RENDERING\n\n");

	return 0;
}