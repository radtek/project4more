#include "StdAfx.h"
#include "MyLib.h"

CServiceModule _Module;
void WatchArray(CStringArray &arrayShow)
{
#ifndef _DEBUG
	return;
#endif
	CString str;
	for (int i=0; i<arrayShow.GetCount(); i++)
	{
		str += Int2Str(i) + " -> " + arrayShow[i] + "\r\n";
	}
	MsgBox(str);
}

int CompareStrRight(CString strSrc, CString strDest)
{
	return strSrc.Right((int)strlen(strDest)).CompareNoCase(strDest);
}
CString GetExeFilePath()
{
	CString strFile;
	GetModuleFileName(AfxGetInstanceHandle(),strFile.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	strFile.ReleaseBuffer();
	CString strFilePath = strFile;
	return PraseFilePath(strFilePath,0) + PraseFilePath(strFilePath,1);
}

void InitExceptionCatch()
{
	SetUnhandledExceptionFilter(CleanToolExceptionFun);
	DisableSetUnhandledExceptionFilter();
}

void DisableSetUnhandledExceptionFilter()
{
	void *addr = (void*)GetProcAddress(LoadLibrary(_T("kernel32.dll")),"SetUnhandledExceptionFilter");
	if (addr) 
	{
		unsigned char code[16];
		int size = 0;
		code[size++] = 0x33;
		code[size++] = 0xC0;
		code[size++] = 0xC2;
		code[size++] = 0x04;
		code[size++] = 0x00;
		DWORD dwOldFlag, dwTempFlag;
		VirtualProtect(addr, size, PAGE_READWRITE, &dwOldFlag);
		WriteProcessMemory(GetCurrentProcess(), addr, code, size, NULL);
		VirtualProtect(addr, size, dwOldFlag, &dwTempFlag);
	}
}

LONG WINAPI CleanToolExceptionFun(struct _EXCEPTION_POINTERS* ExceptionInfo)
{
	return Excep_Filter(ExceptionInfo);
}

void Dump_CallStack( CONTEXT *context )
{
	STACKFRAME sf;
	memset( &sf, 0, sizeof( STACKFRAME ) );

	sf.AddrPC.Offset = context->Eip;
	sf.AddrPC.Mode = AddrModeFlat;
	sf.AddrStack.Offset = context->Esp;
	sf.AddrStack.Mode = AddrModeFlat;
	sf.AddrFrame.Offset = context->Ebp;
	sf.AddrFrame.Mode = AddrModeFlat;

	DWORD machineType = IMAGE_FILE_MACHINE_I386;

	HANDLE hProcess = GetCurrentProcess();
	HANDLE hThread = GetCurrentThread();

	for( ; ; )
	{
		CString str;
		if( !StackWalk(machineType, hProcess, hThread, &sf, context, 0, SymFunctionTableAccess, SymGetModuleBase, 0 ) )
			break;

		if( sf.AddrFrame.Offset == 0 )
			break;
		BYTE symbolBuffer[ sizeof( SYMBOL_INFO ) + 1024 ];
		PSYMBOL_INFO pSymbol = ( PSYMBOL_INFO ) symbolBuffer;

		pSymbol->SizeOfStruct = sizeof( symbolBuffer );
		pSymbol->MaxNameLen = 1024;			

		IMAGEHLP_LINE lineInfo = { sizeof(IMAGEHLP_LINE) };
		DWORD dwLineDisplacement;

		if( SymGetLineFromAddr( hProcess, sf.AddrPC.Offset, &dwLineDisplacement, &lineInfo ) )
		{
			if( SymFromAddr( hProcess, sf.AddrPC.Offset, 0, pSymbol ) )
			{			
				str += " func: ";
				str += pSymbol->Name;
			}
			str += " line: " + Int2Str(lineInfo.LineNumber);
			str += "\r\nfile: ";
			str += lineInfo.FileName;
			WriteLog(str,"CallStack");
		}
	}
}

DWORD Excep_Filter( LPEXCEPTION_POINTERS lpEP )
{
	/**//// init dbghelp.dll
	if(!SymInitialize( GetCurrentProcess(), NULL, TRUE ))
	{
		WriteLog("Init dbghelp err.\n","CallStack");
		return 0;
	}
	Dump_CallStack( lpEP->ContextRecord );
	if(!SymCleanup(GetCurrentProcess()))
	{
		WriteLog("Cleanup dbghelp err.\n","CallStack");
	}
	MsgBox("系统异常退出,请重新安装客户端！");
	return EXCEPTION_EXECUTE_HANDLER;
}

/*----------------------------local-value----------------------------------*/
//int m_iReTryCount;
//
//BOOL m_bIsShow;
//CString m_csErr;
//
//CCriticalSection m_Cs;
//CEvent m_Evt;
//CMutex m_Mutex;

BOOL ShutdownComputer()   
{   
	HANDLE hToken;   
	TOKEN_PRIVILEGES tkp;   
	if ( ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, 0) )   
		  return TRUE; 

	// Get a token for this process.           
	if (!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))   
		  return FALSE; 

	// Get the LUID for the shutdown privilege.   
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,&tkp.Privileges[0].Luid);   

	tkp.PrivilegeCount = 1;   // one privilege to set     
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;   

	// Get the shutdown privilege for this process.   
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,(PTOKEN_PRIVILEGES)NULL, 0);   

	// Cannot test the return value of AdjustTokenPrivileges.   
	if (GetLastError() != ERROR_SUCCESS)   
		  return FALSE; 

	// Shut down the system and force all applications to close.   
	if (!ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, 0))   
		  return FALSE; 

	return TRUE; 
}   

/*---------------------usefull-function----------------------------*/
/*url*/
CString urlEncode(const TCHAR* szEncode)
{
	CString strEncoded;
	static const TCHAR szUnsafe[] = {_T("\"<>%\\^[]`+$,@:;/!#?=&")};
	static const TCHAR szHexChr[] = {_T("0123456789ABCDEF")};
	int nLength = lstrlen(szEncode);
	for(int i = 0; i < nLength; i++)
	{
		TCHAR ch = szEncode[i];
		if((NULL == _tcschr(szUnsafe, ch)) && ((int)ch > 32) && ((int)ch < 123))
			strEncoded += ch;
		else
		{
			strEncoded += _T("%");
			strEncoded += szHexChr[(int)((ch >> 4) & 0x0f)];
			strEncoded += szHexChr[(int)(ch & 0x0f)];
		}
	}
	return strEncoded;
}

HINSTANCE GotoURL(LPCTSTR url, int showcmd)
{
    //TCHAR key[MAX_PATH + MAX_PATH];

    // First try ShellExecute()
    HINSTANCE result = ShellExecute(NULL, _T("open"), url, NULL,NULL, showcmd);

    //// If it failed, get the .htm regkey and lookup the program
    //if ((UINT)result <= HINSTANCE_ERROR) {

    //    if (GetRegKey(HKEY_CLASSES_ROOT, _T(".htm"), key) == ERROR_SUCCESS) {
    //        lstrcat(key, _T("\\shell\\open\\command"));

    //        if (GetRegKey(HKEY_CLASSES_ROOT,key,key) == ERROR_SUCCESS) {
    //            TCHAR *pos;
    //            pos = _tcsstr(key, _T("\"%1\""));
    //            if (pos == NULL) {                     // No quotes found
    //                pos = strstr(key, _T("%1"));       // Check for %1, without quotes 
    //                if (pos == NULL)                   // No parameter at all...
    //                    pos = key+lstrlen(key)-1;
    //                else
    //                    *pos = '\0';                   // Remove the parameter
    //            }
    //            else
    //                *pos = '\0';                       // Remove the parameter

    //            lstrcat(pos, _T(" "));
    //            lstrcat(pos, url);
    //            result = (HINSTANCE) WinExec(key,showcmd);
    //        }
    //    }
    //}

    return result;
}
/*ctrl*/
int GetListCurSel(CListCtrl& listCtrl)
{
	POSITION pos = listCtrl.GetFirstSelectedItemPosition();   

	if (pos == NULL)   
		return -1;
	else   
		return listCtrl.GetNextSelectedItem(pos);
}

BOOL GetListCheckedValuesByCol(CListCtrl& listCtrl, CString &strValues, int iCol)
{
	BOOL rt = FALSE;
	CStringArray arrayValues;
	strValues = "";
	for (int i=0; i<listCtrl.GetItemCount(); i++)
	{
		if(listCtrl.GetCheck(i)) 
		{
			arrayValues.Add(listCtrl.GetItemText(i,iCol));
			rt = TRUE;
		}
	}
	strValues = Array2String(arrayValues);
	return rt;
}

BOOL GetListSelectedValuesByCol(CListCtrl& listCtrl, CString &strValues, int iCol)
{
	strValues = "";
	for (POSITION pos = listCtrl.GetFirstSelectedItemPosition(); pos;)
	{
		int iItem = listCtrl.GetNextSelectedItem(pos);
		strValues += listCtrl.GetItemText(iItem,iCol) + ",";
	}
	strValues = strValues.Left(strValues.GetLength()-1);
	return strValues.IsEmpty() ? FALSE : TRUE ;
}

int GetListCurSel(HWND hwnd,int nListCtrlID)
{
	CListCtrl listCtrl;
	listCtrl.m_hWnd = GetDlgItem(hwnd,nListCtrlID);
	POSITION pos = listCtrl.GetFirstSelectedItemPosition();   

	if (pos == NULL)   
		return -1;
	else   
		return listCtrl.GetNextSelectedItem(pos);
}
/*scrn*/
int GetEncoderClsid(LPCWSTR format, CLSID* pClsid)
{
	UINT  num = 0;
	UINT  size = 0;
	Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;
	Gdiplus::GetImageEncodersSize(&num, &size);
	if(size == 0) return -1;
	pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL)	return -1;

	Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

	for(UINT j = 0; j < num; ++j)
	{
		if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;
		}
	}
	free(pImageCodecInfo);
	return -1;
}

// 参数
// xs = 图象x轴大小
// ys = 图象y轴大小
// quality = jpeg图象质量
  
VOID SaveCurScreenJpg(LPCWSTR pszFileName, int xs, int ys, int quality)
{
	HWND hwnd = ::GetDesktopWindow();
	HDC hdc = GetWindowDC(NULL);
	int x = GetDeviceCaps(hdc, HORZRES);	
	int y = GetDeviceCaps(hdc, VERTRES);
	HBITMAP hbmp = ::CreateCompatibleBitmap(hdc, x, y), hold;
	HDC hmemdc = ::CreateCompatibleDC(hdc);
	hold = (HBITMAP)::SelectObject(hmemdc, hbmp);
	BitBlt(hmemdc, 0, 0, x, y, hdc, 0, 0, SRCCOPY);
	SelectObject(hmemdc, hold);
	{
		Gdiplus::Bitmap bit(xs, ys), bit2(hbmp, NULL);
		Gdiplus::Graphics g(&bit);
		g.ScaleTransform((float)xs/x, (float)ys/y);
		g.DrawImage(&bit2, 0, 0);
		  
		CLSID encoderClsid;
		Gdiplus::EncoderParameters encoderParameters;
		  
		encoderParameters.Count = 1;
		encoderParameters.Parameter[0].Guid = Gdiplus::EncoderQuality;
		encoderParameters.Parameter[0].Type = Gdiplus::EncoderParameterValueTypeLong;
		encoderParameters.Parameter[0].NumberOfValues = 1;
		encoderParameters.Parameter[0].Value = &quality;
		  
		GetEncoderClsid(L"image/jpeg", &encoderClsid);
		bit.Save(pszFileName, &encoderClsid, &encoderParameters);
	}
	::DeleteObject(hbmp);
	::DeleteObject(hmemdc);
	return;
}
/*msg*/
void MsgBox(CString csMsg)
{
	AfxMessageBox(csMsg);
}

BOOL CheckMsgBox(CString csMsg)
{
	if(AfxMessageBox(csMsg, 1) == 1) return TRUE;
	return FALSE;	
}

void MsgBoxArray(CStringArray &arrayValue)
{
	CString strMsg = "";
	int count = (int) arrayValue.GetCount();
	for(int i=0; i<count; i++)
		strMsg += Int2Str(i) + ": " + arrayValue[i] + "\r\n";
	MsgBox(strMsg);
}

void ClearTodayLog(CString strLogName)
{
	CTime Time = CTime::GetCurrentTime();
	CString strFileName;
	strFileName.Format("_%4d%02d%02d.Log",Time.GetYear(), Time.GetMonth(), Time.GetDay());
	strFileName = SOCKET_LOG_FILE_NAME + strFileName;
	strFileName = ".\\LOG\\" + strFileName;
	::DeleteFile(strFileName);
	strFileName.Format(".\\LOG\\" + strLogName +  "_%4d%02d%02d.Log",Time.GetYear(), Time.GetMonth(), Time.GetDay());
	::DeleteFile(strFileName);
	strFileName.Format(".\\LOG\\package_%4d%02d%02d.Log",Time.GetYear(), Time.GetMonth(), Time.GetDay());
	::DeleteFile(strFileName);
	strFileName.Format(".\\LOG\\SqlLog_%4d%02d%02d.Log",Time.GetYear(), Time.GetMonth(), Time.GetDay());
	::DeleteFile(strFileName);
	strFileName.Format(".\\LOG\\sqlErr_%4d%02d%02d.Log",Time.GetYear(), Time.GetMonth(), Time.GetDay());
	::DeleteFile(strFileName);
}

void WriteLog( CString csMsg, CString csFileName )
{
	USES_CONVERSION;
	CTime Time = CTime::GetCurrentTime();
	CString strTime,strFileName;
	CString strLog = "";

	CreateDirectory("LOG",NULL);
	csFileName = csFileName.IsEmpty() ? "LogFile" : csFileName;
	strTime.Format("[%02d-%02d %02d:%02d:%02d] -> ",Time.GetMonth(), Time.GetDay(),Time.GetHour(), Time.GetMinute(), Time.GetSecond());
	strFileName.Format(".\\LOG\\" + csFileName + "_%4d%02d%02d.Log",Time.GetYear(), Time.GetMonth(), Time.GetDay());
	strLog = strTime + csMsg + "\r\n";
	const char *pFName = T2A(strFileName.GetBuffer(strFileName.GetLength()));
	const char *pstrLog = T2A(strLog.GetBuffer(strLog.GetLength()));

	FILE * fpLogFile = fopen(pFName, "a+");
	fputs(pstrLog, fpLogFile);
	fclose(fpLogFile);
}

void Log(CString csMsg, CString& csErr,BOOL isShow, CString csFileName)
{
	if(!isShow) return;

	USES_CONVERSION;
	CTime Time = CTime::GetCurrentTime();
	CString strTime,strFileName;
	csErr = "";
	CString strLog = "";

	CreateDirectory("LOG",NULL);
	csFileName = csFileName.IsEmpty() ? "LogFile" : csFileName;
	strTime.Format("[%02d-%02d %02d:%02d:%02d] -> ",Time.GetMonth(), Time.GetDay(),Time.GetHour(), Time.GetMinute(), Time.GetSecond());
	strFileName.Format(".\\LOG\\" + csFileName + "_%4d%02d%02d.Log",Time.GetYear(), Time.GetMonth(), Time.GetDay());
	strLog = strTime + csMsg + "\r\n";
	csErr = strLog;
	const char *pFName = T2A(strFileName.GetBuffer(strFileName.GetLength()));
	const char *pstrLog = T2A(strLog.GetBuffer(strLog.GetLength()));

	FILE * fpLogFile = fopen(pFName, "a+");
	fputs(pstrLog, fpLogFile);
	fclose(fpLogFile);

	//if(isShow) MsgBox(strLog);
}

void Log(CString csMsg, BOOL isShow, CString csFileName)
{
	CString csErr = "";
	Log(csMsg, csErr,isShow, csFileName);
}

void Log(CString csMsg, CString csFileName)
{
	CString csErr = "";
	Log(csMsg, csErr, 1, csFileName);
}

void LogPackage(WSABUF wsabuf)
{
	CString strAll,strTemp;
	for(int i=0; i<(int)wsabuf.len; i++)
	{		
		strTemp.Format("%02X ",(BYTE)wsabuf.buf[i]);
		if(!(i%4)) strTemp = "\r\n" + strTemp;
		strAll += strTemp;
	}
	Log(strAll,0,"package");
}

void SetWdsText(CString strText, HWND hwnd){::SetWindowText(hwnd,strText);}
void FrshWindows(HWND hwnd)
{
	if (::GetActiveWindow()==AfxGetMainWnd()->m_hWnd)  
	{
		::FlashWindow(hwnd, FALSE);
	}
	else
	{
		::FlashWindow(hwnd, TRUE);
	}
}
/*string*/
CString ConvertSqlValue(CString strValue, BOOL bWithOutDT)
{
	strValue.Replace("'","‘");
	if (strValue.IsEmpty())
	{
		return "NULL";
	}else if (bWithOutDT)
	{
		return strValue;
	}else
	{
		return "'" + strValue + "'";
	}
}

BOOL IsNumber(CString str)
{
	char   c;   
	for(int i= 0;i<str.GetLength();i++)   
	{   
		c = (char)str.GetAt(i);   
		if(c>='0'&& c<='9'){}   
		else if (c == '.' || (c == '-' && i==0))
		{
		}else
		return FALSE;
	}
	return TRUE;
}

void PutClipboard(CString source,HWND hwnd)
{
	if(OpenClipboard(hwnd))   
	{   
		HGLOBAL   clipbuffer;   
		char   *   buffer;   
		EmptyClipboard();   
		clipbuffer   =   GlobalAlloc(GMEM_DDESHARE,   source.GetLength()+1);   
		buffer   =   (char*)GlobalLock(clipbuffer);   
		USES_CONVERSION;
		strcpy(buffer,T2A(source.GetBuffer()));   
		GlobalUnlock(clipbuffer);   
		SetClipboardData(CF_TEXT,clipbuffer);   
		CloseClipboard();   
	}
}

CString GetClipboard(HWND hwnd)
{
	CString strRt;
	if(OpenClipboard(hwnd))   
	{   
		HGLOBAL hglb; 
		LPTSTR lptstr;
		hglb = (HGLOBAL)GetClipboardData(CF_TEXT); 
		if (hglb != NULL) 
		{
			lptstr = (LPTSTR)GlobalLock(hglb); 
			strRt = lptstr;
			GlobalUnlock(hglb); 
		}
	}
	return strRt;
}

CString TrimA(CString str)
{
	return str.TrimLeft().TrimRight();
}
CString Int2Str0x(int numb)
{
	BYTE * pbyte = new BYTE[4];
	memcpy(pbyte,&numb,4);
	CString str,strTemp;
	strTemp.Format("%02X%02X %02X%02X",pbyte[0],pbyte[1],pbyte[2],pbyte[3]);
	str = "0x" + strTemp;
	return str;
}


CString Int2Str(int numb)
{
	CString str;
	str.Format(_T("%d"),numb);
	return str;
}

CString Int2Str(DWORD numb)
{
	CString str;
	str.Format(_T("%d"),numb);
	return str;
}

CString Numb2Str(double numb)
{
	CString str;
	str.Format(_T("%.2f"),numb);
	return str;
}

CString Float2Str(float numb)
{
	CString str;
	str.Format(_T("%.3f"),numb);
	return str;
}

int Str2Int(CString str)
{
	return _ttoi(str);
}

int Str2Int(LPSTR lpstr)
{
	return atoi(lpstr);
}

long Str2Long(CString str)
{
	return _ttol(str);
}

float Str2Float(CString str)
{
	return (float)atof(str);
}

BOOL FindStr(CStringList& strListDest, CString strF)
{
	POSITION position = 0;
	position = strListDest.Find(strF);
	if(position) return TRUE;
	else return FALSE;
	return TRUE;
}

BOOL FindStr(CStringArray& strArrayDest, CString strF)
{
	int count = 0;
	count = (int)strArrayDest.GetCount();
	for(int i=0; i<count; i++)
		if(!strArrayDest[i].CompareNoCase(strF))
			return TRUE;
	return FALSE;
}

BOOL FindStr(CStringArray& strArrayDest, CString strF, int &Index)
{
	int count = 0;
	Index = -1;
	count = (int)strArrayDest.GetCount();
	for(int i=0; i<count; i++)
		if(!strArrayDest[i].CompareNoCase(strF))
		{
			Index = i;
			return TRUE;
		}
	return FALSE;
}

int FindStrCount(CString Dstr, CString Fstr, CString Fstr2)
{
	int Point = 0, CountFind = 0;
	Point = Dstr.Find(Fstr);
	while(Point != -1) {
		CountFind ++;
		Point = Dstr.Find(Fstr,Point+1);
	}
	if(!Fstr2.IsEmpty())
	{
		Point = Dstr.Find(Fstr2);
		while(Point != -1) {
			CountFind ++;
			Point = Dstr.Find(Fstr,Point+1);
		}
	}
	return CountFind;
}

CString GetValueByKey(CStringArray& strArrayKey, CStringArray& strArrayValue, CString strKey)
{
	int index = -1;
	if(!FindStr(strArrayKey,strKey,index)) return "";
	return strArrayValue[index];
}

void SaveToArry(CArray<CString,CString> &SaveArry, CString ScStr, TCHAR Fstr, int &Count)
{
	CStringArray InfoArr;
	CStringList szList;
	CString TempStr = "";
#ifdef _UNICODE
	TCHAR TempFstr;
#else
	CHAR TempFstr;
#endif
	InfoArr.RemoveAll();

	TempFstr = Fstr;
	int Point = 0;
	Point = ScStr.Find("-");
	

#ifdef _UNICODE
	if(Point == -1) 
		TempFstr = L'、';
#else
	if(Point == -1) 
		TempFstr = (char)'、';
#endif

	while(AfxExtractSubString(TempStr, ScStr, Count++ , TempFstr))   
		szList.AddTail(TempStr);
	Count --;
	SaveArry.SetSize(Count);
	for(int i = 0; i< Count; i++)
	{
		if(!szList.IsEmpty())
			SaveArry[i] = szList.RemoveHead();
	}
	Point = SaveArry[Count - 1].Find("(");
	if(Point != -1) SaveArry[Count - 1] = SaveArry[Count - 1].Left(Point);
}

void Split(CString source, CStringArray& dest, CString division)
{
    int pos = 0;
    int pre_pos = 0;
	dest.RemoveAll();
	if (source.IsEmpty()) return;
	pos = source.Find(division);
	if(pos == -1)
		dest.Add(source);
	else
	{
		dest.Add(source.Left(pos));
		pre_pos = pos;
		pos = source.Find(division, pos+1);
		while( -1 != pos ){
			//dest.Add(source.Mid(pre_pos+1,(pos-pre_pos-1)));
			dest.Add(source.Mid(pre_pos+division.GetLength(),(pos-pre_pos-division.GetLength())));
			pre_pos = pos;
			pos = source.Find(division, pos+division.GetLength());
		}
		//dest.Add(source.Right(source.GetLength() - pre_pos - 1));
		dest.Add(source.Right(source.GetLength() - pre_pos - division.GetLength()));
	}
}

void Split(CString source, CStringList& dest, CString division)
{
    int pos = 0;
    int pre_pos = 0;
	dest.RemoveAll();
	pos = source.Find(division);
	if(pos == -1)
		dest.AddTail(source);
	else
	{
		dest.AddTail(source.Left(pos));
		pre_pos = pos;
		pos = source.Find(division, pos+1);
		while( -1 != pos ){
			dest.AddTail(source.Mid(pre_pos+1,(pos-pre_pos-1)));
			pre_pos = pos;
			pos = source.Find(division, pos+1);
		}
		dest.AddTail(source.Right(source.GetLength() - pre_pos - 1));
	}
}

DWORD StrIP2DWD(CString strIP)
{
	USES_CONVERSION;
	return htonl(inet_addr(T2A(strIP.GetBuffer())));
}

CString Addr2String(SOCKADDR_IN addrFrom)
{
	CString strIP = (CString)inet_ntoa(addrFrom.sin_addr);
	strIP += ":";
	strIP += Int2Str(ntohs(addrFrom.sin_port));
	return strIP;
}
/*file*/
CString ReadFile(CString csFilePath,long &ReadLenth ,int iCharType)
{
	CString temp;
	if(csFilePath.IsEmpty()) return "";
	USES_CONVERSION;
	const char *pFName = T2A(csFilePath.GetBuffer(csFilePath.GetLength()));
	FILE * pfile;
    CHAR szfile[1024*10];
    TCHAR sztfile[1024*10];
	memset(szfile,0x00,1024*10);
	memset(sztfile,0x00,1024*10);
	//errno_t rt = fopen_s(&file, pFName, "a+")
	if(fopen_s(&pfile, pFName, "a+"))
	{
		MsgBox("打开文件出错！");
		fclose(pfile);	
		return "";
	}

	fseek(pfile,0,SEEK_END); 
	ReadLenth = ftell(pfile); //取得文件的大小 
	fseek(pfile,0,SEEK_SET);

	if(iCharType == READ_FILE_TYPE_CHAR)
	{
		fread(szfile,1,ReadLenth,pfile);
		temp = szfile;
	}else
	{
		fread(sztfile,1,ReadLenth,pfile);		
		temp = sztfile;
	}
	fclose(pfile);
	return temp;
}

