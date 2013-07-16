#include "../GameCore.h"

CORE::Mesh::Mesh()
{
	this->origin = VERTEX(0.0, 0.0, 0.0);
	this->parent = NULL;
	this->freeze();
	this->renderSettings = 0;
}
CORE::Mesh::~Mesh()
{
	this->clear();
}

void CORE::Mesh::translate(VALUE x, VALUE y, VALUE z, int mode)
{
	if (x == 0.0 && y == 0.0 && z == 0.0) return;

	if (mode & MODE_LOCAL)
	{
	}
	
	this->translation.x += x;
	this->translation.y += y;
	this->translation.z += z;
	this->moveOrigin(x, y, z);
}
void CORE::Mesh::rotate(VALUE x, VALUE y, VALUE z, int mode)
{
	if (x == 0.0 && y == 0.0 && z == 0.0) return;

	if (mode & MODE_LOCAL)
	{
	}

	this->rotation.x += x;
	this->rotation.y += y;
	this->rotation.z += z;

	VECTOR::Module(this->rotation, 360);
}
void CORE::Mesh::transform(VALUE x, VALUE y, VALUE z, int mode)
{
	if (x == 0.0 && y == 0.0 && z == 0.0) return;

	if (mode & MODE_LOCAL)
	{
	}
	
	this->transformation.x += x;
	this->transformation.y += y;
	this->transformation.z += z;
}
void CORE::Mesh::moveOrigin(VALUE x, VALUE y, VALUE z)
{
	this->origin.x += x;
	this->origin.y += y;
	this->origin.z += z;
}
void CORE::Mesh::rotateChildren(VALUE x, VALUE y, VALUE z, int mode)
{
	if (x == 0.0 && y == 0.0 && z == 0.0) return;

	this->childRotation.x += x;
	this->childRotation.y += y;
	this->childRotation.z += z;

	VECTOR::Module(this->childRotation, 360);
}
void CORE::Mesh::translate(VECTOR &v, int mode)
{
	this->translate(v.x, v.y, v.z, mode);
}
void CORE::Mesh::rotate(VECTOR &v, int mode)
{
	this->rotate(v.x, v.y, v.z, mode);
}
void CORE::Mesh::transform(VECTOR &v, int mode)
{
	this->transform(v.x, v.y, v.z, mode);
}
void CORE::Mesh::moveOrigin(VECTOR &v)
{
	this->moveOrigin(v.x, v.y, v.z);
}
void CORE::Mesh::rotateChildren(VECTOR &v, int mode)
{
	this->rotateChildren(v.x, v.y, v.z, mode);
}

void CORE::Mesh::freeze()
{
	VERTEXMATRIX scale = VERTEXMATRIX::Scale(this->transformation);
	VERTEXMATRIX rx = VERTEXMATRIX::RotateX(this->rotation.x, MODE_DEGREES);
	VERTEXMATRIX ry = VERTEXMATRIX::RotateY(this->rotation.y, MODE_DEGREES);
	VERTEXMATRIX rz = VERTEXMATRIX::RotateZ(this->rotation.z, MODE_DEGREES);
	VERTEXMATRIX move = VERTEXMATRIX::Translate(this->translation);
	VERTEXMATRIX childrx, childry, childrz, parentrx, parentry, parentrz, parentloc;
	if (this->parent != NULL)
	{
		childrx = VERTEXMATRIX::RotateX(this->parent->childRotation.x, MODE_DEGREES);
		childry = VERTEXMATRIX::RotateY(this->parent->childRotation.y, MODE_DEGREES);
		childrz = VERTEXMATRIX::RotateZ(this->parent->childRotation.z, MODE_DEGREES);
		parentrx = VERTEXMATRIX::RotateX(this->parent->rotation.x, MODE_DEGREES);
		parentry = VERTEXMATRIX::RotateY(this->parent->rotation.y, MODE_DEGREES);
		parentrz = VERTEXMATRIX::RotateZ(this->parent->rotation.z, MODE_DEGREES);
		parentloc = VERTEXMATRIX::Translate(this->parent->translation);
	}
	for (int i = 0; i < this->vertexBuffer.size(); i++)
	{
		VERTEX* v = &this->vertexBuffer[i];
		VERTEXMATRIX::Multiply(scale, *v);
		VERTEXMATRIX::Multiply(rx, *v);
		VERTEXMATRIX::Multiply(ry, *v);
		VERTEXMATRIX::Multiply(rz, *v);
		VERTEXMATRIX::Multiply(move, *v);
		if (this->parent != NULL)
		{
			VERTEXMATRIX::Multiply(childrx, *v);
			VERTEXMATRIX::Multiply(childry, *v);
			VERTEXMATRIX::Multiply(childrz, *v);
			VERTEXMATRIX::Multiply(parentrx, *v);
			VERTEXMATRIX::Multiply(parentry, *v);
			VERTEXMATRIX::Multiply(parentrz, *v);
			VERTEXMATRIX::Multiply(parentloc, *v);
		}
	}

	for (int k = 0; k < this->children.size(); k++) this->children[k]->freeze();

	this->translation = VECTOR(0.0, 0.0, 0.0, 0.0);
	this->rotation = VECTOR(0.0, 0.0, 0.0, 0.0);
	this->transformation = VECTOR(1.0, 1.0, 1.0, 0.0);
	this->childRotation = VECTOR(0, 0, 0, 0.0);
}
void CORE::Mesh::reset()
{
	this->translate(-this->translation.x, -this->translation.y, -this->translation.z);
	this->rotate(360.0 - this->rotation.x, 360.0 - this->rotation.y, 360.0 - this->rotation.z);
	this->transform(-(this->transformation.x - 1), -(this->transformation.y - 1), -(this->transformation.z - 1));

	this->freeze();
	this->origin = VERTEX(0.0, 0.0, 0.0);
}
void CORE::Mesh::clear()
{
	this->indexBuffer.clear();
	this->vertexBuffer.clear();
	this->vertexNormalBuffer.clear();
	this->uvChannel.clear();
}

