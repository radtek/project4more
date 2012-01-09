// SearchMainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SearchMainDlg.h"


// CSearchMainDlg dialog

IMPLEMENT_DYNAMIC(CSearchMainDlg, CDialog)

CSearchMainDlg::CSearchMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchMainDlg::IDD, pParent)
{

}

CSearchMainDlg::~CSearchMainDlg()
{
}

void CSearchMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_SEARCH_WAY, m_tabSearchWay);
}


BEGIN_MESSAGE_MAP(CSearchMainDlg, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SEARCH_WAY, &CSearchMainDlg::OnTcnSelchangeTabSearchWay)
END_MESSAGE_MAP()


// CSearchMainDlg message handlers

BOOL CSearchMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_tabSearchWay.InsertItem(0,"搜索方式一");
	m_tabSearchWay.InsertItem(1,"搜索方式二");
	m_tabSearchWay.InsertItem(2,"搜索方式三");
	m_tabSearchWay.InsertItem(3,"收藏的搜索");

	m_oWayOneDlg.Create(IDD_SEARCH_WAY_ONE, GetDlgItem(IDC_TAB_SEARCH_WAY));
	m_oWayTwoDlg.Create(IDD_SEARCH_WAY_TWO, &m_tabSearchWay);
	m_oWayThreeDlg.Create(IDD_SEARCH_WAY_THREE, &m_tabSearchWay);
	m_oFavoriteDlg.Create(IDD_SEARCH_FAVORITE, &m_tabSearchWay);

	CRect rect;
	m_tabSearchWay.GetClientRect(&rect);

	//调整子对话框在父窗口中的位置
	rect.top+=22; 
	rect.left+=2; 
	rect.right-=2;
	rect.bottom-=2;

	m_oWayOneDlg.MoveWindow(&rect);
	m_oWayTwoDlg.MoveWindow(&rect);
	m_oWayThreeDlg.MoveWindow(&rect);
	m_oFavoriteDlg.MoveWindow(&rect);

	m_oWayOneDlg.ShowWindow(SW_SHOW);
	m_oWayTwoDlg.ShowWindow(SW_HIDE);
	m_oWayThreeDlg.ShowWindow(SW_HIDE);
	m_oFavoriteDlg.ShowWindow(SW_HIDE);

	m_tabSearchWay.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSearchMainDlg::OnTcnSelchangeTabSearchWay(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	int nCurSel = m_tabSearchWay.GetCurSel();
	if( nCurSel == 0 )
	{
		m_oWayOneDlg.ShowWindow(SW_SHOW);
		m_oWayTwoDlg.ShowWindow(SW_HIDE);
		m_oWayThreeDlg.ShowWindow(SW_HIDE);
		m_oFavoriteDlg.ShowWindow(SW_HIDE);
	}
	else if( nCurSel == 1 )
	{
		m_oWayOneDlg.ShowWindow(SW_HIDE);
		m_oWayTwoDlg.ShowWindow(SW_SHOW);
		m_oWayThreeDlg.ShowWindow(SW_HIDE);
		m_oFavoriteDlg.ShowWindow(SW_HIDE);
	}
	else if( nCurSel == 2 )
	{
		m_oWayOneDlg.ShowWindow(SW_HIDE);
		m_oWayTwoDlg.ShowWindow(SW_HIDE);
		m_oWayThreeDlg.ShowWindow(SW_SHOW);
		m_oFavoriteDlg.ShowWindow(SW_HIDE);
	}
	else if( nCurSel == 3 )
	{
		m_oWayOneDlg.ShowWindow(SW_HIDE);
		m_oWayTwoDlg.ShowWindow(SW_HIDE);
		m_oWayThreeDlg.ShowWindow(SW_HIDE);
		m_oFavoriteDlg.ShowWindow(SW_SHOW);
	}
}
