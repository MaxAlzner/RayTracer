#include "../GameCore.h"

CORE::AnaglyphCamera::AnaglyphCamera()
{
}
CORE::AnaglyphCamera::~AnaglyphCamera()
{
}

void CORE::AnaglyphCamera::castRays(int* photo, int width, int height, COLOR &leftEye, COLOR &rightEye, VALUE eyeBridge)
{
	eyeBridge /= 2;
	VERTEX leftp1, leftp2, leftp3, leftp4;
	this->calcViewPort(width, height, this->position + VECTOR(-eyeBridge, 0, 0, 0), this->direction, 
		&leftp1, &leftp2, &leftp3, &leftp4);
	VECTOR leftpx = VECTOR::CreateVector(leftp1, leftp2);
	VECTOR leftpy = VECTOR::CreateVector(leftp1, leftp3);
	
	VERTEX rightp1, rightp2, rightp3, rightp4;
	this->calcViewPort(width, height, this->position + VECTOR(eyeBridge, 0, 0, 0), this->direction, 
		&rightp1, &rightp2, &rightp3, &rightp4);
	VECTOR rightpx = VECTOR::CreateVector(rightp1, rightp2);
	VECTOR rightpy = VECTOR::CreateVector(rightp1, rightp3);

	VECTOR normal = FACE::CreateSurfaceNormal(leftp2, leftp1, leftp3);
	VERTEX leftFocalPoint = leftp1 + (leftpx * 0.5) + (leftpy * 0.5) + ((normal * -1) * this->focalLength);
	VERTEX rightFocalPoint = rightp1 + (rightpx * 0.5) + (rightpy * 0.5) + ((normal * -1) * this->focalLength);
	
	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			GameCore::DataCore::renderProgress = float(k + (i * width)) / float(width * height);

			VERTEX leftRayPosition0 = leftp1 + 
				(leftpx * (VALUE(k) / VALUE(width))) + 
				(leftpy * (VALUE(i) / VALUE(height)));
			VERTEX rightRayPosition0 = rightp1 + 
				(rightpx * (VALUE(k) / VALUE(width))) + 
				(rightpy * (VALUE(i) / VALUE(height)));
			VERTEX leftRayPosition1 = leftp1 + 
				(leftpx * (VALUE(k + 1) / VALUE(width))) + 
				(leftpy * (VALUE(i + 1) / VALUE(height)));
			VERTEX rightRayPosition1 = rightp1 + 
				(rightpx * (VALUE(k + 1) / VALUE(width))) + 
				(rightpy * (VALUE(i + 1) / VALUE(height)));
			VECTOR leftRayDirection = VECTOR::CreateVector(leftFocalPoint, leftRayPosition0);
			VECTOR rightRayDirection = VECTOR::CreateVector(rightFocalPoint, rightRayPosition0);
			leftRayDirection.normalize();
			rightRayDirection.normalize();

			COLOR leftcolor(0), rightcolor(0);
			RAYHIT lefthit, righthit;
			
			this->sampleCastRays(&leftcolor, 
				leftRayDirection, 
				leftRayPosition0, 
				leftRayPosition1, 
				this->sampleSize);
			this->sampleCastRays(&rightcolor, 
				rightRayDirection, 
				rightRayPosition0, 
				rightRayPosition1, 
				this->sampleSize);

			leftcolor.gray();
			rightcolor.gray();
			leftcolor *= leftEye;
			rightcolor *= rightEye;
			COLOR color = leftcolor + rightcolor;
			
			if (color.a > 0) Drawing::PutPixel(photo, width, height, k, i, color.toInt());
		}
	}
}