// TabCustomInfDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WLRClient.h"
#include "WLRClientdlg.h"
#include "TabCustomInfDlg.h"
#include "SendPhoneMsgDlg.h"
#include "AddCustomZoneDlg.h"
#include "header.h"
#include "NewInfoDetailDlg.h"
// CTabCustomInfDlg 对话框

IMPLEMENT_DYNAMIC(CTabCustomInfDlg, CDialog)
int index=0;
int nCustom;
CTabCustomInfDlg::CTabCustomInfDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTabCustomInfDlg::IDD, pParent)
    , customInf(_T(""))
{
	m_bFresh = false;
    isInit = false;
    ifShowPhone = true;
    curType = 0;
    curInput.record = 10;
    curInput.curpage = 1;
    curInput.customid = "-1";
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

CTabCustomInfDlg::~CTabCustomInfDlg()
{
}

void CTabCustomInfDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CTabNewInfDlg)
    DDX_Control(pDX, IDC_TAB_CUSTOM_INF_LIST, m_Grid); // associate the grid window with a C++ object
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_TAB_CUSTOM_COMB, combCustomInf);
    DDX_CBString(pDX, IDC_TAB_CUSTOM_COMB, customInf);
    DDX_Control(pDX, IDC_TAB_CUSTOM_PREV, btnPrev);
    DDX_Control(pDX, IDC_TAB_CUSTOM_NEXT, btnNext);
    DDX_Control(pDX, IDC_TAB_CUSTOM_ADD, btnAddCustom);
    DDX_Control(pDX, IDC_TAB_CUSTOM_DELETE, btnDelCustom);
}


BEGIN_MESSAGE_MAP(CTabCustomInfDlg, CDialog)
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
    ON_NOTIFY(NM_RCLICK, IDC_TAB_CUSTOM_INF_LIST, OnGridRClick)
	ON_NOTIFY(NM_DBLCLK, IDC_TAB_CUSTOM_INF_LIST, OnGridDBLClick)
    ON_CBN_SELCHANGE(IDC_TAB_CUSTOM_COMB, &CTabCustomInfDlg::OnCbnSelchangeTabCustomComb)
    ON_BN_CLICKED(IDC_TAB_CUSTOM_ADD, &CTabCustomInfDlg::OnBnClickedTabCustomAdd)
    ON_BN_CLICKED(IDC_TAB_CUSTOM_DELETE, &CTabCustomInfDlg::OnBnClickedTabCustomDelete)
    ON_COMMAND(ID_MENU_OPERATION_SENDMSG, &CTabCustomInfDlg::OnMenuSendmsgSendmsg)
    ON_BN_CLICKED(IDC_TAB_CUSTOM_PREV, &CTabCustomInfDlg::OnBnClickedTabCustomPrev)
    ON_BN_CLICKED(IDC_TAB_CUSTOM_NEXT, &CTabCustomInfDlg::OnBnClickedTabCustomNext)
	ON_CBN_DROPDOWN(IDC_TAB_CUSTOM_COMB, &CTabCustomInfDlg::OnCbnDropdownTabCustomComb)

	ON_MESSAGE(WM_SETGRID,OnFresh)
	ON_CBN_CLOSEUP(IDC_TAB_CUSTOM_COMB, &CTabCustomInfDlg::OnCbnCloseupTabCustomComb)
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(CTabCustomInfDlg)
    // EASYSIZE(control,left,top,right,bottom,options)
	EASYSIZE(IDC_TAB_CUSTOM_INF_LIST, ES_BORDER, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	EASYSIZE(IDC_TAB_CUSTOM_NEXT, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_KEEPSIZE, 0)
    EASYSIZE(IDC_TAB_CUSTOM_PREV, ES_KEEPSIZE, ES_BORDER, IDC_TAB_CUSTOM_NEXT, ES_KEEPSIZE, 0)
END_EASYSIZE_MAP

// CTabCustomInfDlg 消息处理程序

BOOL CTabCustomInfDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化
    // 初始化Grid控件
    initGrid();
	
    // 初始化按钮
    btnPrev.LoadBitmap(IDB_PREVPAGE);
    btnNext.LoadBitmap(IDB_NEXTPAGE);

    // 初始化自动调整控件位置
    INIT_EASYSIZE;
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}
    
