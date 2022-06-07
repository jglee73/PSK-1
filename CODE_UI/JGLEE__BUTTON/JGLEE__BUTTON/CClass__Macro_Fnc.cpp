#include "StdAfx.h"

#include "CClass__Macro_Fnc.h"
CClass__Macro_Fnc mMacro_Fnc;

#include "CMng_Text.h"
extern CMng_Text  mMng_Text;


// ...
CClass__Macro_Fnc::CClass__Macro_Fnc()
{
	InitializeCriticalSection(&mCS_Lock);

	mColor_Black = RGB(0,0,0);
}

CClass__Macro_Fnc::~CClass__Macro_Fnc()
{

	DeleteCriticalSection(&mCS_Lock);
}


COLORREF CClass__Macro_Fnc::GetColor(CString string)
{
	int r, g, b;

	return GetColor(string,&r,&g,&b);
}

COLORREF CClass__Macro_Fnc::GetColor(CString string,int *r,int *g,int *b)
{
	EnterCriticalSection(&mCS_Lock);

	COLORREF color = RGB(255,255,255);
	*r = 255;
	*g = 255;
	*b = 255;

	int	 count, para;
	char ch, word[300];
	CString  word1, word2, word3, word4;

	count = 0;
	para  = 0;
	
	int limit = string.GetLength();
	for(int i=0;i<=limit;i++)
	{
		if(i != limit)	ch = string.GetAt(i);
		else			ch = '\0';

		if((ch == ' ')||(ch == ',')||(ch == '(')||(ch == ')')||(ch == '\0'))
		{
			if(count > 0)
			{
				count = 0;
				para++;

					 if(para == 1)		word1 = word;
				else if(para == 2)		word2 = word;
				else if(para == 3)		word3 = word;
				else if(para == 4)		word4 = word;
			}
		}
		else
		{
			word[count++] = ch;
			word[count]   = '\0';
		}
	}

	if(word1.CompareNoCase("RGB") == 0)	
	{
		*r = atoi(word2);
		*g = atoi(word3);
		*b = atoi(word4); 

		color = RGB(atoi(word2),atoi(word3),atoi(word4)); 
	}
	else
	{
		*r = atoi(word1);
		*g = atoi(word2);
		*b = atoi(word3); 

		color = RGB(atoi(word1),atoi(word2),atoi(word3)); 
	}

	LeaveCriticalSection(&mCS_Lock);
	return color;
}

void CClass__Macro_Fnc::Copy(HDC hdc,POINT t_st,POINT t_et,HDC hdc_back,POINT s_st,POINT s_et)
{
	EnterCriticalSection(&mCS_Lock);

	int t_width  = t_et.x - t_st.x;
	int t_height = t_et.y - t_st.y;
	
	int s_width  = s_et.x - s_st.x;
	int s_height = s_et.y - s_st.y;

	StretchBlt(hdc,  	
			   t_st.x,t_st.y,t_width,t_height,
			   hdc_back,
			   s_st.x,s_st.y,s_width,s_height,
			   SRCCOPY);

	LeaveCriticalSection(&mCS_Lock);
}

void CClass__Macro_Fnc::Copy(HDC hdc,HDC hdc_back,POINT st,POINT et)
{
	EnterCriticalSection(&mCS_Lock);

	int width  = et.x - st.x;
	int height = et.y - st.y;

	StretchBlt(hdc,  	  
			   st.x,st.y,width,height,
			   hdc_back,  
			   st.x,st.y,width,height,
			   SRCCOPY);

	LeaveCriticalSection(&mCS_Lock);
}

void CClass__Macro_Fnc::Get_TextPoint(HDC hdc,POINT st,POINT et,POINT *pt)
{
	EnterCriticalSection(&mCS_Lock);

	TEXTMETRIC  tm;
	GetTextMetrics(hdc,&tm);

	pt->x = (st.x + et.x)/2;
	// pt->y = (st.y + et.y)/2 + tm.tmHeight/2;
	// pt->y = (st.y + et.y)/2 + tm.tmHeight * (2.0 / 3.0);
	// pt->y = (st.y + et.y) / 2.0 - tm.tmHeight / 2;
	pt->y = (st.y + et.y) / 2.0  + tm.tmHeight / 3;
	
	LeaveCriticalSection(&mCS_Lock);
}

