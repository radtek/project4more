// TabSpecialLineDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WLRClient.h"
#include "TabSpecialLineDlg.h"
#include "CommDef.h"
#include "header.h"
#include "SpecLineDetailDlg.h"

// CTabSpecialLineDlg 对话框

IMPLEMENT_DYNAMIC(CTabSpecialLineDlg, CDialog)
    
int nSet;
// 构造函数
CTabSpecialLineDlg::CTabSpecialLineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTabSpecialLineDlg::IDD, pParent)
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
    contentFont.lfHeight=14; // 字体大小 
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

CTabSpecialLineDlg::~CTabSpecialLineDlg()
{
}

void CTabSpecialLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabSpecialLineDlg)
	DDX_Control(pDX, IDC_TAB_SPECIAL_LINE_LIST, m_Grid); // associate the grid window with a C++ object
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_TAB_SPECIAL_LINE_PREV, btnPrev);
	DDX_Control(pDX, IDC_TAB_SPECIAL_LINE_NEXT, btnNext);
	DDX_Control(pDX, IDC_PIC, m_Picture);
	DDX_Control(pDX, IDC_EDID_LINE_START_ADDR, m_editStartAddr);
	DDX_Control(pDX, IDC_EDID_LINE_DEST_ADDR, m_editDestAddr);
	DDX_Control(pDX, IDC_BUTTON_LINE_LOCAL, m_btnLocal);
	DDX_Control(pDX, IDC_BUTTON_LINE_CANCEL_SEARCH, m_btnCancelSearch);
	DDX_Control(pDX, IDC_BUTTON_LINE_SECRECY, m_btnSecrecy);
	DDX_Control(pDX, IDC_BUTTON_LINE_STOP_REFRESH, m_btnStopRefresh);
}


BEGIN_MESSAGE_MAP(CTabSpecialLineDlg, CDialog)
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
    ON_NOTIFY(NM_RCLICK, IDC_TAB_SPECIAL_LINE_LIST, OnGridRClick)
	ON_NOTIFY(NM_DBLCLK, IDC_TAB_SPECIAL_LINE_LIST, OnGridDBLClick)
    ON_COMMAND(ID_MENU_OPERATION_COLLECT, &CTabSpecialLineDlg::OnMenuOperationCollect)
    ON_COMMAND(ID_MENU_OPERATION_DELETE, &CTabSpecialLineDlg::OnMenuOperationDelete)
    ON_COMMAND(ID_MENU_OPERATION_DELFAV, &CTabSpecialLineDlg::OnMenuOperationDelfav)
    ON_BN_CLICKED(IDC_TAB_SPECIAL_LINE_PREV, &CTabSpecialLineDlg::OnBnClickedTabSpecialLinePrev)
    ON_BN_CLICKED(IDC_TAB_SPECIAL_LINE_NEXT, &CTabSpecialLineDlg::OnBnClickedTabSpecialLineNext)
	ON_MESSAGE(WM_SETGRID,OnFresh)
	ON_BN_CLICKED(IDC_BUTTON_LINE_LOCAL, &CTabSpecialLineDlg::OnBnClickedButtonLineLocal)
	ON_BN_CLICKED(IDC_BUTTON_LINE_CANCEL_SEARCH, &CTabSpecialLineDlg::OnBnClickedButtonLineCancelSearch)
	ON_BN_CLICKED(IDC_BUTTON_LINE_SECRECY, &CTabSpecialLineDlg::OnBnClickedButtonLineSecrecy)
	ON_BN_CLICKED(IDC_BUTTON_LINE_STOP_REFRESH, &CTabSpecialLineDlg::OnBnClickedButtonLineStopRefresh)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// 自动改变控件位置大小
