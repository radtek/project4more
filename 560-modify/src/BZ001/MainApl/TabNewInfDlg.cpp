// TabNewInfDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WLRClient.h"
#include "TabNewInfDlg.h"
#include "SendPhoneMsgDlg.h"
#include "CommDef.h"
#include "header.h"

extern UserInfo user;
// CTabNewInfDlg 对话框
CStringArray m_data;
IMPLEMENT_DYNAMIC(CTabNewInfDlg, CDialog)
int nnewhy=0;
int nnewcy=0;
int nnewld=0;

CRITICAL_SECTION csStop;
int nSSset = 0;//搜索的参数
// 构造函数
CTabNewInfDlg::CTabNewInfDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTabNewInfDlg::IDD, pParent)
{
    isInit = false;
    ifShowPhone = true;
    curType = 0;
    curInput.record = 10;
    curInput.curpage = 1;
    curInput.customid = "0";
    // 初始化svrIO
    svrIO = NULL;

    // 设置标题字体
    //LOGFONT titleFont;
    lstrcpy((LPSTR)titleFont.lfFaceName,(LPSTR)"黑体"); 
    titleFont.lfWeight=400; 
    titleFont.lfWidth=0; 
    titleFont.lfHeight=14; // 字体大小 
    titleFont.lfEscapement=0; 
    titleFont.lfUnderline=FALSE; 
    titleFont.lfItalic=FALSE; 
    titleFont.lfStrikeOut=FALSE; 
    titleFont.lfCharSet=GB2312_CHARSET; //以上参数好像一个都不能少

    // 设置数据内容字体
    //LOGFONT logfont;
    lstrcpy((LPSTR)contentFont.lfFaceName,(LPSTR)"新宋体"); 
    contentFont.lfWeight=400; 
    contentFont.lfWidth=0; 
    contentFont.lfHeight=16; // 字体大小 
    contentFont.lfEscapement=0; 
    contentFont.lfUnderline=FALSE; 
    contentFont.lfItalic=FALSE; 
    contentFont.lfStrikeOut=FALSE; 
    contentFont.lfCharSet=GB2312_CHARSET; //以上参数好像一个都不能少

    // 初始化标题内容
    //titleData.startPlace = "浙江省杭州市";
    //titleData.endPlace = "江苏省南京市";
    //titleData.record= "最新信息";

    // 初始化信息内容
    //contentData.push_back(titleData);
}

CTabNewInfDlg::~CTabNewInfDlg()
{
	//m_bEnd = TRUE;
	//WaitForSingleObject(MyThread,INFINITE);
}

void CTabNewInfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabNewInfDlg)
	DDX_Control(pDX, IDC_TAB_NEW_INF_LIST, m_Grid); // associate the grid window with a C++ object
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_TAB_NEW_PREV, btnPrev);
	DDX_Control(pDX, IDC_TAB_NEW_NEXT, btnNext);
	DDX_Control(pDX, IDC_PIC, m_Picture);
	//DDX_Control(pDX, IDC_BUTTON_LOCAL, m_btnLocal);
	//DDX_Control(pDX, IDC_BUTTON_CANCEL_SEARCH, m_btnCancelSearch);
	//DDX_Control(pDX, IDC_BUTTON_SECRECY, m_btnSecrecy);
	//DDX_Control(pDX, IDC_BUTTON_STOP_REFRESH, m_btnStopRefresh);
	//DDX_Control(pDX, IDC_EDID_START_ADDR, m_editStartAddr);
	//DDX_Control(pDX, IDC_EDID_DEST_ADDR, m_editDestAddr);
	DDX_Control(pDX, IDC_TAB_NEW_UPTOP, m_btnTopPage);
	DDX_Control(pDX, IDC_TAB_NEW_BOTTOM_DOWN, m_btnBottomPage);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_btnSearch);
	DDX_Control(pDX, IDC_BUTTON_STOP_REFRESH, m_btnStopRefresh);
	DDX_Control(pDX, IDC_BUTTON_HIDE_PHONE_NUM, m_btnHidePhoneNum);
}


BEGIN_MESSAGE_MAP(CTabNewInfDlg, CDialog)
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
    ON_NOTIFY(NM_RCLICK, IDC_TAB_NEW_INF_LIST, OnGridRClick)
    //ON_NOTIFY(NM_DBLCLK, IDC_TAB_NEW_INF_LIST, OnGridRClick)
    ON_COMMAND(ID_MENU_OPERATION_SENDMSG, &CTabNewInfDlg::OnMenuSendmsgSendmsg)
    ON_BN_CLICKED(IDC_TAB_NEW_PREV, &CTabNewInfDlg::OnBnClickedTabNewPrev)
    ON_BN_CLICKED(IDC_TAB_NEW_NEXT, &CTabNewInfDlg::OnBnClickedTabNewNext)

	ON_MESSAGE(WM_SETGRID,OnFresh)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	/*ON_BN_CLICKED(IDC_BUTTON_LOCAL, &CTabNewInfDlg::OnBnClickedButtonLocal)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL_SEARCH, &CTabNewInfDlg::OnBnClickedButtonCancelSearch)
	ON_BN_CLICKED(IDC_BUTTON_SECRECY, &CTabNewInfDlg::OnBnClickedButtonSecrecy)
	ON_BN_CLICKED(IDC_BUTTON_STOP_REFRESH, &CTabNewInfDlg::OnBnClickedButtonStopRefresh)
	ON_EN_CHANGE(IDC_EDID_START_ADDR, &CTabNewInfDlg::OnEnChangeEdidStartAddr)*/
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CTabNewInfDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_STOP_REFRESH, &CTabNewInfDlg::OnBnClickedButtonStopRefresh)
	ON_BN_CLICKED(IDC_BUTTON_HIDE_PHONE_NUM, &CTabNewInfDlg::OnBnClickedButtonHidePhoneNum)
