// ValueAddedServiceDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "ValueAddedServiceDlg.h"
#include "header.h"
#include "EmbeddedIeDlg.h"

// CValueAddedServiceDlg �Ի���

IMPLEMENT_DYNAMIC(CValueAddedServiceDlg, CDialog)

CValueAddedServiceDlg::CValueAddedServiceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CValueAddedServiceDlg::IDD, pParent)
{

}

CValueAddedServiceDlg::~CValueAddedServiceDlg()
{
}

void CValueAddedServiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CValueAddedServiceDlg, CDialog)
    ON_BN_CLICKED(IDC_VALUE_ADDED_SERVICE_IDCARD, &CValueAddedServiceDlg::OnBnClickedValueAddedServiceIdcard)
    ON_BN_CLICKED(IDC_VALUE_ADDED_SERVICE_REGISTRATION, &CValueAddedServiceDlg::OnBnClickedValueAddedServiceRegistration)
    ON_BN_CLICKED(IDC_VALUE_ADDED_SERVICE_DRIVINGLICENSE, &CValueAddedServiceDlg::OnBnClickedValueAddedServiceDrivinglicense)
END_MESSAGE_MAP()


// CValueAddedServiceDlg ��Ϣ�������
    
// ���֤�˲�
void CValueAddedServiceDlg::OnBnClickedValueAddedServiceIdcard()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	CEmbeddedIeDlg dlg;
	dlg.url = WEB_SERVICE_ADDRESS+"/fmp/verDocument.list.action?name=";
	dlg.url += user.loginName;
	dlg.url += "&password=";
	dlg.url += user.passWord;
	dlg.url += "&type=0&print=0";
	dlg.m_flag = FALSE;
	dlg.DoModal();
}
    
// ��ʻ֤�˲�
void CValueAddedServiceDlg::OnBnClickedValueAddedServiceRegistration()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	CEmbeddedIeDlg dlg;
	dlg.url = WEB_SERVICE_ADDRESS+"/fmp/verDocument.list.action?name=";
	dlg.url += user.loginName;
	dlg.url += "&password=";
	dlg.url += user.passWord;
	dlg.url += "&type=2&print=0";
	dlg.m_flag = FALSE;
	dlg.DoModal();
}
    
// ��ʻ֤�˲�
void CValueAddedServiceDlg::OnBnClickedValueAddedServiceDrivinglicense()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	CEmbeddedIeDlg dlg;
	dlg.url = WEB_SERVICE_ADDRESS+"/fmp/verDocument.list.action?name=";
	dlg.url += user.loginName;
	dlg.url += "&password=";
	dlg.url += user.passWord;
	dlg.url += "&type=1&print=0";
	dlg.m_flag = FALSE;
	dlg.DoModal();
}
