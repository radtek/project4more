// AutoUpdater.cpp: implementation of the CAutoUpdater class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoUpdater.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define TRANSFER_SIZE 4096

CAutoUpdater::CAutoUpdater()
{
	// Initialize WinInet
	hInternet = InternetOpen("AutoUpdateAgent", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);	
}

CAutoUpdater::~CAutoUpdater()
{
	if (hInternet) {
		InternetCloseHandle(hInternet);
	}
}
    
//
// 检查更新
CAutoUpdater::ErrorType CAutoUpdater::CheckUpdate(CString serverURL, CString updateConfigFileName)
{
	if (!InternetOkay()) {
		return InternetConnectFailure;
	}

	bool bTransferSuccess = false;

	/*CString URL = SERVICE_UPDATE_PATH;
	HINTERNET hSession = GetSession(URL);
	if (!hSession)
	{
		return InternetSessionFailure;
	}*/

	// 获取临时文件夹路径
	TCHAR tmpPath[MAX_PATH];
	GetTempPath(MAX_PATH, tmpPath);
	CString tempPath = tmpPath;

	// 获取远程更新文件 updates.txt
	CString URL = serverURL + updateConfigFileName; //SERVICE_UPDATE_PATH;
	HINTERNET hSession = GetSession(URL);
	if (!hSession) {
		return InternetSessionFailure;
	}

	// Proceed with the update
	CString updateFileLocation = tempPath + updateConfigFileName; //"updates.txt";
	bTransferSuccess = DownloadFile(hSession, updateFileLocation);
	InternetCloseHandle(hSession);
	if (!bTransferSuccess) {
		return FileDownloadFailure;
	}	

	// 获取程序运行路径
	CString appPath;
	::GetModuleFileName( NULL, appPath.GetBuffer(MAX_PATH), MAX_PATH );
	appPath.ReleaseBuffer();
	appPath = appPath.Left(appPath.ReverseFind(_T('\\')));
	appPath += "\\";
	//strPath += "\\updates.txt";

	// 获取配置文件信息，并分析
	std::vector<UpdateFileInf> updateSection;
	if (0 == getUpdateFileInf(updateFileLocation, updateSection) ) {
		return UpdateNotRequired;;
	}

	std::vector<UpdateFileInf>::iterator iter = updateSection.begin();

    while (iter != updateSection.end()) {
		if (true == checkFile(appPath + (*iter).serverFileName, (*iter).version) ) {
			return UpdateRequired;
		}
        ++iter;
    }

	return UpdateNotRequired;
}
    
//
// 执行更新
CAutoUpdater::ErrorType CAutoUpdater::RunUpdate(CString serverURL, CString updateConfigFileName)
{
	if (!InternetOkay()) {
		return InternetConnectFailure;
	}

	ErrorType retValue = Success;
	bool bTransferSuccess = false;

	// 获取临时文件夹路径
	TCHAR tmpPath[MAX_PATH];
	GetTempPath(MAX_PATH, tmpPath);
	CString tempPath = tmpPath;

	// 获取远程更新文件 updates.txt
	CString URL = serverURL + updateConfigFileName; //SERVICE_UPDATE_PATH;
	HINTERNET hSession = GetSession(URL);
	if (!hSession)
	{
		return InternetSessionFailure;
	}

	// Proceed with the update
	CString updateFileLocation = tempPath + updateConfigFileName; //"updates.txt";
	bTransferSuccess = DownloadFile(hSession, updateFileLocation);
	InternetCloseHandle(hSession);
	if (!bTransferSuccess)
	{
		return FileDownloadFailure;
	}	

	// 获取程序运行路径
	CString appPath;
	::GetModuleFileName( NULL, appPath.GetBuffer(MAX_PATH), MAX_PATH );
	appPath.ReleaseBuffer();
	appPath = appPath.Left(appPath.ReverseFind(_T('\\')));
	appPath += "\\";
	//strPath += "\\updates.txt";

	// 获取配置文件信息，并分析
	std::vector<UpdateFileInf> updateSection;
	if (0 == getUpdateFileInf(updateFileLocation, updateSection) ) {
		return UpdateNotRequired;;
	}

	std::vector<UpdateFileInf>::iterator iter = updateSection.begin();

    while (iter != updateSection.end()) {
		if (true == checkFile(appPath + (*iter).serverFileName, (*iter).version) ) {
			// 更新文件
			retValue = updateFile((*iter).url, tempPath + (*iter).serverFileName, 
				                  appPath + (*iter).serverFileName, (*iter).fileSize);
		}
        ++iter;
    }

	return retValue;
}
    
