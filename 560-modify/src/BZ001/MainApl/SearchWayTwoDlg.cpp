// SearchWayTwoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SearchWayTwoDlg.h"
#include "CommDef.h"
#include "CountryRegion.h"
#include "GLB.h"

extern UserInfo user;


// CSearchWayTwoDlg dialog

IMPLEMENT_DYNAMIC(CSearchWayTwoDlg, CDialog)

CSearchWayTwoDlg::CSearchWayTwoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchWayTwoDlg::IDD, pParent)
{
	m_nSearchType = eSearchType_Goods|eSearchType_Car;
	m_sStartProvince = "�Ĵ�";//user.province.c_str();
	m_sStartCity = "�ɶ�";//user.city.c_str();
}

CSearchWayTwoDlg::~CSearchWayTwoDlg()
{
}

void CSearchWayTwoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SW2_FROM_PROVINCE, m_comboxFromProv);
	DDX_Control(pDX, IDC_COMBO_SW2_FROM_CITY, m_comboxFromCity);
	DDX_Control(pDX, IDC_COMBO_SW2_FROM_COUNTY, m_comboxFromCounty);
	DDX_Control(pDX, IDC_LIST_SW2_TO_PROVINCE, m_listToProvince);
	DDX_Control(pDX, IDC_LIST_SW2_TO_CITY, m_listToCity);
	DDX_Control(pDX, IDC_LIST_SW2_TO_COUNTY, m_listToCounty);
	DDX_Control(pDX, IDC_LIST_SW2_DEST_KEY_WORD, m_listCriteria);
	DDX_Control(pDX, IDC_COMBO4, m_comboxKWPN);
}


BEGIN_MESSAGE_MAP(CSearchWayTwoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SW2_ADD_DEST, &CSearchWayTwoDlg::OnBnClickedButtonSw2AddDest)
	ON_BN_CLICKED(IDC_BUTTON_SW2_ADD_ALL_CITY, &CSearchWayTwoDlg::OnBnClickedButtonSw2AddAllCity)
	ON_BN_CLICKED(IDC_BUTTON_SW2_ADD_ALL_COUNTY, &CSearchWayTwoDlg::OnBnClickedButtonSw2AddAllCounty)
	ON_BN_CLICKED(IDC_BUTTON_SW2_DEL, &CSearchWayTwoDlg::OnBnClickedButtonSw2Del)
	ON_BN_CLICKED(IDC_BUTTON_SW2_CLEAN, &CSearchWayTwoDlg::OnBnClickedButtonSw2Clean)
	ON_BN_CLICKED(IDC_BUTTON_SW2_ADD_KEY_WORD, &CSearchWayTwoDlg::OnBnClickedButtonSw2AddKeyWord)
	ON_BN_CLICKED(IDC_RADIO_SW2_ALL, &CSearchWayTwoDlg::OnBnClickedRadioSw2All)
	ON_BN_CLICKED(IDC_RADIO_SW2_GOODS, &CSearchWayTwoDlg::OnBnClickedRadioSw2Goods)
	ON_BN_CLICKED(IDC_RADIO_SW2_CARS, &CSearchWayTwoDlg::OnBnClickedRadioSw2Cars)
	ON_CBN_SELCHANGE(IDC_COMBO_SW2_FROM_PROVINCE, &CSearchWayTwoDlg::OnCbnSelchangeComboSw2FromProvince)
	ON_CBN_SELCHANGE(IDC_COMBO_SW2_FROM_CITY, &CSearchWayTwoDlg::OnCbnSelchangeComboSw2FromCity)
	ON_CBN_SELCHANGE(IDC_COMBO_SW2_FROM_COUNTY, &CSearchWayTwoDlg::OnCbnSelchangeComboSw2FromCounty)
	ON_LBN_SELCHANGE(IDC_LIST_SW2_TO_PROVINCE, &CSearchWayTwoDlg::OnLbnSelchangeListSw2ToProvince)
	ON_LBN_SELCHANGE(IDC_LIST_SW2_TO_CITY, &CSearchWayTwoDlg::OnLbnSelchangeListSw2ToCity)
	ON_LBN_SELCHANGE(IDC_LIST_SW2_TO_COUNTY, &CSearchWayTwoDlg::OnLbnSelchangeListSw2ToCounty)
END_MESSAGE_MAP()


void CSearchWayTwoDlg::InitFromProvinceList()
{
	int nSel = 0;
	int i = 0;
	vector<Province>::iterator it = g_pCountryRegion->govProvince.begin(), end = g_pCountryRegion->govProvince.end();
	for(it; it != end; ++it, ++i)
	{
		if( m_sStartProvince == (*it).name.c_str() )
		{
			nSel = i;
		}
		m_comboxFromProv.AddString((*it).name.c_str());
	}
	
	m_comboxFromProv.SetCurSel(nSel);
	FillFromCityList(m_sStartProvince);

}

