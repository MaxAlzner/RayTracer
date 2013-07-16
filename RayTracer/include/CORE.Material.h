#ifndef __CORE_MATERIAL_H_
#define __CORE_MATERIAL_H_

class Material
{
public:
	Material();
	~Material();

	void setDiffuseMap(SURFACE* texture);
	void setSpecularMap(SURFACE* texture);
	void setNormalMap(SURFACE* texture);

	void getColorAt(COLOR* outColor, VEC2& uv);
	float getSpecularAt(VEC2& uv);
	VEC3 getNormalAt(VEC3& normal, VEC2& uv);
		
	COLOR overlay;
	COLOR emissive;
	COLOR reflect;
	float alpha;
	float specular;

	SURFACE* diffuseMap;
	SURFACE* specularMap;
	SURFACE* normalMap;

	static void GetColor(COLOR* outColor, RAYHIT &hit);
};

#endif