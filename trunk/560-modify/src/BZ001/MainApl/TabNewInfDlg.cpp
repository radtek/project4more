// TabNewInfDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "TabNewInfDlg.h"
#include "SendPhoneMsgDlg.h"
#include "CommDef.h"
#include "header.h"

extern UserInfo user;
// CTabNewInfDlg �Ի���
CStringArray m_data;
IMPLEMENT_DYNAMIC(CTabNewInfDlg, CDialog)
int nnewhy=0;
int nnewcy=0;
int nnewld=0;

CRITICAL_SECTION csStop;
int nSSset = 0;//�����Ĳ���
// ���캯��
CTabNewInfDlg::CTabNewInfDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTabNewInfDlg::IDD, pParent)
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

// �Զ��ı�ؼ�λ�ô�С
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

// CTabNewInfDlg ��Ϣ�������

BOOL CTabNewInfDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//
	if (m_Picture.Load(MAKEINTRESOURCE(IDR_WAIT),_T("GIF")))
	{
		m_Picture.Draw();
	}
    // ��ʼ��Grid�ؼ�
    initGrid();

    // ��ʼ����ť
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
	//MyThread=CreateThread(NULL,0,ProcMore,this,0,&PID);//��ʱˢ�µ����ݲɼ�
	//ResetEvent(MyEvent);

	m_bStart = TRUE;
	m_bEnd = FALSE;
	
	//SetTimer(1,50,NULL);
	//SetEvent()

    // ��ʼ���Զ������ؼ�λ��
    INIT_EASYSIZE;
    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}

