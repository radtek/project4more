#pragma once


// CHoverButton

class CHoverButton : public CBitmapButton
{
	DECLARE_DYNAMIC(CHoverButton)

public:
	CHoverButton();
	virtual ~CHoverButton();
public:
	void SetTextColor(COLORREF textColor)
	{
		m_textColor = textColor;
	}
    BOOL LoadBitmap(UINT bitmapid);
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
    LRESULT OnMouseHover(WPARAM wparam, LPARAM lparam) ;
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
public:
	//指示鼠标是否在按钮上面
	BOOL m_bHover;
	//按钮是否跟踪到鼠标
	BOOL m_bTracking;
	//保存图片的变量
	CBitmap mybitmap;
	//按钮尺寸
	CSize m_ButtonSize;
private:
	UINT m_bitmapId;
	COLORREF m_textColor;
protected:
	virtual void PreSubclassWindow();
};