int CORE::Mesh::addFace(VALUE ax, VALUE ay, VALUE az, VALUE bx, VALUE by , VALUE bz, VALUE cx, VALUE cy, VALUE cz)
{
	int aIndex, bIndex, cIndex;
	aIndex = this->checkForVertex(ax, ay, az);
	bIndex = this->checkForVertex(bx, by, bz);
	cIndex = this->checkForVertex(cx, cy, cz);
	VERTEX a = VERTEX(ax, ay, az);
	VERTEX b = VERTEX(bx, by, bz);
	VERTEX c = VERTEX(cx, cy, cz);

	if (aIndex < 0)
	{
		aIndex = this->vertexBuffer.size();
		this->vertexBuffer.push_back(a);
	}
	if (bIndex < 0)
	{
		bIndex = this->vertexBuffer.size();
		this->vertexBuffer.push_back(b);
	}
	if (cIndex < 0)
	{
		cIndex = this->vertexBuffer.size();
		this->vertexBuffer.push_back(c);
	}

	int normalIndex = this->vertexNormalBuffer.size();
	this->vertexNormalBuffer.push_back(FACE::CreateSurfaceNormal(a, b, c));

	this->indexBuffer.push_back(FACE(aIndex, bIndex, cIndex, -1, -1, -1, normalIndex));
	return this->indexBuffer.size() - 1;
}
int CORE::Mesh::addFace(VALUE ax, VALUE ay, VALUE az, VALUE bx, VALUE by, VALUE bz, VALUE cx, VALUE cy, VALUE cz, VALUE au, VALUE av, VALUE bu, VALUE bv, VALUE cu, VALUE cv)
{
	int index = this->addFace(ax, ay, az, bx, by, bz, cx, cy, cz);
	if (index < 0) return -1;

	FACE* face = &this->indexBuffer[index];
	UVPOINT auv(au, av);
	UVPOINT buv(bu, bv);
	UVPOINT cuv(cu, cv);
	face->auv = this->uvChannel.size();
	this->uvChannel.push_back(auv);
	face->buv = this->uvChannel.size();
	this->uvChannel.push_back(buv);
	face->cuv = this->uvChannel.size();
	this->uvChannel.push_back(cuv);
	return index;
}
int CORE::Mesh::addFace(VERTEX &a, VERTEX &b, VERTEX &c)
{
	return this->addFace(a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z);
}
int CORE::Mesh::addFace(VERTEX &a, VERTEX &b, VERTEX &c, VALUE au, VALUE av, VALUE bu, VALUE bv, VALUE cu, VALUE cv)
{
	return this->addFace(a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z, au, av, bu, bv, cu, cv);
}
int CORE::Mesh::addFace(VERTEX &a, VERTEX &b, VERTEX &c, UVPOINT &auv, UVPOINT &buv, UVPOINT &cuv)
{
	return this->addFace(a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z, auv.u, auv.v, buv.u, buv.v, cuv.u, cuv.v);
}
int CORE::Mesh::addVertex(VALUE x, VALUE y, VALUE z)
{
	int index = this->checkForVertex(x, y, z);
	if (index < 0)
	{
		index = this->vertexBuffer.size();
		this->vertexBuffer.push_back(VERTEX(x, y, z));
	}
	return index;
}
int CORE::Mesh::addVertex(VERTEX &vertex)
{
	return this->addVertex(vertex.x, vertex.y, vertex.z);
}
int CORE::Mesh::addNormal(VALUE x, VALUE y, VALUE z)
{
	int index = this->checkForNormal(x, y, z);
	if (index < 0)
	{
		index = this->vertexNormalBuffer.size();
		this->vertexNormalBuffer.push_back(VECTOR(x, y, z, 0));
	}
	return index;
}
int CORE::Mesh::addNormal(VECTOR &vector)
{
	return this->addNormal(vector.x, vector.y, vector.z);
}
int CORE::Mesh::addUV(VALUE u, VALUE v)
{
	int index = this->checkForUV(u, v);
	if (index < 0)
	{
		index = this->uvChannel.size();
		this->uvChannel.push_back(UVPOINT(u ,v));
	}
	return index;
}
int CORE::Mesh::addUV(UVPOINT &uv)
{
	return this->addUV(uv.u, uv.v);
}

