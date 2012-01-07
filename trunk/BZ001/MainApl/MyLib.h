/*++

Copyright shane 2008-7-29

Module Name:

    MyLib.h

--*/
#include "stdafx.h"
#pragma once

#pragma warning(disable:4996) //全部关掉
//#pragma warning(once:4996) //仅显示一个
//#pragma warning(disable:4146)

#include <odbcinst.h>	//EXCEL

#include <dbghelp.h>
#pragma comment( lib, "dbghelp.lib" )


#import <msxml.dll> named_guids
//#import "msxml.dl" raw_interfaces_only
#include <winsock.h>

#include  <mshtml.h> 
#include <afxdb.h>
#include <wininet.h>
#pragma comment(lib, "Wininet.lib")
#import  <mshtml.tlb> no_auto_exclude rename("TranslateAccelerator","HtmlTranslateAccelerator")
#include <comdef.h>
#include <afxinet.h>

#include "afxwin.h"
#include "afxmt.h"
#include "winerror.h"
#include <winsvc.h>

#include <atlbase.h>
#include <atlcom.h>

#include <gdiplus.h>
#pragma comment (lib, "gdiplus.lib")

//#import "c:\program files\common files\system\ado\msado15.dl" 	no_namespace rename ("EOF", "adoEOF") no_namespace rename ("Error", "adoError")
#include <atlrx.h>
//#pragma comment(lib, "wsock32.lib")
//#include "afxmt.h"


#define READ_FILE_TYPE_TCHAR 999
#define READ_FILE_TYPE_CHAR 998
#define SOCKET_LOG_FILE_NAME "SOCKET_LOG"
#define WORKTHREAD_LOG_FILE "workthread"
#define SOCKET_REV_BUFF_LENTH 1024
#define SOCKET_CLOSE_SLEEP_TIME 50
#define SOCKET_TYPE_SRV 1
#define SOCKET_TYPE_CLI 2

#define SPLIT_CHAR (CString)(char)12
#define SPLIT_CHAR_11 "||"

#define UM_SOCK WM_USER + 1
//#define UM_SOCK_2 WM_USER + 2

//int m_iReTryCount; 
//BOOL m_bIsShow;
//CString m_csErr;
//CCriticalSection m_Cs;
//CEvent m_Evt;
//CMutex m_Mutex;


typedef struct SockInfo{
	SOCKET ClientSocket;
	sockaddr_in Address;
	char Msgstr[SOCKET_REV_BUFF_LENTH];
}SocketInfo,* pSocketInfo;

BOOL ShutdownComputer();
/*ctrl*/
//void CArray2TreeCtrl(CArray<CStringArray,CStringArray> *arrayBranchInfo, CTreeCtrl &tree);
int GetListCurSel(CListCtrl& listCtrl);
int GetListCurSel(HWND hwnd,int nListCtrlID);
BOOL GetListSelectedValuesByCol(CListCtrl& listCtrl, CString &strValues, int iCol);
BOOL GetListCheckedValuesByCol(CListCtrl& listCtrl, CString &strValues, int iCol);
/*url*/
CString urlEncode(const TCHAR* szEncode);
HINSTANCE GotoURL(LPCTSTR url, int showcmd);
/*scrn*/
VOID SaveCurScreenJpg(LPCWSTR pszFileName, int xs, int ys, int quality);
int GetEncoderClsid(LPCWSTR format, CLSID* pClsid);
/*msg*/
void MsgBox(CString csMsg);
BOOL CheckMsgBox(CString csMsg);
void MsgBoxArray(CStringArray &arrayValue);
void ClearTodayLog(CString strLogName);
void WriteLog(CString csMsg, CString csFileName);
void Log(CString csMsg, CString csFileName);
void Log(CString csMsg, BOOL isShow = TRUE, CString csFileName = "");
void Log(CString csMsg, CString& csErr, BOOL isShow = TRUE, CString csFileName = "");
void LogPackage(WSABUF wsabuf);
void SetWdsText(CString strText, HWND hwnd);
void FrshWindows(HWND hwnd);

