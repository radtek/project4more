#pragma once

#define WM_EDIT_LBUTTON_DOWN (WM_USER+2000)
// CMouseRspEdit

class CMouseRspEdit : public CEdit
{
	DECLARE_DYNAMIC(CMouseRspEdit)

public:
	CMouseRspEdit();
	virtual ~CMouseRspEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