void CSearchWayTwoDlg::FillFromCityList(const CString& sProvince)
{
	if( !sProvince.IsEmpty() )
	{
		m_comboxFromCity.ResetContent();
		const vector<City>* pVecCity = GetCities(sProvince);
		if(pVecCity != NULL)
		{
			int i = 0;
			int nSel = 0;
			vector<City>::const_iterator it = pVecCity->begin(), end = pVecCity->end();
			for(it; it != end; ++it,++i)
			{
				if( (*it).name != NO_LIMIT_STRING )
				{
					if( m_sStartCity == (*it).name.c_str() )
					{
						nSel = i;
					}
					m_comboxFromCity.AddString((*it).name.c_str());
				}
			}

			if( m_comboxFromCity.GetCount() > 0 )
			{
				CString sCity;
				m_comboxFromCity.SetCurSel(nSel);
				m_comboxFromCity.GetLBText(nSel, sCity);
				FillFromCountyList(sProvince, sCity);
			}
		}
	}
}

void CSearchWayTwoDlg::FillFromCountyList(const CString& sProvince, const CString& sCity)
{
	m_comboxFromCounty.ResetContent();
	const vector<County>* pVecCounty = GetCounties(sProvince, sCity);
	if(pVecCounty != NULL)
	{
		tdVecCounty::const_iterator it = pVecCounty->begin(), end = pVecCounty->end();
		for(it; it != end; ++it)
		{
			if( (*it).name != NO_LIMIT_STRING )
			{
				m_comboxFromCounty.AddString((*it).name.c_str());
			}
		}
		if( m_comboxFromCounty.GetCount() > 0 )
		{
			m_comboxFromCounty.SetCurSel(0);
		}
	}
}

void CSearchWayTwoDlg::InitToProvinceList()
{
	if(g_pCountryRegion == NULL)
	{
		return ;
	}

	vector<Province>::iterator it = g_pCountryRegion->govProvince.begin(), end = g_pCountryRegion->govProvince.end();
	for(it; it != end; ++it)
	{
		m_listToProvince.AddString((*it).name.c_str());
	}

	if( m_listToProvince.GetCount() > 0 )
	{
		m_listToProvince.SetCurSel(0);
		m_listToProvince.GetText(0, m_sEndProvince);
		FillToCityList(m_sEndProvince);
	}
}

void CSearchWayTwoDlg::FillToCityList(const CString& sProvince)
{
	if( !sProvince.IsEmpty() )
	{
		m_listToCity.ResetContent();
		const vector<City>* pVecCity = GetCities(sProvince);
		if(pVecCity != NULL)
		{
			vector<City>::const_iterator it = pVecCity->begin(), end = pVecCity->end();
			for(it; it != end; ++it)
			{
				if( (*it).name != NO_LIMIT_STRING )
				{
					m_listToCity.AddString((*it).name.c_str());
				}
			}

			if( m_listToCity.GetCount() > 0 )
			{
			//	m_listCity.SetSel(0);
			//	m_selCities.clear();
			//	m_selCities.push_back((*(pVecCity->begin())).name.c_str());
				FillToCountyList(sProvince, (*(pVecCity->begin())).name.c_str());
			}
		}
	}
}

void CSearchWayTwoDlg::FillToCountyList(const CString& sProvince, const CString& sCity)
{
	m_listToCounty.ResetContent();
	const vector<County>* pVecCounty = GetCounties(sProvince, sCity);
	if(pVecCounty != NULL)
	{
		tdVecCounty::const_iterator it = pVecCounty->begin(), end = pVecCounty->end();
		for(it; it != end; ++it)
		{
			if( (*it).name != NO_LIMIT_STRING )
			{
				m_comboxFromCounty.AddString((*it).name.c_str());
			}
		}
		/*if(m_listCounty.GetCount() > 0 )
		{
		m_listCounty.SetSel(0);
		}*/
	}
}


// CSearchWayTwoDlg message handlers

