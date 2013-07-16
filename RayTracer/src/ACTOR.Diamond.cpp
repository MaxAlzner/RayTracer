#include "../GameCore.h"

using namespace CORE;

GameCore::Diamond::Diamond()
{
}
GameCore::Diamond::~Diamond()
{
}

void GameCore::Diamond::initialize()
{
	this->initialize(VECTOR());
}
void GameCore::Diamond::initialize(VECTOR &position, VALUE size)
{
	VERTEX v1(0, size, 0);
	VERTEX v2(size, 0, 0);
	VERTEX v3(0, -size, 0);
	VERTEX v4(-size, 0, 0);
	VERTEX v5(0, 0, -size);
	VERTEX v6(0, 0, size);

	UVPOINT uv1(0.5, 0);
	UVPOINT uv2(1.0, 0.5);
	UVPOINT uv3(0.5, 1.0);
	UVPOINT uv4(0, 0.5);
	UVPOINT uv5(0.5, 0.5);

	this->mesh.addFace(v1, v2, v5, uv1, uv2, uv5);
	this->mesh.addFace(v2, v3, v5, uv2, uv3, uv5);
	this->mesh.addFace(v3, v4, v5, uv3, uv4, uv5);
	this->mesh.addFace(v4, v1, v5, uv4, uv1, uv5);

	this->mesh.addFace(v2, v1, v6, uv1, uv2, uv5);
	this->mesh.addFace(v3, v2, v6, uv2, uv3, uv5);
	this->mesh.addFace(v4, v3, v6, uv3, uv4, uv5);
	this->mesh.addFace(v1, v4, v6, uv4, uv1, uv5);

	this->mesh.translate(position.x, position.y, position.z);
}
void GameCore::Diamond::update()
{
}