BOOL ReadFile(CString csFilePath,LPSTR pbuf, long &ReadLenth)
{
	CString temp;
	if(csFilePath.IsEmpty()) return 0;
	USES_CONVERSION;
	const char *pFName = T2A(csFilePath.GetBuffer(csFilePath.GetLength()));
	FILE * pfile;

	if(fopen_s(&pfile, pFName, "a+"))
	{
		MsgBox("打开文件出错！");
		fclose(pfile);	
		return 0;
	}

	fseek(pfile,0,SEEK_END); 
	ReadLenth = ftell(pfile); //取得文件的大小 
	fseek(pfile,0,SEEK_SET);

	fread(pbuf,1,ReadLenth,pfile);

	fclose(pfile);
	return 1;
}

CString ReadFile(CString csFilePath)
{
	CString str = "";
	CFile rfile;
	CFileException exp;
	if(rfile.Open(csFilePath,CFile::modeRead))
	{
		int len = (int)rfile.GetLength();
		char *g_in;
		g_in = new char[len+1];
		ZeroMemory(g_in,len+1);
		rfile.Read(g_in,len);
		rfile.Close();
		str = CString(g_in);
		delete g_in;
	}else
	{
		exp.ReportError(MB_OK);
	}
	return str;
}

BOOL SaveFile(CString csFilePath, CString csMsg)
{
	USES_CONVERSION;
	CFile rfile;
	CFileException exp;
	const char *pstrLog = T2A(csMsg.GetBuffer(csMsg.GetLength()));
	if(rfile.Open(csFilePath,CFile::modeCreate|CFile::modeWrite))
	{
		rfile.Write(pstrLog,(int)strlen(pstrLog));
		rfile.Close();
	}else
	{
		exp.ReportError(MB_OK|MB_ICONERROR);
		return FALSE;
	}
	return True;
}

BOOL SaveFile(const char * msg, int lenth, char * mode, CString csFileName)
{
	USES_CONVERSION;
	//CString strLog = "";
	//strLog = csMsg;
	const char *pFName = T2A(csFileName.GetBuffer(csFileName.GetLength()));
	//const char *pstrLog = T2A(strLog.GetBuffer(strLog.GetLength()));
	try{
		//FILE * fpLogFile = fopen(pFName, mode);
		FILE * fpLogFile;
		fopen_s(&fpLogFile, pFName, mode);
		if(!fpLogFile) 
		{			
			Log("保存文件失败,请检查该文件是否处于打开状态,如果是,请关闭文件再重试!");
			return 0;
		}
		fwrite(msg,1,lenth,fpLogFile);
		fflush(fpLogFile);

		//fputs(msg, fpLogFile);
		fclose(fpLogFile);
	}catch(CFileException * e){
		TCHAR tempstr[256];
		e->GetErrorMessage(tempstr,255);
		CString Err;
		Err = "save file err!";
		Err += tempstr;
		Log(Err);
	}
	return 1;
}

BOOL SaveFile(CString csMsg, char * mode, CString csFileName)
{
	USES_CONVERSION;
	CString strLog = "";
	strLog = csMsg;
	const char *pFName = T2A(csFileName.GetBuffer(csFileName.GetLength()));
	const char *pstrLog = T2A(strLog.GetBuffer(strLog.GetLength()));
	try{
		//FILE * fpLogFile = fopen(pFName, mode);
		FILE * fpLogFile;
		fopen_s(&fpLogFile, pFName, mode);
		if(!fpLogFile) 
		{			
			Log("保存文件失败,请检查该文件是否处于打开状态,如果是,请关闭文件再重试!");
			return 0;
		}
		fputs(pstrLog, fpLogFile);
		fclose(fpLogFile);
	}catch(CFileException * e){
		TCHAR tempstr[256];
		e->GetErrorMessage(tempstr,255);
		CString Err;
		Err = "save file err!";
		Err += tempstr;
		Log(Err);
	}
	return 1;
}


CString ReadIni(CString IniFile, CString AppName, CString KeyName, CString Default)
{
	TCHAR ReadIni[500];
	CString str = "";
	GetPrivateProfileString(AppName,KeyName,Default,ReadIni,500,IniFile);
	str = ReadIni;
	return str;
}

BOOL ReadIniEx(CString IniFile, CString AppName, CString KeyName,CString &value, CString Default)
{
	value = ReadIni(IniFile, AppName, KeyName,Default);
	if(value.IsEmpty())
	{
		Log("没有配置" + AppName + "的" + KeyName + "参数，请检查配置文件：\r\n" + IniFile);
		return FALSE;
	}
	return TRUE;
}

BOOL ReadIniDc(CString IniFile, CString AppName, CString KeyName,CString &value, CString Default)
{
	TCHAR ReadIni[500];
	TCHAR ReadIniDc[500];
	ZeroMemory(ReadIni,500);
	ZeroMemory(ReadIniDc,500);

	CString str = "";
	GetPrivateProfileString(AppName,KeyName,Default,ReadIni,500,IniFile);
	
	int i = 0;
	while (ReadIni[i])
	{
		ReadIniDc[i] = ReadIni[i] + i + 1;
		i++;
	}
	value = ReadIniDc;

	/*if(value.IsEmpty())
	{
		Log("没有配置" + AppName + "的" + KeyName + "参数，请检查配置文件！");
		return FALSE;
	}*/
	return TRUE;
}

BOOL WriteIniEc(CString IniFile, CString AppName, CString KeyName, CString strValue)
{
#ifdef _UNICODE
	USES_CONVERSION;
	TCHAR WriteIni[500];
	TCHAR WriteIniEc[500];
	ZeroMemory(WriteIni,500);
	ZeroMemory(WriteIniEc,500);
	wmemcpy(WriteIni,strValue.GetBuffer(),wcslen((LPSTR)strValue.GetBuffer()));
#else
	CHAR WriteIni[500];
	CHAR WriteIniEc[500];
	ZeroMemory(WriteIni,500);
	ZeroMemory(WriteIniEc,500);
	memcpy(WriteIni,strValue.GetBuffer(),strlen((LPSTR)strValue.GetBuffer()));
#endif
	int i = 0;
	while (WriteIni[i])
	{
		WriteIniEc[i] = WriteIni[i] - i - 1;
		i++;
	}
	CString str;
	str = WriteIniEc;
	return WritePrivateProfileString(AppName,KeyName,str,IniFile);
}

BOOL WriteIni(CString IniFile, CString AppName, CString KeyName, CString strValue)
{
	return WritePrivateProfileString(AppName,KeyName,strValue,IniFile);
}

BOOL SaveBmp(HBITMAP hBitmap, CString FileName)
{
	HDC hDC;											
	int iBits;											//当前分辨率下每象素所占字节数
	WORD wBitCount;										//位图中每象素所占字节数
	DWORD dwPaletteSize=0, dwBmBitsSize=0, dwDIBSize=0, dwWritten=0; 	 //定义调色板大小， 位图中像素字节大小 ，位图文件大小 ， 写入文件字节数 
	BITMAP Bitmap;  									//位图属性结构
	BITMAPFILEHEADER bmfHdr;							//位图文件头结构
	BITMAPINFOHEADER bi;  								//位图信息头结构 
	LPBITMAPINFOHEADER lpbi;  							//指向位图信息头结构
	HANDLE fh, hDib, hPal,hOldPal=NULL; 				//定义文件，分配内存句柄，调色板句柄 
	hDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES); //计算位图文件每个像素所占字节数 
	DeleteDC(hDC); 
	if (iBits <= 1)wBitCount = 1; 
	else if (iBits <= 4) wBitCount = 4; 
	else if (iBits <= 8) wBitCount = 8; 
	else wBitCount = 24; 

	GetObject(hBitmap, sizeof(Bitmap), (LPSTR)&Bitmap);
	bi.biSize= sizeof(BITMAPINFOHEADER);
	bi.biWidth= Bitmap.bmWidth;
	bi.biHeight= Bitmap.bmHeight;
	bi.biPlanes= 1;
	bi.biBitCount= wBitCount;
	bi.biCompression= BI_RGB;
	bi.biSizeImage= 0;
	bi.biXPelsPerMeter= 0;
	bi.biYPelsPerMeter= 0;
	bi.biClrImportant= 0;
	bi.biClrUsed= 0;

	dwBmBitsSize = ((Bitmap.bmWidth * wBitCount + 31) / 32) * 4 * Bitmap.bmHeight;	//为位图内容分配内存 
	hDib = GlobalAlloc(GHND,dwBmBitsSize + dwPaletteSize + 	sizeof(BITMAPINFOHEADER)); 
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib); 
	*lpbi = bi; 

	hPal = GetStockObject(DEFAULT_PALETTE); 	// 处理调色板  
	if (hPal) 
	{
		hDC = ::GetDC(NULL); 
		hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE); 
		RealizePalette(hDC); 
	}

	GetDIBits(hDC, hBitmap, 0, (UINT) Bitmap.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER) +dwPaletteSize,(BITMAPINFO *)lpbi, DIB_RGB_COLORS); // 获取该调色板下新的像素值 

	if (hOldPal) //恢复调色板  
	{ 
		::SelectPalette(hDC, (HPALETTE)hOldPal, TRUE); 
		RealizePalette(hDC); 
		::ReleaseDC(NULL, hDC); 
	} 
	
	DeleteFile(FileName);
	fh = CreateFile(FileName, GENERIC_WRITE,0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL); //创建位图文件 

	if (fh == INVALID_HANDLE_VALUE)  return FALSE; 

	//设置位图文件头 
	bmfHdr.bfType = 0x4D42; // "BM" 
	dwDIBSize = /*sizeof(BITMAPFILEHEADER) +*/ sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;  
	bmfHdr.bfSize = dwDIBSize; 
	bmfHdr.bfReserved1 = 0; 
	bmfHdr.bfReserved2 = 0; 
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
	
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL); // 写入位图文件头 
	WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL); //写入位图文件其余内容 
	
	GlobalUnlock(hDib); //清除  
	GlobalFree(hDib); 
	CloseHandle(fh); 

	return TRUE;
}

BOOL SaveBmp(HBITMAP hBitmap, CString FileName, WSABUF * pwsabuf)
{
	HDC hDC;											
	int iBits;											//当前分辨率下每象素所占字节数
	WORD wBitCount;										//位图中每象素所占字节数
	DWORD dwPaletteSize=0, dwBmBitsSize=0, dwDIBSize=0, dwWritten=0; 	 //定义调色板大小， 位图中像素字节大小 ，位图文件大小 ， 写入文件字节数 
	BITMAP Bitmap;  									//位图属性结构
	BITMAPFILEHEADER bmfHdr;							//位图文件头结构
	BITMAPINFOHEADER bi;  								//位图信息头结构 
	LPBITMAPINFOHEADER lpbi;  							//指向位图信息头结构
	HANDLE hDib, hPal,hOldPal=NULL; 				//定义文件，分配内存句柄，调色板句柄 
	hDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES); //计算位图文件每个像素所占字节数 
	DeleteDC(hDC); 
	if (iBits <= 1)wBitCount = 1; 
	else if (iBits <= 4) wBitCount = 4; 
	else if (iBits <= 8) wBitCount = 8; 
	else wBitCount = 24; 

	GetObject(hBitmap, sizeof(Bitmap), (LPSTR)&Bitmap);
	bi.biSize= sizeof(BITMAPINFOHEADER);
	bi.biWidth= Bitmap.bmWidth;
	bi.biHeight= Bitmap.bmHeight;
	bi.biPlanes= 1;
	bi.biBitCount= wBitCount;
	bi.biCompression= BI_RGB;
	bi.biSizeImage= 0;
	bi.biXPelsPerMeter= 0;
	bi.biYPelsPerMeter= 0;
	bi.biClrImportant= 0;
	bi.biClrUsed= 0;

	dwBmBitsSize = ((Bitmap.bmWidth * wBitCount + 31) / 32) * 4 * Bitmap.bmHeight;	//为位图内容分配内存 
	hDib = GlobalAlloc(GHND,dwBmBitsSize + dwPaletteSize + 	sizeof(BITMAPINFOHEADER)); 
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib); 
	*lpbi = bi; 

	hPal = GetStockObject(DEFAULT_PALETTE); 	// 处理调色板  
	if (hPal) 
	{
		hDC = ::GetDC(NULL); 
		hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE); 
		RealizePalette(hDC); 
	}

	GetDIBits(hDC, hBitmap, 0, (UINT) Bitmap.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER) +dwPaletteSize,(BITMAPINFO *)lpbi, DIB_RGB_COLORS); // 获取该调色板下新的像素值 

	if (hOldPal) //恢复调色板  
	{ 
		::SelectPalette(hDC, (HPALETTE)hOldPal, TRUE); 
		RealizePalette(hDC); 
		::ReleaseDC(NULL, hDC); 
	} 
	
	DeleteFile(FileName);
	//fh = CreateFile(FileName, GENERIC_WRITE,0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL); //创建位图文件 

	//if (fh == INVALID_HANDLE_VALUE)  return FALSE; 

	//设置位图文件头 
	bmfHdr.bfType = 0x4D42; // "BM" 
	dwDIBSize = /*sizeof(BITMAPFILEHEADER) +*/ sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;  
	bmfHdr.bfSize = dwDIBSize; 
	bmfHdr.bfReserved1 = 0; 
	bmfHdr.bfReserved2 = 0; 
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
	
	//WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL); // 写入位图文件头 
	//WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL); //写入位图文件其余内容 

	memcpy(pwsabuf->buf,&bmfHdr,sizeof(BITMAPFILEHEADER));
	memcpy(pwsabuf->buf + sizeof(BITMAPFILEHEADER),lpbi,dwDIBSize);
	pwsabuf->len = dwDIBSize + sizeof(BITMAPFILEHEADER);
	
	GlobalUnlock(hDib); //清除  
	GlobalFree(hDib); 
	//CloseHandle(fh); 

	return TRUE;
}
void CopyScreenToBitmap(CString FileName, int xStartPt, int yStartPt, int width, int height, int xToCopy, int yToCopy)
{
	CBitmap * pBackBitmap = new CBitmap();

	CDC ScrDC,MemDC;

	ScrDC.CreateDC("DISPLAY", NULL, NULL, NULL);
	MemDC.CreateCompatibleDC(&ScrDC);

	pBackBitmap->CreateCompatibleBitmap(&ScrDC,width,height);
	MemDC.SelectObject(pBackBitmap);

	//开始拷贝
	MemDC.BitBlt(xStartPt, yStartPt, width, height,&ScrDC,xToCopy,yToCopy,SRCCOPY);

	ScrDC.DeleteDC();
	MemDC.DeleteDC();

	SaveBmp((HBITMAP)(*pBackBitmap), FileName);

	delete pBackBitmap;
}

void DeleteDir(CString str)
{
	while(str.Right(1) == "\\") 
	{
		str = str.Left(str.GetLength()-1);
	}
	CFileFind finder; //文件查找类
	CString strdel,strdir;//strdir:要删除的目录，strdel：要删除的文件
	strdir= str + "\\*.*";//删除文件夹，先要清空文件夹,加上路径,注意加"\\"
	BOOL b_finded=(BOOL)finder.FindFile(strdir); 
	while(b_finded) 
	{ 
		b_finded=(BOOL)finder.FindNextFile(); 
		if (finder.IsDots())  continue;//找到的是当前目录或上级目录则跳过
			strdel=finder.GetFileName(); //获取找到的文件名
		if(finder.IsDirectory())   //如果是文件夹
		{ 
			strdel=str + "\\" + strdel;//加上路径,注意加"\\"
			DeleteDir(strdel); //递归删除文件夹
		} 
		else //不是文件夹
		{ 
			strdel=str + "\\" + strdel;
			if(finder.IsReadOnly())//清除只读属性
			{    
				SetFileAttributes(strdel,GetFileAttributes(strdel)&(~FILE_ATTRIBUTE_READONLY));
			}
			DeleteFile(strdel); //删除文件(API)
		} 
	} 
	finder.Close(); 
	RemoveDirectory(str); //删除文件夹(API)
}

BOOL GetFtpFileList(CFtpConnection *m_pFtpConnection, CStringArray & arrFilePathList, CString ExceptFile)
{
	CString strFileTempName;
	CFtpFileFind * pFtpFileFind = new CFtpFileFind(m_pFtpConnection);

	BOOL bContinue = pFtpFileFind->FindFile("*");
	while(bContinue) 
	{
		bContinue = pFtpFileFind->FindNextFile();
		strFileTempName = pFtpFileFind->GetFileName();
		if(pFtpFileFind->IsDirectory())
		{
			continue;
			if(!strFileTempName.Compare("..")) continue;
			int rt = m_pFtpConnection->SetCurrentDirectory(strFileTempName);
			GetFtpFileList(m_pFtpConnection,arrFilePathList,ExceptFile);
			rt = m_pFtpConnection->SetCurrentDirectory("..");
		}
		else if(ExceptFile.CompareNoCase(strFileTempName))
		{
			arrFilePathList.Add(strFileTempName);
		}
	}
	
	pFtpFileFind->Close();
	delete pFtpFileFind;
	pFtpFileFind = NULL;

	return TRUE;
}

BOOL DownloadFiles(CString pstrServer, CString pstrUserName, CString pstrPassword, int nPort, CString strFtpFolder, CString strFileName, CString strLocalFolder, CString ExceptFile, CString &csErr)
{
	BOOL bBackDir = FALSE;
	int DownType;	// 1:folder, 0:files
	DownType = strFileName.IsEmpty() ? 1 : 0;

	CInternetSession *m_pInetSession = NULL;
	CFtpConnection *m_pFtpConnection = NULL;
	
	int rt = TRUE;
	if(m_pFtpConnection) 
	{
		m_pFtpConnection->Close();
		delete m_pFtpConnection;
		m_pFtpConnection = NULL;
	}
	if(m_pInetSession)
	{
		m_pInetSession->Close();
		delete m_pInetSession;
		m_pInetSession = NULL;
	}
	m_pInetSession = new CInternetSession(AfxGetAppName(),1,PRE_CONFIG_INTERNET_ACCESS);
	try
	{ 
		m_pFtpConnection=m_pInetSession->GetFtpConnection(pstrServer,pstrUserName,pstrPassword,nPort); 
	} 
	catch(CInternetException *pEx) 
	{
		TCHAR szError[1024]; 
		if(pEx->GetErrorMessage(szError,1024)) 
			AfxMessageBox(szError); 
		else 
			AfxMessageBox("There was an exception"); 

		pEx->Delete();
		//m_pFtpConnection->Close();
		delete m_pFtpConnection;
		m_pFtpConnection=NULL;

		m_pInetSession->Close();
		delete m_pInetSession;
		m_pInetSession = NULL;
		Log("与服务器连接失败，请检查Ftp参数配置是否填写正确。",1);
		return FALSE;
	}	

	if(strFtpFolder.Right(1) != "\\") strFtpFolder += "\\";
	//if(strLocalFolder.Right(1) != "\\") strLocalFolder += "\\";
	try 
	{
		if(!m_pFtpConnection->SetCurrentDirectory(strFtpFolder))
		{
			m_pFtpConnection->Close();
			delete m_pFtpConnection;
			m_pFtpConnection=NULL;

			m_pInetSession->Close();
			delete m_pInetSession;
			m_pInetSession = NULL;
			Log("ftp目录:" + strFtpFolder + "不存在!",1);
			return FALSE;
		}
	}
	catch(CInternetException *pEx) 
	{
		TCHAR szError[1024]; 
		if(pEx->GetErrorMessage(szError,1024)) 
		{
			csErr = szError;
			Log("目录跳转失败:" + csErr,1);
		}
		else 
			Log("create folder file err:There was an exception",1); 

		pEx->Delete(); 
		rt = 0;
	}

	CStringArray arrFileNameList;

	if(DownType)
	{
		GetFtpFileList(m_pFtpConnection,arrFileNameList,ExceptFile);
		if(bBackDir)
		{
			try 
			{
				if(!m_pFtpConnection->SetCurrentDirectory(strFtpFolder))
				{
					m_pFtpConnection->Close();
					delete m_pFtpConnection;
					m_pFtpConnection=NULL;

					m_pInetSession->Close();
					delete m_pInetSession;
					m_pInetSession = NULL;
					Log("ftp目录:" + strFtpFolder + "不存在!",1);
					return FALSE;
				}
			}
			catch(CInternetException *pEx) 
			{
				TCHAR szError[1024]; 
				if(pEx->GetErrorMessage(szError,1024)) 
				{
					csErr = szError;
					Log("目录跳转失败:" + csErr,1);
				}
				else 
					Log("create folder file err:There was an exception",1); 

				pEx->Delete(); 
				rt = 0;
			}
		}
	}else
	{		
		Split(strFileName,arrFileNameList,",");
	}

	INT_PTR iFileArrLenth;
	iFileArrLenth = arrFileNameList.GetCount();

	if(strLocalFolder.IsEmpty()) strLocalFolder = ".\\";
	//DeleteDir(strLocalFolder);
	::CreateDirectory(strLocalFolder, NULL);
	::CreateDirectory(strLocalFolder + "Back\\", NULL);

	CString oldf = "";
	CString newf = "";

	for(int i=0; i<iFileArrLenth; i++)
	{
		try 
		{	
			oldf = strLocalFolder + arrFileNameList[i];
			newf =  strLocalFolder + "Back\\" + arrFileNameList[i];
			CopyFile(oldf,newf,FALSE);
#ifdef _UNICODE
			DeleteFileW(strLocalFolder + arrFileNameList[i]);
#else
			DeleteFile(strLocalFolder + arrFileNameList[i]);
#endif
			if(!m_pFtpConnection->GetFile(arrFileNameList[i], strLocalFolder + arrFileNameList[i]))
			{
				Log("下载文件'" + arrFileNameList[i] + "'失败,请检查本地路径的文件是否处于打开或自读状态！",1);
				rt = FALSE;
			}
		}
		catch(CInternetException *pEx)
		{
			TCHAR szError[1024];
			if(pEx->GetErrorMessage(szError,1024))
			{
				csErr = szError;
				Log("文件下载失败:" + csErr,1);
			}
			else
				Log("download file err:There was an exception",1);

			pEx->Delete();
			rt = FALSE;
		}
	}

	m_pFtpConnection->Close();
	m_pInetSession->Close();	
	delete m_pInetSession;
	delete m_pFtpConnection;
	m_pInetSession = NULL;
	m_pFtpConnection=NULL;
	return rt;
}
BOOL UploadFile(CString pstrServer, CString pstrUserName, CString pstrPassword, int nPort, CString strFilePath, CString &strFileName, CString strFtpFolder, CString &csErr)
{
	strFileName = "";
	if(strFilePath.IsEmpty()) return false;
	CInternetSession *m_pInetSession = NULL; 
	CFtpConnection *m_pFtpConnection = NULL;
	
	int rt = 1;
	if(m_pFtpConnection) 
	{
		m_pFtpConnection->Close();
		delete m_pFtpConnection;
		m_pFtpConnection = NULL;
	}
	if(m_pInetSession)
	{
		m_pInetSession->Close();
		delete m_pInetSession;
		m_pInetSession = NULL;
	}
	m_pInetSession = new CInternetSession(AfxGetAppName(),1,PRE_CONFIG_INTERNET_ACCESS);
	try
	{ 
		m_pFtpConnection=m_pInetSession->GetFtpConnection(pstrServer,pstrUserName,pstrPassword,nPort); 
	} 
	catch(CInternetException *pEx) 
	{
		TCHAR szError[1024]; 
		if(pEx->GetErrorMessage(szError,1024)) 
			AfxMessageBox(szError); 
		else 
			AfxMessageBox("There was an exception"); 

		pEx->Delete();
		delete m_pFtpConnection;
		m_pFtpConnection=NULL;

		m_pInetSession->Close();
		delete m_pInetSession;
		m_pInetSession = NULL;
		Log("文件上传失败，与服务器连接失败，请检查配置文件Ftp参数是否填写正确。");
		return 0;
	}

	
	if(strFtpFolder.Right(1) != "\\") strFtpFolder += "\\";
	try 
	{
		if(!m_pFtpConnection->SetCurrentDirectory(strFtpFolder))
		{
			m_pFtpConnection->CreateDirectory(strFtpFolder);
			m_pFtpConnection->SetCurrentDirectory(strFtpFolder);
		}
	}
	catch(CInternetException *pEx) 
	{
		TCHAR szError[1024]; 
		if(pEx->GetErrorMessage(szError,1024)) 
		{
			csErr = szError;
			Log("创建目录或者目录跳转失败:" + csErr);
		}
		else 
			Log("create folder file err:There was an exception"); 

		pEx->Delete(); 
		rt = 0;
	}

	CFtpFileFind * pFtpFileFind = new CFtpFileFind(m_pFtpConnection);

	CString sUploadFile = "",strFtpFileName = "";
	INT_PTR iFileArrLenth;
	CTime Time;

	CStringArray arrFilePath;
	Split(strFilePath,arrFilePath,",");
	iFileArrLenth = arrFilePath.GetCount();

	for(int i=0; i<iFileArrLenth; i++)
	{
		Time = CTime::GetCurrentTime();
		sUploadFile.Format("UploadFile_%02d%02d%02d%02d%02d%02d", Time.GetYear(), Time.GetMonth(), Time.GetDay(),Time.GetHour(), Time.GetMinute(), Time.GetSecond());
		strFtpFileName = sUploadFile + PraseFilePath(arrFilePath[i],3);

		int k = 0;
		while(pFtpFileFind->FindFile(strFtpFileName))
		{
			k++;
			strFtpFileName = sUploadFile + "(" + Int2Str(k) + ")" + strFilePath.Right(4);
		}

		strFileName += (strFileName.IsEmpty() ? "" : ",");
		strFileName += strFtpFileName;

		try 
		{			
			CString ii = arrFilePath[i];
			if(!m_pFtpConnection->PutFile(arrFilePath[i], strFtpFileName))
			{
				Log("上传文件'" + arrFilePath[i] + "'失败，请确认该文件是否处理被打开状态，如果是，请关闭文件重试。");
				rt = 0;
			}
		}
		catch(CInternetException *pEx) 
		{
			TCHAR szError[1024]; 
			if(pEx->GetErrorMessage(szError,1024)) 
			{
				csErr = szError;
				Log("文件上传失败:" + csErr);
			}
			else 
				Log("upload file err:There was an exception"); 

			pEx->Delete(); 
			rt = 0;
		}
	}

	m_pFtpConnection->Close();
	m_pInetSession->Close();
	pFtpFileFind->Close();
	delete pFtpFileFind;
	delete m_pInetSession;
	delete m_pFtpConnection;
	pFtpFileFind = NULL;
	m_pInetSession = NULL;
	m_pFtpConnection=NULL;

	return rt;
}



