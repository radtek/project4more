// SearchWayOneDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SearchWayOneDlg.h"
#include "AddrSelDlg.h"
#include "CommDef.h"
#include "GLB.h"
#include "ContentDlg.h"
#include "HistoryManager.h"


extern UserInfo user;
// CSearchWayOneDlg dialog

IMPLEMENT_DYNAMIC(CSearchWayOneDlg, CDialog)

CSearchWayOneDlg::CSearchWayOneDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchWayOneDlg::IDD, pParent)
	, m_sDestAddr(_T(""))
{
	m_nSearchType = eSearchType_Goods|eSearchType_Car;
}

CSearchWayOneDlg::~CSearchWayOneDlg()
{
}

void CSearchWayOneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DEST_ADDR, m_sDestAddr);
	DDX_Control(pDX, IDC_COMBO_SW1_PUBLISHER, m_comboxPublisher);
	DDX_Control(pDX, IDC_COMBO_SW1_PHONE_NUM, m_comboxPhoneNum);
	DDX_Control(pDX, IDC_COMBO_SW1_KEY_WORD, m_comboxKeyword);
}


BEGIN_MESSAGE_MAP(CSearchWayOneDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO_SW1_ALL, &CSearchWayOneDlg::OnBnClickedRadioSw1All)
	ON_BN_CLICKED(IDC_RADIO_SW1_GOODS, &CSearchWayOneDlg::OnBnClickedRadioSw1Goods)
	ON_BN_CLICKED(IDC_RADIO_SW1_CARS, &CSearchWayOneDlg::OnBnClickedRadioSw1Cars)
	ON_BN_CLICKED(IDC_BUTTON_SW1_SELECT, &CSearchWayOneDlg::OnBnClickedButtonSw1Select)
	ON_BN_CLICKED(IDC_BUTTON_SW1_CLEAN_ADDR, &CSearchWayOneDlg::OnBnClickedButtonSw1CleanAddr)
	//ON_BN_CLICKED(IDC_BUTTON_SW1_ADDR, &CSearchWayOneDlg::OnBnClickedButtonSw1Addr)
	ON_BN_CLICKED(IDC_BUTTON_SW1_GOODS, &CSearchWayOneDlg::OnBnClickedButtonSw1Goods)
	ON_BN_CLICKED(IDC_BUTTON_SW1_CAR_TYPE, &CSearchWayOneDlg::OnBnClickedButtonSw1CarType)
	ON_BN_CLICKED(IDC_BUTTON_SW1_CAR_SIZE, &CSearchWayOneDlg::OnBnClickedButtonSw1CarSize)
	ON_BN_CLICKED(IDC_BUTTON_SW1_GOODS_TYPE, &CSearchWayOneDlg::OnBnClickedButtonSw1GoodsType)
	ON_BN_CLICKED(IDC_BUTTON_SW1_CLEAN_PUBLISHER, &CSearchWayOneDlg::OnBnClickedButtonSw1CleanPublisher)
	ON_BN_CLICKED(IDC_BUTTON_SW1_CLEAN_PHONE_NUM, &CSearchWayOneDlg::OnBnClickedButtonSw1CleanPhoneNum)
	ON_BN_CLICKED(IDC_RADIO_MATCH_ALL, &CSearchWayOneDlg::OnBnClickedRadioMatchAll)
	ON_BN_CLICKED(IDC_RADIO_MATCH_ANY, &CSearchWayOneDlg::OnBnClickedRadioMatchAny)
END_MESSAGE_MAP()



BOOL CSearchWayOneDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_STATIC_SW1_FROM_ADDR)->SetWindowText(user.city.empty()?user.province.c_str():user.city.c_str());

	((CButton*)GetDlgItem(IDC_RADIO_MATCH_ANY))->SetCheck(BST_CHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_MATCH_ALL))->SetCheck(BST_UNCHECKED);

	AddStartAddr(user.province.c_str(), user.city.c_str(), NO_LIMIT_STRING);

	InitSearchTypeRadio();

	FillKeywordCombox();
	FillPublisherCombox();
	FillPhoneNumberCombox();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


// CSearchWayOneDlg message handlers

void CSearchWayOneDlg::OnBnClickedRadioSw1All()
{
	m_nSearchType = eSearchType_Goods|eSearchType_Car;
	((CButton*)GetDlgItem(IDC_RADIO_SW1_ALL))->SetCheck(BST_CHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_SW1_GOODS))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_SW1_CARS))->SetCheck(BST_UNCHECKED);
}

