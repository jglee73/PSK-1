#pragma once


class CClass__Macro_Fnc
{
private:
	CRITICAL_SECTION mCS_Lock;
	COLORREF         mColor_Black;


public:
	CClass__Macro_Fnc();
	~CClass__Macro_Fnc();

	// ...
	COLORREF GetColor(CString string);
	COLORREF GetColor(CString string,int *r,int *g,int *b);

	//
	void Copy(HDC hdc,POINT t_st,POINT t_et,HDC hdc_back,POINT s_st,POINT s_et);
	void Copy(HDC hdc,HDC hdc_back,POINT st,POINT et);
	
	//
	void Get_TextPoint(HDC hdc,POINT st,POINT et,POINT *pt);
	void Draw_Line(HDC hdc,POINT st,POINT et,COLORREF color);
	HFONT MakeFont(HDC hdc,int width,int height,HFONT *hfont);
	void  DeleteFont(HDC hdc,HFONT old_hfont,HFONT new_hfont);
	HBRUSH MakeBrush(HDC hdc,HBRUSH *hbrush,COLORREF color);
	void DeleteBrush(HDC hdc,HBRUSH hbrush,HBRUSH old_brush);
	int  GetWaferColor(CString status,COLORREF *color);
	
	//
	void Draw_Ellipse(HDC hdc,POINT st,POINT et,COLORREF color);
	void Draw_Polygon(HDC hdc,POINT *ppt,int pt_limit,COLORREF color);
	void Draw_Rectangle(HDC hdc,POINT st,POINT et,int width);
	void Draw_Rectangle_Pressed(HDC hdc,POINT st,POINT et,int width);
	void Draw_Rectangle(HDC hdc,POINT st,POINT et,int width, COLORREF up_color,COLORREF down_color);
	void Fill_Rectangle(HDC hdc,POINT st,POINT et,COLORREF b_color);

	//
	void Draw_Text(HDC hdc,CString title,POINT t_pt,int width,int height, COLORREF color,CString mode);
	void Draw_Text(HDC hdc,CString title,POINT t_pt,int width,int height,int weight, COLORREF color,CString mode,CString font_name);

	void Draw_Text(HDC hdc,CString title,POINT t_pt,COLORREF t_color);
	void Draw_Text(HDC hdc,CString title,POINT t_pt,int width,int height,COLORREF color);
	void Draw_Text(HDC hdc,CString title,POINT t_pt,COLORREF t_color,LOGFONT fontlog,int fonttype);
	void Draw_Text(HDC hdc,CString title,POINT t_pt,COLORREF t_color,LOGFONT fontlog,int fonttype,CString mode);
	void Draw_Text(HDC hdc,CString title,POINT st,POINT et,POINT t_pt,
				   COLORREF t_color,COLORREF b_color,
				   int tr_color,int tg_color,int tb_color,
				   int br_color,int bg_color,int bb_color,
				   LOGFONT fontlog,int fonttype);
	void Draw_Text(HDC hdc,CString title,POINT st,POINT et,POINT t_pt,
				   COLORREF t_color,COLORREF b_color,CString mode,
				   int tr_color,int tg_color,int tb_color,
				   int br_color,int bg_color,int bb_color,
				   int gr_color,int gg_color,int gb_color,
				    LOGFONT fontlog,int fonttype);

	//
	void Draw_GradientFill(HDC hdc,POINT st,POINT et,int section,
						   int br_color,int bg_color,int bb_color,
						   int gr_color,int gg_color,int gb_color);
	void Draw_GradientCenter(HDC hdc,POINT st,POINT et,int section,
						    int br_color,int bg_color,int bb_color,
						    int gr_color,int gg_color,int gb_color);
	void Draw_ArrowUp(HDC hdc,POINT st,POINT et,COLORREF color);
	void Draw_ArrowDown(HDC hdc,POINT st,POINT et,COLORREF color);
	void Draw_ArrowLeft(HDC hdc,POINT st,POINT et,COLORREF color);
	void Draw_ArrowRight(HDC hdc,POINT st,POINT et,COLORREF color);
};