END_MESSAGE_MAP()

// 自动改变控件位置大小
BEGIN_EASYSIZE_MAP(CTabNewInfDlg)
    // EASYSIZE(control,left,top,right,bottom,options)
	EASYSIZE(IDC_TAB_NEW_INF_LIST, ES_BORDER, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	EASYSIZE(IDC_TAB_NEW_BOTTOM_DOWN, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_KEEPSIZE, 0)
	EASYSIZE(IDC_TAB_NEW_NEXT, ES_KEEPSIZE, ES_BORDER, IDC_TAB_NEW_BOTTOM_DOWN, ES_KEEPSIZE, 0)
	EASYSIZE(IDC_TAB_NEW_PREV, ES_KEEPSIZE, ES_BORDER, IDC_TAB_NEW_NEXT, ES_KEEPSIZE, 0)
	EASYSIZE(IDC_TAB_NEW_UPTOP, ES_KEEPSIZE, ES_BORDER, IDC_TAB_NEW_PREV, ES_KEEPSIZE, 0)
	EASYSIZE(IDC_BUTTON_HIDE_PHONE_NUM, ES_KEEPSIZE, ES_BORDER, IDC_TAB_NEW_UPTOP, ES_KEEPSIZE, 0)
	EASYSIZE(IDC_BUTTON_STOP_REFRESH, ES_KEEPSIZE, ES_BORDER, IDC_BUTTON_HIDE_PHONE_NUM, ES_KEEPSIZE, 0)
	EASYSIZE(IDC_BUTTON_SEARCH, ES_KEEPSIZE, ES_BORDER, IDC_BUTTON_STOP_REFRESH, ES_KEEPSIZE, 0)
	
    
    
END_EASYSIZE_MAP

// CTabNewInfDlg 消息处理程序

BOOL CTabNewInfDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化
	//
	if (m_Picture.Load(MAKEINTRESOURCE(IDR_WAIT),_T("GIF")))
	{
		m_Picture.Draw();
	}
    // 初始化Grid控件
    initGrid();

    // 初始化按钮
    btnPrev.LoadBitmap(IDB_PREVPAGE);
    btnNext.LoadBitmap(IDB_NEXTPAGE);
	m_btnTopPage.LoadBitmap(IDB_TOP_PAGE);
	m_btnBottomPage.LoadBitmap(IDB_BOTTOM_PAGE);


	m_btnSearch.LoadBitmap(IDB_LOCAL);//
	m_btnStopRefresh.LoadBitmap(IDB_STOP_REFRESH);
	m_btnHidePhoneNum.LoadBitmap(IDB_SECRECY);
	
	/*btnPrev.ShowWindow(SW_HIDE);
	btnNext.ShowWindow(SW_HIDE);*/

	/*m_btnLocal.LoadBitmap(IDB_LOCAL);
	m_btnCancelSearch.LoadBitmap(IDB_CANCEL);
	m_btnSecrecy.LoadBitmap(IDB_SECRECY);
	m_btnStopRefresh.LoadBitmap(IDB_STOP_REFRESH);*/

	InitializeCriticalSection(&csStop);
	//DWORD PID;
	//MyEvent=CreateEvent(NULL,TRUE,TRUE,NULL);
	//MyThread=CreateThread(NULL,0,ProcMore,this,0,&PID);//定时刷新的数据采集
	//ResetEvent(MyEvent);

	m_bStart = TRUE;
	m_bEnd = FALSE;
	
	//SetTimer(1,50,NULL);
	//SetEvent()

    // 初始化自动调整控件位置
    INIT_EASYSIZE;
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void CTabNewInfDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);
    UPDATE_EASYSIZE;  // 自动改变控件位置大小

    // TODO: 在此处添加消息处理程序代码
	CRect rect;
    GetClientRect(&rect);
    // 当最小化时
	if(rect.Width() < 1 || rect.Height() < 1) {
        return;
    }

	if (GLB::ifMiniSize) {
		return;
	}

    if (isInit) {
        initGrid();
        setData(curType);
    }
}
    
