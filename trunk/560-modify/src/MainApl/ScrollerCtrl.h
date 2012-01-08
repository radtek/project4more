#pragma once

#include "GLB.h"
#include "ServerIO.h"

//#include <vector>

// CScrollerCtrl

class CScrollerCtrl : public CWnd
{
	DECLARE_DYNAMIC(CScrollerCtrl)

public:
	CScrollerCtrl();
	virtual ~CScrollerCtrl();

// {
public:
    // create the window.
	BOOL Create(CWnd* pParentWnd, ServerIO *pSvrIO, UINT nID = 100);

    // resize the window.
    int Resize();

    // ���ñ���ɫ
    void SetBgColor(COLORREF clrBg) {
        bgColor = clrBg;
    };
    // ����������ɫ
    void SetFgColor(COLORREF clrBg) {
        fgColor = clrBg;
    };
	// ������ʾ
	void DrawScrollerText();
private:
    // ������ͨ��
    ServerIO *svrIO;

    CWnd*   parentWnd;    // ������ָ��
    CRect	repaintRect;  // �ػ������
	CFont	curFont;	  // ��ǰ��ʾ������
	CBrush	bgBrush;	  // �ı���ʾ��������ɫ

    COLORREF bgColor; // ����ɫ
    COLORREF fgColor; // ����ɫ

	int	curShowMsgIndex; // ��ǰ��ʾ�����

	int showHeight;	// ��ǰ��ʾ����ĸ߶�
	int	showWidth;	// ��ǰ��ʾ����Ŀ��

	LOGFONT logFont; // ϵͳ��ʾ������	
    UINT_PTR	mTimer;
	BOOL	ifPause;

	int	showYLocation; // ��ǰ��ʾ���ַ�����Դ�ֱλ��
	int	strCurrentPos; // �ַ���ʾ��ʼˮƽλ��	

	std::vector<CString> showMsg; // ��ǰҪ��ʾ����Ϣ

private:


    // ��ȡ��Ϣ
    int getShowMsg();
// }

protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
};