BEGIN_EASYSIZE_MAP(CTabSpecialLineDlg)
    // EASYSIZE(control,left,top,right,bottom,options)
	EASYSIZE(IDC_TAB_SPECIAL_LINE_LIST, ES_BORDER, ES_BORDER, ES_BORDER, ES_BORDER, 0)
    EASYSIZE(IDC_TAB_SPECIAL_LINE_NEXT, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_KEEPSIZE, 0)
    EASYSIZE(IDC_TAB_SPECIAL_LINE_PREV, ES_KEEPSIZE, ES_BORDER, IDC_TAB_SPECIAL_LINE_NEXT, ES_KEEPSIZE, 0)
END_EASYSIZE_MAP

// CTabSpecialLineDlg 消息处理程序

BOOL CTabSpecialLineDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化
	if (m_Picture.Load(MAKEINTRESOURCE(IDR_WAIT),_T("GIF")))
		m_Picture.Draw();
    // 初始化Grid控件
    initGrid();

    // 初始化按钮
    btnPrev.LoadBitmap(IDB_PREVPAGE);
    btnNext.LoadBitmap(IDB_NEXTPAGE);

	//btnPrev.ShowWindow(SW_HIDE);
	//btnNext.ShowWindow(SW_HIDE);

	m_btnLocal.LoadBitmap(IDB_LOCAL);
	m_btnCancelSearch.LoadBitmap(IDB_CANCEL);
	m_btnSecrecy.LoadBitmap(IDB_HIDE_PHONE_NUM);
	m_btnStopRefresh.LoadBitmap(IDB_STOP_REFRESH);


    // 初始化自动调整控件位置
    INIT_EASYSIZE;
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}
    