HFONT CClass__Macro_Fnc::MakeFont(HDC hdc,int width,int height,HFONT *hfont)
{
	EnterCriticalSection(&mCS_Lock);

	*hfont = CreateFont(height,
						width,
						0,
						0,
						FW_NORMAL,
						0,
						0,
						0,
						ANSI_CHARSET,
						OUT_DEFAULT_PRECIS,
						CLIP_DEFAULT_PRECIS,
						DEFAULT_QUALITY,
						DEFAULT_PITCH | FF_DONTCARE,
						NULL);   //  "Century Gothic");  "Courier New");

	HFONT font = (HFONT) SelectObject(hdc, *hfont);

	LeaveCriticalSection(&mCS_Lock);

	if(*hfont == NULL)
	{
		MessageBox(NULL,"FONT : NULL","CClass__Macro_Fnc::MakeFont",MB_OK|MB_TOPMOST);
	}
	return font;
}

void CClass__Macro_Fnc::DeleteFont(HDC hdc,HFONT old_hfont,HFONT new_hfont)
{
	EnterCriticalSection(&mCS_Lock);

	SelectObject(hdc,old_hfont);
	
	if(new_hfont != NULL)
		DeleteObject(new_hfont);

	LeaveCriticalSection(&mCS_Lock);
}

HBRUSH CClass__Macro_Fnc::MakeBrush(HDC hdc,HBRUSH *hbrush,COLORREF color)
{
	EnterCriticalSection(&mCS_Lock);

	*hbrush = CreateSolidBrush(color);
	if(*hbrush == NULL)
	{
		MessageBox(NULL,"BRUSH : NULL","CClass__Macro_Fnc::MakeBrush",MB_OK|MB_TOPMOST);
	}

	HBRUSH brush = (HBRUSH) SelectObject(hdc,*hbrush);

	LeaveCriticalSection(&mCS_Lock);
	return brush;
}

void CClass__Macro_Fnc::DeleteBrush(HDC hdc,HBRUSH hbrush,HBRUSH old_brush)
{ 	
	EnterCriticalSection(&mCS_Lock);

	if(hbrush != NULL)		DeleteObject(hbrush);

	SelectObject(hdc,old_brush);

	LeaveCriticalSection(&mCS_Lock);
}

int CClass__Macro_Fnc::GetWaferColor(CString status,COLORREF *color)
{
	EnterCriticalSection(&mCS_Lock);

	if(status.CompareNoCase("EXIST") == 0)
	{
		 *color = RGB(255,255,255);
	}
	else if(status.CompareNoCase("MAPPED") == 0)
	{
		*color = RGB(0,100,200);
	}
	else if(status.CompareNoCase("PROCING") == 0)
	{
		*color = RGB(50,100,0);
	}
	else if(status.CompareNoCase("PROCESSED") == 0)
	{
		*color = RGB(100,200,0);
	}
	else if(status.CompareNoCase("ABORTED") == 0)
	{
		*color = RGB(180,50,0);
	}
	else
	{
		// "UNKNOWN"
		*color = RGB(200,200,60);
	}

	LeaveCriticalSection(&mCS_Lock);
	return 1;
}

void CClass__Macro_Fnc::Draw_Line(HDC hdc,POINT st,POINT et,COLORREF color)
{
	EnterCriticalSection(&mCS_Lock);
	
	int width  = et.x - st.x;
	int height = et.y - st.y;
	
	if(width  == 0)		width  = 1;
	if(height == 0)		height = 1;
	
	SetPixel(hdc,st.x,st.y,color);	

	StretchBlt(hdc,
			   st.x,st.y, width,height,
			   hdc,
			   st.x,st.y, 1,1,
			   SRCCOPY);	

	LeaveCriticalSection(&mCS_Lock);
}

void CClass__Macro_Fnc::Draw_Ellipse(HDC hdc,POINT st,POINT et,COLORREF color)
{
	EnterCriticalSection(&mCS_Lock);
	
	HBRUSH hBrush;
	HBRUSH hOld_Brush;
	
	hBrush = CreateSolidBrush(color);
	hOld_Brush = (HBRUSH) SelectObject(hdc,hBrush);
	Ellipse(hdc,st.x,st.y,et.x,et.y);

	if(hBrush != NULL)	DeleteObject(hBrush);
	SelectObject(hdc,hOld_Brush);
	
	LeaveCriticalSection(&mCS_Lock);
}

