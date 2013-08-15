#include "..\include\RayTracer.h"

Entity::Entity()
{
	this->position = VEC4(0.0f, 0.0f, 0.0f, 1.0);
	this->material = NULL;
	this->mesh = NULL;
}
Entity::~Entity()
{
}

void Entity::initialize()
{
	this->material = new Material;
}
void Entity::uninitialize()
{
	if (this->material != NULL) delete this->material;
}

bool Entity::hitByRay(RAY& ray, RAYHIT* outputHit)
{
	if (this->mesh == NULL || this->material == NULL) return false;
	RAYHIT hit;

	for (uint index = 0; index < this->mesh->faces.length(); index++)
	{
		OBJ_FACE* face = &this->mesh->faces[index];
		if (
			face->a_vertex < 0 || face->b_vertex < 0 || face->c_vertex < 0 || 
			face->a_texcoord < 0 || face->b_texcoord < 0 || face->c_texcoord < 0 || 
			face->a_normal < 0 || face->b_normal < 0 || face->c_normal < 0) continue;
		OBJ_VERTEX va = this->mesh->vertices[face->a_vertex];
		OBJ_VERTEX vb = this->mesh->vertices[face->b_vertex];
		OBJ_VERTEX vc = this->mesh->vertices[face->c_vertex];
		OBJ_TEXCOORD auv = this->mesh->texcoords[face->a_texcoord];
		OBJ_TEXCOORD buv = this->mesh->texcoords[face->b_texcoord];
		OBJ_TEXCOORD cuv = this->mesh->texcoords[face->c_texcoord];
		OBJ_NORMAL an = this->mesh->normals[face->a_normal];
		OBJ_NORMAL bn = this->mesh->normals[face->b_normal];
		OBJ_NORMAL cn = this->mesh->normals[face->c_normal];
		OBJ_NORMAL at = this->mesh->tangents[face->a_normal];
		OBJ_NORMAL bt = this->mesh->tangents[face->b_normal];
		OBJ_NORMAL ct = this->mesh->tangents[face->c_normal];
		OBJ_NORMAL ab = this->mesh->binormals[face->a_normal];
		OBJ_NORMAL bb = this->mesh->binormals[face->b_normal];
		OBJ_NORMAL cb = this->mesh->binormals[face->c_normal];
		
		VEC3 faceNormal = Normalize(VEC3(an.x + bn.x + cn.x, an.y + bn.y + cn.y, an.z + bn.z + cn.z));
		if (Dot(ray.direction, faceNormal) > 0) continue;

		float a = va.x - vb.x;
		float b = va.x - vc.x;
		float c = ray.direction.x;
		float d = va.x - ray.origin.x;
		float e = va.y - vb.y;
		float f = va.y - vc.y;
		float g = ray.direction.y;
		float h = va.y - ray.origin.y;
		float i = va.z - vb.z;
		float j = va.z - vc.z;
		float k = ray.direction.z;
		float l = va.z - ray.origin.z;

		float beta = 
			((d * ((f * k) - (g * j))) + (b * ((g * l) - (h * k))) + (c * ((h * j) - (f * l)))) / 
			((a * ((f * k) - (g * j))) + (b * ((g * i) - (e * k))) + (c * ((e * j) - (f * i))));
		float gamma = 
			((a * ((h * k) - (g * l))) + (d * ((g * i) - (e * k))) + (c * ((e * l) - (h * i)))) / 
			((a * ((f * k) - (g * j))) + (b * ((g * i) - (e * k))) + (c * ((e * j) - (f * i))));
		float alpha = 1.0f - (beta + gamma);

		if (alpha >= 0 && beta >= 0 && gamma >= 0)
		{
			float t = 
				(a * (f * l - h * j) + b * (h * i - e * l) + d * (e * j - f * i)) / 
				(a * (f * k - g * j) + b * (g * i - e * k) + c * (e * j - f * i));

			//if (t < 0) return false;
			if (ray.length > 0 && t > ray.length) return false;

			VEC4 intersection = ray.origin + (ray.direction * t);

			float u = (alpha * auv.u) + (beta * buv.u) + (gamma * cuv.u);
			float v = (alpha * auv.v) + (beta * buv.v) + (gamma * cuv.v);
			
			VEC3 surfaceNormal = Normalize(VEC3(
				(an.x * alpha) + (bn.x * beta) + (cn.x * gamma), 
				(an.y * alpha) + (bn.y * beta) + (cn.y * gamma), 
				(an.z * alpha) + (bn.z * beta) + (cn.z * gamma)
				));
			VEC3 surfaceTangent = Normalize(VEC3(
				(at.x * alpha) + (bt.x * beta) + (ct.x * gamma), 
				(at.y * alpha) + (bt.y * beta) + (ct.y * gamma), 
				(at.z * alpha) + (bt.z * beta) + (ct.z * gamma)
				));
			VEC3 surfaceBinormal = Normalize(VEC3(
				(ab.x * alpha) + (bb.x * beta) + (cb.x * gamma), 
				(ab.y * alpha) + (bb.y * beta) + (cb.y * gamma), 
				(ab.z * alpha) + (bb.z * beta) + (cb.z * gamma)
				));
			
			if (outputHit != NULL)
			{
				*outputHit = RAYHIT(
					ray, 
					t, 
					intersection, 
					surfaceNormal, 
					surfaceTangent, 
					surfaceBinormal, 
					this->material, 
					VEC2(u, v), 
					this);
			}
			return true;
		}
	}

	return false;
}