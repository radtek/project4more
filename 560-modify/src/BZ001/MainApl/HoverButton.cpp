// HoverButton.cpp : 实现文件
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



// CHoverButton 消息处理程序

BOOL CHoverButton::LoadBitmap(UINT bitmapid)
{
	if( m_bitmapId == bitmapid )
	{
		return TRUE;
	}

	mybitmap.Detach();
	m_bitmapId = bitmapid;
    // 载入图片：用一张包含按钮的三种状态(鼠标移开，鼠标在按钮上，鼠标单击)的位图来绘制按钮
    mybitmap.Attach(::LoadImage(::AfxGetInstanceHandle(),MAKEINTRESOURCE(bitmapid),
        IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS));
    BITMAP bitmapbits;
    //获取位图信息并存入bitmapbits结构中
    mybitmap.GetBitmap(&bitmapbits);
    
    //取位图相应的高度和1/3宽度。
    m_ButtonSize.cy=bitmapbits.bmHeight;
    m_ButtonSize.cx=bitmapbits.bmWidth/3;
    SetWindowPos( NULL, 0,0, m_ButtonSize.cx,m_ButtonSize.cy, SWP_NOMOVE |SWP_NOOWNERZORDER );
	Invalidate(TRUE);
    return TRUE;
}

void CHoverButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//获取保存在DRAWITEMSTRUCT结构中且在绘制按钮时必须使用的设备上下文
	CDC* mydc=CDC::FromHandle(lpDrawItemStruct->hDC);
	mydc->SetTextColor(RGB(0, 66, 118));

	if( m_bitmapId != -1 )
	{
		//创建兼容的设备上下文
		CDC* pMemDC = new CDC;
		pMemDC -> CreateCompatibleDC(mydc);

		//保存旧对象
		CBitmap * pOldBitmap;
		pOldBitmap = pMemDC -> SelectObject(&mybitmap);

		CPoint point(0,0);    

		//判断按钮是否处于选择状态，如果是则绘制选择状态的按钮位图，在我们提供的位图中，选中状态的按钮图片是第三个
		if(lpDrawItemStruct->itemState & ODS_SELECTED)
		{        
			mydc->BitBlt(0,0,m_ButtonSize.cx,m_ButtonSize.cy,pMemDC,m_ButtonSize.cx*2,0,SRCCOPY);
		}
		else
		{   //判断鼠标是否离开还是在按钮上面，以便绘制相应的位图
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
    // TODO: 在此添加消息处理程序代码和/或调用默认值
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
    //重画按钮
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
