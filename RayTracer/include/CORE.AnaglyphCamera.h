#ifndef __CORE_ANAGLYPHCAMERA_H_
#define __CORE_ANAGLYPHCAMERA_H_

namespace CORE
{
	class AnaglyphCamera : public CORE::Camera
	{
	public:
		AnaglyphCamera();
		~AnaglyphCamera();

		void castRays(int* photo, int width, int height, COLOR &leftEye, COLOR &rightEye, VALUE eyeBridge);
	};
}

#endif