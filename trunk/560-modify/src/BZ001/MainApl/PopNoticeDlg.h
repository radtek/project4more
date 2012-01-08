#pragma once

#include "VerticalScrollerCtrl.h"
#include "HyperLink/HyperLink.h"
#include "afxwin.h"
// CPopNoticeDlg �Ի���

class CPopNoticeDlg : public CDialog
{
	DECLARE_DYNAMIC(CPopNoticeDlg)

public:
	CPopNoticeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPopNoticeDlg();

// �Ի�������
	enum { IDD = IDD_POP_NOTICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// { �Զ���
public:
    CString showMsg;

	CString showMsgAG;
	BOOL m_popclose;
public:
    void setPos(int x, int y) {
        posX = x;
        posY = y;
    };

private:
    // �Ի������½�����
    int posX;
    int posY;


    // ��ֱ�������
    CVerticalScrollerCtrl m_scroller;
// }

	DECLARE_MESSAGE_MAP()
public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
    virtual BOOL OnInitDialog();
protected:
    virtual void PostNcDestroy();
public:
    afx_msg void OnDestroy();
public:
    afx_msg void OnClose();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CHyperLink m_HyperLink1;
	afx_msg void OnPaint();
	CHyperLink m_hyperAG;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
