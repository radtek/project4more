#pragma once
#include "afxwin.h"

#include "CountryRegion.h"
#include "GLB.h"

// CPubBulkGoodsDlg 对话框

class CPubBulkGoodsDlg : public CDialog
{
	DECLARE_DYNAMIC(CPubBulkGoodsDlg)

public:
	CPubBulkGoodsDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPubBulkGoodsDlg();

// 对话框数据
	enum { IDD = IDD_PUB_BULKGOODS };

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
	int initSynPoint();
// }   

public:
    // 出发地省
    CComboBox combStProvince;
    CString stProvince;
    // 出发地市
    CComboBox combStCity;
    CString stCity;
    // 出发地区/县
    CComboBox combStCounty;
    CString stCounty;
    // 目的地省
    CComboBox combEnProvince;
    CString enProvince;
    // 目的地市
    CComboBox combEnCity;
    CString enCity;
    // 目的地区/县
    CComboBox combEnCounty;
    CString enCounty;
    // 货源名称
    CComboBox combName;
    CString name;
    // 货源重量
    CString weight;
    // 重量单位
    CComboBox combWeightUnit;
    CString weightUnit;
    // 车类型
    CComboBox combCarType;
    CString carType; 
    // 联系电话
    CString tel;
    // 预览信息
    CString preview;
    // 同时发布的省
    CComboBox combSyProvince;
    CString syProvince;
    // 同时发布的市
    CComboBox combSyCity;
    CString syCity;
    // 重发设置
    CComboBox combRePubType;
    CString rePubType;
    // 是否记住重发设置。（1：是  0：否，默认为0）
    BOOL ifRemRePub;
    // 是否长期有效。（默认：24小时、72小时、长期有效）
    BOOL ifLongTime;
    // 是否置顶。（1：是  0：否，默认为0）
    BOOL ifUp;
	//是否预览
	BOOL bPreview;
public:
    afx_msg void OnBnClickedPubGoodsPreviewBtn();
    afx_msg void OnCbnSelchangePubGoodsStprovince();
    afx_msg void OnCbnSelchangePubGoodsStcity();
    afx_msg void OnCbnSelchangePubGoodsEnprovince();
    afx_msg void OnCbnSelchangePubGoodsEncity();
    afx_msg void OnCbnSelchangePubGoodsSyprovince();
public:
    virtual BOOL OnInitDialog();
public:
    afx_msg void OnBnClickedOk();
	CEdit m_msgedit;
};
