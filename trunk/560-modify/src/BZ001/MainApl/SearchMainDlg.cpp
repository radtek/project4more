// SearchMainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SearchMainDlg.h"
#include "HistoryManager.h"


// CSearchMainDlg dialog

IMPLEMENT_DYNAMIC(CSearchMainDlg, CDialog)

CSearchMainDlg::CSearchMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchMainDlg::IDD, pParent)
{
	m_pCurSearch = NULL;
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
	ON_BN_CLICKED(IDC_BUTTON_OK, &CSearchMainDlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN, &CSearchMainDlg::OnBnClickedButtonClean)
	ON_BN_CLICKED(IDC_BUTTON_ADD_FAVORITE, &CSearchMainDlg::OnBnClickedButtonAddFavorite)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CSearchMainDlg::OnBnClickedButtonClose)
END_MESSAGE_MAP()


// CSearchMainDlg message handlers

BOOL CSearchMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_tabSearchWay.InsertItem(0,"������ʽһ");
	m_tabSearchWay.InsertItem(1,"������ʽ��");
	m_tabSearchWay.InsertItem(2,"������ʽ��");
	m_tabSearchWay.InsertItem(3,"�ղص�����");

	m_oWayOneDlg.Create(IDD_SEARCH_WAY_ONE, GetDlgItem(IDC_TAB_SEARCH_WAY));
	m_oWayTwoDlg.Create(IDD_SEARCH_WAY_TWO, &m_tabSearchWay);
	m_oWayThreeDlg.Create(IDD_SEARCH_WAY_THREE, &m_tabSearchWay);
	m_oFavoriteDlg.Create(IDD_SEARCH_FAVORITE, &m_tabSearchWay);

	CRect rect;
	m_tabSearchWay.GetClientRect(&rect);

	//�����ӶԻ����ڸ������е�λ��
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

	m_pCurSearch = &m_oWayOneDlg;
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
		m_pCurSearch = &m_oWayOneDlg;
		m_oWayOneDlg.ShowWindow(SW_SHOW);
		m_oWayTwoDlg.ShowWindow(SW_HIDE);
		m_oWayThreeDlg.ShowWindow(SW_HIDE);
		m_oFavoriteDlg.ShowWindow(SW_HIDE);
	}
	else if( nCurSel == 1 )
	{
		m_pCurSearch = &m_oWayTwoDlg;
		m_oWayOneDlg.ShowWindow(SW_HIDE);
		m_oWayTwoDlg.ShowWindow(SW_SHOW);
		m_oWayThreeDlg.ShowWindow(SW_HIDE);
		m_oFavoriteDlg.ShowWindow(SW_HIDE);
	}
	else if( nCurSel == 2 )
	{
		m_pCurSearch = &m_oWayThreeDlg;
		m_oWayOneDlg.ShowWindow(SW_HIDE);
		m_oWayTwoDlg.ShowWindow(SW_HIDE);
		m_oWayThreeDlg.ShowWindow(SW_SHOW);
		m_oFavoriteDlg.ShowWindow(SW_HIDE);
	}
	else if( nCurSel == 3 )
	{
		m_pCurSearch = NULL;
		m_oWayOneDlg.ShowWindow(SW_HIDE);
		m_oWayTwoDlg.ShowWindow(SW_HIDE);
		m_oWayThreeDlg.ShowWindow(SW_HIDE);
		m_oFavoriteDlg.ShowWindow(SW_SHOW);
		m_oFavoriteDlg.RefreshFavorite();
	}
}

void CSearchMainDlg::OnBnClickedButtonOk()
{
	if( m_pCurSearch != NULL )
	{
		m_pCurSearch->Confirm();
		CHistoryManager::getInstance()->addSearchHis(m_pCurSearch);
	}
	else if( m_oFavoriteDlg.GetUsedSearchFav() != NULL )
	{
		m_bUseSearchFavorite = true;
	}
	CDialog::OnOK();
}

void CSearchMainDlg::OnBnClickedButtonClose()
{
	CDialog::OnCancel();
}

void CSearchMainDlg::OnBnClickedButtonClean()
{
	if( m_pCurSearch != NULL )
	{
		m_pCurSearch->Clean();
	}
}

void CSearchMainDlg::OnBnClickedButtonAddFavorite()
{
	if( m_pCurSearch != NULL )
	{
		m_pCurSearch->Confirm();
		CHistoryManager::getInstance()->addSearchFav(m_pCurSearch);
		MessageBox("�ղسɹ�", "��Ϣ��ʾ", MB_OK);
	}
}


LRESULT CSearchMainDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_USE_SEARCH_FAVORITE:
		m_bUseSearchFavorite = true;
		CDialog::OnOK();
		return 0;
	}
	return CDialog::WindowProc(message, wParam, lParam);
}