void CClass__Macro_Fnc::Draw_Polygon(HDC hdc,POINT *ppt,int pt_limit,COLORREF color)
{
	EnterCriticalSection(&mCS_Lock);
	
	HPEN   hPen, hOld_Pen;
	HBRUSH hBrush;
	HBRUSH hOld_Brush;

	hBrush = CreateSolidBrush(color);

	POINT  lpt;
	LOGPEN LP;
	
	lpt.x = 1;
	LP.lopnStyle = PS_SOLID;
	LP.lopnWidth = lpt;
	LP.lopnColor = color;
	
	hPen = CreatePenIndirect(&LP);
	if(hPen == NULL)
	{
		MessageBox(NULL,"Pen : NULL","CClass__Macro_Fnc::Draw_Polygon",MB_OK|MB_TOPMOST);
	}

	hOld_Pen = (HPEN) SelectObject(hdc,hPen);
	hOld_Brush = (HBRUSH) SelectObject(hdc,hBrush);
	SelectObject(hdc,hPen);
	SelectObject(hdc,hBrush);
	
	Polygon(hdc,ppt,pt_limit);

	SelectObject(hdc,hOld_Pen);
	SelectObject(hdc,hOld_Brush);

	if(hPen   != NULL)	DeleteObject(hPen);
	if(hBrush != NULL)	DeleteObject(hBrush);

	LeaveCriticalSection(&mCS_Lock);
}

void CClass__Macro_Fnc::Draw_Rectangle(HDC hdc,POINT st,POINT et,int width)
{
	Draw_Rectangle(hdc,st,et,width,RGB(255,255,255),RGB(0,0,0));
}

void CClass__Macro_Fnc::Draw_Rectangle_Pressed(HDC hdc,POINT st,POINT et,int width)
{
	Draw_Rectangle(hdc,st,et,width,RGB(0,0,0),RGB(255,255,255));
}

void CClass__Macro_Fnc::
Draw_Rectangle(HDC hdc,
			   POINT st,POINT et,int width,
			   COLORREF up_color,
			   COLORREF down_color)
{
	EnterCriticalSection(&mCS_Lock);
	
	COLORREF line_color;
	POINT    d_st, d_et;
	int      i;

	et.x -= 1;		et.y -= 1;
	
	line_color = up_color;
	for(i=0;i < width;i++)
	{
		d_st.x = st.x + i;
		d_st.y = st.y + i;
		d_et.x = st.x + i;
		d_et.y = et.y - i;
		Draw_Line(hdc,d_st,d_et,line_color);
	}
	for(i=0;i < width;i++)
	{
		d_st.x = st.x + i;
		d_st.y = st.y + i;
		d_et.x = et.x - i;
		d_et.y = st.y + i;
		Draw_Line(hdc,d_st,d_et,line_color);
	}

	line_color = down_color;
	for(i=0;i < width;i++)
	{
		d_st.x = et.x - i;
		d_st.y = st.y + i;
		d_et.x = et.x - i;
		d_et.y = et.y - i;
		Draw_Line(hdc,d_st,d_et,line_color);
	}
	for(i=0;i < width;i++)
	{
		d_st.x = st.x + i;
		d_st.y = et.y - i;
		d_et.x = et.x - i;
		d_et.y = et.y - i;
		Draw_Line(hdc,d_st,d_et,line_color);
	}

	for(i=0;i<width;i++)
	{
		d_st.x = et.x-i;
		d_st.y = et.y-i;
		d_et.x = et.x+1;
		d_et.y = et.y-i;
		Draw_Line(hdc,d_st,d_et,line_color);
	}

	LeaveCriticalSection(&mCS_Lock);
}