// OnSize
void CTabCustomInfDlg::OnSize(UINT nType, int cx, int cy)
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
        if (0 == curType) {
            setGoods();
        }

        if (1 == curType) {
            setCars();
        }
    }
}
        
// 初始化表格
int CTabCustomInfDlg::initGrid()
{
	int m_nFixRows = 0; 
	int m_nCols = 4;

    CRect rect;
    GetDlgItem(IDC_TAB_CUSTOM_INF_LIST)->GetWindowRect(rect); //得到显示区域
    int spaceWidth = 0;
    int colWidth1 = spaceWidth;
    int colWidth2 = spaceWidth;
    int colWidth3 = rect.Width() - colWidth1 - colWidth2 - 20;
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
        // 设置成列表模式
        m_Grid.SetListMode();
        // 设置每次只选择一行，必须和列表模式一起使用
        m_Grid.SetSingleRowSelection();

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

// 设置Grid控件
int CTabCustomInfDlg::setGrid(vector<TabCustomInfRecord> * pcontentData)
{
	//EnterCriticalSection(&csPrintFresh);
	//vector<TabCustomInfRecord> contentData(pLocalContentData);
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
    vector<TabCustomInfRecord>::iterator iter = pcontentData->begin();
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
	//delete pcontentData;
	//LeaveCriticalSection(&csPrintFresh);
    return 0;
}
    
// NM_RCLICK
void CTabCustomInfDlg::OnGridRClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
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
	pPopupMenu->TrackPopupMenu(TPM_TOPALIGN, point.x, point.y, this, NULL);
}

void CTabCustomInfDlg::OnGridDBLClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
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

	int index = curSelRow;
	CNewInfoDetailDlg dlg(&contentData.at(index), (curType==0)?CNewInfoDetailDlg::eInfoType_CustomGoods:CNewInfoDetailDlg::eInfoType_CustomCars, this);
	dlg.DoModal();
}

// 弹出菜单：发短信
void CTabCustomInfDlg::OnMenuSendmsgSendmsg()
{
    // TODO: 在此添加命令处理程序代码
	if( curSelRow >= 0 )
	{
		SendSMS(contentData.at(curSelRow));
	}
}    

void CTabCustomInfDlg::SendSMS(const TabCustomInfRecord& content)
{
	string tmp = content.startPlace + "->" + content.endPlace+ "。" + content.record+ content.tel;
	CSendPhoneMsgDlg dlg;
	dlg.phoneMsg = tmp.c_str();
	if (dlg.DoModal() == IDOK) {
		//		SuspendThread(hThread);
		//         string result = svrIONew->sendPhoneMessage((LPTSTR)(LPCTSTR)dlg.phoneNumber, (LPTSTR)(LPCTSTR)dlg.phoneMsg);
		//         if (result == "TRUE") {
		//             MessageBox("短信发送成功！","发送短信");
		//         } else {
		//             MessageBox(result.c_str(),"短信发送失败");
		//         }
		sphonenum = (LPTSTR)(LPCTSTR)dlg.phoneNumber;
		sphonetext = (LPTSTR)(LPCTSTR)dlg.phoneMsg;
		DWORD PID;
		HANDLE Main_Thread;
		nCustom = 20;
		//SuspendThread(hThread);
		//Sleep(100);
		Main_Thread=CreateThread(NULL,0,ThreadFuncMy,this,0,&PID);
	}
}


// set grid content font
int CTabCustomInfDlg::setCridContentFont(SettingFont& font)
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
       
// 计算行数
int CTabCustomInfDlg::calRow()
{
    CRect rect;
    GetDlgItem(IDC_TAB_CUSTOM_INF_LIST)->GetWindowRect(rect); //得到显示区域
    if (rect.Width() > 800) {
        curInput.record = rect.Height()/(abs(contentFont.lfHeight) + 10);
    } else {
        curInput.record = (rect.Height()/abs(contentFont.lfHeight))/2;
    } 

    return 0;
}
    
