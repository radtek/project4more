// ValueAddedServiceDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WLRClient.h"
#include "ValueAddedServiceDlg.h"
#include "header.h"
#include "EmbeddedIeDlg.h"

// CValueAddedServiceDlg 对话框

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


// CValueAddedServiceDlg 消息处理程序
    
// 身份证核查
void CValueAddedServiceDlg::OnBnClickedValueAddedServiceIdcard()
{
    // TODO: 在此添加控件通知处理程序代码
	CEmbeddedIeDlg dlg;
	dlg.url = WEB_SERVICE_ADDRESS+"/fmp/verDocument.list.action?name=";
	dlg.url += user.loginName;
	dlg.url += "&password=";
	dlg.url += user.passWord;
	dlg.url += "&type=0&print=0";
	dlg.m_flag = FALSE;
	dlg.DoModal();
}
    
// 行驶证核查
void CValueAddedServiceDlg::OnBnClickedValueAddedServiceRegistration()
{
    // TODO: 在此添加控件通知处理程序代码
	CEmbeddedIeDlg dlg;
	dlg.url = WEB_SERVICE_ADDRESS+"/fmp/verDocument.list.action?name=";
	dlg.url += user.loginName;
	dlg.url += "&password=";
	dlg.url += user.passWord;
	dlg.url += "&type=2&print=0";
	dlg.m_flag = FALSE;
	dlg.DoModal();
}
    
// 驾驶证核查
void CValueAddedServiceDlg::OnBnClickedValueAddedServiceDrivinglicense()
{
    // TODO: 在此添加控件通知处理程序代码
	CEmbeddedIeDlg dlg;
	dlg.url = WEB_SERVICE_ADDRESS+"/fmp/verDocument.list.action?name=";
	dlg.url += user.loginName;
	dlg.url += "&password=";
	dlg.url += user.passWord;
	dlg.url += "&type=1&print=0";
	dlg.m_flag = FALSE;
	dlg.DoModal();
}
