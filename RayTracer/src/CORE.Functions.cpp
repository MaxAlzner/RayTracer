#include "..\GameCore.h"

namespace CORE
{
	float PI = 3.141592653;

	int sign(int n)
	{
		if (n < 0) return -1;
		return 1;
	}
	int sign(float n)
	{
		return sign(int(n));
	}
	int sign(double n)
	{
		return sign(int(n));
	}
	int iabs(int n)
	{
		if (n < 0) n *= -1;
		return n;
	}
	int iabs(float n)
	{
		return iabs(int(n));
	}
	int iabs(double n)
	{
		return iabs(int(n));
	}
	int distance(int x1, int y1, int x2, int y2)
	{
		return ((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1));
	}
	int distance(int x1, int y1, int z1, int x2, int y2, int z2)
	{
		return ((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)) * ((z2 - z1) * (z2 - z1));
	}
	int diceRoll(int sides)
	{
		return (rand()%sides) + 1;
	}
	void swap(int &n1, int &n2)
	{
		int tmp = n1;
		n1 = n2;
		n2 = tmp;
	}
	void swap(float &n1, float &n2)
	{
		float tmp = n1;
		n1 = n2;
		n2 = tmp;
	}
	void swap(double &n1, double &n2)
	{
		double tmp = n1;
		n1 = n2;
		n2 = tmp;
	}
	void clipBounds(int &x, int &y, int boundsWidth, int boundsHeight, int boundsX, int boundsY)
	{
		if (x < boundsX) x = boundsX;
		else if (x > boundsWidth + boundsX) x = boundsWidth + boundsX;
		if (y < boundsY) y = boundsY;
		else if (y > boundsHeight + boundsY) y = boundsHeight + boundsY;
	}
	double toDegrees(double radians)
	{
		return radians * (180 / PI);
	}
	double toRadians(double degrees)
	{
		return degrees * (PI / 180);
	}
	bool insideBounds(int x, int y, int boundsX, int boundsY, int boundsWidth, int boundsHeight)
	{
		return x >= boundsX && x <= boundsWidth + boundsX && y >= boundsY && y <= boundsHeight + boundsY;
	}
	float randFloat()
	{
		return float(rand()%1000) / 1000.0;
	}
}