CString SelFileG(CString csFilter,CString csInitialDir)
{
	CStringArray arrFilter;
	CString sFileFilter = "";
	CString rtFilePath = ""; 
	Split(csFilter,arrFilter,",");
	for(int i=0; i<arrFilter.GetSize(); i++)
	{
		sFileFilter += arrFilter[i] + "|";
		sFileFilter += arrFilter[i] + "|";
	}
	if(sFileFilter.IsEmpty()) sFileFilter = "*.*|*.*||";
	else sFileFilter += "|";

	CFileDialog fDlg(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT,sFileFilter,NULL);
	fDlg.m_ofn.lpstrInitialDir=csInitialDir;
	INT_PTR dwRet = fDlg.DoModal();
	/*if(fDlg.GetFileExt() != "xls")
	{
		fDlg.DoModal();
	}*/
	if(dwRet==IDOK)   
	{ 
		POSITION pos = fDlg.GetStartPosition();
		 
		while(pos)
		{
			rtFilePath += (rtFilePath.IsEmpty() ? "" : ",");
			rtFilePath += fDlg.GetNextPathName(pos);
		}
	}
	return rtFilePath;
}
CString SelFileT()
{
	//LPSTR szPath = new WCHAR[255];
#ifdef _UNICODE
	WCHAR szPath[255];
#else
	CHAR szPath[255];
#endif

	BROWSEINFO br;
	ITEMIDLIST *pItem;
	br.hwndOwner = NULL; //::GetDlgItem(m_hWnd, IDC_BUTTON_PATH);
	br.iImage = 0;
	br.pszDisplayName = 0;
	br.lParam = 0;
	br.lpfn = 0;
	br.lpszTitle = "请选择保存路径:";
	br.pidlRoot = 0;
	br.ulFlags = BIF_RETURNONLYFSDIRS;
	pItem = SHBrowseForFolder(&br);
	if (SHGetPathFromIDList(pItem,szPath)==TRUE) return szPath;
	return "";
}
CString PraseFilePath(CString csFileFullPath, int GetItem, CString csHelpStr)
{
	USES_CONVERSION;
	char Drive[256];
	char Dir[256];
	char Filename[256];
	char Ext[256];
	CStringArray RT;
	CString csTemp;
	const char *pFName = T2A(csFileFullPath.GetBuffer(csFileFullPath.GetLength()));
	_splitpath_s(pFName,Drive,Dir,Filename,Ext);
	csTemp = Drive;	RT.Add(csTemp);	csTemp = Dir; RT.Add(csTemp);
	csTemp = Filename;	RT.Add(csTemp);	csTemp = Ext; RT.Add(csTemp);
	return RT[GetItem];
}
/*time*/
CString GetCurtTimeEx(int exlenth)
{
	CString rt;
	rt = GetCurrentTimeString(0);
	LARGE_INTEGER liPerfNow;
	QueryPerformanceCounter(&liPerfNow);
	return rt + Int2Str((DWORD)liPerfNow.QuadPart).Right(exlenth);
	//return rt;
}

CString GetCurtTime()
{
	CTime Time = CTime::GetCurrentTime();
	CString strTime;
	strTime.Format("%04d-%02d-%02d %02d:%02d:%02d",Time.GetYear(),Time.GetMonth(), Time.GetDay(),Time.GetHour(), Time.GetMinute(), Time.GetSecond());
	return strTime;
}

SYSTEMTIME String2CTime( CString strT ) 
{
	COleDateTime tm;   
	tm.ParseDateTime(strT);   
	SYSTEMTIME st;   
	tm.GetAsSystemTime(st);
	return st;
}

CString GetCurrentTimeString(int iType, long iDateDiff, CString strHelp)
{
	CTime time = CTime::GetCurrentTime();
	CString str_Time;
	if (iDateDiff)
	{
		CTimeSpan span( iDateDiff, 0, 0, 0);
		time += span;
	}
	switch (iType)
	{
	case 0:
		str_Time = time.Format("%Y%m%d%H%M%S");
		break;
	case 1:
		str_Time = time.Format("%H%M%S");
		break;
	case 2:
		str_Time = time.Format("%Y%m%d");
		break;
	case 3:
		str_Time = time.Format("%Y-%m-%d %H:%M:%S");
		break;
	case 4:
		str_Time = time.Format("%H:%M:%S");
		break;
	case 5:
		str_Time = time.Format("%Y-%m-%d");
		break;
	}
	return str_Time;
}
/*IP*/
BOOL GetHostIP(CString& IPAddress)
{
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2,2);
	IPAddress = "";
	if(WSAStartup(wVersionRequested,&wsaData))
	{
		Log("WSAStartup Err: " + Int2Str(GetLastError()), SOCKET_LOG_FILE_NAME);
		return FALSE;
	}
	if(LOBYTE(wsaData.wVersion)!= 2 || HIBYTE(wsaData.wVersion)!= 2)
	{
		Log("WSA Version Err: " + Int2Str(GetLastError()), SOCKET_LOG_FILE_NAME);
		return FALSE;
	}
	char szHostName[128];		//将本机的名称存入一维数组,数组名称为szHostName
	struct hostent * pHost;		//定义结构体 hostent
	//int i;					
	if(gethostname(szHostName,128)==0)    //如果查到就将其送入ListBox控件，这样就可以实现多网卡的支持（本文所提供的源码中存在部分疏漏，即只获取到了最后一个IP地址，读者按照我写的代码将其稍加改动即可。）
	{
		//m_hostname=szHostName;
		pHost = gethostbyname(szHostName);
		if(pHost->h_addr_list[0]==NULL) return FALSE;
		//for(i=0;pHost!=NULL&&pHost->h_addr_list[i]!=NULL;i++) 
		//{
		  IPAddress = inet_ntoa(*(struct in_addr *)pHost->h_addr_list[0]);
		//}
	}
	else
	{ 
		MsgBox("IP地址获取错误!");
	}
	WSACleanup();
	return TRUE;
}

BOOL GetHostIpHead(CString& IPAddressHand)
{
	IPAddressHand = "";

	CString strIp = "";
	CStringArray strArray;

	GetHostIP(strIp);
	if(strIp.IsEmpty()) return 0;
	Split(strIp,strArray,".");
	IPAddressHand = strArray[0] + "." + IPAddressHand[1] + "." + IPAddressHand[2];
	return 1;
}

BOOL ReplaceWD(CString& strSoce, CString strDivision)
{
	CStringArray strArray;
	Split(strSoce,strArray,".");
	if(Str2Int(strArray[2]) == Str2Int(strDivision))
		return 0;
	else
	{
		strArray[2] = strDivision;
		strSoce = strArray[0];
		int len = (int)strArray.GetSize();
		for(int i=1; i<len; i++)
			strSoce += "." + strArray[i];
	}
	return 1;
}
/*others*/
BOOL RunExe(LPSTR strFileFullName)
{
	STARTUPINFO si;
    ZeroMemory(&si,sizeof(si));
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi,sizeof(pi));
    return CreateProcess(strFileFullName,NULL,NULL,NULL,FALSE,NULL,NULL,NULL,&si,&pi);
}
BOOL CheckInstance(LPCSTR InstanceName)
{
	HANDLE hInstance;
	hInstance = CreateEvent(NULL,TRUE,false,InstanceName);
	if(hInstance)
	{
		if(ERROR_ALREADY_ASSIGNED == GetLastError())
			return FALSE;
	}
	CloseHandle(hInstance);
	return TRUE;
}
int RandomInt(int iMin, int iMax)   
{
	//static int iInitSeed;
	if(iMin >= iMax) return iMin;
	//if(iInitSeed != 1)
	//{
		srand((UINT)time(NULL));
		//iInitSeed = 1;
	//}
	return iMin + rand()%(iMax - iMin + 1);
}

BOOL TimeAdd( CString &strTime, LONG lDays, int nHours, int nMins, int nSecs )
{
	COleDateTime time;
	time.ParseDateTime(strTime.Left(19));
	COleDateTimeSpan ds;
	ds.SetDateTimeSpan(lDays, nHours, nMins, nSecs);   
	time += ds;
	strTime = time.Format("%Y-%m-%d %H:%M:%S");
	return 0;
}

CString TimeDiff(CString strTimeStart, CString strTimeEnd)
{
	COleDateTime time1,time2;
	COleDateTimeSpan ds;

	time1.ParseDateTime(strTimeStart.Left(19));
	time2.ParseDateTime(strTimeEnd.Left(19));
	ds = time2 - time1;
	return ds.Format("%D天%H小时%M分钟%S秒");
}

void ShowOneWindow(CString strTitle)
{
	HWND hProgramWnd = ::FindWindow(NULL,strTitle);
	if (hProgramWnd)
	{
		WINDOWPLACEMENT* pWndpl = NULL;
		WINDOWPLACEMENT   wpm; 
		pWndpl =&wpm;
		GetWindowPlacement(hProgramWnd,&wpm);
		if (pWndpl)
		{
			pWndpl->showCmd = SW_SHOWNORMAL;
			::SetWindowPlacement(hProgramWnd,pWndpl);
			::SetForegroundWindow(hProgramWnd);
		}
	}
}

CString Array2String( CStringArray &arrayDest, CString division )
{
	CString str = "";
	for (int i=0; i<arrayDest.GetCount(); i++)
	{
		str += arrayDest[i] + division;
	}
	str = str.Left(str.GetLength()-division.GetLength());
	return str;
}

CString Array2StringCvtSql( CStringArray &arrayDest, CString division, BOOL bWithOutDT )
{
	CString str = "";
	for (int i=0; i<arrayDest.GetCount(); i++)
	{
		str += ConvertSqlValue(arrayDest[i],bWithOutDT) + division;
	}
	str = str.Left(str.GetLength()-division.GetLength());
	return str;
}

BOOL GetTimeArea( CTime &strStart, CTime &strEnd, CString strType )
{
	CTime tempTime,time = CTime::GetCurrentTime();

	if (!strType.CompareNoCase("day"))
	{
		strStart = strEnd = time;
	}else if (!strType.CompareNoCase("week"))
	{
		CTimeSpan span(time.GetDayOfWeek()-2,0,0,0);
		CTimeSpan span1(8 - time.GetDayOfWeek(),0,0,0);

		tempTime = time;
		tempTime -= span;
		strStart = tempTime;

		tempTime = time;
		tempTime += span1;
		strEnd = tempTime;
	}else if (!strType.CompareNoCase("month"))
	{
		CTimeSpan span( 1, 0, 0, 0);

		tempTime = CTime(time.GetYear(),time.GetMonth(),1,0,0,0);
		strStart = tempTime;

		if(time.GetMonth() == 12)
		{
			tempTime = CTime(time.GetYear()+1,1,1,0,0,0);
		}else
			tempTime = CTime(time.GetYear(),(time.GetMonth()+1),1,0,0,0);
		tempTime -= span;
		strEnd = tempTime;

	}else if (!strType.CompareNoCase("year"))
	{
		tempTime = CTime(time.GetYear(),1,1,0,0,0);
		strStart = tempTime;

		tempTime = CTime(time.GetYear(),12,31,0,0,0);
		strEnd = tempTime;
	}else return FALSE;
	return TRUE;
}
BOOL GetTimeArea( CString &strStart, CString &strEnd, CString strType )
{
	CTime tempTime,time = CTime::GetCurrentTime();
	CString str_Time;
	str_Time = time.Format("%Y-%m-%d");

	if (!strType.CompareNoCase("day"))
	{
		strStart = strEnd = str_Time;
	}else if (!strType.CompareNoCase("week"))
	{
		CTimeSpan span(time.GetDayOfWeek()-2,0,0,0);
		CTimeSpan span1(8 - time.GetDayOfWeek()-1,0,0,0);

		tempTime = time;
		tempTime -= span;
		strStart = time.Format("%Y-%m-%d");

		tempTime = time;
		tempTime += span1;
		strEnd = time.Format("%Y-%m-%d");
	}else if (!strType.CompareNoCase("month"))
	{
		CTimeSpan span( 1, 0, 0, 0);

		tempTime = CTime(time.GetYear(),time.GetMonth(),1,0,0,0);
		strStart = tempTime.Format("%Y-%m-%d");

		tempTime = CTime(time.GetYear(),time.GetMonth() == 12 ? 1 : (time.GetMonth()+1),1,0,0,0);
		tempTime -= span;
		strEnd = tempTime.Format("%Y-%m-%d");

	}else if (!strType.CompareNoCase("year"))
	{
		tempTime = CTime(time.GetYear(),1,1,0,0,0);
		strStart = tempTime.Format("%Y-%m-%d");
		
		tempTime = CTime(time.GetYear(),12,31,0,0,0);
		strEnd = tempTime.Format("%Y-%m-%d");
	}else return FALSE;
	return TRUE;
}

//void CArray2TreeCtrl( CArray<CStringArray,CStringArray> *arrayBranchInfo, CTreeCtrl &tree )
//{
//	CMap<int, int,HTREEITEM,HTREEITEM> map;
//	CString temp;
//	HTREEITEM tempHItem,parentHItem; 
//
//	for(int i=0; i<arrayBranchInfo->GetCount(); i++)
//	{
//		tempHItem = NULL;
//		parentHItem = NULL;
//		if((*arrayBranchInfo)[i][0].IsEmpty())
//		{
//			tempHItem = tree.InsertItem((*arrayBranchInfo)[i][1],0,1);
//		}else
//		{
//			if(!map.Lookup(Str2Int((*arrayBranchInfo)[i][0]),parentHItem))
//			{
//				continue;
//			}
//			tempHItem = tree.InsertItem((*arrayBranchInfo)[i][1],0,1,parentHItem);
//			tree.Expand(parentHItem, TVE_EXPAND);
//		}		
//		map[Str2Int((*arrayBranchInfo)[i][2])] = tempHItem;
//	}
//}
/*---------------------MyAdo------------------------*/
MyAdo::MyAdo()
{
	m_odbcRecordSet = NULL;
	m_strSqlLogFile = "SqlLog";
	m_strErrLogFile = "sqlErr";

	m_bIsShow = TRUE;

#ifdef _DEBUG
	m_bIsShow = True;
#endif

}

MyAdo::~MyAdo()
{
	if(m_odbcRecordSet)
	{
		m_odbcRecordSet->Close();
		delete m_odbcRecordSet;
		m_odbcRecordSet = NULL;
	}
	CloseDB();
}

void MyAdo::SetSqlLogFile(CString strFileName)
{
	if(strFileName.IsEmpty()) return;
	m_strSqlLogFile = strFileName;
}

void MyAdo::SetErrLogFile(CString strFileName)
{
	if(strFileName.IsEmpty()) return;
	m_strErrLogFile = strFileName;
}

int MyAdo::GetRecordCount(CRecordset * RecordSet)
{
	int RecordCount = 0;
	if(RecordSet) 
	{
		if(RecordSet->IsEOF() && RecordSet->IsBOF())
		{
			//AfxMessageBox("没有相关记录！");
			//CloseRecordset(RecordSet);
			return RecordCount;
		}	
		while(!RecordSet->IsEOF())
		{
			RecordCount ++;
			RecordSet->MoveNext();
		}
		RecordSet->MoveFirst();
	}
	else
	{
		if(!m_odbcRecordSet) return RecordCount;
		if(m_odbcRecordSet->IsEOF() && m_odbcRecordSet->IsBOF())
		{
			//AfxMessageBox("没有相关记录！");
			CloseRecordset();
			return RecordCount;
		}	
		while(!m_odbcRecordSet->IsEOF())
		{
			RecordCount ++;
			m_odbcRecordSet->MoveNext();
		}
		m_odbcRecordSet->MoveFirst();
	}
	return RecordCount;
}

BOOL MyAdo::GetRowCount(CString & strRowCount)
{
	if(!GetOneRcdFdsValue("","@@RowCount as TheRowCount","",strRowCount)) return false;
	return true;
}

BOOL MyAdo::GetCurrentID( CString &strCID )
{
	if(!GetOneRcdFdsValue("","@@IDENTITY as TheCID","",strCID)) return false;
	return true;
}

CString MyAdo::GetDatabaseName()
{
	return m_odbcConnection.GetDatabaseName();
}

BOOL MyAdo::ConnectAccessDB(CString csFile, CString csUid, CString csPwd, CString csDateBs, int iConnectType)
{
	USES_CONVERSION;
	BOOL rt = FALSE;
	m_csSrv = csFile;
	m_csUid = csUid;
	m_csPwd = csPwd;
	m_csDateBs = csDateBs;
	try{
		if(iConnectType)			
			rt = m_odbcConnection.OpenEx("Driver={Microsoft Access Driver (*.mdb)};Dbq=" + csFile + ";Uid=" + csUid + ";Pwd=" + csPwd, CDatabase::noOdbcDialog);
		else
			rt = m_odbcConnection.Open(csFile,false,false,"ODBC;UID=" + csUid + ";pwd=" + csPwd,true);
		m_odbcConnection.SetLoginTimeout(20000);
		m_odbcConnection.SetQueryTimeout(10*60*1000);
	}
	catch(CDBException* e)
	{
		Log(e->m_strError,1,m_strSqlLogFile);
		return FALSE;
	}
	return rt;
}

BOOL MyAdo::ConnectDB(CString csSrv, CString csUid, CString csPwd, CString csDateBs, int iConnectType, int iDbType)
{
	USES_CONVERSION;
	BOOL rt = FALSE;
	m_csSrv = csSrv;
	m_csUid = csUid;
	m_csPwd = csPwd;
	m_csDateBs = csDateBs;
	try{
		if(!iConnectType)
		{
			rt = m_odbcConnection.Open(csSrv,false,false,"ODBC;UID=" + csUid + ";pwd=" + csPwd,true);
		}else
		{
			CString strConnect;
			if(iDbType == 2 || iDbType == 3)
				strConnect = "driver={sql server};server=" + csSrv + ";uid=" + csUid + ";pwd=" + csPwd + ";DATABASE=" + csDateBs + ";namedPipe=true;";
			else if(iDbType == 0 || iDbType == 1)
				strConnect = "driver={sql server};server=" + csSrv + ";uid=" + csUid + ";pwd=" + csPwd + ";DATABASE=" + csDateBs;
			rt = m_odbcConnection.OpenEx(strConnect,CDatabase::noOdbcDialog);
		}
		m_odbcConnection.SetLoginTimeout(20000);
		m_odbcConnection.SetQueryTimeout(10*60*1000);
	}
	catch(CDBException* e)
	{
		m_strLastErr = "连接数据库" + csSrv + "失败：" + e->m_strError;
		Log(e->m_strError,1,m_strSqlLogFile);
		return FALSE;
	}
	return rt;
}

void MyAdo::SetMyQueryTimeout(DWORD DTimeOut)
{
	m_odbcConnection.SetQueryTimeout(DTimeOut);
}

void MyAdo::BeginTrans()
{
	m_odbcConnection.BeginTrans();
}

void MyAdo::Rollback()
{
	m_odbcConnection.Rollback();
}

void MyAdo::CommitTrans()
{
	m_odbcConnection.CommitTrans();
}

BOOL MyAdo::CheckConnect()
{
	return m_odbcConnection.IsOpen();
}

BOOL MyAdo::ReConnectDB()
{
	USES_CONVERSION;
	BOOL rt = FALSE;
	try{
		if(!m_odbcConnection.IsOpen())
		{
			m_odbcConnection.Close();
			rt = m_odbcConnection.OpenEx("driver={sql server};server=" + m_csSrv + ";uid=" + m_csUid + ";pwd=" + m_csPwd + ";DATABASE=" + m_csDateBs,CDatabase::noOdbcDialog);
		}else
			rt = TRUE;
	}
	catch(CDBException* e)
	{
		Log(e->m_strError,1,m_strSqlLogFile);
		return FALSE;
	}
	return rt;
}
BOOL MyAdo::NewRecordset()
{
	if(!m_odbcRecordSet)
		m_odbcRecordSet = new CRecordset(&m_odbcConnection);
		
	return TRUE;
	/*while(m_odbcRecordSet) Sleep(100);
	m_odbcRecordSet = new CRecordset(&m_odbcConnection);*/
}

void MyAdo::CloseRecordset(CRecordset * RecordSet)
{
	if(RecordSet)
	{
		RecordSet->Close();
		delete RecordSet;
		RecordSet = NULL;
	}
	if(!m_odbcRecordSet) return;
	m_odbcRecordSet->Close();
	delete m_odbcRecordSet;
	m_odbcRecordSet = NULL;
}

BOOL MyAdo::CreateLogTable(CString strTableName)
{
	CString strTableLog = strTableName + "_log";
	CString sql;
	sql =  "if not exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[" + strTableLog + "]') and OBJECTPROPERTY(id, N'IsUserTable') = 1) ";
	sql += "begin ";
	sql += "SELECT 1 as src_id, * INTO [dbo]." + strTableLog + " FROM " + strTableName + " WHERE 1<>1 ";
	sql += "ALTER TABLE " + strTableLog + " DROP COLUMN T_CI_ID ";
	sql += "ALTER TABLE " + strTableLog + " ALTER COLUMN src_id INT NULL ";
	sql += "ALTER TABLE " + strTableLog + " ADD Operator VARCHAR(30) NULL ";
	sql += "ALTER TABLE " + strTableLog + " ADD Operatetime DATETIME NULL CONSTRAINT DF_" + strTableLog + "_operatetime DEFAULT getdate() WITH VALUES ";
	sql += "end ";
	return ExecSQL(sql);
}


