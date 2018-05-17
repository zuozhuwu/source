#pragma once
#include "afxwin.h"
class CStuckButton :
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

	void turnOnLight();
	void turnOffLight();

public:
	CStuckButton();
	~CStuckButton();
	virtual void PreSubclassWindow();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};