/*string*/
CString ConvertSqlValue(CString strValue, BOOL bWithOutDT = FALSE);
void PutClipboard(CString source, HWND hwnd);
BOOL IsNumber(CString str);
CString TrimA(CString str);
CString Int2Str0x(int numb);
CString Int2Str(int numb);
CString Int2Str(DWORD numb);
CString Numb2Str(double numb);
int Str2Int(CString str);
int Str2Int(LPSTR lpstr);
long Str2Long(CString str);
CString GetValueByKey(CStringArray& strArrayKey, CStringArray& strArrayValue, CString strKey);
BOOL FindStr(CStringList& strListDest, CString strF);
BOOL FindStr(CStringArray& strArrayDest, CString strF);
BOOL FindStr(CStringArray& strArrayDest, CString strF, int &Index);
int FindStrCount(CString Dstr, CString Fstr, CString Fstr2 = "");
void SaveToArry(CArray<CString,CString> &SaveArry, CString ScStr, TCHAR Fstr, int &Count);
void Split(CString source, CStringArray& dest, CString division = ",");
void Split(CString source, CStringList& dest, CString division);
CString Addr2String(SOCKADDR_IN addrFrom);
DWORD StrIP2DWD(CString strIP);
CString Array2String(CStringArray &arrayDest, CString division = ",");
/*file*/
CString PraseFilePath(CString csFileFullPath, int GetItem, CString csHelpStr = "GetItem: 0-Drive,1-Dir,2-Filename,3-Ext");
CString ReadFile(CString csFilePath, long &ReadLenth, int iCharType = READ_FILE_TYPE_CHAR);
BOOL ReadFile(CString csFilePath,LPSTR pbuf, long &ReadLenth);
CString ReadFile(CString csFilePath);
BOOL SaveFile(CString csMsg, char * mode, CString csFileName);
BOOL SaveFile(const char * msg,int lenth, char * mode, CString csFileName);
BOOL SaveFile(CString csFilePath, CString csMsg);
CString ReadIni(CString IniFile, CString AppName, CString KeyName, CString Default = "");
BOOL ReadIniEx(CString IniFile, CString AppName, CString KeyName,CString &value, CString Default = "");
BOOL WriteIni(CString IniFile, CString AppName, CString KeyName, CString strValue);
BOOL SaveBmp(HBITMAP hBitmap, CString FileName);
BOOL SaveBmp(HBITMAP hBitmap, CString FileName, WSABUF * pwsabuf);
void CopyScreenToBitmap(CString FileName, int xStartPt, int yStartPt, int width, int height, int xToCopy, int yToCopy);
BOOL UploadFile(CString pstrServer, CString pstrUserName, CString pstrPassword, int nPort, CString strFilePath, CString &strFileName, CString strFtpFolder, CString &csErr);
BOOL DownloadFiles(CString pstrServer, CString pstrUserName, CString pstrPassword, int nPort, CString strFtpFolder, CString strFileFullName, CString strLocalFolder, CString ExceptFile, CString &csErr);
CString SelFileG(CString csFilter = "*.*",CString csInitialDir = "C:\\Documents and Settings\\Administrator\\桌面");
CString SelFileT();
/*time*/
CString GetCurtTimeEx(int exlenth);
CString GetCurtTime();
BOOL GetTimeArea(CString &strStart, CString &strEnd, CString strType);
BOOL GetTimeArea( CTime &strStart, CTime &strEnd, CString strType );
CString GetCurrentTimeString(int iType = 0,long iDateDiff = 0, CString strHelp = "0:20090101120101, 1:120101, 2:20090101, 3:2009-01-01 12:01:01, 4:12:01:01, 5:2009-01-01");
BOOL TimeAdd(CString &strTime, LONG lDays, int nHours, int nMins, int nSecs);
CString TimeDiff(CString strTimeStart, CString strTimeEnd);
/*others*/
BOOL RunExe(LPSTR strFileFullName);
BOOL CheckInstance();
int RandomInt(int iMin, int iMax);
/*ip*/
BOOL GetHostIP(CString& IPAddress);
BOOL GetHostIpHead(CString& IPAddress);
BOOL ReplaceWD(CString& strSoce, CString strDivision);
BOOL WriteIniEc(CString IniFile, CString AppName, CString KeyName, CString strValue);
BOOL ReadIniDc(CString IniFile, CString AppName, CString KeyName,CString &value, CString Default = "");
void ShowOneWindow(CString strTitle);
float Str2Float(CString str);
CString Array2StringCvtSql( CStringArray &arrayDest, CString division = ",", BOOL bWithOutDT = FALSE );
CString Float2Str(float numb);
LONG WINAPI CleanToolExceptionFun(struct _EXCEPTION_POINTERS* ExceptionInfo);
void DisableSetUnhandledExceptionFilter();
void Dump_CallStack( CONTEXT *context );
DWORD Excep_Filter( LPEXCEPTION_POINTERS lpEP );
//系统崩溃异常捕获
void InitExceptionCatch();
CString GetExeFilePath();
void WatchArray(CStringArray &arrayShow);
int CompareStrRight(CString strSrc, CString strDest);
SYSTEMTIME String2CTime( CString strT );
CString GetClipboard(HWND hwnd);
/*class*/
class Help
{
public:
	void TimeUsed()
	{
		LARGE_INTEGER m_liPerfFreq;
		LARGE_INTEGER m_liPerfStart;
		LARGE_INTEGER liPerfNow;

		QueryPerformanceFrequency(&m_liPerfFreq); 
		QueryPerformanceCounter(&m_liPerfStart);
		Sleep(100);
		QueryPerformanceCounter(&liPerfNow);
		int time=(int)(((liPerfNow.QuadPart - m_liPerfStart.QuadPart) * 1000)/m_liPerfFreq.QuadPart);
		CString timestr;
		timestr.Format("%d",time);
	}
};