/*BOOL MyAdo::ExecSQL(CString sql)
{
	m_bIsShow = FALSE;
	Log(sql,0 ,m_strSqlLogFile);
	m_bIsShow = TRUE;
	try{
		ReConnectDB();
		m_odbcConnection.ExecuteSQL(sql);
	}catch(CDBException* e ){
		Log(e->m_strError);
		return FALSE;
	}
	return TRUE;
}

BOOL MyAdo::Select(CString sql, CRecordset * &RecordSet)
{
	m_bIsShow = TRUE;
	try{
		Log(sql,0 ,m_strSqlLogFile);
		if(!ReConnectDB()) return FALSE;
		RecordSet = new CRecordset(&m_odbcConnection);
		RecordSet->Open(CRecordset::snapshot,sql);
	}catch(CDBException* e ){
		Log(e->m_strError + sql);
		CString err;
		CStringArray strArray;
		err = e->m_strStateNativeOrigin;
		Split(err,strArray,",");
		if(!strArray[0].CompareNoCase("State:01000"))
		{
			m_odbcConnection.m_hdbc = SQL_NULL_HDBC;
			try{
				if(!ReConnectDB()) return FALSE;
				delete RecordSet;
				RecordSet = new CRecordset(&m_odbcConnection);
				RecordSet->Open(CRecordset::snapshot,sql);
				return TRUE;
			}catch(CDBException* e ){
				Log(e->m_strError + sql,0);
				return FALSE;
			}
		}
		return FALSE;
	}
	return TRUE;
}

BOOL MyAdo::SelectSQL(CString sql, int &RecordCount)
{
	RecordCount = 0;
	m_bIsShow = TRUE;
	try{
		Log(sql,0 ,m_strSqlLogFile);
		ReConnectDB();
		NewRecordset();
		m_odbcRecordSet->Open(CRecordset::snapshot,sql);
		RecordCount = GetRecordCount();
	}catch(CDBException* e ){
		Log(e->m_strError + sql);
		return FALSE;
	}
	return TRUE;	
}

BOOL MyAdo::SelectSQLEx(CString sql, CRecordset * &RecordSet, int &RecordCount)
{
	RecordCount = 0;
	m_bIsShow = TRUE;
	try{
		Log(sql,0 ,m_strSqlLogFile);
		ReConnectDB();
		RecordSet = new CRecordset(&m_odbcConnection);
		RecordSet->Open(CRecordset::snapshot,sql);
		RecordCount = GetRecordCount(RecordSet);
	}catch(CDBException* e ){
		Log(e->m_strError + sql);
		return FALSE;
	}
	return TRUE;	
}

*/
BOOL MyAdo::ExecSQL(CString sql, BOOL bIsLog)
{
	if(bIsLog) Log(sql,m_bIsShow ,m_strSqlLogFile);
	//m_bIsShow = TRUE;
	try{
		if(!ReConnectDB()) return FALSE;
		m_odbcConnection.ExecuteSQL(sql);
	}catch(CDBException* e ){
		m_strLastErr = e->m_strError + " \r\n发生在sql: \r\n " + sql;

#ifdef _DEBUG
		MsgBox(m_strLastErr);
#endif

		Log(e->m_strError + sql,m_bIsShow,m_strErrLogFile);
		CString err;
		CStringArray strArray;
		err = e->m_strStateNativeOrigin;
		Split(err,strArray,",");
		if(!strArray[0].CompareNoCase("State:01000"))
		{
			m_odbcConnection.m_hdbc = SQL_NULL_HDBC;
			try{
				if(!ReConnectDB()) return FALSE;
				m_odbcConnection.ExecuteSQL(sql);
				return TRUE;
			}catch(CDBException* e ){
				Log(e->m_strError + sql,m_bIsShow,m_strErrLogFile);
				return FALSE;
			}
		}
		return FALSE;
	}
	return TRUE;
}

BOOL MyAdo::ExecTransSQL(CString sql, BOOL bIsLog)
{
	if(bIsLog) Log(sql,0 ,m_strSqlLogFile);
	//m_bIsShow = TRUE;
	try{
		if(!ReConnectDB()) return FALSE;
		m_odbcConnection.BeginTrans();
		m_odbcConnection.ExecuteSQL(sql);
		m_odbcConnection.CommitTrans();
	}catch(CDBException* e ){
		m_strLastErr = e->m_strError + " \r\n发生在sql: \r\n " + sql;
		Log(e->m_strError + sql,m_bIsShow,m_strErrLogFile);
		CString err;
		CStringArray strArray;
		err = e->m_strStateNativeOrigin;
		Split(err,strArray,",");
		if(!strArray[0].CompareNoCase("State:01000"))
		{
			m_odbcConnection.m_hdbc = SQL_NULL_HDBC;
			try{
				if(!ReConnectDB()) return FALSE;
				m_odbcConnection.BeginTrans();				
				m_odbcConnection.ExecuteSQL(sql);
				m_odbcConnection.CommitTrans();
				return TRUE;
			}catch(CDBException* e ){
				Log(e->m_strError + sql,m_bIsShow,m_strErrLogFile);
				m_odbcConnection.Rollback();
				return FALSE;
			}
		}
		m_odbcConnection.Rollback();
		return FALSE;
	}
	return TRUE;
}

//BOOL MyAdo::ExecSQL(CString sql)
//{
//	m_bIsShow = FALSE;
//	Log(sql,0 ,m_strSqlLogFile);
//	m_bIsShow = TRUE;
//	try{
//		if(!ReConnectDB()) return FALSE;
//		m_odbcConnection.ExecuteSQL(sql);
//	}catch(CDBException* e ){
//		Log(e->m_strError + sql,1,m_strErrLogFile);
//		CString err;
//		CStringArray strArray;
//		err = e->m_strStateNativeOrigin;
//		Split(err,strArray,",");
//		if(!strArray[0].CompareNoCase("State:01000"))
//		{
//			m_odbcConnection.m_hdbc = SQL_NULL_HDBC;
//			try{
//				if(!ReConnectDB()) return FALSE;
//				m_odbcConnection.ExecuteSQL(sql);
//				return TRUE;
//			}catch(CDBException* e ){
//				Log(e->m_strError + sql);
//				return FALSE;
//			}
//		}
//		return FALSE;
//	}
//	return TRUE;
//}

BOOL MyAdo::Select(CString sql, CRecordset * &RecordSet)
{
	//m_bIsShow = TRUE;
	try{
		Log(sql,m_bIsShow,m_strSqlLogFile);
		if(!ReConnectDB()) return FALSE;
		RecordSet = new CRecordset(&m_odbcConnection);
		RecordSet->Open(CRecordset::snapshot,sql);
	}catch(CDBException* e ){
		m_strLastErr = e->m_strError + " \r\n发生在sql: \r\n " + sql;

	#ifdef _DEBUG
		MsgBox(m_strLastErr);
	#endif

		Log(e->m_strError + sql,m_bIsShow,m_strErrLogFile);
		CString err;
		CStringArray strArray;
		err = e->m_strStateNativeOrigin;
		Split(err,strArray,",");
		if(!strArray[0].CompareNoCase("State:01000"))
		{
			m_odbcConnection.m_hdbc = SQL_NULL_HDBC;
			try{
				if(!ReConnectDB()) return FALSE;
				delete RecordSet;
				RecordSet = new CRecordset(&m_odbcConnection);
				RecordSet->Open(CRecordset::snapshot,sql);
				return TRUE;
			}catch(CDBException* e ){
				Log(e->m_strError + sql,m_bIsShow,m_strErrLogFile);
				return FALSE;
			}
		}
		return FALSE;
	}
	return TRUE;
}

BOOL MyAdo::SelectSQL(CString sql, int &RecordCount)
{
	RecordCount = 0;
	//m_bIsShow = TRUE;
	try{
		Log(sql,m_bIsShow ,m_strSqlLogFile);
		if(!ReConnectDB()) return FALSE;
		NewRecordset();
		m_odbcRecordSet->Open(CRecordset::snapshot,sql);
		RecordCount = GetRecordCount();
		if(!RecordCount) 
		{
			m_strLastErr = "结果集为空";
			return FALSE;
		}
	}catch(CDBException* e ){
		m_strLastErr = e->m_strError + " \r\n发生在sql: \r\n " + sql;

#ifdef _DEBUG
		MsgBox(m_strLastErr);
#endif

		Log(e->m_strError + sql,m_bIsShow,m_strErrLogFile);
		CString err;
		CStringArray strArray;
		err = e->m_strStateNativeOrigin;
		Split(err,strArray,",");
		if(!strArray[0].CompareNoCase("State:01000"))
		{
			m_odbcConnection.m_hdbc = SQL_NULL_HDBC;
			try{
				if(!ReConnectDB()) return FALSE;
				NewRecordset();
				m_odbcRecordSet->Open(CRecordset::snapshot,sql);
				RecordCount = GetRecordCount();
				return TRUE;
			}catch(CDBException* e ){
				Log(e->m_strError + sql,m_bIsShow,m_strErrLogFile);
				return FALSE;
			}
		}
		return FALSE;
	}
	return TRUE;	
}

/*
	最终执行sql
*/
BOOL MyAdo::SelectSQLEx(CString sql, CRecordset * &RecordSet, int &RecordCount)
{
	RecordCount = 0;
	//m_bIsShow = TRUE;
	try{
		Log(sql,m_bIsShow ,m_strSqlLogFile);
		if(!ReConnectDB()) return FALSE;
		RecordSet = new CRecordset(&m_odbcConnection);
		RecordSet->Open(CRecordset::snapshot,sql);
		RecordCount = GetRecordCount(RecordSet);
		if(!RecordCount)
		{
			/*RecordSet->Close();
			delete RecordSet;
			RecordSet = NULL;
			return FALSE;*/
			m_strLastErr = "查询结果为空";
			return TRUE;
		}
	}catch(CDBException* e ){
		m_strLastErr = e->m_strError + " \r\n发生在sql: \r\n" + sql;

#ifdef _DEBUG
		MsgBox(m_strLastErr);
#endif

		Log(e->m_strError + sql,m_bIsShow,m_strErrLogFile);
		CString err;
		CStringArray strArray;
		err = e->m_strStateNativeOrigin;
		Split(err,strArray,",");
		if(!strArray[0].CompareNoCase("State:01000"))
		{
			m_odbcConnection.m_hdbc = SQL_NULL_HDBC;
			try{
				if(!ReConnectDB()) return FALSE;
				delete RecordSet;
				RecordSet = new CRecordset(&m_odbcConnection);
				RecordSet->Open(CRecordset::snapshot,sql);
				RecordCount = GetRecordCount(RecordSet);
				return TRUE;
			}catch(CDBException* e ){
				Log(e->m_strError + sql,m_bIsShow,m_strErrLogFile);
				return FALSE;
			}
		}
		return FALSE;
	}
	return TRUE;	
}

/*
	select arryExpres as arryField from strTable where strWhere
	结果集没有关闭
*/
BOOL MyAdo::SelectSQLEx(CString strTable, CStringArray& arryFields, CString strWhere, CRecordset * &pRecordSet, int &RecordCount)
{
	int size = (int)arryFields.GetCount();
	ASSERT(strTable);
	ASSERT(size);
	
	CString sql,strTempFields,strTemp = "";
	//CRecordset * pRecordset = 0;
	for(int i=0; i<size; i++)
	{
		strTemp += strTemp.IsEmpty() ? "" : ",";
		strTemp += arryFields[i];
	}
	sql = "select " +  strTemp + " from " + strTable + (strWhere.IsEmpty() ? "" : (" where " + strWhere));
	if(!SelectSQLEx(sql,pRecordSet,RecordCount)) return FALSE;
	//if(!RecordCount) return FALSE;
	return TRUE;
}
/*
	select arryExpres as arryField from strTable where strWhere
	结果集没有关闭
*/
BOOL MyAdo::SelectSQLEx(CString strTable,CStringArray& arryExpres, CStringArray& arryFields, CString strWhere, CRecordset * &pRecordSet, int &RecordCount)
{
	int size = (int)arryFields.GetCount();
	ASSERT(strTable);
	ASSERT(size);
	size = (int)arryExpres.GetCount();
	ASSERT(size);
	
	CString sql,strTempFields,strTemp = "";
	//CRecordset * pRecordset = 0;
	for(int i=0; i<size; i++)
	{
		strTemp += strTemp.IsEmpty() ? "" : ",";
		if(!arryExpres[i].CompareNoCase(arryFields[i]))
			strTemp += arryFields[i];
		else
			strTemp += arryExpres[i] + " as " + arryFields[i];
	}
	sql = "select " +  strTemp + " from " + strTable + (strWhere.IsEmpty() ? "" : (" where " + strWhere));
	if(!SelectSQLEx(sql,pRecordSet,RecordCount)) return FALSE;
	//if(!RecordCount) return FALSE;
	return TRUE;
}

/*
	data to map<int,string>
*/
BOOL MyAdo::Data2Map(CString strTable, CString KeyField, CString ValueField, CString strWhere, CMap<int,int,CString,CString> & map)
{	
	int i = 0,rcount = 0;
	CRecordset * pRset = NULL;
	CStringArray arryValue,arrayFields;
	arrayFields.Add(KeyField);
	arrayFields.Add(ValueField);

	if(!SelectSQLEx(strTable,arrayFields,strWhere,pRset,rcount)) return FALSE;
	
	/*if (bCheck)
	{
		if (rcount == (int)map.GetCount())
		{
			Log("无需更新map",0);
			return TRUE;
		}else
		{
			Log("重新读取map",0);
			map.RemoveAll();
		}
	}*/

	map.RemoveAll();

	for(int i=0; i<rcount; i++)
	{
		if(!GetFdsValuesArray(pRset,arrayFields,arryValue,TRUE)) break;
		map.SetAt(Str2Int(arryValue[0]),arryValue[1]);
	}
	CloseRecordset(pRset);
	return TRUE;
}

/*
	data to map<string,string>
*/
BOOL MyAdo::Data2Map(CString strTable, CString KeyField, CString ValueField, CString strWhere, CMap<LPSTR,LPSTR,CString,CString> & map)
{	
	int i = 0,rcount = 0;
	CRecordset * pRset = NULL;
	CStringArray arryValue,arrayFields;
	arrayFields.Add(KeyField);
	arrayFields.Add(ValueField);

	if(!SelectSQLEx(strTable,arrayFields,strWhere,pRset,rcount)) return FALSE;
	
	for(int i=0; i<rcount; i++)
	{
		if(!GetFdsValuesArray(pRset,arrayFields,arryValue,TRUE)) break;
		map.SetAt(arryValue[0].GetBuffer(),arryValue[1]);
	}
	CloseRecordset(pRset);
	return TRUE;
}


/*
	data to xml
*/
BOOL MyAdo::Data2Xml(CString strTable, CStringArray &arryFileds, CString strWhere, CString & strXml, BOOL bIncludeHead)
{
	strXml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n<fileds>\r\n";
	if(!bIncludeHead) strXml = "";
	
	int i = 0,rcount = 0;
	CRecordset * pRset = NULL;
	CStringArray arryValue;

	if(!SelectSQLEx(strTable,arryFileds,strWhere,pRset,rcount)) return FALSE;
	
	for(int i=0; i<rcount; i++)
	{
		if(!GetFdsValuesArray(pRset,arryFileds,arryValue,TRUE)) break;
		strXml += "\t<node ";
		for(int k=0; k<arryFileds.GetCount(); k++)
			strXml += arryFileds[k] + "=\"" + arryValue[k] + "\" ";
		strXml += "></node>\r\n";
	}
	if(bIncludeHead) strXml += "</fileds>";
	CloseRecordset(pRset);
	return TRUE;
}

/*
	数据绑定到combox
*/
BOOL MyAdo::Data2Combox(HWND Hdlg, int nComBoxID,CString strTableName, CString strTitleFiled, CString strValueField, CString strWhere, CStringArray &arrayValues)
{
	CStringArray arryFields,arrayTempValue;
	CRecordset * pRecordSet; 
	int RecordCount;

	arryFields.Add(strTitleFiled);
	arryFields.Add(strValueField);

	if(!SelectSQLEx(strTableName,arryFields,strWhere,pRecordSet,RecordCount)) return FALSE;
	
	if(!Hdlg) return FALSE;
	CComboBox Combox;
	Combox.m_hWnd = GetDlgItem(Hdlg,nComBoxID);
	if(!Combox.GetSafeHwnd()) return FALSE;
	Combox.ResetContent();
	arrayValues.RemoveAll();

	for(int i=0; i<RecordCount; i++)
	{
		GetFdsValuesArray(pRecordSet,arryFields,arrayTempValue,1);
		Combox.InsertString(Combox.GetCount(),arrayTempValue[0]);
		arrayValues.Add(arrayTempValue[1]);
	}
	pRecordSet->Close();
	return TRUE;
}

BOOL MyAdo::Data2Combox(CComboBox & Combox,CString strTableName, CString strTitleFiled, CString strValueField, CString strWhere, CStringArray &arrayValues)
{
	CStringArray arryFields,arrayTempValue;
	CRecordset * pRecordSet; 
	int RecordCount;

	arryFields.Add(strTitleFiled);
	arryFields.Add(strValueField);

	if(!SelectSQLEx(strTableName,arryFields,strWhere,pRecordSet,RecordCount)) return FALSE;
	
	if(!Combox.GetSafeHwnd()) return FALSE;
	Combox.ResetContent();
	arrayValues.RemoveAll();

	for(int i=0; i<RecordCount; i++)
	{
		GetFdsValuesArray(pRecordSet,arryFields,arrayTempValue,1);
		Combox.InsertString(Combox.GetCount(),arrayTempValue[0]);
		arrayValues.Add(arrayTempValue[1]);
	}
	pRecordSet->Close();
	return TRUE;
}

/*
	数据绑定到List
*/
BOOL MyAdo::Data2List(CListBox &List,CString strTableName, CString strDescriptionField, CString strOutField, CString strWhere, CStringArray & OutValueArray)
{
	CRecordset * pRecordSet; 
	CStringArray arrayFields,arrayTempValue;
	int RecordCount;
	
	arrayFields.Add(strOutField);
	arrayFields.Add(strDescriptionField);
	
	if(!SelectSQLEx(strTableName,arrayFields,strWhere,pRecordSet,RecordCount)) return FALSE;
	
	if(!List.GetSafeHwnd()) return FALSE;
	List.ResetContent();
	OutValueArray.RemoveAll();

	for(int i=0; i<RecordCount; i++)
	{
		GetFdsValuesArray(pRecordSet,arrayFields,arrayTempValue,1);
		OutValueArray.Add(arrayTempValue[0]);
		List.InsertString(List.GetCount(),arrayTempValue[1]);		
	}
	pRecordSet->Close();
	return TRUE;
}

/*
	数据绑定到List
*/
BOOL MyAdo::Data2List(CListBox &List,CString strTableName, CString strDescriptionField, CString strOutField, CString strWhere, CStringList & OutValueList)
{
	CRecordset * pRecordSet; 
	CStringArray arrayFields,arrayTempValue;
	int RecordCount;
	
	arrayFields.Add(strOutField);
	arrayFields.Add(strDescriptionField);
	
	if(!SelectSQLEx(strTableName,arrayFields,strWhere,pRecordSet,RecordCount)) return FALSE;
	
	if(!List.GetSafeHwnd()) return FALSE;
	List.ResetContent();
	OutValueList.RemoveAll();

	for(int i=0; i<RecordCount; i++)
	{
		GetFdsValuesArray(pRecordSet,arrayFields,arrayTempValue,1);
		OutValueList.AddTail(arrayTempValue[0]);
		List.InsertString(List.GetCount(),arrayTempValue[1]);		
	}
	pRecordSet->Close();
	return TRUE;
}

/*
	获取数据库版本
*/
int MyAdo::GetDBVersion()
{
	CString strVeresion;
	if(!GetOneRcdFdsValue("","case when left(convert(varchar(20),ServerProperty('Productversion')),1) < 9 then 2000 else 2005 end","",strVeresion)) return 0;
	return Str2Int(strVeresion);
}

/*
	数据绑定到ListCtrl
*/
BOOL MyAdo::Data2ListCtrl(CListCtrl &ListCtrl,CString strTableName, CStringArray &arrayFields, CString strWhere)
{
	CRecordset * pRecordSet; 
	CStringArray arrayTempValue;
	int RecordCount;

	if(!SelectSQLEx(strTableName,arrayFields,strWhere,pRecordSet,RecordCount)) return FALSE;
	
	if(!ListCtrl.GetSafeHwnd()) return FALSE;
	ListCtrl.DeleteAllItems();

	for(int i=0; i<RecordCount; i++)
	{
		GetFdsValuesArray(pRecordSet,arrayFields,arrayTempValue,1);
		int itemCount = ListCtrl.GetItemCount();
		ListCtrl.InsertItem(itemCount,"");
		for(int k=0; k<arrayTempValue.GetCount(); k++)
			ListCtrl.SetItemText(itemCount,k,arrayTempValue[k]);
		
	}
	pRecordSet->Close();
	return TRUE;
}

/*
	数据绑定到ListCtrl
*/
BOOL MyAdo::Data2ListCtrl(CListCtrl &ListCtrl,CString strTableName, CString strWhere, CStringArray & arrayFieldOut)
{
	CRecordset * pRecordSet; 
	CString temp;
	int RecordCount;

	CString sql;
	sql = "select * from " + strTableName + " where " + (strWhere.IsEmpty() ? " 1=1" : strWhere);
	if(!SelectSQLEx(sql,pRecordSet,RecordCount)) return FALSE;
	
	if(!ListCtrl.GetSafeHwnd()) return FALSE;
	ListCtrl.DeleteAllItems();
	arrayFieldOut.RemoveAll();
	for(int i=ListCtrl.GetHeaderCtrl()->GetItemCount(); i>=0; i--) ListCtrl.DeleteColumn(0);
	int ColCount=pRecordSet->GetODBCFieldCount();//列数 
	for(int i=0;i<ColCount;i++)   
	{
		CODBCFieldInfo fieldinfo;
		pRecordSet->GetODBCFieldInfo(i,fieldinfo);
		arrayFieldOut.Add(fieldinfo.m_strName);
		ListCtrl.InsertColumn(i,fieldinfo.m_strName,0,100);
	}

	for(int i=0; i<RecordCount; i++)
	{		
		int itemCount = ListCtrl.GetItemCount();
		ListCtrl.InsertItem(itemCount,"");
		for(int k=0; k<ColCount; k++)
		{
			pRecordSet->GetFieldValue(k,temp);
			ListCtrl.SetItemText(itemCount,k,temp);
		}
		pRecordSet->MoveNext();
	}
	pRecordSet->Close();
	return TRUE;
}

BOOL MyAdo::Data2ListCtrl(CListCtrl &ListCtrl,CString strTableName, CStringArray &arrayFields, CString strWhere, CStringList & OutValueList, int OutIndex)
{
	CRecordset * pRecordSet; 
	CStringArray arrayTempValue;
	int RecordCount;

	if(!SelectSQLEx(strTableName,arrayFields,strWhere,pRecordSet,RecordCount)) return FALSE;
	
	if(!ListCtrl.GetSafeHwnd()) return FALSE;
	ListCtrl.DeleteAllItems();
	OutValueList.RemoveAll();

	for(int i=0; i<RecordCount; i++)
	{
		GetFdsValuesArray(pRecordSet,arrayFields,arrayTempValue,1);
		int itemCount = ListCtrl.GetItemCount();
		ListCtrl.InsertItem(itemCount,"");
		for(int k=0; k<arrayTempValue.GetCount(); k++)
			ListCtrl.SetItemText(itemCount,k,arrayTempValue[k]);
		OutValueList.AddTail(arrayTempValue[OutIndex]);
	}
	pRecordSet->Close();
	return TRUE;
}

/*
	数据绑定到ListCtrl
*/
BOOL MyAdo::Data2ListCtrl(HWND Hdlg, int nListCtrlID,CString strTableName, CStringArray &arrayFields, CString strWhere)
{
	CRecordset * pRecordSet; 
	CStringArray arrayTempValue;
	int RecordCount;

	if(!SelectSQLEx(strTableName,arrayFields,strWhere,pRecordSet,RecordCount)) return FALSE;
	
	if(!Hdlg) return FALSE;
	CListCtrl theListCtrl;
	theListCtrl.m_hWnd = GetDlgItem(Hdlg,nListCtrlID);
	if(!theListCtrl.GetSafeHwnd()) return FALSE;
	theListCtrl.DeleteAllItems();

	for(int i=0; i<RecordCount; i++)
	{
		GetFdsValuesArray(pRecordSet,arrayFields,arrayTempValue,1);
		int itemCount = theListCtrl.GetItemCount();
		theListCtrl.InsertItem(itemCount,"");
		for(int k=0; k<arrayTempValue.GetCount(); k++)
			theListCtrl.SetItemText(itemCount,k,arrayTempValue[k]);
		
	}
	pRecordSet->Close();
	return TRUE;
}

/*
	获取表主键
*/
BOOL MyAdo::GetTablePrimaryKey(CString strTable, CString &strPrimaryKey)
{
	return GetOneRcdFdsValue("sys.columns c left join sys.extended_properties ex on ex.minor_id = c.column_id and ex.major_id = c.object_id inner join systypes t on t.xtype = c.system_type_id left join sys.index_columns i on c.object_id  = i.object_id and c.column_id = i.column_id",
		"convert(varchar(200),c.name) as fieldname","c.object_id=object_id('" + strTable + "') and i.object_id is not null order by c.column_id",strPrimaryKey);
}

