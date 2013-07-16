#ifndef __CORE_MESH_H_
#define __CORE_MESH_H_

namespace CORE
{
#define MODE_WORLD 0
#define MODE_LOCAL 1

	class Mesh
	{
	public:
		Mesh();
		~Mesh();

		void translate(VALUE x, VALUE y, VALUE z, int mode = MODE_WORLD);
		void rotate(VALUE x, VALUE y, VALUE z, int mode = MODE_WORLD);
		void transform(VALUE x, VALUE y, VALUE z, int mode = MODE_WORLD);
		void moveOrigin(VALUE x, VALUE y, VALUE z);
		void rotateChildren(VALUE x, VALUE y, VALUE z, int mode = MODE_WORLD);
		void translate(VECTOR &v, int mode = MODE_WORLD);
		void rotate(VECTOR &v, int mode = MODE_WORLD);
		void transform(VECTOR &v, int mode = MODE_WORLD);
		void moveOrigin(VECTOR &v);
		void rotateChildren(VECTOR &v, int mode = MODE_WORLD);

		void freeze();
		void reset();
		void clear();

		int addFace(VALUE ax, VALUE ay, VALUE az, VALUE bx, VALUE by, VALUE bz, VALUE cx, VALUE cy, VALUE cz);
		int addFace(VALUE ax, VALUE ay, VALUE az, VALUE bx, VALUE by, VALUE bz, VALUE cx, VALUE cy, VALUE cz, VALUE au, VALUE av, VALUE bu, VALUE bv, VALUE cu, VALUE cv);
		int addFace(VERTEX &a, VERTEX &b, VERTEX &c);
		int addFace(VERTEX &a, VERTEX &b, VERTEX &c, VALUE au, VALUE av, VALUE bu, VALUE bv, VALUE cu, VALUE cv);
		int addFace(VERTEX &a, VERTEX &b, VERTEX &c, UVPOINT &auv, UVPOINT &buv, UVPOINT &cuv);
		int addVertex(VALUE x, VALUE y, VALUE z);
		int addVertex(VERTEX &vertex);
		int addNormal(VALUE x, VALUE y, VALUE z);
		int addNormal(VECTOR &vector);
		int addUV(VALUE u, VALUE v);
		int addUV(UVPOINT &uv);

		void draw(int* video, float* zBuffer, int width, int height, VECTOR &cameradir, VERTEX &camerapos, Mesh** onScreen = NULL);

		void projectUV();
		void parentTo(Mesh* parent);
		VECTOR smoothNormal(int a, int b, int c);
		bool mouseOver(Mesh** onScreen, int width, int height);
			
		vector<FACE> indexBuffer;
		vector<VERTEX> vertexBuffer;
		vector<VECTOR> vertexNormalBuffer;
		vector<UVPOINT> uvChannel;

		VERTEX origin;
		VECTOR translation, rotation, transformation, childRotation;
		vector<Mesh*> children;
		Mesh* parent;
	private:
		int renderSettings;
		
		int checkForVertex(VALUE x, VALUE y, VALUE z);
		int checkForVertex(VERTEX &vertex);
		int checkForNormal(VALUE x, VALUE y, VALUE z);
		int checkForNormal(VECTOR &vector);
		int checkForUV(VALUE u, VALUE v);
		int checkForUV(UVPOINT &uv);

		void recalculateNormals();
	};
}

#endif