class MyAdo
{
public:
	MyAdo(void);
	~MyAdo(void);

	BOOL m_bIsShow;

	CRecordset * m_odbcRecordSet;
	CCriticalSection g_cs;
	CString m_strLastErr;
	CString m_strSqlLogFile, m_strErrLogFile;
	BOOL CheckConnect();
	BOOL ConnectAccessDB(CString csFile, CString csUid, CString csPwd, CString csDateBs, int iConnectType = 1);
	BOOL ConnectDB(CString csSrv, CString csUid, CString csPwd, CString csDateBs = "", int iConnectType = 1, int iDbType = 0);
	CString GetDatabaseName();
	BOOL ReConnectDB();
	//BOOL ExecSQL(CString sql);
	BOOL ExecSQL(CString sql, BOOL bIsLog = TRUE);
	BOOL ExecTransSQL(CString sql, BOOL bIsLog = TRUE);
	BOOL NewRecordset();
	//void NewRecordset();
	void CloseRecordset(CRecordset * RecordSet = NULL);
	BOOL SelectSQL(CString sql, int &RecordCount);
	BOOL SelectSQLEx(CString sql, CRecordset * &RecordSet, int &RecordCount);
	BOOL SelectSQLEx(CString strTable, CStringArray& arryFields, CString strWhere, CRecordset * &RecordSet, int &RecordCount);
	BOOL SelectSQLEx(CString strTable,CStringArray& arryExpres, CStringArray& arryFields, CString strWhere, CRecordset * &RecordSet, int &RecordCount);
	BOOL Data2Xml(CString strTable, CStringArray &arryFileds, CString strWhere, CString & strXml, BOOL bIncludeHead = TRUE);
	BOOL Data2Map(CString strTable, CString KeyField, CString ValueField, CString strWhere, CMap<int,int,CString,CString> & map);
	BOOL Data2Map(CString strTable, CString KeyField, CString ValueField, CString strWhere, CMap<LPSTR,LPSTR,CString,CString> & map);
	BOOL Data2Combox(HWND Hdlg, int nComBoxID,CString strTableName, CString strTitleFiled, CString strValueField, CString strWhere, CStringArray &arrayValues);
	BOOL Data2Combox(CComboBox &Combox,CString strTableName, CString strTitleFiled, CString strValueField, CString strWhere, CStringArray &arrayValues);
	BOOL Data2List(CListBox &List,CString strTableName, CString strDescriptionField, CString strOutField, CString strWhere, CStringList & OutValueList);
	BOOL Data2List(CListBox &List,CString strTableName, CString strDescriptionField, CString strOutField, CString strWhere, CStringArray & OutValueArray);
	BOOL Data2ListCtrl(CListCtrl &ListCtrl,CString strTableName, CStringArray &arrayFields, CString strWhere, CStringList & OutValueList, int OutIndex);
	BOOL Data2ListCtrl(CListCtrl &ListCtrl,CString strTableName, CStringArray &arrayFields, CString strWhere);
	BOOL Data2ListCtrl(CListCtrl &ListCtrl,CString strTableName, CString strWhere, CStringArray & arrayFieldOut);
	BOOL Data2ListCtrl(HWND Hdlg, int nListCtrlID,CString strTableName, CStringArray &arrayFields, CString strWhere);
	BOOL Data2ListCtrl(CListCtrl &ListCtrl,CString strTableName, CString strWhere, int &count, CStringArray & arrayFieldOut, CString strPrimaryKey = "", int iCountPrePage = 0, int iPage = 0);
	BOOL Data2ListCtrl(CListCtrl &ListCtrl,CString strSql, int &count, int iShowCount = 0);
	BOOL Data2ListCtrl(CListCtrl &ListCtrl, CStringArray& arrayField, CString strTableName, CString strWhere, int &count, CString strPrimaryKey = "", int iCountPrePage = 0, int iPage = 0);
	BOOL CreateLogTable(CString strTableName);
	BOOL GetTablePrimaryKey(CString strTable, CString &strPrimaryKey);
	BOOL CloseDB();
	int GetDBVersion();
	BOOL Attach_DB(CString strDBName, CString strMDF, CString strLDF);

