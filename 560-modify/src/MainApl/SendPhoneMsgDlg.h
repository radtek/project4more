#pragma once
#include "MyEdit.h"

// CSendPhoneMsgDlg �Ի���

class CSendPhoneMsgDlg : public CDialog
{
	DECLARE_DYNAMIC(CSendPhoneMsgDlg)

public:
	CSendPhoneMsgDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSendPhoneMsgDlg();

// �Ի�������
	enum { IDD = IDD_SEND_PHONEMSG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    // ��������
    CString phoneMsg;

    // �ֻ�����
    CString phoneNumber;
public:
    afx_msg void OnBnClickedOk();
	CMyEdit myedit;
};
