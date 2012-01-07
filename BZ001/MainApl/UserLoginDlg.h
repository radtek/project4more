#pragma once

#include "HyperLink/HyperLink.h"
#include "GLB.h"

#include "UserData.h"
#include "afxwin.h"
#include "MyLib.h"
#include "hoverbutton.h"
#include "MyCheckBox.h"
// CUserLoginDlg 对话框

class CUserLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserLoginDlg)

public:
	CUserLoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserLoginDlg();

// 对话框数据
	enum { IDD = IDD_USER_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// { 自定义
public:
    
// }

    DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    afx_msg void OnClose();
    afx_msg void OnBnClickedUserLoginRemUsername();
    afx_msg void OnBnClickedUserLoginRemPassname();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
	// 保存用户数据
	int saveUserData();
	// 加载用户数据
	int loadUserData();

public:
	// 用户名
	CString userName;
	// 密码
	CString passWord;
private:
	CHoverButton m_btnLogin;
	CHoverButton m_btnCancel;
	CHoverButton m_btnClose;

	COLORREF	m_bgColor;
	COLORREF	m_textColor;
	// 记住用户名控件
	CMyCheckBox btnRemUserName;
	// 记住密码控件
	CMyCheckBox btnRemPassWord;

	CHyperLink regNewUser;
	CHyperLink m_retrievePW;

	// 用户数据
	WLRUserData userData;
	// 记住帐号
	BOOL ifRemUserName;
	// 记住密码
	BOOL ifRemPassWord;
public:
	afx_msg void OnBnClickedButtonClose();
};
