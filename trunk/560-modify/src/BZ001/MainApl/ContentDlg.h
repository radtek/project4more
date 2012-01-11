#pragma once
#include "resource.h"

#include <map>
#include <vector>
using std::map;
using std::vector;

// CContentDlg dialog

class CContentDlg : public CDialog
{
	DECLARE_DYNAMIC(CContentDlg)

public:
	CContentDlg(CWnd* pParent, CWnd* pCtrlWnd, const vector<CString> *pVecItems, CString *strOut);   // standard constructor
	virtual ~CContentDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_CONTENT_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnLbnSelchangeListContent();

private:
	const vector<CString> *m_pVecItems;
	CString *m_strOut;

	CWnd	 *m_pCtrlWnd;
	CListBox *m_pListBox;
};
