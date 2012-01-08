#pragma once

#include "CountryRegion.h"

// CAddCustomZoneDlg 对话框

class CAddCustomZoneDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddCustomZoneDlg)

public:
	CAddCustomZoneDlg(CWnd* pParent = NULL);   // 标准构造函数  
	virtual ~CAddCustomZoneDlg();

// 对话框数据
	enum { IDD = IDD_ADD_CUSTOM_ZONE };

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
    // 到达省
    CComboBox endProvince;
    CString strEndProvince;
    // 到达市
    CComboBox endCity;
    CString strEndCity;

public:
    virtual BOOL OnInitDialog();
public:
    afx_msg void OnCbnSelchangeStartProvince();
    afx_msg void OnCbnSelchangeEndProvince();
    
public:
    afx_msg void OnBnClickedOk();
};