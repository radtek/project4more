// TabMyInfDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WLRClient.h"
#include "TabMyInfDlg.h"
#include "header.h"
#include "NewInfoDetailDlg.h"
#include "SendPhoneMsgDlg.h"

// CTabMyInfDlg 对话框
int nmyhy=0;
int nmycy=0;
int nmyld=0;
int nMySet;
IMPLEMENT_DYNAMIC(CTabMyInfDlg, CDialog)

CTabMyInfDlg::CTabMyInfDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTabMyInfDlg::IDD, pParent)
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

CTabMyInfDlg::~CTabMyInfDlg()
{
}

void CTabMyInfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabNewInfDlg)
	DDX_Control(pDX, IDC_TAB_MY_INF_LIST, m_Grid); // associate the grid window with a C++ object
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_TAB_MY_PREV, btnPrev);
	DDX_Control(pDX, IDC_TAB_MY_NEXT, btnNext);
	DDX_Control(pDX, IDC_TAB_MY_TOP, m_btnFirstPage);
	DDX_Control(pDX, IDC_TAB_MY_BOTTOM, m_btnLastPage);
}


BEGIN_MESSAGE_MAP(CTabMyInfDlg, CDialog)
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
    ON_NOTIFY(NM_RCLICK, IDC_TAB_MY_INF_LIST, OnGridRClick)
	ON_NOTIFY(NM_DBLCLK, IDC_TAB_MY_INF_LIST, OnGridDBLClick)
    ON_COMMAND(ID_MENU_OPERATION_DELETE, &CTabMyInfDlg::OnMenuOperationDelete)
    ON_BN_CLICKED(IDC_TAB_MY_PREV, &CTabMyInfDlg::OnBnClickedTabMyPrev)
    ON_BN_CLICKED(IDC_TAB_MY_NEXT, &CTabMyInfDlg::OnBnClickedTabMyNext)
	ON_MESSAGE(WM_SETGRID,OnFresh)
	ON_BN_CLICKED(IDC_TAB_MY_TOP, &CTabMyInfDlg::OnBnClickedTabMyTop)
	ON_BN_CLICKED(IDC_TAB_MY_BOTTOM, &CTabMyInfDlg::OnBnClickedTabMyBottom)
END_MESSAGE_MAP()