	void Exp_Select()
	{
		CString strValue;
		CDBVariant GetValue;
		int RecordCount = 0;

		CString strSql = "SELECT * FROM table";
		SelectSQL(strSql,RecordCount);

		if(!RecordCount) return;

		m_odbcRecordSet->MoveFirst();
		while(!m_odbcRecordSet->IsEOF())
		{			
			try{
				m_odbcRecordSet->GetFieldValue("fieldname",GetValue);
			}catch(CDBException* e ){			
				m_csErr = "获取值失败：" + e->m_strError;
				Log(m_csErr);
			}
			switch (GetValue.m_dwType)
			{
				case DBVT_NULL:
					strValue = "";
					break;
				case DBVT_BOOL: 
					strValue = Int2Str((int)GetValue.m_boolVal);
					break;
				case DBVT_SHORT:
					strValue = Int2Str((int)GetValue.m_iVal);
					break;
				case DBVT_LONG: 
					strValue = Int2Str((int)GetValue.m_lVal);
					break;
				case DBVT_DOUBLE: 
					strValue = Int2Str((int)GetValue.m_dblVal);
					break;
				case DBVT_DATE:       
					strValue.Format("%04d-%02d-%02d %02d:%02d:%02d",GetValue.m_pdate->year,GetValue.m_pdate->month,GetValue.m_pdate->day,GetValue.m_pdate->hour,GetValue.m_pdate->minute,GetValue.m_pdate->second);
					break;
				case DBVT_STRING:   
					strValue = *(GetValue.m_pstring);
					break;
				case DBVT_ASTRING:    
					strValue = *(CStringA *)GetValue.m_pstringA;
					break;
				case DBVT_WSTRING:
					strValue = *(CStringW *)GetValue.m_pstringW;
					break;
				case DBVT_UCHAR:
					strValue = Int2Str((int)GetValue.m_chVal);
					break;
			}
			m_odbcRecordSet->MoveNext();
		}		
		CloseRecordset();
	};
	int GetRecordCount(CRecordset * RecordSet = NULL);
	
	BOOL GetRcdsFdValues(CString strTable, CString strField, CString strWhere, CString& strValueList);
	BOOL GetRcdsFdValues(CString strTable, CString strField, CString strWhere, CStringArray& arrayValues);
	BOOL GetRowCount(CString &strRowCount);
	BOOL GetCurrentID(CString &strCID);

