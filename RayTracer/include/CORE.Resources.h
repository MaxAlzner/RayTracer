#ifndef __CORE_RESOURCES_H_
#define __CORE_RESOURCES_H_

#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::Windows::Forms;

namespace GameCore
{
	public class Resources
	{
	public:
		static int* UV_Layout_Grid_1024x1024;
		static int* BrickWall_512x512;
		static int* Pebbles_1400x1400;
		static int* WoodWall_1024x1024;
		static int* Marble_1024x1024;

		static int* BrickWall_Specular_512x512;
		static int* WoodWall_Specular_1024x1024;

		static int* BrickWall_Normal_512x512;
		static int* WoodWall_Normal_1024x1024;
		static int* Stone_Normal_512x512;
		static int* Krinkle_Normal_428x428;
	};

	public ref class ResourceLoader
	{
	public:
		static void _LoadResources();
	};

	BitmapData^ _GetImageData(Bitmap^ bmp);
	void _LoadImage(int** pDest, IntPtr pSurface, int length);
	void _LoadImage(int** pDest, Bitmap^ bmp);
}

#endif