void CClass__Macro_Fnc::
Fill_Rectangle(HDC hdc,POINT st,POINT et,COLORREF b_color)
{
	EnterCriticalSection(&mCS_Lock);
	
	HBRUSH		brush, old_brush;
	HPEN        hpen,  hold_pen;
	LOGBRUSH	logbrush;

	hpen = CreatePen(PS_SOLID,1,mColor_Black);

	logbrush.lbStyle = BS_SOLID;
	logbrush.lbColor = b_color;
	logbrush.lbHatch = 0;
	brush = CreateBrushIndirect(&logbrush);
	if(brush == NULL)
	{
		MessageBox(NULL,"Brush : NULL","CClass__Macro_Fnc:Fill_Rectangle",MB_OK|MB_TOPMOST);
	}

	hold_pen  = (HPEN)   SelectObject(hdc,hpen);
	old_brush = (HBRUSH) SelectObject(hdc,brush);

	Rectangle(hdc,st.x,st.y,et.x,et.y);

	SelectObject(hdc,hold_pen);
	SelectObject(hdc,old_brush);

	if(hpen  != NULL)	DeleteObject(hpen);
	if(brush != NULL)	DeleteObject(brush);

	LeaveCriticalSection(&mCS_Lock);
}

void CClass__Macro_Fnc::Draw_Text(HDC hdc,
							 CString title,
							 POINT t_pt,
							 int width,
							 int height,
							 COLORREF color,
							 CString mode)
{
	Draw_Text(hdc,title,t_pt,width,height,FW_NORMAL,color,mode,"Fixedsys");
}
void CClass__Macro_Fnc::Draw_Text(HDC hdc,
							 CString title,
							 POINT t_pt,
							 int width,
							 int height,
							 int weight,
							 COLORREF color,
							 CString mode,
							 CString font_name)
{
	EnterCriticalSection(&mCS_Lock);

	HFONT hfont = CreateFont(height,
							   width,
							   0,
							   0,
							   weight,
							   0,
							   0,
							   0,
							   ANSI_CHARSET,
							   OUT_DEFAULT_PRECIS,
							   CLIP_DEFAULT_PRECIS,
							   DEFAULT_QUALITY,
							   DEFAULT_PITCH | FF_DONTCARE,
							   font_name);    
	
	if(hfont == NULL)
	{
		MessageBox(NULL,"Font : NULL","CClass__Macro_Fnc::Draw_Text",MB_OK|MB_TOPMOST);
	}
	HFONT old_hfont = (HFONT) SelectObject(hdc, hfont);

	SetTextColor(hdc,color);
	SetBkMode(hdc,TRANSPARENT);
	
		 if(mode.CompareNoCase("LEFT")  == 0)					SetTextAlign(hdc, TA_LEFT|VTA_BASELINE);
	else if(mode.CompareNoCase("RIGHT") == 0)					SetTextAlign(hdc, TA_RIGHT|VTA_BASELINE);
	else														SetTextAlign(hdc, TA_CENTER|VTA_BASELINE);

	TextOut(hdc,t_pt.x,t_pt.y,title,strlen(title));

	SelectObject(hdc,old_hfont);
	if(hfont != NULL)	DeleteObject(hfont);

	LeaveCriticalSection(&mCS_Lock);	
}

void CClass__Macro_Fnc::
Draw_Text(HDC hdc,
		  CString title,
		  POINT t_pt,
		  int width,
		  int height,
		  COLORREF color)
{
	EnterCriticalSection(&mCS_Lock);
	
	HFONT hfont = CreateFont(height,
							   width,
							   0,
							   0,
							   FW_NORMAL,
							   0,
							   0,
							   0,
							   ANSI_CHARSET,
							   OUT_DEFAULT_PRECIS,
							   CLIP_DEFAULT_PRECIS,
							   DEFAULT_QUALITY,
							   //FIXED_PITCH | FF_SWISS,  //FF_DONTCARE,
							   DEFAULT_PITCH | FF_DONTCARE,
							   NULL);   //  "Century Gothic");  "Courier New");

	if(hfont == NULL)
	{
		MessageBox(NULL,"Font : NULL","CClass__Macro_Fnc:Draw_Text",MB_OK|MB_TOPMOST);
	}
	HFONT old_hfont = (HFONT) SelectObject(hdc, hfont);

	SetTextColor(hdc,color);
	SetBkMode(hdc,TRANSPARENT);
	SetTextAlign(hdc,TA_CENTER|VTA_BASELINE);

	TextOut(hdc,t_pt.x,t_pt.y,title,strlen(title));

	SelectObject(hdc,old_hfont);
	if(hfont != NULL)	DeleteObject(hfont);

	LeaveCriticalSection(&mCS_Lock);
}

