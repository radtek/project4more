#pragma once

#include "VerticalScrollerCtrl.h"
#include "HyperLink/HyperLink.h"
#include "afxwin.h"
// CPopNoticeDlg 对话框

class CPopNoticeDlg : public CDialog
{
	DECLARE_DYNAMIC(CPopNoticeDlg)

public:
	CPopNoticeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPopNoticeDlg();

// 对话框数据
	enum { IDD = IDD_POP_NOTICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// { 自定义
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
    // 对话框右下角坐标
    int posX;
    int posY;


    // 垂直卷滚变量
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
