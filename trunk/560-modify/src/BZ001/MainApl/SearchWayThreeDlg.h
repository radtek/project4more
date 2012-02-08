#pragma once
#include "resource.h"
#include "SearchCriteria.h"
#include "afxwin.h"

// CSearchWayThreeDlg dialog

class CSearchWayThreeDlg : public CDialog, public CSearchCriteria
{
	DECLARE_DYNAMIC(CSearchWayThreeDlg)

public:
	CSearchWayThreeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSearchWayThreeDlg();

// Dialog Data
	enum { IDD = IDD_SEARCH_WAY_THREE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadioSw3All();
	afx_msg void OnBnClickedRadioSw3Goods();
	afx_msg void OnBnClickedRadioSw3Cars();
	afx_msg void OnBnClickedButtonSw3AddFromAddr();
	afx_msg void OnBnClickedButtonSw3AddAllCity();
	afx_msg void OnBnClickedButtonSw3AddAllCounty();
	afx_msg void OnBnClickedButtonSw3Del();
	afx_msg void OnBnClickedButtonSw3Clean();
	afx_msg void OnBnClickedButtonSw3CleanKeyWord();
	afx_msg void OnBnClickedButtonSw3Backspace();
	//afx_msg void OnBnClickedButtonSw3Addr();
	afx_msg void OnBnClickedButtonSw3Goods();
	afx_msg void OnBnClickedButtonSw3CarType();
	afx_msg void OnBnClickedButtonSw3CarSize();
	afx_msg void OnBnClickedButtonSw3GoodsType();
	afx_msg void OnLbnSelchangeListSw3FromProvince();
	afx_msg void OnLbnSelchangeListSw3FromCity();
	afx_msg void OnLbnSelchangeListSw3FromCounty();
private:
	void InitSearchTypeRadio();

	void InitFromProvinceList();
	void FillFromCityList(const CString& sProvince);
	void FillFromCountyList(const CString& sProvince, const CString& sCity);

	void FillKeywordCombox();

	void Clean();
	void Confirm();

	void UpdateKeyword(const CString& sNewKeyword);
private:
	enum{eItemData_Province, eItemData_City, eItemData_County};
	CListBox m_lstFromProv;
	CListBox m_lstFromCity;
	CListBox m_lstFromCounty;
	CListBox m_lstFromAddr;
	CComboBox m_comboxKeyword;

	CString m_sSelStartProv;

protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

private:
	void ShowContentDialog(int nCtrlID, const vector<CString> *pVec, CString *pStrOut);

	CString m_strContentValue;
};
