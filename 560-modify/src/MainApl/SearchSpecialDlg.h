#pragma once

#include "CountryRegion.h"

// CSearchSpecialDlg 对话框

class CSearchSpecialDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchSpecialDlg)

public:
	CSearchSpecialDlg(CWnd* pParent = NULL);   // 标准构造函数  
	virtual ~CSearchSpecialDlg();

// 对话框数据
	enum { IDD = IDD_SEARCH_SPECIAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
// { 自定义
public:
    // 区域信息
    CountryRegion *myCR;
private:    
    // 初始化出发地
	int initStartPoint();
    // 初始化到达地
	int initEndPoint();
// }
public:
    // 出发省
    CComboBox startProvince;
    CString strStartProvince;
    // 出发市
    CComboBox startCity;
    CString strStartCity;
    // 出发县
    CComboBox startCounty;
    CString strStartCounty;
    // 到达省
    CComboBox endProvince;
    CString strEndProvince;
    // 到达市
    CComboBox endCity;
    CString strEndCity;
    // 到达县
    CComboBox endCounty;
    CString strEndCounty;

public:
    virtual BOOL OnInitDialog();
public:
    afx_msg void OnCbnSelchangeStartProvince();
    afx_msg void OnCbnSelchangeStartCity();
    afx_msg void OnCbnSelchangeEndProvince();
    afx_msg void OnCbnSelchangeEndCity();

    
public:
    afx_msg void OnBnClickedOk();
};
