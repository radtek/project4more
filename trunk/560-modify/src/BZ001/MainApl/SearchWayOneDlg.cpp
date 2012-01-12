// SearchWayOneDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SearchWayOneDlg.h"
#include "AddrSelDlg.h"
#include "CommDef.h"
#include "GLB.h"
#include "ContentDlg.h"


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
	ON_BN_CLICKED(IDC_BUTTON_SW1_ADDR, &CSearchWayOneDlg::OnBnClickedButtonSw1Addr)
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

	((CButton*)GetDlgItem(IDC_RADIO_SW1_ALL))->SetCheck(BST_CHECKED);

	m_sStartProvince = user.province.c_str();
	m_sStartCity = user.city.c_str();
	m_sStartCounty = NO_LIMIT_STRING;

	GetDlgItem(IDC_STATIC_SW1_FROM_ADDR)->SetWindowText(m_sStartCity.IsEmpty()?m_sStartProvince:m_sStartCity);

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
}

void CSearchWayOneDlg::OnBnClickedRadioSw1Goods()
{
	m_nSearchType = eSearchType_Goods;
}

void CSearchWayOneDlg::OnBnClickedRadioSw1Cars()
{
	m_nSearchType = eSearchType_Car;
}

void CSearchWayOneDlg::OnBnClickedRadioMatchAll()
{
	((CButton*)GetDlgItem(IDC_RADIO_MATCH_ALL))->SetCheck(BST_CHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_MATCH_ANY))->SetCheck(BST_UNCHECKED);
}

void CSearchWayOneDlg::OnBnClickedRadioMatchAny()
{
	((CButton*)GetDlgItem(IDC_RADIO_MATCH_ALL))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_MATCH_ANY))->SetCheck(BST_CHECKED);
}


void CSearchWayOneDlg::OnBnClickedButtonSw1Select()
{
	CAddrSelDlg dlg;
	if( dlg.DoModal() == IDOK )
	{
		m_sEndProvince = m_sDestAddr = dlg.GetSelProvince();

		const list<CString>& cityList = dlg.GetSelCities();
		if(cityList.size() > 0)
		{
			m_sDestAddr.Empty();

			list<CString>::const_iterator it = cityList.begin(), end = cityList.end();
			m_sEndCity = *it;
			for(it; it != end; ++it)
			{
				m_sDestAddr += *it + _T(" ");
			}

			const list<CString>& countyList = dlg.GetSelCounties();
			if(countyList.size() > 0)
			{
				m_sDestAddr.Empty();
				it = countyList.begin(), end = countyList.end();
				m_sEndCounty = *it;
				for(it; it != end; ++it)
				{
					m_sDestAddr += *it + _T(" ");
				}
			}
			else
			{
				m_sEndCounty = NO_LIMIT_STRING;
			}
		}
		else
		{
			m_sEndCity = m_sEndCounty = NO_LIMIT_STRING;
		}
		
		UpdateData(FALSE);
	}
}

void CSearchWayOneDlg::OnBnClickedButtonSw1CleanAddr()
{
	m_sDestAddr.Empty();
	UpdateData(FALSE);
}

void CSearchWayOneDlg::OnBnClickedButtonSw1Addr()
{
	CAddrSelDlg dlg;
	if( dlg.DoModal() == IDOK )
	{
		CString sKeyWord;
		m_comboxKeyword.GetWindowText(sKeyWord);

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

		sKeyWord += _T(" ") + sDestAddr;
		m_comboxKeyword.SetWindowText(sKeyWord);
	}
}

void CSearchWayOneDlg::OnBnClickedButtonSw1Goods()
{
	vector<CString> vecGoods;
	vecGoods.push_back(NO_LIMIT_STRING);
	vecGoods.push_back("≤‚ ‘");
	vecGoods.push_back("≤‚ ‘1");
	CContentDlg dlg(GetParent(), GetDlgItem(IDC_BUTTON_SW1_GOODS), &vecGoods, &m_sGoods);
	//CWnd* pCtrl = GetDlgItem(IDC_BUTTON_SW1_GOODS);
	if( dlg.DoModal() == IDOK )
	{
		UpdateKeyword(m_sGoods);
	}
}


void CSearchWayOneDlg::OnBnClickedButtonSw1GoodsType()
{
	vector<CString> vecGoodsType;
	vecGoodsType.push_back(NO_LIMIT_STRING);
	CContentDlg dlg(this, GetDlgItem(IDC_BUTTON_SW1_GOODS_TYPE), &vecGoodsType, &m_sGoodsType);
	if( dlg.DoModal() == IDOK )
	{
		UpdateKeyword(m_sGoodsType);
	}
}


void CSearchWayOneDlg::OnBnClickedButtonSw1CarType()
{
	vector<CString> vecCarType;
	vecCarType.push_back(NO_LIMIT_STRING);
	CContentDlg dlg(this, GetDlgItem(IDC_BUTTON_SW1_CAR_TYPE), &vecCarType, &m_sCarType);
	if( dlg.DoModal() == IDOK )
	{
		UpdateKeyword(m_sCarType);
	}
}

void CSearchWayOneDlg::OnBnClickedButtonSw1CarSize()
{
	vector<CString> vecCarType;
	vecCarType.push_back(NO_LIMIT_STRING);
	CContentDlg dlg(this, GetDlgItem(IDC_BUTTON_SW1_CAR_SIZE), &vecCarType, &m_sCarLength);
	if( dlg.DoModal() == IDOK )
	{
		UpdateKeyword(m_sCarLength);
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

}

void CSearchWayOneDlg::FillPublisherCombox()
{

}

void CSearchWayOneDlg::FillPhoneNumberCombox()
{

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
	GetDlgItem(IDC_EDIT_DEST_ADDR)->SetWindowText(m_sDestAddr = _T(""));
	m_comboxKeyword.SetWindowText(_T(""));
	m_comboxPublisher.SetWindowText(_T(""));
	m_comboxPhoneNum.SetWindowText(_T(""));
}