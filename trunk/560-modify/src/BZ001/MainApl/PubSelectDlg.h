#pragma once


// CPubSelectDlg �Ի���

class CPubSelectDlg : public CDialog
{
	DECLARE_DYNAMIC(CPubSelectDlg)

public:
	CPubSelectDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPubSelectDlg();

// �Ի�������
	enum { IDD = IDD_PUB_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    // ѡ���ֵ��0-3
    int selectValue;
	afx_msg void OnBnClickedOk();
};
