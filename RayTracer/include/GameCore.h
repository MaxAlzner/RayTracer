#ifndef __GAME_CORE_H_
#define __GAME_CORE_H_

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <vector>

using namespace std;
using namespace System;

namespace CORE
{
	class Mesh;
	class Material;
	class Light;
	class Entity;
	class Camera;
	class Scene;
}

#include "DataCore.h"
#include "CORE\CORE.Resources.h"

#include "CORE\CORE.Functions.h"
#include "CORE\CORE.Primitives.h"
#include "CORE\CORE.RGB.h"
#include "CORE\CORE.Drawing.2D.h"
#include "CORE\CORE.Texture.h"
#include "CORE\CORE.Material.h"
#include "CORE\CORE.Mesh.h"
#include "CORE\CORE.Light.h"
#include "CORE\CORE.Entity.h"
#include "CORE\CORE.Camera.h"
#include "CORE\CORE.Scene.h"

#include "ACTOR\ACTOR.Cube.h"
#include "ACTOR\ACTOR.Diamond.h"
#include "ACTOR\ACTOR.Plane.h"
#include "ACTOR\ACTOR.Sphere.h"

#include "SCENES\SCENE.SolarSystem.h"

#include "CORE\CORE.AnaglyphCamera.h"

namespace GameCore
{
	public ref class GameClass
	{
	public:

		void _OnInitialize();
		void _OnUninitialize();
		void _OnFrame(IntPtr surface, int width, int height);

	};

}

#endif