	BOOL GetOneRcdFdsValue(CString strTable, CStringArray& arryFields, CString strWhere, CStringArray& arryValue);
	BOOL GetOneRcdFdsValue(CString strTable, CString strFields, CString strWhere, CString& strValue);
	BOOL GetFdsValuesArray(CRecordset * &pRecordset, CStringArray& arryFields, CStringArray& strValueList, BOOL BbyIndex = FALSE);

protected:
	CString m_csSrv, m_csUid, m_csPwd, m_csDateBs;
	CDatabase m_odbcConnection;
	int m_iReTryCount;
	CString m_csErr;
public:
	void SetMyQueryTimeout(DWORD DTimeOut);
	void BeginTrans();
	void Rollback();
	void CommitTrans();
	BOOL Select(CString strSql, CRecordset * &RecordSet);
	void SetSqlLogFile(CString strFileName);
	void SetErrLogFile(CString strFileName);
	BOOL Select_ForXml(CString strTable, CStringArray& arryFields, CString strWhere, CString& strXmlValue);
	BOOL RecordSet2Xml(CRecordset * pRecordSet, int RecordCount, CString &strXml);
	BOOL Select_ForXml(CString strSql, CString& strXmlValue);

public:
	//BOOL Data2Map(void);
};

//class HttpCode
//{
//public:
//	HttpCode(void);
//	~HttpCode(void);
//	
//	void FreeHd();
//	BOOL SetPath(CString Path);
//	BOOL SetServer(CString Server);
//	BOOL SetServer(CString Server, int Port);
//	//BOOL GetHtmlCode(CString path);
//	BOOL GetHtmlCode(CString path, BOOL savebuf = FALSE ,CString Type = "GET");
//
//	CString ShowHtmlCode();
//	void WriteToDoc(bstr_t content,MSHTML::IHTMLDocument2Ptr pDoc);
//	void SetEncoding(int iEncoding, CString csHelp = "CP_UTF8-CP_THREAD_ACP-CP_ACP");
//	BOOL SetCookie(CString csUrl, CString csCookieName, CString csCookieData);
//	CString GetCookie(CString csUrl);
//	BOOL CoInit();
//	void CoUninit();
//	char * m_lpszBuf;
//	int m_isizeofbuf;
//
//protected:
//	HINTERNET  m_hHSession;
//	HINTERNET  m_hHConnect;
//	MSHTML::IHTMLDocument2Ptr pDoc2,pDoc2Tp; 
//	MSHTML::IHTMLDocument3Ptr pDoc3,pDoc3Tp; 
//	MSHTML::IHTMLElementCollectionPtr pCollection; 
//	MSHTML::IHTMLElementCollectionPtr pCollectionTemp; 
//	MSHTML::IHTMLElementPtr pElement;
//
//	CString m_csPath;
//	CString m_csServer;
//	CString m_csContent;
//	int m_iReadFileSize;
//	int m_iBufSize;
//	int m_iReTryCount;
//	int m_iEncoding;
//	BOOL m_bIsShow;
//	CString m_csErr;
//};

class MySocket
{
protected:

	typedef struct TcpThrd{
		MySocket * pMySocket;
		HANDLE hThread;
		sockaddr_in Address;
		SOCKET ClientSocket;
		BOOL operator==(const TcpThrd &TcpThreadInfo) const  
		{  
			return (ClientSocket == TcpThreadInfo.ClientSocket && hThread == TcpThreadInfo.hThread);   
		};
		void operator=(const TcpThrd &TcpThreadInfo)  
		{  
			pMySocket = TcpThreadInfo.pMySocket;
			Address = TcpThreadInfo.Address;
			ClientSocket = TcpThreadInfo.ClientSocket;
			hThread = TcpThreadInfo.hThread;
		};
	}TcpThread,* pTcpThread;

	WSADATA m_wdData;
	WORD m_wdVersionRequested;
	
	CWinThread * m_pSocketSrvThread;
	CWinThread * m_pSocketWorkThread;
	CMutex m_SrvMutex;
	CMutex m_WorkMutex;
	CMutex m_TcpThreadMutex;

	SOCKET m_sServer;
	//SOCKET m_sClient;

	SOCKET m_sClient;

	
	//sockaddr_in m_adClient;

