#pragma once
#include "embedded_ie_browser.h"
#include <string>

// CEmbeddedIeDlg 对话框

class CEmbeddedIeDlg : public CDialog
{
	DECLARE_DYNAMIC(CEmbeddedIeDlg)

public:
	CEmbeddedIeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEmbeddedIeDlg();

// 对话框数据
	enum { IDD = IDD_EMBEDDED_IE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
// { 自定义
public:
	std::string url;
	BOOL m_flag;
	std::string urll;

	void SetDrump(BOOL bflag,std::string strl);
	void GoTo( CString url );
// }
public:
    // ie浏览器
    CEmbedded_ie_browser mWebBrowser;
public:
    virtual BOOL OnInitDialog();
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_EVENTSINK_MAP()
	void DocumentCompleteEmbeddedIeBrowser(LPDISPATCH pDisp, VARIANT* URL);
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();
	void NewWindow3EmbeddedIeBrowser(LPDISPATCH* ppDisp, BOOL* Cancel, unsigned long dwFlags, LPCTSTR bstrUrlContext, LPCTSTR bstrUrl);
};