// 初始化表格
int CTabNewInfDlg::initGrid() {
	int m_nFixRows = 0; 
	int m_nCols = 4;
    CRect rect;
    GetDlgItem(IDC_TAB_NEW_INF_LIST)->GetWindowRect(rect); //得到显示区域
    int spaceWidth = 0;
    int colWidth1 = spaceWidth;
    int colWidth2 = spaceWidth;
    int colWidth3 = rect.Width() - colWidth1 - colWidth2 - 20;//- 20;//-20;
    int colWidth4 = 20;

	TRY {	    
		m_Grid.SetColumnCount(m_nCols);
		m_Grid.SetFixedRowCount(m_nFixRows);
		    //m_Grid.SetFixedColumnCount(m_nFixCols);
        m_Grid.SetEditable(false); // 不可编辑
        
        // 设置列宽
        m_Grid.SetColumnWidth(0, colWidth1); // 设置第1列的列宽
        m_Grid.SetColumnWidth(1, colWidth2); // 设置第2列的列宽
        m_Grid.SetColumnWidth(2, colWidth3); // 设置第3列的列宽
        m_Grid.ExpandLastColumn(); // 调整最后一列的宽度以添满grid区域.

        // 自动行高
        //m_Grid.SetAutoSizeStyle(GVS_BOTH);

        // 取消标题提示
        m_Grid.EnableTitleTips(false);//.EnableToolTips(false);
        // 取消点击固定标题现在对应列
        m_Grid.SetFixedColumnSelection(false);
        // 设置同行/列中的固定单元格作为焦点单元格时是否高亮显示并且使用凹陷边缘
        m_Grid.SetTrackFocusCell(false);
        // 设置焦点单元格是否高亮显示并且加上外边框
        m_Grid.SetFrameFocusCell(false);
        // 取消拖放功能
        m_Grid.EnableDragAndDrop(false);
        // 设置是否可设置行的大小
        m_Grid.SetRowResize(false);
        // 设置是否可设置列的大小
        m_Grid.SetColumnResize(false);
        // 设置是否可以通过鼠标将列的宽度压缩为0
        m_Grid.EnableColumnHide(false);
        // 设置是否可以通过鼠标将行的高度压缩为0
        m_Grid.EnableRowHide(false);
        // 设置单元格是否可选
        m_Grid.EnableSelection(false);

        // 设置成列表模式
        m_Grid.SetListMode();
        // 设置每次只选择一行，必须和列表模式一起使用
        m_Grid.SetSingleRowSelection();  

        // 设置网格线：只有横线
        m_Grid.SetGridLines(GVL_HORZ);

        // 设置双倍缓存
        m_Grid.SetDoubleBuffering();

        // 设置初始化标志
        isInit = true;
	}
	CATCH (CMemoryException, e)
	{
	   	e->ReportError();
    	return -1;
	}
    END_CATCH   
    return 0;
}
    
// 计算行数
int CTabNewInfDlg::calRow()
{
    CRect rect;
    GetDlgItem(IDC_TAB_NEW_INF_LIST)->GetWindowRect(rect); // 得到显示区域
    if (rect.Width() > 800) {
        curInput.record = rect.Height()/(abs(contentFont.lfHeight) + 10);
    } else {
        curInput.record = (rect.Height()/abs(contentFont.lfHeight))/2;
    }
    return 0;
}

