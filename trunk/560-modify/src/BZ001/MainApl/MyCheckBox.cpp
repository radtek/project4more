// MyCheckBox.cpp : 实现文件
//

#include "stdafx.h"
#include "MyCheckBox.h"


// CMyCheckBox

IMPLEMENT_DYNAMIC(CMyCheckBox, CButton)

CMyCheckBox::CMyCheckBox()
{
	m_textColor = RGB(0, 66, 118);
	m_bkColor = RGB(200, 230, 254);
	m_BkBrush.CreateSolidBrush(m_bkColor);
}

CMyCheckBox::~CMyCheckBox()
{
}


BEGIN_MESSAGE_MAP(CMyCheckBox, CButton)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// CMyCheckBox 消息处理程序

HBRUSH CMyCheckBox::CtlColor(CDC* pDC, UINT nCtlColor)
{
	COLORREF old = pDC->SetTextColor( m_textColor);	//设置文字颜色
	pDC->SetBkColor( m_bkColor );		//设置背景色
	return (HBRUSH)m_BkBrush.GetSafeHandle();
}
