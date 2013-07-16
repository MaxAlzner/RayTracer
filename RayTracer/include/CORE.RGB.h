#ifndef __CORE_RGB_H_
#define __CORE_RGB_H_

namespace CORE
{
#define RGB_WHITE 0xFFFFFFFF
#define RGB_GRAY_LIGHT 0xFFCCCCCC
#define RGB_GRAY_MEDIUM 0xFF888888
#define RGB_GRAY_DARK 0xFF444444
#define RGB_BLACK 0xFF000000

#define RGB_PINK 0xFFFF0088
#define RGB_RED 0xFFFF0000
#define RGB_ORANGE 0xFFFF8800
#define RGB_YELLOW 0xFFFFFF00
#define RGB_YELLOWGREEN 0xFF88FF00
#define RGB_GREEN 0xFF00FF00
#define RGB_TURQUIOSE 0xFF00FF88
#define RGB_CYAN 0xFF00FFFF
#define RGB_BLUEGREEN 0xFF0088FF
#define RGB_BLUE 0xFF0000FF
#define RGB_VIOLET 0xFF8800FF
#define RGB_MAGENTA 0xFFFF00FF

	class RGB
	{
	public:
		static int CreateARGB(int a, int r, int g, int b);
		static int CreateRGB(int r, int g, int b);
		static void ExtractColor(unsigned int pixel, unsigned int &a, unsigned int &r, unsigned int &g, unsigned int &b);
		static int BlendColor(int dest, int src);
		static bool IsColorKey(unsigned int color, unsigned int colorKey);
		static int GetAlpha(unsigned int color);
		static int GetRed(unsigned int color);
		static int GetGreen(unsigned int color);
		static int GetBlue(unsigned int color);
		static int ModAlpha(int color, int n);
		static int ModRed(int color, int n);
		static int ModGreen(int color, int n);
		static int ModBlue(int color, int n);
		static int SetAlpha(int color, int n);
		static int SetRed(int color, int n);
		static int SetGreen(int color, int n);
		static int SetBlue(int color, int n);
	};
}

#endif