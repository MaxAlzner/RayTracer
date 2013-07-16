#ifndef __CORE_DATACORE_H_
#define __CORE_DATACORE_H_

namespace GameCore
{
	public ref class DataCore
	{
	public:
		static int focalLength = 0;
		static int cameraPositionX = 0;
		static int cameraPositionY = 0;
		static int cameraPositionZ = 0;
		static int cameraRotationX = 0;
		static int cameraRotationY = 0;
		static int cameraRotationZ = 0;

		static int lightIntensity = 0;
		static int lightPositionX = 0;
		static int lightPositionY = 0;
		static int lightPositionZ = 0;
		static int lightColorR = 0;
		static int lightColorG = 0;
		static int lightColorB = 0;
		
		static bool enable3D = false;
		static int sampleSize = 0;

		static float renderProgress = 1.0;
	};

}

#endif