void CSearchWayOneDlg::OnBnClickedRadioSw1Goods()
{
	m_nSearchType = eSearchType_Goods;
	((CButton*)GetDlgItem(IDC_RADIO_SW1_ALL))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_SW1_GOODS))->SetCheck(BST_CHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_SW1_CARS))->SetCheck(BST_UNCHECKED);
}

void CSearchWayOneDlg::OnBnClickedRadioSw1Cars()
{
	m_nSearchType = eSearchType_Car;
	((CButton*)GetDlgItem(IDC_RADIO_SW1_ALL))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_SW1_GOODS))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_SW1_CARS))->SetCheck(BST_CHECKED);
}

void CSearchWayOneDlg::OnBnClickedRadioMatchAll()
{
	((CButton*)GetDlgItem(IDC_RADIO_MATCH_ALL))->SetCheck(BST_CHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_MATCH_ANY))->SetCheck(BST_UNCHECKED);
	m_bMatchAll = true;
}

void CSearchWayOneDlg::OnBnClickedRadioMatchAny()
{
	((CButton*)GetDlgItem(IDC_RADIO_MATCH_ALL))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_MATCH_ANY))->SetCheck(BST_CHECKED);
	m_bMatchAll = false;
}


void CSearchWayOneDlg::OnBnClickedButtonSw1Select()
{
	CAddrSelDlg dlg;
	if( dlg.DoModal() == IDOK )
	{
		CString sAddr;
		const CString& sProvince =  dlg.GetSelProvince();
		sAddr = sProvince;

		const list<CString>& cityList = dlg.GetSelCities();
		if(cityList.size() > 0)
		{
			if(cityList.size() > 1 )
			{
				sAddr.Empty();
				list<CString>::const_iterator it = cityList.begin(), end = cityList.end();
				for(it; it != end; ++it)
				{
					sAddr += *it + _T(" ");
					AddEndAddr(sProvince, *it, NO_LIMIT_STRING);
				}
			}
			else
			{
				const CString& sCity = *cityList.begin();
				const list<CString>& countyList = dlg.GetSelCounties();
				if(countyList.size() > 0)
				{
					sAddr.Empty();
					list<CString>::const_iterator it = countyList.begin(), end = countyList.end();
					for(it; it != end; ++it)
					{
						sAddr += *it + _T(" ");
						AddEndAddr(sProvince, sCity, *it);
					}
				}
				else
				{
					sAddr = sCity;
					AddEndAddr(sProvince, sCity, NO_LIMIT_STRING);
				}
			}
		}
		else
		{
			AddEndAddr(sProvince, NO_LIMIT_STRING, NO_LIMIT_STRING);
		}
		m_sDestAddr += " " + sAddr;
		UpdateData(FALSE);
	}
}

void CSearchWayOneDlg::OnBnClickedButtonSw1CleanAddr()
{
	CSearchCriteria::Clean();
	m_sDestAddr.Empty();
	UpdateData(FALSE);
}
//
//void CSearchWayOneDlg::OnBnClickedButtonSw1Addr()
//{
//	CAddrSelDlg dlg;
//	if( dlg.DoModal() == IDOK )
//	{
//		CString sKeyWord;
//		m_comboxKeyword.GetWindowText(sKeyWord);
//
//		CString sDestAddr(dlg.GetSelProvince());
//		AddEndProvice(sDestAddr);
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
//				AddEndCity(*it);
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
//					AddEndCounty(*it);
//				}
//			}
//		}
//
//		sKeyWord += _T(" ") + sDestAddr;
//		m_comboxKeyword.SetWindowText(sKeyWord);
//	}
//}

void CSearchWayOneDlg::OnBnClickedButtonSw1Goods()
{
	CString sGoods;
	CContentDlg dlg(GetParent(), GetDlgItem(IDC_BUTTON_SW1_GOODS), &g_vecSearchGoods, &sGoods);
	//CWnd* pCtrl = GetDlgItem(IDC_BUTTON_SW1_GOODS);
	if( dlg.DoModal() == IDOK )
	{
		AddGoods(sGoods);
		UpdateKeyword(sGoods);
	}
}


void CSearchWayOneDlg::OnBnClickedButtonSw1GoodsType()
{
	CString sGoodsType;
	CContentDlg dlg(this, GetDlgItem(IDC_BUTTON_SW1_GOODS_TYPE), &g_vecSearchGoodsType, &sGoodsType);
	if( dlg.DoModal() == IDOK )
	{
		AddGoodsType(sGoodsType);
		UpdateKeyword(sGoodsType);
	}
}