// 自动改变控件位置大小
BEGIN_EASYSIZE_MAP(CTabMyInfDlg)
    // EASYSIZE(control,left,top,right,bottom,options)
	EASYSIZE(IDC_TAB_MY_INF_LIST, ES_BORDER, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	EASYSIZE(IDC_TAB_MY_BOTTOM, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_KEEPSIZE, 0)
    EASYSIZE(IDC_TAB_MY_NEXT, ES_KEEPSIZE, ES_BORDER, IDC_TAB_MY_BOTTOM, ES_KEEPSIZE, 0)
    EASYSIZE(IDC_TAB_MY_PREV, ES_KEEPSIZE, ES_BORDER, IDC_TAB_MY_NEXT, ES_KEEPSIZE, 0)
	EASYSIZE(IDC_TAB_MY_TOP, ES_KEEPSIZE, ES_BORDER, IDC_TAB_MY_PREV, ES_KEEPSIZE, 0)
END_EASYSIZE_MAP

// CTabMyInfDlg 消息处理程序

BOOL CTabMyInfDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化

    // 初始化Grid控件
    initGrid();

    // 初始化按钮
    btnPrev.LoadBitmap(IDB_PREVPAGE);
    btnNext.LoadBitmap(IDB_NEXTPAGE);
	m_btnFirstPage.LoadBitmap(IDB_FIRST_PAGE);
	m_btnLastPage.LoadBitmap(IDB_LAST_PAGE);

    // 初始化自动调整控件位置
    INIT_EASYSIZE;
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void CTabMyInfDlg::OnSize(UINT nType, int cx, int cy)
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
int CTabMyInfDlg::initGrid() {
	int m_nFixRows = 0; 
	int m_nCols = 4;

    CRect rect;
    GetDlgItem(IDC_TAB_MY_INF_LIST)->GetWindowRect(rect); //得到显示区域
    int spaceWidth = 0;
    int colWidth1 = spaceWidth;
    int colWidth2 = spaceWidth;
    int colWidth3 = rect.Width() - colWidth1 - colWidth2 - 20;
    int colWidth4 = 20;

	TRY {
	    //m_Grid.SetRowCount(m_nRows);
		m_Grid.SetColumnCount(m_nCols);
		m_Grid.SetFixedRowCount(m_nFixRows);
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
int CTabMyInfDlg::calRow()
{
    CRect rect;
    GetDlgItem(IDC_TAB_MY_INF_LIST)->GetWindowRect(rect); //得到显示区域
    //curInput.record = (rect.Height() - 28 )/(contentFont.lfHeight + 10);
    if (rect.Width() > 800) {
        curInput.record = rect.Height()/(abs(contentFont.lfHeight) + 10);
    } else {
        curInput.record = (rect.Height()/abs(contentFont.lfHeight))/2;
    }

    return 0;
}
    
// 设置数据
int CTabMyInfDlg::setData(int type, int curpage)
{
	//EnterCriticalSection(&csPrintFresh);
    if (svrIO == NULL) {
        return -1;
    }
	//EnterCriticalSection(&csPrint);
    curType = type;
    if (-1 != curpage) { // -1: 保留当前curpage
        curInput.curpage = curpage;
    }
    calRow();
	//Sleep(100);
    // 设置标题数据

	vector<TabMyInfRecord> * pcontentData = new vector<TabMyInfRecord>();
	//ZeroMemory(pcontentData,sizeof vector<TabMyInfRecord>);


    TabMyInfRecord title;
    title.startPlace = "出发地";
    title.endPlace = "到达地";
	contentData.clear();
    switch (curType) {
        case 0: // 货源
            title.record = "我的货源信息";
// 			EnterCriticalSection(&csPrint);
//             svrIO->getMyGoodsInf(contentData, curInput);
// 			LeaveCriticalSection(&csPrint);
			/**/pcontentData->clear();
			contentData.clear();
			if (contentDataMYHY.size() != 0)
			{
				int len = contentDataMYHY.size();
				//EnterCriticalSection(&csPrint);
				if (len < curInput.record)
				{
					for (int i=0;i<len;i++)
					{
						if (contentDataMYHY[i].recordID != "")
						{
							pcontentData->push_back(contentDataMYHY[i]);
							contentData.push_back(contentDataMYHY[i]);
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
							DWORD PID;
							HANDLE Main_Thread;
							nMySet = 0;
							//SuspendThread(hThread);
							//Sleep(100);
							Main_Thread=CreateThread(NULL,0,ThreadFuncMy,this,0,&PID);
							CloseHandle(Main_Thread);
							//LeaveCriticalSection(&csPrintFresh);
							return 0;
						}
						if (contentDataMYHY[i].recordID != "")
						{
							pcontentData->push_back(contentDataMYHY[i]);
							contentData.push_back(contentDataMYHY[i]);
						}

					}
				}
			}
            break;
        case 1: // 零担
            title.record = "我的零担信息";
// 			EnterCriticalSection(&csPrint);
//             svrIO->getMyBulkGoodsInf(contentData, curInput);
// 			LeaveCriticalSection(&csPrint);
			/**/pcontentData->clear();
			if (contentDataMYLD.size() != 0)
			{
				int len = contentDataMYLD.size();
				//EnterCriticalSection(&csPrint);
				if (len < curInput.record)
				{
					for (int i=0;i<len;i++)
					{
						if (contentDataMYLD[i].recordID != "")
						{
							pcontentData->push_back(contentDataMYLD[i]);
							contentData.push_back(contentDataMYLD[i]);
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
							DWORD PID;
							HANDLE Main_Thread;
							nMySet = 1;
							//SuspendThread(hThread);
							////Sleep(100);
							Main_Thread=CreateThread(NULL,0,ThreadFuncMy,this,0,&PID);
							CloseHandle(Main_Thread);
							//LeaveCriticalSection(&csPrintFresh);
							return 0;
						}
						if (contentDataMYLD[i].recordID != "")
						{
							pcontentData->push_back(contentDataMYLD[i]);
							contentData.push_back(contentDataMYLD[i]);
						}
					}
				}
			}
            break;
        case 2: // 车源
            title.record = "我的车源信息";
// 			EnterCriticalSection(&csPrint);
//             svrIO->getMyCarsInf(contentData, curInput);
// 			LeaveCriticalSection(&csPrint);
			pcontentData->clear();
			if (contentDataMYCY.size() != 0)
			{
				int len = contentDataMYCY.size();
				if (len < curInput.record)
				{
					for (int i=0;i<len;i++)
					{
						if (contentDataMYCY[i].recordID != "")
						{
							pcontentData->push_back(contentDataMYCY[i]);
							contentData.push_back(contentDataMYCY[i]);
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
							DWORD PID;
							HANDLE Main_Thread;
							nMySet = 2;
							//SuspendThread(hThread);
							//Sleep(100);
							Main_Thread=CreateThread(NULL,0,ThreadFuncMy,this,0,&PID);
							CloseHandle(Main_Thread);
							//LeaveCriticalSection(&csPrintFresh);
							return 0;
						}
						if (contentDataMYCY[i].recordID != "")
						{
							pcontentData->push_back(contentDataMYCY[i]);
							contentData.push_back(contentDataMYCY[i]);
						}
					}
				}
			}
            break;
        default:
            break;
    }
    
    titleData = title;

    // 设置最大页数
    if (contentData.size() > 0) {
        maxPageNum = atoi(contentData.at(0).totalNum.c_str()) / curInput.record+1;
        if (maxPageNum < 1) {
            maxPageNum = 1;
        }
    }
	//vector<TabMyInfRecord> *newdata(&contentData);
    // 设置表格    
	try
	{
		setGrid(pcontentData);
	}
	catch (...)
	{

	}
	ClearVector(*pcontentData);
	//LeaveCriticalSection(&csPrintFresh);
    return 0;
}
    
// 设置Grid控件
int CTabMyInfDlg::setGrid(vector<TabMyInfRecord> * pcontentData)
{
	EnterCriticalSection(&csPrintFresh);

	//vector<TabMyInfRecord> contentData(pLocalContentData);
    int m_nRows = pcontentData->size();
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
    vector<TabMyInfRecord>::iterator iter = pcontentData->begin();
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
            tmpStr = "编号:" + (*iter).recordID + "【" + (*iter).startPlace + "→" + (*iter).endPlace +"】" 
                          + (*iter).record + (*iter).tel;
        } else {
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
		//if (iter != contentData.end())
		{
			++iter;
		}
        
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
	ClearVector(*pcontentData);
	LeaveCriticalSection(&csPrintFresh);
    return 0;
}
    
// NM_RCLICK
void CTabMyInfDlg::OnGridRClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    curSelRow = pItem->iRow;
    if (curSelRow < 0) {
        return;
    }

	const TabMyInfRecord& content = contentData.at(curSelRow);

	// 设置弹出菜单
	CPoint   point; 
	::GetCursorPos(&point);     			
	int nMenuId = 1000;
	CMenu menu;
	menu.CreatePopupMenu();
	menu.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "打开本信息");
	menu.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "修改并发布");
	menu.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "发送短信");
	menu.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "删除");
	menu.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "已成交");

	int nRetId = menu.TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON|TPM_RETURNCMD,point.x,point.y,this,NULL);
	if( nRetId == 1000 )
	{
		ShowDetailInfo(&content);
	}
	else if( nRetId == 1001 )
	{
		
	}
	else if( nRetId == 1002 )
	{
		SendSMS(content);
	}
	else if( nRetId == 1003 )
	{
		Delete();
	}
	else if( nRetId == 1004 )
	{

	}
}
void CTabMyInfDlg::OnGridDBLClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
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
	ShowDetailInfo(&contentData.at(curSelRow));
}

    
// 弹出菜单：删除
void CTabMyInfDlg::OnMenuOperationDelete()
{
   Delete();
}
    
