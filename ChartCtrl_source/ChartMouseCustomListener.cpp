#include "stdafx.h"

CRect MaxWindow(311,10,1476,740);



CChartMouseCustomListener::CChartMouseCustomListener()
{
	m_isMaxWindow = FALSE;
}

CChartMouseCustomListener::CChartMouseCustomListener(HWND Hwnd, CRect r)
{
	m_isMaxWindow = FALSE;

	r.top -= 30;
	r.left -= 8;
	r.bottom -= 30;
	r.right -= 8;


	m_oldRect = r;
	m_Hwnd = Hwnd;
}


CChartMouseCustomListener::~CChartMouseCustomListener()
{
}

void CChartMouseCustomListener::setOrginRect(CRect r)
{
	m_oldRect = r;
}

void CChartMouseCustomListener::OnMouseEventPlotArea(MouseEvent mouseEvent, CPoint point)
{
	if (mouseEvent == LButtonDoubleClick)
	{
		if (m_isMaxWindow == FALSE)
		{
			CWnd::FromHandle(m_Hwnd)->MoveWindow(MaxWindow);
			m_isMaxWindow = TRUE;

			::SendMessage(CWnd::FromHandle(m_Hwnd)->GetParent()->m_hWnd, WM_HIDEWINDOW, 0, 0);
		}
		else
		{
			CWnd::FromHandle(m_Hwnd)->MoveWindow(m_oldRect);
			m_isMaxWindow = FALSE;
			::SendMessage(CWnd::FromHandle(m_Hwnd)->GetParent()->m_hWnd, WM_SHOWALLWINDOW, 0, 0);
		}		
	}
}

void CChartMouseCustomListener::OnMouseEventAxis(MouseEvent mouseEvent, CPoint point, CChartAxis* pAxisClicked)
{
	if (mouseEvent == LButtonDoubleClick)
	{
		
	}

}

void CChartMouseCustomListener::OnMouseEventTitle(MouseEvent mouseEvent, CPoint point)
{
	if (mouseEvent == MouseMove)
	{

	}

}

void CChartMouseCustomListener::OnMouseEventLegend(MouseEvent mouseEvent, CPoint point)
{
	if (mouseEvent == LButtonDoubleClick)
	{

	}

}
