#include <Windows.h>

#include "BitMapObj.h"
#include "tiledefs.h"

BitMapObj::BitMapObj()
{
	hdcMemory = NULL;
	current_new = NULL;
	old = NULL;
	bmHeight = 0;
	bmWidth = 0;
}

BitMapObj::~BitMapObj()
{
	Destroy();
}

void BitMapObj::Load(HDC hdcCompatible, LPCTSTR filename)
{
	Destroy();

	hdcMemory = CreateCompatibleDC(hdcCompatible);
	current_new = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	old = (HBITMAP)SelectObject(hdcMemory,current_new);

	BITMAP bmp;
	GetObject(current_new,sizeof(BITMAP),(LPVOID)&bmp);
	bmHeight = bmp.bmHeight;
	bmWidth = bmp.bmWidth;
}

void BitMapObj::Create(HDC hdcCompatible, int height, int width)
{
	Destroy();

	hdcMemory = CreateCompatibleDC(hdcCompatible);
	current_new = CreateCompatibleBitmap(hdcCompatible, width, height);
	old =  (HBITMAP)SelectObject(hdcMemory, current_new);

	bmHeight = height;
	bmWidth = width;
}

void BitMapObj::Destroy()
{
    if (hdcMemory)
    {
        SelectObject(hdcMemory, old);
        DeleteObject(current_new);
        DeleteDC(hdcMemory);

        hdcMemory = NULL;
        current_new = NULL;
        old = NULL;
        bmHeight = 0;
        bmWidth = 0;
    }
}

int BitMapObj::getHeight()
{
	return bmHeight;
}

int BitMapObj::getWidth()
{
	return bmWidth;
}

BitMapObj::operator HDC()
{
	return(hdcMemory);
}
