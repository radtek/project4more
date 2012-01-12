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
	ON_LBN_SELCHANGE(IDC_LIST_COUNTY, &CAddrSelDlg::OnLbnSelchangeListCounty)
END_MESSAGE_MAP()


void CAddrSelDlg::InitProvinceList()
{
	if(g_pCountryRegion == NULL)
	{
		return ;
	}

	vector<Province>::iterator it = g_pCountryRegion->govProvince.begin(), end = g_pCountryRegion->govProvince.end();
	for(it; it != end; ++it)
	{
		m_listProvince.AddString((*it).name.c_str());
	}

	if( m_listProvince.GetCount() > 0 )
	{
		m_listProvince.SetCurSel(0);
		m_listProvince.GetText(0, m_sProvince);
		FillCityList(m_sProvince);
	}
}

void CAddrSelDlg::FillCityList(const CString& sProvince)
{
	if( !sProvince.IsEmpty() )
	{
		m_listCity.ResetContent();
		const vector<City>* pVecCity = GetCities(sProvince);
		if(pVecCity != NULL)
		{
			vector<City>::const_iterator it = pVecCity->begin(), end = pVecCity->end();
			for(it; it != end; ++it)
			{
				if( (*it).name != NO_LIMIT_STRING )
				{
					m_listCity.AddString((*it).name.c_str());
				}
			}

			if( m_listCity.GetCount() > 0 )
			{
			//	m_listCity.SetSel(0);
			//	m_selCities.clear();
			//	m_selCities.push_back((*(pVecCity->begin())).name.c_str());
				FillCountyList((*(pVecCity->begin())).name.c_str());
			}
		}
	}
}

void CAddrSelDlg::FillCountyList(const CString& sCity)
{
	m_listCounty.ResetContent();
	const vector<County>* pVecCounty = GetCounties(m_sProvince, sCity);
	if(pVecCounty != NULL)
	{
		tdVecCounty::const_iterator it = pVecCounty->begin(), end = pVecCounty->end();
		for(it; it != end; ++it)
		{
			if( (*it).name != NO_LIMIT_STRING )
			{
				m_listCounty.AddString((*it).name.c_str());
			}
		}
		/*if(m_listCounty.GetCount() > 0 )
		{
		m_listCounty.SetSel(0);
		}*/
	}
}
// CAddrSelDlg message handlers

BOOL CAddrSelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_listProvince.SetColumnWidth(70);
	m_listCity.SetColumnWidth(70);
	m_listCounty.SetColumnWidth(70);

	InitProvinceList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAddrSelDlg::OnBnClickedButtonAllCity()
{
	int nItemCount = m_listCity.GetCount();
	if( nItemCount == 1 )
	{
		m_listCity.SetSel(0);
	}
	else
	{
		m_listCity.SelItemRange(TRUE, 0, nItemCount-1);
	}
}

void CAddrSelDlg::OnBnClickedButtonAllCounty()
{
	if( m_listCity.GetSelCount() == 0 )
	{
		m_listCity.SetSel(0);
	}

	int nItemCount = m_listCounty.GetCount();
	if( nItemCount == 1 )
	{
		m_listCounty.SetSel(0);
	}
	else
	{
		m_listCounty.SelItemRange(TRUE, 0, nItemCount-1);
	}
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
		FillCityList(m_sProvince);
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
		FillCountyList(sCity);
	}
	else if( nSelCount > 1 )
	{
		m_listCounty.ResetContent();

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

void CAddrSelDlg::OnLbnSelchangeListCounty()
{
	if( m_listCity.GetSelCount() == 0 )
	{
		m_listCity.SetSel(0);
		m_selCities.clear();
		CString sCity;
		m_listCity.GetText(0, sCity);
		m_selCities.push_back(sCity);
	}
}
