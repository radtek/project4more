#pragma once
#include "resource.h"
#include "afxwin.h"

// CSearchWayOneDlg dialog

class CSearchWayOneDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchWayOneDlg)

public:
	CSearchWayOneDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSearchWayOneDlg();

// Dialog Data
	enum { IDD = IDD_SEARCH_WAY_ONE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadioSw1All();
	afx_msg void OnBnClickedRadioSw1Goods();
	afx_msg void OnBnClickedRadioSw1Cars();
	afx_msg void OnBnClickedButtonSw1Select();
	afx_msg void OnBnClickedButtonSw1CleanAddr();
	afx_msg void OnBnClickedButtonSw1Addr();
	afx_msg void OnBnClickedButtonSw1Goods();
	afx_msg void OnBnClickedButtonSw1CarType();
	afx_msg void OnBnClickedButtonSw1CarSize();
	afx_msg void OnBnClickedButtonSw1GoodsType();
	afx_msg void OnBnClickedButtonSw1CleanPublisher();
	afx_msg void OnBnClickedButtonSw1CleanPhoneNum();
	afx_msg void OnBnClickedRadioMatchAll();
	afx_msg void OnBnClickedRadioMatchAny();
	CString m_sDestAddr;
private:
	CComboBox m_comboxPublisher;
	CComboBox m_comboxPhoneNum;
};