void CORE::Mesh::draw(int* video, float* zBuffer, int width, int height, VECTOR &cameradir, VERTEX &camerapos, Mesh** onScreen)
{
	if (video == NULL || zBuffer == NULL || this->indexBuffer.size() <= 0) return;

	VERTEXMATRIX offset = VERTEXMATRIX::Translate(width / 2, height / 2, 0);
	VERTEXMATRIX flip = VERTEXMATRIX::RotateZ(PI);
	VERTEXMATRIX perp = VERTEXMATRIX::Perspective(0.001);
	VERTEXMATRIX scale = VERTEXMATRIX::Scale(this->transformation);
	VERTEXMATRIX rx = VERTEXMATRIX::RotateX(this->rotation.x, MODE_DEGREES);
	VERTEXMATRIX ry = VERTEXMATRIX::RotateY(this->rotation.y, MODE_DEGREES);
	VERTEXMATRIX rz = VERTEXMATRIX::RotateZ(this->rotation.z, MODE_DEGREES);
	VERTEXMATRIX move = VERTEXMATRIX::Translate(this->translation);
	VERTEXMATRIX zoom = VERTEXMATRIX::Scale(1.25, 1.25, 1);
	VERTEXMATRIX childrx, childry, childrz, parentrx, parentry, parentrz, parentloc;
	if (this->parent != NULL)
	{
		childrx = VERTEXMATRIX::RotateX(this->parent->childRotation.x, MODE_DEGREES);
		childry = VERTEXMATRIX::RotateY(this->parent->childRotation.y, MODE_DEGREES);
		childrz = VERTEXMATRIX::RotateZ(this->parent->childRotation.z, MODE_DEGREES);
		parentrx = VERTEXMATRIX::RotateX(this->parent->rotation.x, MODE_DEGREES);
		parentry = VERTEXMATRIX::RotateY(this->parent->rotation.y, MODE_DEGREES);
		parentrz = VERTEXMATRIX::RotateZ(this->parent->rotation.z, MODE_DEGREES);
		parentloc = VERTEXMATRIX::Translate(this->parent->translation);
	}
	VERTEXMATRIX camerarx = VERTEXMATRIX::RotateX(cameradir.x * 360, MODE_DEGREES);
	VERTEXMATRIX camerary = VERTEXMATRIX::RotateY(cameradir.y * 360, MODE_DEGREES);
	VERTEXMATRIX camerarz = VERTEXMATRIX::RotateZ(cameradir.z * 360, MODE_DEGREES);
	VERTEXMATRIX cameratrans = VERTEXMATRIX::Translate(camerapos);
	for (int i = 0; i < this->indexBuffer.size(); i++)
	{
		FACE* face = &this->indexBuffer[i];
		if (face->a < 0 || face->b < 0 || face->c < 0 || face->auv < 0 || face->buv < 0 || face->cuv < 0/* || face->normalIndex < 0*/) return;
		VERTEX a = this->vertexBuffer[face->a];
		VERTEX b = this->vertexBuffer[face->b];
		VERTEX c = this->vertexBuffer[face->c];
		UVPOINT auv = this->uvChannel[face->auv];
		UVPOINT buv = this->uvChannel[face->buv];
		UVPOINT cuv = this->uvChannel[face->cuv];

		VERTEXMATRIX::Multiply(scale, a);
		VERTEXMATRIX::Multiply(scale, b);
		VERTEXMATRIX::Multiply(scale, c);
		VERTEXMATRIX::Multiply(rx, a);
		VERTEXMATRIX::Multiply(rx, b);
		VERTEXMATRIX::Multiply(rx, c);
		VERTEXMATRIX::Multiply(ry, a);
		VERTEXMATRIX::Multiply(ry, b);
		VERTEXMATRIX::Multiply(ry, c);
		VERTEXMATRIX::Multiply(rz, a);
		VERTEXMATRIX::Multiply(rz, b);
		VERTEXMATRIX::Multiply(rz, c);
		VERTEXMATRIX::Multiply(move, a);
		VERTEXMATRIX::Multiply(move, b);
		VERTEXMATRIX::Multiply(move, c);
		if (this->parent != NULL)
		{
			VERTEXMATRIX::Multiply(childrx, a);
			VERTEXMATRIX::Multiply(childrx, b);
			VERTEXMATRIX::Multiply(childrx, c);
			VERTEXMATRIX::Multiply(childry, a);
			VERTEXMATRIX::Multiply(childry, b);
			VERTEXMATRIX::Multiply(childry, c);
			VERTEXMATRIX::Multiply(childrz, a);
			VERTEXMATRIX::Multiply(childrz, b);
			VERTEXMATRIX::Multiply(childrz, c);
			VERTEXMATRIX::Multiply(parentrx, a);
			VERTEXMATRIX::Multiply(parentrx, b);
			VERTEXMATRIX::Multiply(parentrx, c);
			VERTEXMATRIX::Multiply(parentry, a);
			VERTEXMATRIX::Multiply(parentry, b);
			VERTEXMATRIX::Multiply(parentry, c);
			VERTEXMATRIX::Multiply(parentrz, a);
			VERTEXMATRIX::Multiply(parentrz, b);
			VERTEXMATRIX::Multiply(parentrz, c);
			VERTEXMATRIX::Multiply(parentloc, a);
			VERTEXMATRIX::Multiply(parentloc, b);
			VERTEXMATRIX::Multiply(parentloc, c);
		}
		VERTEXMATRIX::Multiply(camerarx, a);
		VERTEXMATRIX::Multiply(camerarx, b);
		VERTEXMATRIX::Multiply(camerarx, c);
		VERTEXMATRIX::Multiply(camerary, a);
		VERTEXMATRIX::Multiply(camerary, b);
		VERTEXMATRIX::Multiply(camerary, c);
		VERTEXMATRIX::Multiply(camerarz, a);
		VERTEXMATRIX::Multiply(camerarz, b);
		VERTEXMATRIX::Multiply(camerarz, c);
		VERTEXMATRIX::Multiply(cameratrans, a);
		VERTEXMATRIX::Multiply(cameratrans, b);
		VERTEXMATRIX::Multiply(cameratrans, c);
		VERTEXMATRIX::Multiply(perp, a);
		VERTEXMATRIX::Multiply(perp, b);
		VERTEXMATRIX::Multiply(perp, c);
		
		if (a.z < 0 && b.z < 0 && c.z < 0) continue;
		
		VERTEXMATRIX::Multiply(zoom, a);
		VERTEXMATRIX::Multiply(zoom, b);
		VERTEXMATRIX::Multiply(zoom, c);
		VERTEXMATRIX::Multiply(offset, a);
		VERTEXMATRIX::Multiply(offset, b);
		VERTEXMATRIX::Multiply(offset, c);
		a.homogenize();
		b.homogenize();
		c.homogenize();
		
		VECTOR normal = FACE::CreateSurfaceNormal(a, b, c);
		//VECTOR normal = this->smoothNormal(face->a, face->b, face->c);
		a.y = height - a.y;
		b.y = height - b.y;
		c.y = height - c.y;
		a.x = width - a.x;
		b.x = width - b.x;
		c.x = width - c.x;

		/*for (int k = 0; k < this->textureChannel.size(); k++)
		{
			Texture* texture = this->textureChannel[k];
			if (texture == NULL) continue;
			int width, height = 0;
			int* video = NULL;
			texture->extract(video, &width, &height);
			if (video == NULL) continue;

			_DrawFace(video, zBuffer, width, height, a, b, c, auv, buv, cuv, normal, video, width, height, this->overlay, this->alpha, onScreen, this);
		}*/
	}
}

