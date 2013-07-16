#include <stdio.h>
#include <string.h>

#include "..\GameCore.h"

namespace GameCore
{
	int* Resources::UV_Layout_Grid_1024x1024 = NULL;
	int* Resources::BrickWall_512x512;
	int* Resources::Pebbles_1400x1400;
	int* Resources::WoodWall_1024x1024;
	int* Resources::Marble_1024x1024;

	int* Resources::BrickWall_Specular_512x512;
	int* Resources::WoodWall_Specular_1024x1024;

	int* Resources::BrickWall_Normal_512x512;
	int* Resources::WoodWall_Normal_1024x1024;
	int* Resources::Stone_Normal_512x512;
	int* Resources::Krinkle_Normal_428x428;

	void ResourceLoader::_LoadResources()
	{
		_LoadImage(&Resources::UV_Layout_Grid_1024x1024, GameResources::Properties::Resources::Uv_grid_subgrid);
		_LoadImage(&Resources::BrickWall_512x512, GameResources::Properties::Resources::brickwall);
		_LoadImage(&Resources::Pebbles_1400x1400, GameResources::Properties::Resources::pebbles);
		_LoadImage(&Resources::WoodWall_1024x1024, GameResources::Properties::Resources::woodwall);
		_LoadImage(&Resources::Marble_1024x1024, GameResources::Properties::Resources::marble);

		_LoadImage(&Resources::BrickWall_Specular_512x512, GameResources::Properties::Resources::brickwall_specular);
		_LoadImage(&Resources::WoodWall_Specular_1024x1024, GameResources::Properties::Resources::woodwall_specular);

		_LoadImage(&Resources::BrickWall_Normal_512x512, GameResources::Properties::Resources::brickwall_normal);
		_LoadImage(&Resources::WoodWall_Normal_1024x1024, GameResources::Properties::Resources::woodwall_normal);
		_LoadImage(&Resources::Stone_Normal_512x512, GameResources::Properties::Resources::stone_normal);
		_LoadImage(&Resources::Krinkle_Normal_428x428, GameResources::Properties::Resources::krinkle_normal);
	}

	BitmapData^ _GetImageData(Bitmap^ bmp)
	{
		Rectangle^ rect = gcnew Rectangle(0, 0, bmp->Width, bmp->Height);
		BitmapData^ bmpData = bmp->LockBits(
			*rect, ImageLockMode::ReadWrite, PixelFormat::Format32bppArgb
		);
		return bmpData;
	}

	void _LoadImage(int** pDest, IntPtr pSurface, int length)
	{
		int *pSrc = (int*)pSurface.ToPointer();
		*pDest = new int[length];
		memcpy(*pDest, pSrc, length);
	}

	void _LoadImage(int** pDest, Bitmap^ bmp)
	{
        BitmapData^ bmpData = _GetImageData(bmp);
        _LoadImage(pDest, bmpData->Scan0, bmpData->Stride * bmpData->Height);
        bmp->UnlockBits(bmpData);
	}

}