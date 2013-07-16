#ifndef __CORE_ENTITY_H_
#define __CORE_ENTITY_H_

class Entity
{
public:
	Entity();
	~Entity();

	virtual void initialize();
	virtual void uninitialize();

	virtual bool hitByRay(RAY& ray, RAYHIT* outputHit = NULL);
			
	VEC4 position;
	Material* material;
	OBJ_MESH* mesh;
};

#endif