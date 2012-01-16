// TabCustomInfDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "WLRClientdlg.h"
#include "TabCustomInfDlg.h"
#include "SendPhoneMsgDlg.h"
#include "AddCustomZoneDlg.h"
#include "header.h"
#include "NewInfoDetailDlg.h"
// CTabCustomInfDlg �Ի���

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

// CTabCustomInfDlg ��Ϣ�������

BOOL CTabCustomInfDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    // ��ʼ��Grid�ؼ�
    initGrid();
	
    // ��ʼ����ť
    btnPrev.LoadBitmap(IDB_PREVPAGE);
    btnNext.LoadBitmap(IDB_NEXTPAGE);

    // ��ʼ���Զ������ؼ�λ��
    INIT_EASYSIZE;
    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}
    
// OnSize
void CTabCustomInfDlg::OnSize(UINT nType, int cx, int cy)
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
        if (0 == curType) {
            setGoods();
        }

        if (1 == curType) {
            setCars();
        }
    }
}
        
// ��ʼ�����
int CTabCustomInfDlg::initGrid()
{
	int m_nFixRows = 0; 
	int m_nCols = 4;

    CRect rect;
    GetDlgItem(IDC_TAB_CUSTOM_INF_LIST)->GetWindowRect(rect); //�õ���ʾ����
    int spaceWidth = 0;
    int colWidth1 = spaceWidth;
    int colWidth2 = spaceWidth;
    int colWidth3 = rect.Width() - colWidth1 - colWidth2 - 20;
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
        // ���ó��б�ģʽ
        m_Grid.SetListMode();
        // ����ÿ��ֻѡ��һ�У�������б�ģʽһ��ʹ��
        m_Grid.SetSingleRowSelection();

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

// ����Grid�ؼ�
int CTabCustomInfDlg::setGrid(vector<TabCustomInfRecord> * pcontentData)
{
	//EnterCriticalSection(&csPrintFresh);
	//vector<TabCustomInfRecord> contentData(pLocalContentData);
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
	//delete pcontentData;
	//LeaveCriticalSection(&csPrintFresh);
    return 0;
}
    
// NM_RCLICK
void CTabCustomInfDlg::OnGridRClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
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
	pPopupMenu->TrackPopupMenu(TPM_TOPALIGN, point.x, point.y, this, NULL);
}

void CTabCustomInfDlg::OnGridDBLClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
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

	int index = curSelRow;
	CNewInfoDetailDlg dlg(&contentData.at(index), (curType==0)?CNewInfoDetailDlg::eInfoType_CustomGoods:CNewInfoDetailDlg::eInfoType_CustomCars, this);
	dlg.DoModal();
}

// �����˵���������
void CTabCustomInfDlg::OnMenuSendmsgSendmsg()
{
    // TODO: �ڴ���������������
	if( curSelRow >= 0 )
	{
		SendSMS(contentData.at(curSelRow));
	}
}    

void CTabCustomInfDlg::SendSMS(const TabCustomInfRecord& content)
{
	string tmp = content.startPlace + "->" + content.endPlace+ "��" + content.record+ content.tel;
	CSendPhoneMsgDlg dlg;
	dlg.phoneMsg = tmp.c_str();
	if (dlg.DoModal() == IDOK) {
		//		SuspendThread(hThread);
		//         string result = svrIONew->sendPhoneMessage((LPTSTR)(LPCTSTR)dlg.phoneNumber, (LPTSTR)(LPCTSTR)dlg.phoneMsg);
		//         if (result == "TRUE") {
		//             MessageBox("���ŷ��ͳɹ���","���Ͷ���");
		//         } else {
		//             MessageBox(result.c_str(),"���ŷ���ʧ��");
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
       
// ��������
int CTabCustomInfDlg::calRow()
{
    CRect rect;
    GetDlgItem(IDC_TAB_CUSTOM_INF_LIST)->GetWindowRect(rect); //�õ���ʾ����
    if (rect.Width() > 800) {
        curInput.record = rect.Height()/(abs(contentFont.lfHeight) + 10);
    } else {
        curInput.record = (rect.Height()/abs(contentFont.lfHeight))/2;
    } 

    return 0;
}
    
// ���û�Դ
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
		if (-1 != curpage) { // -1: ������ǰcurpage
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

		// ���������б�  
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

		// ���ñ�������
		TabCustomInfRecord title;
		title.startPlace = "������";
		title.endPlace = "�����";
		title.record = "���ƻ�Դ��Ϣ";
		titleData = title;

		// ��������
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

		// �������ҳ��
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
    
// ���ó�Դ
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
		if (-1 != curpage) { // -1: ������ǰcurpage
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

		// ���������б�
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
		// ���ñ�������
		TabCustomInfRecord title;
		title.startPlace = "������";
		title.endPlace = "�����";
		title.record = "���Ƴ�Դ��Ϣ";
		titleData = title;


		vector<TabCustomInfRecord> * pcontentData = new vector<TabCustomInfRecord>();
		//ZeroMemory(pcontentData,sizeof vector<TabCustomInfRecord>);
		// ��������
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

		// �������ҳ��
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
    
// ���������
void CTabCustomInfDlg::OnCbnSelchangeTabCustomComb()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
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
    
// ���Ӷ���
void CTabCustomInfDlg::OnBnClickedTabCustomAdd()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
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
            MessageBox("���Ӷ�������ɹ���","���Ӷ�������");
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
            MessageBox(result.c_str(),"���Ӷ�������");
        }
    }
    
}
    
// ɾ������
void CTabCustomInfDlg::OnBnClickedTabCustomDelete()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
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
        MessageBox("ɾ����������ɹ���","ɾ����������");
        curInput.customid = "-1";

        if (curType == 0) {
            setGoods();
        } else {
            setCars();
        }            
    } else {
        MessageBox(result.c_str(),"ɾ����������");
    }
}
    
// ǰһҳ
void CTabCustomInfDlg::OnBnClickedTabCustomPrev()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
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
    
// ��һҳ
void CTabCustomInfDlg::OnBnClickedTabCustomNext()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	//vector<TabCustomInfRecord> *newdata(&dlg->contentData);
	// ���ñ��   
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

//������Ϣˢ��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bFresh = FALSE;
}
