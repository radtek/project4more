// TabMyInfDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "TabMyInfDlg.h"
#include "header.h"
#include "NewInfoDetailDlg.h"
#include "SendPhoneMsgDlg.h"

// CTabMyInfDlg �Ի���
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
    // ��ʼ��svrIO
    svrIO = NULL;

    // ���ñ�������
    //LOGFONT titleFont;
    lstrcpy((LPSTR)titleFont.lfFaceName,(LPSTR)"����"); 
    titleFont.lfWeight=400; 
    titleFont.lfWidth=0; 
    titleFont.lfHeight=14; // �����С 
    titleFont.lfEscapement=0; 
    titleFont.lfUnderline=FALSE; 
    titleFont.lfItalic=FALSE; 
    titleFont.lfStrikeOut=FALSE; 
    titleFont.lfCharSet=GB2312_CHARSET; //���ϲ�������һ����������

    // ����������������
    //LOGFONT logfont;
    lstrcpy((LPSTR)contentFont.lfFaceName,(LPSTR)"������"); 
    contentFont.lfWeight=400; 
    contentFont.lfWidth=0; 
    contentFont.lfHeight=16; // �����С 
    contentFont.lfEscapement=0; 
    contentFont.lfUnderline=FALSE; 
    contentFont.lfItalic=FALSE; 
    contentFont.lfStrikeOut=FALSE; 
    contentFont.lfCharSet=GB2312_CHARSET; //���ϲ�������һ����������

    // ��ʼ����������
    //titleData.startPlace = "�㽭ʡ������";
    //titleData.endPlace = "����ʡ�Ͼ���";
    //titleData.record= "������Ϣ";

    // ��ʼ����Ϣ����
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

// �Զ��ı�ؼ�λ�ô�С
BEGIN_EASYSIZE_MAP(CTabMyInfDlg)
    // EASYSIZE(control,left,top,right,bottom,options)
	EASYSIZE(IDC_TAB_MY_INF_LIST, ES_BORDER, ES_BORDER, ES_BORDER, ES_BORDER, 0)
	EASYSIZE(IDC_TAB_MY_BOTTOM, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_KEEPSIZE, 0)
    EASYSIZE(IDC_TAB_MY_NEXT, ES_KEEPSIZE, ES_BORDER, IDC_TAB_MY_BOTTOM, ES_KEEPSIZE, 0)
    EASYSIZE(IDC_TAB_MY_PREV, ES_KEEPSIZE, ES_BORDER, IDC_TAB_MY_NEXT, ES_KEEPSIZE, 0)
	EASYSIZE(IDC_TAB_MY_TOP, ES_KEEPSIZE, ES_BORDER, IDC_TAB_MY_PREV, ES_KEEPSIZE, 0)
END_EASYSIZE_MAP

// CTabMyInfDlg ��Ϣ�������

BOOL CTabMyInfDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��

    // ��ʼ��Grid�ؼ�
    initGrid();

    // ��ʼ����ť
    btnPrev.LoadBitmap(IDB_PREVPAGE);
    btnNext.LoadBitmap(IDB_NEXTPAGE);
	m_btnFirstPage.LoadBitmap(IDB_FIRST_PAGE);
	m_btnLastPage.LoadBitmap(IDB_LAST_PAGE);

    // ��ʼ���Զ������ؼ�λ��
    INIT_EASYSIZE;
    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}

void CTabMyInfDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);
    UPDATE_EASYSIZE;  // �Զ��ı�ؼ�λ�ô�С

    // TODO: �ڴ˴������Ϣ����������
	CRect rect;
    GetClientRect(&rect);
    // ����С��ʱ
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
    
