#pragma once
#include "afxwin.h"



class CSwitchButton :
	public CButton
{
private:
	int m_width;
	int m_height;

	HBITMAP m_hBitmapOff;
	HBITMAP m_hBitmapOn;

	unsigned int m_ACCKEY;     //自定义加速键

public:
	BOOL m_buttonState;


public:
	void setButtonSize(int width, int height);

	void setAccKey(unsigned int accKey);


public:
	CSwitchButton();
	~CSwitchButton();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClicked();
	virtual void PreSubclassWindow();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};

