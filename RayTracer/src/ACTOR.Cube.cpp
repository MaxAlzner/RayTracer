#include "../GameCore.h"

using namespace CORE;

GameCore::Cube::Cube()
{
}
GameCore::Cube::~Cube()
{
}

void GameCore::Cube::initialize()
{
	this->initialize(VECTOR());
}
void GameCore::Cube::initialize(VECTOR &position, VALUE size)
{
	this->mesh.addVertex(-size, -size, -size);
	this->mesh.addVertex(size, size, size);
	
	this->mesh.addNormal(-1, 0, 0);
	this->mesh.addNormal(0, -1, 0);
	this->mesh.addNormal(0, 0, -1);
	this->mesh.addNormal(1, 0, 0);
	this->mesh.addNormal(0, 1, 0);
	this->mesh.addNormal(0, 0, 1);

	this->mesh.translate(position.x, position.y, position.z);
}
void GameCore::Cube::update()
{
}

bool GameCore::Cube::hitByRay(RAY &ray, CORE::RAYHIT* outputHit)
{
	if (this->mesh.vertexBuffer.size() < 2) return false;
	VERTEX p0 = this->mesh.vertexBuffer[0];
	VERTEX p1 = this->mesh.vertexBuffer[1];
	VALUE x0 = p0.x;
	VALUE y0 = p0.y;
	VALUE z0 = p0.z;
	VALUE x1 = p1.x;
	VALUE y1 = p1.y;
	VALUE z1 = p1.z;
	VALUE ox = ray.origin.x;
	VALUE oy = ray.origin.y;
	VALUE oz = ray.origin.z;
	VALUE dx = ray.direction.x;
	VALUE dy = ray.direction.y;
	VALUE dz = ray.direction.z;

	if (x0 > x1) VECTOR::Swap(x0, x1);
	if (y0 > y1) VECTOR::Swap(y0, y1);
	if (z0 > z1) VECTOR::Swap(z0, z1);

	VALUE txmin, tymin, tzmin, txmax, tymax, tzmax;

	VALUE a = 1.0 / dx;
	if (a >= 0)
	{
		txmin = (x0 - ox) * a;
		txmax = (x1 - ox) * a;
	}
	else
	{
		txmin = (x1 - ox) * a;
		txmax = (x0 - ox) * a;
	}
	VALUE b = 1.0 / dy;
	if (b >= 0)
	{
		tymin = (y0 - oy) * b;
		tymax = (y1 - oy) * b;
	}
	else
	{
		tymin = (y1 - oy) * b;
		tymax = (y0 - oy) * b;
	}
	VALUE c = 1.0 / dz;
	if (c >= 0)
	{
		tzmin = (z0 - oz) * c;
		tzmax = (z1 - oz) * c;
	}
	else
	{
		tzmin = (z1 - oz) * c;
		tzmax = (z0 - oz) * c;
	}

	VALUE t0, t1;
	int facein, faceout;

	if (txmin > tymin)
	{
		t0 = txmin;
		facein = (a >= 0.0) ? 0 : 3;
	}
	else
	{
		t0 = tymin;
		facein = (b >= 0.0) ? 1 : 4;
	}

	if (tzmin > t0)
	{
		t0 = tzmin;
		facein = (c >= 0.0) ? 2 : 5;
	}


	if (txmax < tymax)
	{
		t1 = txmax;
		faceout = (a >= 0.0) ? 3 : 0;
	}
	else
	{
		t1 = tymax;
		faceout = (b >= 0.0) ? 4 : 1;
	}

	if (tzmax < t1)
	{
		t1 = tzmax;
		faceout = (c >= 0.0) ? 5 : 2;
	}


	VALUE kEpsilon = 1.0;
	VALUE t = 0;
	if (t0 < t1 && t1 > kEpsilon)
	{
		if (t0 > kEpsilon) t = t0;
		else t = t1;

		if (ray.length > 0 && t > ray.length) return false;

		VERTEX intersection = ray.origin + (ray.direction * t);
		VECTOR surfaceNormal = this->mesh.vertexNormalBuffer[facein];

		if (VECTOR::DotProduct(ray.direction, surfaceNormal) > 1) return false;

		VALUE u, v;
		VALUE width = abs(p1.x - p0.x);
		VALUE height = abs(p1.y - p0.y);
		VALUE depth = abs(p1.z - p0.z);
		VECTOR toEdge;
		if (facein < 3)
		{
			toEdge = VECTOR::CreateVector(intersection, p0);

			if (facein == 0)
			{
				u = abs(toEdge.z) / (depth);
				v = abs(toEdge.y) / (height);
			}
			else if (facein == 1)
			{
				u = abs(toEdge.x) / (width);
				v = abs(toEdge.z) / (depth);
			}
			else
			{
				u = abs(toEdge.x) / (width);
				v = abs(toEdge.y) / (height);
			}
		}
		else
		{
			toEdge = VECTOR::CreateVector(intersection, p1);

			if (facein == 3)
			{
				u = abs(toEdge.z) / (depth);
				v = abs(toEdge.y) / (height);
			}
			else if (facein == 4)
			{
				u = abs(toEdge.x) / (width);
				v = abs(toEdge.z) / (depth);
			}
			else
			{
				u = abs(toEdge.x) / (width);
				v = abs(toEdge.y) / (height);
			}
		}
		
		if (outputHit != NULL)
		{
			*outputHit = RAYHIT(
				ray, 
				t, 
				intersection, 
				surfaceNormal, 
				&this->material, 
				UVPOINT(u, v), 
				this);
		}
		return true;
	}

	return false;
}