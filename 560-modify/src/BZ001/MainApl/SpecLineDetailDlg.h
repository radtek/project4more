#pragma once
#include "resource.h"
#include <afxwin.h>

// CSpecLineDetailDlg 对话框
struct TabSpecialLineRecord;

class CSpecLineDetailDlg : public CDialog
{
	DECLARE_DYNAMIC(CSpecLineDetailDlg)

public:
	enum {eInfoType_SpecialLine, eInfoType_My_SpecialLine};

	CSpecLineDetailDlg(const TabSpecialLineRecord* pSpecLineDetail, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSpecLineDetailDlg();

// 对话框数据
	enum { IDD = IDD_SPECIAL_LINE_DETAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	void InitSpecialLineDetail();
private:
	const TabSpecialLineRecord* m_pSpecLineDetail;
//	CMyGroupBox m_goalGroup;
//	CMyGroupBox m_contactGroup;
public:
	afx_msg void OnBnClickedButtonClose();
};