void CClass__Macro_Fnc::
Draw_Text(HDC hdc,
		  CString title,
		  POINT st,POINT et,POINT t_pt,
		  COLORREF t_color,COLORREF b_color,
		  int tr_color,int tg_color,int tb_color,
		  int br_color,int bg_color,int bb_color,
		  LOGFONT fontlog,int fonttype)
{
	Draw_Text(hdc, 
		      title, 
			  st,et, t_pt,t_color,b_color, 
			  "", 
			  tr_color,tg_color,tb_color,
			  br_color,bg_color,bb_color,
			  0,0,0,
			  fontlog,fonttype);
}
void CClass__Macro_Fnc::
Draw_Text(HDC hdc,
		  CString title,
		  POINT st,POINT et,POINT t_pt,
		  COLORREF t_color,COLORREF b_color,
		  CString mode,
		  int tr_color,int tg_color,int tb_color,
		  int br_color,int bg_color,int bb_color,
		  int gr_color,int gg_color,int gb_color,
		  LOGFONT fontlog,int fonttype)
{
	EnterCriticalSection(&mCS_Lock);
	
	HBRUSH	 brush, old_brush;
	LOGBRUSH logbrush;

	logbrush.lbStyle = BS_SOLID;
	logbrush.lbColor = b_color;
	logbrush.lbHatch = 0;

	brush = CreateBrushIndirect(&logbrush);
	if(brush == NULL)
	{
		MessageBox(NULL,"Brush : NULL","CClass__Macro_Fnc:Draw_Text",MB_OK|MB_TOPMOST);
	}
	old_brush = (HBRUSH) SelectObject(hdc,brush);

	SetTextColor(hdc,t_color);
	SetBkMode(hdc,TRANSPARENT);
	SetTextAlign(hdc,TA_CENTER|VTA_BASELINE);

	HFONT n_font = CreateFontIndirect(&fontlog);
	if(n_font == NULL)
	{
		MessageBox(NULL,"Font : NULL","CClass__Macro_Fnc::Draw_Text",MB_OK|MB_TOPMOST);
	}
	HFONT o_font = (HFONT) SelectObject(hdc,n_font);

	if(mode.CompareNoCase("EDGE") == 0)			
	{
		Draw_GradientFill(hdc,st,et,1,
						  br_color,bg_color,bb_color,
						  gr_color,gg_color,gb_color);
	}
	else if(mode.CompareNoCase("CENTER") == 0)	
	{
		Draw_GradientCenter(hdc,st,et,1,
							br_color,bg_color,bb_color,
							gr_color,gg_color,gb_color);
	}
	else	
	{
		Rectangle(hdc,st.x,st.y,et.x,et.y);
	}

	HDC bmp_hdc = mMng_Text.hDC;
	SetTextColor(bmp_hdc,t_color);
	SetBkMode(bmp_hdc,TRANSPARENT);
	SetTextAlign(bmp_hdc,TA_CENTER|VTA_BASELINE);
	SelectObject(bmp_hdc,n_font);
	mMng_Text.DrawText(title,hdc,t_pt,st,et);
	
	SelectObject(hdc,o_font);
	if(n_font != NULL)	DeleteObject(n_font);

	SelectObject(hdc,old_brush);
	if(brush != NULL)	DeleteObject(brush);

	LeaveCriticalSection(&mCS_Lock);
}

void CClass__Macro_Fnc::
Draw_Text(HDC hdc,
		  CString title,  
		  POINT t_pt,
		  COLORREF t_color,
		  LOGFONT fontlog,
		  int fonttype)
{
	Draw_Text(hdc,title,t_pt,t_color,fontlog,fonttype,"");
}

