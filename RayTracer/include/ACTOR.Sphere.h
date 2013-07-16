#ifndef __ACTOR_SPHERE_H_
#define __ACTOR_SPHERE_H_

class Sphere : public Entity
{
public:
	Sphere();
	~Sphere();

	void initialize(VEC4 &position, float size = 1.0f);
	void uninitialize();

	bool hitByRay(RAY &ray, RAYHIT* outputHit = NULL);

	float radius;
};

#endif