#pragma once
#include "resource.h"
#include "afxwin.h"
#include "CountryRegion.h"
#include <string>
#include <map>
#include <list>
#include <vector>
using std::map;
using std::list;
using std::vector;
// CAddrSelDlg dialog

class CAddrSelDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddrSelDlg)

public:
	CAddrSelDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddrSelDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_ADDR_SEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAllCity();
	afx_msg void OnBnClickedButtonAllCounty();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnLbnSelchangeListProvince();
	afx_msg void OnLbnSelchangeListCity();
public:
	const CString& GetSelProvince()const
	{
		return m_sProvince;
	}
	const list<CString>& GetSelCities()const
	{
		return m_selCities;
	}
	const list<CString>& GetSelCounties()const
	{
		return m_selCounties;
	}
private:
	void InitProvinceList();
	void FillCityList(const CString& sProvince);
	void FillCountyList(const CString& sCity);
private:
	CListBox m_listProvince;
	CListBox m_listCity;
	CListBox m_listCounty;
	CString	 m_sProvince;
	list<CString> m_selCities;
	list<CString> m_selCounties;
public:
	afx_msg void OnLbnSelchangeListCounty();
};
