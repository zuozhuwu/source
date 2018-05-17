#pragma once
#include "StdAfx.h"

class CMyChartCtrl: public CChartCtrl
{
public:
	CMyChartCtrl();
	~CMyChartCtrl();
	
	void setLeftAxisMinMax(double Minimum, double Maximum);
	void setBottomAxisMinMax(double Minimum, double Maximum);
	void addLine(const std::vector<double> &vecData);

	void clearData();
	void clearGraph();

	void draw();

private:
	virtual void PreSubclassWindow();

	int m_lineWidth;

	BOOL m_isLeftAxisSet;
	BOOL m_isBottomAxisSet;
	std::vector<std::vector<double> > m_vecData;
	std::vector<CChartLineSerie*>     m_vecLines;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};