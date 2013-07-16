#include "..\include\RayTracer.h"

Sphere::Sphere()
{
	this->radius = 0.0f;
}
Sphere::~Sphere()
{
}

void Sphere::initialize(VEC4 &position, float size)
{
	Entity::initialize();
	this->radius = size;
	this->position = position;
}
void Sphere::uninitialize()
{
}

bool Sphere::hitByRay(RAY &ray, RAYHIT* outputHit)
{
	float a = Dot(ray.direction, ray.direction);
	float b = Dot(((ray.origin - this->position) * 2), ray.direction);
	float c = Dot((ray.origin - this->position), (ray.origin - this->position)) - (this->radius * this->radius);
	float d = (b * b) - (4.0f * a * c);

	if (d >= 0)
	{
		float e = sqrt(d);

		float t1 = (-b - e) / (2 * a);
		float t2 = (-b + e) / (2 * a);

		if (t1 < 0.0f || t2 < 0.0f) return false;

		VEC4 intersection;
		float t;
		if (t1 < t2)
		{
			intersection = ray.origin + (ray.direction * t1);
			t = t1;
		}
		else
		{
			intersection = ray.origin + (ray.direction * t2);
			t = t2;
		}

		if (ray.length > 0.0f && t > ray.length) return false;

		VEC3 surfaceNormal = Normalize(intersection - this->position);

		VEC3 d = CreateVector(intersection, this->position, true);//CreateVector(this->position, intersection, true);
		float u = (surfaceNormal.x + 1) / 2;
		float v = (surfaceNormal.y + 1) / 2;

		if (outputHit != NULL)
		{
			*outputHit = RAYHIT(
				ray, 
				t, 
				intersection, 
				surfaceNormal, 
				this->material, 
				VEC2(u, v), 
				this);
		}
		return true;
	}
	
	return false;
}