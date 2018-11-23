#ifndef PB_BMO_H_
#define PB_BMO_H_

#pragma once
#include<Windows.h>

class BitMapObj
{
private:
	HDC hdcMemory;
	HBITMAP current_new;
	HBITMAP old;
	int bmHeight;
	int bmWidth;

public:
	BitMapObj();
	~BitMapObj();
	void Load(HDC hdcCompatible, LPCTSTR filename);
	void Create(HDC hdcCompatible, int height, int width);
	void Destroy();
	int getHeight();
	int getWidth();

	operator HDC();
};

#endif