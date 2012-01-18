// TabSpecialLineDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "TabSpecialLineDlg.h"
#include "CommDef.h"
#include "header.h"
#include "SpecLineDetailDlg.h"

// CTabSpecialLineDlg �Ի���

IMPLEMENT_DYNAMIC(CTabSpecialLineDlg, CDialog)
    
int nSet;
// ���캯��
CTabSpecialLineDlg::CTabSpecialLineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTabSpecialLineDlg::IDD, pParent)
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
    contentFont.lfHeight=14; // �����С 
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

// �Զ��ı�ؼ�λ�ô�С
BEGIN_EASYSIZE_MAP(CTabSpecialLineDlg)
    // EASYSIZE(control,left,top,right,bottom,options)
	EASYSIZE(IDC_TAB_SPECIAL_LINE_LIST, ES_BORDER, ES_BORDER, ES_BORDER, ES_BORDER, 0)
    EASYSIZE(IDC_TAB_SPECIAL_LINE_NEXT, ES_KEEPSIZE, ES_BORDER, ES_BORDER, ES_KEEPSIZE, 0)
    EASYSIZE(IDC_TAB_SPECIAL_LINE_PREV, ES_KEEPSIZE, ES_BORDER, IDC_TAB_SPECIAL_LINE_NEXT, ES_KEEPSIZE, 0)
END_EASYSIZE_MAP

// CTabSpecialLineDlg ��Ϣ�������

BOOL CTabSpecialLineDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if (m_Picture.Load(MAKEINTRESOURCE(IDR_WAIT),_T("GIF")))
		m_Picture.Draw();
    // ��ʼ��Grid�ؼ�
    initGrid();

    // ��ʼ����ť
    btnPrev.LoadBitmap(IDB_PREVPAGE);
    btnNext.LoadBitmap(IDB_NEXTPAGE);

	//btnPrev.ShowWindow(SW_HIDE);
	//btnNext.ShowWindow(SW_HIDE);

	m_btnLocal.LoadBitmap(IDB_LOCAL);
	m_btnCancelSearch.LoadBitmap(IDB_CANCEL);
	m_btnSecrecy.LoadBitmap(IDB_HIDE_PHONE_NUM);
	m_btnStopRefresh.LoadBitmap(IDB_STOP_REFRESH);


    // ��ʼ���Զ������ؼ�λ��
    INIT_EASYSIZE;
    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}
    
