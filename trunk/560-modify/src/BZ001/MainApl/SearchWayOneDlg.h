#pragma once
#include "resource.h"
#include "afxwin.h"
#include "SearchCriteria.h"

// CSearchWayOneDlg dialog

class CSearchWayOneDlg : public CDialog, public CSearchCriteria
{
	DECLARE_DYNAMIC(CSearchWayOneDlg)

public:
	CSearchWayOneDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSearchWayOneDlg();

// Dialog Data
	enum { IDD = IDD_SEARCH_WAY_ONE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioSw1All();
	afx_msg void OnBnClickedRadioSw1Goods();
	afx_msg void OnBnClickedRadioSw1Cars();
	afx_msg void OnBnClickedButtonSw1Select();
	afx_msg void OnBnClickedButtonSw1CleanAddr();
	//afx_msg void OnBnClickedButtonSw1Addr();
	afx_msg void OnBnClickedButtonSw1Goods();
	afx_msg void OnBnClickedButtonSw1CarType();
	afx_msg void OnBnClickedButtonSw1CarSize();
	afx_msg void OnBnClickedButtonSw1GoodsType();
	afx_msg void OnBnClickedButtonSw1CleanPublisher();
	afx_msg void OnBnClickedButtonSw1CleanPhoneNum();
	afx_msg void OnBnClickedRadioMatchAll();
	afx_msg void OnBnClickedRadioMatchAny();
public:
	void Clean();
	void Confirm();
private:
	void InitSearchTypeRadio();
	void FillKeywordCombox();
	void FillPublisherCombox();
	void FillPhoneNumberCombox();
	void UpdateKeyword(const CString& sNewKeyword);

private:
	CComboBox m_comboxPublisher;
	CComboBox m_comboxPhoneNum;
	CComboBox m_comboxKeyword;

	CString m_sDestAddr;

protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

private:
	void ShowContentDialog(int nCtrlID, const vector<CString> *pVec, CString *pStrOut);

	CString m_strContentValue;
};
