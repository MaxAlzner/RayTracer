#ifndef __RAYTRACER_H_
#define __RAYTRACER_H_

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <vector>

#include <MALib.h>

using namespace std;
using namespace MALib;

class Material;
class Light;
class Entity;
class Camera;

extern ARRAY<Entity*> Entities;
extern ARRAY<Light*> Lights;
extern Camera* MainCamera;

//#include "DataCore.h"
//#include "CORE\CORE.Resources.h"

//#include "CORE\CORE.Functions.h"
#include "CORE.Primitives.h"
//#include "CORE\CORE.RGB.h"
//#include "CORE\CORE.Drawing.2D.h"
//#include "CORE\CORE.Texture.h"
#include "CORE.Material.h"
//#include "CORE\CORE.Mesh.h"
#include "CORE.Light.h"
#include "CORE.Entity.h"
#include "CORE.Camera.h"
//#include "CORE\CORE.Scene.h"

//#include "ACTOR\ACTOR.Cube.h"
//#include "ACTOR\ACTOR.Diamond.h"
//#include "ACTOR\ACTOR.Plane.h"
#include "ACTOR.Sphere.h"

#endif