// OnSize
void CTabSpecialLineDlg::OnSize(UINT nType, int cx, int cy)
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
int CTabSpecialLineDlg::initGrid()
{
    int m_nFixRows = 1; // total rows
	int m_nCols = 8;    // total cols
    
    CRect rect;
    GetDlgItem(IDC_TAB_SPECIAL_LINE_LIST)->GetWindowRect(rect); //得到显示区域
    int spaceWidth = rect.Width()*1/10;
    if (spaceWidth > 120) {  // 出发地和到达地最大宽度
        spaceWidth = 120;
    }
    int colWidth1 = spaceWidth;
    int colWidth2 = spaceWidth;
    int colWidth3 = 60;
    int colWidth4 = 60;
    int colWidth5 = 81;
    int colWidth6 = 69;
    int colWidth7 = rect.Width() - colWidth1 - colWidth2 - colWidth3 - colWidth4 - colWidth5 - colWidth6 -20;//- 20;//-20;
    int colWidth8 = 20;

	TRY {	    
		m_Grid.SetColumnCount(m_nCols);
		m_Grid.SetFixedRowCount(m_nFixRows);
		    //m_Grid.SetFixedColumnCount(m_nFixCols);
        m_Grid.SetEditable(false); // 不可编辑
        
        // 设置列宽
        m_Grid.SetColumnWidth(0, colWidth1); // 设置第1列的列宽
        m_Grid.SetColumnWidth(1, colWidth2); // 设置第2列的列宽
        m_Grid.SetColumnWidth(2, colWidth3); // 设置第3列的列宽
        m_Grid.SetColumnWidth(3, colWidth4); // 设置第4列的列宽
        m_Grid.SetColumnWidth(4, colWidth5); // 设置第5列的列宽
        m_Grid.SetColumnWidth(5, colWidth6); // 设置第6列的列宽
        m_Grid.SetColumnWidth(6, colWidth7); // 设置第7列的列宽
        m_Grid.ExpandLastColumn(); // 调整最后一列的宽度以添满grid区域.

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
        //m_Grid.SetGridLines(GVL_HORZ);

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
int CTabSpecialLineDlg::calRow()
{
    CRect rect;
    GetDlgItem(IDC_TAB_SPECIAL_LINE_LIST)->GetWindowRect(rect); //得到显示区域
    curInput.record = (rect.Height() - 28 )/(abs(contentFont.lfHeight) + 10); 

    return 0;
}
    
// 设置数据
int CTabSpecialLineDlg::setData(int type, int curpage)
{
    if (svrIO == NULL) {
        return -1;
    }
	//EnterCriticalSection(&csPrint);
    curType = type;
    if (-1 != curpage) { // -1: 保留当前curpage
        curInput.curpage = curpage;
    }
    calRow();
	//Sleep(100);//等待
    // 设置标题数据

	vector<TabSpecialLineRecord> * pcontentData = new vector<TabSpecialLineRecord>();
	//ZeroMemory(pcontentData,sizeof vector<TabSpecialLineRecord>);
    TabSpecialLineRecord title;
    title.startPlace = "出发地";
    title.endPlace = "到达地";
    title.weightPrice = "重货价";
    title.lightPrice = "泡货价";
    title.schedules = "发车班次";
    title.needTime = "途中时间";
    //title.record = "联系信息";
	contentData.clear();
    switch (curType) {
        case 0: // 所有专线
			
			m_editStartAddr.SetWindowText(_T(""));
			m_editDestAddr.SetWindowText(_T(""));

            title.record = "联系信息";
			//svrIO->getAllSpecialLineInf(contentData, curInput);
			pcontentData->clear();
			
			if (contentDataALL.size() != 0)
			{
				int len = contentDataALL.size();
				if (len < curInput.record)
				{
					for (int i=0;i<len;i++)
					{
						if (contentDataALL[i].recordID != "")
						{
							pcontentData->push_back(contentDataALL[i]);
							contentData.push_back(contentDataALL[i]);
						}

					}
				}
				else
				{
					for (int i=(curInput.curpage-1)*curInput.record ;i<curInput.curpage*curInput.record ;i++)
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
							nSet = 3;
							//SuspendThread(hThread);
							//Sleep(100);
							Main_Thread=CreateThread(NULL,0,ThreadFuncZX,this,0,&PID);
							CloseHandle(Main_Thread);
							/*contentData.clear();
							svrIO->getAllSpecialLineInf(contentData, curInput);
							break;*/
							return 0;
						}
						if (contentDataALL[i].recordID != "")
						{
							pcontentData->push_back(contentDataALL[i]);
							contentData.push_back(contentDataALL[i]);
						}
					}
				}
			}
            break;
        case 1: // 我的专线
            title.record = "联系信息";
			pcontentData->clear();
			if (contentDataMY.size() != 0)
			{
				int len = contentDataMY.size();
				if (len < curInput.record)
				{
					for (int i=0;i<len;i++)
					{
						if (contentDataMY[i].recordID != "")
						{
							pcontentData->push_back(contentDataMY[i]);
							contentData.push_back(contentDataMY[i]);
						}
						//pcontentData->push_back(contentDataMY[i]);
						//contentData.push_back(contentDataMY[i]);
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
							nSet = 4;
							//SuspendThread(hThread);
							//Sleep(100);
							Main_Thread=CreateThread(NULL,0,ThreadFuncZX,this,0,&PID);
							CloseHandle(Main_Thread);
							return 0;
							/*contentData.clear();
							svrIO->getMySpecialLineInf(contentData, curInput);
							break;*/
						}
						if (contentDataMY[i].recordID != "")
						{
							pcontentData->push_back(contentDataMY[i]);
							contentData.push_back(contentDataMY[i]);
						}
					}
				}
			}
            //svrIO->getMySpecialLineInf(contentData, curInput);
            break;
        case 2: // 我的收藏
            title.record = "联系信息";
			pcontentData->clear();
			if (contentDataSAVE.size() != 0)
			{
				int len = contentDataSAVE.size();
				if (len < curInput.record)
				{
					for (int i=0;i<len;i++)
					{
						if (contentDataSAVE[i].recordID != "")
						{
							pcontentData->push_back(contentDataSAVE[i]);
							contentData.push_back(contentDataSAVE[i]);
						}
						//pcontentData->push_back(contentDataSAVE[i]);
						//contentData.push_back(contentDataSAVE[i]);
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
						if (curInput.curpage*curInput.record > RECORD_NUM || (curInput.curpage-1)*curInput.record > RECORD_NUM)
						{
							pcontentData->clear();
							DWORD PID;
							HANDLE Main_Thread;
							nSet = 5;
							//SuspendThread(hThread);
							//Sleep(100);
							Main_Thread=CreateThread(NULL,0,ThreadFuncZX,this,0,&PID);
							CloseHandle(Main_Thread);
							return 0;
							/*contentData.clear();
							svrIO->getFavoriteSpecialLineInf(contentData, curInput);
							break;*/
						}
						if (contentDataSAVE[i].recordID != "")
						{
							pcontentData->push_back(contentDataSAVE[i]);
							contentData.push_back(contentDataSAVE[i]);
						}
					}
				}
			}
            //svrIO->getFavoriteSpecialLineInf(contentData, curInput);
            break;
        case 3: // 搜索专线
            title.record = "联系信息";
			//contentData.clear();
			DWORD PID;
			HANDLE Main_Thread;
			nSet = 0;
			//SuspendThread(hThread);
			Main_Thread=CreateThread(NULL,0,ThreadFuncZX,this,0,&PID);
			CloseHandle(Main_Thread);
			GetDlgItem(IDC_PIC)->ShowWindow(TRUE);
			GetDlgItem(IDC_SHOW)->ShowWindow(TRUE);
            //svrIO->getSearchSpecialLineInf(specialKeyword, contentData, curInput);
            break;
        case 4: // 点击搜索专线
            title.record = "联系信息";
			//contentData.clear();
			//SuspendThread(hThread);
			nSet = 1;
            //svrIO->getClickSearchSpecialLineInf(clickKeyWord, contentData, curInput);
			Main_Thread=CreateThread(NULL,0,ThreadFuncZX,this,0,&PID);
			CloseHandle(Main_Thread);
			GetDlgItem(IDC_PIC)->ShowWindow(TRUE);
			GetDlgItem(IDC_SHOW)->ShowWindow(TRUE);
            break; 
        default:
            break;
    }
    
    titleData = title;

    // 设置最大页数
    if (pcontentData->size() > 0) {
        maxPageNum = atoi(pcontentData->at(0).totalNum.c_str()) / curInput.record +1;
        if (maxPageNum < 1) {
            maxPageNum = 1;
        }
    }
	//vector<TabSpecialLineRecord> *newdata(&contentData);
    // 设置表格    
	try
	{
		setGrid(pcontentData);
	}
	catch (...)
	{

	}
	ClearVector(*pcontentData);
	//LeaveCriticalSection(&csPrint);
    return 0;
}
     
