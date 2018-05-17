#pragma once
#include "stdafx.h"

#define WM_HIDEWINDOW WM_USER + 101      //发送隐藏其他窗口的消息
#define WM_SHOWALLWINDOW WM_USER + 102      //发送显示所有窗口消息

extern CRect MaxWindow;

class CChartMouseCustomListener :
	public CChartMouseListener
{
public:
	CChartMouseCustomListener();
	CChartMouseCustomListener(HWND Hwnd, CRect r);
	~CChartMouseCustomListener();

	void setOrginRect(CRect r);
	void OnMouseEventPlotArea(MouseEvent mouseEvent, CPoint point);
	void OnMouseEventAxis(MouseEvent mouseEvent, CPoint point, CChartAxis* pAxisClicked);
	void OnMouseEventTitle(MouseEvent mouseEvent, CPoint point);
	void OnMouseEventLegend(MouseEvent mouseEvent, CPoint point);


private:
	CRect m_oldRect;
	HWND m_Hwnd;
	BOOL m_isMaxWindow;
};