	int m_iServerLen;
	//int m_iClientLen;

	int m_iPort;
	int m_iSocketTyp;

	CList<SocketInfo, SocketInfo&> m_sClientList;
	CList<TcpThread, TcpThread&> m_sTcpThreadList;
	
	void Close_Socket(SOCKET Close_Socket);
public:
	AFX_THREADPROC m_SocketWorkThread;

	MySocket();
	~MySocket();

	BOOL InitSocketSrv(int iPort, int iSocketType, AFX_THREADPROC SocketSrvThread, MySocket * pSocket);
	BOOL InitSocketClient(CString csSrvIp, int iPort, int iSocketType, AFX_THREADPROC SocketWorkThread, MySocket * pSocket);
	BOOL CloseSocket();
	BOOL CheckStop();
	BOOL CheckSrvThread();
	BOOL CheckWorkThread();
	BOOL CheckTcpThread();
	//void CheckTcpThreadList();
	void FreeWorkThread();
	BOOL GetMessageInfo(SocketInfo& TaskInfo);
	BOOL SendMsg2Client(char * pMsg, sockaddr_in adClient,  SOCKET ClientSocket = NULL, int msgsize = 0);
	BOOL SendMsg2Srv(char * pMsg, int msgsize = 0);
	HANDLE m_StopHevent;
	sockaddr_in m_adServer;

	static UINT SocketSrvThread_Udp(LPVOID pSocket);
	static UINT SocketSrvThread_Tcp(LPVOID pSocket);
	static UINT SingleClientThread(LPVOID pSocket);
	static UINT SocketClientThread(LPVOID pSocket);
};

class MySocketEx
{
public:
	MySocketEx(void);
	~MySocketEx(void);
	typedef struct  
	{
		SOCKET cliSocket;
		//SOCKADDR_IN addrFrom;
		WSABUF wsabuf;
		BOOL bContinueRd;
		int iRdBufSize;
	} ClientSocket, * pClientSocket;

private:
	CCriticalSection g_cs;
	int m_iClientCount;
	SOCKET m_Socket;
	SOCKADDR_IN m_addrSocket;
	int m_iType;
	HWND m_hClientWnd;
	int m_bSrvOrCli;
	CArray<ClientSocket,ClientSocket> m_arrayCliSocket;
	BOOL AddCliSocket2Array(SOCKET cliSocket);
	BOOL DetCliSocket(SOCKET cliSocket);
	CString _RecvMsg(SOCKET cliSocket, SOCKADDR_IN &addrFrom, WSABUF &wsabuf);
	BOOL _RecvMsgEx(SOCKET cliSocket, pClientSocket & pCliSocket);

public:
	BOOL InitSocketSrv(int iPort, int iType, HWND hWnd, u_int iMsg = UM_SOCK, CString strHelp = "iType: 0-TCP, 1-UDP");
	//BOOL InitSocketSrv(int iPort, int iType, HWND hWnd, const int iMsgAdd, CString strHelp = "iType: 0-TCP, 1-UDP");
	BOOL InitSocketClient(LPSTR pstrIP, int iPort, int iType, HWND hWnd, u_int iMsg = UM_SOCK, CString strHelp = "iType: 0-TCP, 1-UDP");
	BOOL InitSocketClient(DWORD dwIp, int iPort, int iType, HWND hWnd, u_int iMsg = UM_SOCK, CString strHelp = "iType: 0-TCP, 1-UDP");
	BOOL InitSocketClientEx(LPSTR pstrIP, int iPort, int iType, HWND hWnd, const int iMsgAdd);
	BOOL InitSocketClientEx(DWORD dwIp, int iPort, int iType, HWND hWnd, const int iMsgAdd);
	CString OnSocket(WPARAM wParam,LPARAM lParam,SOCKET &cliSocket, SOCKADDR_IN &addrFrom, WSABUF &wsabuf);	
	CString GetIpAddr(SOCKET socket, sockaddr_in * sockAddr);
	BOOL SendSktMessage(WSABUF wsabuf, SOCKET socket, SOCKADDR_IN *addrFrom = NULL);
	BOOL SendTcpMessage(WSABUF wsabuf, SOCKET socket);
	BOOL SendUdpMessage(WSABUF wsabuf, SOCKADDR_IN addrFrom);
	BOOL SendMsgToSrv(WSABUF wsabuf);
	CString OnSocketEx(WPARAM wParam,LPARAM lParam,SOCKET &cliSocket, SOCKADDR_IN &addrFrom, pClientSocket & pCliSocket);
	void CloseSocket();
	int GetClientCount();
};