// set this grid title
int CTabSpecialLineDlg::setThisGridTitle(int m_nCols)
{
    // 设置标题字体
    for (int i=0; i<m_nCols; ++i) {
        m_Grid.SetItemFont(0, i, &titleFont);
    }
    // 定义标题背景色
    COLORREF titleBKClr = RGB(0, 128, 0);
    // 定义标题文字色
    COLORREF titleFgClr = RGB(255,255,255);

    // 出发地
    GV_ITEM item[MAX_COL_NUM];
    for (int i=0; i<m_nCols; ++i) {
        item[i].mask = GVIF_TEXT|GVIF_FORMAT|GVIF_BKCLR|GVIF_FGCLR;
        item[i].row = 0;
        item[i].col = i;
        item[i].crBkClr = titleBKClr;
        item[i].crFgClr = titleFgClr;    				    
        item[i].nFormat = DT_CENTER;
        
        switch (i) {
            case 0: // 出发地
                item[i].strText = titleData.startPlace.c_str();
                break;
            case 1: // 到达地
                item[i].strText = titleData.endPlace.c_str();
                break;
            case 2: // 重货价
                item[i].strText = titleData.weightPrice.c_str();
                break;
            case 3: // 泡货价
                item[i].strText = titleData.lightPrice.c_str();
                break;
            case 4: // 发车班次
                item[i].strText = titleData.schedules.c_str();
                break;
            case 5: // 途中时间
                item[i].strText = titleData.needTime.c_str();
                break;
            case 6: // 信息内容
                item[i].strText = titleData.record.c_str();
                break;
            case 7: // 保留列
                break;
            default:
                break;
        }

        m_Grid.SetItem(&item[i]);
    } 
 
    // 设置标题行高
    m_Grid.SetRowHeight(0, 28);
    return 0;
}
    
