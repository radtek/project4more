// SearchWayThreeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SearchWayThreeDlg.h"
#include "AddrSelDlg.h"
#include "CommDef.h"
#include "GLB.h"
#include "ContentDlg.h"

extern UserInfo user;



// CSearchWayThreeDlg dialog

IMPLEMENT_DYNAMIC(CSearchWayThreeDlg, CDialog)

CSearchWayThreeDlg::CSearchWayThreeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchWayThreeDlg::IDD, pParent)
{

}

CSearchWayThreeDlg::~CSearchWayThreeDlg()
{
}

void CSearchWayThreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SW3_FROM_PROVINCE, m_lstFromProv);
	DDX_Control(pDX, IDC_LIST_SW3_FROM_CITY, m_lstFromCity);
	DDX_Control(pDX, IDC_LIST_SW3_FROM_COUNTY, m_lstFromCounty);
	DDX_Control(pDX, IDC_LIST_SW3_FROM_ADDR, m_lstFromAddr);
	DDX_Control(pDX, IDC_COMBO_SW3_KEY_WORD, m_comboxKeyword);
}


BEGIN_MESSAGE_MAP(CSearchWayThreeDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO_SW3_ALL, &CSearchWayThreeDlg::OnBnClickedRadioSw3All)
	ON_BN_CLICKED(IDC_RADIO_SW3_GOODS, &CSearchWayThreeDlg::OnBnClickedRadioSw3Goods)
	ON_BN_CLICKED(IDC_RADIO_SW3_CARS, &CSearchWayThreeDlg::OnBnClickedRadioSw3Cars)
	ON_BN_CLICKED(IDC_BUTTON_SW3_ADD_FROM_ADDR, &CSearchWayThreeDlg::OnBnClickedButtonSw3AddFromAddr)
	ON_BN_CLICKED(IDC_BUTTON_SW3_ADD_ALL_CITY, &CSearchWayThreeDlg::OnBnClickedButtonSw3AddAllCity)
	ON_BN_CLICKED(IDC_BUTTON_SW3_ADD_ALL_COUNTY, &CSearchWayThreeDlg::OnBnClickedButtonSw3AddAllCounty)
	ON_BN_CLICKED(IDC_BUTTON_SW3_DEL, &CSearchWayThreeDlg::OnBnClickedButtonSw3Del)
	ON_BN_CLICKED(IDC_BUTTON_SW3_CLEAN, &CSearchWayThreeDlg::OnBnClickedButtonSw3Clean)
	ON_BN_CLICKED(IDC_BUTTON_SW3_CLEAN_KEY_WORD, &CSearchWayThreeDlg::OnBnClickedButtonSw3CleanKeyWord)
	ON_BN_CLICKED(IDC_BUTTON_SW3_BACKSPACE, &CSearchWayThreeDlg::OnBnClickedButtonSw3Backspace)
	ON_BN_CLICKED(IDC_BUTTON_SW3_ADDR, &CSearchWayThreeDlg::OnBnClickedButtonSw3Addr)
	ON_BN_CLICKED(IDC_BUTTON_SW3_GOODS, &CSearchWayThreeDlg::OnBnClickedButtonSw3Goods)
	ON_BN_CLICKED(IDC_BUTTON_SW3_CAR_TYPE, &CSearchWayThreeDlg::OnBnClickedButtonSw3CarType)
	ON_BN_CLICKED(IDC_BUTTON_SW3_CAR_SIZE, &CSearchWayThreeDlg::OnBnClickedButtonSw3CarSize)
	ON_BN_CLICKED(IDC_BUTTON_SW3_GOODS_TYPE, &CSearchWayThreeDlg::OnBnClickedButtonSw3GoodsType)
	ON_LBN_SELCHANGE(IDC_LIST_SW3_FROM_PROVINCE, &CSearchWayThreeDlg::OnLbnSelchangeListSw3FromProvince)
	ON_LBN_SELCHANGE(IDC_LIST_SW3_FROM_CITY, &CSearchWayThreeDlg::OnLbnSelchangeListSw3FromCity)
	ON_LBN_SELCHANGE(IDC_LIST_SW3_FROM_COUNTY, &CSearchWayThreeDlg::OnLbnSelchangeListSw3FromCounty)
	
