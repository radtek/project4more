#pragma once


// CSearchSelectDlg 对话框

class CSearchSelectDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchSelectDlg)

public:
	CSearchSelectDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSearchSelectDlg();

// 对话框数据
	enum { IDD = IDD_SEARCH_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    // 选择的值：0-3
    int selectValue;
};
