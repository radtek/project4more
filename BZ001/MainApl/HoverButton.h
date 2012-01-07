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
	//ָʾ����Ƿ��ڰ�ť����
	BOOL m_bHover;
	//��ť�Ƿ���ٵ����
	BOOL m_bTracking;
	//����ͼƬ�ı���
	CBitmap mybitmap;
	//��ť�ߴ�
	CSize m_ButtonSize;
private:
	UINT m_bitmapId;
	COLORREF m_textColor;
protected:
	virtual void PreSubclassWindow();
};


