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
	m_sStartProvince = "ËÄ´¨";//user.province.c_str();
	m_sStartCity = "³É¶¼";//user.city.c_str();
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
				FillToCountyList(sProvince, sCity);
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
				m_listToCounty.AddString((*it).name.c_str());
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

void CSearchWayTwoDlg::OnBnClickedButtonSw2AddDest()
{
	// TODO: Add your control notification handler code here
}

void CSearchWayTwoDlg::OnBnClickedButtonSw2AddAllCity()
{
	// TODO: Add your control notification handler code here
}

void CSearchWayTwoDlg::OnBnClickedButtonSw2AddAllCounty()
{
	// TODO: Add your control notification handler code here
}

void CSearchWayTwoDlg::OnBnClickedButtonSw2Del()
{
	// TODO: Add your control notification handler code here
}

void CSearchWayTwoDlg::OnBnClickedButtonSw2Clean()
{
	// TODO: Add your control notification handler code here
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
