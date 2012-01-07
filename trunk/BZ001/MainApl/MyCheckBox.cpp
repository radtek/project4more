// MyCheckBox.cpp : ʵ���ļ�
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



// CMyCheckBox ��Ϣ�������

HBRUSH CMyCheckBox::CtlColor(CDC* pDC, UINT nCtlColor)
{
	COLORREF old = pDC->SetTextColor( m_textColor);	//����������ɫ
	pDC->SetBkColor( m_bkColor );		//���ñ���ɫ
	return (HBRUSH)m_BkBrush.GetSafeHandle();
}