END_MESSAGE_MAP()



void CSearchWayThreeDlg::InitSearchTypeRadio()
{
	((CButton*)GetDlgItem(IDC_RADIO_SW3_ALL))->SetCheck(m_nSearchType == (eSearchType_Goods|eSearchType_Car)?BST_CHECKED:BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_SW3_GOODS))->SetCheck(m_nSearchType == eSearchType_Goods?BST_CHECKED:BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_SW3_CARS))->SetCheck(m_nSearchType == eSearchType_Car?BST_CHECKED:BST_UNCHECKED);
}

void CSearchWayThreeDlg::InitFromProvinceList()
{
	int i = 0;
	vector<Province>::iterator it = g_pCountryRegion->govProvince.begin(), end = g_pCountryRegion->govProvince.end();
	for(it; it != end; ++it, ++i)
	{
		m_lstFromProv.AddString((*it).name.c_str());
	}
	
	if( m_lstFromProv.GetCount() > 0 )
	{
		m_sSelStartProv = (*g_pCountryRegion->govProvince.begin()).name.c_str();
		m_lstFromProv.SetCurSel(0);
		FillFromCityList(m_sSelStartProv);
	}

}

void CSearchWayThreeDlg::FillFromCityList(const CString& sProvince)
{
	if( !sProvince.IsEmpty() )
	{
		m_lstFromCity.ResetContent();
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
					m_lstFromCity.AddString((*it).name.c_str());
				}
			}

			if( m_lstFromCity.GetCount() > 0 )
			{
				CString sCity;
				//m_lstFromCity.SetSel(0);
				m_lstFromCity.GetText(nSel, sCity);
				FillFromCountyList(sProvince, sCity);
			}
		}
	}
}

void CSearchWayThreeDlg::FillFromCountyList(const CString& sProvince, const CString& sCity)
{
	m_lstFromCounty.ResetContent();
	const vector<County>* pVecCounty = GetCounties(sProvince, sCity);
	if(pVecCounty != NULL)
	{
		tdVecCounty::const_iterator it = pVecCounty->begin(), end = pVecCounty->end();
		for(it; it != end; ++it)
		{
			if( (*it).name != NO_LIMIT_STRING )
			{
				m_lstFromCounty.AddString((*it).name.c_str());
			}
		}
		/*if( m_comboxFromCounty.GetCount() > 0 )
		{
			m_comboxFromCounty.SetCurSel(0);
		}*/
	}
}

BOOL CSearchWayThreeDlg::OnInitDialog()
{
	__super::OnInitDialog();

	AddEndProvice(user.province.c_str());
	AddEndCity(user.city.c_str());

	InitSearchTypeRadio();
	InitFromProvinceList();

	GetDlgItem(IDC_STATIC_SW3_DEST_ADDR)->SetWindowText(user.city.empty()?user.province.c_str():user.city.c_str());

	return TRUE;  // return TRUE unless you set the focus to a control
	// “Ï≥£: OCX  Ù–‘“≥”¶∑µªÿ FALSE
}


void CSearchWayThreeDlg::OnLbnSelchangeListSw3FromProvince()
{
	int nSel = m_lstFromProv.GetCurSel();
	if( nSel != -1 )
	{
		m_lstFromProv.GetText(nSel, m_sSelStartProv);
		FillFromCityList(m_sSelStartProv);
	}
}

void CSearchWayThreeDlg::OnLbnSelchangeListSw3FromCity()
{
	int nSel = m_lstFromCity.GetCurSel();
	if(nSel != -1)
	{
		CString sCity;
		m_lstFromCity.GetText(nSel, sCity);
		FillFromCountyList(m_sSelStartProv, sCity);
	}
}

