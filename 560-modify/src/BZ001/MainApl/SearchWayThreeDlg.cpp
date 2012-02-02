// SearchWayThreeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SearchWayThreeDlg.h"
#include "AddrSelDlg.h"
#include "CommDef.h"
#include "GLB.h"
#include "ContentDlg.h"
#include "HistoryManager.h"

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
	//ON_BN_CLICKED(IDC_BUTTON_SW3_ADDR, &CSearchWayThreeDlg::OnBnClickedButtonSw3Addr)
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

void CSearchWayThreeDlg::FillKeywordCombox()
{
	const tdListSearchHistory& lstSearchHis = CHistoryManager::getInstance()->getSearchesHis();
	tdListSearchHistory::const_iterator it = lstSearchHis.begin(), end = lstSearchHis.end();
	for(it; it != end; ++it)
	{
		CSearchHistory* pHistory = *it;
		const char* pcszKeyword = pHistory->GetKeyword().c_str();
		if( pcszKeyword[0] != '\0' && m_comboxKeyword.FindString(-1, pcszKeyword) == CB_ERR )
		{
			m_comboxKeyword.AddString(pcszKeyword);
		}
	}
}


BOOL CSearchWayThreeDlg::OnInitDialog()
{
	__super::OnInitDialog();

	AddEndAddr(user.province.c_str(), user.city.c_str(), NO_LIMIT_STRING);

	InitSearchTypeRadio();
	InitFromProvinceList();

	CString sDestAddr;
	sDestAddr.Format("[%s]", user.city.empty()?user.province.c_str():user.city.c_str());
	GetDlgItem(IDC_STATIC_SW3_DEST_ADDR)->SetWindowText(sDestAddr);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
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
	int nSelCount = m_lstFromCity.GetSelCount();
	if( nSelCount == 1 )
	{
		CString sCity;
		m_lstFromCity.GetText(m_lstFromCity.GetCurSel(), sCity);
		FillFromCountyList(m_sSelStartProv, sCity);
	}
	else
	{
		m_lstFromCounty.ResetContent();
	}
}

