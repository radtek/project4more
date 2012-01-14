#pragma once
#include "resource.h"

// CSearchFavRenameDlg 对话框

class CSearchFavRenameDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchFavRenameDlg)

public:
	CSearchFavRenameDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSearchFavRenameDlg();

// 对话框数据
	enum { IDD = IDD_SEARCH_FAV_RENAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	const CString& GetNewName()const
	{
		return m_sNewName;
	}
private:
	CString m_sNewName;
public:
	afx_msg void OnBnClickedOk();
};