//
// 获取下载下来的配置文件信息
int CAutoUpdater::getUpdateFileInf(const CString &strPath, std::vector<UpdateFileInf> &section) 
{  
    TCHAR chSectionNames[2048]={0}; //所有节名组成的字符数组  
    char * pSectionName; //保存找到的某个节名字符串的首地址  
    int i; //i指向数组chSectionNames的某个位置，从0开始，顺序后移  
    int j=0; //j用来保存下一个节名字符串的首地址相对于当前i的位置偏移量 
    int count=0; //统计节的个数 

    //CString name; 
    //char id[20]; 
    section.clear();
    ::GetPrivateProfileSectionNames(chSectionNames, 2048, strPath); 
    for(i=0; i<2048; i++,j++) {  
		if(chSectionNames[0]=='\0') {
            break; //如果第一个字符就是0，则说明ini中一个节也没有 
		}

        if(chSectionNames[i]=='\0') { 
            pSectionName=&chSectionNames[i-j]; //找到一个0，则说明从这个字符往前，减掉j个偏移量， 
            //就是一个节名的首地址 

            j=-1; //找到一个节名后，j的值要还原，以统计下一个节名地址的偏移量 
                  //赋成-1是因为节名字符串的最后一个字符0是终止符，不能作为节名的一部分 
            /*::GetPrivateProfileString(pSectionName,"id","Error",id,20,".\\ex1.ini"); 
            name.Format("%s",id);*/ 
            //在获取节名的时候可以获取该节中键的值，前提是我们知道该节中有哪些键。  

            //AfxMessageBox(pSectionName); //把找到的显示出来 
	        UpdateFileInf tmp;
			TCHAR buffer[MAX_PATH];

			// 获取字符串
			GetPrivateProfileString(pSectionName, "Name", "ERROR", buffer, MAX_PATH, strPath);
			tmp.name = buffer;
			GetPrivateProfileString(pSectionName, "URL", "ERROR", buffer, MAX_PATH, strPath);
			tmp.url = buffer;
			tmp.fileSize = GetPrivateProfileInt(pSectionName, "Size", 0, strPath);

			GetPrivateProfileString(pSectionName, "MD5", "ERROR", buffer, MAX_PATH, strPath);
			tmp.md5 = buffer;
			GetPrivateProfileString(pSectionName, "ServerFileName", "ERROR", buffer, MAX_PATH, strPath);
			tmp.serverFileName = buffer;

			GetPrivateProfileString(pSectionName, "Version", "ERROR", buffer, MAX_PATH, strPath);
			tmp.version = buffer;
			section.push_back(tmp);	

			// 节数目增加1
			++count;

			if(chSectionNames[i+1]==0) { 
				break; //当两个相邻的字符都是0时，则所有的节名都已找到，循环终止  
			} 
		} 
	} 

	return count; 
} 
    
//
// 检查文件是否需要更新
bool CAutoUpdater::checkFile(CString filePath, CString updateVersion)
{
	CString fileVersion = GetFileVersion(filePath);
	if (fileVersion.IsEmpty()) {
		return false;
	}

	if (CompareVersions(updateVersion, fileVersion) != 1) {	
		return false;
	} else {
		return true;
	}

	return false;
}
    
//
// 更新文件
CAutoUpdater::ErrorType CAutoUpdater::updateFile(CString serverFilePath, CString tmpFilePath, 
								   CString localFilePath, DWORD fileSize)
{
	if (!InternetOkay()) {
		return InternetConnectFailure;
	}

	bool bTransferSuccess = false;

	// 获取远程更新文件
	CString URL = serverFilePath;
	HINTERNET hSession = GetSession(URL);
	if (!hSession) {
		return InternetSessionFailure;
	}

	bTransferSuccess = DownloadFile(hSession, tmpFilePath, fileSize);
	InternetCloseHandle(hSession);
	if (!bTransferSuccess) {
		return FileDownloadFailure;
	}

	// 交换临时保存的文件和运行目录的文件
	if (!Switch(localFilePath, tmpFilePath, false))	{
		return UpdateNotComplete;
	}

	return Success;
}
    
