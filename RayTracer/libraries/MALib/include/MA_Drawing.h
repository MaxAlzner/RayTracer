#ifndef _MA_DRAWING_H_
#define _MA_DRAWING_H_
_MALIB_BEGIN

#ifndef _INC_MATH
#include <math.h>
#endif

#define MA_RGBA_WHITE          0xFFFFFFFF
#define MA_RGBA_GRAY_LIGHT     0xCCCCCCFF
#define MA_RGBA_GRAY_MEDIUM    0x888888FF
#define MA_RGBA_GRAY_DARK      0x444444FF
#define MA_RGBA_BLACK          0x000000FF

#define MA_RGBA_PINK           0xFF0088FF
#define MA_RGBA_RED            0xFF0000FF
#define MA_RGBA_ORANGE         0xFF8800FF
#define MA_RGBA_YELLOW         0xFFFF00FF
#define MA_RGBA_YELLOWGREEN    0x88FF00FF
#define MA_RGBA_GREEN          0x00FF00FF
#define MA_RGBA_TURQUIOSE      0x00FF88FF
#define MA_RGBA_CYAN           0x00FFFFFF
#define MA_RGBA_BLUEGREEN      0x0088FFFF
#define MA_RGBA_BLUE           0x0000FFFF
#define MA_RGBA_VIOLET         0x8800FFFF
#define MA_RGBA_MAGENTA        0xFF00FFFF

enum PIXELFORMAT
{
	PIXELFORMAT_NONE         = 0x00000000, 
	PIXELFORMAT_RGB          = 0x00000001, 
	PIXELFORMAT_RGBA         = 0x00000002, 
	PIXELFORMAT_ARGB         = 0x00000004, 
	PIXELFORMAT_BGR          = 0x00000010, 
	PIXELFORMAT_BGRA         = 0x00000020, 
	PIXELFORMAT_ABGR         = 0x00000040, 
};
enum DRAWMODE
{
	DRAWMODE_NORMAL          = 0x00000000, 
	DRAWMODE_ALPHA           = 0x00000001, 
	DRAWMODE_FLIPPEDX        = 0x00000002, 
	DRAWMODE_FLIPPEDY        = 0x00000004, 
};

MALIB_API unsigned int ByteCount(PIXELFORMAT format);
MALIB_API unsigned int PackColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a, PIXELFORMAT format);
MALIB_API void UnpackColor(unsigned int c, unsigned int* r, unsigned int* g, unsigned int* b, unsigned int* a, PIXELFORMAT format);

MALIB_API unsigned int BlendColor(unsigned int dest, unsigned int src, PIXELFORMAT format = PIXELFORMAT_NONE);
MALIB_API void PutPixel(unsigned int* data, unsigned int width, unsigned int height, unsigned int x, unsigned int y, unsigned int color, PIXELFORMAT format);
MALIB_API int GetPixel(unsigned int* data, unsigned int width, unsigned int height, unsigned int x, unsigned int y);
MALIB_API void DrawBitmap(unsigned int* data, unsigned int width, unsigned int height, unsigned int x, unsigned int y, unsigned int* image, unsigned int imageWidth, unsigned int imageHeight, PIXELFORMAT format, DRAWMODE option = DRAWMODE_NORMAL);
MALIB_API void DrawBitmapCell(unsigned int* data, unsigned int width, unsigned int height, unsigned int xDest, unsigned int yDest, unsigned int* image, unsigned int cellColumn, unsigned int cellRow, unsigned int cellWidth, unsigned int cellHeight, unsigned int imageWidth, unsigned int imageHeight, PIXELFORMAT format, DRAWMODE option = DRAWMODE_NORMAL);
MALIB_API void ClearBitmap(unsigned int* data, unsigned int width, unsigned int height, unsigned int color, PIXELFORMAT format);
MALIB_API void DrawCircle(unsigned int* data, unsigned int width, unsigned int height, unsigned int cx, unsigned int cy, unsigned int r, unsigned int color, PIXELFORMAT format);
MALIB_API void DrawBox(unsigned int* data, unsigned int width, unsigned int height, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color, PIXELFORMAT format);
MALIB_API void DrawRectangle(unsigned int* data, unsigned int width, unsigned int height, unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int color, PIXELFORMAT format);
MALIB_API void DrawLine(unsigned int* data, unsigned int width, unsigned int height, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color, PIXELFORMAT format);
MALIB_API void DrawTriangle(unsigned int* data, unsigned int width, unsigned int height, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int x3, unsigned int y3, unsigned int color, PIXELFORMAT format);


_MALIB_END
#endif