// 设置货源
int CTabCustomInfDlg::setGoods(int curpage)
{
	try
	{
		if (svrIO == NULL) {
			return -1;
		}
		//EnterCriticalSection(&csPrint);
		//svrIO->getUserCustomInf();
		/*SuspendThread(hThread);
		SuspendThread(hThreadTimer);
		SuspendThread(hThreadCY);
		if ("TRUE" != svrIO->getUserCustomInfHY()) {
			combCustomInf.ResetContent();
			contentData.clear();
			try
			{
				setGrid();
			}
			catch (...)
			{

			}
		return -1;
		}*/

		//Sleep(100);
		curType = 0;
		if (-1 != curpage) { // -1: 保留当前curpage
			curInput.curpage = curpage;
		}
		calRow();
		//Sleep(100);
		// Delete every other item from the combo box.
		//if (!m_bFresh)
		{
			while (combCustomInf.GetCount() > 0) {
				combCustomInf.DeleteString( 0 );
			}
		}

		
		int setSel = 0;
		int pos = 0;

		// 设置区域列表  
		//zoneInf = svrIO->hyZoneInf;
		 vector<CustomZoneInf> zoneInf;
		zoneInf = zoneInfHY;

		vector<CustomZoneInf>::iterator iter = zoneInf.begin();
		string tmp("");
		while (iter != zoneInf.end()) {

			tmp = (*iter).startProvince + (*iter).startCity + "->"
				+ (*iter).endProvince + (*iter).endCity;
			combCustomInf.AddString(tmp.c_str());
			if ((*iter).id == curInput.customid) {
				setSel = pos;
			}
			++iter;
			++pos;
		}

		if (index > combCustomInf.GetCount() -1)
		{
			index = 0;
			combCustomInf.SetCurSel(index);
		}
		else
			combCustomInf.SetCurSel(index);

		int nUM = combCustomInf.FindStringExact(0,m_NewAddGoods);
		if (nUM != CB_ERR)
		{
			combCustomInf.SetCurSel(nUM);
			index = nUM;
		}
		vector<TabCustomInfRecord> * pcontentData = new vector<TabCustomInfRecord>();
		//ZeroMemory(pcontentData,sizeof vector<TabCustomInfRecord>);

		// 设置标题数据
		TabCustomInfRecord title;
		title.startPlace = "出发地";
		title.endPlace = "到达地";
		title.record = "定制货源信息";
		titleData = title;

		// 设置内容
		if (svrIO->hyZoneInf.size() > 0) {
			//if (curInput.customid == "-1") {
			//	curInput.customid = svrIO->hyZoneInf.at(0).id;
			//}
			//else
			//svrIO->getCustomGoodsInf(contentData, curInput);
			pcontentData->clear();
			contentData.clear();
			/*int len = contentDataDZHY[index].size();
			if (len < curInput.record)
			{
				for (int i=0;i<len;i++)
				{
					contentData.push_back(contentDataDZHY[index][i]);
				}
			}*/

			if (contentDataDZHY[index].size() != 0)
			{
				int len = contentDataDZHY[index].size();
				if (len < curInput.record)
				{
					for (int i=0;i<len;i++)
					{
						if (contentDataDZHY[index][i].recordID != "")
						{
							pcontentData->push_back(contentDataDZHY[index][i]);
							contentData.push_back(contentDataDZHY[index][i]);
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
							TRACE("hi \n");
							pcontentData->clear();
							DWORD PID;
							HANDLE Main_Thread;
							nCustom = 0;
							//SuspendThread(hThread);
							//Sleep(100);
							Main_Thread=CreateThread(NULL,0,ThreadFuncMy,this,0,&PID);
							CloseHandle(Main_Thread);
							return 0;
						}
						if (contentDataDZHY[index][i].recordID != "")
						{
							pcontentData->push_back(contentDataDZHY[index][i]);
							contentData.push_back(contentDataDZHY[index][i]);
						}
					}
				}
			}
		} else {
			//contentData.clear();
		}

		// 设置最大页数
		if (pcontentData->size() > 0) {
			maxPageNum = atoi(pcontentData->at(0).totalNum.c_str()) / curInput.record;
			if (maxPageNum < 1) {
				maxPageNum = 1;
			}
		}
		//vector<TabCustomInfRecord> *newdata(&contentData);
		try
		{
			setGrid(pcontentData);
		}
		catch (...)
		{

		}
		//ClearVector(*pcontentData);
	}
	catch (...)
	{
		setGoods();
	}
	
	//LeaveCriticalSection(&csPrint);
    return 0;
}
    