// set this grid content
int CTabSpecialLineDlg::setThisGridContent(int m_nCols,vector<TabSpecialLineRecord> * pcontentData)
{
	
    // 定义行背景色
    COLORREF rowBKClr = svrIO->myColor.oddRowBKClr;
    // 定义行文字色
    COLORREF rowFgClr = svrIO->myColor.oddRowFgClr;
    // 开关变量
    bool ifOddRow = true; 
	//vector<TabSpecialLineRecord> contentData(pLocalContentData);
    int row = 1;
    GV_ITEM item[MAX_COL_NUM];
    int itemHeight[MAX_COL_NUM]; // 单元格高度
    int rowHeight = MIN_ROW_HEIGHT; // 行高
    vector<TabSpecialLineRecord>::iterator iter = pcontentData->begin();
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
        // 分别设置每列
        for (int i=0; i<m_nCols; ++i) {        
            switch (i) {
                case 0: // 出发地
                    item[i].strText = (*iter).startPlace.c_str();
                    break;
                case 1: // 到达地
                    item[i].strText = (*iter).endPlace.c_str();
                    break;
                case 2: // 重货价
                    item[i].strText = (*iter).weightPrice.c_str();
                    break;
                case 3: // 泡货价
                    item[i].strText = (*iter).lightPrice.c_str();
                    break;
                case 4: // 发车班次
                    item[i].strText = (*iter).schedules.c_str();
                    break;
                case 5: // 途中时间
                    item[i].strText = (*iter).needTime.c_str();
                    break;
                case 6: // 信息内容
                    //item[i].strText = (*iter).record.c_str();
                    if (ifShowPhone) { 
                        //item[i].strText = (*iter).record.c_str();
                        item[i].strText += (*iter).tel.c_str();
                    } else {
                        item[i].strText = (*iter).pubName.c_str();            
                    }                    
                    break;
                case 7: // 保留列
                    break;
                default:
                    break;
            }
            m_Grid.SetItemFont(row, i, &contentFont);
            item[i].row = row;
            item[i].col = i;
            item[i].mask = GVIF_TEXT|GVIF_FORMAT|GVIF_BKCLR|GVIF_FGCLR;
            item[i].nFormat = DT_LEFT|DT_EXTERNALLEADING|DT_WORDBREAK;
            item[i].crBkClr = rowBKClr;
            item[i].crFgClr = rowFgClr;  
            // 设置此单元格信息
            m_Grid.SetItem(&item[i]);  
            // 计算需要的行高
            CSize size = m_Grid.GetTextExtent(row, i, item[i].strText);
            int n = size.cx / (m_Grid.GetColumnWidth(i) - 12);
            if (0 != size.cx%(m_Grid.GetColumnWidth(i) - 12)) {
                ++n; 
            } 
            itemHeight[i] = n*(size.cy -12) + 12;
            // 在所有单元格高度里面取最大值作为整行的高
            rowHeight = (rowHeight > itemHeight[i])?rowHeight:itemHeight[i];            
        } 

        // 设置行高 
        m_Grid.SetRowHeight(row, rowHeight);	

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
	ClearVector(*pcontentData);
	//delete pcontentData;
    return 0;
}    
    