/*
	数据绑定到ListCtrl
*/
BOOL MyAdo::Data2ListCtrl(CListCtrl &ListCtrl,CString strTableName, CString strWhere, int &count, CStringArray & arrayFieldOut, CString strPrimaryKey, int iCountPrePage, int iPage)
{
	CRecordset * pRecordSet; 
	CString temp;
	int RecordCount;
	count = 0;

	CString sql;
	if(strPrimaryKey.IsEmpty() && !GetTablePrimaryKey(strTableName, strPrimaryKey)) return FALSE;

	CString strCount;
	GetOneRcdFdsValue(strTableName,"count(1) as totlecount",strWhere,strCount);
	count = Str2Int(strCount);

	if(!iCountPrePage && !iPage)
		sql = "select * from " + strTableName + " where " + (strWhere.IsEmpty() ? " 1=1" : strWhere);
	else
	{
		sql = "SELECT TOP " + Int2Str(iCountPrePage) + " * FROM " + strTableName + " where " + strWhere;
		if(iPage != 1) 
			sql += " and (" + strPrimaryKey + " > (select max(" + strPrimaryKey + ") from (select top " +  Int2Str((iPage-1)*iCountPrePage) + " " +
			strPrimaryKey + " from " + strTableName + " where " + strWhere + " order by " + strPrimaryKey + " asc) as T))";
		sql += " order by " + strPrimaryKey + " asc";
	}
	if(!SelectSQLEx(sql,pRecordSet,RecordCount)) return FALSE;
	
	if(!ListCtrl.GetSafeHwnd()) return FALSE;
	ListCtrl.DeleteAllItems();
	arrayFieldOut.RemoveAll();
	for(int i=ListCtrl.GetHeaderCtrl()->GetItemCount(); i>=0; i--) ListCtrl.DeleteColumn(0);
	int ColCount=pRecordSet->GetODBCFieldCount();//列数 
	for(int i=0;i<ColCount;i++)   
	{
		CODBCFieldInfo fieldinfo;
		pRecordSet->GetODBCFieldInfo(i,fieldinfo);
		arrayFieldOut.Add(fieldinfo.m_strName);
		ListCtrl.InsertColumn(i,fieldinfo.m_strName,0,100);
	}

	for(int i=0; i<RecordCount; i++)
	{		
		int itemCount = ListCtrl.GetItemCount();
		ListCtrl.InsertItem(itemCount,"");
		for(int k=0; k<ColCount; k++)
		{
			pRecordSet->GetFieldValue(k,temp);
			ListCtrl.SetItemText(itemCount,k,temp);
		}
		pRecordSet->MoveNext();
	}
	pRecordSet->Close();
	return TRUE;
}

/*
	数据绑定到ListCtrl
*/
BOOL MyAdo::Data2ListCtrl(CListCtrl &ListCtrl, CStringArray &arrayField, CString strTableName, CString strWhere, int &count, CString strPrimaryKey, int iCountPrePage, int iPage)
{
	CRecordset * pRecordSet; 
	CString temp,strFields = "";
	if(strWhere.IsEmpty()) strWhere = " 1=1 ";
	int RecordCount;
	count = 0;

	for(int i=0; i<arrayField.GetCount(); i++) strFields += arrayField[i] + ",";
	strFields = strFields.Left(strFields.GetLength()-1);


	CString sql;
	if(strPrimaryKey.IsEmpty() && !GetTablePrimaryKey(strTableName, strPrimaryKey)) return FALSE;

	CString strCount;
	GetOneRcdFdsValue(strTableName,"count(1) as totlecount",strWhere,strCount);
	count = Str2Int(strCount);

	if(!iCountPrePage && !iPage)
		sql = "select " + strFields + " from " + strTableName + " where " + (strWhere.IsEmpty() ? " 1=1" : strWhere);
	else
	{
		sql = "SELECT TOP " + Int2Str(iCountPrePage) + " " + strFields + " FROM " + strTableName + " where " + strWhere;
		if(iPage != 1) 
			sql += " and (" + strPrimaryKey + " > (select max(" + strPrimaryKey + ") from (select top " +  Int2Str((iPage-1)*iCountPrePage) + " " +
			strPrimaryKey + " from " + strTableName + " where " + strWhere + " order by " + strPrimaryKey + " asc) as T))";
		sql += " order by " + strPrimaryKey + " asc";
	}
	if(!SelectSQLEx(sql,pRecordSet,RecordCount)) return FALSE;
	
	if(!ListCtrl.GetSafeHwnd()) return FALSE;
	ListCtrl.DeleteAllItems();
	//arrayFieldOut.RemoveAll();
	for(int i=ListCtrl.GetHeaderCtrl()->GetItemCount(); i>=0; i--) ListCtrl.DeleteColumn(0);
	int ColCount=pRecordSet->GetODBCFieldCount();//列数 
	for(int i=0;i<ColCount;i++)   
	{
		CODBCFieldInfo fieldinfo;
		pRecordSet->GetODBCFieldInfo(i,fieldinfo);
		//arrayFieldOut.Add(fieldinfo.m_strName);
		ListCtrl.InsertColumn(i,fieldinfo.m_strName,0,100);
	}

	for(int i=0; i<RecordCount; i++)
	{		
		int itemCount = ListCtrl.GetItemCount();
		ListCtrl.InsertItem(itemCount,"");
		for(int k=0; k<ColCount; k++)
		{
			pRecordSet->GetFieldValue(k,temp);
			ListCtrl.SetItemText(itemCount,k,temp);
		}
		pRecordSet->MoveNext();
	}
	pRecordSet->Close();
	return TRUE;
}
/*
	数据绑定到ListCtrl
*/
BOOL MyAdo::Data2ListCtrl(CListCtrl &ListCtrl,CString strSql, int &count, int iShowCount)
{
	CRecordset * pRecordSet = NULL; 
	CString temp;
	count = 0;

	if(!SelectSQLEx(strSql,pRecordSet,count)) return FALSE;
	iShowCount = iShowCount < count ? (iShowCount ? iShowCount : (count > 1000 ? 1000 : count)) : count;
	if(!ListCtrl.GetSafeHwnd()) return FALSE;
	ListCtrl.DeleteAllItems();
	for(int i=ListCtrl.GetHeaderCtrl()->GetItemCount(); i>=0; i--) ListCtrl.DeleteColumn(0);
	int ColCount=pRecordSet->GetODBCFieldCount();//列数 
	for(int i=0;i<ColCount;i++)   
	{
		CODBCFieldInfo fieldinfo;
		pRecordSet->GetODBCFieldInfo(i,fieldinfo);
		ListCtrl.InsertColumn(i,fieldinfo.m_strName,0,100);
	}

	for(int i=0; i<iShowCount; i++)
	{		
		int itemCount = ListCtrl.GetItemCount();
		ListCtrl.InsertItem(itemCount,"");
		for(int k=0; k<ColCount; k++)
		{
			pRecordSet->GetFieldValue(k,temp);
			ListCtrl.SetItemText(itemCount,k,temp);
		}
		pRecordSet->MoveNext();
	}
	pRecordSet->Close();
	return TRUE;
}

/*
	获取一条记录的多个字段的值，值保存在String数组中
*/
BOOL MyAdo::GetOneRcdFdsValue(CString strTable, CStringArray& arryFields, CString strWhere, CStringArray& arryValue)
{
	int size = (int)arryFields.GetCount();
	ASSERT(strTable);
	ASSERT(size);

	arryValue.RemoveAll();
	
	int count = 0;
	CString sql,strTempFields,strTemp = "";
	CRecordset * pRecordset = 0;
	for(int i=0; i<size; i++)
	{
		strTemp += strTemp.IsEmpty() ? "" : ",";
		strTemp += arryFields[i];
	}
	sql = "select " +  strTemp + " from " + strTable + (strWhere.IsEmpty() ? "" : (" where " + strWhere));
	if(!SelectSQLEx(sql,pRecordset,count)) return FALSE;
	if(!count) return FALSE;
	pRecordset->MoveFirst();
	for(int i=0; i<size; i++)
	{
		//strTempFields = arryFields.GetAt(i);
		//pRecordset->GetFieldValue(strTempFields,strTemp);
		pRecordset->GetFieldValue(i,strTemp);
		strTemp = strTemp.GetString();
		strTemp = TrimA(strTemp);
		arryValue.Add(TrimA(strTemp));
	}
	CloseRecordset(pRecordset);
	return TRUE;
}

BOOL MyAdo::Select_ForXml(CString strTable, CStringArray& arryFields, CString strWhere, CString& strXmlValue)
{
	int size = (int)arryFields.GetCount();
	ASSERT(strTable);
	ASSERT(size);

	int count = 0;
	CString sql,strTempFields,strTemp = "";
	CRecordset * pRecordset = 0;
	for(int i=0; i<size; i++)
	{
		strTemp += strTemp.IsEmpty() ? "" : ",";
		strTemp += arryFields[i];
	}
	sql = "select " +  strTemp + " from " + strTable + (strWhere.IsEmpty() ? "" : (" where " + strWhere));
	if(!SelectSQLEx(sql,pRecordset,count)) return FALSE;
	if(!count) return FALSE;
	pRecordset->MoveFirst();
	
	RecordSet2Xml(pRecordset,count,strXmlValue);

	CloseRecordset(pRecordset);
	return TRUE;
}

BOOL MyAdo::Select_ForXml(CString strSql, CString& strXmlValue)
{
	if (strSql.IsEmpty())
	{
		m_strLastErr = "sql语句不能为空！";
		return false;
	}
	int count = 0;
	CRecordset * pRecordset = 0;
	if(!SelectSQLEx(strSql,pRecordset,count)) return FALSE;
	if(!count) return FALSE;
	pRecordset->MoveFirst();

	RecordSet2Xml(pRecordset,count,strXmlValue);

	CloseRecordset(pRecordset);
	return TRUE;
}

BOOL MyAdo::RecordSet2Xml(CRecordset * pRecordSet, int RecordCount, CString &strXml)
{
	CString temp;
	CStringArray arrayFieldName;
	int ColCount=pRecordSet->GetODBCFieldCount();//列数 
	for(int i=0;i<ColCount;i++)   
	{
		CODBCFieldInfo fieldinfo;
		pRecordSet->GetODBCFieldInfo(i,fieldinfo);
		temp = fieldinfo.m_strName;
		int index = -1, flag = 0;
		while (FindStr(arrayFieldName,temp,index))
		{
			temp += Int2Str(flag++);
		}
		arrayFieldName.Add(temp);
	}

	for(int i=0; i<RecordCount; i++)
	{
		strXml += "\t<row ";
		for(int j=0; j<arrayFieldName.GetCount(); j++)
		{
			pRecordSet->GetFieldValue(j,temp);
			strXml += arrayFieldName[j] + " = \"" + Xml::ConvertXmlChar(temp.GetString()) + "\" ";
		}
		strXml += "></row>\r\n";
		pRecordSet->MoveNext();
	}
	return TRUE;
}
/*
	获取多条记录的一个字段的值，值保存在String中，SPLIT_CHAR分隔
*/
BOOL MyAdo::GetRcdsFdValues(CString strTable, CString strField, CString strWhere, CString& strValueList)
{
	ASSERT(strTable);
	ASSERT(strField);

	strValueList = "";
	
	int count = 0;
	CString sql,strTemp = "";
	CRecordset * pRecordset = 0;

	sql = "select " +  strField + " from " + strTable + (strWhere.IsEmpty() ? "" : (" where " + strWhere));
	SelectSQLEx(sql,pRecordset,count);
	if(!count) return FALSE;
	pRecordset->MoveFirst();
	for(int i=0; i<count; i++)
	{
		pRecordset->GetFieldValue(strField,strTemp);
		strTemp = strTemp.GetString();
		strTemp = TrimA(strTemp);
		strTemp.Replace(",","，");

		strValueList += strValueList.IsEmpty() ? "" : SPLIT_CHAR;
		strValueList += strTemp;

		pRecordset->MoveNext();
	}
	CloseRecordset(pRecordset);
	return TRUE;
}
/*
	获取多条记录的一个字段的值，值保存在CStringArray中
*/
BOOL MyAdo::GetRcdsFdValues(CString strTable, CString strField, CString strWhere, CStringArray& arrayValues)
{
	ASSERT(strTable);
	ASSERT(strField);

	arrayValues.RemoveAll();
	
	int count = 0;
	CString sql,strTemp = "";
	CRecordset * pRecordset = 0;

	sql = "select " +  strField + " from " + strTable + (strWhere.IsEmpty() ? "" : (" where " + strWhere));
	SelectSQLEx(sql,pRecordset,count);
	if(!count) return FALSE;
	pRecordset->MoveFirst();
	for(int i=0; i<count; i++)
	{
		pRecordset->GetFieldValue(strField,strTemp);
		strTemp = strTemp.GetString();
		arrayValues.Add(strTemp);		
		pRecordset->MoveNext();
	}
	CloseRecordset(pRecordset);
	return TRUE;
}
/*
	将结果集中的一行记录保存到CStringArray中，取完记录游标下移一位。
*/
BOOL MyAdo::GetFdsValuesArray(CRecordset * &pRecordset, CStringArray& arryFields, CStringArray& strValueList, BOOL BbyIndex)
{
	int size = (int)arryFields.GetCount();
	ASSERT(size);
	if(pRecordset->IsEOF()) return FALSE;

	strValueList.RemoveAll();

	CString sql,strTempFields,strTemp = "";
	for(int i=0; i<size; i++)
	{
		if(BbyIndex) pRecordset->GetFieldValue(i,strTemp);
		else
		{
			strTempFields = arryFields.GetAt(i);
			pRecordset->GetFieldValue(strTempFields,strTemp);
		}
		
		strTemp = strTemp.GetString();
		strTemp = TrimA(strTemp);
		strValueList.Add(TrimA(strTemp));
	}
	pRecordset->MoveNext();
	return TRUE;
}

/*
	取一条记录的某个字段的值
*/
BOOL MyAdo::GetOneRcdFdsValue(CString strTable, CString strField, CString strWhere, CString& strValue)
{
	ASSERT(strTable);
	ASSERT(strField);

	strValue = "";

	int count = 0;
	CString sql,strTempFields,strTemp = "";
	CRecordset * pRecordset = 0;

	sql = "select " +  strField + (strTable.IsEmpty() ? "" : " from ") + strTable + (strWhere.IsEmpty() ? "" : (" where " + strWhere));
	SelectSQLEx(sql,pRecordset,count);
	if(!count) return FALSE;
	pRecordset->MoveFirst();

	int item = 0;
	pRecordset->GetFieldValue(item,strTemp);

	strValue = strTemp.GetString();
	strValue = TrimA(strValue);

	CloseRecordset(pRecordset);
	return TRUE;
}

BOOL MyAdo::CloseDB()
{
	try{
		if(m_odbcConnection.IsOpen()) m_odbcConnection.Close();
	}catch(CDBException* e)
	{
		Log(e->m_strError);
		return FALSE;
	}
	return TRUE;
}

BOOL MyAdo::Attach_DB( CString strDBName, CString strMDF, CString strLDF )
{
	CString strSql;
	strSql = "EXEC sp_attach_db @dbname = N '" + strDBName + "',@filename1 = N'" + strMDF + "',@filename2   =   N '" + strLDF + "'";
	return ExecSQL(strSql);
}
/*---------------------socket------------------------*/
MySocket::MySocket()
{
	m_sServer = INVALID_SOCKET;
	//m_sRevClient = INVALID_SOCKET;
	m_sClient = INVALID_SOCKET;

	m_pSocketSrvThread = NULL;
	m_pSocketWorkThread = NULL;
	m_StopHevent = FALSE;

	m_iServerLen = sizeof(m_adServer);
	//m_iClientLen = sizeof(m_adClient);
	m_wdVersionRequested = MAKEWORD(1,1);
	if (WSAStartup(m_wdVersionRequested,&m_wdData))
		Log("WSADATA start failed", SOCKET_LOG_FILE_NAME);
}

MySocket::~MySocket()
{
	WSACleanup();
}

BOOL MySocket::CloseSocket()
{
	if(m_StopHevent) SetEvent(m_StopHevent);
	Sleep(SOCKET_CLOSE_SLEEP_TIME * 2);
	while(CheckWorkThread())
	{
		Log("wait for WorkThread sleep once!", 0,SOCKET_LOG_FILE_NAME);
		Sleep(SOCKET_CLOSE_SLEEP_TIME);//WaitForSingleObject(m_pSocketWorkThread->m_hThread,INFINITE);
	}

	//CLOSE ALL CLIENT CLOSE 
	CSingleLock SingleLock(&m_TcpThreadMutex);	
	SingleLock.Lock();
	if(!m_sTcpThreadList.IsEmpty())
	{	
		TcpThread TcpClient;
		POSITION Tposition = m_sTcpThreadList.GetHeadPosition();
		int count = (int)m_sTcpThreadList.GetSize();
		for(int i=0; i<count; i++)
		{
			TcpClient = m_sTcpThreadList.GetNext(Tposition);
			Close_Socket(TcpClient.ClientSocket);
			CloseHandle(TcpClient.hThread);
		}
	}
	SingleLock.Unlock();

	Sleep(SOCKET_CLOSE_SLEEP_TIME);

	while(CheckTcpThread())
	{
		Log("wait for client socket sleep once!", 0,SOCKET_LOG_FILE_NAME);
		Sleep(SOCKET_CLOSE_SLEEP_TIME);
	}

	Close_Socket(m_sServer);
	//Close_Socket(m_sRevClient);
	Close_Socket(m_sClient);	

	Sleep(SOCKET_CLOSE_SLEEP_TIME);

	while(CheckSrvThread()) 
	{
		Log("wait for SrvThread sleep once!", 0,SOCKET_LOG_FILE_NAME);
		Sleep(SOCKET_CLOSE_SLEEP_TIME);
	}
	CloseHandle(m_StopHevent);
	Log("close socket cuccess!", 0,SOCKET_LOG_FILE_NAME);
	return 1;
}

void MySocket::Close_Socket(SOCKET ClsSocket)
{
	if(ClsSocket != INVALID_SOCKET)
	{
		closesocket(ClsSocket);
		ClsSocket = INVALID_SOCKET;
	}
}

BOOL MySocket::InitSocketSrv(int iPort, int iSocketType, AFX_THREADPROC SocketWorkThread, MySocket * pSocket)
{
	BOOL RT = FALSE;

	if(iSocketType != 1 && iSocketType != 2)
	{
		Log("Socket type err",  SOCKET_LOG_FILE_NAME);
		return RT;
	}

	m_iPort = iPort;
	m_iSocketTyp = iSocketType;
	
	m_sServer = socket(PF_INET,m_iSocketTyp,0); 
	if (m_sServer == INVALID_SOCKET) 
	{ 
		Log("Socket create failed: " + Int2Str(WSAGetLastError()),  SOCKET_LOG_FILE_NAME);
		return RT;
	}

	m_adServer.sin_family = PF_INET; 
	m_adServer.sin_addr.s_addr = htonl(INADDR_ANY); 
	m_adServer.sin_port = htons(m_iPort);

	if (bind(m_sServer,(struct sockaddr *)&m_adServer,sizeof(m_adServer)) != 0) 
	{ 
		Log("bind failed: " + Int2Str(WSAGetLastError()), SOCKET_LOG_FILE_NAME);
		closesocket(m_sServer);
		return RT;
	}

	if(m_iSocketTyp == 1)
	{
		if(listen(m_sServer,5) != 0) 
		{
			Log("listen failed: " + Int2Str(WSAGetLastError()), SOCKET_LOG_FILE_NAME);
			closesocket(m_sServer);
			return RT;
		}
	}

	m_StopHevent = CreateEvent(NULL,TRUE,false,NULL);
	m_SocketWorkThread = SocketWorkThread;

	if(m_iSocketTyp == 1)
		m_pSocketSrvThread = AfxBeginThread(&MySocket::SocketSrvThread_Tcp, (LPVOID)pSocket);//(LPVOID)SocketSrvThread
	else if(m_iSocketTyp == 2)
		m_pSocketSrvThread = AfxBeginThread(&MySocket::SocketSrvThread_Udp, (LPVOID)pSocket);

	if(!m_pSocketSrvThread)
	{
		Log("Create srv thread failed: " + Int2Str(WSAGetLastError()), SOCKET_LOG_FILE_NAME);
		closesocket(m_sServer);
		return RT;
	}

	m_pSocketWorkThread = AfxBeginThread(m_SocketWorkThread, (LPVOID)pSocket);

	if(!m_pSocketWorkThread)
	{
		Log("Create work thread failed: " + Int2Str(WSAGetLastError()), SOCKET_LOG_FILE_NAME);
		closesocket(m_sServer);
		return RT;
	}

	return 1;
}

BOOL MySocket::InitSocketClient(CString csSrvIp, int iPort, int iSocketType, AFX_THREADPROC SocketWorkThread, MySocket * pSocket)
{
	BOOL RT = FALSE;

	if(iSocketType != 1 && iSocketType != 2)
	{
		Log("Socket type err",  SOCKET_LOG_FILE_NAME);
		return RT;
	}

	m_iPort = iPort;
	m_iSocketTyp = iSocketType;
	
	m_sServer = socket(PF_INET,m_iSocketTyp,0); 
	if (m_sServer == INVALID_SOCKET) 
	{ 
		Log("Socket create failed: " + Int2Str(WSAGetLastError()),  SOCKET_LOG_FILE_NAME);
		return RT;
	}

	USES_CONVERSION;
	m_adServer.sin_family = PF_INET; 
	m_adServer.sin_addr.s_addr = inet_addr(T2A(csSrvIp.GetBuffer(csSrvIp.GetLength()))); 
	m_adServer.sin_port = htons(m_iPort);

	if(m_iSocketTyp == 1)
	{
		if(connect(m_sServer,(struct sockaddr *)&m_adServer,sizeof(m_adServer)) == SOCKET_ERROR)
		{
			Log("connect srv failed: " + Int2Str(WSAGetLastError()), SOCKET_LOG_FILE_NAME);
			closesocket(m_sServer);
			return RT;
		}
	}

	m_StopHevent = CreateEvent(NULL,TRUE,false,NULL);
	m_SocketWorkThread = SocketWorkThread;

	m_pSocketSrvThread = AfxBeginThread(&MySocket::SocketClientThread, (LPVOID)pSocket);

	if(!m_pSocketSrvThread)
	{
		Log("Create srv thread failed: " + Int2Str(WSAGetLastError()), SOCKET_LOG_FILE_NAME);
		closesocket(m_sServer);
		return RT;
	}

	m_pSocketWorkThread = AfxBeginThread(m_SocketWorkThread, (LPVOID)pSocket);

	if(!m_pSocketWorkThread)
	{
		Log("Create work thread failed: " + Int2Str(WSAGetLastError()), SOCKET_LOG_FILE_NAME);
		closesocket(m_sServer);
		return RT;
	}
	return 1;
}

BOOL MySocket::CheckStop()
{
	return (WaitForSingleObject(m_StopHevent,0) != WAIT_TIMEOUT);
}

BOOL MySocket::CheckSrvThread()
{
	BOOL RT = FALSE;
	CSingleLock SingleLock(&m_SrvMutex);	
	SingleLock.Lock();	
	if(m_pSocketSrvThread) RT = TRUE;
	SingleLock.Unlock();
	return RT;
}

BOOL MySocket::CheckWorkThread()
{
	BOOL RT = FALSE;
	CSingleLock SingleLock(&m_WorkMutex);	
	SingleLock.Lock();	
	if(m_pSocketWorkThread) RT = TRUE;
	SingleLock.Unlock();
	return RT;
}

BOOL MySocket::CheckTcpThread()
{
	BOOL RT = FALSE;
	CSingleLock SingleLock(&m_TcpThreadMutex);	
	SingleLock.Lock();	
	if(!m_sTcpThreadList.IsEmpty()) RT = TRUE;
	SingleLock.Unlock();
	return RT;
}

void MySocket::FreeWorkThread()
{
	CSingleLock SingleLock(&m_SrvMutex);	
	SingleLock.Lock();
	m_pSocketWorkThread = NULL;
	SingleLock.Unlock();
}

BOOL MySocket::GetMessageInfo(SocketInfo &TaskInfo)
{
	if(m_sClientList.IsEmpty()) return FALSE;
	TaskInfo = m_sClientList.GetHead();
	m_sClientList.RemoveHead();
	return TRUE;
}

BOOL MySocket::SendMsg2Client(char * pMsg, sockaddr_in adClient, SOCKET ClientSocket, int msgsize)
{
	CString strLog = "";
	CString strId = "";
	BOOL RT = TRUE;

	strId = (CString)inet_ntoa(adClient.sin_addr);

	strLog = "post msg to   " + strId + ": ";
	strLog += pMsg;
	int len;
	len = (msgsize ? msgsize : (int)strlen(pMsg));
	char Msg[SOCKET_REV_BUFF_LENTH];
	//ZeroMemory(Msg,SOCKET_REV_BUFF_LENTH);
	memcpy(Msg,pMsg,len);

	if(m_iSocketTyp == 1)
		if(!send(ClientSocket,Msg, len, 0))
		{
			strLog += "err: " + Int2Str(WSAGetLastError());
			RT = FALSE;
		}
	
	if(m_iSocketTyp == 2)
		if(!sendto(m_sServer,Msg,len,0,(SOCKADDR*)&adClient,m_iServerLen))
		{
			strLog += "err: " + Int2Str(WSAGetLastError());
			RT = FALSE;
		}
	
	Log(strLog, 0, SOCKET_LOG_FILE_NAME);
	return RT;
}

BOOL MySocket::SendMsg2Srv(char * pMsg, int msgsize)
{
	/*CString strLog = "";
	CString strId = "";
	BOOL RT = TRUE;

	strId = (CString)inet_ntoa(m_adServer.sin_addr);

	strLog = "post msg to   " + strId + ": ";
	strLog += pMsg;

	if(m_iSocketTyp == 1)
		if(!send(m_sServer,pMsg,(int)strlen(pMsg),0))
		{
			strLog += "err: " + Int2Str(WSAGetLastError());
			RT = FALSE;
		}
	
	if(m_iSocketTyp == 2)
		if(!sendto(m_sServer,pMsg,(int)strlen(pMsg),0,(SOCKADDR*)&m_adServer,m_iServerLen))
		{
			if(!strcmp(pMsg,"")) return FALSE;
			strLog += "err: " + Int2Str(WSAGetLastError());
			RT = FALSE;
		}
	
	Log(strLog, 0, SOCKET_LOG_FILE_NAME);*/
	return SendMsg2Client(pMsg, m_adServer, m_sServer, msgsize);
}