// 设置数据
int CTabNewInfDlg::setData(int type, int curpage)
{
	//EnterCriticalSection(&csPrint);
	m_bStart = FALSE;
    if (svrIO == NULL) {
        return -1;
    }
	//EnterCriticalSection(&csPrint);
    curType = type;
    if (-1 != curpage) { // -1: 保留当前curpage
        curInput.curpage = curpage;
    }
    calRow();
    // 设置标题数据

	struct _TabNewInfRecord {
    string totalNum;   // total record number
    string returnNum;  // return record number
    string recordID;   // this record id
    string startPlace; // start place
    string endPlace;   // arrive place
    string record;     // record information
    string tel;        // tel information
    string pubUID;     // the user id of pub this record
	};

	vector<TabNewInfRecord> * pcontentData = new vector<TabNewInfRecord>();
	//xqh:
	//内存空间,会导致pcontentData的调用失败，再次取消ZeroMemory
	//ZeroMemory(pcontentData,sizeof vector<TabNewInfRecord>);
    TabNewInfRecord title;
    title.startPlace = "出发地";
    title.endPlace = "到达地";
	contentData.clear();
	pcontentData->clear();
	
    switch (curType) {
        case 0: // 货源
			
		//	m_editStartAddr.SetWindowText(_T(""));
		//	m_editDestAddr.SetWindowText(_T(""));

			title.record = "最新货源信息";
			//svrIO->getNewGoodsInf(contentData, curInput);
			
			if (contentDataHY.size() != 0)
			{
				int len = contentDataHY.size();
				if (len < curInput.record)
				{
					for (int i=0;i<len;i++)
					{
						if (contentDataHY[i].recordID != "")
						{
							pcontentData->push_back(contentDataHY[i]);
							contentData.push_back(contentDataHY[i]);
						}

					}
				}
				else
				{
					for (int i=(curInput.curpage-1)*curInput.record;i<curInput.curpage*curInput.record;i++)
					{

						if (i == len && len < curInput.curpage*curInput.record && len > (curInput.curpage-1)*curInput.record)
						{
							break;
						}
						if (curInput.curpage*curInput.record > RECORD_NUM|| (curInput.curpage-1)*curInput.record > RECORD_NUM)
						{

							pcontentData->clear();
							//svrIO->getNewGoodsInf(contentData, curInput);
							TRACE("ok0  =  %d\n");
							nSSset = 10;
							DWORD PID;
							HANDLE Main_Thread;
							Main_Thread=CreateThread(NULL,0,ProcMore,this,0,&PID);
							//LeaveCriticalSection(&csPrintMore);
							//LeaveCriticalSection(&csPrint);
							CloseHandle(Main_Thread);
							return 0;
							break;
						}
						if (contentDataHY[i].recordID != "")
						{
							pcontentData->push_back(contentDataHY[i]);
							contentData.push_back(contentDataHY[i]);
						}

					}
				}
			}
			break;
        case 1: // 零担
            title.record = "最新零担信息";
			//pcontentData->clear();
			if (contentDataLD.size() != 0)
			{
				int len = contentDataLD.size();
				if (len < curInput.record)
				{
					for (int i=0;i<len;i++)
					{
						if (contentDataLD[i].recordID != "")
						{
							pcontentData->push_back(contentDataLD[i]);
							contentData.push_back(contentDataLD[i]);
						}
					}
				}
				else
				{
					for (int i=(curInput.curpage-1)*curInput.record;i<curInput.curpage*curInput.record;i++)
					{
						if (i == len && len < curInput.curpage*curInput.record && len > (curInput.curpage-1)*curInput.record)
						{
							break;
						}
						if (curInput.curpage*curInput.record > RECORD_NUM|| (curInput.curpage-1)*curInput.record > RECORD_NUM)
						{
							//SuspendThread(hThread);

							//Sleep(100);
							pcontentData->clear();
							//svrIO->getNewGoodsInf(contentData, curInput);
							TRACE("ok0  =  %d\n");
							nSSset = 11;
							m_bStart = TRUE;
							DWORD PID;
							HANDLE Main_Thread;
							//EnterCriticalSection(&csStop);
							Main_Thread=CreateThread(NULL,0,ProcMore,this,0,&PID);
							//LeaveCriticalSection(&csStop);
							//LeaveCriticalSection(&csPrint);
							CloseHandle(Main_Thread);
							return 0;
						}
						if (contentDataLD[i].recordID != "")
						{
							pcontentData->push_back(contentDataLD[i]);
							contentData.push_back(contentDataLD[i]);
						}

					}
				}
			}
            //svrIO->getNewBulkGoodsInf(contentData, curInput);
            break;
        case 2: // 车源
		//	m_editStartAddr.SetWindowText(_T(""));
		//	m_editDestAddr.SetWindowText(_T(""));

            title.record = "最新车源信息";
			//contentData.clear();
			//pcontentData->clear();
			if (contentDataCY.size() != 0)
			{
				int len = contentDataCY.size();
				if (len < curInput.record)
				{
					for (int i=0;i<len;i++)
					{
						if (contentDataCY[i].recordID != "")
						{
							pcontentData->push_back(contentDataCY[i]);
							contentData.push_back(contentDataCY[i]);
						}
					}
				}
				else
				{
					for (int i=(curInput.curpage-1)*curInput.record;i<curInput.curpage*curInput.record;i++)
					{
						if (i == len && len < curInput.curpage*curInput.record && len > (curInput.curpage-1)*curInput.record)
						{
							break;
						}
						if (curInput.curpage*curInput.record > RECORD_NUM|| (curInput.curpage-1)*curInput.record > RECORD_NUM)
						{
							//SuspendThread(hThread);

							//Sleep(100);
							//pcontentData->clear();
							//svrIO->getNewGoodsInf(contentData, curInput);
							TRACE("ok0  =  %d\n");
							nSSset = 12;
							m_bStart = TRUE;
							DWORD PID;
							HANDLE Main_Thread;
							Main_Thread=CreateThread(NULL,0,ProcMore,this,0,&PID);
							CloseHandle(Main_Thread);
							//LeaveCriticalSection(&csPrint);
							return 0;
						}
						if (contentDataCY[i].recordID != "")
						{
							pcontentData->push_back(contentDataCY[i]);
							//TRACE(contentDataCY[i].recordID.c_str());
							//TRACE("\n");
							contentData.push_back(contentDataCY[i]);
						}

					}
				}
			}
            //svrIO->getNewCarsInf(contentData, curInput);
            break;
        case 3: // 搜索：货源
            title.record = "搜索到的货源信息";
			//contentData.clear();
			//SuspendThread(hThread);
			//Sleep(200);
			pcontentData->clear();
			nSSset = 0;
			DWORD PID;
			HANDLE Main_Thread;
			Main_Thread=CreateThread(NULL,0,ThreadFuncSS,this,0,&PID);
			CloseHandle(Main_Thread);

            break;
        case 4: // 搜索：零担
            title.record = "搜索到的零担信息";
			//contentData.clear();
			//SuspendThread(hThread);
			//Sleep(200);
			pcontentData->clear();
			nSSset = 1;
			Main_Thread=CreateThread(NULL,0,ThreadFuncSS,this,0,&PID);
			CloseHandle(Main_Thread);
            break;
        case 5: // 搜索：车源
            title.record = "搜索到的车源信息";
			//contentData.clear();
			//SuspendThread(hThread);
			pcontentData->clear();
			nSSset = 2;
			Main_Thread=CreateThread(NULL,0,ThreadFuncSS,this,0,&PID);
			CloseHandle(Main_Thread);

            break;
        case 6: // 点击搜索：货源
            title.record = "搜索到的货源信息";
			//contentData.clear();
			//SuspendThread(hThread);
			pcontentData->clear();
			nSSset = 3;
			Main_Thread=CreateThread(NULL,0,ThreadFuncSS,this,0,&PID);
            break;
        case 7: // 点击搜索：零担
            title.record = "搜索到的零担信息";
			//contentData.clear();
			//SuspendThread(hThread);
			pcontentData->clear();
			nSSset = 4;
			Main_Thread=CreateThread(NULL,0,ThreadFuncSS,this,0,&PID);
			CloseHandle(Main_Thread);
            break;
        case 8: // 点击搜索：车源
            title.record = "搜索到的车源信息";
			//contentData.clear();
			//SuspendThread(hThread);
			pcontentData->clear();
			nSSset = 5;
			Main_Thread=CreateThread(NULL,0,ThreadFuncSS,this,0,&PID);
			CloseHandle(Main_Thread);
            break;
        default:
            break;
    }
    
    titleData = title;
	
    // 设置最大页数
	if (pcontentData->size() > 0) {
		maxPageNum = atoi(pcontentData->at(0).totalNum.c_str()) / curInput.record;
		int n =atoi(pcontentData->at(0).totalNum.c_str()) % curInput.record;
		if (n == 0)
		{

		} 
		else
		{
			maxPageNum += 1;
		}
		if (maxPageNum < 1) {
			maxPageNum = 1;
		}
	}
	//vector<TabNewInfRecord>*newdata(&contentData);
    // 设置表格   
	try
	{
		 setGrid(pcontentData);
	}
	catch (...)
	{
		
	}

	//ClearVector(*pcontentData);
	//LeaveCriticalSection(&csPrint);
	//LeaveCriticalSection(&csPrint);
    return 0;
}
    
