#include "..\include\RayTracer.h"

Material::Material()
{
	this->overlay = COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	this->emissive = COLOR(0.0f, 0.0f, 0.0f, 1.0f);
	this->reflect = COLOR(0.0f, 0.0f, 0.0f, 1.0f);
	this->alpha = 1.0f;
	this->specular = 1.0f;
	this->diffuseMap = NULL;
	this->specularMap = NULL;
	this->normalMap = NULL;
}
Material::~Material()
{
}

void Material::setDiffuseMap(SURFACE* texture)
{
	this->diffuseMap = texture;
}
void Material::setSpecularMap(SURFACE* texture)
{
	this->specularMap = texture;
}
void Material::setNormalMap(SURFACE* texture)
{
	this->normalMap = texture;
}

void Material::getColorAt(COLOR* outColor, VEC2& uv)
{
	if (outColor == NULL) return;
	float u = Clamp(uv.x);
	float v = Clamp(uv.y);
	
	COLOR diffuse;
	if (this->diffuseMap != NULL)
	{
		uint x = uint(u * float(this->diffuseMap->width));
		uint y = uint(v * float(this->diffuseMap->height));
		COLOR texture = COLOR();
		GetPixel(this->diffuseMap, x, y, &texture);
		diffuse.r *= texture.r;
		diffuse.g *= texture.g;
		diffuse.b *= texture.b;
		diffuse.a *= texture.a;
	}
	diffuse.r *= this->overlay.r;
	diffuse.g *= this->overlay.g;
	diffuse.b *= this->overlay.b;
	diffuse.a *= this->overlay.a;
	outColor->r = diffuse.r;
	outColor->g = diffuse.g;
	outColor->b = diffuse.b;
	outColor->a = diffuse.a;
}
float Material::getSpecularAt(VEC2& uv)
{
	float u = Clamp(uv.x);
	float v = Clamp(uv.y);
	
	float brightness = 1.0f;
	if (this->specularMap != NULL)
	{
		uint x = uint(u * float(this->specularMap->width));
		uint y = uint(v * float(this->specularMap->height));
		COLOR texture = COLOR();
		GetPixel(this->specularMap, x, y, &texture);
		brightness = texture.r * texture.g * texture.b;
	}

	return brightness;
}
VEC3 Material::getNormalAt(VEC3& normal, VEC2& uv)
{
	float u = Clamp(uv.x);
	float v = Clamp(uv.y);
	
	/*if (this->normalMap != NULL)
	{
		int* video = this->normalMap->video;
		int width = this->normalMap->width;
		int height = this->normalMap->height;

		if (video != NULL)
		{
			int normalInt = Drawing::GetPixel(video, width, height, u * width, v * height);
			VECTOR mapNormal = VECTOR(
				VALUE(RGB::GetRed(normalInt)) / 255.0, 
				VALUE(RGB::GetGreen(normalInt)) / 255.0, 
				VALUE(RGB::GetBlue(normalInt)) / 255.0, 
				0);

			// Calculate a local coordinate space
			VECTOR upVector(0.0, 0.0, 1.0, 0.0);
			VECTOR xAxis = VECTOR::Tangent(upVector, normal);
			VECTOR yAxis = normal; // At surface of the object
			VECTOR zAxis = VECTOR::CrossProduct(yAxis, xAxis);
			// Project the normal map value into the local space at this object
			VECTOR result = (xAxis * mapNormal.x) + (yAxis * mapNormal.y) + (zAxis * mapNormal.z);
			return result;
		}
	}*/

	return normal;
}

void Material::GetColor(COLOR* outColor, RAYHIT& hit)
{
	if (hit.surfaceMaterial == NULL) return;

	hit.surfaceMaterial->getColorAt(outColor, hit.surfaceUV);
}