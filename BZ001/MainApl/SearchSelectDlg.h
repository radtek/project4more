#pragma once


// CSearchSelectDlg �Ի���

class CSearchSelectDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchSelectDlg)

public:
	CSearchSelectDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSearchSelectDlg();

// �Ի�������
	enum { IDD = IDD_SEARCH_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    // ѡ���ֵ��0-3
    int selectValue;
};