// 设置Grid控件
int CTabNewInfDlg::setGrid(vector<TabNewInfRecord> * pcontentData)
{
	//EnterCriticalSection(&csPrintFresh);
	//EnterCriticalSection(&csPrintOther);
	//vector<TabNewInfRecord> contentData1(pcontentData->begin(),pcontentData->end());
    int m_nRows = pcontentData->size();
	//contentData.resize(m_nRows);
    m_Grid.SetRowCount(m_nRows);

    /****************** 设置内容 ******************/

    // 设置网格线颜色
    m_Grid.SetGridColor(svrIO->myColor.gridClr);

    // 定义行背景色
    COLORREF rowBKClr = svrIO->myColor.oddRowBKClr;
    // 定义行文字色
    COLORREF rowFgClr = svrIO->myColor.oddRowFgClr;
    // 开关变量
    bool ifOddRow = true;    

    int row = 0;
    int colWidth3 = m_Grid.GetColumnWidth(2);
    vector<TabNewInfRecord>::iterator iter = pcontentData->begin();
	//vector<TabNewInfRecord>::iterator iterend = contentData1.end();
    while (iter != pcontentData->end()) {
        if (ifOddRow) {
            setCridContentFont(svrIO->oddFont);
            rowBKClr = svrIO->myColor.oddRowBKClr;
            rowFgClr = svrIO->myColor.oddRowFgClr;
            ifOddRow = false;
        } else {
            setCridContentFont(svrIO->evenFont); 
            rowBKClr = svrIO->myColor.evenRowBKClr;
            rowFgClr = svrIO->myColor.evenRowFgClr;
            ifOddRow = true;
        }   
        m_Grid.SetItemFont(row, 0, &contentFont);
        m_Grid.SetItemFont(row, 1, &contentFont);
        m_Grid.SetItemFont(row, 2, &contentFont);

        string tmpStr;
        if (ifShowPhone) { 
            //tmpStr = "【" + (*iter).startPlace + "→" + (*iter).endPlace +"】" + (*iter).record + (*iter).tel;
            tmpStr = "编号:" + (*iter).recordID + "【" + (*iter).startPlace + "→" + (*iter).endPlace +"】" 
                          + (*iter).record + (*iter).tel;
        } else {
            //tmpStr = "【" + (*iter).startPlace + "→" + (*iter).endPlace +"】" + (*iter).record;
            tmpStr = "编号:" + (*iter).recordID + "【" + (*iter).startPlace + "→" + (*iter).endPlace +"】" 
                          + (*iter).record;
        }        
        CString str3 = tmpStr.c_str();

        // 插入第1列
        // 设置属性
  		GV_ITEM Item1;        
        Item1.row = row;
        Item1.col = 0;
        Item1.mask = GVIF_TEXT|GVIF_FORMAT|GVIF_BKCLR|GVIF_FGCLR;
        Item1.nFormat = DT_LEFT|DT_EXTERNALLEADING|DT_WORDBREAK;
        Item1.crBkClr = rowBKClr;
        Item1.crFgClr = rowFgClr;        
        //CString str;
        //str.Format(_T("%d"), row);
        //Item1.strText = str1;
        m_Grid.SetItem(&Item1);

        // 插入第2列
        // 设置属性
        GV_ITEM Item2;
        Item2.row = row;
        Item2.col = 1;
        Item2.mask = GVIF_TEXT|GVIF_FORMAT|GVIF_BKCLR|GVIF_FGCLR;				    
        Item2.nFormat = DT_LEFT|DT_EXTERNALLEADING|DT_WORDBREAK;
        Item2.crBkClr = rowBKClr;
        Item2.crFgClr = rowFgClr;        
        //Item2.strText = str2;
        m_Grid.SetItem(&Item2);

        // 插入第3列
        // 设置属性
  		GV_ITEM Item3;        
        Item3.row = row;
        Item3.col = 2; 
        Item3.mask = GVIF_TEXT|GVIF_FORMAT|GVIF_BKCLR|GVIF_FGCLR;       
        Item3.nFormat = DT_LEFT|DT_EXTERNALLEADING|DT_WORDBREAK;        
        Item3.crBkClr = rowBKClr;
        Item3.crFgClr = rowFgClr;   
        Item3.strText = str3;
        m_Grid.SetItem(&Item3);

        // 插入保留列
        GV_ITEM Item4;        
        Item4.row = row;
        Item4.col = 3; 
        Item4.mask = GVIF_TEXT|GVIF_FORMAT|GVIF_BKCLR|GVIF_FGCLR;       
        Item4.nFormat = DT_LEFT|DT_EXTERNALLEADING|DT_WORDBREAK;        
        Item4.crBkClr = rowBKClr;
        Item4.crFgClr = rowFgClr;   
        //Item4.strText = str3;
        m_Grid.SetItem(&Item4);

        // 设置行高
        // 计算需要的行高        
        CSize size3 = m_Grid.GetTextExtent(row, 2, str3);
        int n3 = size3.cx / (colWidth3-12);
        if (0 != size3.cx%(colWidth3-12)) {
            ++n3; 
        } 
        int lineHeight3 = n3*(size3.cy - 12) + 12;
        m_Grid.SetRowHeight(row, lineHeight3);	

        ++row;
        ++iter;
    }

    if (ifOddRow) {
        // 设置控件的背景颜色 (单元格之外的区域).
        m_Grid.SetBkColor(svrIO->myColor.oddRowBKClr);
    } else {
        // 设置控件的背景颜色 (单元格之外的区域).
        m_Grid.SetBkColor(svrIO->myColor.evenRowBKClr);
    }

    // 刷新
    m_Grid.Refresh();
	//ClearVector(*pcontentData);
	//LeaveCriticalSection(&csPrintFresh);
	//LeaveCriticalSection(&csPrintOther);

    return 0;
}
    