BOOL CSearchWayTwoDlg::OnInitDialog()
{
	__super::OnInitDialog();

	InitFromProvinceList();
	InitToProvinceList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CSearchWayTwoDlg::OnCbnSelchangeComboSw2FromProvince()
{
	int nSel = m_comboxFromProv.GetCurSel();
	if( nSel != -1 )
	{
		m_comboxFromProv.GetLBText(nSel, m_sStartProvince);
		FillFromCityList(m_sStartProvince);
	}
}

void CSearchWayTwoDlg::OnCbnSelchangeComboSw2FromCity()
{
	int nSel = m_comboxFromCity.GetCurSel();
	if( nSel != -1 )
	{
		m_comboxFromCity.GetLBText(nSel, m_sStartCity);
		FillFromCountyList(m_sStartProvince, m_sStartCity);
	}
}


void CSearchWayTwoDlg::OnCbnSelchangeComboSw2FromCounty()
{
	int nSel = m_comboxFromCounty.GetCurSel();
	if( nSel != -1 )
	{
		m_comboxFromCounty.GetLBText(nSel, m_sStartCounty);
	}
}


void CSearchWayTwoDlg::OnLbnSelchangeListSw2ToProvince()
{
	int nSel = m_listToProvince.GetCurSel();
	if( nSel != -1 )
	{
		m_listToProvince.GetText(nSel, m_sStartProvince);
		FillToCityList(m_sStartProvince);
	}
}


void CSearchWayTwoDlg::OnLbnSelchangeListSw2ToCity()
{
	CString sCity;
	int nSelCount = m_listToCity.GetSelCount();
	if( nSelCount == 1 )
	{
		m_listToCity.GetText(m_listToCity.GetCurSel(), sCity);
		FillFromCountyList(m_sEndProvince, sCity);
	}
	else if( nSelCount > 1 )
	{
	/*	m_listCounty.ResetContent();

		int *pItems = new int[nSelCount];
		m_listCity.GetSelItems(nSelCount, pItems);
		for(int i = 0; i<nSelCount; ++i)
		{
			m_listCity.GetText(pItems[i], sCity);
			m_selCities.push_back(sCity);
		}
		delete []pItems;*/
	}
}

void CSearchWayTwoDlg::OnLbnSelchangeListSw2ToCounty()
{
	// TODO: Add your control notification handler code here
}


void CSearchWayTwoDlg::OnBnClickedButtonSw2AddDest()
{
	CString sAddr;
	int nSel = m_listToCounty.GetSelCount();
	if( nSel > 0 )
	{
		int *pItems = new int[nSel];
		m_listToCounty.GetSelItems(nSel, pItems);
		for(int i = 0; i<nSel; ++i)
		{
			m_listToCounty.GetText(pItems[i], sAddr);
			if( find(m_selCounties.begin(), m_selCounties.end(), sAddr) == m_selCounties.end() )
			{
				m_selCounties.push_back(sAddr);
				m_listCriteria.AddString(sAddr);
			}
		}
		delete []pItems;

		m_listToCounty.GetText(0, m_sEndCounty);
	}
	else if( (nSel = m_listToCity.GetSelCount()) > 0 )
	{
		int *pItems = new int[nSel];
		m_listToCity.GetSelItems(nSel, pItems);
		for(int i = 0; i<nSel; ++i)
		{
			m_listToCity.GetText(pItems[i], sAddr);
			if( find(m_selCities.begin(), m_selCities.end(), sAddr) == m_selCities.end() )
			{
				m_selCities.push_back(sAddr);
				m_listCriteria.AddString(sAddr);
			}
		}
		delete []pItems;

		m_listToCity.GetText(0, m_sEndCity);
	}
	else if( (nSel = m_listToProvince.GetCurSel()) != -1 )
	{
		//m_listToProvince.GetText(nSel, m_sEndProvince);
	}

}

void CSearchWayTwoDlg::OnBnClickedButtonSw2AddAllCity()
{
	CString sCity;
	int nCount = m_listToCity.GetCount();
	for(int i = 0; i<nCount; ++i)
	{
		m_listToCity.GetText(i, sCity);
		if( find(m_selCities.begin(), m_selCities.end(), sCity) == m_selCities.end() )
		{
			m_selCities.push_back(sCity);
			m_listCriteria.AddString(sCity);
		}
	}

	m_listToCity.GetText(0, m_sEndCity);

}

void CSearchWayTwoDlg::OnBnClickedButtonSw2AddAllCounty()
{
	CString sCounty;
	int nCount = m_listToCounty.GetCount();
	for(int i = 0; i<nCount; ++i)
	{
		m_listToCounty.GetText(i, sCounty);
		if( find(m_selCounties.begin(), m_selCounties.end(), sCounty) == m_selCounties.end() )
		{
			m_selCounties.push_back(sCounty);
			m_listCriteria.AddString(sCounty);
		}
	}

	m_listToCounty.GetText(0, m_sEndCounty);
}

void CSearchWayTwoDlg::OnBnClickedButtonSw2Del()
{
	
}

void CSearchWayTwoDlg::OnBnClickedButtonSw2Clean()
{
	Clean();
}

void CSearchWayTwoDlg::OnBnClickedButtonSw2AddKeyWord()
{
	// TODO: Add your control notification handler code here
}

void CSearchWayTwoDlg::OnBnClickedRadioSw2All()
{
	m_nSearchType = eSearchType_Goods|eSearchType_Car;
}

void CSearchWayTwoDlg::OnBnClickedRadioSw2Goods()
{
	m_nSearchType = eSearchType_Goods;
}

void CSearchWayTwoDlg::OnBnClickedRadioSw2Cars()
{
	m_nSearchType = eSearchType_Car;
}

void CSearchWayTwoDlg::Clean()
{
	m_listCriteria.ResetContent();
	m_selCities.clear();
	m_selCounties.clear();
	m_sEndProvince.Empty();
	m_sEndCity.Empty();
	m_sEndCounty.Empty();
}