UINT MySocket::SocketSrvThread_Tcp(LPVOID pSocket)
{
	int ClientRecv = 0;
	int lenth = sizeof(sockaddr_in);
	CString strLog = "";
	CString ClientAddr = "";

	MySocket * pMySocket = (MySocket *) pSocket;
	Log("SocketSrvThread_Tcp start!", 0, SOCKET_LOG_FILE_NAME);

	while(!pMySocket->CheckStop())
	{	
		pTcpThread TcpThreadInfo = new TcpThread();
		memset(TcpThreadInfo,0x00,sizeof(TcpThread));
		TcpThreadInfo->pMySocket = pMySocket;
		TcpThreadInfo->ClientSocket = accept(pMySocket->m_sServer,(struct sockaddr *)&(TcpThreadInfo->Address),&(pMySocket->m_iServerLen));
		if(pMySocket->CheckStop()) break;
		if(TcpThreadInfo->ClientSocket == SOCKET_ERROR || TcpThreadInfo->ClientSocket == INVALID_SOCKET)
		{
			if(WSAGetLastError() != WSAEINTR && !pMySocket->CheckStop())
				Log("recv msg err: " + Int2Str(WSAGetLastError()), 0, SOCKET_LOG_FILE_NAME);
		}else
		{
			strLog = "client " + (CString)inet_ntoa(TcpThreadInfo->Address.sin_addr) + " connected! thread id ";
			CWinThread * pThread = AfxBeginThread(SingleClientThread,(LPVOID)TcpThreadInfo);
			Log(strLog + Int2Str(pThread->m_nThreadID),0,SOCKET_LOG_FILE_NAME);
		}
	}

	CSingleLock SingleLock(&pMySocket->m_SrvMutex);	
	SingleLock.Lock();	
	Log("SocketSrvThread_Tcp end", 0, SOCKET_LOG_FILE_NAME);
	pMySocket->m_pSocketSrvThread = NULL;
	SingleLock.Unlock();

	return 0;
}

UINT MySocket::SocketSrvThread_Udp(LPVOID pSocket)
{
	int ClientRecv = 0;
	int lenth = sizeof(sockaddr_in);
	CString csRcvMsg = "";
	CString ClientAddr = "";
	SocketInfo SktInfo;
	MySocket * pMySocket = (MySocket *) pSocket;

	Log("SocketSrvThread_Udp start!", 0, SOCKET_LOG_FILE_NAME);
	while(!pMySocket->CheckStop())
	{		
		csRcvMsg = "recv msg from ";
		ClientAddr = "";
		memset(&SktInfo,0x00,sizeof(SocketInfo));
		ClientRecv = recvfrom(pMySocket->m_sServer,SktInfo.Msgstr,SOCKET_REV_BUFF_LENTH,0,(SOCKADDR*)&SktInfo.Address,&lenth);
		if(pMySocket->CheckStop()) break;
		if(ClientRecv == SOCKET_ERROR || ClientRecv == 0)
		{
			if(WSAGetLastError() != WSAEINTR && ClientRecv != 0)
				Log("recv msg err: " + Int2Str(WSAGetLastError()), 0, SOCKET_LOG_FILE_NAME);
		}else
		{
			ClientAddr = inet_ntoa(SktInfo.Address.sin_addr);
			csRcvMsg += ClientAddr + ": ";
			csRcvMsg += SktInfo.Msgstr;
			Log(csRcvMsg, 0, SOCKET_LOG_FILE_NAME);
			pMySocket->m_sClientList.AddTail(SktInfo);		
		}
	}

	CSingleLock SingleLock(&pMySocket->m_SrvMutex);	
	SingleLock.Lock();	
	Log("SocketSrvThread_Udp end", 0, SOCKET_LOG_FILE_NAME);
	pMySocket->m_pSocketSrvThread = NULL;
	SingleLock.Unlock();
	return 0;
}

UINT MySocket::SingleClientThread(LPVOID TcpThreadInfo)
{
	int ClientRecv = 0;
	int lenth = sizeof(sockaddr_in);
	CString csRcvMsg = "";
	CString ClientAddr = "";
	SocketInfo SktInfo;
	CString csThreadId = Int2Str(GetCurrentThreadId());
	pTcpThread ThreadInfo = (pTcpThread) TcpThreadInfo; 
	DuplicateHandle(GetCurrentProcess(),GetCurrentThread(),GetCurrentProcess(),&ThreadInfo->hThread,0,FALSE,DUPLICATE_SAME_ACCESS);
	ThreadInfo->pMySocket->m_sTcpThreadList.AddTail(*ThreadInfo);

	Log("Thread " + csThreadId + " start!",0,SOCKET_LOG_FILE_NAME);

	while(!ThreadInfo->pMySocket->CheckStop())
	{		
		csRcvMsg = "recv msg from ";
		ClientAddr = "";
		memset(&SktInfo,0x00,sizeof(SocketInfo));
		ClientRecv = recv(ThreadInfo->ClientSocket,SktInfo.Msgstr,SOCKET_REV_BUFF_LENTH,0);
		if(ThreadInfo->pMySocket->CheckStop()) break;
		if(ClientRecv == SOCKET_ERROR || ClientRecv == 0)
		{
			//if(WSAGetLastError() == WSAEINTR || WSAGetLastError() == WSAECONNRESET || WSAGetLastError() == WSAECONNABORTED || ClientRecv == 0)				
			//{
			Log("client socket err: "  + Int2Str(WSAGetLastError()), 0, SOCKET_LOG_FILE_NAME);
				break;
			//}
			//Log("recv msg err", 0, SOCKET_LOG_FILE_NAME);
		}else
		{
			SktInfo.ClientSocket = ThreadInfo->ClientSocket;
			SktInfo.Address = ThreadInfo->Address;
			ClientAddr = inet_ntoa(SktInfo.Address.sin_addr);
			csRcvMsg += ClientAddr + ": ";
			csRcvMsg += SktInfo.Msgstr;
			Log(csRcvMsg, 0, SOCKET_LOG_FILE_NAME);
			ThreadInfo->pMySocket->m_sClientList.AddTail(SktInfo);					
		}	
	}	

	CSingleLock SingleLock(&ThreadInfo->pMySocket->m_TcpThreadMutex);	
	SingleLock.Lock();
	Log("Thread " + csThreadId + " end!",0,SOCKET_LOG_FILE_NAME);
	ThreadInfo->pMySocket->m_sTcpThreadList.RemoveAt(ThreadInfo->pMySocket->m_sTcpThreadList.Find(*ThreadInfo));
	SingleLock.Unlock();
	delete ThreadInfo;
	return 1;
}

UINT MySocket::SocketClientThread(LPVOID pSocket)
{
	int ClientRecv = 0;
	int lenth = sizeof(sockaddr_in);
	CString csRcvMsg = "";
	CString ClientAddr = ""; 
	SocketInfo SktInfo;

	MySocket * pMySocket = (MySocket *) pSocket;
	Log("rcv socket thread start!", 0, SOCKET_LOG_FILE_NAME);

	if(pMySocket->m_iSocketTyp == 2) pMySocket->SendMsg2Srv("");

	while(!pMySocket->CheckStop())
	{		
		csRcvMsg = "recv msg from srv ";
		ClientAddr = "";
		memset(&SktInfo,0x00,sizeof(SocketInfo));
		if(pMySocket->m_iSocketTyp == 1) 
			ClientRecv = recv(pMySocket->m_sServer,SktInfo.Msgstr,SOCKET_REV_BUFF_LENTH,0);		
		else if(pMySocket->m_iSocketTyp == 2) 
			ClientRecv = recvfrom(pMySocket->m_sServer,SktInfo.Msgstr,SOCKET_REV_BUFF_LENTH,0,(SOCKADDR*)&SktInfo.Address,&lenth);

		if(pMySocket->CheckStop()) break;
		if(ClientRecv == SOCKET_ERROR || ClientRecv == 0)
		{
			int err = WSAGetLastError();
			Log("client socket err: "  + Int2Str(err), 0, SOCKET_LOG_FILE_NAME);
			if(err == WSAECONNRESET)
			{
				memcpy(SktInfo.Msgstr,"WSAECONNRESET",sizeof("WSAECONNRESET"));
				pMySocket->m_sClientList.AddTail(SktInfo);
			}
				break;
		}else
		{
			SktInfo.ClientSocket = pMySocket->m_sServer;
			if(pMySocket->m_iSocketTyp == 1) SktInfo.Address = pMySocket->m_adServer;
			ClientAddr = inet_ntoa(SktInfo.Address.sin_addr);
			csRcvMsg += ClientAddr + ": ";
			csRcvMsg += SktInfo.Msgstr;
			Log(csRcvMsg, 0, SOCKET_LOG_FILE_NAME);
			pMySocket->m_sClientList.AddTail(SktInfo);					
		}	
	}

	CSingleLock SingleLock(&pMySocket->m_SrvMutex);	
	SingleLock.Lock();
	Log("rcv socket thread end!",0,SOCKET_LOG_FILE_NAME);
	pMySocket->m_pSocketSrvThread = NULL;
	SingleLock.Unlock();
	return 0;
}



/*--------------------socketex----------------------------------*/
MySocketEx::MySocketEx(void)
{	
	m_iClientCount = 0;
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2,2);
	if(WSAStartup(wVersionRequested,&wsaData))
	{
		Log("WSAStartup Err: " + Int2Str(WSAGetLastError()), SOCKET_LOG_FILE_NAME);
		return;
	}
	if(LOBYTE(wsaData.wVersion)!= 2 || HIBYTE(wsaData.wVersion)!= 2)
	{
		Log("WSA Version Err: " + Int2Str(WSAGetLastError()), SOCKET_LOG_FILE_NAME);
		return;
	}
	m_Socket = 0;
}

MySocketEx::~MySocketEx(void)
{
	g_cs.Lock();
	int size = (int) m_arrayCliSocket.GetCount();
	for (int i=0; i<size; i++)
	{
		delete m_arrayCliSocket[i].wsabuf.buf;
	}
	m_arrayCliSocket.RemoveAll();
	g_cs.Unlock();
	WSACleanup();
}

BOOL MySocketEx::InitSocketSrv(int iPort, int iType, HWND hWnd, u_int iMsg, CString strHelp)
{
	m_bSrvOrCli = SOCKET_TYPE_SRV;
	m_iType = (iType ? SOCK_DGRAM : SOCK_STREAM);
	m_Socket = WSASocket(AF_INET,m_iType,0,NULL,0,0);
	m_hClientWnd = hWnd;
	if(INVALID_SOCKET == m_Socket)
	{
		Log("create socket err: " + Int2Str(WSAGetLastError()), 0, SOCKET_LOG_FILE_NAME);
		return FALSE;
	}

	BOOL bOptVal = TRUE;
	/* Set to enable reuse the address,or the bind() will result an error*/
	/*int rc = setsockopt(m_Socket, SOL_SOCKET, SO_REUSEADDR, (char *)&bOptVal, sizeof(int));
	if (rc == SOCKET_ERROR)
	{
		int nResult = GetLastError();
		if (m_Socket != INVALID_SOCKET)
		{
			m_Socket = INVALID_SOCKET;
		}
		WSASetLastError(nResult);
		return FALSE;
	}*/


    /*如果要已经处于连接状态的soket在调用closesocket后强制关闭，不经历
     TIME_WAIT状态的过程 */

	BOOL bDontLinger = FALSE;
	setsockopt(m_Socket,SOL_SOCKET,SO_DONTLINGER,(const char*)&bDontLinger,sizeof(BOOL));

	SOCKADDR_IN addrsock;
	addrsock.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrsock.sin_family = AF_INET;
	addrsock.sin_port = htons(iPort);

	if(SOCKET_ERROR == bind(m_Socket,(SOCKADDR*)&addrsock,sizeof(SOCKADDR)))
	{
		Log("bind socket err: " + Int2Str(WSAGetLastError()), 0, SOCKET_LOG_FILE_NAME);
		return FALSE;
	}

	if(m_iType == 1)
	{
		if(SOCKET_ERROR == listen(m_Socket, 5))		
		{
			Log("listen err:" + Int2Str(WSAGetLastError()), SOCKET_LOG_FILE_NAME);
			return FALSE;
		}
	}

	if(SOCKET_ERROR == WSAAsyncSelect(m_Socket,m_hClientWnd,iMsg,FD_READ | FD_CONNECT | FD_CLOSE | FD_ACCEPT))
	{
		Log("WSAAsyncSelect err(注册网络读取事件): " + Int2Str(WSAGetLastError()), 0, SOCKET_LOG_FILE_NAME);
		return FALSE;
	}

	return TRUE;
}

CString MySocketEx::GetIpAddr(SOCKET socket, sockaddr_in * sockAddr)
{
	int len = sizeof(SOCKADDR);
	getpeername(socket, (SOCKADDR*) sockAddr, &len);		
	CString rt = (CString)inet_ntoa(sockAddr->sin_addr);
	rt += ":";
	rt += Int2Str(ntohs(sockAddr->sin_port));
	return rt;
}

BOOL MySocketEx::_RecvMsgEx(SOCKET cliSocket, pClientSocket & pCliSocket)
{
	g_cs.Lock();
	int size = (int) m_arrayCliSocket.GetCount();
	for (int i=0; i<size; i++)
	{
		if(m_arrayCliSocket[i].cliSocket == cliSocket)
		{
			pCliSocket = &m_arrayCliSocket[i];
			DWORD dwFlag=0;
			WSABUF wsabuf;
			wsabuf.len = SOCKET_REV_BUFF_LENTH*SOCKET_REV_BUFF_LENTH;

			if (m_arrayCliSocket[i].bContinueRd)
				wsabuf.len = m_arrayCliSocket[i].iRdBufSize;
			else
				wsabuf.len = 40;

			wsabuf.buf = new char[wsabuf.len];			
			//ZeroMemory(wsabuf.buf,wsabuf.len);

			if(SOCKET_ERROR == WSARecv(cliSocket,&wsabuf,1,&wsabuf.len,&dwFlag,NULL,NULL))
			{
				Log("WSARecv Err: " + Int2Str(WSAGetLastError()), 0, SOCKET_LOG_FILE_NAME);
			}
			
			if (m_arrayCliSocket[i].bContinueRd)
			{
				int copySize = SOCKET_REV_BUFF_LENTH*SOCKET_REV_BUFF_LENTH - m_arrayCliSocket[i].wsabuf.len;
				copySize = ((int)wsabuf.len > copySize ? copySize : wsabuf.len);
				memcpy(m_arrayCliSocket[i].wsabuf.buf + m_arrayCliSocket[i].wsabuf.len,wsabuf.buf,copySize);
				m_arrayCliSocket[i].wsabuf.len += copySize;
			}else
			{
				int copySize = SOCKET_REV_BUFF_LENTH*SOCKET_REV_BUFF_LENTH;
				copySize = ((int)wsabuf.len > copySize ? copySize : wsabuf.len);
				//ZeroMemory(m_arrayCliSocket[i].wsabuf.buf,SOCKET_REV_BUFF_LENTH*SOCKET_REV_BUFF_LENTH);
				memcpy(m_arrayCliSocket[i].wsabuf.buf,wsabuf.buf,copySize);
				m_arrayCliSocket[i].wsabuf.len = copySize;
			}
			delete wsabuf.buf;
			g_cs.Unlock();
			return TRUE;
		}
	}
	g_cs.Unlock();
	return FALSE;
}

CString MySocketEx::_RecvMsg(SOCKET cliSocket, SOCKADDR_IN &addrFrom, WSABUF &wsabuf)
{
	CString str;
	int len = sizeof(SOCKADDR);

	if(m_iType == 1)
	{			
		DWORD dwFlag=0;
		if(SOCKET_ERROR == WSARecv(cliSocket,&wsabuf,1,&wsabuf.len,&dwFlag,NULL,NULL))
		{
			Log("WSARecv Err: " + Int2Str(WSAGetLastError()), 0, SOCKET_LOG_FILE_NAME);
		}			
		str = GetIpAddr(cliSocket,&addrFrom);
		str += " -> ";
		//str += wsabuf.buf;
	}
	else
	{
		cliSocket = 0;
		DWORD dwFlag = 0;
		if(SOCKET_ERROR == WSARecvFrom(m_Socket,&wsabuf,1,&wsabuf.len,&dwFlag,
			(SOCKADDR*)&addrFrom,&len,NULL,NULL))
		{
			Log("WSARecvFrom Err: " + Int2Str(WSAGetLastError()), 0, SOCKET_LOG_FILE_NAME);
		}
		str = inet_ntoa(addrFrom.sin_addr);
		str += ":";
		str += Int2Str(ntohs(addrFrom.sin_port));
		str += "->";
		str += wsabuf.buf;		
	}
	if(wsabuf.len == SOCKET_REV_BUFF_LENTH)
	{
		//Log("receive buf is too small!",0, SOCKET_LOG_FILE_NAME);
		//str = "---receive buf is too small!-----";
	}
	return str;
}

CString MySocketEx::OnSocket(WPARAM wParam,LPARAM lParam,SOCKET &cliSocket, SOCKADDR_IN &addrFrom, WSABUF &wsabuf)
{
	USES_CONVERSION;

	int len = sizeof(SOCKADDR);

	CString str,strold;	

	str = "";	

	switch(LOWORD(lParam))
	{
	case FD_READ:
		cliSocket = (SOCKET)wParam;
		str = _RecvMsg(cliSocket,addrFrom,wsabuf);
		break;
	case FD_CONNECT:
		str = "FD_CONNECT";
		break;
	case FD_ACCEPT:	
		cliSocket = WSAAccept(m_Socket,(SOCKADDR*)&addrFrom,&len,NULL,NULL);
		str += inet_ntoa(addrFrom.sin_addr);
		str += ":";
		str += Int2Str(ntohs(addrFrom.sin_port));
		str += " -> CONNECT";
		break;
	case FD_CLOSE:
		if(m_bSrvOrCli == SOCKET_TYPE_SRV)
			str = "Cli ";
		else
			str = "Srv ";
		cliSocket = (SOCKET)wParam;
		getpeername((SOCKET)wParam, (SOCKADDR*) &addrFrom, &len);		
		str += inet_ntoa(addrFrom.sin_addr);
		str += ":";
		str += Int2Str(ntohs(addrFrom.sin_port));
		str += " exit!";
		if (!cliSocket) 
		{
			closesocket(cliSocket);
			str += "(closesocket)";
		}
		break;
	}

	//::GetDlgItemText(m_hClientWnd,IDC_EDIT1,strold);
	//str = str +"\r\n"+ strold;
	//::SetDlgItemText(m_hClientWnd,IDC_EDIT1,str);
	//delete wsabuf.buf;
	return str;
}

CString MySocketEx::OnSocketEx(WPARAM wParam,LPARAM lParam,SOCKET &cliSocket, SOCKADDR_IN &addrFrom, pClientSocket & pCliSocket)
{
	USES_CONVERSION;

	int len = sizeof(SOCKADDR);

	CString str,strold;	

	str = "";	

	switch(LOWORD(lParam))
	{
	case FD_READ:
		cliSocket = (SOCKET)wParam;
		if(m_iType == 1)
		{
			_RecvMsgEx(cliSocket,pCliSocket);
		}
		break;
	case FD_CONNECT:
		str = "FD_CONNECT";
		break;
	case FD_ACCEPT:	
		cliSocket = WSAAccept(m_Socket,(SOCKADDR*)&addrFrom,&len,NULL,NULL);
		str += inet_ntoa(addrFrom.sin_addr);
		str += ":";
		str += Int2Str(ntohs(addrFrom.sin_port));
		str += " -> CONNECT";
		AddCliSocket2Array(cliSocket);
		break;
	case FD_CLOSE:
		if(m_bSrvOrCli == SOCKET_TYPE_SRV)
			str = "Cli ";
		else
			str = "Srv ";
		cliSocket = (SOCKET)wParam;
		getpeername((SOCKET)wParam, (SOCKADDR*) &addrFrom, &len);		
		str += inet_ntoa(addrFrom.sin_addr);
		str += ":";
		str += Int2Str(ntohs(addrFrom.sin_port));
		str += " exit!";
		DetCliSocket(cliSocket);
		if (cliSocket) 
		{
			closesocket(cliSocket);
			str += "(closesocket)";
		}
		break;
	}

	//::GetDlgItemText(m_hClientWnd,IDC_EDIT1,strold);
	//str = str +"\r\n"+ strold;
	//::SetDlgItemText(m_hClientWnd,IDC_EDIT1,str);
	//delete wsabuf.buf;
	return str;
}

void MySocketEx::CloseSocket()
{
	if(m_Socket) closesocket(m_Socket);
}

BOOL MySocketEx::SendSktMessage(WSABUF wsabuf, SOCKET Socket, SOCKADDR_IN *addrFrom)
{
	if(!wsabuf.len) return FALSE;
	BOOL RT = TRUE;
	if(m_iType == 1)
	{	 
		if(SOCKET_ERROR == WSASend(Socket,&wsabuf,1,&wsabuf.len,0,NULL,NULL))
		{
			Log("WSASend err: " + Int2Str(WSAGetLastError()), 0, SOCKET_LOG_FILE_NAME);
			RT = FALSE;
		}
	}
	else
	{	 
		if(SOCKET_ERROR == WSASendTo(m_Socket,&wsabuf,1,&wsabuf.len,0,(SOCKADDR*)addrFrom,sizeof(SOCKADDR),NULL,NULL))
		{
			Log("WSASendTo Err: " + Int2Str(WSAGetLastError()), 0, SOCKET_LOG_FILE_NAME);
			RT = FALSE;
		}
	}
	return RT;
}

BOOL MySocketEx::SendTcpMessage(WSABUF wsabuf, SOCKET Socket)
{
	BOOL RT = TRUE; 
	if(!wsabuf.len) return FALSE;
	if(m_iType != 1) return FALSE;
	
	if(SOCKET_ERROR == WSASend(Socket,&wsabuf,1,&wsabuf.len,0,NULL,NULL))
	{
		AfxMessageBox("Send message err: " + Int2Str(WSAGetLastError()));
		RT = FALSE;
	}
	return RT;
}

BOOL MySocketEx::SendUdpMessage(WSABUF wsabuf, SOCKADDR_IN addrFrom)
{
	BOOL RT = TRUE; 
	if(!wsabuf.len) return FALSE;
	if(m_iType != 2) return FALSE;

	if(SOCKET_ERROR == WSASendTo(m_Socket,&wsabuf,1,&wsabuf.len,0,(SOCKADDR*)&addrFrom,sizeof(SOCKADDR),NULL,NULL))
	{
		Log("WSASendTo Err: " + Int2Str(WSAGetLastError()), 0, SOCKET_LOG_FILE_NAME);
		RT = FALSE;
	}
	return RT;
}

BOOL MySocketEx::InitSocketClient(LPSTR pstrIP, int iPort, int iType, HWND hWnd, u_int iMsg, CString strHelp)
{
	return InitSocketClient(ntohl(inet_addr(pstrIP)), iPort, iType, hWnd, iMsg, strHelp);
}

BOOL MySocketEx::InitSocketClient(DWORD dwIp, int iPort, int iType, HWND hWnd, u_int iMsg, CString strHelp)
{
	m_bSrvOrCli = SOCKET_TYPE_CLI;
	m_iType = (iType ? SOCK_DGRAM : SOCK_STREAM);
	m_Socket = WSASocket(AF_INET,m_iType,0,NULL,0,0);
	m_hClientWnd = hWnd;
	if(INVALID_SOCKET == m_Socket)
	{
		Log("create socket err: " + Int2Str(WSAGetLastError()), 0, SOCKET_LOG_FILE_NAME);
		return FALSE;
	}

	m_addrSocket.sin_addr.S_un.S_addr = htonl(dwIp);
	m_addrSocket.sin_family = AF_INET;
	m_addrSocket.sin_port = htons(iPort);

	if(m_iType == 1)
	{
		if(SOCKET_ERROR == WSAConnect(m_Socket,(SOCKADDR*)&m_addrSocket,sizeof(SOCKADDR),0,0,NULL,NULL))
		{
			Log("WSAConnect err: " + Int2Str(WSAGetLastError()), 0, SOCKET_LOG_FILE_NAME);
			return FALSE;
		}
	}

	if(SOCKET_ERROR == WSAAsyncSelect(m_Socket,m_hClientWnd,iMsg,FD_READ | FD_CLOSE))
	{
		Log("WSAAsyncSelect err(注册网络读取事件): " + Int2Str(WSAGetLastError()), 0, SOCKET_LOG_FILE_NAME);
		return FALSE;
	}
	return TRUE;
}