// 设置Grid控件
int CTabSpecialLineDlg::setGrid(vector<TabSpecialLineRecord> * pcontentData)
{
	EnterCriticalSection(&csPrintFresh);
    // 设置网格线颜色
    m_Grid.SetGridColor(svrIO->myColor.gridClr);
	//vector<TabSpecialLineRecord> contentData(pcontentData);
    int m_nRows = pcontentData->size()+1;
    m_Grid.SetRowCount(m_nRows);
    
    // 设置标题 
    setThisGridTitle(m_Grid.GetColumnCount());

    // 设置内容
    setThisGridContent(m_Grid.GetColumnCount(),pcontentData);

    // 刷新
    m_Grid.Refresh();
	TRACE("busy\n");
	LeaveCriticalSection(&csPrintFresh);
    return 0;
}
       
// NM_RCLICK
void CTabSpecialLineDlg::OnGridRClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    curSelRow = pItem->iRow;
    if (curSelRow <= 0) {
        return;
    }
    // 设置弹出菜单
    CPoint   point; 
    ::GetCursorPos(&point);     			
    CMenu menu;//菜单
	menu.CreatePopupMenu();

	int nMenuId = 1000;
    if (curType == 0 || curType == 3 || curType == 4) 
	{
		int index = curSelRow-1;
		menu.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "打开本信息");
		menu.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "收藏专线");
		int nRetId = menu.TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON|TPM_RETURNCMD,point.x,point.y,this,NULL);
		if( nRetId == 1000 )
		{
			ShowDetail(contentData.at(index));
		}
		else if( nRetId == 1001 )
		{
			AddFavorite(contentData.at(index));
		}
		
    }

    if (curType == 1) {
		int index = curSelRow-1;
		menu.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "打开本信息");
		menu.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "删除");
		int nRetId = menu.TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON|TPM_RETURNCMD,point.x,point.y,this,NULL);
		if( nRetId == 1000 )
		{
			ShowDetail(contentData.at(index));
		}
		else if( nRetId == 1001 )
		{
			DeleteSpecLine(contentData.at(index));
		}

    }

    if (curType == 2) {
        int index = curSelRow-1;
		menu.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "打开本信息");
		menu.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "取消收藏");
		int nRetId = menu.TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON|TPM_RETURNCMD,point.x,point.y,this,NULL);
		if( nRetId == 1000 )
		{
			ShowDetail(contentData.at(index));
		}
		else if( nRetId == 1001 )
		{
			RemoveFavorite(contentData.at(index));
		}
    }

    //弹出菜单函数，第一个参数表示快捷菜单的下边界与由参数y指定的坐标对齐 
	//第二和第三个为x、y坐标，第四个表示拥有此菜单的窗口句柄，
	//第五个默认为NULL,表示当用户在菜单以外的区域按鼠标键时，菜单会消失
	//pPopupMenu->TrackPopupMenu(TPM_TOPALIGN,point.x,point.y,this,NULL);
}
void CTabSpecialLineDlg::OnGridDBLClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	//CString str;
	//str.Format(_T("选中行为： %d"), pItem->iRow);
	//AfxMessageBox(str);
	// 获取当前选择的行
	curSelRow = pItem->iRow;
	if (curSelRow <= 0) {
		return;
	}

	int index = curSelRow-1;
	CSpecLineDetailDlg dlg(&contentData.at(index), this);
	dlg.DoModal();
}


    
// set grid content font
int CTabSpecialLineDlg::setCridContentFont(SettingFont& font)
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
    
// 收藏专线菜单
void CTabSpecialLineDlg::OnMenuOperationCollect()
{
    // TODO: 在此添加命令处理程序代码
    int index = curSelRow-1;
	if (index < 0)
	{
		index = 0;
	}
	//SuspendThread(hThread);
    string result = svrIO->collectSpecialLine(contentData.at(index).recordID);
	//ResumeThread(hThread);
    if (result == "TRUE") {
        MessageBox("收藏专线成功！","收藏专线");
    } else {
        MessageBox(result.c_str(),"收藏专线失败");
    }
}
    