void CClass__Macro_Fnc::
Draw_Text(HDC hdc,
		  CString title,  
		  POINT t_pt,
		  COLORREF t_color,
		  LOGFONT fontlog,
		  int fonttype,
		  CString mode)
{
	EnterCriticalSection(&mCS_Lock);
	
	SetTextColor(hdc,t_color);
	SetBkMode(hdc,TRANSPARENT);
	
	if(mode.Compare("CENTER") == 0)
		SetTextAlign(hdc,TA_CENTER|VTA_BASELINE);
	else
		SetTextAlign(hdc,TA_LEFT|VTA_BASELINE);

	HFONT n_font = CreateFontIndirect(&fontlog);
	if(n_font == NULL)
	{
		MessageBox(NULL,"Font : NULL","CClass__Macro_Fnc:Draw_Text",MB_OK|MB_TOPMOST);
	}
	HFONT o_font = (HFONT) SelectObject(hdc,n_font);

	TextOut(hdc,t_pt.x,t_pt.y,title,strlen(title));

	SelectObject(hdc,o_font);
	if(n_font != NULL)	DeleteObject(n_font);

	LeaveCriticalSection(&mCS_Lock);
}

void CClass__Macro_Fnc::
Draw_Text(HDC hdc,
		  CString title,
		  POINT t_pt,
		  COLORREF t_color)							 
{
	EnterCriticalSection(&mCS_Lock);
	
	SetTextColor(hdc,t_color);
	SetBkMode(hdc,TRANSPARENT);
	SetTextAlign(hdc,TA_LEFT|VTA_BASELINE);

	TextOut(hdc,t_pt.x,t_pt.y,title,strlen(title));
	
	LeaveCriticalSection(&mCS_Lock);
}

void CClass__Macro_Fnc::
Draw_GradientFill(HDC hdc,
				  POINT st,POINT et,int section,
				  int br_color,int bg_color,int bb_color,
				  int gr_color,int gg_color,int gb_color)
{
	EnterCriticalSection(&mCS_Lock);
	
	double  width, c_px;
	POINT	pt;
	int     i;

	if(section < 1)		section = 1;
	width  = (et.x - st.x)/section;
	pt.x = st.x;
	c_px = st.x;

	int r_color,   g_color,  b_color;
	int dr_color, dg_color, db_color;
	r_color  = 255*br_color;
	g_color  = 255*bg_color;
	b_color  = 255*bb_color;
	dr_color = 255*gr_color;
	dg_color = 255*gg_color;
	db_color = 255*gb_color;

	r_color -= dr_color;
	g_color -= dg_color;
	b_color -= db_color;
	
	r_color  /= section;
	g_color  /= section;
	b_color  /= section;

	TRIVERTEX		vert[4];
	GRADIENT_RECT	grt;

	grt.UpperLeft  = 0;
	grt.LowerRight = 1;

	for(i=0;i<section;i++)
	{
		vert[0].x     = pt.x;
		vert[0].y     = st.y;
		vert[0].Red   = i * r_color + dr_color;
		vert[0].Green = i * g_color + dg_color;
		vert[0].Blue  = i * b_color + db_color;
		vert[0].Alpha = 0;

		c_px += width; 
		pt.x = (int) c_px;

		vert[1].x     = pt.x;
		vert[1].y     = et.y;
		vert[1].Red   = (i+1) * r_color + dr_color;
		vert[1].Green = (i+1) * g_color + dg_color;
		vert[1].Blue  = (i+1) * b_color + db_color;
		vert[1].Alpha = 0;

		GradientFill(hdc,vert,2,&grt,1,GRADIENT_FILL_RECT_H);
	}

	LeaveCriticalSection(&mCS_Lock);
}

