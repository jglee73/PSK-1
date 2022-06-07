#pragma once


class CMng_Text
{
private:
	HBITMAP  hBMP;

	int mSize_X;
	int mSize_Y;

	CRITICAL_SECTION mCS_Lock;

public:
	CMng_Text();
	~CMng_Text();

	// ...
	HDC	hDC;

	int DrawText(CString text, HDC hdc,POINT pt,POINT st,POINT et);
};