void CTabNewInfDlg::OnSize(UINT nType, int cx, int cy)
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
int CTabNewInfDlg::initGrid() {
	int m_nFixRows = 0; 
	int m_nCols = 4;
    CRect rect;
    GetDlgItem(IDC_TAB_NEW_INF_LIST)->GetWindowRect(rect); //�õ���ʾ����
    int spaceWidth = 0;
    int colWidth1 = spaceWidth;
    int colWidth2 = spaceWidth;
    int colWidth3 = rect.Width() - colWidth1 - colWidth2 - 20;//- 20;//-20;
    int colWidth4 = 20;

	TRY {	    
		m_Grid.SetColumnCount(m_nCols);
		m_Grid.SetFixedRowCount(m_nFixRows);
		    //m_Grid.SetFixedColumnCount(m_nFixCols);
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
int CTabNewInfDlg::calRow()
{
    CRect rect;
    GetDlgItem(IDC_TAB_NEW_INF_LIST)->GetWindowRect(rect); // �õ���ʾ����
    if (rect.Width() > 800) {
        curInput.record = rect.Height()/(abs(contentFont.lfHeight) + 10);
    } else {
        curInput.record = (rect.Height()/abs(contentFont.lfHeight))/2;
    }
    return 0;
}

// ��������
int CTabNewInfDlg::setData(int type, int curpage)
{
	//EnterCriticalSection(&csPrint);
	m_bStart = FALSE;
    if (svrIO == NULL) {
        return -1;
    }
	//EnterCriticalSection(&csPrint);
    curType = type;
    if (-1 != curpage) { // -1: ������ǰcurpage
        curInput.curpage = curpage;
    }
    calRow();
    // ���ñ�������

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
	//�ڴ�ռ�,�ᵼ��pcontentData�ĵ���ʧ�ܣ��ٴ�ȡ��ZeroMemory
	//ZeroMemory(pcontentData,sizeof vector<TabNewInfRecord>);
    TabNewInfRecord title;
    title.startPlace = "������";
    title.endPlace = "�����";
	contentData.clear();
	pcontentData->clear();
	
    switch (curType) {
        case 0: // ��Դ
			
		//	m_editStartAddr.SetWindowText(_T(""));
		//	m_editDestAddr.SetWindowText(_T(""));

			title.record = "���»�Դ��Ϣ";
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
        case 1: // �㵣
            title.record = "�����㵣��Ϣ";
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
        case 2: // ��Դ
		//	m_editStartAddr.SetWindowText(_T(""));
		//	m_editDestAddr.SetWindowText(_T(""));

            title.record = "���³�Դ��Ϣ";
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
        case 3: // ��������Դ
            title.record = "�������Ļ�Դ��Ϣ";
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
        case 4: // �������㵣
            title.record = "���������㵣��Ϣ";
			//contentData.clear();
			//SuspendThread(hThread);
			//Sleep(200);
			pcontentData->clear();
			nSSset = 1;
			Main_Thread=CreateThread(NULL,0,ThreadFuncSS,this,0,&PID);
			CloseHandle(Main_Thread);
            break;
        case 5: // ��������Դ
            title.record = "�������ĳ�Դ��Ϣ";
			//contentData.clear();
			//SuspendThread(hThread);
			pcontentData->clear();
			nSSset = 2;
			Main_Thread=CreateThread(NULL,0,ThreadFuncSS,this,0,&PID);
			CloseHandle(Main_Thread);

            break;
        case 6: // �����������Դ
            title.record = "�������Ļ�Դ��Ϣ";
			//contentData.clear();
			//SuspendThread(hThread);
			pcontentData->clear();
			nSSset = 3;
			Main_Thread=CreateThread(NULL,0,ThreadFuncSS,this,0,&PID);
            break;
        case 7: // ����������㵣
            title.record = "���������㵣��Ϣ";
			//contentData.clear();
			//SuspendThread(hThread);
			pcontentData->clear();
			nSSset = 4;
			Main_Thread=CreateThread(NULL,0,ThreadFuncSS,this,0,&PID);
			CloseHandle(Main_Thread);
            break;
        case 8: // �����������Դ
            title.record = "�������ĳ�Դ��Ϣ";
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
	
    // �������ҳ��
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
    // ���ñ��   
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
    
// ����Grid�ؼ�
int CTabNewInfDlg::setGrid(vector<TabNewInfRecord> * pcontentData)
{
	//EnterCriticalSection(&csPrintFresh);
	//EnterCriticalSection(&csPrintOther);
	//vector<TabNewInfRecord> contentData1(pcontentData->begin(),pcontentData->end());
    int m_nRows = pcontentData->size();
	//contentData.resize(m_nRows);
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
            //tmpStr = "��" + (*iter).startPlace + "��" + (*iter).endPlace +"��" + (*iter).record + (*iter).tel;
            tmpStr = "���:" + (*iter).recordID + "��" + (*iter).startPlace + "��" + (*iter).endPlace +"��" 
                          + (*iter).record + (*iter).tel;
        } else {
            //tmpStr = "��" + (*iter).startPlace + "��" + (*iter).endPlace +"��" + (*iter).record;
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
        ++iter;
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
    //str.Format(_T("ѡ����Ϊ�� %d"), pItem->iRow);
    //AfxMessageBox(str);
    // ��ȡ��ǰѡ�����
    curSelRow = pItem->iRow;
    if (curSelRow < 0) {
        return;
    }

    // ���õ����˵�
    CPoint   point; 
    ::GetCursorPos(&point);     			
    CMenu menu;//�˵�
    CMenu* pPopupMenu;//�˵�ָ��
    menu.LoadMenu(IDR_MENU_OPERATION);//����IDΪIDR_MENU1�Ĳ˵�
    pPopupMenu = menu.GetSubMenu(0);   //��ȡ�����˵��ĵ�һ���Ӳ˵�����ָ��

    //�����˵���������һ��������ʾ��ݲ˵����±߽����ɲ���yָ����������� 
	//�ڶ��͵�����Ϊx��y���꣬���ĸ���ʾӵ�д˲˵��Ĵ��ھ����
	//�����Ĭ��ΪNULL,��ʾ���û��ڲ˵��������������ʱ���˵�����ʧ
	pPopupMenu->TrackPopupMenu(TPM_TOPALIGN,point.x,point.y,this,NULL);
}
    
// �����˵���������
void CTabNewInfDlg::OnMenuSendmsgSendmsg()
{
    // TODO: �ڴ���������������
    int index = curSelRow;
    string tmp = contentData.at(index).startPlace + "->" + contentData.at(index).endPlace
        + "��" + contentData.at(index).record+ contentData.at(index).tel;
    CSendPhoneMsgDlg dlg;
    dlg.phoneMsg = tmp.c_str();
    if (dlg.DoModal() == IDOK) {
		sphonenum = (LPTSTR)(LPCTSTR)dlg.phoneNumber;
		sphonetext = (LPTSTR)(LPCTSTR)dlg.phoneMsg;
		//SuspendThread(hThread);
//         string result = svrIO->sendPhoneMessage((LPTSTR)(LPCTSTR)dlg.phoneNumber, (LPTSTR)(LPCTSTR)dlg.phoneMsg);
// 
//         if (result == "TRUE") {
//             MessageBox("���ŷ��ͳɹ���","���Ͷ���");
//         } else {
//             MessageBox(result.c_str(),"���ŷ���ʧ��");
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
    
// ǰһҳ
void CTabNewInfDlg::OnBnClickedTabNewPrev()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    if(curInput.curpage <= 1) {
        return;
    }

    curInput.curpage -= 1;
    setData(curType, curInput.curpage);
	Invalidate(TRUE);
}
    
// ��һҳ
void CTabNewInfDlg::OnBnClickedTabNewNext()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    if(curInput.curpage == maxPageNum) {
        return;
    }

    curInput.curpage += 1;
    setData(curType, curInput.curpage);
	Invalidate(TRUE);
}


//���������߳�
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
	// ���ñ��   
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

//������Ϣˢ��
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
	// ���ñ��   
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
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
//	if( m_sStartProvince.empty() || m_sStartProvince == "����" )
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
			if( curType == 0 || curType == 3)//��Դ
			{
				((CWLRClientDlg*)AfxGetApp()->GetMainWnd())->PostMessage(WM_TNI_START_SEARCH, eSearchType_Goods, 2);
			}
			else if( curType == 2 || curType == 5 )//��Դ
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
	if( curType == 0 || curType == 3)//��Դ
	{
		((CWLRClientDlg*)AfxGetApp()->GetMainWnd())->PostMessage(WM_TNI_START_SEARCH, eSearchType_Goods, 2);
	}
	else if( curType == 2 || curType == 5 )//��Դ
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