// Check if an update is required
//
CAutoUpdater::ErrorType CAutoUpdater::CheckForUpdate(LPCTSTR UpdateServerURL, CString &verFile, 
													 CString &exeFile, bool onlyCheck)
{		
	_verFile = verFile;
	_exeFile = exeFile;

	if (!InternetOkay())
	{
		return InternetConnectFailure;
	}

	bool bTransferSuccess = false;

	// First we must check the remote configuration file to see if an update is necessary
	CString URL = UpdateServerURL + _verFile;
	HINTERNET hSession = GetSession(URL);
	if (!hSession)
	{
		return InternetSessionFailure;
	}

	BYTE pBuf[TRANSFER_SIZE];
	memset(pBuf, NULL, sizeof(pBuf));
	bTransferSuccess = DownloadConfig(hSession, pBuf, TRANSFER_SIZE);
	InternetCloseHandle(hSession);
	if (!bTransferSuccess)
	{
		return ConfigDownloadFailure;
	}

	// Get the version number of our executable and compare to see if an update is needed
	CString executable = GetExecutable();
	CString fileVersion = GetFileVersion(executable);\
	if (fileVersion.IsEmpty())
	{
		return NoExecutableVersion;
	}

	CString updateVersion = (char *) pBuf;
	if (CompareVersions(updateVersion, fileVersion) != 1)
	{	
		return UpdateNotRequired;
	}

	// 如果只比较版本，不下载文件，则直接退出。
	if (onlyCheck) {
		return Success;
	}

	// At this stage an update is required	
	TCHAR path[MAX_PATH];
	GetTempPath(MAX_PATH, path);
	CString exeName = executable.Mid(1+executable.ReverseFind(_T('\\')));
	CString directory = path;
	
	// Download the updated file
	URL = UpdateServerURL + exeName;
	hSession = GetSession(URL);
	if (!hSession)
	{
		return InternetSessionFailure;
	}

	CString msg;
	//msg.Format(_T("An update of %s is now available. Proceed with the update?"), exeName);
    //msg.Format(_T("存在一个可用更新，需要继续吗?"), exeName);
	//if (IDNO == MessageBox(GetActiveWindow(), msg, _T("更新可用"), MB_YESNO|MB_ICONQUESTION))
	//{
	//	return UpdateNotComplete;	
	//}

	// Proceed with the update
	CString updateFileLocation = directory+exeName;
	bTransferSuccess = DownloadFile(hSession, updateFileLocation);
	InternetCloseHandle(hSession);
	if (!bTransferSuccess)
	{
		return FileDownloadFailure;
	}	

	if (!Switch(executable, updateFileLocation, false))
	{
		return UpdateNotComplete;
	}
	
	return Success;
}

// Check if an update is required
//
/*CAutoUpdater::ErrorType CAutoUpdater::CheckForUpdate(LPCTSTR UpdateServerURL)
{		
	if (!InternetOkay())
	{
		return InternetConnectFailure;
	}

	bool bTransferSuccess = false;

	// First we must check the remote configuration file to see if an update is necessary
	CString URL = UpdateServerURL + CString(_verFile);
	HINTERNET hSession = GetSession(URL);
	if (!hSession)
	{
		return InternetSessionFailure;
	}

	BYTE pBuf[TRANSFER_SIZE];
	memset(pBuf, NULL, sizeof(pBuf));
	bTransferSuccess = DownloadConfig(hSession, pBuf, TRANSFER_SIZE);
	InternetCloseHandle(hSession);
	if (!bTransferSuccess)
	{
		return ConfigDownloadFailure;
	}

	// Get the version number of our executable and compare to see if an update is needed
	CString executable = GetExecutable();
	CString fileVersion = GetFileVersion(executable);\
	if (fileVersion.IsEmpty())
	{
		return NoExecutableVersion;
	}

	CString updateVersion = (char *) pBuf;
	if (CompareVersions(updateVersion, fileVersion) != 1)
	{	
		return UpdateNotRequired;
	}

	// At this stage an update is required	
	TCHAR path[MAX_PATH];
	GetTempPath(MAX_PATH, path);
	CString exeName = executable.Mid(1+executable.ReverseFind(_T('\\')));
	CString directory = path;
	
	// Download the updated file
	URL = UpdateServerURL + exeName;
	hSession = GetSession(URL);
	if (!hSession)
	{
		return InternetSessionFailure;
	}

	CString msg;
	//msg.Format(_T("An update of %s is now available. Proceed with the update?"), exeName);
    //msg.Format(_T("存在一个可用更新，需要继续吗?"), exeName);
	//if (IDNO == MessageBox(GetActiveWindow(), msg, _T("更新可用"), MB_YESNO|MB_ICONQUESTION))
	//{
	//	return UpdateNotComplete;	
	//}

	// Proceed with the update
	CString updateFileLocation = directory+exeName;
	bTransferSuccess = DownloadFile(hSession, updateFileLocation);
	InternetCloseHandle(hSession);
	if (!bTransferSuccess)
	{
		return FileDownloadFailure;
	}	

	if (!Switch(executable, updateFileLocation, false))
	{
		return UpdateNotComplete;
	}
	
	return Success;
}
*/

