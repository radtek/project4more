// DlgService.cpp : 实现文件
//

#include "stdafx.h"
#include "WLRClient.h"
#include "DlgService.h"
#include "WLRClientDlg.h"
#include "DlgSendRequest.h"
// CDlgService 对话框


HWND m_servicehwnd;
InSearchService strIn;
inputParamFwz curInput;

CArray<ServiceData,ServiceData> m_servicedata;//服务站的数据

#define WM_LISTFRESH WM_USER+88

IMPLEMENT_DYNAMIC(CDlgService, CXTResizeDialog)

CDlgService::CDlgService(CWnd* pParent /*=NULL*/)
	: CXTResizeDialog(CDlgService::IDD, pParent)
{

	// 初始化svrIO
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


// CDlgService 消息处理程序

BOOL CDlgService::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();
	HICON m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//SetIcon(m_hIcon, TRUE);			// 设置大图标
	//SetIcon(m_hIcon, FALSE);		// 设置小图标
	if (m_Picture.Load(MAKEINTRESOURCE(IDR_WAIT),_T("GIF")))
		m_Picture.Draw();
	strIn.Province="";
	strIn.City="";
	m_servicehwnd = m_hWnd;
	// 加载地区信息
	if ( -1 == CountryRegion::loadData(myCR, "RegionInfo.bin") ) {
		AfxMessageBox("加载程序配置文件失败，请重新安装应用程序！");
		exit(0);
	}
	//初始化结构树
	initTreeCtrl();
	// TODO:  在此添加额外的初始化

	CRect rect;
	GetDlgItem(IDC_LIST1)->GetClientRect(&rect);
	CString strTitle;
	strTitle.Format(_T("服务站名/编号, %d, 1; 地址, %d, 1; 联系人, %d, 1;电话, %d, 1;请求, %d, 1"),(int)(0.15*rect.Width()),(int)(0.45*rect.Width()),(int)(0.1*rect.Width()),(int)(0.2*rect.Width()),(int)(0.1*rect.Width()));
	m_list.SetColumnHeader(strTitle);
	m_list.SetGridLines(TRUE);



	/*m_list.InsertItem( 0 , _T(""));
	
	m_list.SetItemText(0, 0, "江山店[12555]");
	m_list.SetItemText(0, 1, "浙江省杭州市文一西路75号");
	m_list.SetItemText(0, 2, "abc");
	m_list.SetItemText(0, 3, "0571-89898989");
	m_list.SetItemText(0, 4, "发送请求");
	m_list.SetItemURL(0, 4,"","");

	ServiceData sdata;
	strcpy(sdata.Number,"江山店[12555]");
	strcpy(sdata.Address,"浙江省杭州市文一西路75号");
	strcpy(sdata.Name,"cab");
	strcpy(sdata.Tel,"0571-89898989");
	m_servicedata.Add(sdata);


	m_list.InsertItem(1, _T(""));

	m_list.SetItemText(1, 0, "北京店[2553]");
	m_list.SetItemText(1, 1, "北京市海淀区");
	m_list.SetItemText(1, 2, "efg");
	m_list.SetItemText(1, 3, "0571-12345678");
	m_list.SetItemText(1, 4, "发送请求");
	m_list.SetItemURL(1, 4,"", "");

	strcpy(sdata.Number,"北京店[2553]");
	strcpy(sdata.Address,"北京市海淀区75号");
	strcpy(sdata.Name,"feg");
	strcpy(sdata.Tel,"0571-12345678");
	m_servicedata.Add(sdata);*/


	SetResize(IDC_TREE1, SZ_TOP_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_LIST1, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
	//SetResize(IDC_PIC,SZ_TOP_CENTER,SZ_BOTTOM_CENTER);
	//SetResize(IDC_SHOW,SZ_TOP_RIGHT,SZ_BOTTOM_RIGHT);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
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
	tvInsert.item.pszText = _T("中国");

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
	int num = (int)lParam;//点击的是第几个数据条数
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
	dlg.m_number += "服务站";
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
		strTitle.Format(_T("服务站名/编号, %d, 1; 地址, %d, 1; 联系人, %d, 1;电话, %d, 1;请求, %d, 1"),(int)(0.15*rect.Width()),(int)(0.45*rect.Width()),(int)(0.1*rect.Width()),(int)(0.2*rect.Width()),(int)(0.1*rect.Width()));

		//m_list.SetColumnHeader(strTitle);
	}
	// TODO: 在此处添加消息处理程序代码
}

void CDlgService::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	HTREEITEM selectHtm = mTreeMain.GetSelectedItem();
	CString strSelect = mTreeMain.GetItemText(selectHtm);

	//得到父节点句柄
	HTREEITEM parentHtm = mTreeMain.GetParentItem(selectHtm);
	CString parStr = mTreeMain.GetItemText(parentHtm);

	if (parStr==_T("中国")||parStr==_T(""))
		return;

	//MessageBox("您选中的是:" + parStr + " " + strSelect);
	
		
	curInput.input = parStr+"|"+ strSelect;
	curInput.curpage =1;
	curInput.record = 20;
	//curInput.customid = "0";
	//CWLRClientDlg *pDlg=(CWLRClientDlg*)AfxGetApp()->GetMainWnd();
	
		
	
	strIn.Province = parStr.GetBuffer();
	strIn.City = strSelect.GetBuffer();
	
	m_servicedata.RemoveAll();
		
	//开启线程来处理
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
//处理消息刷新
LONG CDlgService::OnFresh(WPARAM w, LPARAM l)
{
	//往listctrl里插入数据
	m_list.DeleteAllItems();
	CString str,temp;
	for (unsigned int i=0;i<input.size();i++)
	{
		ServiceData sdata;
		strcpy(sdata.cprovince,strIn.Province.c_str());//省
		strcpy(sdata.ccity,strIn.City.c_str());//市
	
		m_list.InsertItem( i , _T(""));
		str = input.at(i).serviceName.c_str();
		strcpy(sdata.serviceN,str);//服务站名称
		str += "[";
		str += input.at(i).serviceNo.c_str();
		str +="]";
		temp = input.at(i).serviceNo.c_str();
		strcpy(sdata.Number,temp);//编号
		m_list.SetItemText(i, 0, str);
	
		str = input.at(i).serviceAddr.c_str();
		strcpy(sdata.Address,str);//地址
		m_list.SetItemText(i, 1, str);
	
		str = input.at(i).servicePerson.c_str();
		strcpy(sdata.Name,str);//联系人
		m_list.SetItemText(i, 2, str);
	
		str = input.at(i).tel.c_str();
		strcpy(sdata.Tel,str);//电话号码
		m_list.SetItemText(i, 3, str);
	
		m_list.SetItemText(i, 4, "发送请求");
		m_list.SetItemURL(i, 4,"","");
			
		str = input.at(i).recordID.c_str();
	
		strcpy(sdata.serviceID,str);//服务站ID
	
		m_servicedata.Add(sdata);
	}
	GetDlgItem(IDC_PIC)->ShowWindow(FALSE);
	GetDlgItem(IDC_SHOW)->ShowWindow(FALSE);
	return 0;
}