void CSearchWayOneDlg::OnBnClickedButtonSw1CarType()
{

	CString sCarType;
	CContentDlg dlg(this, GetDlgItem(IDC_BUTTON_SW1_CAR_TYPE), &g_vecSearchCarType, &sCarType);
	if( dlg.DoModal() == IDOK )
	{
		AddCarType(sCarType);
		UpdateKeyword(sCarType);
	}
}

void CSearchWayOneDlg::OnBnClickedButtonSw1CarSize()
{
	CString sCarLength;
	CContentDlg dlg(this, GetDlgItem(IDC_BUTTON_SW1_CAR_SIZE), &g_vecSearchCarSize, &sCarLength);
	if( dlg.DoModal() == IDOK )
	{
		AddCarLength(sCarLength);
		UpdateKeyword(sCarLength);
	}
}

void CSearchWayOneDlg::OnBnClickedButtonSw1CleanPublisher()
{
	m_comboxPublisher.SetWindowText(_T(""));
}

void CSearchWayOneDlg::OnBnClickedButtonSw1CleanPhoneNum()
{
	m_comboxPhoneNum.SetWindowText(_T(""));
}


void CSearchWayOneDlg::InitSearchTypeRadio()
{
	((CButton*)GetDlgItem(IDC_RADIO_SW1_ALL))->SetCheck(m_nSearchType == (eSearchType_Goods|eSearchType_Car)?BST_CHECKED:BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_SW1_GOODS))->SetCheck(m_nSearchType == eSearchType_Goods?BST_CHECKED:BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_SW1_CARS))->SetCheck(m_nSearchType == eSearchType_Car?BST_CHECKED:BST_UNCHECKED);
}

void CSearchWayOneDlg::FillKeywordCombox()
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

void CSearchWayOneDlg::FillPublisherCombox()
{
	const tdListSearchHistory& lstSearchHis = CHistoryManager::getInstance()->getSearchesHis();
	tdListSearchHistory::const_iterator it = lstSearchHis.begin(), end = lstSearchHis.end();
	for(it; it != end; ++it)
	{
		CSearchHistory* pHistory = *it;
		const char* pcszPublisher = pHistory->GetPublisher().c_str();
		if( pcszPublisher[0] != '\0' && m_comboxPublisher.FindString(-1, pcszPublisher) == CB_ERR )
		{
			m_comboxPublisher.AddString(pcszPublisher);
		}
	}
}

void CSearchWayOneDlg::FillPhoneNumberCombox()
{
	const tdListSearchHistory& lstSearchHis = CHistoryManager::getInstance()->getSearchesHis();
	tdListSearchHistory::const_iterator it = lstSearchHis.begin(), end = lstSearchHis.end();
	for(it; it != end; ++it)
	{
		CSearchHistory* pHistory = *it;
		const char* pcszPhoneNum = pHistory->GetPhoneNumber().c_str();
		if( pcszPhoneNum[0] != '\0' && m_comboxPhoneNum.FindString(-1, pcszPhoneNum) == CB_ERR )
		{
			m_comboxPhoneNum.AddString(pcszPhoneNum);
		}
	}
}

void CSearchWayOneDlg::UpdateKeyword(const CString& sNewKeyword)
{
	CString sKeyWord;
	m_comboxKeyword.GetWindowText(sKeyWord);
	sKeyWord += _T(" ") + sNewKeyword;
	m_comboxKeyword.SetWindowText(sKeyWord);
}

void CSearchWayOneDlg::Clean()
{
	CSearchCriteria::Clean();

	GetDlgItem(IDC_EDIT_DEST_ADDR)->SetWindowText(m_sDestAddr = _T(""));
	m_comboxKeyword.SetWindowText(_T(""));
	m_comboxPublisher.SetWindowText(_T(""));
	m_comboxPhoneNum.SetWindowText(_T(""));
}

void CSearchWayOneDlg::Confirm()
{
	CString sKeyWord;
	m_comboxKeyword.GetWindowText(sKeyWord);
	m_sKeyword = sKeyWord;

	CString sPublisher;
	CString sPhoneNum;
	m_comboxPublisher.GetWindowText(sPublisher);
	m_comboxPhoneNum.GetWindowText(sPhoneNum);
	if( !sPublisher.IsEmpty() )
	{
		m_lstPublisher.push_back(string(sPublisher));
	}
	if( !sPhoneNum.IsEmpty() )
	{
		m_lstPhoneNum.push_back(string(sPhoneNum));
	}
}