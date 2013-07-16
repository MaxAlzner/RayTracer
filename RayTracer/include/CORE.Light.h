#ifndef __CORE_LIGHT_H_
#define __CORE_LIGHT_H_

class Light
{
public:
	Light();
	Light(VEC4& pos, VEC3& intensity, COLOR& color);
	~Light();

	void calcLight(COLOR* outColor, RAYHIT& hit, VEC3& cameraVector);
	void calcDiffuse(COLOR* outColor, RAYHIT& hit);
	void calcSpecular(COLOR* outColor, RAYHIT& hit, VEC3& cameraVector);
	void calcIridescence(COLOR* outColor, RAYHIT& hit, VEC3& cameraVector);
	void calcShadow(COLOR* outColor, RAYHIT& hit);

	bool hitByLight(RAYHIT& hit);

	VEC4 position;
	VEC3 direction;
	VEC3 intensity;
	COLOR color;
	float shadowIntensity;
	COLOR shadowColor;
	uint lightingMode;
};

#endif