// 设置车源
int CTabCustomInfDlg::setCars(int curpage)
{
	try
	{
		if (svrIO == NULL) {
			return -1;
		}

		//svrIO->getUserCustomInf();
		//EnterCriticalSection(&csPrint);

		/*SuspendThread(hThread);
		SuspendThread(hThreadTimer);
		SuspendThread(hThreadCY);


		if ("TRUE" != svrIO->getUserCustomInfCY()) {
			combCustomInf.ResetContent();
			contentData.clear();
			try
			{
				setGrid();
			}
			catch (...)
			{

			}
		return -1;
		}*/
		
		//Sleep(100);
		curType = 1;
		if (-1 != curpage) { // -1: 保留当前curpage
			curInput.curpage = curpage;
		}
		calRow();
		//Sleep(100);
		// Delete every other item from the combo box.
		//if (!m_bFresh)
		{
			while (combCustomInf.GetCount() > 0) {
				combCustomInf.DeleteString( 0 );
			}
		}
		combCustomInf.ResetContent();
		int setSel = 0;
		int pos = 0;

		// 设置区域列表
		//zoneInf = svrIO->cyZoneInf;
		 vector<CustomZoneInf> zoneInf;
		zoneInf = zoneInfCY;
		vector<CustomZoneInf>::iterator iter = zoneInf.begin();
		string tmp("");
		while (iter != zoneInf.end()) {
			tmp = (*iter).startProvince + (*iter).startCity + "->"
				+ (*iter).endProvince + (*iter).endCity;
			combCustomInf.AddString(tmp.c_str());
			if ((*iter).id == curInput.customid) {
				setSel = pos;
			}
			++iter;
			++pos;
		}
		if (index > combCustomInf.GetCount() -1)
		{
			index = 0;
			combCustomInf.SetCurSel(index);
		}
		else
			combCustomInf.SetCurSel(index);

		int nUM = combCustomInf.FindStringExact(0,m_NewAddCars);
		if (nUM != CB_ERR)
		{
			combCustomInf.SetCurSel(nUM);
			index = nUM;
		}
		//CWLRClientDlg *pDlg=(CWLRClientDlg*)AfxGetApp()->GetMainWnd();
		// pDlg->refreshShow();
		// 设置标题数据
		TabCustomInfRecord title;
		title.startPlace = "出发地";
		title.endPlace = "到达地";
		title.record = "定制车源信息";
		titleData = title;


		vector<TabCustomInfRecord> * pcontentData = new vector<TabCustomInfRecord>();
		//ZeroMemory(pcontentData,sizeof vector<TabCustomInfRecord>);
		// 设置内容
		if (svrIO->cyZoneInf.size() > 0) {
			//if (curInput.customid == "-1") {
			//	curInput.customid = svrIO->cyZoneInf.at(0).id;
			//}
			//else
			//svrIO->getCustomCarsInf(contentData, curInput);
			pcontentData->clear();
			contentData.clear();
			/*int len = contentDataDZCY[index].size();
			if (len < curInput.record)
			{
				for (int i=0;i<len;i++)
				{
					contentData.push_back(contentDataDZCY[index][i]);
				}
			}*/

			if (contentDataDZCY[index].size() != 0)
			{
				int len = contentDataDZCY[index].size();
				if (len < curInput.record)
				{
					for (int i=0;i<len;i++)
					{
						if (contentDataDZCY[index][i].recordID != "")
						{
							pcontentData->push_back(contentDataDZCY[index][i]);
							contentData.push_back(contentDataDZCY[index][i]);
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
							nCustom = 1;
							//SuspendThread(hThread);
							//Sleep(100);
							Main_Thread=CreateThread(NULL,0,ThreadFuncMy,this,0,&PID);
							CloseHandle(Main_Thread);
							return 0;
						}
						if (contentDataDZCY[index][i].recordID != "")
						{
							pcontentData->push_back(contentDataDZCY[index][i]);
							contentData.push_back(contentDataDZCY[index][i]);
						}

					}
				}
			}

		} else {
			contentData.clear();
		}

		// 设置最大页数
		if (pcontentData->size() > 0) {
			maxPageNum = atoi(pcontentData->at(0).totalNum.c_str()) / curInput.record;
			if (maxPageNum < 1) {
				maxPageNum = 1;
			}
		}
		//vector<TabCustomInfRecord> *newdata(&contentData);
		setGrid(pcontentData);
	}
	catch (...)
	{
		//setCars();
	}
 
	//LeaveCriticalSection(&csPrint);
    return 0;
}
    