// set grid content font
int CTabMyInfDlg::setCridContentFont(SettingFont& font)
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
void CTabMyInfDlg::OnBnClickedTabMyPrev()
{
    // TODO: 在此添加控件通知处理程序代码
    if(curInput.curpage <= 1) {
        return;
    }

    curInput.curpage -= 1;
	//EnterCriticalSection(&csPrintFresh);
    setData(curType, curInput.curpage);
	//LeaveCriticalSection(&csPrintFresh);
}
    
// 后一页
void CTabMyInfDlg::OnBnClickedTabMyNext()
{
    // TODO: 在此添加控件通知处理程序代码
    if(curInput.curpage == maxPageNum) {
        return;
    }

    curInput.curpage += 1;
	//EnterCriticalSection(&csPrintFresh);
    setData(curType, curInput.curpage);
	//LeaveCriticalSection(&csPrintFresh);
}


void CTabMyInfDlg::OnBnClickedTabMyTop()
{
	if(curInput.curpage <= 1) {
		return;
	}

	curInput.curpage = 1;
	//EnterCriticalSection(&csPrintFresh);
	setData(curType, curInput.curpage);
	//LeaveCriticalSection(&csPrintFresh);
}

void CTabMyInfDlg::OnBnClickedTabMyBottom()
{
	if(curInput.curpage == maxPageNum) {
		return;
	}

	curInput.curpage = maxPageNum;
	//EnterCriticalSection(&csPrintFresh);
	setData(curType, curInput.curpage);
	//LeaveCriticalSection(&csPrintFresh);
}

