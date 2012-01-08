#pragma once

#include "CountryRegion.h"

// CSearchCarsDlg 对话框

class CSearchCarsDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchCarsDlg)

public:
	CSearchCarsDlg(CWnd* pParent = NULL);   // 标准构造函数  
	virtual ~CSearchCarsDlg();

// 对话框数据
	enum { IDD = IDD_SEARCH_CARS };

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
    // 车长
    CComboBox carLength;
    CString strCarLength;
    // 车类型
    CComboBox carType;
    CString strCarType;
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
