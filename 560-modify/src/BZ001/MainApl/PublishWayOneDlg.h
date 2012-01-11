#pragma once
#include "resource.h"

// CPublishWayOne dialog

class CPublishWayOneDlg : public CDialog
{
	DECLARE_DYNAMIC(CPublishWayOneDlg)

public:
	CPublishWayOneDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPublishWayOneDlg();

// Dialog Data
	enum { IDD = IDD_PUB_WAY_ONE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonPw1FromProvince();
	afx_msg void OnBnClickedButtonPw1FromCity();
	afx_msg void OnBnClickedButtonPw1FromCounty();
	afx_msg void OnBnClickedButtonW1ToProvince();
	afx_msg void OnBnClickedButtonW1ToCity();
	afx_msg void OnBnClickedButtonW1ToCounty();
	afx_msg void OnBnClickedButtonGoodsNum();
	afx_msg void OnBnClickedButtonCarNum();

private:
	CString m_strProvinceFrom;
	CString m_strCityFrom;
	CString m_strCountyFrom;
	CString m_strProvinceTo;
	CString m_strCityTo;
	CString m_strCountyTo;
public:
	afx_msg void OnBnClickedButtonPw1History();
};