void CORE::Mesh::projectUV()
{
	VALUE maxX, maxY, maxZ, minX, minY, minZ = 0.0;
	for (int i = 0; i < this->vertexBuffer.size(); i++)
	{
		VERTEX* v = &this->vertexBuffer[i];
		if (i == 0)
		{
			maxX = v->x;
			maxY = v->y;
			maxZ = v->z;
			minX = v->x;
			minY = v->y;
			minZ = v->z;
		}
		else
		{
			if (v->x > maxX) maxX = v->x;
			if (v->y > maxY) maxY = v->y;
			if (v->z > maxZ) maxZ = v->z;
			if (v->x < minX) minX = v->x;
			if (v->y < minY) minY = v->y;
			if (v->z < minZ) minZ = v->z;
		}
	}

	this->uvChannel.clear();
	for (int k = 0; k < this->indexBuffer.size(); k++)
	{
		FACE* face = &this->indexBuffer[k];
		VERTEX* a = &this->vertexBuffer[face->a];
		VERTEX* b = &this->vertexBuffer[face->b];
		VERTEX* c = &this->vertexBuffer[face->c];
		UVPOINT auv(
			(a->x - minX) / (maxX - minX), 
			(a->z - minZ) / (maxZ - minZ));
		UVPOINT buv(
			(b->x - minX) / (maxX - minX), 
			(b->z - minZ) / (maxZ - minZ));
		UVPOINT cuv(
			(c->x - minX) / (maxX - minX), 
			(c->z - minZ) / (maxZ - minZ));
		face->auv = this->uvChannel.size();
		this->uvChannel.push_back(auv);
		face->buv = this->uvChannel.size();
		this->uvChannel.push_back(buv);
		face->cuv = this->uvChannel.size();
		this->uvChannel.push_back(cuv);
	}
}
void CORE::Mesh::parentTo(Mesh* parent)
{
	this->parent = parent;
	parent->children.push_back(this);
}
CORE::VECTOR CORE::Mesh::smoothNormal(int a, int b, int c)
{
	int num = 0;
	VECTOR smooth(0, 0, 0, 0);

	for (int i = 0; i < this->indexBuffer.size(); i++)
	{
		FACE* face = &this->indexBuffer[i];
		if (face->a == a || face->b == b || face->c == c)
		{
			smooth += FACE::CreateSurfaceNormal(this->vertexBuffer[a], this->vertexBuffer[b], this->vertexBuffer[c]);
			num++;
		}
	}

	smooth /= num;
	smooth.normalize();
	return smooth;
}
bool CORE::Mesh::mouseOver(Mesh** onScreen, int width, int height)
{
	if (onScreen == NULL) return false;
	//if (this == onScreen[(Mouse::y * width) + Mouse::x]) return true;
	return false;
}