// NM_RCLICK
void CTabNewInfDlg::OnGridRClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    //CString str;
    //str.Format(_T("选中行为： %d"), pItem->iRow);
    //AfxMessageBox(str);
    // 获取当前选择的行
    curSelRow = pItem->iRow;
    if (curSelRow < 0) {
        return;
    }

    // 设置弹出菜单
    CPoint   point; 
    ::GetCursorPos(&point);     			
    CMenu menu;//菜单
    CMenu* pPopupMenu;//菜单指针
    menu.LoadMenu(IDR_MENU_OPERATION);//加载ID为IDR_MENU1的菜单
    pPopupMenu = menu.GetSubMenu(0);   //获取弹出菜单的第一层子菜单的类指针

    //弹出菜单函数，第一个参数表示快捷菜单的下边界与由参数y指定的坐标对齐 
	//第二和第三个为x、y坐标，第四个表示拥有此菜单的窗口句柄，
	//第五个默认为NULL,表示当用户在菜单以外的区域按鼠标键时，菜单会消失
	pPopupMenu->TrackPopupMenu(TPM_TOPALIGN,point.x,point.y,this,NULL);
}
    
// 弹出菜单：发短信
void CTabNewInfDlg::OnMenuSendmsgSendmsg()
{
    // TODO: 在此添加命令处理程序代码
    int index = curSelRow;
    string tmp = contentData.at(index).startPlace + "->" + contentData.at(index).endPlace
        + "。" + contentData.at(index).record+ contentData.at(index).tel;
    CSendPhoneMsgDlg dlg;
    dlg.phoneMsg = tmp.c_str();
    if (dlg.DoModal() == IDOK) {
		sphonenum = (LPTSTR)(LPCTSTR)dlg.phoneNumber;
		sphonetext = (LPTSTR)(LPCTSTR)dlg.phoneMsg;
		//SuspendThread(hThread);
//         string result = svrIO->sendPhoneMessage((LPTSTR)(LPCTSTR)dlg.phoneNumber, (LPTSTR)(LPCTSTR)dlg.phoneMsg);
// 
//         if (result == "TRUE") {
//             MessageBox("短信发送成功！","发送短信");
//         } else {
//             MessageBox(result.c_str(),"短信发送失败");
//         }
		nSSset = 20;
		DWORD PID;
		HANDLE Main_Thread;
		Main_Thread=CreateThread(NULL,0,ProcMore,this,0,&PID);
    }
}
        
// set grid content font
int CTabNewInfDlg::setCridContentFont(SettingFont& font)
{
    lstrcpy((LPSTR)contentFont.lfFaceName, (LPSTR)font.lfFaceName.c_str()); 
    contentFont.lfWeight = font.lfWeight; 
    contentFont.lfWidth = font.lfWidth; 
    contentFont.lfHeight = font.lfHeight;  
    contentFont.lfEscapement = font.lfEscapement; 
    contentFont.lfUnderline = font.lfUnderline; 
    contentFont.lfItalic = font.lfItalic; 
    contentFont.lfStrikeOut = font.lfStrikeOut; 
    contentFont.lfCharSet = font.lfCharSet;
    return 0;
}
    
// 前一页
void CTabNewInfDlg::OnBnClickedTabNewPrev()
{
    // TODO: 在此添加控件通知处理程序代码
    if(curInput.curpage <= 1) {
        return;
    }

    curInput.curpage -= 1;
    setData(curType, curInput.curpage);
	Invalidate(TRUE);
}
    
// 后一页
void CTabNewInfDlg::OnBnClickedTabNewNext()
{
    // TODO: 在此添加控件通知处理程序代码
    if(curInput.curpage == maxPageNum) {
        return;
    }

    curInput.curpage += 1;
    setData(curType, curInput.curpage);
	Invalidate(TRUE);
}