void CSearchWayThreeDlg::OnLbnSelchangeListSw3FromCounty()
{
	if( m_lstFromCity.GetSelCount() == 0 )
	{
		m_lstFromCity.SetSel(0);
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
	int nProvSel = m_lstFromProv.GetCurSel();

	CString sAddr;
	int nSel = m_lstFromCounty.GetSelCount();
	if( nSel > 0 )
	{
		int nCitySel = m_lstFromCity.GetCurSel();
		CString sCity;
		m_lstFromCity.GetText(nCitySel, sCity);

		int nItemData = (nProvSel<<24)|(nCitySel<<16)|eItemData_County;

		int *pItems = new int[nSel];
		m_lstFromCounty.GetSelItems(nSel, pItems);
		for(int i = 0; i<nSel; ++i)
		{
			m_lstFromCounty.GetText(pItems[i], sAddr);
			AddStartAddr(m_sSelStartProv, sCity, sAddr);
			int nItemIndex = m_lstFromAddr.FindString(-1, sAddr);
			if( nItemIndex == LB_ERR ||  m_lstFromAddr.GetItemData(nItemIndex) != nItemData )
			{
				m_lstFromAddr.AddString(sAddr);
				m_lstFromAddr.SetItemData(m_lstFromAddr.GetCount()-1, nItemData);
			}
		}
		delete []pItems;
	}
	else if( (nSel = m_lstFromCity.GetSelCount()) > 0 )
	{
		int nItemData = (nProvSel<<24)|eItemData_City;

		int *pItems = new int[nSel];
		m_lstFromCity.GetSelItems(nSel, pItems);
		for(int i = 0; i<nSel; ++i)
		{
			m_lstFromCity.GetText(pItems[i], sAddr);
			AddStartAddr(m_sSelStartProv, sAddr, NO_LIMIT_STRING);

			int nItemIndex = m_lstFromAddr.FindString(-1, sAddr);
			if( nItemIndex == LB_ERR || (m_lstFromAddr.GetItemData(nItemIndex)&0xffff0000) != (nItemData&0xffff0000) )
			{
				m_lstFromAddr.AddString(sAddr);
				m_lstFromAddr.SetItemData(m_lstFromAddr.GetCount()-1, nItemData);
			}
		}
		delete []pItems;
	}
	else if( (nSel = m_lstFromProv.GetCurSel()) != -1 )
	{
		m_lstFromProv.GetText(nSel, m_sSelStartProv);
		int nItemData = (nSel<<24)|eItemData_Province;

		AddStartAddr(m_sSelStartProv, NO_LIMIT_STRING, NO_LIMIT_STRING);

		int nItemIndex = m_lstFromAddr.FindString(-1, m_sSelStartProv);
		if( nItemIndex == LB_ERR || (m_lstFromAddr.GetItemData(nItemIndex)&0xffff0000) != (nItemData&0xffff0000) )
		{
			m_lstFromAddr.AddString(m_sSelStartProv);
			m_lstFromAddr.SetItemData(m_lstFromAddr.GetCount()-1, nItemData);
		}
	}
}

void CSearchWayThreeDlg::OnBnClickedButtonSw3AddAllCity()
{
	int nProvSel = m_lstFromProv.GetCurSel();
	int nItemData = (nProvSel<<24)|eItemData_City;

	CString sCity;
	int nCount = m_lstFromCity.GetCount();
	for(int i = 0; i<nCount; ++i)
	{
		m_lstFromCity.GetText(i, sCity);
		AddStartAddr(m_sSelStartProv, sCity, NO_LIMIT_STRING);

		int nItemIndex = m_lstFromAddr.FindString(-1, sCity);
		if( nItemIndex == LB_ERR ||  (m_lstFromAddr.GetItemData(nItemIndex)&0xffff0000) != (nItemData&0xffff0000) )
		{
			m_lstFromAddr.AddString(sCity);
			m_lstFromAddr.SetItemData(m_lstFromAddr.GetCount()-1, nItemData);
		}
	}
}

void CSearchWayThreeDlg::OnBnClickedButtonSw3AddAllCounty()
{
	int nProvSel = m_lstFromProv.GetCurSel();
	int nCitySel = m_lstFromCity.GetCurSel();
	CString sCity;
	m_lstFromCity.GetText(nCitySel, sCity);

	int nItemData = (nProvSel<<24)|(nCitySel<<16)|eItemData_County;

	CString sCounty;
	int nCount = m_lstFromCounty.GetCount();
	for(int i = 0; i<nCount; ++i)
	{
		m_lstFromCounty.GetText(i, sCounty);
		AddStartAddr(m_sSelStartProv, sCity, sCounty);

		int nItemIndex = m_lstFromAddr.FindString(-1, sCounty);
		if( nItemIndex == LB_ERR ||  (m_lstFromAddr.GetItemData(nItemIndex)&0xffff0000) != (nItemData&0xffff0000) )
		{
			m_lstFromAddr.AddString(sCounty);
			m_lstFromAddr.SetItemData(m_lstFromAddr.GetCount()-1, nItemData);
		}
	}
}

void CSearchWayThreeDlg::OnBnClickedButtonSw3Del()
{
	int nSel = m_lstFromAddr.GetCurSel();
	if( nSel != -1 )
	{
		CString sAddr;
		m_lstFromAddr.GetText(nSel, sAddr);
		int nItemData = m_lstFromAddr.GetItemData(nSel);
		int nProvIndex = (nItemData>>24)&0x000000ff;

		CString sProvince;
		m_lstFromProv.GetText(nProvIndex, sProvince);

		int nAddrType = nItemData&0x0000ffff;

		if( nAddrType == eItemData_Province )
		{
			RemoveStartAddr(sProvince, NO_LIMIT_STRING, NO_LIMIT_STRING);
		}
		else if( nAddrType == eItemData_City )
		{
			RemoveStartAddr(sProvince, sAddr==sProvince?NO_LIMIT_STRING:sAddr, NO_LIMIT_STRING);
		}
		else if( nAddrType == eItemData_County )
		{
			int nCityIndex = (nItemData>>16)&0x000000ff;
			CString sCity = GetCity(sProvince, nCityIndex).c_str();
			RemoveStartAddr(sProvince, sCity, sAddr);
		}
		m_lstFromAddr.DeleteString(nSel);		
	}
	else
	{
		MessageBox("请选择要删除的始发地");//, "系统提示", MB_OK);
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

	if( sKeyword.IsEmpty() )
	{
		return ;
	}
	int	length = sKeyword.GetLength();
	wchar_t *pwszKeyword = NULL;
	int nWideCharLen = ::MultiByteToWideChar(CP_ACP, 0, sKeyword, length+1, NULL, 0);
	pwszKeyword = new wchar_t[nWideCharLen+1];
	::MultiByteToWideChar(CP_ACP, 0, sKeyword, length+1, pwszKeyword, nWideCharLen+1);
	int nLength = wcslen(pwszKeyword);
	pwszKeyword[nLength-1] = L'\0';

	int nMultiByteLen = nWideCharLen*2+2;
	char *pszKeyword = new char[nMultiByteLen];
	memset(pszKeyword, 0, nMultiByteLen);
	WideCharToMultiByte(CP_ACP, 0, pwszKeyword, nWideCharLen-1, pszKeyword, nMultiByteLen, NULL, NULL);

	sKeyword = pszKeyword;
	delete []pwszKeyword;
	delete []pszKeyword;

	m_comboxKeyword.SetWindowText(sKeyword);

}

//void CSearchWayThreeDlg::OnBnClickedButtonSw3Addr()
//{
//	CAddrSelDlg dlg;
//	if( dlg.DoModal() == IDOK )
//	{
//		CString sDestAddr(dlg.GetSelProvince());
//
//		const list<CString>& cityList = dlg.GetSelCities();
//		if( cityList.size() > 0 )
//		{
//			sDestAddr.Empty();
//
//			list<CString>::const_iterator it = cityList.begin(), end = cityList.end();
//			for(it; it != end; ++it)
//			{
//				sDestAddr += *it + _T(" ");
//			}
//
//			const list<CString>& countyList = dlg.GetSelCounties();
//			if(countyList.size() > 0)
//			{
//				sDestAddr.Empty();
//
//				it = countyList.begin(), end = countyList.end();
//				for(it; it != end; ++it)
//				{
//					sDestAddr += *it + _T(" ");
//				}
//			}
//		}
//		UpdateKeyword(sDestAddr);
//	}
//}

void CSearchWayThreeDlg::OnBnClickedButtonSw3Goods()
{
	
	CString sGoods;
	CContentDlg dlg(GetParent(), GetDlgItem(IDC_BUTTON_SW3_GOODS), &g_vecSearchGoods, &sGoods);
	if( dlg.DoModal() == IDOK )
	{
		AddGoods(sGoods);
		UpdateKeyword(sGoods);
	}
}


void CSearchWayThreeDlg::OnBnClickedButtonSw3GoodsType()
{
	CString sGoodsType;
	CContentDlg dlg(this, GetDlgItem(IDC_BUTTON_SW3_GOODS_TYPE), &g_vecSearchGoodsType, &sGoodsType);
	if( dlg.DoModal() == IDOK )
	{
		AddGoodsType(sGoodsType);
		UpdateKeyword(sGoodsType);
	}
}

void CSearchWayThreeDlg::OnBnClickedButtonSw3CarType()
{
	CString sCarType;
	CContentDlg dlg(this, GetDlgItem(IDC_BUTTON_SW3_CAR_TYPE), &g_vecSearchCarType, &sCarType);
	if( dlg.DoModal() == IDOK )
	{
		AddCarType(sCarType);
		UpdateKeyword(sCarType);
	}
}

void CSearchWayThreeDlg::OnBnClickedButtonSw3CarSize()
{
	CString sCarLength;
	CContentDlg dlg(this, GetDlgItem(IDC_BUTTON_SW3_CAR_SIZE), &g_vecSearchCarSize, &sCarLength);
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
	m_comboxKeyword.SetWindowText("");
	m_sKeyword = "";
}

void CSearchWayThreeDlg::Confirm()
{
	CString sKeyWord;
	m_comboxKeyword.GetWindowText(sKeyWord);
	m_sKeyword = sKeyWord;
}

void CSearchWayThreeDlg::UpdateKeyword(const CString& sNewKeyword)
{
	CString sKeyWord;
	m_comboxKeyword.GetWindowText(sKeyWord);
	sKeyWord += _T(" ") + sNewKeyword;
	m_comboxKeyword.SetWindowText(sKeyWord);
}