// OnSize
void CTabSpecialLineDlg::OnSize(UINT nType, int cx, int cy)
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
int CTabSpecialLineDlg::initGrid()
{
    int m_nFixRows = 1; // total rows
	int m_nCols = 8;    // total cols
    
    CRect rect;
    GetDlgItem(IDC_TAB_SPECIAL_LINE_LIST)->GetWindowRect(rect); //�õ���ʾ����
    int spaceWidth = rect.Width()*1/10;
    if (spaceWidth > 120) {  // �����غ͵���������
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
        m_Grid.SetEditable(false); // ���ɱ༭
        
        // �����п�
        m_Grid.SetColumnWidth(0, colWidth1); // ���õ�1�е��п�
        m_Grid.SetColumnWidth(1, colWidth2); // ���õ�2�е��п�
        m_Grid.SetColumnWidth(2, colWidth3); // ���õ�3�е��п�
        m_Grid.SetColumnWidth(3, colWidth4); // ���õ�4�е��п�
        m_Grid.SetColumnWidth(4, colWidth5); // ���õ�5�е��п�
        m_Grid.SetColumnWidth(5, colWidth6); // ���õ�6�е��п�
        m_Grid.SetColumnWidth(6, colWidth7); // ���õ�7�е��п�
        m_Grid.ExpandLastColumn(); // �������һ�еĿ��������grid����.

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
        //m_Grid.SetGridLines(GVL_HORZ);

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
int CTabSpecialLineDlg::calRow()
{
    CRect rect;
    GetDlgItem(IDC_TAB_SPECIAL_LINE_LIST)->GetWindowRect(rect); //�õ���ʾ����
    curInput.record = (rect.Height() - 28 )/(abs(contentFont.lfHeight) + 10); 

    return 0;
}
    
// ��������
int CTabSpecialLineDlg::setData(int type, int curpage)
{
    if (svrIO == NULL) {
        return -1;
    }
	//EnterCriticalSection(&csPrint);
    curType = type;
    if (-1 != curpage) { // -1: ������ǰcurpage
        curInput.curpage = curpage;
    }
    calRow();
	//Sleep(100);//�ȴ�
    // ���ñ�������

	vector<TabSpecialLineRecord> * pcontentData = new vector<TabSpecialLineRecord>();
	//ZeroMemory(pcontentData,sizeof vector<TabSpecialLineRecord>);
    TabSpecialLineRecord title;
    title.startPlace = "������";
    title.endPlace = "�����";
    title.weightPrice = "�ػ���";
    title.lightPrice = "�ݻ���";
    title.schedules = "�������";
    title.needTime = ";��ʱ��";
    //title.record = "��ϵ��Ϣ";
	contentData.clear();
    switch (curType) {
        case 0: // ����ר��
			
			m_editStartAddr.SetWindowText(_T(""));
			m_editDestAddr.SetWindowText(_T(""));

            title.record = "��ϵ��Ϣ";
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
        case 1: // �ҵ�ר��
            title.record = "��ϵ��Ϣ";
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
        case 2: // �ҵ��ղ�
            title.record = "��ϵ��Ϣ";
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
        case 3: // ����ר��
            title.record = "��ϵ��Ϣ";
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
        case 4: // �������ר��
            title.record = "��ϵ��Ϣ";
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

    // �������ҳ��
    if (pcontentData->size() > 0) {
        maxPageNum = atoi(pcontentData->at(0).totalNum.c_str()) / curInput.record +1;
        if (maxPageNum < 1) {
            maxPageNum = 1;
        }
    }
	//vector<TabSpecialLineRecord> *newdata(&contentData);
    // ���ñ��    
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
    // ���ñ�������
    for (int i=0; i<m_nCols; ++i) {
        m_Grid.SetItemFont(0, i, &titleFont);
    }
    // ������ⱳ��ɫ
    COLORREF titleBKClr = RGB(0, 128, 0);
    // �����������ɫ
    COLORREF titleFgClr = RGB(255,255,255);

    // ������
    GV_ITEM item[MAX_COL_NUM];
    for (int i=0; i<m_nCols; ++i) {
        item[i].mask = GVIF_TEXT|GVIF_FORMAT|GVIF_BKCLR|GVIF_FGCLR;
        item[i].row = 0;
        item[i].col = i;
        item[i].crBkClr = titleBKClr;
        item[i].crFgClr = titleFgClr;    				    
        item[i].nFormat = DT_CENTER;
        
        switch (i) {
            case 0: // ������
                item[i].strText = titleData.startPlace.c_str();
                break;
            case 1: // �����
                item[i].strText = titleData.endPlace.c_str();
                break;
            case 2: // �ػ���
                item[i].strText = titleData.weightPrice.c_str();
                break;
            case 3: // �ݻ���
                item[i].strText = titleData.lightPrice.c_str();
                break;
            case 4: // �������
                item[i].strText = titleData.schedules.c_str();
                break;
            case 5: // ;��ʱ��
                item[i].strText = titleData.needTime.c_str();
                break;
            case 6: // ��Ϣ����
                item[i].strText = titleData.record.c_str();
                break;
            case 7: // ������
                break;
            default:
                break;
        }

        m_Grid.SetItem(&item[i]);
    } 
 
    // ���ñ����и�
    m_Grid.SetRowHeight(0, 28);
    return 0;
}
    
// set this grid content
int CTabSpecialLineDlg::setThisGridContent(int m_nCols,vector<TabSpecialLineRecord> * pcontentData)
{
	
    // �����б���ɫ
    COLORREF rowBKClr = svrIO->myColor.oddRowBKClr;
    // ����������ɫ
    COLORREF rowFgClr = svrIO->myColor.oddRowFgClr;
    // ���ر���
    bool ifOddRow = true; 
	//vector<TabSpecialLineRecord> contentData(pLocalContentData);
    int row = 1;
    GV_ITEM item[MAX_COL_NUM];
    int itemHeight[MAX_COL_NUM]; // ��Ԫ��߶�
    int rowHeight = MIN_ROW_HEIGHT; // �и�
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
        // �ֱ�����ÿ��
        for (int i=0; i<m_nCols; ++i) {        
            switch (i) {
                case 0: // ������
                    item[i].strText = (*iter).startPlace.c_str();
                    break;
                case 1: // �����
                    item[i].strText = (*iter).endPlace.c_str();
                    break;
                case 2: // �ػ���
                    item[i].strText = (*iter).weightPrice.c_str();
                    break;
                case 3: // �ݻ���
                    item[i].strText = (*iter).lightPrice.c_str();
                    break;
                case 4: // �������
                    item[i].strText = (*iter).schedules.c_str();
                    break;
                case 5: // ;��ʱ��
                    item[i].strText = (*iter).needTime.c_str();
                    break;
                case 6: // ��Ϣ����
                    //item[i].strText = (*iter).record.c_str();
                    if (ifShowPhone) { 
                        //item[i].strText = (*iter).record.c_str();
                        item[i].strText += (*iter).tel.c_str();
                    } else {
                        item[i].strText = (*iter).pubName.c_str();            
                    }                    
                    break;
                case 7: // ������
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
            // ���ô˵�Ԫ����Ϣ
            m_Grid.SetItem(&item[i]);  
            // ������Ҫ���и�
            CSize size = m_Grid.GetTextExtent(row, i, item[i].strText);
            int n = size.cx / (m_Grid.GetColumnWidth(i) - 12);
            if (0 != size.cx%(m_Grid.GetColumnWidth(i) - 12)) {
                ++n; 
            } 
            itemHeight[i] = n*(size.cy -12) + 12;
            // �����е�Ԫ��߶�����ȡ���ֵ��Ϊ���еĸ�
            rowHeight = (rowHeight > itemHeight[i])?rowHeight:itemHeight[i];            
        } 

        // �����и� 
        m_Grid.SetRowHeight(row, rowHeight);	

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
	ClearVector(*pcontentData);
	//delete pcontentData;
    return 0;
}    
    
// ����Grid�ؼ�
int CTabSpecialLineDlg::setGrid(vector<TabSpecialLineRecord> * pcontentData)
{
	EnterCriticalSection(&csPrintFresh);
    // ������������ɫ
    m_Grid.SetGridColor(svrIO->myColor.gridClr);
	//vector<TabSpecialLineRecord> contentData(pcontentData);
    int m_nRows = pcontentData->size()+1;
    m_Grid.SetRowCount(m_nRows);
    
    // ���ñ��� 
    setThisGridTitle(m_Grid.GetColumnCount());

    // ��������
    setThisGridContent(m_Grid.GetColumnCount(),pcontentData);

    // ˢ��
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
    // ���õ����˵�
    CPoint   point; 
    ::GetCursorPos(&point);     			
    CMenu menu;//�˵�
	menu.CreatePopupMenu();

	int nMenuId = 1000;
    if (curType == 0 || curType == 3 || curType == 4) 
	{
		int index = curSelRow-1;
		menu.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�򿪱���Ϣ");
		menu.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ղ�ר��");
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
		menu.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�򿪱���Ϣ");
		menu.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ɾ��");
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
		menu.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�򿪱���Ϣ");
		menu.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ȡ���ղ�");
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

    //�����˵���������һ��������ʾ��ݲ˵����±߽����ɲ���yָ����������� 
	//�ڶ��͵�����Ϊx��y���꣬���ĸ���ʾӵ�д˲˵��Ĵ��ھ����
	//�����Ĭ��ΪNULL,��ʾ���û��ڲ˵��������������ʱ���˵�����ʧ
	//pPopupMenu->TrackPopupMenu(TPM_TOPALIGN,point.x,point.y,this,NULL);
}
void CTabSpecialLineDlg::OnGridDBLClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	//CString str;
	//str.Format(_T("ѡ����Ϊ�� %d"), pItem->iRow);
	//AfxMessageBox(str);
	// ��ȡ��ǰѡ�����
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
    
// �ղ�ר�߲˵�
void CTabSpecialLineDlg::OnMenuOperationCollect()
{
    // TODO: �ڴ���������������
    int index = curSelRow-1;
	if (index < 0)
	{
		index = 0;
	}
	//SuspendThread(hThread);
    string result = svrIO->collectSpecialLine(contentData.at(index).recordID);
	//ResumeThread(hThread);
    if (result == "TRUE") {
        MessageBox("�ղ�ר�߳ɹ���","�ղ�ר��");
    } else {
        MessageBox(result.c_str(),"�ղ�ר��ʧ��");
    }
}
    
// ɾ���˵�
void CTabSpecialLineDlg::OnMenuOperationDelete()
{
    // TODO: �ڴ���������������
    int index = curSelRow-1;
	if (index < 0)
	{
		index = 0;
	}

	DeleteSpecLine(contentData.at(index));
}
    
// ȡ��ר��
void CTabSpecialLineDlg::OnMenuOperationDelfav()
{
    // TODO: �ڴ���������������
    int index = curSelRow-1;
	if (index < 0)
	{
		index = 0;
	}
	//SuspendThread(hThread);
    string result = svrIO->delFavoriteSpecialLine(contentData.at(index).recordID);
	//ResumeThread(hThread);
    if (result == "TRUE") {
        MessageBox("ȡ���ղسɹ���","ȡ��ר���ղ�");
    } else {
        MessageBox(result.c_str(),"ȡ���ղ�ʧ��");
    }

    // ������ʾ����
    setData(curType);
}
    
// ǰһҳ
void CTabSpecialLineDlg::OnBnClickedTabSpecialLinePrev()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    if(curInput.curpage <= 1) {
        return;
    }

    curInput.curpage -= 1;
    setData(curType, curInput.curpage);
}
    
// ��һҳ
void CTabSpecialLineDlg::OnBnClickedTabSpecialLineNext()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    if(curInput.curpage == maxPageNum) {
        return;
    }

    curInput.curpage += 1;
    setData(curType, curInput.curpage);
}
//���������߳�
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
	// ���ñ��   
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

//������Ϣˢ��
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
		MessageBox("ɾ��ר�߳ɹ���","ɾ��ר��");
	} else {
		MessageBox(result.c_str(),"ɾ��ר��ʧ��");
	}

	// ������ʾ����
	setData(curType);
}
void CTabSpecialLineDlg::AddFavorite(const TabSpecialLineRecord& content)
{
	string result = svrIO->collectSpecialLine(content.recordID);
	//ResumeThread(hThread);
	if (result == "TRUE") {
		MessageBox("�ղ�ר�߳ɹ���","�ղ�ר��");
	} else {
		MessageBox(result.c_str(),"�ղ�ר��ʧ��");
	}
}
void CTabSpecialLineDlg::RemoveFavorite(const TabSpecialLineRecord& content)
{
	//SuspendThread(hThread);
	string result = svrIO->delFavoriteSpecialLine(content.recordID);
	//ResumeThread(hThread);
	if (result == "TRUE") {
		MessageBox("ȡ���ղسɹ���","ȡ��ר���ղ�");
	} else {
		MessageBox(result.c_str(),"ȡ���ղ�ʧ��");
	}

	// ������ʾ����
	setData(curType);
}
void CTabSpecialLineDlg::ShowDetail(const TabSpecialLineRecord& content)
{
	CSpecLineDetailDlg dlg(&content, this);
	dlg.DoModal();
}