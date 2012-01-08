#pragma once
#include "embedded_ie_browser.h"
#include <string>

// CWebHTTP 对话框

class CWebHTTP : public CDialog
{
	DECLARE_DYNAMIC(CWebHTTP)

public:
	CWebHTTP(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWebHTTP();
	std::string url;
// 对话框数据
	enum { IDD = IDD_DLGWEB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEmbedded_ie_browser mWebBrowser;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();
};
