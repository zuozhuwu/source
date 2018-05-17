#include "stdafx.h"


CStuckButton::CStuckButton()
{
	m_width = 60;
	m_height = 60;

	m_hBitmapOn = (HBITMAP)::LoadImage(
		NULL,
		_T("./res/stuckButtonOn.bmp"),                           // 图片全路径  
		IMAGE_BITMAP,                          // 图片格式  
		m_width, m_height,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);  // 注意LR_LOADFROMFILE  

	m_hBitmapOff = (HBITMAP)::LoadImage(
		NULL,
		_T("./res/stuckButtonOff.bmp"),                           // 图片全路径  
		IMAGE_BITMAP,                          // 图片格式  
		m_width, m_height,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);  // 注意LR_LOADFROMFILE 
}


CStuckButton::~CStuckButton()
{
}

void CStuckButton::setButtonSize(int width, int height)
{
	m_width = width;
	m_height = height;
}

void CStuckButton::setAccKey(unsigned int accKey)
{
	m_ACCKEY = accKey;
}

void CStuckButton::PreSubclassWindow()
{
	CRect rect;
	this->GetWindowRect(&rect);

	this->MoveWindow(rect.left, rect.top, m_width, m_height);  //resize window to fit bitmap size

	this->ModifyStyle(0, BS_BITMAP);

	turnOffLight();

	CButton::PreSubclassWindow();
}
BEGIN_MESSAGE_MAP(CStuckButton, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()


void CStuckButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	turnOnLight();

	CButton::OnLButtonDown(nFlags, point);
}


void CStuckButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	turnOffLight();

	CButton::OnLButtonUp(nFlags, point);
}



void CStuckButton::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (m_ACCKEY == nChar)
	{
		turnOnLight();
	}

	CButton::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CStuckButton::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (m_ACCKEY == nChar)
	{
		turnOffLight();
	}

	CButton::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CStuckButton::turnOnLight()
{
	this->SetBitmap(m_hBitmapOn);
	m_buttonState = TRUE;
}

void CStuckButton::turnOffLight()
{
	this->SetBitmap(m_hBitmapOff);
	m_buttonState = FALSE;
}
