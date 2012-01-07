#pragma once


// CPubSelectDlg 对话框

class CPubSelectDlg : public CDialog
{
	DECLARE_DYNAMIC(CPubSelectDlg)

public:
	CPubSelectDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPubSelectDlg();

// 对话框数据
	enum { IDD = IDD_PUB_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    // 选择的值：0-3
    int selectValue;
	afx_msg void OnBnClickedOk();
};
