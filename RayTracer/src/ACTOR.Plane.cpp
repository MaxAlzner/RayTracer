#include "../GameCore.h"

using namespace CORE;

GameCore::Plane::Plane()
{
}
GameCore::Plane::~Plane()
{
}

void GameCore::Plane::initialize()
{
	this->initialize(VECTOR());
}
void GameCore::Plane::initialize(VECTOR &position, VALUE size)
{
	VERTEX v1(-size, size, 0);
	VERTEX v2(size, size, 0);
	VERTEX v3(-size, -size, 0);
	VERTEX v4(size, -size, 0);
	UVPOINT uv1(0, 0);
	UVPOINT uv2(1.0, 0);
	UVPOINT uv3(0, 1.0);
	UVPOINT uv4(1.0, 1.0);

	this->mesh.addFace(v3, v1, v2, uv3, uv1, uv2);
	this->mesh.addFace(v2, v4, v3, uv2, uv4, uv3);

	this->mesh.translate(position.x, position.y, position.z);
}
void GameCore::Plane::update()
{
}