void CSearchWayThreeDlg::OnLbnSelchangeListSw3FromCounty()
{
	if( m_lstFromCity.GetCount() == 0 )
	{
		m_lstFromCity.SetCurSel(0);
	}
}


void CSearchWayThreeDlg::OnBnClickedRadioSw3All()
{
	m_nSearchType = eSearchType_Goods|eSearchType_Car;
}

void CSearchWayThreeDlg::OnBnClickedRadioSw3Goods()
{
	m_nSearchType = eSearchType_Goods;
}

void CSearchWayThreeDlg::OnBnClickedRadioSw3Cars()
{
	m_nSearchType = eSearchType_Car;
}

void CSearchWayThreeDlg::OnBnClickedButtonSw3AddFromAddr()
{
	CString sAddr;
	int nSel = m_lstFromCounty.GetSelCount();
	if( nSel > 0 )
	{
		int *pItems = new int[nSel];
		m_lstFromCounty.GetSelItems(nSel, pItems);
		for(int i = 0; i<nSel; ++i)
		{
			m_lstFromCounty.GetText(pItems[i], sAddr);
			if( AddStartCounty(sAddr) )
			{
				m_lstFromAddr.AddString(sAddr);
				m_lstFromAddr.SetItemData(m_lstFromAddr.GetCount()-1, eItemData_County);
			}
		}
		delete []pItems;
	}
	else if( (nSel = m_lstFromCity.GetSelCount()) > 0 )
	{
		int *pItems = new int[nSel];
		m_lstFromCity.GetSelItems(nSel, pItems);
		for(int i = 0; i<nSel; ++i)
		{
			m_lstFromCity.GetText(pItems[i], sAddr);
			if( AddStartCity(sAddr) )
			{
				m_lstFromAddr.AddString(sAddr);
				m_lstFromAddr.SetItemData(m_lstFromAddr.GetCount()-1, eItemData_City);
			}
		}
		delete []pItems;
	}
	else if( (nSel = m_lstFromProv.GetCurSel()) != -1 )
	{
		//m_listToProvince.GetText(nSel, m_sEndProvince);
	}
}

void CSearchWayThreeDlg::OnBnClickedButtonSw3AddAllCity()
{
	CString sCity;
	int nCount = m_lstFromCity.GetCount();
	for(int i = 0; i<nCount; ++i)
	{
		m_lstFromCity.GetText(i, sCity);
		if( AddStartCity(sCity) )
		{
			m_lstFromAddr.AddString(sCity);
			m_lstFromAddr.SetItemData(m_lstFromAddr.GetCount()-1, eItemData_City);
		}
	}
}

void CSearchWayThreeDlg::OnBnClickedButtonSw3AddAllCounty()
{
	CString sCounty;
	int nCount = m_lstFromCounty.GetCount();
	for(int i = 0; i<nCount; ++i)
	{
		m_lstFromCounty.GetText(i, sCounty);
		if( AddStartCounty(sCounty) )
		{
			m_lstFromAddr.AddString(sCounty);
			m_lstFromAddr.SetItemData(m_lstFromAddr.GetCount()-1, eItemData_County);
		}
	}
}

void CSearchWayThreeDlg::OnBnClickedButtonSw3Del()
{
	int nSel = m_lstFromAddr.GetCurSel();
	if( nSel != -1 )
	{
		CString sItemData;
		m_lstFromAddr.GetText(nSel, sItemData);
		int nItemData = m_lstFromAddr.GetItemData(nSel);
		if( nItemData == eItemData_City )
		{
			RemoveStartCity(sItemData);
		}
		else if( nItemData == eItemData_County )
		{
			RemoveStartCounty(sItemData);
		}
		m_lstFromAddr.DeleteString(nSel);		
	}
}

void CSearchWayThreeDlg::OnBnClickedButtonSw3Clean()
{
	Clean();
}

void CSearchWayThreeDlg::OnBnClickedButtonSw3CleanKeyWord()
{
	m_comboxKeyword.SetWindowText(_T(""));
}

