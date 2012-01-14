#pragma once
#include "resource.h"
#include "hoverbutton.h"
#include "afxwin.h"

#include "CountryRegion.h"
#include "GLB.h"

// CPublishWayTwoDlg dialog

class CPublishWayTwoDlg : public CDialog
{
	DECLARE_DYNAMIC(CPublishWayTwoDlg)

public:
	CPublishWayTwoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPublishWayTwoDlg();

// Dialog Data
	enum { IDD = IDD_PUB_WAY_TWO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
	CHoverButton m_btnFromProvince;
	CHoverButton m_btnFromCity;
	CHoverButton m_btnFromCounty;
	CHoverButton m_btnToProvince;
	CHoverButton m_btnToCity;
	CHoverButton m_btnToCounty;

public:
	afx_msg void OnBnClickedButtonW1FromProvince();
	afx_msg void OnBnClickedButtonW1FromCity();
	afx_msg void OnBnClickedButtonW1FromCounty();
	afx_msg void OnBnClickedButtonW1ToProvince();
	afx_msg void OnBnClickedButtonW1ToCity();
	afx_msg void OnBnClickedButtonW1ToCounty();
	afx_msg void OnBnClickedButtonNumOne();
	afx_msg void OnBnClickedButtonNumTwo();
	afx_msg void OnBnClickedButtonNumThree();
	afx_msg void OnBnClickedButtonNumFour();
	afx_msg void OnBnClickedButtonNumFive();
	afx_msg void OnBnClickedButtonNumSix();
	afx_msg void OnBnClickedButtonNumSeven();
	afx_msg void OnBnClickedButtonNumEight();
	afx_msg void OnBnClickedButtonNumNine();
	afx_msg void OnBnClickedButtonNumZero();
	afx_msg void OnBnClickedButtonNumDZero();
	afx_msg void OnBnClickedButtonNumPeriod();
	afx_msg void OnBnClickedButtonNumComma();
	afx_msg void OnBnClickedButtonNumDot();
	afx_msg void OnBnClickedButtonNumSemicolon();
	afx_msg void OnBnClickedButtonNumHyphen();
	afx_msg void OnBnClickedButtonNumSlash();
	afx_msg void OnBnClickedButtonNumRBracket();
	afx_msg void OnBnClickedButtonNumArrow();
	afx_msg void OnBnClickedButtonJi();
	afx_msg void OnBnClickedButtonXu();
	afx_msg void OnBnClickedButtonYao();
	afx_msg void OnBnClickedButtonQiu();
	afx_msg void OnBnClickedButtonFa();
	afx_msg void OnBnClickedButtonDao();
	afx_msg void OnBnClickedButtonHui();
	afx_msg void OnBnClickedButtonQu();
	afx_msg void OnBnClickedButtonChe();
	afx_msg void OnBnClickedButtonHuo();
	afx_msg void OnBnClickedButtonDian();
	afx_msg void OnBnClickedButtonDun();
	afx_msg void OnBnClickedButtonMi();
	afx_msg void OnBnClickedButtonYuan();
	afx_msg void OnBnClickedButtonYuanDun();
	afx_msg void OnBnClickedButtonUnit();
	afx_msg void OnBnClickedButtonBackspace();
	afx_msg void OnBnClickedButtonGood1();
	afx_msg void OnBnClickedButtonGood2();
	afx_msg void OnBnClickedButtonGood3();
	afx_msg void OnBnClickedButtonCarSize();
	afx_msg void OnBnClickedButtonCarType();
	afx_msg void OnBnClickedButtonPrice();
	afx_msg void OnBnClickedButtonPhrase();
	afx_msg void OnBnClickedButtonSpecial();
	afx_msg void OnBnClickedButtonCharacter();
	afx_msg void OnBnClickedButtonWord();

public:
	CComboBox msgType;
	CComboBox shipTime;
	CComboBox repubSetting;

public:
	CString m_strProvinceFrom;
	CString m_strCityFrom;
	CString m_strCountyFrom;
	CString m_strProvinceTo;
	CString m_strCityTo;
	CString m_strCountyTo;
	CString preview;
	CString mobile;
	CString name;
	CString shipTimeValue;
	CString repubSettingValue;
	BOOL autoClose;
	BOOL withoutFrom;
	BOOL withMobile;
	BOOL withName;
	BOOL longTimeAvailable;
	BOOL rememberRepubSetting;

	string	pubInf;

	CountryRegion *myCR;
	UserInfo userInfo;

	int	publishKind;

	CString goodsValue;
	CString goodsCountValue;
	CString truckLengthValue;
	CString truckTypeValue;
	CString truckCountValue;
	CString priceListValue;

private:
	void appendToPreview(CString str);

	void initControlValue();
public:
	afx_msg void OnBnClickedButtonPw2History();
	afx_msg void OnBnClickedButtonPw2Pub();
	afx_msg void OnBnClickedButtonPw2Clean();
	afx_msg void OnBnClickedButtonPw2Close();
	afx_msg void OnCbnSelchangeComboInfoType();
};
