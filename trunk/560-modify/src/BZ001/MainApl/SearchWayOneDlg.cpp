// SearchWayOneDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SearchWayOneDlg.h"
#include "AddrSelDlg.h"

// CSearchWayOneDlg dialog

IMPLEMENT_DYNAMIC(CSearchWayOneDlg, CDialog)

CSearchWayOneDlg::CSearchWayOneDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchWayOneDlg::IDD, pParent)
	, m_sDestAddr(_T(""))
{

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


// CSearchWayOneDlg message handlers

void CSearchWayOneDlg::OnBnClickedRadioSw1All()
{
	// TODO: Add your control notification handler code here
}

void CSearchWayOneDlg::OnBnClickedRadioSw1Goods()
{
	// TODO: Add your control notification handler code here
}

void CSearchWayOneDlg::OnBnClickedRadioSw1Cars()
{
	// TODO: Add your control notification handler code here
}

void CSearchWayOneDlg::OnBnClickedButtonSw1Select()
{
	// TODO: Add your control notification handler code here
}

void CSearchWayOneDlg::OnBnClickedButtonSw1CleanAddr()
{
	// TODO: Add your control notification handler code here
}

void CSearchWayOneDlg::OnBnClickedButtonSw1Addr()
{
	CAddrSelDlg dlg;
	if( dlg.DoModal() == IDOK )
	{

	}
}

void CSearchWayOneDlg::OnBnClickedButtonSw1Goods()
{
	// TODO: Add your control notification handler code here
}

void CSearchWayOneDlg::OnBnClickedButtonSw1CarType()
{
	// TODO: Add your control notification handler code here
}

void CSearchWayOneDlg::OnBnClickedButtonSw1CarSize()
{
	// TODO: Add your control notification handler code here
}

void CSearchWayOneDlg::OnBnClickedButtonSw1GoodsType()
{
	// TODO: Add your control notification handler code here
}

void CSearchWayOneDlg::OnBnClickedButtonSw1CleanPublisher()
{
	// TODO: Add your control notification handler code here
}

void CSearchWayOneDlg::OnBnClickedButtonSw1CleanPhoneNum()
{
	// TODO: Add your control notification handler code here
}

void CSearchWayOneDlg::OnBnClickedRadioMatchAll()
{
	// TODO: Add your control notification handler code here
}

void CSearchWayOneDlg::OnBnClickedRadioMatchAny()
{
	// TODO: Add your control notification handler code here
}
