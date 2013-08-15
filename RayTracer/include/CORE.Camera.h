#ifndef __CORE_CAMERA_H_
#define __CORE_CAMERA_H_

class Camera
{
public:
	Camera();
	~Camera();

	void sampleCastRays(COLOR* outColor, VEC3& rayDirection, VEC4& minBound, VEC4& maxBound, int sampleSize = 1);
	bool castRay(RAYHIT* hit, RAY &ray);
	void calcSource(COLOR* outColor, RAYHIT &hit, VEC3& cameraDirection);

	void castRays(SURFACE* surface);

	void calcViewPort(uint width, uint height, VEC3& translation, VEC4* p1, VEC4* p2, VEC4* p3, VEC4* p4, VEC3* normal);

	VEC4 position;
	VEC2 dimensions;
	float focalLength;
	uint sampleSize;
};

#endif