class AutoUpdate
{
public:
	AutoUpdate();
	~AutoUpdate();
	virtual BOOL CheckVersion();
	virtual BOOL DownLoadUpdate(CString pstrServer, CString pstrUserName, CString pstrPassword, int nPort, CString strFtpFolder, CString strFileName = "", CString strLocalFolder = "", CString ExceptFile = "");
	virtual BOOL RunUpdate(LPSTR strExeName);
	virtual BOOL CloseSingleFile(CString strFileName);
};
class Xml
{
private:
public:
	Xml();
	MSXML::IXMLDOMDocumentPtr m_plDomDocument;
	MSXML::IXMLDOMElementPtr m_pDocRoot;
	CString m_strDocName;
	CString m_strDocContents;
	CString m_strNodeName;
	int m_iShowLogMsg;
	CString m_strLogFileName;

	BOOL Init();
	BOOL Err(HRESULT rt);
	BOOL LoadXmlFile(CString strFilePath);
	BOOL LoadXmlString(LPSTR lpstr);
	void NodeInfo(MSXML::IXMLDOMNodePtr pChild);
	CString GetNodeAttrValue(MSXML::IXMLDOMNodePtr pChild, CString strAttrName);
	void DisplayChildren(HTREEITEM hParent, MSXML::IXMLDOMNodePtr pParent);
	BOOL GetNodeInfo(MSXML::IXMLDOMNodePtr pChild, CString &strNodeName, int &iNodeType, CStringList &strAttrName, CStringList &strAttrValue);
	BOOL GetNodeInfo(MSXML::IXMLDOMNodePtr pChild, CString &strNodeName, int &iNodeType, CStringArray &strAttrName, CStringArray &strAttrValue);
	BOOL FindSingleNode(CString strNodeName, int &iNodeType, CStringList &strAttrName, CStringList &strAttrValue, MSXML::IXMLDOMNodePtr pChild = NULL);
	BOOL FindSingleNode(CString strNodeName, CStringArray &strAttrName, CStringArray &strAttrValue, MSXML::IXMLDOMNodePtr pChild = NULL);
	HTREEITEM DisplayChild(HTREEITEM hParent, MSXML::IXMLDOMNodePtr pChild);
	CString GetSingleNodeContext( CString strNodeName );
	MSXML::IXMLDOMNodePtr SelectSingleNode(CString strNodeName, MSXML::IXMLDOMNodePtr pChild = NULL);
	static CString ConvertXmlChar(CString strXml);
	static CString UnConvertXmlChar(CString strXml);
};
/*help*/

/*#include <string>
#include <vector>
using namespace std;
string MyFormat(string strFormat, vector<string>& Var)
{
	string::size_type idx = strFormat.find("%s");
	if (idx == string::npos)
    {
        return strFormat;
    }
    int i=0;
	while (idx != std::string::npos)
    {
        strFormat.replace(idx, 2, Var.at(i++));
        idx = strFormat.find("%s");
    }
    return strFormat;
}*/


class CServiceModule : public CComModule
{
public:
	void Init(_ATL_OBJMAP_ENTRY* p, HINSTANCE h, LPTSTR szServiceName, const GUID* plibid = NULL);
    void Start();
	void ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
    void Handler(DWORD dwOpcode);
	virtual void Run(){}
    BOOL IsInstalled();
	BOOL Install(CString strIniPath);
	BOOL Install();
    BOOL Uninstall();
	LONG Unlock();
	void LogEvent(LPCTSTR pszFormat, ...);
    void SetServiceStatus(DWORD dwState);
    //void SetupAsLocalServer();
	void StartMyService();

//Implementation
private:
	static void WINAPI _ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
    static void WINAPI _Handler(DWORD dwOpcode);

// data members
public:
    CString m_szServiceName;
    SERVICE_STATUS_HANDLE m_hServiceStatus;
    SERVICE_STATUS m_status;
	DWORD dwThreadID;
	BOOL m_bService;
};