// ��ʼ�����
int CTabMyInfDlg::initGrid() {
	int m_nFixRows = 0; 
	int m_nCols = 4;

    CRect rect;
    GetDlgItem(IDC_TAB_MY_INF_LIST)->GetWindowRect(rect); //�õ���ʾ����
    int spaceWidth = 0;
    int colWidth1 = spaceWidth;
    int colWidth2 = spaceWidth;
    int colWidth3 = rect.Width() - colWidth1 - colWidth2 - 20;
    int colWidth4 = 20;

	TRY {
	    //m_Grid.SetRowCount(m_nRows);
		m_Grid.SetColumnCount(m_nCols);
		m_Grid.SetFixedRowCount(m_nFixRows);
        m_Grid.SetEditable(false); // ���ɱ༭
        
        // �����п�
        m_Grid.SetColumnWidth(0, colWidth1); // ���õ�1�е��п�
        m_Grid.SetColumnWidth(1, colWidth2); // ���õ�2�е��п�
        m_Grid.SetColumnWidth(2, colWidth3); // ���õ�3�е��п�
        m_Grid.ExpandLastColumn(); // �������һ�еĿ��������grid����.

        // �Զ��и�
        //m_Grid.SetAutoSizeStyle(GVS_BOTH);

        // ȡ��������ʾ
        m_Grid.EnableTitleTips(false);//.EnableToolTips(false);
        // ȡ������̶��������ڶ�Ӧ��
        m_Grid.SetFixedColumnSelection(false);
        // ����ͬ��/���еĹ̶���Ԫ����Ϊ���㵥Ԫ��ʱ�Ƿ������ʾ����ʹ�ð��ݱ�Ե
        m_Grid.SetTrackFocusCell(false);
        // ���ý��㵥Ԫ���Ƿ������ʾ���Ҽ�����߿�
        m_Grid.SetFrameFocusCell(false);
        // ȡ���ϷŹ���
        m_Grid.EnableDragAndDrop(false);
        // �����Ƿ�������еĴ�С
        m_Grid.SetRowResize(false);
        // �����Ƿ�������еĴ�С
        m_Grid.SetColumnResize(false);
        // �����Ƿ����ͨ����꽫�еĿ��ѹ��Ϊ0
        m_Grid.EnableColumnHide(false);
        // �����Ƿ����ͨ����꽫�еĸ߶�ѹ��Ϊ0
        m_Grid.EnableRowHide(false);
        // ���õ�Ԫ���Ƿ��ѡ
        m_Grid.EnableSelection(false);

        // ���ó��б�ģʽ
        m_Grid.SetListMode();
        // ����ÿ��ֻѡ��һ�У�������б�ģʽһ��ʹ��
        m_Grid.SetSingleRowSelection();  

        // ���������ߣ�ֻ�к���
        m_Grid.SetGridLines(GVL_HORZ);

        // ����˫������
        m_Grid.SetDoubleBuffering();

        // ���ó�ʼ����־
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
    
// ��������
int CTabMyInfDlg::calRow()
{
    CRect rect;
    GetDlgItem(IDC_TAB_MY_INF_LIST)->GetWindowRect(rect); //�õ���ʾ����
    //curInput.record = (rect.Height() - 28 )/(contentFont.lfHeight + 10);
    if (rect.Width() > 800) {
        curInput.record = rect.Height()/(abs(contentFont.lfHeight) + 10);
    } else {
        curInput.record = (rect.Height()/abs(contentFont.lfHeight))/2;
    }

    return 0;
}
    
// ��������
int CTabMyInfDlg::setData(int type, int curpage)
{
	//EnterCriticalSection(&csPrintFresh);
    if (svrIO == NULL) {
        return -1;
    }
	//EnterCriticalSection(&csPrint);
    curType = type;
    if (-1 != curpage) { // -1: ������ǰcurpage
        curInput.curpage = curpage;
    }
    calRow();
	//Sleep(100);
    // ���ñ�������

	vector<TabMyInfRecord> * pcontentData = new vector<TabMyInfRecord>();
	//ZeroMemory(pcontentData,sizeof vector<TabMyInfRecord>);


    TabMyInfRecord title;
    title.startPlace = "������";
    title.endPlace = "�����";
	contentData.clear();
    switch (curType) {
        case 0: // ��Դ
            title.record = "�ҵĻ�Դ��Ϣ";
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
        case 1: // �㵣
            title.record = "�ҵ��㵣��Ϣ";
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
        case 2: // ��Դ
            title.record = "�ҵĳ�Դ��Ϣ";
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

    // �������ҳ��
    if (contentData.size() > 0) {
        maxPageNum = atoi(contentData.at(0).totalNum.c_str()) / curInput.record+1;
        if (maxPageNum < 1) {
            maxPageNum = 1;
        }
    }
	//vector<TabMyInfRecord> *newdata(&contentData);
    // ���ñ��    
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
    
// ����Grid�ؼ�
int CTabMyInfDlg::setGrid(vector<TabMyInfRecord> * pcontentData)
{
	EnterCriticalSection(&csPrintFresh);

	//vector<TabMyInfRecord> contentData(pLocalContentData);
    int m_nRows = pcontentData->size();
    m_Grid.SetRowCount(m_nRows);

    /****************** �������� ******************/
    // ������������ɫ
    m_Grid.SetGridColor(svrIO->myColor.gridClr);

    // �����б���ɫ
    COLORREF rowBKClr = svrIO->myColor.oddRowBKClr;
    // ����������ɫ
    COLORREF rowFgClr = svrIO->myColor.oddRowFgClr;
    // ���ر���
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
            tmpStr = "���:" + (*iter).recordID + "��" + (*iter).startPlace + "��" + (*iter).endPlace +"��" 
                          + (*iter).record + (*iter).tel;
        } else {
            tmpStr = "���:" + (*iter).recordID + "��" + (*iter).startPlace + "��" + (*iter).endPlace +"��" 
                          + (*iter).record;    
        }
        CString str3 = tmpStr.c_str();

        // �����1��
        // ��������
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

        // �����2��
        // ��������
        GV_ITEM Item2;
        Item2.row = row;
        Item2.col = 1;
        Item2.mask = GVIF_TEXT|GVIF_FORMAT|GVIF_BKCLR|GVIF_FGCLR;				    
        Item2.nFormat = DT_LEFT|DT_EXTERNALLEADING|DT_WORDBREAK;
        Item2.crBkClr = rowBKClr;
        Item2.crFgClr = rowFgClr;        
        //Item2.strText = str2;
        m_Grid.SetItem(&Item2);

        // �����3��
        // ��������
  		GV_ITEM Item3;        
        Item3.row = row;
        Item3.col = 2; 
        Item3.mask = GVIF_TEXT|GVIF_FORMAT|GVIF_BKCLR|GVIF_FGCLR;       
        Item3.nFormat = DT_LEFT|DT_EXTERNALLEADING|DT_WORDBREAK;        
        Item3.crBkClr = rowBKClr;
        Item3.crFgClr = rowFgClr;   
        Item3.strText = str3;
        m_Grid.SetItem(&Item3);

        // ���뱣����
        GV_ITEM Item4;        
        Item4.row = row;
        Item4.col = 3; 
        Item4.mask = GVIF_TEXT|GVIF_FORMAT|GVIF_BKCLR|GVIF_FGCLR;       
        Item4.nFormat = DT_LEFT|DT_EXTERNALLEADING|DT_WORDBREAK;        
        Item4.crBkClr = rowBKClr;
        Item4.crFgClr = rowFgClr;   
        //Item4.strText = str3;
        m_Grid.SetItem(&Item4);

        // �����и�
        // ������Ҫ���и�        
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
        // ���ÿؼ��ı�����ɫ (��Ԫ��֮�������).
        m_Grid.SetBkColor(svrIO->myColor.oddRowBKClr);
    } else {
        // ���ÿؼ��ı�����ɫ (��Ԫ��֮�������).
        m_Grid.SetBkColor(svrIO->myColor.evenRowBKClr);
    }

    // ˢ��
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

	// ���õ����˵�
	CPoint   point; 
	::GetCursorPos(&point);     			
	int nMenuId = 1000;
	CMenu menu;
	menu.CreatePopupMenu();
	menu.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�򿪱���Ϣ");
	menu.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�޸Ĳ�����");
	menu.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "���Ͷ���");
	menu.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ɾ��");
	menu.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ѳɽ�");

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
	//str.Format(_T("ѡ����Ϊ�� %d"), pItem->iRow);
	//AfxMessageBox(str);
	// ��ȡ��ǰѡ�����
	curSelRow = pItem->iRow;
	if (curSelRow < 0) {
		return;
	}
	ShowDetailInfo(&contentData.at(curSelRow));
}

    
// �����˵���ɾ��
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
    
// ǰһҳ
void CTabMyInfDlg::OnBnClickedTabMyPrev()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    if(curInput.curpage <= 1) {
        return;
    }

    curInput.curpage -= 1;
	//EnterCriticalSection(&csPrintFresh);
    setData(curType, curInput.curpage);
	//LeaveCriticalSection(&csPrintFresh);
}
    
