#pragma once
#include "embedded_ie_browser.h"
#include <string>

// CWebHTTP �Ի���

class CWebHTTP : public CDialog
{
	DECLARE_DYNAMIC(CWebHTTP)

public:
	CWebHTTP(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWebHTTP();
	std::string url;
// �Ի�������
	enum { IDD = IDD_DLGWEB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEmbedded_ie_browser mWebBrowser;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();
};
