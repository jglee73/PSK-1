#include "StdAfx.h"
#include "CMng_Text.h"


#define COLOR_BIT				16

CMng_Text  mMng_Text;


// ...
CMng_Text::CMng_Text()
{
	InitializeCriticalSection(&mCS_Lock);

	// ...
	{
		HDC hdc = GetDC(NULL); 
	
		mSize_X = 100;
		mSize_Y = 50;

		BITMAPINFO bi;
		void *lpBits;

		ZeroMemory(&bi,sizeof(BITMAPINFOHEADER));

		bi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
		bi.bmiHeader.biWidth       = mSize_X;
		bi.bmiHeader.biHeight      = mSize_Y;
		bi.bmiHeader.biPlanes      = 1;
		bi.bmiHeader.biBitCount    = COLOR_BIT;
		bi.bmiHeader.biCompression = BI_RGB;

		hBMP = CreateDIBSection(hdc,(BITMAPINFO *)&bi,DIB_RGB_COLORS,&lpBits,NULL,(DWORD)0);

		hDC  = CreateCompatibleDC(hdc);
		SelectObject(hDC,hBMP);

		ReleaseDC(NULL,hdc);
	}
}
CMng_Text::~CMng_Text()
{

	DeleteCriticalSection(&mCS_Lock);
}

int CMng_Text::DrawText(CString text, HDC hdc,POINT pt,POINT st,POINT et)
{
	EnterCriticalSection(&mCS_Lock);

	// ...
	int limit = strlen(text);

	int w = et.x-st.x;
	int h = et.y-st.y;

	SIZE sz;
	GetTextExtentPoint32(hDC,text,limit,&sz);

	if(w < sz.cx)	
	{
		if(limit > 0)
		{
			int ch_w = sz.cx / limit;
			if(ch_w < 2)	ch_w = 2;

			int len = w / ch_w; 
			if(len < 0)		len = 0;
			
			if(len < limit)	
			{
				text.SetAt(len,0);
			}
		}
	}
	TextOut(hdc,pt.x,pt.y,text,strlen(text));

	LeaveCriticalSection(&mCS_Lock);
	return 1;
}
