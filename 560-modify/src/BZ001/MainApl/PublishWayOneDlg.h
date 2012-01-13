#pragma once
#include "resource.h"
#include "hoverbutton.h"
#include "afxwin.h"

#include <vector>
using namespace std;

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

	virtual BOOL OnInitDialog();

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
	CHoverButton m_btnFromProv;
	CHoverButton m_btnFromCity;
	CHoverButton m_btnFromCounty;
	CHoverButton m_btnToProvince;
	CHoverButton m_btnToCity;
	CHoverButton m_btnToCounty;
	CHoverButton m_bntPrice;
	CHoverButton m_btnGoodsNum;
	CHoverButton m_btnCarNum;

	CString m_strProvinceFrom;
	CString m_strCityFrom;
	CString m_strCountyFrom;
	CString m_strProvinceTo;
	CString m_strCityTo;
	CString m_strCountyTo;

public:
	afx_msg void OnBnClickedButtonPw1History();
	afx_msg void OnBnClickedButtonPreview();
	afx_msg void OnBnClickedButtonPw1Pub();
	afx_msg void OnBnClickedButtonPw1Clean();
	afx_msg void OnBnClickedButtonPw1Close();
	afx_msg void OnCbnSelchangeComboPw1InfoType();

private:
	
	void initControlValue();

	void MoveControl(CWnd& control, int dx, int dy);

public:
	CComboBox msgType;
	CComboBox shipTime;
	CComboBox repubSetting;
	BOOL autoClose;
	BOOL rememberRepubSetting;
	BOOL longTimeAvailable;
	BOOL withMobile;
	BOOL withName;
	CString mobile;
	CString name;

	CStatic firstPanel;
	CStatic secondPanel;

	CListBox goodsList;
	CEdit goodsCount;
	CComboBox goodsUnit;

	CListBox truckLength;
	CListBox truckType;
	CEdit truckCount;
	CStatic truckUnit;

	CListBox priceList;
};