void CSearchWayThreeDlg::OnBnClickedButtonSw3Backspace()
{
	CString sKeyword;
	m_comboxKeyword.GetWindowText(sKeyword);
	sKeyword.Delete(sKeyword.GetLength()-1);
	m_comboxKeyword.SetWindowText(sKeyword);
}

void CSearchWayThreeDlg::OnBnClickedButtonSw3Addr()
{
	CAddrSelDlg dlg;
	if( dlg.DoModal() == IDOK )
	{
		CString sDestAddr(dlg.GetSelProvince());

		const list<CString>& cityList = dlg.GetSelCities();
		if( cityList.size() > 0 )
		{
			sDestAddr.Empty();

			list<CString>::const_iterator it = cityList.begin(), end = cityList.end();
			for(it; it != end; ++it)
			{
				sDestAddr += *it + _T(" ");
			}

			const list<CString>& countyList = dlg.GetSelCounties();
			if(countyList.size() > 0)
			{
				sDestAddr.Empty();

				it = countyList.begin(), end = countyList.end();
				for(it; it != end; ++it)
				{
					sDestAddr += *it + _T(" ");
				}
			}
		}
		UpdateKeyword(sDestAddr);
	}
}

void CSearchWayThreeDlg::OnBnClickedButtonSw3Goods()
{
	vector<CString> vecGoods;
	vecGoods.push_back(NO_LIMIT_STRING);
	vecGoods.push_back("≤‚ ‘");
	vecGoods.push_back("≤‚ ‘1");
	CString sGoods;
	CContentDlg dlg(GetParent(), GetDlgItem(IDC_BUTTON_SW3_GOODS), &vecGoods, &sGoods);
	//CWnd* pCtrl = GetDlgItem(IDC_BUTTON_SW1_GOODS);
	if( dlg.DoModal() == IDOK )
	{
		AddGoods(sGoods);
		UpdateKeyword(sGoods);
	}
}


void CSearchWayThreeDlg::OnBnClickedButtonSw3GoodsType()
{
	vector<CString> vecGoodsType;
	vecGoodsType.push_back(NO_LIMIT_STRING);

	CString sGoodsType;
	CContentDlg dlg(this, GetDlgItem(IDC_BUTTON_SW3_GOODS_TYPE), &vecGoodsType, &sGoodsType);
	if( dlg.DoModal() == IDOK )
	{
		AddGoodsType(sGoodsType);
		UpdateKeyword(sGoodsType);
	}
}

void CSearchWayThreeDlg::OnBnClickedButtonSw3CarType()
{
	vector<CString> vecCarType;
	vecCarType.push_back(NO_LIMIT_STRING);

	CString sCarType;
	CContentDlg dlg(this, GetDlgItem(IDC_BUTTON_SW3_CAR_TYPE), &vecCarType, &sCarType);
	if( dlg.DoModal() == IDOK )
	{
		AddCarType(sCarType);
		UpdateKeyword(sCarType);
	}
}

void CSearchWayThreeDlg::OnBnClickedButtonSw3CarSize()
{
	vector<CString> vecCarType;
	vecCarType.push_back(NO_LIMIT_STRING);

	CString sCarLength;
	CContentDlg dlg(this, GetDlgItem(IDC_BUTTON_SW3_CAR_SIZE), &vecCarType, &sCarLength);
	if( dlg.DoModal() == IDOK )
	{
		AddCarLength(sCarLength);
		UpdateKeyword(sCarLength);
	}
}




void CSearchWayThreeDlg::Clean()
{
	CSearchCriteria::Clean();
	m_lstFromAddr.ResetContent();
}

void CSearchWayThreeDlg::Confirm()
{

}

void CSearchWayThreeDlg::UpdateKeyword(const CString& sNewKeyword)
{
	CString sKeyWord;
	m_comboxKeyword.GetWindowText(sKeyWord);
	sKeyWord += _T(" ") + sNewKeyword;
	m_comboxKeyword.SetWindowText(sKeyWord);
}
