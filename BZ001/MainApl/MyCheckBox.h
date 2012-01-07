#pragma once


// CMyCheckBox

class CMyCheckBox : public CButton
{
	DECLARE_DYNAMIC(CMyCheckBox)

public:
	CMyCheckBox();
	virtual ~CMyCheckBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	void SetTextColor(COLORREF textColor)
	{
		m_textColor = textColor;
	}
	void SetBkColor(COLORREF bkColor)
	{
		m_bkColor= bkColor;
		m_BkBrush.Detach();
		m_BkBrush.CreateSolidBrush( m_bkColor );
	}
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
private:
	COLORREF m_textColor;
	COLORREF m_bkColor;
	CBrush	 m_BkBrush;		//±³¾°Ë¢
};


