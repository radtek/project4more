// SearchFavoriteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SearchFavoriteDlg.h"
#include "HistoryManager.h"
#include "SearchFavorite.h"
#include "SearchFavRenameDlg.h"
#include "SearchMainDlg.h"


// CSearchFavoriteDlg dialog

IMPLEMENT_DYNAMIC(CSearchFavoriteDlg, CDialog)

CSearchFavoriteDlg::CSearchFavoriteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchFavoriteDlg::IDD, pParent)
{
	m_pSelSearchFav = NULL;
}

CSearchFavoriteDlg::~CSearchFavoriteDlg()
{
}

void CSearchFavoriteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CTRL_SEARCH_FAVORITE, m_listCtrlFavorite);
}


BEGIN_MESSAGE_MAP(CSearchFavoriteDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CSearchFavoriteDlg::OnBnClickedButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_USE, &CSearchFavoriteDlg::OnBnClickedButtonUse)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CSearchFavoriteDlg::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_RENAME, &CSearchFavoriteDlg::OnBnClickedButtonRename)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CTRL_SEARCH_FAVORITE, &CSearchFavoriteDlg::OnLvnItemchangedListCtrlSearchFavorite)
END_MESSAGE_MAP()


void CSearchFavoriteDlg::InitFavoriteListBox()
{
	m_listCtrlFavorite.DeleteAllItems();
	int i = 0;
	CString sIndex;
	const tdListSearchFavorite& favList =  CHistoryManager::getInstance()->getSearchesFav();
	tdListSearchFavorite::const_iterator it = favList.begin(), end = favList.end();
	for(it; it != end; ++it, ++i)
	{
		CSearchFavorite* pSearchFav = *it;
		sIndex.Format(" %d ", i);
		m_listCtrlFavorite.InsertItem(i, "");
		m_listCtrlFavorite.SetItemText(i, 1, sIndex);
		m_listCtrlFavorite.SetItemText(i, 2, pSearchFav->GetName().c_str());
		m_listCtrlFavorite.SetItemData(i, i);
	}
}

void CSearchFavoriteDlg::GetSearchFavName(int nSel, CString& sName)
{
	sName = m_listCtrlFavorite.GetItemText(nSel, 2);
}
// CSearchFavoriteDlg message handlers
BOOL CSearchFavoriteDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_listCtrlFavorite.InsertColumn(0, "Image");
	m_listCtrlFavorite.InsertColumn(1, "���");
	m_listCtrlFavorite.InsertColumn(2, "�ղ���");

	DWORD dwExtStyle = m_listCtrlFavorite.GetExStyle();
	dwExtStyle |= (LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_ONECLICKACTIVATE);
	dwExtStyle &= ~LVS_EX_CHECKBOXES;
	m_listCtrlFavorite.SetExtendedStyle(dwExtStyle);

	CImageList imgList;  //ΪClistCtrl����һ��ͼ���б��������и�
	imgList.Create(IDB_BITMAP5, 20, 1, RGB(255, 255, 255)); // IDB_BITMAP4 �� 16*16�� �����и�16����

	m_listCtrlFavorite.SetImageList(&imgList,LVSIL_SMALL);


	CRect rc;
	m_listCtrlFavorite.GetWindowRect(&rc);
	m_listCtrlFavorite.SetColumnWidth(0, 0);
	m_listCtrlFavorite.SetColumnWidth(1, 30);
	m_listCtrlFavorite.SetColumnWidth(2, rc.Width() - 30);
	

	InitFavoriteListBox();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CSearchFavoriteDlg::OnBnClickedButtonRefresh()
{
	InitFavoriteListBox();
}

void CSearchFavoriteDlg::OnBnClickedButtonUse()
{
	int nSelIndex = m_listCtrlFavorite.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelIndex == -1 )
	{
		MessageBox(_T("��ѡ��Ҫʹ�õ�����"), _T("ϵͳ��ʾ"), MB_OK);
		return;
	}
	CString sName;
	GetSearchFavName(nSelIndex, sName);
	m_pSelSearchFav = CHistoryManager::getInstance()->findSearchFav(string(sName));
	((CSearchMainDlg*)(GetParent()->GetParent()))->PostMessage(WM_USE_SEARCH_FAVORITE);
}

void CSearchFavoriteDlg::OnBnClickedButtonDel()
{
	int nSelIndex = m_listCtrlFavorite.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelIndex == -1 )
	{
		MessageBox(_T("��ѡ��Ҫɾ��������"), _T("ϵͳ��ʾ"), MB_OK);
		return;
	}

	CString sName;
	GetSearchFavName(nSelIndex, sName);
	CHistoryManager::getInstance()->delSearchFav(string(sName));
	m_listCtrlFavorite.DeleteItem(nSelIndex);

	CString sIndex;
	int i = nSelIndex;
	int nCount = m_listCtrlFavorite.GetItemCount();
	for(i; i<nCount; ++i)
	{
		sIndex.Format(" %d ", i);
		m_listCtrlFavorite.SetItemText(i, 1, sIndex);
	}
}

void CSearchFavoriteDlg::OnBnClickedButtonRename()
{
	int nSelIndex = m_listCtrlFavorite.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelIndex == -1 )
	{
		MessageBox(_T("��ѡ��Ҫ������������"), _T("ϵͳ��ʾ"), MB_OK);
		return;
	}
	CSearchFavRenameDlg dlg;
	if( dlg.DoModal() == IDOK)
	{
		CString sName, sNewName;
		sNewName = dlg.GetNewName();
		if( !sNewName.IsEmpty() )
		{
			GetSearchFavName(nSelIndex, sName);
			CHistoryManager::getInstance()->renameSearchFav(string(sName), string(sNewName));
			m_listCtrlFavorite.SetItemText(nSelIndex, 2, sNewName);
		}
	}
}

void CSearchFavoriteDlg::OnLvnItemchangedListCtrlSearchFavorite(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	m_nSelIndex = pNMLV->iItem;
	*pResult = 0;
}
