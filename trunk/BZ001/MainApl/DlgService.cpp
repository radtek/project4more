// DlgService.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "DlgService.h"
#include "WLRClientDlg.h"
#include "DlgSendRequest.h"
// CDlgService �Ի���


HWND m_servicehwnd;
InSearchService strIn;
inputParamFwz curInput;

CArray<ServiceData,ServiceData> m_servicedata;//����վ������

#define WM_LISTFRESH WM_USER+88

IMPLEMENT_DYNAMIC(CDlgService, CXTResizeDialog)

CDlgService::CDlgService(CWnd* pParent /*=NULL*/)
	: CXTResizeDialog(CDlgService::IDD, pParent)
{

	// ��ʼ��svrIO
	svrIO = NULL;
}

CDlgService::~CDlgService()
{
}

void CDlgService::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_TREE1, mTreeMain);
	DDX_Control(pDX, IDC_PIC, m_Picture);
}


BEGIN_MESSAGE_MAP(CDlgService, CXTResizeDialog)
	ON_MESSAGE(WM_REQUEST,OnRequest)
	ON_WM_SIZE()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CDlgService::OnTvnSelchangedTree1)
	ON_MESSAGE(WM_LISTFRESH,OnFresh)
END_MESSAGE_MAP()


// CDlgService ��Ϣ�������

