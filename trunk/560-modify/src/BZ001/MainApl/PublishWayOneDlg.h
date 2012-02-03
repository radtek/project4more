#pragma once
#include "resource.h"
#include "hoverbutton.h"
#include "afxwin.h"

#include "CountryRegion.h"
#include "GLB.h"

#include "PubHistoryDlg.h"

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
	afx_msg void OnBnClickedButtonPw1History();
	afx_msg void OnBnClickedButtonPreview();
	afx_msg void OnBnClickedButtonPw1Pub();
	afx_msg void OnBnClickedButtonPw1Clean();
	afx_msg void OnBnClickedButtonPw1Close();
	afx_msg void OnCbnSelchangeComboPw1InfoType();

private:	// control variables
	CHoverButton m_btnFromProv;
	CHoverButton m_btnFromCity;
	CHoverButton m_btnFromCounty;
	CHoverButton m_btnToProvince;
	CHoverButton m_btnToCity;
	CHoverButton m_btnToCounty;
	CHoverButton m_bntPrice;
	CHoverButton m_btnGoodsNum;
	CHoverButton m_btnCarNum;

	CComboBox msgType;
	CComboBox shipTime;
	CComboBox repubSetting;

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

public:		// value variables
	CString m_strProvinceFrom;
	CString m_strCityFrom;
	CString m_strCountyFrom;
	CString m_strProvinceTo;
	CString m_strCityTo;
	CString m_strCountyTo;

	BOOL autoClose;
	BOOL rememberRepubSetting;
	BOOL longTimeAvailable;
	BOOL withMobile;
	BOOL withMobile2;
	CString mobile;
	CString mobile2;

	CString goodsValue;
	CString goodsCountValue;
	CString goodsUnitValue;

	CString truckLengthValue;
	CString truckTypeValue;
	CString truckCountValue;

	CString priceCountValue;
	CString priceListValue;
	CString preview;
	CString shipTimeValue;
	CString repubSettingValue;

	string	pubInf;
	int		publishKind;

	CountryRegion *myCR;
	UserInfo userInfo;

private:

	BOOL				bPreview;
	CPublishRecord*		pRecord;
	CPublishRecord*		pPublishRecord;

	void initControlValue();

	void MoveControl(CWnd& control, int dx, int dy);
	void MoveAllControl();

	void BuildGoodsPreview();

	void BuildTruckPreview();

	BOOL CheckGoodsInfo();

	BOOL CheckTruckInfo();

	BOOL PublishGoodsInfo();

	BOOL PublishTruckInfo();

	void ToHistory();

	void FromHistory();

	void SetComboSection(CComboBox& b, string k);

	void SetListSection(CListBox& b, string k);
public:
	afx_msg void OnBnClickedButtonPriaceNum();
	void	SaveHistory();
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
