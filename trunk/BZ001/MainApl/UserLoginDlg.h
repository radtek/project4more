#pragma once

#include "HyperLink/HyperLink.h"
#include "GLB.h"

#include "UserData.h"
#include "afxwin.h"
#include "MyLib.h"
#include "hoverbutton.h"
#include "MyCheckBox.h"
// CUserLoginDlg �Ի���

class CUserLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserLoginDlg)

public:
	CUserLoginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserLoginDlg();

// �Ի�������
	enum { IDD = IDD_USER_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// { �Զ���
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
	// �����û�����
	int saveUserData();
	// �����û�����
	int loadUserData();

public:
	// �û���
	CString userName;
	// ����
	CString passWord;
private:
	CHoverButton m_btnLogin;
	CHoverButton m_btnCancel;
	CHoverButton m_btnClose;

	COLORREF	m_bgColor;
	COLORREF	m_textColor;
	// ��ס�û����ؼ�
	CMyCheckBox btnRemUserName;
	// ��ס����ؼ�
	CMyCheckBox btnRemPassWord;

	CHyperLink regNewUser;
	CHyperLink m_retrievePW;

	// �û�����
	WLRUserData userData;
	// ��ס�ʺ�
	BOOL ifRemUserName;
	// ��ס����
	BOOL ifRemPassWord;
public:
	afx_msg void OnBnClickedButtonClose();
};
