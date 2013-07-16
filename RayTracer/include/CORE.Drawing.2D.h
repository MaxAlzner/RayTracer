#ifndef __CORE_DRAWING_2D_
#define __CORE_DRAWING_2D_

namespace CORE
{
#define OPTION_NORMAL 0
#define OPTION_ALPHA 1
#define OPTION_FLIPPED 2

	class Drawing
	{
	public:
		static float* CreateZBuffer(int width, int height);
		static void ClearZBuffer(float* zBuffer, int width, int height);
		static void DestroyZBuffer(float* zBuffer);

		static Mesh** CreateOnScreen(int width, int height);
		static void ClearOnScreen(Mesh** onScreen, int width, int height);
		static void DestroyOnScreen(Mesh** onScreen);

		static void PutPixel(int *video, int width, int height, int x, int y, int color);
		static int GetPixel(int* video, int width, int height, int x, int y);
		static void DrawBitmap(int *video, int width, int height, int x1, int y1, int *image, int nImageWidth, int nImageHeight, int option = OPTION_NORMAL);
		static void DrawBitmapCell(int *video, int width, int height, int xDest, int yDest, int *image, int nCellColumn, int nCellRow, int nCellWidth, int nCellHeight, int nImageWidth, int nImageHeight, int option = OPTION_NORMAL);
		static void ClearBitmap(int *video, int width, int height, int color);
		static void DrawCircle(int *video, int width, int height, int cx, int cy, int r, int color);
		static void DrawBox(int* video, int width, int height, int x1, int y1, int x2, int y2, int color);
		static void DrawRectangle(int* video, int width, int height, int x, int y, int w, int h, int color);
		static void DrawLine(int* video, int width, int height, int x1, int y1, int x2, int y2, int color);
		static void DrawTriangle(int* video, int width, int height, int x1, int y1, int x2, int y2, int x3, int y3, int color);
		static void DrawFace(int* video, float* zBuffer, int width, int height, VERTEX &v1, VERTEX &v2, VERTEX &v3, VECTOR &normal, COLOR &c1, COLOR &c2, COLOR &c3);
		static void DrawFace(int* video, float* zBuffer, int width, int height, 
			VERTEX &v1, VERTEX &v2, VERTEX &v3, 
			UVPOINT &uv1, UVPOINT &uv2, UVPOINT &uv3, 
			VECTOR &normal, int* texture, int textureWidth, int textureHeight, 
			COLOR overlay = COLOR(0), VALUE transparency = 1.0, 
			Mesh** onScreen = NULL, Mesh* thisMesh = NULL);
	};
}

#endif