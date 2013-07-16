#ifndef __CORE_FUNCTION_H_
#define __CORE_FUNCTION_H_

namespace CORE
{
	extern float PI;

	int sign(int n);
	int sign(float n);
	int sign(double n);
	int iabs(int n);
	int iabs(float n);
	int iabs(double n);
	int distance(int x1, int y1, int x2, int y2);
	int distance(int x1, int y1, int z1, int x2, int y2, int z2);
	int diceRoll(int sides);
	void swap(int &n1, int &n2);
	void swap(float &n1, float &n2);
	void swap(double &n1, double &n2);
	void clipBounds(int &x, int &y, int boundsWidth, int boundsHeight, int boundsX = 0, int boundsY = 0);
	double toDegrees(double radians);
	double toRadians(double degrees);
	bool insideBounds(int x, int y, int boundsX, int boundsY, int boundsWidth, int boundsHeight);
	float randFloat();
}

#endif