BOOL MySocketEx::InitSocketClientEx(LPSTR pstrIP, int iPort, int iType, HWND hWnd, const int iMsgAdd)
{
	return InitSocketClientEx(ntohl(inet_addr(pstrIP)), iPort, iType, hWnd, iMsgAdd);
}

BOOL MySocketEx::InitSocketClientEx(DWORD dwIp, int iPort, int iType, HWND hWnd, const int iMsgAdd)
{
	m_bSrvOrCli = SOCKET_TYPE_CLI;
	m_iType = (iType ? SOCK_DGRAM : SOCK_STREAM);
	m_Socket = WSASocket(AF_INET,m_iType,0,NULL,0,0);
	m_hClientWnd = hWnd;
	if(INVALID_SOCKET == m_Socket)
	{
		Log("create socket err: " + Int2Str(WSAGetLastError()), 0, SOCKET_LOG_FILE_NAME);
		return FALSE;
	}

	m_addrSocket.sin_addr.S_un.S_addr = htonl(dwIp);
	m_addrSocket.sin_family = AF_INET;
	m_addrSocket.sin_port = htons(iPort);

	if(m_iType == 1)
	{
		if(SOCKET_ERROR == WSAConnect(m_Socket,(SOCKADDR*)&m_addrSocket,sizeof(SOCKADDR),0,0,NULL,NULL))
		{
			Log("WSAConnect err: " + Int2Str(WSAGetLastError()), 0, SOCKET_LOG_FILE_NAME);
			return FALSE;
		}
	}

	if(SOCKET_ERROR == WSAAsyncSelect(m_Socket,m_hClientWnd,WM_USER + iMsgAdd,FD_READ | FD_CLOSE))
	{
		Log("WSAAsyncSelect err(注册网络读取事件): " + Int2Str(WSAGetLastError()), 0, SOCKET_LOG_FILE_NAME);
		return FALSE;
	}
	return TRUE;
}

BOOL MySocketEx::SendMsgToSrv(WSABUF wsabuf)
{
	BOOL RT = TRUE;
	if(m_iType == 1)
	{
		if(SOCKET_ERROR == WSASend(m_Socket,&wsabuf,1,&wsabuf.len,0,NULL,NULL))
		{
			Log("WSASend Err: " + Int2Str(WSAGetLastError()), 0, SOCKET_LOG_FILE_NAME);
			RT = FALSE;
		}
		
	}else
	{
		if(SOCKET_ERROR == WSASendTo(m_Socket,&wsabuf,1,&wsabuf.len,0,(SOCKADDR*)&m_addrSocket,sizeof(SOCKADDR),NULL,NULL))
		{
			Log("WSASendTo Err: " + Int2Str(WSAGetLastError()), 0, SOCKET_LOG_FILE_NAME);
			RT = FALSE;
		}
	}
	return RT;
}

BOOL MySocketEx::AddCliSocket2Array( SOCKET cliSocket )
{
	g_cs.Lock();
	int size = (int) m_arrayCliSocket.GetCount();
	
	ClientSocket newItem;
	newItem.cliSocket = cliSocket;
	newItem.wsabuf.buf = new char[SOCKET_REV_BUFF_LENTH*SOCKET_REV_BUFF_LENTH];
	newItem.wsabuf.len = SOCKET_REV_BUFF_LENTH*SOCKET_REV_BUFF_LENTH;
	newItem.bContinueRd = FALSE;
	m_arrayCliSocket.Add(newItem);
	m_iClientCount = (int)m_arrayCliSocket.GetCount();
	g_cs.Unlock();
	return TRUE;
}

BOOL MySocketEx::DetCliSocket( SOCKET cliSocket )
{
	g_cs.Lock();
	int size = (int) m_arrayCliSocket.GetCount();
	for (int i=0; i<size; i++)
	{
		if(m_arrayCliSocket[i].cliSocket == cliSocket)
		{
			delete m_arrayCliSocket[i].wsabuf.buf;
			m_arrayCliSocket.RemoveAt(i);
			m_iClientCount = (int)m_arrayCliSocket.GetCount();
			g_cs.Unlock();
			return TRUE;
		}
	}
	g_cs.Unlock();
	return FALSE;
}

int MySocketEx::GetClientCount()
{
	return m_iClientCount;
}

/*--------------------AutoUpdate----------------------------------*/
AutoUpdate::AutoUpdate(void)
{
}

AutoUpdate::~AutoUpdate(void)
{}

BOOL AutoUpdate::CheckVersion()
{

	return FALSE;
}

BOOL AutoUpdate::CloseSingleFile(CString strFileName)
{
	CFileFind FileFind;
	if(!FileFind.FindFile(strFileName)) return TRUE;
	int i = 0;
	
	CString old = ".\\" + strFileName;
	CString newf =  ".\\Back\\" + strFileName;
	::CreateDirectory(".\\Back\\", NULL);

	while(!CopyFile(old,newf,FALSE))
	{
		i++;Sleep(1000);
		if(i>5) MsgBox("备份文件失败！请退出或关闭程序" + strFileName + "及便继续自动更新！");
		if(i>8) return FALSE;
	}
	i = 0;
	while(!DeleteFile(strFileName))
	{
		i++;Sleep(1000);if(i>5) MsgBox("删除文件失败！请退出或关闭程序" + strFileName + "及便继续自动更新！");if(i>8) return FALSE;
	}
	return TRUE;
}

BOOL AutoUpdate::DownLoadUpdate(CString pstrServer, CString pstrUserName, CString pstrPassword, int nPort, CString strFtpFolder, CString strFileName, CString strLocalFolder, CString ExceptFile)
{
	CString strErr = "";
	BOOL RT = DownloadFiles(pstrServer, pstrUserName, pstrPassword, nPort, strFtpFolder, strFileName, strLocalFolder, ExceptFile, strErr);
	return RT;
}

BOOL AutoUpdate::RunUpdate(LPSTR strExeName)
{
	RunExe(strExeName);
	return TRUE;
}
/*----------------------------xml--------------------------------*/
Xml::Xml()
{
	m_plDomDocument = NULL;
	m_pDocRoot = NULL;
	m_iShowLogMsg = 1;
	m_strLogFileName = "ReadXmlLog";
	Init();
}

BOOL Xml::Init()
{
	::CoInitialize(NULL);
	HRESULT hr = m_plDomDocument.CreateInstance(MSXML::CLSID_DOMDocument);
	if(!Err(hr)) return FALSE;
	return TRUE;
}

void Xml::DisplayChildren(HTREEITEM hParent, MSXML::IXMLDOMNodePtr pParent)
{
	HTREEITEM hItem = DisplayChild(hParent, pParent);
	MSXML::IXMLDOMNodePtr pChild = pParent->firstChild;
	for(;pChild != NULL;pChild = pChild->nextSibling)
		DisplayChildren(hItem, pChild);
}

HTREEITEM Xml::DisplayChild(HTREEITEM hParent, MSXML::IXMLDOMNodePtr pChild)
{
	CString strElement;
	//MSXML::IXMLDOMNamedNodeMapPtr pAttrMap=NULL;
	MSXML::IXMLDOMNodePtr  pmethodAttrItem=NULL;
	MSXML::IXMLDOMNamedNodeMapPtr methodpAttrs=NULL;

	int nodetype = (int)pChild->nodeType;
	if(MSXML::NODE_TEXT == pChild->nodeType){}
		//AfxMessageBox("text:" + pChild->text);
	else if(MSXML::NODE_COMMENT == pChild->nodeType) {}
	else{
		strElement = "ELEMENT:";
		strElement += (LPCTSTR)pChild->nodeName;
		strElement += "\r\n";		
		methodpAttrs = pChild->Getattributes();
		int count = methodpAttrs->Getlength();
		for(int i=0; i<count; i++)
		{
			methodpAttrs->get_item(i,&pmethodAttrItem);   
            CString strgetName =(_bstr_t)pmethodAttrItem->nodeName;   
            CString strgetValue=(_bstr_t)pmethodAttrItem->nodeTypedValue; 
			strElement += strgetName + " -> " + strgetValue + "\r\n";
		}
		AfxMessageBox(strElement);
	}	
	return hParent;
}

BOOL Xml::LoadXmlFile(CString strFilePath)
{
	variant_t vResult;
	vResult = m_plDomDocument->load((_bstr_t)strFilePath.AllocSysString());
	
	if(((bool)vResult) == TRUE)
	{
		_bstr_t bstrDocContents = m_plDomDocument->xml;
		m_strDocContents = (LPCTSTR)bstrDocContents;
		m_pDocRoot = m_plDomDocument->documentElement;
		//DisplayChildren(TVI_ROOT, m_pDocRoot);
		return TRUE;
	}else
	{
		_com_error er(vResult);
		//Log(er.ErrorMessage(),m_iShowLogMsg,m_strLogFileName);
		return FALSE;
	}
}

BOOL Xml::LoadXmlString(LPSTR lpstr)
{
	variant_t vResult;
	vResult = m_plDomDocument->loadXML(lpstr);
	
	if(((bool)vResult) == TRUE)
	{
		_bstr_t bstrDocContents = m_plDomDocument->xml;
		m_strDocContents = (LPCTSTR)bstrDocContents;
		m_pDocRoot = m_plDomDocument->documentElement;
		//DisplayChildren(TVI_ROOT, m_pDocRoot);
		return TRUE;
	}else
	{
		_com_error er(vResult);
		//Log(er.ErrorMessage(),m_iShowLogMsg,m_strLogFileName);
		return FALSE;
	}
}

BOOL Xml::FindSingleNode(CString strNodeName, int &iNodeType, CStringList &strAttrName, CStringList &strAttrValue, MSXML::IXMLDOMNodePtr pChild)
{
	CString nodename = m_strNodeName;
	MSXML::IXMLDOMNodePtr pChildNode;
	if(!pChild) pChild = m_pDocRoot;
	
	return GetNodeInfo(pChild->selectSingleNode((_bstr_t)strNodeName.AllocSysString()), nodename, iNodeType, strAttrName, strAttrValue);
}

BOOL Xml::FindSingleNode(CString strNodeName, CStringArray &strAttrName, CStringArray &strAttrValue, MSXML::IXMLDOMNodePtr pChild)
{
	int iNodeType;
	CString nodename = m_strNodeName;
	MSXML::IXMLDOMNodePtr pChildNode;
	if(!pChild) pChild = m_pDocRoot;

	return GetNodeInfo(SelectSingleNode(strNodeName,pChild), nodename, iNodeType, strAttrName, strAttrValue);
}

MSXML::IXMLDOMNodePtr Xml::SelectSingleNode(CString strNodeName, MSXML::IXMLDOMNodePtr pChild)
{
	if(!pChild) pChild = m_pDocRoot;
	return pChild->selectSingleNode((_bstr_t)strNodeName.AllocSysString());
}

BOOL Xml::GetNodeInfo(MSXML::IXMLDOMNodePtr pChild, CString &strNodeName, int &iNodeType, CStringList &strAttrName, CStringList &strAttrValue)
{
	if(!pChild) return FALSE;

	strAttrName.RemoveAll();
	strAttrValue.RemoveAll();

	CString strElement;
	//MSXML::IXMLDOMNamedNodeMapPtr pAttrMap=NULL;
	MSXML::IXMLDOMNodePtr  pmethodAttrItem=NULL;
	MSXML::IXMLDOMNamedNodeMapPtr methodpAttrs=NULL;

	strNodeName = (LPCTSTR)pChild->nodeName;
	iNodeType = (int)pChild->nodeType;

	if(MSXML::NODE_TEXT == iNodeType)
		AfxMessageBox("text:" + pChild->text);
	else if(MSXML::NODE_COMMENT == iNodeType) {}
	else{		
		methodpAttrs = pChild->Getattributes();
		int count = methodpAttrs->Getlength();
		for(int i=0; i<count; i++)
		{
			methodpAttrs->get_item(i,&pmethodAttrItem);   
            CString strgetName =(_bstr_t)pmethodAttrItem->nodeName;
			strAttrName.AddTail(strgetName);
            CString strgetValue=(_bstr_t)pmethodAttrItem->nodeTypedValue; 
			strAttrValue.AddTail(UnConvertXmlChar(strgetValue));
			//strAttrValue.AddTail(strgetValue);
			//strElement += strgetName + " -> " + strgetValue + "\r\n";
		}
		//AfxMessageBox(strElement);
	}	
	return TRUE;
}

BOOL Xml::GetNodeInfo(MSXML::IXMLDOMNodePtr pChild, CString &strNodeName, int &iNodeType, CStringArray &strAttrName, CStringArray &strAttrValue)
{
	if(!pChild) return FALSE;

	CString strElement;
	strAttrName.RemoveAll();
	strAttrValue.RemoveAll();

	//MSXML::IXMLDOMNamedNodeMapPtr pAttrMap=NULL;
	MSXML::IXMLDOMNodePtr  pmethodAttrItem=NULL;
	MSXML::IXMLDOMNamedNodeMapPtr methodpAttrs=NULL;

	strNodeName = (LPCTSTR)pChild->nodeName;
	iNodeType = (int)pChild->nodeType;

	if(MSXML::NODE_TEXT == iNodeType)
		AfxMessageBox("text:" + pChild->text);
	else if(MSXML::NODE_COMMENT == iNodeType) {}
	else{		
		methodpAttrs = pChild->Getattributes();
		int count = methodpAttrs->Getlength();
		for(int i=0; i<count; i++)
		{
			methodpAttrs->get_item(i,&pmethodAttrItem);   
            CString strgetName =(_bstr_t)pmethodAttrItem->nodeName;
			strAttrName.Add(strgetName);
            CString strgetValue=(_bstr_t)pmethodAttrItem->nodeTypedValue; 
			strAttrValue.Add(UnConvertXmlChar(strgetValue));
			//strElement += strgetName + " -> " + strgetValue + "\r\n";
		}
		//AfxMessageBox(strElement);
	}	
	return TRUE;
}

CString Xml::GetNodeAttrValue(MSXML::IXMLDOMNodePtr pChild, CString strAttrName)
{
	MSXML::IXMLDOMNamedNodeMapPtr methodpAttrs=NULL;
	MSXML::IXMLDOMNodePtr  pmethodAttrItem=NULL;
	CString rt = NULL;

	if(MSXML::NODE_TEXT == (int)pChild->nodeType)
		AfxMessageBox("text:" + pChild->text);
	else if(MSXML::NODE_COMMENT == (int)pChild->nodeType) {}
	else{		
		methodpAttrs = pChild->Getattributes();
		int count = methodpAttrs->Getlength();
		for(int i=0; i<count; i++)
		{
			methodpAttrs->get_item(i,&pmethodAttrItem);   
            CString strgetName =(_bstr_t)pmethodAttrItem->nodeName;
			if(!strgetName.CompareNoCase(strAttrName))
			{
				CString value = (_bstr_t)pmethodAttrItem->nodeTypedValue;
				rt = value;
				break;
			}
		}
	}
	return rt;
}

BOOL Xml::Err(HRESULT hr)
{
	if(FAILED(hr))
	{
		_com_error er(hr);
		Log(er.ErrorMessage(),m_iShowLogMsg,m_strLogFileName);
		return FALSE;
	}
	return TRUE;
}

void Xml::NodeInfo( MSXML::IXMLDOMNodePtr pChild )
{
	if(!pChild) return;
	CString strElement;
	//MSXML::IXMLDOMNamedNodeMapPtr pAttrMap=NULL;
	MSXML::IXMLDOMNodePtr  pmethodAttrItem=NULL;
	MSXML::IXMLDOMNamedNodeMapPtr methodpAttrs=NULL;

	int nodetype = (int)pChild->nodeType;
	if(MSXML::NODE_TEXT == pChild->nodeType)
		AfxMessageBox("text:" + pChild->text);
	else if(MSXML::NODE_COMMENT == pChild->nodeType) {}
	else{
		strElement = "ELEMENT:";
		strElement += (LPCTSTR)pChild->nodeName;
		strElement += "\r\n";		
		methodpAttrs = pChild->Getattributes();
		int count = methodpAttrs->Getlength();
		for(int i=0; i<count; i++)
		{
			methodpAttrs->get_item(i,&pmethodAttrItem);   
			CString strgetName =(_bstr_t)pmethodAttrItem->nodeName;   
			CString strgetValue=(_bstr_t)pmethodAttrItem->nodeTypedValue; 
			strElement += strgetName + " -> " + strgetValue + "\r\n";
		}
		AfxMessageBox(strElement);
	}		
}

CString Xml::GetSingleNodeContext( CString strNodeName )
{
	_bstr_t bstrNodeName;
	bstrNodeName = strNodeName.AllocSysString();
	MSXML::IXMLDOMNodePtr pChild = m_pDocRoot->selectSingleNode(bstrNodeName);
	if (!pChild) return "";
	CString strRT = pChild->text;
	return strRT;
}

CString Xml::ConvertXmlChar(CString strXml)
{
	strXml.Replace("<","&lt;");
	strXml.Replace(">","&gt;");
	strXml.Replace("&","&amp;");
	strXml.Replace("'","&apos;");
	strXml.Replace("\"","&quot;");
	return strXml;
}

CString Xml::UnConvertXmlChar(CString strXml)
{
	strXml.Replace("&lt;","<");
	strXml.Replace("&gt;",">");
	strXml.Replace("&amp;","&");
	strXml.Replace("&apos;","'");
	strXml.Replace("&quot;","\"");
	return strXml;
}
/*----------------------------srv--------------------------------*/

void CServiceModule::Init(_ATL_OBJMAP_ENTRY* p, HINSTANCE h, LPTSTR szServiceName, const GUID* plibid)
{
    m_bService = TRUE;

    //LoadString(h, nServiceNameID, m_szServiceName, sizeof(m_szServiceName) / sizeof(TCHAR));
	m_szServiceName = szServiceName;
    // set up the initial service status 
    m_hServiceStatus = NULL;
    m_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    m_status.dwCurrentState = SERVICE_STOPPED;
    m_status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    m_status.dwWin32ExitCode = 0;
    m_status.dwServiceSpecificExitCode = 0;
    m_status.dwCheckPoint = 0;
    m_status.dwWaitHint = 0;
}

LONG CServiceModule::Unlock()
{
    LONG l = CComModule::Unlock();
    if (l == 0 && !m_bService)
        PostThreadMessage(dwThreadID, WM_QUIT, 0, 0);
    return l;
}

BOOL CServiceModule::IsInstalled()
{
    BOOL bResult = FALSE;

    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

    if (hSCM != NULL)
    {
        SC_HANDLE hService = ::OpenService(hSCM, m_szServiceName, SERVICE_QUERY_CONFIG);
        if (hService != NULL)
        {
            bResult = TRUE;
            ::CloseServiceHandle(hService);
        }
        ::CloseServiceHandle(hSCM);
    }
    return bResult;
}