BOOL CDlgService::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();
	HICON m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	//SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	if (m_Picture.Load(MAKEINTRESOURCE(IDR_WAIT),_T("GIF")))
		m_Picture.Draw();
	strIn.Province="";
	strIn.City="";
	m_servicehwnd = m_hWnd;
	// ���ص�����Ϣ
	if ( -1 == CountryRegion::loadData(myCR, "RegionInfo.bin") ) {
		AfxMessageBox("���س��������ļ�ʧ�ܣ������°�װӦ�ó���");
		exit(0);
	}
	//��ʼ���ṹ��
	initTreeCtrl();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CRect rect;
	GetDlgItem(IDC_LIST1)->GetClientRect(&rect);
	CString strTitle;
	strTitle.Format(_T("����վ��/���, %d, 1; ��ַ, %d, 1; ��ϵ��, %d, 1;�绰, %d, 1;����, %d, 1"),(int)(0.15*rect.Width()),(int)(0.45*rect.Width()),(int)(0.1*rect.Width()),(int)(0.2*rect.Width()),(int)(0.1*rect.Width()));
	m_list.SetColumnHeader(strTitle);
	m_list.SetGridLines(TRUE);



	/*m_list.InsertItem( 0 , _T(""));
	
	m_list.SetItemText(0, 0, "��ɽ��[12555]");
	m_list.SetItemText(0, 1, "�㽭ʡ��������һ��·75��");
	m_list.SetItemText(0, 2, "abc");
	m_list.SetItemText(0, 3, "0571-89898989");
	m_list.SetItemText(0, 4, "��������");
	m_list.SetItemURL(0, 4,"","");

	ServiceData sdata;
	strcpy(sdata.Number,"��ɽ��[12555]");
	strcpy(sdata.Address,"�㽭ʡ��������һ��·75��");
	strcpy(sdata.Name,"cab");
	strcpy(sdata.Tel,"0571-89898989");
	m_servicedata.Add(sdata);


	m_list.InsertItem(1, _T(""));

	m_list.SetItemText(1, 0, "������[2553]");
	m_list.SetItemText(1, 1, "�����к�����");
	m_list.SetItemText(1, 2, "efg");
	m_list.SetItemText(1, 3, "0571-12345678");
	m_list.SetItemText(1, 4, "��������");
	m_list.SetItemURL(1, 4,"", "");

	strcpy(sdata.Number,"������[2553]");
	strcpy(sdata.Address,"�����к�����75��");
	strcpy(sdata.Name,"feg");
	strcpy(sdata.Tel,"0571-12345678");
	m_servicedata.Add(sdata);*/


	SetResize(IDC_TREE1, SZ_TOP_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_LIST1, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
	//SetResize(IDC_PIC,SZ_TOP_CENTER,SZ_BOTTOM_CENTER);
	//SetResize(IDC_SHOW,SZ_TOP_RIGHT,SZ_BOTTOM_RIGHT);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
int CDlgService::initTreeCtrl()
{
	mTreeMain.ModifyStyle(0,WS_VISIBLE|WS_HSCROLL|WS_VSCROLL
		|TVS_LINESATROOT|TVS_HASLINES|TVS_HASBUTTONS|TVS_TRACKSELECT|TVS_SHOWSELALWAYS);
	//pCtrl->SetBkColor(RGB(193,221,186));
	//mTreeMain.SetBkColor(RGB(239,246,236));

	TVINSERTSTRUCT tvInsert;
	tvInsert.hParent = NULL;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT;
	tvInsert.item.pszText = _T("�й�");

	HTREEITEM hCountry = mTreeMain.InsertItem(&tvInsert);

	vector<Province>::iterator iter = myCR.govProvince.begin();
	while (iter != myCR.govProvince.end()) {
		HTREEITEM hPA = mTreeMain.InsertItem((*iter).name.c_str(), 0, 0, hCountry, NULL);
		vector<City>::iterator iter2 = (*iter).govCity.begin();
		while (iter2 != (*iter).govCity.end()) {
			mTreeMain.InsertItem((*iter2).name.c_str(), 0, 0, hPA, NULL);
			++iter2;
		}
		++iter;
	}
	mTreeMain.Expand(hCountry, TVE_EXPAND);
	return 0;
}
LRESULT CDlgService::OnRequest(WPARAM wParam, LPARAM lParam)
{
	int num = (int)lParam;//������ǵڼ�����������
	CString str;
	str.Format("%d",num);
	//AfxMessageBox(str);

	CDlgSendRequest dlg;
	dlg.svrIO = svrIO;
	dlg.m_number = strIn.Province.c_str();
	dlg.m_number += strIn .City.c_str();
	dlg.m_number += "  [";
	dlg.m_number += m_servicedata[num].serviceN;
	dlg.m_number += "]";
	dlg.m_number += "����վ";
	dlg.recordID = m_servicedata[num].serviceID;
	dlg.DoModal();
	
	return 0;
}
void CDlgService::OnSize(UINT nType, int cx, int cy)
{
	CXTResizeDialog::OnSize(nType, cx, cy);
	if (GetDlgItem(IDC_LIST1)->GetSafeHwnd() != NULL)
	{
		CRect rect;
		GetDlgItem(IDC_LIST1)->GetClientRect(&rect);
		CString strTitle;
		strTitle.Format(_T("����վ��/���, %d, 1; ��ַ, %d, 1; ��ϵ��, %d, 1;�绰, %d, 1;����, %d, 1"),(int)(0.15*rect.Width()),(int)(0.45*rect.Width()),(int)(0.1*rect.Width()),(int)(0.2*rect.Width()),(int)(0.1*rect.Width()));

		//m_list.SetColumnHeader(strTitle);
	}
	// TODO: �ڴ˴������Ϣ����������
}

void CDlgService::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HTREEITEM selectHtm = mTreeMain.GetSelectedItem();
	CString strSelect = mTreeMain.GetItemText(selectHtm);

	//�õ����ڵ���
	HTREEITEM parentHtm = mTreeMain.GetParentItem(selectHtm);
	CString parStr = mTreeMain.GetItemText(parentHtm);

	if (parStr==_T("�й�")||parStr==_T(""))
		return;

	//MessageBox("��ѡ�е���:" + parStr + " " + strSelect);
	
		
	curInput.input = parStr+"|"+ strSelect;
	curInput.curpage =1;
	curInput.record = 20;
	//curInput.customid = "0";
	//CWLRClientDlg *pDlg=(CWLRClientDlg*)AfxGetApp()->GetMainWnd();
	
		
	
	strIn.Province = parStr.GetBuffer();
	strIn.City = strSelect.GetBuffer();
	
	m_servicedata.RemoveAll();
		
	//�����߳�������
	//SuspendThread(hThread);
	//Sleep(200);
	
	m_list.DeleteAllItems();
	//
	
	//GetDlgItem(IDC_TREE1)->EnableWindow(FALSE);
	//GetDlgItem(IDC_LIST1)->EnableWindow(FALSE);
	GetDlgItem(IDC_PIC)->ShowWindow(TRUE);
	GetDlgItem(IDC_SHOW)->ShowWindow(TRUE);
	
	
	DWORD PID;
	HANDLE Main_Thread;
	Main_Thread=CreateThread(NULL,0,ThreadFunc,this,0,&PID);
	
	
// 	DWORD dip = 0;
// 	if (hThread != NULL)
// 	{
// 		while(1)
// 		{
// 			dip = ResumeThread(hThread);
// 			if (dip == 0)
// 			{
// 				break;
// 			}
// 			Sleep(100);
// 		}
// 	}
	
	//
	*pResult = 0;
}
DWORD CDlgService::ThreadFunc(LPVOID p)
{
	CoInitialize(NULL);
	CDlgService * dlg = (CDlgService*)p;

	if (csService.LockCount == 0) return -1;
	EnterCriticalSection(&csService);
	
	//dlg->GetDlgItem(IDC_PIC)->ShowWindow(TRUE);
	//dlg->GetDlgItem(IDC_SHOW)->ShowWindow(TRUE);
	
	string  result =dlg->svrIO->getServicestationInf(strIn,dlg->input,curInput);
	
	//AfxMessageBox(result.c_str());
	
	::SendMessage(dlg->GetSafeHwnd(),WM_LISTFRESH,0,0);
	LeaveCriticalSection(&csService);
	CoUninitialize();
	return 0 ;
}
//������Ϣˢ��
LONG CDlgService::OnFresh(WPARAM w, LPARAM l)
{
	//��listctrl���������
	m_list.DeleteAllItems();
	CString str,temp;
	for (unsigned int i=0;i<input.size();i++)
	{
		ServiceData sdata;
		strcpy(sdata.cprovince,strIn.Province.c_str());//ʡ
		strcpy(sdata.ccity,strIn.City.c_str());//��
	
		m_list.InsertItem( i , _T(""));
		str = input.at(i).serviceName.c_str();
		strcpy(sdata.serviceN,str);//����վ����
		str += "[";
		str += input.at(i).serviceNo.c_str();
		str +="]";
		temp = input.at(i).serviceNo.c_str();
		strcpy(sdata.Number,temp);//���
		m_list.SetItemText(i, 0, str);
	
		str = input.at(i).serviceAddr.c_str();
		strcpy(sdata.Address,str);//��ַ
		m_list.SetItemText(i, 1, str);
	
		str = input.at(i).servicePerson.c_str();
		strcpy(sdata.Name,str);//��ϵ��
		m_list.SetItemText(i, 2, str);
	
		str = input.at(i).tel.c_str();
		strcpy(sdata.Tel,str);//�绰����
		m_list.SetItemText(i, 3, str);
	
		m_list.SetItemText(i, 4, "��������");
		m_list.SetItemURL(i, 4,"","");
			
		str = input.at(i).recordID.c_str();
	
		strcpy(sdata.serviceID,str);//����վID
	
		m_servicedata.Add(sdata);
	}
	GetDlgItem(IDC_PIC)->ShowWindow(FALSE);
	GetDlgItem(IDC_SHOW)->ShowWindow(FALSE);
	return 0;
}