//搜索处理线程
DWORD CTabNewInfDlg::ThreadFuncSS(LPVOID p)
{
	CoInitialize(NULL);
	CTabNewInfDlg * dlg = (CTabNewInfDlg*)p;
	if (csPrintOther.LockCount == 0) return -1;
	dlg->GetDlgItem(IDC_PIC)->ShowWindow(TRUE);
	dlg->GetDlgItem(IDC_SHOW)->ShowWindow(TRUE);
	EnterCriticalSection(&csPrintOther);	
	vector<TabNewInfRecord> * pcontentData = new vector<TabNewInfRecord>();
	//ZeroMemory(pcontentData,sizeof vector<TabNewInfRecord>);
	//while(1)
	{
		int nstat = -1;

		switch (nSSset)
		{
		case 0:
			nstat = dlg->svrIONew->getSearchGoodsInf(dlg->goodsKeyword, *pcontentData, dlg->curInput);
			break;
		case 1:
			nstat = dlg->svrIONew->getSearchBulkGoodsInf(dlg->bulkGoodsKeyword, *pcontentData, dlg->curInput);
			break;
		case 2:
			nstat = dlg->svrIONew->getSearchCarsInf(dlg->carsKeyword, *pcontentData, dlg->curInput);
			break;
		case 3:
			nstat = dlg->svrIONew->getClickSearchGoodsInf(dlg->clickKeyWord, *pcontentData, dlg->curInput);
			break;
		case 4:
			nstat = dlg->svrIONew->getClickSearchBulkGoodsInf(dlg->clickKeyWord, *pcontentData, dlg->curInput);
			break;
		case 5:
			nstat = dlg->svrIONew->getClickSearchCarsInf(dlg->clickKeyWord, *pcontentData, dlg->curInput);
			break;
		}
		if (nstat == 0)
		{
			//break;
		}
		//Sleep(100);
	}

	
	if (pcontentData->size() > 0) {
		dlg->maxPageNum = atoi(pcontentData->at(0).totalNum.c_str()) / dlg->curInput.record;
		int n =atoi(pcontentData->at(0).totalNum.c_str()) % dlg->curInput.record;
		if (n == 0)
		{

		} 
		else
		{
			dlg->maxPageNum += 1;
		}
		if (dlg->maxPageNum < 1) {
			dlg->maxPageNum = 1;
		}
	}
	dlg->contentData = *pcontentData;
	//vector<TabNewInfRecord> *newdata(&dlg->contentData);
	// 设置表格   
	try
	{
		::PostMessage(dlg->GetSafeHwnd(),WM_SETGRID,(WPARAM)pcontentData,0);
	}
	catch (...)
	{

	}
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
 	//ClearVector(*pcontentData);
	LeaveCriticalSection(&csPrintOther);
	CoUninitialize();
	return 0;
}

//处理消息刷新
LONG CTabNewInfDlg::OnFresh(WPARAM w, LPARAM l)
{
	vector<TabNewInfRecord> * data = (vector<TabNewInfRecord> *)w;
	try
	{
		setGrid((vector<TabNewInfRecord> *)w);
	}
	catch (...)
	{

	}
	GetDlgItem(IDC_PIC)->ShowWindow(FALSE);
	GetDlgItem(IDC_SHOW)->ShowWindow(FALSE);

	return 0;
}

DWORD CTabNewInfDlg::ProcMore(LPVOID p)
{
	CoInitialize(NULL);
	CTabNewInfDlg * dlg = (CTabNewInfDlg*)p;
	//DWORD dwWait;
	if (csPrintMore.LockCount == 0) return -1;
	/**/
	EnterCriticalSection(&csPrintMore);
	vector<TabNewInfRecord> * pcontentData = new vector<TabNewInfRecord>();
	//ZeroMemory(pcontentData,sizeof vector<TabNewInfRecord>);
	//while(1)
	{
		int nstat = -1;
		switch (nSSset)
		{
		case 10:
			nstat = dlg->svrIO->getNewGoodsInf(*pcontentData, dlg->curInput);
			break;
		case 11:
			nstat = dlg->svrIO->getNewBulkGoodsInf(*pcontentData, dlg->curInput);
			break;
		case 12:
			nstat = dlg->svrIO->getNewCarsInf(*pcontentData, dlg->curInput);
			break;
		case 20:
			string result = dlg->svrIO->sendPhoneMessage(dlg->sphonenum,dlg->sphonetext);
			// 
			LeaveCriticalSection(&csPrintMore);
			
			if (result == "TRUE") {
			    AfxMessageBox("短信发送成功！");
			} else {
			            AfxMessageBox(result.c_str());
		         }
			return 0;
			break;
		}
		if (nstat == 0)
		{
			//break;
		}
		Sleep(100);
	}

	
	if (pcontentData->size() > 0) {
		dlg->maxPageNum = atoi(pcontentData->at(0).totalNum.c_str()) / dlg->curInput.record;
		int n =atoi(pcontentData->at(0).totalNum.c_str()) % dlg->curInput.record;
		if (n == 0)
		{
		} 
		else
		{
			dlg->maxPageNum += 1;
		}
		if (dlg->maxPageNum < 1) {
			dlg->maxPageNum = 1;
		}
	}
	//vector<TabNewInfRecord> *newdata(&dlg->contentData);
	dlg->contentData = *pcontentData;
	// 设置表格   
	try
	{
		::PostMessage(dlg->GetSafeHwnd(),WM_SETGRID,(WPARAM)pcontentData,0);
	}
	catch (...)
	{
	}
	//ClearVector(*pcontentData);
	CoUninitialize();
	LeaveCriticalSection(&csPrintMore);
	return 0;
}
void CTabNewInfDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	static int i=0;
	if (i%2 == 0)
	{
		OnBnClickedTabNewPrev();
	} 
	else
	{
		OnBnClickedTabNewNext();
	}

	i++;
	CDialog::OnTimer(nIDEvent);
}

void CTabNewInfDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	//CBitmap bmp;
	//if (bmp.LoadBitmap(IDB_NEW_INFO_TABLE))
	//{
	//	// Get the size of the bitmap
	//	BITMAP bmpInfo;
	//	bmp.GetBitmap(&bmpInfo);

	//	CDC dcMemory;
	//	dcMemory.CreateCompatibleDC(&dc);

	//	CBitmap* pOldBitmap = dcMemory.SelectObject(&bmp);

	//	CRect rect;
	//	GetClientRect(&rect);
	//	dc.BitBlt(0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, &dcMemory, 0, 0, SRCCOPY);

	//	dcMemory.SelectObject(pOldBitmap);
	//}
}

HBRUSH CTabNewInfDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	if( nCtlColor == CTLCOLOR_STATIC )
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(49,49,49)); 
		return   (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
	}

	return hbr;
}


#include "WLRClientDlg.h"
//void CTabNewInfDlg::OnBnClickedButtonLocal()
//{
//	m_editStartAddr.SetWindowText(_T(""));
//	if( curType == 0 || curType == 3)
//	{
//		((CWLRClientDlg*)AfxGetApp()->GetMainWnd())->PostMessage(WM_TNI_START_SEARCH, 0, 0);
//	}
//	else if( curType == 2 || curType == 5 )
//	{
//		((CWLRClientDlg*)AfxGetApp()->GetMainWnd())->PostMessage(WM_TNI_START_SEARCH, 2, 0);
//	}
//}
//
//void CTabNewInfDlg::OnBnClickedButtonCancelSearch()
//{
//	CString sStartAddr, sDestAddr;
//	m_editDestAddr.GetWindowText(sDestAddr);
//	if( sDestAddr.IsEmpty() )
//	{
//		m_sStartProvince = m_sStartCity = m_sStartCounty = "";
//		m_sDestProvince = m_sDestCity = m_sDestCounty = "";
//		return ;
//	}
//	m_editDestAddr.SetWindowText(_T(""));
//
//	if( m_sStartProvince.empty() || m_sStartProvince == "不限" )
//	{
//		m_editStartAddr.SetWindowText(_T(""));
//		m_sStartProvince = m_sStartCity = m_sStartCounty = "";
//		vector<TabNewInfRecord> vecRecord;
//		setGrid(&vecRecord);
//		return ;
//	}
//	m_editDestAddr.SetWindowText(_T(""));
//	if( curType == 0 || curType == 3)
//	{
//		((CWLRClientDlg*)AfxGetApp()->GetMainWnd())->PostMessage(WM_TNI_CANCEL_SEARCH, 0, 1);
//	}
//	else if( curType == 2 || curType == 5 )
//	{
//		((CWLRClientDlg*)AfxGetApp()->GetMainWnd())->PostMessage(WM_TNI_CANCEL_SEARCH, 2, 1);
//	}
//}
//
//void CTabNewInfDlg::OnBnClickedButtonSecrecy()
//{
//	((CWLRClientDlg*)AfxGetApp()->GetMainWnd())->PostMessage(WM_TNI_SECRECY);
//}
//
//void CTabNewInfDlg::OnBnClickedButtonStopRefresh()
//{
//	((CWLRClientDlg*)AfxGetApp()->GetMainWnd())->PostMessage(WM_TNI_STOP_REFRESH);
//}

LRESULT CTabNewInfDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_EDIT_LBUTTON_DOWN:
		{
			if( curType == 0 || curType == 3)//货源
			{
				((CWLRClientDlg*)AfxGetApp()->GetMainWnd())->PostMessage(WM_TNI_START_SEARCH, eSearchType_Goods, 2);
			}
			else if( curType == 2 || curType == 5 )//车源
			{
				((CWLRClientDlg*)AfxGetApp()->GetMainWnd())->PostMessage(WM_TNI_START_SEARCH, eSearchType_Car, 2);
			}
		}
		break;
	}
	return CDialog::WindowProc(message, wParam, lParam);
}


void CTabNewInfDlg::OnBnClickedButtonSearch()
{
	if( curType == 0 || curType == 3)//货源
	{
		((CWLRClientDlg*)AfxGetApp()->GetMainWnd())->PostMessage(WM_TNI_START_SEARCH, eSearchType_Goods, 2);
	}
	else if( curType == 2 || curType == 5 )//车源
	{
		((CWLRClientDlg*)AfxGetApp()->GetMainWnd())->PostMessage(WM_TNI_START_SEARCH, eSearchType_Car, 2);
	}
}

void CTabNewInfDlg::OnBnClickedButtonStopRefresh()
{
	((CWLRClientDlg*)AfxGetApp()->GetMainWnd())->PostMessage(WM_TNI_STOP_REFRESH);
}

void CTabNewInfDlg::OnBnClickedButtonHidePhoneNum()
{
	((CWLRClientDlg*)AfxGetApp()->GetMainWnd())->PostMessage(WM_TNI_SECRECY);
}