//搜索处理线程
DWORD CTabMyInfDlg::ThreadFuncMy(LPVOID p)
{
	CoInitialize(NULL);
	CTabMyInfDlg * dlg = (CTabMyInfDlg*)p;
	if (csPrintMy.LockCount == 0) return -1;
	EnterCriticalSection(&csPrintMy);

	vector<TabMyInfRecord> * pcontentData = new vector<TabMyInfRecord>();
	//ZeroMemory(pcontentData,sizeof vector<TabMyInfRecord>);
	//while(1)
	{
		int nstat = -1;
		switch (nMySet)
		{
		case 0:
			nstat = dlg->svrIO->getMyGoodsInf(* pcontentData, dlg->curInput);
			break;
		case 1:
			nstat = dlg->svrIO->getMyBulkGoodsInf(* pcontentData, dlg->curInput);
			break;
		case 2:
			nstat = dlg->svrIO->getMyCarsInf(* pcontentData, dlg->curInput);
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
	//vector<TabMyInfRecord> *newdata(&dlg->contentData);
	// 设置表格   
	try
	{
		//dlg->setGrid();
		::PostMessage(dlg->GetSafeHwnd(),WM_SETGRID,(WPARAM)pcontentData,0);
	}
	catch (...)
	{

	}
	DWORD dip = 0;
	/*if (hThread != NULL)
	{
		while(1)
		{
			dip = ResumeThread(hThread);
			TRACE("close \n");
			if (dip == 0)
			{
				break;
			}
			Sleep(100);
		}
	}*/
	//delete pcontentData;
	LeaveCriticalSection(&csPrintMy);
	CoUninitialize();
	return 0;
}

//处理消息刷新
LONG CTabMyInfDlg::OnFresh(WPARAM w, LPARAM l)
{
	//vector<TabMyInfRecord> *newdata = (vector<TabMyInfRecord> *) w;
	try
	{
		setGrid((vector<TabMyInfRecord> *) w);
	}
	catch (...)
	{

	}
	return 0;
}

void CTabMyInfDlg::ShowDetailInfo(const TabMyInfRecord* pContent)
{
	CNewInfoDetailDlg dlg(pContent, (curType==0)?CNewInfoDetailDlg::eInfoType_MyGoods:CNewInfoDetailDlg::eInfoType_MyCars, this);
	dlg.DoModal();
}
void CTabMyInfDlg::SendSMS(const TabMyInfRecord& content)
{
	string tmp = content.startPlace + "->" + content.endPlace+ "。" + content.record+ content.tel;
	CSendPhoneMsgDlg dlg;
	dlg.phoneMsg = tmp.c_str();
	if (dlg.DoModal() == IDOK) 
	{
		sphonenum = (LPTSTR)(LPCTSTR)dlg.phoneNumber;
		sphonetext = (LPTSTR)(LPCTSTR)dlg.phoneMsg;
		DWORD PID;
		HANDLE Main_Thread;
		nMySet = 20;
		//SuspendThread(hThread);
		//Sleep(100);
		Main_Thread=CreateThread(NULL,0,ThreadFuncMy,this,0,&PID);
	}
}
void CTabMyInfDlg::Delete()
{
	// TODO: 在此添加命令处理程序代码
	int index = curSelRow;
	//SuspendThread(hThread);

	switch (curType) {
		case 0: { // 货源

			string result = svrIO->delGoodsInf(contentData.at(index).recordID);
			if (result == "TRUE") {
				MessageBox("删除货源成功！","删除货源");
			} else {
				MessageBox(result.c_str(),"删除货源失败");
			}
			break;
				}
		case 1: {// 零担
			string result = svrIO->delBulkGoodsInf(contentData.at(index).recordID);
			if (result == "TRUE") {
				MessageBox("删除零担成功！","删除零担");
			} else {
				MessageBox(result.c_str(),"删除零担失败");
			}
			break;
				}
		case 2: {// 车源
			string result = svrIO->delCarsInf(contentData.at(index).recordID);
			if (result == "TRUE") {
				MessageBox("删除车源成功！","删除车源");
			} else {
				MessageBox(result.c_str(),"删除车源失败");
			}
			break;
				}
		default:
			break;
	}

	// 更新数据
	setData(curType);
}