#pragma once
#include "afxwin.h"

#include "CountryRegion.h"
#include "GLB.h"

// CPubSpecialDlg 对话框

class CPubSpecialDlg : public CDialog
{
	DECLARE_DYNAMIC(CPubSpecialDlg)

public:
	CPubSpecialDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPubSpecialDlg();

// 对话框数据
	enum { IDD = IDD_PUB_SPECIAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
// { 自定义
public:
    // 发布信息
    string pubInf;

public:
    // 区域信息
    CountryRegion *myCR;
    // 用户信息
    UserInfo userInfo;

private:
	int initStartPoint();
	int initEndPoint();
// } 
public:
    // 出发地省
    CComboBox combStProvince;
    CString stProvince;
    // 出发地市
    CComboBox combStCity;
    CString stCity;
    // 出发地县
    CComboBox combStCounty;
    CString stCounty;
    // 目的地省
    CComboBox combEnProvince;
    CString enProvince;
    // 目的地市
    CComboBox combEnCity;
    CString enCity;
    // 目的地县
    CComboBox combEnCounty;
    CString enCounty;
    // 重货价格
    CString weightPrice;
    // 泡货价格
    CString lightPrice;
    // 类型
    int type;
    // 运输
    int transport;
    // 发车方式
    CComboBox combSend;
    CString send;
    // 在途时间
    int time;
    // 信息发布
    CString information;
    // 出发地联系人
    CString stName;
    // 出发地地址
    CString stAddress;
    // 出发地电话
    CString stTel;
    // 目的地联系人
    CString enName;
    // 目的地地址
    CString enAddress;
    // 目的地电话
    CString enTel;
    // 是否置顶
    BOOL ifUp;
public:
    afx_msg void OnCbnSelchangePubSpecialStprovince();
public:
    afx_msg void OnCbnSelchangePubSpecialStcity();
public:
    afx_msg void OnCbnSelchangePubSpecialEnprovince();
public:
    afx_msg void OnCbnSelchangePubSpecialEncity();
public:
    afx_msg void OnBnClickedOk();
public:
    virtual BOOL OnInitDialog();
	afx_msg void OnEnChangePubSpecialWeightPrice();
};