// Ensure the internet is ok to use
//
bool CAutoUpdater::InternetOkay()
{
	if (hInternet == NULL) {
		return false;
	}

	// Important step - ensure we have an internet connection. We don't want to force a dial-up.
	DWORD dwType;
	if (!InternetGetConnectedState(&dwType, 0))
	{
		return false;
	}

	return true;
}

// Get a session pointer to the remote file
//
HINTERNET CAutoUpdater::GetSession(CString &URL)
{
	// Canonicalization of the URL converts unsafe characters into escape character equivalents
	TCHAR canonicalURL[1024];
	DWORD nSize = 1024;
	InternetCanonicalizeUrl(URL, canonicalURL, &nSize, ICU_BROWSER_MODE);		
	
	DWORD options = INTERNET_FLAG_NEED_FILE|INTERNET_FLAG_HYPERLINK|INTERNET_FLAG_RESYNCHRONIZE|INTERNET_FLAG_RELOAD;
	HINTERNET hSession = InternetOpenUrl(hInternet, canonicalURL, NULL, NULL, options, 0);
	URL = canonicalURL;

	return hSession;
}

// Download a file into a memory buffer
//
bool CAutoUpdater::DownloadConfig(HINTERNET hSession, BYTE *pBuf, DWORD bufSize)
{	
	DWORD	dwReadSizeOut;
	InternetReadFile(hSession, pBuf, bufSize, &dwReadSizeOut);
	if (dwReadSizeOut <= 0)
	{
		return false;
	}

	
	return true;
}

    
// Download a file to a specified location
//
bool CAutoUpdater::DownloadFile(HINTERNET hSession, LPCTSTR localFile)
{	
	HANDLE	hFile;
	BYTE	pBuf[TRANSFER_SIZE];
	DWORD	dwReadSizeOut, dwTotalReadSize = 0;

	hFile = CreateFile(localFile, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return false;

	do {
		DWORD dwWriteSize, dwNumWritten;
		BOOL bRead = InternetReadFile(hSession, pBuf, TRANSFER_SIZE, &dwReadSizeOut);
		dwWriteSize = dwReadSizeOut;

		if (bRead && dwReadSizeOut > 0) {
			dwTotalReadSize += dwReadSizeOut;
			WriteFile(hFile, pBuf, dwWriteSize, &dwNumWritten, NULL); 
			// File write error
			if (dwWriteSize != dwNumWritten) {
				CloseHandle(hFile);					
				return false;
			}
		}
		else {
			if (!bRead)
			{
				// Error
				CloseHandle(hFile);	
				return false;
			}			
			break;
		}
	} while(1);

	// 获取下载文件大小，如果大小异常则返回错误。
	//DWORD dwFileSize = GetFileSize(hFile, NULL);

	CloseHandle(hFile);
	return true;
}
    
// 下载文件，比较大小
//
bool CAutoUpdater::DownloadFile(HINTERNET hSession, LPCTSTR localFile, DWORD getFileSize)
{	
	HANDLE	hFile;
	BYTE	pBuf[TRANSFER_SIZE];
	DWORD	dwReadSizeOut, dwTotalReadSize = 0;

	hFile = CreateFile(localFile, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return false;

	do {
		DWORD dwWriteSize, dwNumWritten;
		BOOL bRead = InternetReadFile(hSession, pBuf, TRANSFER_SIZE, &dwReadSizeOut);
		dwWriteSize = dwReadSizeOut;

		if (bRead && dwReadSizeOut > 0) {
			dwTotalReadSize += dwReadSizeOut;
			WriteFile(hFile, pBuf, dwWriteSize, &dwNumWritten, NULL); 
			// File write error
			if (dwWriteSize != dwNumWritten) {
				CloseHandle(hFile);					
				return false;
			}
		}
		else {
			if (!bRead)
			{
				// Error
				CloseHandle(hFile);	
				return false;
			}			
			break;
		}
	} while(1);

	// 获取下载文件大小，如果大小异常则返回错误。
	DWORD dwFileSize = GetFileSize(hFile, NULL);
	if (getFileSize != dwFileSize) {
		CloseHandle(hFile);
		return false;
	}

	CloseHandle(hFile);
	return true;
}

// Get the version of a file
//
CString CAutoUpdater::GetFileVersion(LPCTSTR file)
{
	CString version;
	VS_FIXEDFILEINFO *pVerInfo = NULL;
	DWORD	dwTemp, dwSize, dwHandle = 0;
	BYTE	*pData = NULL;
	UINT	uLen;

	try {
		dwSize = GetFileVersionInfoSize((LPTSTR) file, &dwTemp);
		if (dwSize == 0) throw 1;

		pData = new BYTE[dwSize];
		if (pData == NULL) throw 1;

		if (!GetFileVersionInfo((LPTSTR) file, dwHandle, dwSize, pData))
			throw 1;

		if (!VerQueryValue(pData, _T("\\"), (void **) &pVerInfo, &uLen)) 
			throw 1;

		DWORD verMS = pVerInfo->dwFileVersionMS;
		DWORD verLS = pVerInfo->dwFileVersionLS;

		int ver[4];
		ver[0] = HIWORD(verMS);
		ver[1] = LOWORD(verMS);
		ver[2] = HIWORD(verLS);
		ver[3] = LOWORD(verLS);

		// Are lo-words used?
		if (ver[2] != 0 || ver[3] != 0)
		{
			version.Format(_T("%d.%d.%d.%d"), ver[0], ver[1], ver[2], ver[3]);
		}
		else if (ver[0] != 0 || ver[1] != 0)
		{
			version.Format(_T("%d.%d"), ver[0], ver[1]);
		}

		delete pData;
		return version;
	}
	catch(...) {
		return _T("");
	}	
}

// Compare two versions 
//
int CAutoUpdater::CompareVersions(CString ver1, CString ver2)
{
	int  wVer1[4], wVer2[4];
	int	 i;
	TCHAR *pVer1 = ver1.GetBuffer(256);
	TCHAR *pVer2 = ver2.GetBuffer(256);

	for (i=0; i<4; i++)
	{
		wVer1[i] = 0;
		wVer2[i] = 0;
	}

	// Get version 1 to DWORDs
	TCHAR *pToken = strtok(pVer1, _T("."));
	if (pToken == NULL)
	{
		return -21;
	}

	i=3;
	while(pToken != NULL)
	{
		if (i<0 || !IsDigits(pToken)) 
		{			
			return -21;	// Error in structure, too many parameters
		}		
		wVer1[i] = atoi(pToken);
		pToken = strtok(NULL, _T("."));
		i--;
	}
	ver1.ReleaseBuffer();

	// Get version 2 to DWORDs
	pToken = strtok(pVer2, _T("."));
	if (pToken == NULL)
	{
		return -22;
	}

	i=3;
	while(pToken != NULL)
	{
		if (i<0 || !IsDigits(pToken)) 
		{
			return -22;	// Error in structure, too many parameters
		}		
		wVer2[i] = atoi(pToken);
		pToken = strtok(NULL, _T("."));
		i--;
	}
	ver2.ReleaseBuffer();

	// Compare the versions
	for (i=3; i>=0; i--)
	{
		if (wVer1[i] > wVer2[i])
		{
			return 1;		// ver1 > ver 2
		}
		else if (wVer1[i] < wVer2[i])
		{
			return -1;
		}
	}

	return 0;	// ver 1 == ver 2
}

// Ensure a string contains only digit characters
//
bool CAutoUpdater::IsDigits(CString text)
{
	for (int i=0; i<text.GetLength(); i++)
	{
		TCHAR c = text.GetAt(i);
		if (c >= _T('0') && c <= _T('9'))
		{
		}
		else
		{
			return false;
		}
	}

	return true;
}

CString CAutoUpdater::GetExecutable()
{/*
	HMODULE hModule = ::GetModuleHandle(NULL);
    ASSERT(hModule != 0);
    
    TCHAR path[MAX_PATH];
    VERIFY(::GetModuleFileName(hModule, path, MAX_PATH));
    return path;
*/
    TCHAR path[MAX_PATH];
    VERIFY(GetCurrentDirectory(MAX_PATH, path));
    CString ret = path;
    ret = ret + "\\" + _exeFile;
    return ret;
}

BOOL CAutoUpdater::Switch(CString executable, CString update, bool WaitForReboot)
{
	int type = (WaitForReboot) ? MOVEFILE_DELAY_UNTIL_REBOOT : MOVEFILE_COPY_ALLOWED;

	//const TCHAR *backup = _T("OldExecutable.bak");
	//CString directory = executable.Left(executable.ReverseFind(_T('\\')));	
	//CString oldFile = directory + _T('\\') + _exeFile;

	//DeleteFile(oldFile);
	//if (!MoveFileEx(executable, backupFile, type)) 
	//{
	//	return false;
	//}

    DeleteFile(executable);

	BOOL bMoveOK = (MoveFileEx(update, executable, type) == TRUE);
	int i = GetLastError();

	return bMoveOK;	
}