// ��һҳ
void CTabMyInfDlg::OnBnClickedTabMyNext()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
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

//���������߳�
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
				AfxMessageBox("���ŷ��ͳɹ���");
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
	// ���ñ��   
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

//������Ϣˢ��
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
	string tmp = content.startPlace + "->" + content.endPlace+ "��" + content.record+ content.tel;
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
	// TODO: �ڴ���������������
	int index = curSelRow;
	//SuspendThread(hThread);

	switch (curType) {
		case 0: { // ��Դ

			string result = svrIO->delGoodsInf(contentData.at(index).recordID);
			if (result == "TRUE") {
				MessageBox("ɾ����Դ�ɹ���","ɾ����Դ");
			} else {
				MessageBox(result.c_str(),"ɾ����Դʧ��");
			}
			break;
				}
		case 1: {// �㵣
			string result = svrIO->delBulkGoodsInf(contentData.at(index).recordID);
			if (result == "TRUE") {
				MessageBox("ɾ���㵣�ɹ���","ɾ���㵣");
			} else {
				MessageBox(result.c_str(),"ɾ���㵣ʧ��");
			}
			break;
				}
		case 2: {// ��Դ
			string result = svrIO->delCarsInf(contentData.at(index).recordID);
			if (result == "TRUE") {
				MessageBox("ɾ����Դ�ɹ���","ɾ����Դ");
			} else {
				MessageBox(result.c_str(),"ɾ����Դʧ��");
			}
			break;
				}
		default:
			break;
	}

	// ��������
	setData(curType);
}