void CClass__Macro_Fnc::
Draw_GradientCenter(HDC hdc,
					POINT st,POINT et,int section,
				   int br_color,int bg_color,int bb_color,
				   int gr_color,int gg_color,int gb_color)
{
	EnterCriticalSection(&mCS_Lock);
	
	double  width, c_px;
	POINT	pt;
	int     i;

	if(section < 1)		section = 1;
	width  = (double)(et.x - st.x)/section;
	pt.x = st.x;
	c_px = st.x;

	int r_color,   g_color,  b_color;
	int dr_color, dg_color, db_color;
	r_color  = 255*br_color;
	g_color  = 255*bg_color;
	b_color  = 255*bb_color;
	dr_color = 255*gr_color;
	dg_color = 255*gg_color;
	db_color = 255*gb_color;

	r_color -= dr_color;
	g_color -= dg_color;
	b_color -= db_color;

	r_color /= section;
	g_color /= section;
	b_color /= section;

	int   r_color1, g_color1, b_color1;
	int   r_color2, g_color2, b_color2;
	int   h_section;
	r_color *= 2;
	g_color *= 2;
	b_color *= 2;
	h_section = section / 2;

	TRIVERTEX		vert[4];
	GRADIENT_RECT	grt;

	grt.UpperLeft  = 0;
	grt.LowerRight = 1;

	for(i=0;i<section;i++)
	{
		if(i < h_section)
		{
			r_color1 = i*r_color + dr_color;
			g_color1 = i*g_color + dg_color;
			b_color1 = i*b_color + db_color;
			r_color2 = (i+1)*r_color + dr_color;
			g_color2 = (i+1)*g_color + dg_color;
			b_color2 = (i+1)*b_color + db_color;
		}
		else
		{
			r_color1 = (section-i)*r_color + dr_color;
			g_color1 = (section-i)*g_color + dg_color;
			b_color1 = (section-i)*b_color + db_color;
			r_color2 = (section-i-1)*r_color + dr_color;
			g_color2 = (section-i-1)*g_color + dg_color;
			b_color2 = (section-i-1)*b_color + db_color;
		}

		vert[0].x     = pt.x;
		vert[0].y     = st.y;
		vert[0].Red   = r_color1;
		vert[0].Green = g_color1;
		vert[0].Blue  = b_color1; 
		vert[0].Alpha = 0;

		c_px += width;
		pt.x = (int) c_px;

		vert[1].x	  = pt.x;
		vert[1].y	  = et.y;
		vert[1].Red   = r_color2;
		vert[1].Green = g_color2;
		vert[1].Blue  = b_color2; 
		vert[1].Alpha = 0;
		
		GradientFill(hdc,vert,2,&grt,1,GRADIENT_FILL_RECT_H);
	}

	LeaveCriticalSection(&mCS_Lock);
}

void CClass__Macro_Fnc::
Draw_ArrowUp(HDC hdc,POINT st,POINT et,COLORREF color)
{
	POINT pt[3];

	pt[0].x = (st.x + et.x) / 2;
	pt[0].y = st.y + 3;
	pt[1].x = et.x - 3;
	pt[1].y = et.y - 3;
	pt[2].x = st.x + 3;
	pt[2].y = et.y - 3;

	Draw_Polygon(hdc,pt,3,color);
}

void CClass__Macro_Fnc::
Draw_ArrowDown(HDC hdc,POINT st,POINT et,COLORREF color)
{
	POINT pt[3];

	pt[0].x = st.x + 3;
	pt[0].y = st.y + 3;
	pt[1].x = et.x - 3;
	pt[1].y = st.y + 3;
	pt[2].x = (st.x + et.x) / 2;
	pt[2].y = et.y - 3;

	Draw_Polygon(hdc,pt,3,color);
}

void CClass__Macro_Fnc::
Draw_ArrowLeft(HDC hdc,POINT st,POINT et,COLORREF color)
{
	POINT pt[3];
	int   width, height, edge, h_edge;

	edge   = (et.x-st.x)/4;
	h_edge = edge/2;
	width  = 3*edge;
	height = 3*edge;

	pt[0].x = st.x + h_edge;
	pt[0].y = (st.y + et.y) / 2;
	pt[1].x = et.x - h_edge;
	pt[1].y = st.y + h_edge;
	pt[2].x = et.x - h_edge;
	pt[2].y = et.y - h_edge;

	Draw_Polygon(hdc,pt,3,color);
}

void CClass__Macro_Fnc::
Draw_ArrowRight(HDC hdc,POINT st,POINT et,COLORREF color)
{
	POINT pt[3];
	int   width, height, edge, h_edge;

	edge   = (et.x-st.x)/4;
	h_edge = edge/2;
	width  = 3*edge;
	height = 3*edge;

	pt[0].x = st.x + h_edge;
	pt[0].y = st.y + h_edge;
	pt[1].x = et.x - h_edge;
	pt[1].y = (st.y + et.y) / 2;
	pt[2].x = st.x + h_edge;
	pt[2].y = et.y - h_edge;

	Draw_Polygon(hdc,pt,3,color);
}