// 点击下拉框
void CTabCustomInfDlg::OnCbnSelchangeTabCustomComb()
{
    // TODO: 在此添加控件通知处理程序代码
	//KillTimer(AUTO_REFRESH_TIMER_ID);
    index = combCustomInf.GetCurSel();
	try
	{
		//curInput.customid = zoneInf.at(index).id;
	}
	catch (...)
	{
	}

	m_bFresh = FALSE;
	TRACE("-FALSE-\n");
    if (0 == curType) {
		m_NewAddGoods = "";
		combCustomInf.GetLBText(index,m_NewAddGoods);
		//EnterCriticalSection(&csPrint);
        setGoods();
		//LeaveCriticalSection(&csPrint);
    }

    if (1 == curType) {
		m_NewAddCars = "";
		combCustomInf.GetLBText(index,m_NewAddCars);
		//EnterCriticalSection(&csPrint);
        setCars();
		//LeaveCriticalSection(&csPrint);
    }
	//SetTimer(AUTO_REFRESH_TIMER_ID, 1500, NULL);
}
    
// 增加定制
void CTabCustomInfDlg::OnBnClickedTabCustomAdd()
{
    // TODO: 在此添加控件通知处理程序代码
    CAddCustomZoneDlg dlg;
    dlg.myCR = svrIONew->myCR; 
    if (dlg.DoModal() == IDOK) {        
        CustomZoneInf tmp;
        tmp.startProvince = (LPTSTR)(LPCTSTR)dlg.strStartProvince;
        tmp.startCity = (LPTSTR)(LPCTSTR)dlg.strStartCity;
        tmp.endProvince = (LPTSTR)(LPCTSTR)dlg.strEndProvince;
        tmp.endCity = (LPTSTR)(LPCTSTR)dlg.strEndCity;
        if (curType == 0) {
            tmp.type = "hy";
        } else {
            tmp.type = "cy";
        }
HH:     string result;
		try
		{
			result = svrIONew->addUserCustomInf(tmp);
		}
		catch (...)
		{
			goto HH;
		}
        if (result == "TRUE") {
			TRACE("-FALSE-\n");
			m_bFresh = FALSE;
            MessageBox("增加定制区域成功！","增加定制区域");
            curInput.customid = "-1";
            if (curType == 0) {
				m_NewAddGoods = "";
				m_NewAddGoods += tmp.startProvince.c_str();
				m_NewAddGoods +=tmp.startCity.c_str();
				m_NewAddGoods +="->";
				m_NewAddGoods +=tmp.endProvince.c_str();
				m_NewAddGoods +=tmp.endCity.c_str();
                setGoods();
            } else {
				m_NewAddCars ="";
				m_NewAddCars += tmp.startProvince.c_str();
				m_NewAddCars +=tmp.startCity.c_str();
				m_NewAddCars +="->";
				m_NewAddCars +=tmp.endProvince.c_str();
				m_NewAddCars +=tmp.endCity.c_str();
                setCars();
            }            
        } else {
            MessageBox(result.c_str(),"增加定制区域");
        }
    }
    
}
    
