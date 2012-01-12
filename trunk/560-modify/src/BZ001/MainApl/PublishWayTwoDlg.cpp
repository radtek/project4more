// PublishWayTwoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PublishWayTwoDlg.h"


// CPublishWayTwoDlg dialog

IMPLEMENT_DYNAMIC(CPublishWayTwoDlg, CDialog)

CPublishWayTwoDlg::CPublishWayTwoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPublishWayTwoDlg::IDD, pParent)
{

}

CPublishWayTwoDlg::~CPublishWayTwoDlg()
{
}

void CPublishWayTwoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_W1_FROM_PROVINCE, m_btnFromProvince);
	DDX_Control(pDX, IDC_BUTTON_W1_FROM_CITY, m_btnFromCity);
	DDX_Control(pDX, IDC_BUTTON_W1_FROM_COUNTY, m_btnFromCounty);
	DDX_Control(pDX, IDC_BUTTON_W1_TO_PROVINCE, m_btnToProvince);
	DDX_Control(pDX, IDC_BUTTON_W1_TO_CITY, m_btnToCity);
	DDX_Control(pDX, IDC_BUTTON_W1_TO_COUNTY, m_btnToCounty);
}


BEGIN_MESSAGE_MAP(CPublishWayTwoDlg, CDialog)
END_MESSAGE_MAP()


// CPublishWayTwoDlg message handlers

BOOL CPublishWayTwoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_btnFromProvince.LoadBitmap(IDB_BITMAP_COMMON_BTN);
	m_btnFromCity.LoadBitmap(IDB_BITMAP_COMMON_BTN);
	m_btnFromCounty.LoadBitmap(IDB_BITMAP_COMMON_BTN);
	m_btnToProvince.LoadBitmap(IDB_BITMAP_COMMON_BTN);
	m_btnToCity.LoadBitmap(IDB_BITMAP_COMMON_BTN);
	m_btnToCounty.LoadBitmap(IDB_BITMAP_COMMON_BTN);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
