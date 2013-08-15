#include "..\include\RayTracer.h"

Light::Light()
{
	this->position = VEC4(0.0f, 0.0f, 0.0f, 1.0f);
	this->direction = VEC3(0.0f, 0.0f, 0.0f);
	this->intensity = VEC3(0.4f, 4.0f, 16.0f);
	this->color = COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	this->lightingMode = 0;
	this->shadowIntensity = 0.4f;
	this->shadowColor = COLOR(0.0f, 0.0f, 0.0f, 1.0f);
}
Light::Light(VEC4& pos, VEC3& intensity, COLOR& color)
{
	this->position = pos;
	this->direction = VEC3(0.0f, 0.0f, 0.0f);
	this->intensity = intensity;
	this->color = color;
	this->lightingMode = 0;
	this->shadowIntensity = 0.4f;
	this->shadowColor = COLOR(0.0f, 0.0f, 0.0f, 1.0f);
}
Light::~Light()
{
}

void Light::calcLight(COLOR* outColor, RAYHIT& hit, VEC3& cameraVector)
{
	if (outColor == NULL) return;

	this->calcDiffuse(outColor, hit);
#if 0
	this->calcIridescence(outColor, hit, cameraVector);
#endif

	bool hitByLight = this->hitByLight(hit);
	if (!hitByLight)
	{
		this->calcShadow(outColor, hit);
	}

	if (hitByLight)
	{
		this->calcSpecular(outColor, hit, cameraVector);
	}
}
void Light::calcDiffuse(COLOR* outColor, RAYHIT& hit)
{
	COLOR color;
	Material::GetColor(&color, hit);

	VEC3 lightVector = CreateVector(this->position, hit.intersection);

	float distance = Magnitude(lightVector);
	float dropoff = Clamp(1.0f / (this->intensity.x + (this->intensity.y * distance) + (this->intensity.z * distance * distance)));
	lightVector = Normalize(lightVector);

	float lambert = Clamp(
		Dot(lightVector, 
		hit.surfaceMaterial->getNormalAt(hit.surfaceNormal, hit.surfaceTangent, hit.surfaceBinormal, hit.surfaceUV)
		//hit.surfaceNormal
		) * -1.0f, 0.25f, 1.0f);

	float r = Clamp(this->color.r * lambert * dropoff);
	float g = Clamp(this->color.g * lambert * dropoff);
	float b = Clamp(this->color.b * lambert * dropoff);
	outColor->r *= r;
	outColor->g *= g;
	outColor->b *= b;
}
void Light::calcSpecular(COLOR* outColor, RAYHIT& hit, VEC3& cameraVector)
{
	if (hit.surfaceMaterial == NULL) return;
	if (hit.surfaceMaterial->specular <= 0) return;

	VEC3 lightVector = CreateVector(this->position, hit.intersection);
	lightVector = Normalize(lightVector);

	float dot = Dot(hit.surfaceNormal * 2.0f, cameraVector * hit.surfaceNormal);
	VEC3 reflect = Reflect(cameraVector, hit.surfaceNormal);
	reflect = Normalize(reflect);

	float specular = Dot(lightVector, reflect);
	specular = pow(specular, 40);
	specular *= hit.surfaceMaterial->getSpecularAt(hit.surfaceUV);
	specular *= Clamp(hit.surfaceMaterial->specular);
	
	outColor->r = Clamp(
		outColor->r + 
		specular
		);
	outColor->g = Clamp(
		outColor->g + 
		specular
		);
	outColor->b = Clamp(
		outColor->b + 
		specular
		);
}
void Light::calcIridescence(COLOR* outColor, RAYHIT& hit, VEC3& cameraVector)
{
	VEC3 iri = VEC3(0.4f, 0.2f, 0.9f);
	VEC3 k = VEC3(1.0f, 1.0f, 1.0f);
	k = Normalize(k);
	float theta = 0.5f * 3.14f * Dot(cameraVector, hit.surfaceNormal);
	VEC3 riri = 
		(iri * cos(theta)) + 
		(Cross(cameraVector, iri) * sin(theta)) + 
		(cameraVector * Dot(cameraVector, iri) * (1.0f - cos(theta)));

	outColor->r *= riri.x;
	outColor->g *= riri.y;
	outColor->b *= riri.z;
}
void Light::calcShadow(COLOR* outColor, RAYHIT& hit)
{
	if (outColor == NULL) return;

	this->shadowIntensity = Clamp(this->shadowIntensity);

	outColor->r *= this->shadowIntensity;
	outColor->g *= this->shadowIntensity;
	outColor->b *= this->shadowIntensity;
}

bool Light::hitByLight(RAYHIT& hit)
{
	VEC3 shadowVector = CreateVector(hit.intersection, this->position);

	//if (VECTOR::DotProduct(shadowVector, hit.surfaceNormal) > 0) return false;

	float dist = Magnitude(shadowVector);
	shadowVector = Normalize(shadowVector);
	RAY shadowRay(hit.intersection, shadowVector, dist);

	bool result = true;
	for (uint i = 0; i < Entities.length(); i++)
	{
		Entity* entity = Entities[i];
		if (entity != hit.surface)
		{
			result = result && !entity->hitByRay(shadowRay, NULL);
		}
	}
	return result;
}