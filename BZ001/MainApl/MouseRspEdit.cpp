// MouseRspEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "MouseRspEdit.h"


// CMouseRspEdit

IMPLEMENT_DYNAMIC(CMouseRspEdit, CEdit)

CMouseRspEdit::CMouseRspEdit()
{

}

CMouseRspEdit::~CMouseRspEdit()
{
}


BEGIN_MESSAGE_MAP(CMouseRspEdit, CEdit)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CMouseRspEdit 消息处理程序



void CMouseRspEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	GetParent()->PostMessage(WM_EDIT_LBUTTON_DOWN);
	CEdit::OnLButtonDown(nFlags, point);
}
