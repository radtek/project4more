// HoverButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "HoverButton.h"


// CHoverButton

IMPLEMENT_DYNAMIC(CHoverButton, CBitmapButton)

CHoverButton::CHoverButton()
{
    m_bHover = FALSE;       
    m_bTracking = FALSE;
	m_bitmapId = -1;
	m_textColor = -1;
}

CHoverButton::~CHoverButton()
{
}


BEGIN_MESSAGE_MAP(CHoverButton, CBitmapButton)
    ON_WM_MOUSEMOVE()
    ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
    ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// CHoverButton ��Ϣ�������

BOOL CHoverButton::LoadBitmap(UINT bitmapid)
{
	if( m_bitmapId == bitmapid )
	{
		return TRUE;
	}

	mybitmap.Detach();
	m_bitmapId = bitmapid;
    // ����ͼƬ����һ�Ű�����ť������״̬(����ƿ�������ڰ�ť�ϣ���굥��)��λͼ�����ư�ť
    mybitmap.Attach(::LoadImage(::AfxGetInstanceHandle(),MAKEINTRESOURCE(bitmapid),
        IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS));
    BITMAP bitmapbits;
    //��ȡλͼ��Ϣ������bitmapbits�ṹ��
    mybitmap.GetBitmap(&bitmapbits);
    
    //ȡλͼ��Ӧ�ĸ߶Ⱥ�1/3��ȡ�
    m_ButtonSize.cy=bitmapbits.bmHeight;
    m_ButtonSize.cx=bitmapbits.bmWidth/3;
    SetWindowPos( NULL, 0,0, m_ButtonSize.cx,m_ButtonSize.cy, SWP_NOMOVE |SWP_NOOWNERZORDER );
	Invalidate(TRUE);
    return TRUE;
}

void CHoverButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//��ȡ������DRAWITEMSTRUCT�ṹ�����ڻ��ư�ťʱ����ʹ�õ��豸������
	CDC* mydc=CDC::FromHandle(lpDrawItemStruct->hDC);
	mydc->SetTextColor(RGB(0, 66, 118));

	if( m_bitmapId != -1 )
	{
		//�������ݵ��豸������
		CDC* pMemDC = new CDC;
		pMemDC -> CreateCompatibleDC(mydc);

		//����ɶ���
		CBitmap * pOldBitmap;
		pOldBitmap = pMemDC -> SelectObject(&mybitmap);

		CPoint point(0,0);    

		//�жϰ�ť�Ƿ���ѡ��״̬������������ѡ��״̬�İ�ťλͼ���������ṩ��λͼ�У�ѡ��״̬�İ�ťͼƬ�ǵ�����
		if(lpDrawItemStruct->itemState & ODS_SELECTED)
		{        
			mydc->BitBlt(0,0,m_ButtonSize.cx,m_ButtonSize.cy,pMemDC,m_ButtonSize.cx*2,0,SRCCOPY);
		}
		else
		{   //�ж�����Ƿ��뿪�����ڰ�ť���棬�Ա������Ӧ��λͼ
			if(m_bHover)
			{
				mydc->BitBlt(0,0,m_ButtonSize.cx,m_ButtonSize.cy,pMemDC,m_ButtonSize.cx,0,SRCCOPY);            
			}else
			{
				mydc->BitBlt(0,0,m_ButtonSize.cx,m_ButtonSize.cy,pMemDC,0,0,SRCCOPY);
			}    
		}

		// clean up
		pMemDC -> SelectObject(pOldBitmap);
		delete pMemDC; 
	}
} 

void CHoverButton::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if (!m_bTracking)
    {
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(tme);
        tme.hwndTrack = m_hWnd;
        tme.dwFlags = TME_LEAVE|TME_HOVER;
        tme.dwHoverTime = 1;
        m_bTracking = _TrackMouseEvent(&tme);
    }

    CBitmapButton::OnMouseMove(nFlags, point);
}

LRESULT CHoverButton::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
    m_bTracking = FALSE;
    m_bHover=FALSE;
    //�ػ���ť
    Invalidate(TRUE);
    return 0;
}

LRESULT CHoverButton::OnMouseHover(WPARAM wparam, LPARAM lparam) 
{
    m_bHover=TRUE;
    Invalidate(TRUE);
    return 0;
}

HBRUSH CHoverButton::CtlColor(CDC* pDC, UINT nCtlColor)
{
	if( m_textColor != -1 )
	{
		pDC->SetTextColor(m_textColor);
	}
	
	return NULL;
}

void CHoverButton::PreSubclassWindow()
{

	/*UINT uStyle = GetButtonStyle();
	if( (uStyle&SS_TYPEMASK) != BS_OWNERDRAW )
	{
		uStyle |= BS_OWNERDRAW;
		SetButtonStyle(uStyle, TRUE);
	}*/
	CBitmapButton::PreSubclassWindow();
}
