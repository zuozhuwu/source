#include "StdAfx.h"
#include "MyChartCtrl.h"

CMyChartCtrl::CMyChartCtrl()
{
	m_isLeftAxisSet = FALSE;
	m_isBottomAxisSet = FALSE;

	m_lineWidth = 2;
}
	
CMyChartCtrl::~CMyChartCtrl()
{
}


void CMyChartCtrl::PreSubclassWindow()
{		
	::SetWindowLongA(this->m_hWnd, GWL_STYLE, ::GetWindowLongA(this->m_hWnd, GWL_STYLE) | WS_CLIPCHILDREN);

	((CChartCtrl*)this)->SetBackGradient(RGB(255, 255, 255), RGB(150, 150, 255), gtVertical);

	((CChartCtrl*)this)->CreateStandardAxis(CChartCtrl::LeftAxis)->SetVisible(false);
	((CChartCtrl*)this)->CreateStandardAxis(CChartCtrl::BottomAxis)->SetVisible(false);	

	CChartCtrl::PreSubclassWindow();
}

void CMyChartCtrl::setLeftAxisMinMax(double Minimum, double Maximum)
{
	((CChartCtrl*)this)->GetLeftAxis()->SetMinMax(Minimum, Maximum);   
	m_isLeftAxisSet = TRUE;
}

void CMyChartCtrl::setBottomAxisMinMax(double Minimum, double Maximum)
{
	((CChartCtrl*)this)->GetBottomAxis()->SetMinMax(Minimum, Maximum);   
	m_isBottomAxisSet = TRUE;
}

void CMyChartCtrl::addLine(const std::vector<double> &vecData)
{
	CChartLineSerie* pLineSerie = ((CChartCtrl*)this)->CreateLineSerie();
	pLineSerie->SetWidth(m_lineWidth);

	m_vecLines.push_back(pLineSerie);
	m_vecData.push_back(vecData);
}

void CMyChartCtrl::clearData()
{
	m_vecData.clear();
	m_vecLines.clear();
}

void CMyChartCtrl::clearGraph()
{
	((CChartCtrl*)this)->RemoveAllSeries();
	((CChartCtrl*)this)->RefreshCtrl();
}

void CMyChartCtrl::draw()
{
	if(!m_isLeftAxisSet)
	{
		this->MessageBox(_T("请先设置坐标轴！"), _T("画图出错"));
		return;
	}

	if(m_vecData.size() != m_vecLines.size())
	{
		this->MessageBox(_T("数据与线条不匹配"), _T("画图出错"));
		return;
	}

	if(!m_isBottomAxisSet)    //如果没有设置底部坐标，则默认等于数据的长度
	{
		((CChartCtrl*)this)->GetBottomAxis()->SetMinMax(0, m_vecData[0].size());  		
	}

	((CChartCtrl*)this)->GetBottomAxis()->SetVisible(true);
	((CChartCtrl*)this)->GetLeftAxis()->SetVisible(true);

	for(size_t i = 0; i < (size_t)m_vecData.size(); ++i)
	{
		CChartLineSerie* pLineSerie = m_vecLines[i];
		

		int dataSize = m_vecData[i].size();
		double *pYData = new double[dataSize];
		double *pXData = new double[dataSize];

		for(size_t j = 0; j < (size_t)dataSize; j++)
		{
			*(pYData + j) = m_vecData[i][j];
			*(pXData + j) = j;
		}

		pLineSerie->AddPoints(pYData, pXData, dataSize);

		delete []pYData;
		delete []pXData;		
	}

}BEGIN_MESSAGE_MAP(CMyChartCtrl, CChartCtrl)
	ON_WM_CREATE()
	END_MESSAGE_MAP()


int CMyChartCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CChartCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	

	return 0;
}