// 删除菜单
void CTabSpecialLineDlg::OnMenuOperationDelete()
{
    // TODO: 在此添加命令处理程序代码
    int index = curSelRow-1;
	if (index < 0)
	{
		index = 0;
	}

	DeleteSpecLine(contentData.at(index));
}
    
// 取消专线
void CTabSpecialLineDlg::OnMenuOperationDelfav()
{
    // TODO: 在此添加命令处理程序代码
    int index = curSelRow-1;
	if (index < 0)
	{
		index = 0;
	}
	//SuspendThread(hThread);
    string result = svrIO->delFavoriteSpecialLine(contentData.at(index).recordID);
	//ResumeThread(hThread);
    if (result == "TRUE") {
        MessageBox("取消收藏成功！","取消专线收藏");
    } else {
        MessageBox(result.c_str(),"取消收藏失败");
    }

    // 更新显示数据
    setData(curType);
}
    
// 前一页
void CTabSpecialLineDlg::OnBnClickedTabSpecialLinePrev()
{
    // TODO: 在此添加控件通知处理程序代码
    if(curInput.curpage <= 1) {
        return;
    }

    curInput.curpage -= 1;
    setData(curType, curInput.curpage);
}
    
// 后一页
void CTabSpecialLineDlg::OnBnClickedTabSpecialLineNext()
{
    // TODO: 在此添加控件通知处理程序代码
    if(curInput.curpage == maxPageNum) {
        return;
    }

    curInput.curpage += 1;
    setData(curType, curInput.curpage);
}
//搜索处理线程
DWORD CTabSpecialLineDlg::ThreadFuncZX(LPVOID p)
{
	CoInitialize(NULL);
	CTabSpecialLineDlg * dlg = (CTabSpecialLineDlg*)p;
	if (csPrintSpecial.LockCount == 0) return -1;
	EnterCriticalSection(&csPrintSpecial);


	vector<TabSpecialLineRecord> * pcontentData = new vector<TabSpecialLineRecord>();
	//ZeroMemory(pcontentData,sizeof vector<TabSpecialLineRecord>);
	/*switch (nSet)
	{
	case 0:
		//svrIO->getSearchSpecialLineInf(specialKeyword, contentData, curInput);
		dlg->svrIO->getSearchSpecialLineInf(dlg->specialKeyword, dlg->contentData, dlg->curInput);
		break;
	case 1:
		//svrIO->getClickSearchSpecialLineInf(clickKeyWord, contentData, curInput);
		dlg->svrIO->getClickSearchSpecialLineInf(dlg->clickKeyWord, dlg->contentData, dlg->curInput);
		break;
	}*/
	//while(1)
	{
		int nstat = -1;
		switch (nSet)
		{
		case 0:
			nstat = dlg->svrIONew->getSearchSpecialLineInf(dlg->specialKeyword, * pcontentData, dlg->curInput);
			break;
		case 1:
			nstat = dlg->svrIONew->getClickSearchSpecialLineInf(dlg->clickKeyWord, * pcontentData, dlg->curInput);
			break;
		case 3:
			nstat = dlg->svrIONew->getAllSpecialLineInf(* pcontentData, dlg->curInput);
			break;
		case 4:
			nstat = dlg->svrIONew->getMySpecialLineInf(* pcontentData, dlg->curInput);
			break;
		case 5:
			nstat = dlg->svrIONew->getFavoriteSpecialLineInf(* pcontentData, dlg->curInput);
			
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
	//vector<TabSpecialLineRecord> *newdata(&dlg->contentData);
	// 设置表格   
	try
	{
		//dlg->setGrid();
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
	//delete pcontentData;
	LeaveCriticalSection(&csPrintSpecial);
	CoUninitialize();
	return 0;
}

//处理消息刷新
LONG CTabSpecialLineDlg::OnFresh(WPARAM w, LPARAM l)
{
	//vector<TabSpecialLineRecord> * data = (vector<TabSpecialLineRecord> *)w;
	try
	{
		setGrid((vector<TabSpecialLineRecord> *)w);
	}
	catch (...)
	{

	}
	GetDlgItem(IDC_PIC)->ShowWindow(FALSE);
	GetDlgItem(IDC_SHOW)->ShowWindow(FALSE);
	return 0;
}


HBRUSH CTabSpecialLineDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
void CTabSpecialLineDlg::OnBnClickedButtonLineLocal()
{
	m_editStartAddr.SetWindowText(_T(""));
	m_editDestAddr.SetWindowText(_T(""));

	((CWLRClientDlg*)AfxGetApp()->GetMainWnd())->PostMessage(WM_TNI_START_SEARCH, eSearchType_SpecialLine, 0);
}

void CTabSpecialLineDlg::OnBnClickedButtonLineCancelSearch()
{
	((CWLRClientDlg*)AfxGetApp()->GetMainWnd())->PostMessage(WM_TNI_CANCEL_SEARCH,eSearchType_SpecialLine, 1);
}

void CTabSpecialLineDlg::OnBnClickedButtonLineSecrecy()
{
	((CWLRClientDlg*)AfxGetApp()->GetMainWnd())->PostMessage(WM_TNI_SECRECY);
}

void CTabSpecialLineDlg::OnBnClickedButtonLineStopRefresh()
{
	((CWLRClientDlg*)AfxGetApp()->GetMainWnd())->PostMessage(WM_TNI_STOP_REFRESH);
}


LRESULT CTabSpecialLineDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_EDIT_LBUTTON_DOWN:
		{
			((CWLRClientDlg*)AfxGetApp()->GetMainWnd())->PostMessage(WM_TNI_START_SEARCH, eSearchType_SpecialLine, 2);
		}
		break;
	}
	return CDialog::WindowProc(message, wParam, lParam);
}

void CTabSpecialLineDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CBitmap bmp;
	if (bmp.LoadBitmap(IDB_NEW_INFO_TABLE))
	{
		// Get the size of the bitmap
		BITMAP bmpInfo;
		bmp.GetBitmap(&bmpInfo);

		CDC dcMemory;
		dcMemory.CreateCompatibleDC(&dc);

		CBitmap* pOldBitmap = dcMemory.SelectObject(&bmp);

		CRect rect;
		GetClientRect(&rect);
		dc.BitBlt(0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, &dcMemory, 0, 0, SRCCOPY);

		dcMemory.SelectObject(pOldBitmap);
	}
}