BOOL CServiceModule::Install(CString strIniPath)
{
	if (IsInstalled())
		return TRUE;

	SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCM == NULL)
	{
		MessageBox(NULL, _T("Couldn't open service manager"), m_szServiceName, MB_OK);
		return FALSE;
	}

	// Get the executable file path
	//TCHAR szFilePath[_MAX_PATH];
	//::GetModuleFileName(NULL, szFilePath, _MAX_PATH);

	CString strFile,strIniF, strIniT;
	GetSystemDirectory(strFile.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	strFile.ReleaseBuffer();
	CString strSystemPath = strFile;
	GetModuleFileName(NULL,strFile.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	strFile.ReleaseBuffer();
	CString strFilePath = strFile;

	strIniF = PraseFilePath(strFilePath,0) + PraseFilePath(strFilePath,1) + "\\" + strIniPath;
	strIniT = strSystemPath + "\\" + strIniPath;
	strFile = PraseFilePath(strFilePath,2) + PraseFilePath(strFilePath,3);
	strFile = strSystemPath + "\\" + strFile;

	if(strFile.CompareNoCase(strFilePath))
	{
		//Log("copyfile from " + m_strFilePath + " to " + strFile);
		DeleteFile(strFile);
		DeleteFile(strIniT);
		CopyFile(strFilePath,strFile,0);
		CopyFile(strIniF,strIniT,0);
	}

	SC_HANDLE hService = ::CreateService(
		hSCM, m_szServiceName, m_szServiceName,
		SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,
		SERVICE_AUTO_START, SERVICE_ERROR_NORMAL,
		strFile, NULL, NULL, _T("RPCSS\0"), NULL, NULL);

	if (hService == NULL)
	{
		::CloseServiceHandle(hSCM);
		MessageBox(NULL, _T("Couldn't create service"), m_szServiceName, MB_OK);
		return FALSE;
	}

	::CloseServiceHandle(hService);
	::CloseServiceHandle(hSCM);
	return TRUE;
}

BOOL CServiceModule::Install()
{
    if (IsInstalled())
        return TRUE;

    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (hSCM == NULL)
    {
        MessageBox(NULL, _T("Couldn't open service manager"), m_szServiceName, MB_OK);
        return FALSE;
    }

    // Get the executable file path
    //TCHAR szFilePath[_MAX_PATH];
    //::GetModuleFileName(NULL, szFilePath, _MAX_PATH);

	CString strFile;
	GetSystemDirectory(strFile.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	strFile.ReleaseBuffer();
	CString strSystemPath = strFile;
	GetModuleFileName(NULL,strFile.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	strFile.ReleaseBuffer();
	CString strFilePath = strFile;

	strFile = PraseFilePath(strFilePath,2) + PraseFilePath(strFilePath,3);
	strFile = strSystemPath + "\\" + strFile;

	if(strFile.CompareNoCase(strFilePath))
	{
		//Log("copyfile from " + m_strFilePath + " to " + strFile);
		DeleteFile(strFile);
		CopyFile(strFilePath,strFile,0);
	}

    SC_HANDLE hService = ::CreateService(
        hSCM, m_szServiceName, m_szServiceName,
        SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,
        SERVICE_AUTO_START, SERVICE_ERROR_NORMAL,
        strFile, NULL, NULL, _T("RPCSS\0"), NULL, NULL);

    if (hService == NULL)
    {
        ::CloseServiceHandle(hSCM);
        MessageBox(NULL, _T("Couldn't create service"), m_szServiceName, MB_OK);
        return FALSE;
    }

    ::CloseServiceHandle(hService);
    ::CloseServiceHandle(hSCM);
    return TRUE;
}

BOOL CServiceModule::Uninstall()
{
    if (!IsInstalled())
        return TRUE;

    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

    if (hSCM == NULL)
    {
        MessageBox(NULL, _T("Couldn't open service manager"), m_szServiceName, MB_OK);
        return FALSE;
    }

    SC_HANDLE hService = ::OpenService(hSCM, m_szServiceName, SERVICE_STOP | DELETE);

    if (hService == NULL)
    {
        ::CloseServiceHandle(hSCM);
        MessageBox(NULL, _T("Couldn't open service"), m_szServiceName, MB_OK);
        return FALSE;
    }
    SERVICE_STATUS status;
    ::ControlService(hService, SERVICE_CONTROL_STOP, &status);

    BOOL bDelete = ::DeleteService(hService);
    ::CloseServiceHandle(hService);
    ::CloseServiceHandle(hSCM);

    if (bDelete)
        return TRUE;

    MessageBox(NULL, _T("Service could not be deleted"), m_szServiceName, MB_OK);
    return FALSE;
}

void CServiceModule::StartMyService()
{
    SC_HANDLE scm = NULL, service = NULL;
    scm = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );
    if ( !scm ){
		MsgBox("err in OpenSCMager: " + Int2Str(GetLastError()));       
        return;
    }

    service = OpenService(scm, m_szServiceName, SERVICE_ALL_ACCESS );
    if ( !service ){
		MsgBox("err in OpenService: " + Int2Str(GetLastError()));
        return;
    }

	::StartService(service, 0, NULL);

    CloseServiceHandle( service );
    CloseServiceHandle( scm );
}

///////////////////////////////////////////////////////////////////////////////////////
// Logging functions
void CServiceModule::LogEvent(LPCTSTR pFormat, ...)
{
    TCHAR    chMsg[256];
    HANDLE  hEventSource;
    LPTSTR  lpszStrings[1];
    va_list pArg;

    va_start(pArg, pFormat);
    _vstprintf(chMsg, pFormat, pArg);
    va_end(pArg);

    lpszStrings[0] = chMsg;

    if (m_bService)
    {
        /* Get a handle to use with ReportEvent(). */
        hEventSource = RegisterEventSource(NULL, m_szServiceName);
        if (hEventSource != NULL)
        {
            /* Write to event log. */
            ReportEvent(hEventSource, EVENTLOG_INFORMATION_TYPE, 0, 0, NULL, 1, 0, (LPCTSTR*) &lpszStrings[0], NULL);
            DeregisterEventSource(hEventSource);
        }
    }
    else
    {
        // As we are not running as a service, just write the error to the console.
        _putts(chMsg);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Service startup and registration
void CServiceModule::Start()
{
    SERVICE_TABLE_ENTRY st[] =
    {
		{ m_szServiceName.GetBuffer(), _ServiceMain },
        { NULL, NULL }
    };
    if (m_bService && !::StartServiceCtrlDispatcher(st))
    {
        m_bService = FALSE;
    }
    if (m_bService == FALSE)
        Run();
}

inline void CServiceModule::ServiceMain(DWORD /* dwArgc */, LPTSTR* /* lpszArgv */)
{
    // Register the control request handler
    m_status.dwCurrentState = SERVICE_START_PENDING;
    m_hServiceStatus = RegisterServiceCtrlHandler(m_szServiceName, _Handler);
    if (m_hServiceStatus == NULL)
    {
        LogEvent(_T("Handler not installed"));
        return;
    }
    SetServiceStatus(SERVICE_START_PENDING);

    m_status.dwWin32ExitCode = S_OK;
    m_status.dwCheckPoint = 0;
    m_status.dwWaitHint = 0;

    // When the Run function returns, the service has stopped.
    Run();

    SetServiceStatus(SERVICE_STOPPED);
    LogEvent(_T("Service stopped"));
}

inline void CServiceModule::Handler(DWORD dwOpcode)
{
    switch (dwOpcode)
    {
    case SERVICE_CONTROL_STOP:
        SetServiceStatus(SERVICE_STOP_PENDING);
        PostThreadMessage(dwThreadID, WM_QUIT, 0, 0);
        break;
    case SERVICE_CONTROL_PAUSE:
        break;
    case SERVICE_CONTROL_CONTINUE:
        break;
    case SERVICE_CONTROL_INTERROGATE:
        break;
    case SERVICE_CONTROL_SHUTDOWN:
        break;
    default:
        LogEvent(_T("Bad service request"));
    }
}

void WINAPI CServiceModule::_ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
{
    _Module.ServiceMain(dwArgc, lpszArgv);
}
void WINAPI CServiceModule::_Handler(DWORD dwOpcode)
{
    _Module.Handler(dwOpcode); 
}

void CServiceModule::SetServiceStatus(DWORD dwState)
{
    m_status.dwCurrentState = dwState;
    ::SetServiceStatus(m_hServiceStatus, &m_status);
}

/*-------------------用法--------------------------
在主程序（非对话框）的cpp中添加

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()

void CServiceModule::Run()
{
    _Module.dwThreadID = GetCurrentThreadId();
    LogEvent(_T("Service started"));
    if (m_bService)
        SetServiceStatus(SERVICE_RUNNING);

	CASEDlg dlg;
	theApp.m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		
	}
	else if (nResponse == IDCANCEL)
	{
		
	}

    //MSG msg;
    //while (GetMessage(&msg, 0, 0, 0))
    //   DispatchMessage(&msg);
}

BOOL CXXXApp::InitInstance()
{
	...

	_Module.Init(ObjectMap, this->m_hInstance, "ASE_SRV", NULL);

	if(!_Module.IsInstalled())
	{
		if(CheckMsgBox("即将在您计算机上安装ASE_SRV服务，请确认是否安装该服务?"))
		if(!_Module.Install())	MsgBox("安装失败！");
		if(CheckMsgBox("安装成功，是否现在启动服务?"))
			_Module.StartMyService();
		return FALSE;
	}

    _Module.m_bService = TRUE;
	_Module.Start();

	return FALSE;
}
-------------------用法--------------------------*/

/*---------------------http-code------------------------*/
HttpCode::HttpCode()
{
	m_csPath = "";
	m_csServer = "";
	m_csErr = "";
	m_csContent = "";
	m_iReTryCount = 1;
	m_iReadFileSize = 16;
	m_iBufSize = 1024*100;
	m_iEncoding = CP_THREAD_ACP;
	m_lpszBuf = new char[m_iBufSize];
	m_isizeofbuf = 0;
	ZeroMemory(m_lpszBuf,m_iBufSize);
	FreeHd();
	CoInit();
}

HttpCode::~HttpCode()
{
	delete m_lpszBuf;
	CoUninit();
	if(m_hHSession!=NULL) ::InternetCloseHandle(m_hHSession);
}


BOOL HttpCode::SetServer(CString Server)
{
	if(Server.GetLength() < 1)
	{
		Log(Server + " err.",m_bIsShow);
		return FALSE;
	}else
	{
		m_csServer = Server;

		if(m_hHSession != NULL)	::InternetCloseHandle(m_hHSession);		
		//if(m_hHConnect != NULL)	::InternetCloseHandle(m_hHConnect);
		m_hHSession = NULL;
		m_hHConnect = NULL;
		m_hHSession = ::InternetOpen("raw html reader",PRE_CONFIG_INTERNET_ACCESS,NULL,INTERNET_INVALID_PORT_NUMBER,0);   
		if(m_hHSession==NULL)   
		{   
			Log(Server + " :Internetopen failed!",m_bIsShow);
			::InternetCloseHandle(m_hHSession);
			return FALSE;
		}     
		m_hHConnect=::InternetConnect(m_hHSession,m_csServer,INTERNET_INVALID_PORT_NUMBER,NULL,NULL,INTERNET_SERVICE_HTTP,0,0);   
		if(m_hHConnect==NULL)   
		{   
			Log(Server + " :InternetConnect failed!",m_bIsShow);
			::InternetCloseHandle(m_hHSession);
			return FALSE;
			//::InternetCloseHandle(m_hHConnect);
		}
	}
	return TRUE;
}

BOOL HttpCode::SetServer(CString Server, int Port)
{
	if(Server.GetLength() < 1)
	{
		Log(Server + " err.",m_bIsShow);
		return FALSE;
	}else
	{
		m_csServer = Server;

		if(m_hHSession != NULL)	::InternetCloseHandle(m_hHSession);		
		//if(m_hHConnect != NULL)	::InternetCloseHandle(m_hHConnect);
		m_hHSession = NULL;
		m_hHConnect = NULL;
		m_hHSession = ::InternetOpen("raw html reader",PRE_CONFIG_INTERNET_ACCESS,NULL,INTERNET_INVALID_PORT_NUMBER,0);   
		if(m_hHSession==NULL)   
		{   
			Log(Server + " :Internetopen failed!",m_bIsShow);
			::InternetCloseHandle(m_hHSession);
			return FALSE;
		}     
		m_hHConnect=::InternetConnect(m_hHSession,m_csServer,Port,NULL,NULL,INTERNET_SERVICE_HTTP,0,0);   
		if(m_hHConnect==NULL)   
		{   
			Log(Server + " :InternetConnect failed!",m_bIsShow);
			::InternetCloseHandle(m_hHSession);
			return FALSE;
			//::InternetCloseHandle(m_hHConnect);
		}
	}
	return TRUE;
}


void HttpCode::SetEncoding(int iEncoding, CString csHelp)
{
	m_iEncoding = iEncoding;
}
BOOL HttpCode::SetCookie(CString csUrl, CString csCookieName, CString csCookieData)
{
	BOOL rt = InternetSetCookie(csUrl,csCookieName,csCookieData);		//设置cookie
	if(!rt) MsgBox("SetCookie failed!");
	return rt;
}
CString HttpCode::GetCookie(CString csUrl)
{
	DWORD dwSize = 0;
	LPSTR lpszData = NULL;
	LPSTR pwStr= NULL;
	lpszData = new char[114];
	BOOL GetCookieOk=InternetGetCookie(csUrl, NULL,(LPSTR)lpszData, &dwSize);
	if(GetCookieOk == FALSE) 
	{
		DWORD err = GetLastError();
		if(err == ERROR_INSUFFICIENT_BUFFER) 
			pwStr = new char[dwSize];
		else
		{
			MsgBox("err:" + Int2Str(err));
			return "";
		}
	}
	
	delete lpszData;
	GetCookieOk = InternetGetCookie(csUrl, NULL, pwStr, &dwSize); 
	if(GetCookieOk == FALSE) 
	{
		DWORD err = GetLastError();
		MsgBox("err:" + Int2Str(err));
	}
	CString strValue = (CString)pwStr;
	delete pwStr;
	return strValue;
}
BOOL HttpCode::SetPath(CString Path)
{
	if(Path.GetLength() < 1)
	{
		Log(Path + " err.",m_bIsShow);
		return FALSE;
	}else
		m_csPath = Path;
	return TRUE;
}

BOOL HttpCode::DownLoadFile(CString webPath, CString ToPath)
{
	return FALSE;
}

BOOL HttpCode::GetHtmlCode(CString Path, BOOL savebuf ,CString Type)
{
	SetPath(Path);
	if(m_csPath.GetLength() < 0)
	{
		Log(Path + " err!"),m_bIsShow;
		return FALSE;
	}
	Log(Path,m_bIsShow,"GetIp.Log");
	/*LPSTR type = new CHAR[10];
	ZeroMemory(type,10);
	strcpy(type,"*//*");
	USES_CONVERSION;
	LPSTR LPSTR = A2W(type);

	LPCWSTR * pstr = new LPCWSTR[1];
	pstr[0] = (LPCWSTR)LPSTR;*/
	HINTERNET hHttpFile=::HttpOpenRequest(m_hHConnect,Type,m_csPath,HTTP_VERSION,NULL,NULL,INTERNET_FLAG_DONT_CACHE,0);
	if(hHttpFile==NULL) 
	{
		::InternetCloseHandle(hHttpFile);   
		Log(Path + " :call HttpOpenRequest err!",m_bIsShow);
		return FALSE;
	}	

	BOOL bSend=::HttpSendRequest(hHttpFile,NULL,0,0,0);
	if(!bSend)
	{
		int k = 0;
		while(!bSend)
		{
			Log(Path + " :HttpSendRequest err!",m_bIsShow);
			Sleep(100);
			bSend=::HttpSendRequest(hHttpFile,NULL,0,0,0);
			k++;
			if(k > m_iReTryCount)
				break;
		}
		if(!bSend)
		{
			CString Err= "";
			DWORD dw = GetLastError();
			Err.Format(_T(":%d"),dw);
			Log(Path + " :Connect Web err " + Err,m_bIsShow);
			::InternetCloseHandle(hHttpFile);
			return FALSE;
		}
	}
	else
	{   
		DWORD dwFileSize;   
		DWORD dwQueryBufLen=(DWORD)100; 
		dwFileSize=(DWORD)1024 * m_iReadFileSize;
		char *lpszBuf=new char[dwFileSize*100+1]; 
		DWORD dwBytesRead;
		DWORD dwBytesReadCount = 0;

		BOOL bRead=::InternetReadFile(hHttpFile,lpszBuf,dwFileSize+1,&dwBytesRead);
		while(dwBytesRead && bRead)
		{
			dwBytesReadCount += dwBytesRead;
			bRead=::InternetReadFile(hHttpFile,lpszBuf + dwBytesReadCount,dwFileSize+1,&dwBytesRead);			
		}

		/*char *pBuf=new char[256]; 
		DWORD BytesRead = 256;
		::HttpQueryInfo(hHttpFile,HTTP_QUERY_COOKIE,pBuf,&BytesRead,0);	*/
		if(savebuf)	SaveFile(lpszBuf,dwBytesReadCount,"wb","yzm.gif");
		ZeroMemory(m_lpszBuf,m_iBufSize);
		memcpy(m_lpszBuf,lpszBuf,dwBytesReadCount);
		m_isizeofbuf = dwBytesReadCount;
		

		if(bRead)
		{
			CString ContentCopy = "";
			if(m_iEncoding == CP_UTF8)
			{
				DWORD dwNum = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)lpszBuf, -1, NULL, 0);
				WCHAR * lpwchar=new WCHAR[dwNum+1];
				int nUtfLen = MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,(LPCSTR)lpszBuf,-1,lpwchar, dwNum+1);
				ContentCopy = lpwchar;
				m_csContent = ContentCopy;
				delete lpwchar;
			}else{
				ContentCopy = lpszBuf;
			}			
			int Point = 0;
			Point = ContentCopy.Find("</html>",0);
			if(Point == -1) 
			{
				m_csContent = ContentCopy.Left(Point + 7);
				/*Log(Path + " :not find </html>");
				return FALSE;*/
			}else
				//m_csContent = ContentCopy;
				m_csContent = ContentCopy.Left(Point + 7);

			if(m_csContent.IsEmpty())
			{
				Log(Path + " :content is empty!",m_bIsShow);
				return FALSE;
			}

			if(m_csContent.Find("找不到服务器",0)>0) 
			{
				Log(Path + " :找不到服务器",m_bIsShow);
				return FALSE;
			}
			if(m_csContent.Find("无法找到该页",0)>0)
			{
				Log(Path + " :无法找到该页",m_bIsShow);
				return FALSE;
			}
			if(m_csContent.Find("应用程序中的服务器错误",0)>0)
			{
				Log(Path + " :web应用程序中的服务器错误",m_bIsShow);
				return FALSE;
			}
			if(m_csContent.Find("HTTP 404",0)>0)
			{
				Log(Path + " :HTTP 404",m_bIsShow);
				return FALSE;
			}
		}else
		{
			m_csContent = "";
			::InternetCloseHandle(hHttpFile);
			Log(Path + " :Read Web Code err",m_bIsShow);
			return FALSE;
		}
		delete lpszBuf;	
	}
	::InternetCloseHandle(hHttpFile);
	return TRUE;
}

CString HttpCode::ShowHtmlCode()
{
	return m_csContent;
}
void HttpCode::FreeHd()
{
	//if(pDoc2) pDoc2->close();
	//if(pDoc2Tp) pDoc2Tp->close();

	pCollectionTemp = NULL; 
	pCollection = NULL;
	pDoc2 = NULL;
	pDoc3 = NULL;
	pDoc2Tp = NULL;
	pDoc3Tp = NULL;
	pElement = NULL;
}
BOOL HttpCode::CoInit()
{
	//FreeHd();
	HRESULT hr = 0;
	m_csErr.Empty();
	hr = CoInitialize(NULL);	
	if( FAILED( hr = CoCreateInstance(CLSID_HTMLDocument, NULL, CLSCTX_INPROC_SERVER,IID_IHTMLDocument2, (void**)&pDoc2 )))		
	{
		Log("CoCreateInstance False: " + Int2Str((int)hr),m_bIsShow);
		m_csErr = "CoCreateInstance False: " + Int2Str((int)hr);
		return FALSE;
	}
	if( FAILED( hr = CoCreateInstance(CLSID_HTMLDocument, NULL, CLSCTX_INPROC_SERVER,IID_IHTMLDocument2, (void**)&pDoc2Tp)))
	{
		Log("CoCreateInstance False: " + Int2Str((int)hr),m_bIsShow);
		m_csErr = "CoCreateInstance False: " + Int2Str((int)hr);
		return FALSE;
	}
	return TRUE;
}

void HttpCode::CoUninit()
{
	FreeHd();
	CoUninitialize();
}

void HttpCode::WriteToDoc(bstr_t content,MSHTML::IHTMLDocument2Ptr pDoc)
{	
	HRESULT hr = 0;
	SAFEARRAY* psa;
	VARIANT * param;
	bstr_t bsData = "";
	psa = SafeArrayCreateVector(VT_VARIANT, 0, 1); 
	bsData = content; 
	hr = SafeArrayAccessData(psa, (LPVOID*)&param); 
	param->vt = VT_BSTR; 
	param->bstrVal = (BSTR)bsData; 
	hr = pDoc->write(psa); 
	hr = pDoc->close(); 
	SafeArrayDestroy(psa);
}

HRESULT HttpCode::GetIframeDocument2Ptr( MSHTML::IHTMLElementPtr pElement, MSHTML::IHTMLDocument2Ptr &pDoc2, CComPtr<IDispatch> &disp )
{
	CComPtr<IWebBrowser2> browser;
	HRESULT hr = pElement->QueryInterface(IID_IWebBrowser2,(void**)&browser);
	if (hr == S_OK) 
	{ 					
		browser->get_Document(&disp);
		hr = disp->QueryInterface( IID_IHTMLDocument2,(void **)&pDoc2);
		return hr;	
	}else
		return S_FALSE;	
}

void HttpCode::SetShowLogIf( BOOL bShow )
{
	m_bIsShow = bShow;
}
/*---------------------socket------------------------*/

BOOL CEcFile::EcFile(LPCTSTR fpath)
{
	char *data;
	CFile *file;
	DWORD flen;

	__int64 password = epass();

	file = new CFile;
	if ( !file->Open(fpath, CFile::shareDenyNone|CFile::modeReadWrite))
	{
		return FALSE;
	}

	flen = (DWORD)file->GetLength();
	data = new char[(int)flen];

	file->SeekToBegin();
	file->Read(data, flen);

	for(int i=0; i<(int)flen; i++)
	{
		data[i] ^= password;
		data[i] ^= flen;
	}

	file->SeekToBegin();
	file->Write(data, flen);
	delete[] data;

	//添加密码验证信息
	char cpass[5] = "love";
	for(int j=0; j<5; j++)
	{
		cpass[j] ^= password;
	}
	file->SeekToEnd();
	file->Write(&cpass, 5);
	file->Close();
	delete file;

	return TRUE;
}

BOOL CEcFile::DcFile(LPCTSTR fpath)
{
	char *data;
	CFile *file;
	DWORD flen;
	char love[5];

	file = new CFile;
	if(!file->Open(fpath, CFile::shareDenyNone|CFile::modeReadWrite))
	{
		return FALSE;
	}

	flen =(DWORD)file->GetLength();
	data = new char[(int)flen];

	//检验密码是不是正确
	file->Seek(-5, CFile::end);
	file->Read(&love, 5);

	__int64 password = epass();

	for(int i=0; i<5; i++)
	{
		love[i] ^= password;
	}

	if(strcmp(love, "love")!=0)
	{
		file->Close();
		return FALSE;
	}

	//解密
	file->SeekToBegin();
	file->Read(data, flen);

	for(int j=0; j<(int)flen; j++)
	{
		data[j] ^= password;
		data[j] ^= (flen-5);
	}
	file->SeekToBegin();
	file->Write(data, flen);
	file->SetLength(flen-5);
	file->Close();

	delete[] data;
	delete file;
	return TRUE;
}


//获得密码的函数
__int64 CEcFile::epass()
{
	DWORD plen;
	char *ppass;
	__int64 mc= 8757735233305;

	ppass = "PASS";

	plen = (DWORD)strlen(ppass);

	for(int i=0; i<(int)plen; i++)
	{
		mc ^= ppass[i]|128;
	}
	return mc;
}

CString MyDB::GetLastErr()
{
	return m_strLastErr;
}

/************************************************************************/
/*                           vc-excel                                   */
/************************************************************************/
CString CExcel::GetExcelDriver(CString strFiter)
{
	CHAR szBuf[2001]; 
	WORD cbBufMax = 2000; 
	WORD cbBufOut; 
	CHAR *pszBuf = szBuf; 
	CString sDriver; 

	if (!SQLGetInstalledDrivers(szBuf, cbBufMax, &cbBufOut)) 
		return FALSE; 

	do 
	{ 
		CString strTemp;
		strTemp = pszBuf;
		//Log(strTemp,0,"dirves");
		if (strTemp.Find(strFiter) != -1) 
		{
			sDriver = pszBuf;
			break; 
		} 
		pszBuf = strchr(pszBuf, '\0') + 1; 
	} 
	while (pszBuf[1] != '\0'); 

	return sDriver; 
}

BOOL CExcel::GetExcelFields(CString strDriver, CString strFile, CStringArray &arrayFields, CString strTable)
{
	arrayFields.RemoveAll();
	CDatabase database; 
	CString sSql; 
	CString sDsn; 

	if (strDriver.IsEmpty()) 
	{ 
		// 没有发现Excel驱动 
		AfxMessageBox("没有安装Excel驱动,请确认您的计算机上安装了MS OFFICE EXCEL!"); 
		return FALSE; 
	} 

	// 创建进行存取的字符串 
	sDsn.Format("ODBC;DRIVER={%s};DSN='';DBQ=%s;Pwd=yourscrm2009", strDriver, strFile); 

	try 
	{ 
		// 打开数据库(既Excel文件) 
		database.Open(NULL, false, false, sDsn); 
		CRecordset recset(&database); 

		// 设置读取的查询语句. 
		sSql = "SELECT top 1 * FROM [" + strTable + "$]"; 

		// 执行查询语句 
		recset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly); 

		int excelColCount=recset.GetODBCFieldCount();//列数
		//得到记录集的字段集合中的字段的总个数  
		for(int i=0;i<excelColCount;i++)   
		{
			CODBCFieldInfo fieldinfo;
			recset.GetODBCFieldInfo(i,fieldinfo);
			arrayFields.Add(fieldinfo.m_strName);
		}
		recset.Close();
		database.Close(); 
	} 
	catch(CDBException* e) 
	{ 
		AfxMessageBox("数据库错误: " + e->m_strError); 
	} 
	return TRUE;
}

BOOL CExcel::GetExcelDataCount(CString strDriver, CString strFile, CString strTable)
{
	CDatabase database; 
	CString sSql; 
	CString sDsn; 

	if (strDriver.IsEmpty()) 
	{
		AfxMessageBox("没有安装Excel驱动,请确认您的计算机上安装了MS OFFICE EXCEL!"); 
		return 0; 
	}
	sDsn.Format("ODBC;DRIVER={%s};DSN='';DBQ=%s", strDriver, strFile); 
	try 
	{
		database.Open(NULL, false, false, sDsn); 
		CRecordset recset(&database); 
		sSql = "SELECT count(*) FROM [" + strTable + "$]"; 
		recset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly); 
		int excelColCount=recset.GetODBCFieldCount();
		CDBVariant GetValue;
		CString strValue;
		while (!recset.IsEOF()) 
		{
			try{
				recset.GetFieldValue((short)0, GetValue);
			}catch(CDBException* e ){			
				CString m_csErr = "获取值失败：" + e->m_strError;
				Log(m_csErr);
				recset.Close();
				database.Close(); 
				return 0;
			}
			recset.Close();
			database.Close(); 
			return (int)GetValue.m_lVal;
		}
	} 
	catch(CDBException* e) 
	{ 
		AfxMessageBox("数据库错误: " + e->m_strError);
		return 0;
	}
	return TRUE;
}

/************************************************************************/
/*                       jpg文件读取类                                  */
/************************************************************************/
CLoadJpg::CLoadJpg()
{
	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);
	m_pImage = NULL;
	m_graphics = NULL;
}

CLoadJpg::~CLoadJpg()
{
	if(m_pImage) delete m_pImage;
}

BOOL CLoadJpg::LoadJpgFile( CString strFilePath )
{
	USES_CONVERSION;
	if(m_pImage) delete m_pImage;
	m_pImage = Gdiplus::Image::FromFile(T2W(strFilePath.GetBuffer()),FALSE);
	return m_pImage ? TRUE : FALSE;
}

Gdiplus::Image* CLoadJpg::LoadJpgFileEx( CString strFilePath )
{
	USES_CONVERSION;
	return Gdiplus::Image::FromFile(T2W(strFilePath.GetBuffer()),FALSE);
}

void CLoadJpg::LoadHDC( HDC hdc )
{
	if (m_graphics) delete m_graphics;
	m_graphics = new Gdiplus::Graphics(hdc);
}

BOOL CLoadJpg::DrawImage( HDC hdc, int x,int y,int width,int height )
{
	Gdiplus::Graphics graphics = hdc;
	return !((BOOL)(int)graphics.DrawImage(m_pImage, x,y,width,height));
}

BOOL CLoadJpg::DrawImage( HDC hdc, Gdiplus::Image* pImage, int x,int y,int width,int height )
{
	Gdiplus::Graphics graphics = hdc;
	return !((BOOL)(int)graphics.DrawImage(pImage, x,y,width,height));
}

BOOL CLoadJpg::DrawImage( int x,int y,int width,int height )
{
	if (!m_graphics || !m_pImage) return FALSE;
	return !((BOOL)(int)m_graphics->DrawImage(m_pImage, x,y,width,height));
}

BOOL CLoadJpg::DrawImage( Gdiplus::Image* pImage, int x,int y,int width,int height )
{
	if (!m_graphics || !m_pImage) return FALSE;
	return !((BOOL)(int)m_graphics->DrawImage(pImage, x,y,width,height));
}

BOOL CLoadJpg::DrawImage( CRect rect )
{
	return DrawImage(rect.left,rect.top,rect.Width(),rect.Height());
}

BOOL CLoadJpg::DrawImage( HDC hdc, CRect rect )
{
	return DrawImage(hdc,rect.left,rect.top,rect.Width(),rect.Height());
}

BOOL CLoadJpg::DrawImage( Gdiplus::Image* pImage, CRect rect )
{
	return DrawImage(pImage,rect.left,rect.top,rect.Width(),rect.Height());
}

BOOL CLoadJpg::DrawImage( HDC hdc, Gdiplus::Image* pImage, CRect rect )
{
	return DrawImage(hdc,pImage,rect.left,rect.top,rect.Width(),rect.Height());
}
void CLoadJpg::ReleaseHDC( Gdiplus::Graphics &graphics, HDC hdc )
{
	graphics.ReleaseHDC(hdc);
}

void CLoadJpg::ReleaseHDC( HDC hdc )
{
	if (!m_graphics) return;
	m_graphics->ReleaseHDC(hdc);
}