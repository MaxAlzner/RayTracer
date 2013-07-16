#ifndef __CORE_PRIMITIVES_H_
#define __CORE_PRIMITIVES_H_

struct RAY
{
	RAY()
	{
		this->origin = VEC4(0.0f, 0.0f, 0.0f, 1.0f);
		this->direction = VEC3(0.0f, 0.0f, 0.0f);
		this->color = COLOR(0.0f, 0.0f, 0.0f, 1.0f);
		this->length = 0.0f;
	}
	RAY(VEC4& position, VEC3& direction)
	{
		this->origin = position;
		this->direction = direction;
		this->color = COLOR(0.0f, 0.0f, 0.0f, 1.0f);
		this->length = 0.0f;
	}
	RAY(VEC4& position, VEC3& direction, float length)
	{
		this->origin = position;
		this->direction = direction;
		this->color = COLOR();
		this->length = length;
	}

	VEC4 origin;
	VEC3 direction;
	COLOR color;
	float length;
};
struct RAYHIT
{
	RAYHIT()
	{
		this->t = FLT_MAX;
		this->surfaceMaterial = NULL;
		this->surface = NULL;
	}
	RAYHIT(RAY ray, float t, VEC4& intersection, VEC3& surfaceNormal, Material* surfaceMaterial, VEC2& surfaceUV, Entity* surface)
	{
		this->ray = ray;
		this->t = t;
		this->intersection = intersection;
		this->surfaceNormal = surfaceNormal;
		this->surfaceMaterial = surfaceMaterial;
		this->surfaceUV = surfaceUV;
		this->surface = surface;
	}
	RAY ray;
	float t;
	VEC4 intersection;
	VEC3 surfaceNormal;
	Material* surfaceMaterial;
	VEC2 surfaceUV;
	Entity* surface;
};

#endif