// 删除定制
void CTabCustomInfDlg::OnBnClickedTabCustomDelete()
{
    // TODO: 在此添加控件通知处理程序代码
    string id;
    int index = combCustomInf.GetCurSel();
	
	if (index < 0) {
		return;
	}
	try
	{
		if (curType == 0) {
			id = svrIO->hyZoneInf.at(index).id;
		} else {
			id = svrIO->cyZoneInf.at(index).id;
		}
	}
	catch (...)
	{
	}

string result;
	try
	{
		//while(1)
		{
			result = svrIONew->deleteUserCustomInf(id);
			if (result == "TRUE")
			{
			//	break;
			}
			//Sleep(100);
		}
		
	}
	catch (...)
	{
	}
    if (result == "TRUE") {
		m_bFresh = FALSE;
		TRACE("-FALSE-\n");
		//combCustomInf.SetCurSel(0);
		index = 0;
        MessageBox("删除定制区域成功！","删除定制区域");
        curInput.customid = "-1";

        if (curType == 0) {
            setGoods();
        } else {
            setCars();
        }            
    } else {
        MessageBox(result.c_str(),"删除定制区域");
    }
}
    
// 前一页
void CTabCustomInfDlg::OnBnClickedTabCustomPrev()
{
    // TODO: 在此添加控件通知处理程序代码
    if(curInput.curpage <= 1) {
        return;
    }
    curInput.curpage -= 1;
    
    if(0 == curType) {
        setGoods(curInput.curpage);
    }

    if(1 == curType) {
        setCars(curInput.curpage);
    }
}
    
// 后一页
void CTabCustomInfDlg::OnBnClickedTabCustomNext()
{
    // TODO: 在此添加控件通知处理程序代码
    if(curInput.curpage == maxPageNum) {
        return;
    }
    curInput.curpage += 1;
    
    if(0 == curType) {
        setGoods(curInput.curpage);
    }

    if(1 == curType) {
        setCars(curInput.curpage);
    }
}

void CTabCustomInfDlg::OnCbnDropdownTabCustomComb()
{
	// TODO: 在此添加控件通知处理程序代码
	TRACE("-TRUE-\n");
	m_bFresh = true;
}
DWORD CTabCustomInfDlg::ThreadFuncMy(LPVOID p)
{
	CoInitialize(NULL);
	CTabCustomInfDlg * dlg = (CTabCustomInfDlg*)p;

	if (csPrintCustom.LockCount == 0) return -1;
	EnterCriticalSection(&csPrintCustom);

	vector<TabCustomInfRecord> * pcontentData = new vector<TabCustomInfRecord>();
	//ZeroMemory(pcontentData,sizeof vector<TabCustomInfRecord>);
	//while(1)
	{
		int nstat = -1;
		switch (nCustom)
		{
		case 0:
			nstat = dlg->svrIONew->getCustomGoodsInf(* pcontentData, dlg->curInput);
			break;
		case 1:
			nstat = dlg->svrIONew->getCustomGoodsInf(* pcontentData, dlg->curInput);
			break;
		case 2:
			//nstat = dlg->svrIONew->getMyCarsInf(dlg->contentData, dlg->curInput);
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
	//vector<TabCustomInfRecord> *newdata(&dlg->contentData);
	// 设置表格   
	try
	{
		//dlg->setGrid();
		::PostMessage(dlg->GetSafeHwnd(),WM_SETGRID,(WPARAM)pcontentData,0);
	}
	catch (...)
	{

	}
	//ResumeThread(hThread);
	//delete pcontentData;
	LeaveCriticalSection(&csPrintCustom);
	CoUninitialize();
	return 0;
}

//处理消息刷新
LONG CTabCustomInfDlg::OnFresh(WPARAM w, LPARAM l)
{
	//vector<TabCustomInfRecord> * data = (vector<TabCustomInfRecord> *)w;
	try
	{
		setGrid((vector<TabCustomInfRecord> *)w);
	}
	catch (...)
	{

	}
	return 0;
}
void CTabCustomInfDlg::OnCbnCloseupTabCustomComb()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bFresh = FALSE;
}
