#include "..\include\RayTracer.h"

Camera::Camera()
{
	this->position = VEC4(0.0f, 0.0f, 0.0f, 1.0f);
	this->dimensions = VEC2(1.0f, 1.0f);
	this->focalLength = 0.0f;
	this->sampleSize = 1;
}
Camera::~Camera()
{
}

void Camera::sampleCastRays(COLOR* outColor, VEC3& rayDirection, VEC4& minBound, VEC4& maxBound, int sampleSize)
{
	if (sampleSize < 1) return;
	if (Entities.length() < 1) return;
	float xDif = maxBound.x - minBound.x;
	float yDif = maxBound.y - minBound.y;
	float zDif = maxBound.z - minBound.z;

	if (sampleSize == 1)
	{
		RAYHIT hit;
		VEC4 sampleOrigin = VEC4(
			minBound.x + (xDif * 0.5f), 
			minBound.y + (yDif * 0.5f), 
			minBound.z + (zDif * 0.5f), 
			1.0f);
		this->castRay(&hit, RAY(sampleOrigin, rayDirection));

		this->calcSource(outColor, hit, rayDirection);
		return;
	}

	COLOR sample(0.0f, 0.0f, 0.0f, 0.0f);
	for (int i = 0; i < sampleSize; i++)
	{
		RAYHIT newHit;
		VEC4 randSampleOrigin = VEC4(
			minBound.x + (xDif * RANDOM_Scalar()), 
			minBound.y + (yDif * RANDOM_Scalar()), 
			minBound.z + (zDif * RANDOM_Scalar()), 
			1.0);
		this->castRay(&newHit, RAY(randSampleOrigin, rayDirection));

		COLOR newColor(0.0f, 0.0f, 0.0f, 0.0f);
		this->calcSource(&newColor, newHit, rayDirection);

		sample += newColor;
	}
	sample /= float(sampleSize);

	*outColor = sample;
}
bool Camera::castRay(RAYHIT* hit, RAY &ray)
{
	if (Entities.length() < 1) return false;
		
	RAYHIT rayhit;
	float t = FLT_MAX;
	bool didRayHit = false;
	for (uint e = 0; e < Entities.length(); e++)
	{
		RAYHIT newhit;
		Entity* entity = Entities[e];
		didRayHit = didRayHit || entity->hitByRay(ray, &newhit);

		if (didRayHit && newhit.t < t)
		{
			t = newhit.t;
			rayhit = newhit;
		}
	}

	if (didRayHit)
	{
		*hit = rayhit;
		return true;
	}
	else
	{
		return false;
	}
}
void Camera::calcSource(COLOR* outColor, RAYHIT &hit, VEC3& cameraDirection)
{
	if (Lights.length() < 1) return;
	if (hit.surfaceMaterial == NULL) return;

	//*outColor = COLOR(abs(hit.surfaceNormal.x), abs(hit.surfaceNormal.y), abs(hit.surfaceNormal.z), 1.0f);
	//return;
	
	Material::GetColor(outColor, hit);
	
#if 1
	if (hit.surfaceMaterial->reflect.a > 0)
	{
		//VEC3 reflectVector = hit.ray.direction * VEC3(hit.surfaceMaterial->reflect.r, hit.surfaceMaterial->reflect.g, hit.surfaceMaterial->reflect.b);
		//reflectVector = Normalize(reflectVector);
		RAY reflectRay(hit.intersection, Reflect(hit.ray.direction * -1.0f, hit.surfaceNormal));
		RAYHIT reflectHit;

		this->castRay(&reflectHit, reflectRay);
		COLOR reflectColor;
		Material::GetColor(&reflectColor, reflectHit);
		outColor->r += reflectColor.r * hit.surfaceMaterial->reflect.a;
		outColor->g += reflectColor.g * hit.surfaceMaterial->reflect.a;
		outColor->b += reflectColor.b * hit.surfaceMaterial->reflect.a;
	}
#endif

#if 1
	for (uint l = 0; l < Lights.length(); l++)
	{
		Light* light = Lights[l];
				
		light->calcLight(outColor, hit, cameraDirection);
	}
#endif
}
void Camera::castRays(SURFACE* surface)
{
	VEC4 p1, p2, p3, p4;
	VEC3 normal;
	this->calcViewPort(surface->width, surface->height, VEC3(this->position), &p1, &p2, &p3, &p4, &normal);
	VEC3 px = CreateVector(p1, p2);
	VEC3 py = CreateVector(p1, p3);
	//CalculateNormal(p2, p1, p3, &normal);
	VEC4 focalPoint = p1 + (px * 0.5) + (py * 0.5) + ((normal * -1) * this->focalLength);

	for (uint i = 0; i < surface->height; i++)
	{
		for (uint k = 0; k < surface->width; k++)
		{
			float u = float(k) / float(surface->width);
			float v = float(i) / float(surface->height);
			VEC4 rayPosition = p1 + (px * u) + (py * v);
			VEC3 rayDirection = CreateVector(focalPoint, rayPosition);
			rayDirection = Normalize(rayDirection);
			
			COLOR color(0.0f, 0.0f, 0.0f, 0.0f);
			RAYHIT hit;
			
			/*this->sampleCastRays(&color, rayDirection, 
				p1 + (px * (float(k) / float(surface->width))) + (py * (float(i) / float(surface->height))), 
				p1 + (px * (float(k + 1) / float(surface->width))) + (py * (float(i + 1) / float(surface->height))), 
				this->sampleSize);*/
			this->castRay(&hit, RAY(rayPosition, rayDirection));
			this->calcSource(&color, hit, normal);
			
			if (color.a > 0) PutPixel(surface, k, i, color);
		}
	}
}

void Camera::calcViewPort(uint width, uint height, VEC3& translation, VEC4* p1, VEC4* p2, VEC4* p3, VEC4* p4, VEC3* normal)
{
	float aspect = float(width) / float(height);
	VEC3 f = CreateVector(translation, VEC4(0.0f, 0.0f, 0.0f, 0.0f), true);
	VEC3 s = Cross(VEC3(0.0f, 1.0f, 0.0f), f);
	VEC3 u = Cross(s, f);

	float w = aspect * 0.5f * this->dimensions.x;
	float h = 0.5f * this->dimensions.y;
	VEC4 v1 = VEC4((s * -w) + (u *  h), 1.0f);
	VEC4 v2 = VEC4((s *  w) + (u *  h), 1.0f);
	VEC4 v3 = VEC4((s * -w) + (u * -h), 1.0f);
	VEC4 v4 = VEC4((s *  w) + (u * -h), 1.0f);
	
	*normal = f;
	*p1 = v1 + translation;
	*p2 = v2 + translation;
	*p3 = v3 + translation;
	*p4 = v4 + translation;
	
#if 0
	VEC3 px = CreateVector(*p1, *p2);
	VEC3 py = CreateVector(*p1, *p3);
	LOG_Outvf("F", (float*)&f, 3);
	LOG_Outvf("S", (float*)&s, 3);
	LOG_Outvf("U", (float*)&u, 3);
	LOG_Outvf("P1", (float*)&*p1, 4);
	LOG_Outvf("P2", (float*)&*p2, 4);
	LOG_Outvf("P3", (float*)&*p3, 4);
	LOG_Outvf("P4", (float*)&*p4, 4);
	LOG_Outvf("PX", (float*)&px, 3);
	LOG_Outvf("PY", (float*)&py, 3);
	LOG_Message("");
#endif
}