#pragma once
#include "resource.h"

// CSearchFavRenameDlg �Ի���

class CSearchFavRenameDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchFavRenameDlg)

public:
	CSearchFavRenameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSearchFavRenameDlg();

// �Ի�������
	enum { IDD = IDD_SEARCH_FAV_RENAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
