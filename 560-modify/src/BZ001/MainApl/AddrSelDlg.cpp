// AddrSelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AddrSelDlg.h"
#include "CommDef.h"
#include "CountryRegion.h"
// CAddrSelDlg dialog

IMPLEMENT_DYNAMIC(CAddrSelDlg, CDialog)

CAddrSelDlg::CAddrSelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddrSelDlg::IDD, pParent)
{

}

CAddrSelDlg::~CAddrSelDlg()
{
}

void CAddrSelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROVINCE, m_listProvince);
	DDX_Control(pDX, IDC_LIST_CITY, m_listCity);
	DDX_Control(pDX, IDC_LIST_COUNTY, m_listCounty);
}


BEGIN_MESSAGE_MAP(CAddrSelDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ALL_CITY, &CAddrSelDlg::OnBnClickedButtonAllCity)
	ON_BN_CLICKED(IDC_BUTTON_ALL_COUNTY, &CAddrSelDlg::OnBnClickedButtonAllCounty)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CAddrSelDlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CAddrSelDlg::OnBnClickedButtonCancel)
	ON_LBN_SELCHANGE(IDC_LIST_PROVINCE, &CAddrSelDlg::OnLbnSelchangeListProvince)
	ON_LBN_SELCHANGE(IDC_LIST_CITY, &CAddrSelDlg::OnLbnSelchangeListCity)
END_MESSAGE_MAP()


void CAddrSelDlg::InitProvinceList()
{
	m_listProvince.SetColumnWidth(70);
	if(g_pCountryRegion == NULL)
	{
		return ;
	}

	vector<Province>::iterator it = g_pCountryRegion->govProvince.begin(), end = g_pCountryRegion->govProvince.end();
	for(it; it != end; ++it)
	{
		m_listProvince.AddString((*it).name.c_str());
	}

	//tdMapProvince::const_iterator it = g_mapProvince.begin(), end = g_mapProvince.end();
	//for(it; it != end; ++it)
	//{
	//	m_listProvince.AddString((*it).first);
	//}
}

void CAddrSelDlg::FillCityList()
{
	if( !m_sProvince.IsEmpty() )
	{
		m_listCity.ResetContent();
		const vector<City>* pVecCity = GetCities(m_sProvince);
		if(pVecCity != NULL)
		{
			vector<City>::const_iterator it = pVecCity->begin(), end = pVecCity->end();
			for(it; it != end; ++it)
			{
				m_listCity.AddString((*it).name.c_str());
			}
		}
	}
}

void CAddrSelDlg::FillCountyList()
{
	m_listCounty.ResetContent();
	if( m_selCities.size() == 1 )
	{
		m_listCounty.ResetContent();
		const vector<County>* pVecCounty = GetCounties(m_sProvince, *m_selCities.begin());
		if(pVecCounty != NULL)
		{
			tdVecCounty::const_iterator it = pVecCounty->begin(), end = pVecCounty->end();
			for(it; it != end; ++it)
			{
				m_listCounty.AddString((*it).name.c_str());
			}
		}
	}
}
// CAddrSelDlg message handlers

BOOL CAddrSelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitProvinceList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAddrSelDlg::OnBnClickedButtonAllCity()
{
	int nItemCount = m_listCity.GetCount();
	m_listCity.SelItemRange(TRUE, 0, nItemCount-1);
}

void CAddrSelDlg::OnBnClickedButtonAllCounty()
{
	int nItemCount = m_listCounty.GetCount();
	m_listCounty.SelItemRange(TRUE, 0, nItemCount-1);
}

void CAddrSelDlg::OnBnClickedButtonOk()
{
	m_selCounties.clear();

	CString sCounty;
	int nSelCount = m_listCounty.GetSelCount();
	if( nSelCount == 1 )
	{
		m_listCounty.GetText(m_listCounty.GetCurSel(), sCounty);
		m_selCounties.push_back(sCounty);
	}
	else if( nSelCount > 1 )
	{
		int *pItems = new int[nSelCount];
		m_listCounty.GetSelItems(nSelCount, pItems);
		for(int i = 0; i<nSelCount; ++i)
		{
			m_listCounty.GetText(pItems[i], sCounty);
			m_selCounties.push_back(sCounty);
		}
		delete []pItems;
	}
	CDialog::OnOK();
}

void CAddrSelDlg::OnBnClickedButtonCancel()
{
	m_sProvince.Empty();
	m_selCities.clear();
	m_selCounties.clear();
	CDialog::OnCancel();
}

void CAddrSelDlg::OnLbnSelchangeListProvince()
{
	int nSel = m_listProvince.GetCurSel();
	if( nSel != -1 )
	{
		m_listProvince.GetText(nSel, m_sProvince);
		FillCityList();
	}
}

void CAddrSelDlg::OnLbnSelchangeListCity()
{
	m_selCities.clear();

	CString sCity;
	int nSelCount = m_listCity.GetSelCount();
	if( nSelCount == 1 )
	{
		m_listCity.GetText(m_listCity.GetCurSel(), sCity);
		m_selCities.push_back(sCity);
		FillCountyList();
	}
	else if( nSelCount > 1 )
	{
		int *pItems = new int[nSelCount];
		m_listCity.GetSelItems(nSelCount, pItems);
		for(int i = 0; i<nSelCount; ++i)
		{
			m_listCity.GetText(pItems[i], sCity);
			m_selCities.push_back(sCity);
		}
		delete []pItems;
	}
}