extern CServiceModule _Module;

class HttpCode
{
public:
	HttpCode(void);
	~HttpCode(void);
	
	void FreeHd();
	BOOL SetPath(CString Path);
	BOOL SetServer(CString Server);
	BOOL SetServer(CString Server, int Port);
	BOOL GetHtmlCode(CString path, BOOL savebuf = FALSE ,CString Type = "GET");
	CString ShowHtmlCode();
	void WriteToDoc(bstr_t content,MSHTML::IHTMLDocument2Ptr pDoc);
	static HRESULT GetIframeDocument2Ptr(MSHTML::IHTMLElementPtr pElement, MSHTML::IHTMLDocument2Ptr &pDoc2, CComPtr<IDispatch> &disp);
	void SetEncoding(int iEncoding, CString csHelp = "CP_UTF8-CP_THREAD_ACP-CP_ACP");
	BOOL SetCookie(CString csUrl, CString csCookieName, CString csCookieData);
	CString GetCookie(CString csUrl);
	BOOL CoInit();
	void CoUninit();
	BOOL DownLoadFile(CString webPath, CString ToPath);
	char * m_lpszBuf;
	int m_isizeofbuf;
	void SetShowLogIf(BOOL bShow);

protected:
	HINTERNET  m_hHSession;
	HINTERNET  m_hHConnect;
	MSHTML::IHTMLDocument2Ptr pDoc2,pDoc2Tp; 
	MSHTML::IHTMLDocument3Ptr pDoc3,pDoc3Tp; 
	MSHTML::IHTMLElementCollectionPtr pCollection; 
	MSHTML::IHTMLElementCollectionPtr pCollectionTemp; 
	MSHTML::IHTMLElementPtr pElement;

	CString m_csPath;
	CString m_csServer;
	CString m_csContent;
	int m_iReadFileSize;
	int m_iBufSize;
	int m_iReTryCount;
	int m_iEncoding;
	BOOL m_bIsShow;
	CString m_csErr;
};

class CEcFile
{
public:
	//文件加密
	BOOL static EcFile(LPCTSTR fpath);
	//文件解密
	BOOL static DcFile(LPCTSTR fpath);
private:
	__int64 static epass();
};

class MyDB : public MyAdo
{
public:
	CString GetLastErr();
};

class CExcel
{
public:
	static CString GetExcelDriver(CString strFiter);
	static BOOL GetExcelFields(CString strDriver, CString strFile, CStringArray &arrayFields, CString strTable = "sheet1");
	static int GetExcelDataCount(CString strDriver, CString strFile, CString strTable = "sheet1");
};

class CLoadJpg
{
	public:
		CLoadJpg(void);
		~CLoadJpg();
		Gdiplus::GdiplusStartupInput m_gdiplusStartupInput;
		ULONG_PTR m_gdiplusToken;
		Gdiplus::Image* m_pImage;
		Gdiplus::Graphics * m_graphics;

	public:
		BOOL LoadJpgFile(CString strFilePath);
		Gdiplus::Image* LoadJpgFileEx(CString strFilePath);
		void LoadHDC(HDC hdc);
		void ReleaseHDC(HDC hdc);
		void ReleaseHDC(Gdiplus::Graphics &graphics, HDC hdc);

		BOOL DrawImage( int x,int y,int width,int height);
		BOOL DrawImage( HDC hdc, int x,int y,int width,int height);

		BOOL DrawImage( Gdiplus::Image* pImage, int x,int y,int width,int height);
		BOOL DrawImage( HDC hdc, Gdiplus::Image* pImage, int x,int y,int width,int height);

		BOOL DrawImage( CRect rect );
		BOOL DrawImage( HDC hdc, CRect rect);

		BOOL DrawImage( Gdiplus::Image* pImage, CRect rect );
		BOOL DrawImage( HDC hdc, Gdiplus::Image* pImage, CRect rect );
};