int CORE::Mesh::checkForVertex(VALUE x, VALUE y, VALUE z)
{
	if (this->vertexBuffer.size() > 0)
	{
		for (int i = 0; i < this->vertexBuffer.size(); i++)
		{
			VERTEX* vertex = &this->vertexBuffer[i];
			if (x == vertex->x && y == vertex->y && z == vertex->z) return i;
		}
	}
	return -1;
}
int CORE::Mesh::checkForVertex(VERTEX &vertex)
{
	return this->checkForVertex(vertex.x, vertex.y, vertex.z);
}
int CORE::Mesh::checkForNormal(VALUE x, VALUE y, VALUE z)
{
	if (this->vertexBuffer.size() > 0)
	{
		for (int i = 0; i < this->vertexNormalBuffer.size(); i++)
		{
			VERTEX* normal = &this->vertexNormalBuffer[i];
			if (x == normal->x && y == normal->y && z == normal->z) return i;
		}
	}
	return -1;
}
int CORE::Mesh::checkForNormal(VECTOR &vector)
{
	return this->checkForNormal(vector.x, vector.y, vector.z);
}
int CORE::Mesh::checkForUV(VALUE u, VALUE v)
{
	if (this->uvChannel.size() > 0)
	{
		for (int i = 0; i < this->uvChannel.size(); i++)
		{
			UVPOINT* uv = &this->uvChannel[i];
			if (u == uv->u && v == uv->v) return i;
		}
	}
	return -1;
}
int CORE::Mesh::checkForUV(UVPOINT &uv)
{
	return this->checkForUV(uv.u, uv.v);
}

void CORE::Mesh::recalculateNormals()
{
	if (this->indexBuffer.size() > 0)
	{
		for (int k = 0; k < this->indexBuffer.size(); k++)
		{
			FACE* face = &this->indexBuffer[k];
			this->vertexNormalBuffer[face->normalIndex] = FACE::CreateSurfaceNormal(this->vertexBuffer[face->a], this->vertexBuffer[face->b], this->vertexBuffer[face->c]);
		}
	}
}