void CTabSpecialLineDlg::DeleteSpecLine(const TabSpecialLineRecord& content)
{
	string result;
	try
	{
		result = svrIO->delSpecialLineInf(content.recordID);
	}
	catch (...)
	{	


	}
	//ResumeThread(hThread);
	if (result == "TRUE") {
		MessageBox("删除专线成功！","删除专线");
	} else {
		MessageBox(result.c_str(),"删除专线失败");
	}

	// 更新显示数据
	setData(curType);
}
void CTabSpecialLineDlg::AddFavorite(const TabSpecialLineRecord& content)
{
	string result = svrIO->collectSpecialLine(content.recordID);
	//ResumeThread(hThread);
	if (result == "TRUE") {
		MessageBox("收藏专线成功！","收藏专线");
	} else {
		MessageBox(result.c_str(),"收藏专线失败");
	}
}
void CTabSpecialLineDlg::RemoveFavorite(const TabSpecialLineRecord& content)
{
	//SuspendThread(hThread);
	string result = svrIO->delFavoriteSpecialLine(content.recordID);
	//ResumeThread(hThread);
	if (result == "TRUE") {
		MessageBox("取消收藏成功！","取消专线收藏");
	} else {
		MessageBox(result.c_str(),"取消收藏失败");
	}

	// 更新显示数据
	setData(curType);
}
void CTabSpecialLineDlg::ShowDetail(const TabSpecialLineRecord& content)
{
	CSpecLineDetailDlg dlg(&content, this);
	dlg.DoModal();
}