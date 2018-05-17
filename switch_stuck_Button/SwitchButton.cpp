#include "stdafx.h"
#include "SwitchButton.h"

CSwitchButton::CSwitchButton()
{
	m_width = 120;
	m_height = 40;	

	m_ACCKEY = 0;

	m_hBitmapOn = (HBITMAP)::LoadImage(
		NULL,
		_T("./res/switchOn.bmp"),                           // 图片全路径  
		IMAGE_BITMAP,                          // 图片格式  
		m_width, m_height,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);  // 注意LR_LOADFROMFILE  

	m_hBitmapOff = (HBITMAP)::LoadImage(
		NULL,
		_T("./res/switchOff.bmp"),                           // 图片全路径  
		IMAGE_BITMAP,                          // 图片格式  
		m_width, m_height,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);  // 注意LR_LOADFROMFILE  
	
}


CSwitchButton::~CSwitchButton()
{
}
BEGIN_MESSAGE_MAP(CSwitchButton, CButton)
	ON_CONTROL_REFLECT(BN_CLICKED, &CSwitchButton::OnBnClicked)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_KEYUP()
END_MESSAGE_MAP()


void CSwitchButton::OnBnClicked()
{
	if (m_buttonState == FALSE)
	{
		this->SetBitmap(m_hBitmapOn);
		m_buttonState = TRUE;
	}
	else
	{
		this->SetBitmap(m_hBitmapOff);
		m_buttonState = FALSE;
	}
}

void CSwitchButton::setButtonSize(int width, int height)
{
	m_width = width;
	m_height = height;
}

void CSwitchButton::setAccKey(unsigned int accKey)
{
	m_ACCKEY = accKey;
}

void CSwitchButton::PreSubclassWindow()
{
	CRect rect;
	this->GetWindowRect(&rect);

	this->MoveWindow(rect.left, rect.top, m_width, m_height);  //resize window to fit bitmap size

	this->ModifyStyle(0, BS_BITMAP);

	this->SetBitmap(m_hBitmapOff);
	m_buttonState = FALSE;

	CButton::PreSubclassWindow();
}

void CSwitchButton::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (m_ACCKEY == nChar)
	{
		OnBnClicked();
	}		

	CButton::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CSwitchButton::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (m_ACCKEY == nChar)
		OnBnClicked();
	CButton::OnChar(nChar, nRepCnt, nFlags);
}