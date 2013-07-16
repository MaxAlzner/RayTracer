#include "../GameCore.h"

int CORE::RGB::CreateARGB(int a, int r, int g, int b)
{
	int c = (a << 24) + (r << 16) + (g << 8) + (b);
	return c;
}
int CORE::RGB::CreateRGB(int r, int g, int b)
{
	if (r < 0) r = 0;
	else if (r > 255) r = 255;
	if (g < 0) g = 0;
	else if (g > 255) g = 255;
	if (b < 0) b = 0;
	else if (b > 255) b = 255;
	return CreateARGB(255, r, g, b);
}
void CORE::RGB::ExtractColor(unsigned int pixel, unsigned int &a, unsigned int &r, unsigned int &g, unsigned int &b) {
	a = pixel >> 24;
	r = (pixel << 8) >> 24;
	g = (pixel << 16) >> 24;
	b = (pixel << 24) >> 24;
}
int CORE::RGB::BlendColor(int dest, int src)
{
	unsigned int a1, r1, g1, b1;
	ExtractColor((unsigned int)src, a1, r1, g1, b1);

	unsigned int a2, r2, g2, b2;
	ExtractColor((unsigned int)dest, a2, r2, g2, b2);

	unsigned int a3, r3, g3, b3;
	a3 = a1;
	float pixel_alpha = (float)a3 / 255.0;
			
	r3 = r2 + (unsigned int)(pixel_alpha * ((int)r1 - (int)r2));
	g3 = g2 + (unsigned int)(pixel_alpha * ((int)g1 - (int)g2));
	b3 = b2 + (unsigned int)(pixel_alpha * ((int)b1 - (int)b2));

	return CreateARGB(a2, r3, g3, b3);
}
bool CORE::RGB::IsColorKey(unsigned int color, unsigned int colorKey)
{
	color = color | 0xFF000000;
	colorKey = colorKey | 0xFF000000;

	if(color == colorKey) return true;
	return false;
}
int CORE::RGB::GetAlpha(unsigned int color)
{
	if (color <= 0) return 0;
	else if (color > 0xFFFFFFFF) return 0xFF;
	return color >> 24;
}
int CORE::RGB::GetRed(unsigned int color)
{
	if (color <= 0) return 0;
	else if (color > 0xFFFFFFFF) return 0xFF;
	return (color << 8) >> 24;
}
int CORE::RGB::GetGreen(unsigned int color)
{
	if (color <= 0) return 0;
	else if (color > 0xFFFFFFFF) return 0xFF;
	return (color << 16) >> 24;
}
int CORE::RGB::GetBlue(unsigned int color)
{
	if (color <= 0) return 0;
	else if (color > 0xFFFFFFFF) return 0xFF;
	return (color << 24) >> 24;
}		
int CORE::RGB::ModAlpha(int color, int n)
{
	int alpha = GetAlpha(color) + n;
	if (alpha < 0x00) n = 0x00;
	if (alpha > 0xFF) n = 0xFF;
	return CreateARGB(alpha, GetRed(color), GetGreen(color), GetBlue(color));
}
int CORE::RGB::ModRed(int color, int n)
{
	int red  = GetRed(color) + n;
	if (red < 0x00) red = 0x00;
	if (red > 0xFF) red = 0xFF;
	return CreateARGB(GetAlpha(color), red, GetGreen(color), GetBlue(color));
}
int CORE::RGB::ModGreen(int color, int n)
{
	int green = GetGreen(color) + n;
	if (green < 0x00) green = 0x00;
	if (green > 0xFF) green = 0xFF;
	return CreateARGB(GetAlpha(color), GetRed(color), green, GetBlue(color));
}
int CORE::RGB::ModBlue(int color, int n)
{
	int blue = GetBlue(color) + n;
	if (blue < 0x00) blue = 0x00;
	if (blue > 0xFF) blue = 0xFF;
	return CreateARGB(GetAlpha(color), GetRed(color), GetGreen(color), blue);
}
int CORE::RGB::SetAlpha(int color, int n)
{
	if (n < 0x00) n = 0x00;
	if (n > 0xFF) n = 0xFF;
	return CreateARGB(n, GetRed(color), GetGreen(color), GetBlue(color));
}
int CORE::RGB::SetRed(int color, int n)
{
	if (n < 0x00) n = 0x00;
	if (n > 0xFF) n = 0xFF;
	return CreateARGB(GetAlpha(color), n, GetGreen(color), GetBlue(color));
}
int CORE::RGB::SetGreen(int color, int n)
{
	if (n < 0x00) n = 0x00;
	if (n > 0xFF) n = 0xFF;
	return CreateARGB(GetAlpha(color), GetRed(color), n, GetBlue(color));
}
int CORE::RGB::SetBlue(int color, int n)
{
	if (n < 0x00) n = 0x00;
	if (n > 0xFF) n = 0xFF;
	return CreateARGB(GetAlpha(color), GetRed(color), GetGreen(color), n);
}