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
// ������
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

	// ��ȡ��ʱ�ļ���·��
	TCHAR tmpPath[MAX_PATH];
	GetTempPath(MAX_PATH, tmpPath);
	CString tempPath = tmpPath;

	// ��ȡԶ�̸����ļ� updates.txt
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

	// ��ȡ��������·��
	CString appPath;
	::GetModuleFileName( NULL, appPath.GetBuffer(MAX_PATH), MAX_PATH );
	appPath.ReleaseBuffer();
	appPath = appPath.Left(appPath.ReverseFind(_T('\\')));
	appPath += "\\";
	//strPath += "\\updates.txt";

	// ��ȡ�����ļ���Ϣ��������
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
// ִ�и���
CAutoUpdater::ErrorType CAutoUpdater::RunUpdate(CString serverURL, CString updateConfigFileName)
{
	if (!InternetOkay()) {
		return InternetConnectFailure;
	}

	ErrorType retValue = Success;
	bool bTransferSuccess = false;

	// ��ȡ��ʱ�ļ���·��
	TCHAR tmpPath[MAX_PATH];
	GetTempPath(MAX_PATH, tmpPath);
	CString tempPath = tmpPath;

	// ��ȡԶ�̸����ļ� updates.txt
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

	// ��ȡ��������·��
	CString appPath;
	::GetModuleFileName( NULL, appPath.GetBuffer(MAX_PATH), MAX_PATH );
	appPath.ReleaseBuffer();
	appPath = appPath.Left(appPath.ReverseFind(_T('\\')));
	appPath += "\\";
	//strPath += "\\updates.txt";

	// ��ȡ�����ļ���Ϣ��������
	std::vector<UpdateFileInf> updateSection;
	if (0 == getUpdateFileInf(updateFileLocation, updateSection) ) {
		return UpdateNotRequired;;
	}

	std::vector<UpdateFileInf>::iterator iter = updateSection.begin();

    while (iter != updateSection.end()) {
		if (true == checkFile(appPath + (*iter).serverFileName, (*iter).version) ) {
			// �����ļ�
			retValue = updateFile((*iter).url, tempPath + (*iter).serverFileName, 
				                  appPath + (*iter).serverFileName, (*iter).fileSize);
		}
        ++iter;
    }

	return retValue;
}
    
//
// ��ȡ���������������ļ���Ϣ
int CAutoUpdater::getUpdateFileInf(const CString &strPath, std::vector<UpdateFileInf> &section) 
{  
    TCHAR chSectionNames[2048]={0}; //���н�����ɵ��ַ�����  
    char * pSectionName; //�����ҵ���ĳ�������ַ������׵�ַ  
    int i; //iָ������chSectionNames��ĳ��λ�ã���0��ʼ��˳�����  
    int j=0; //j����������һ�������ַ������׵�ַ����ڵ�ǰi��λ��ƫ���� 
    int count=0; //ͳ�ƽڵĸ��� 

    //CString name; 
    //char id[20]; 
    section.clear();
    ::GetPrivateProfileSectionNames(chSectionNames, 2048, strPath); 
    for(i=0; i<2048; i++,j++) {  
		if(chSectionNames[0]=='\0') {
            break; //�����һ���ַ�����0����˵��ini��һ����Ҳû�� 
		}

        if(chSectionNames[i]=='\0') { 
            pSectionName=&chSectionNames[i-j]; //�ҵ�һ��0����˵��������ַ���ǰ������j��ƫ������ 
            //����һ���������׵�ַ 

            j=-1; //�ҵ�һ��������j��ֵҪ��ԭ����ͳ����һ��������ַ��ƫ���� 
                  //����-1����Ϊ�����ַ��������һ���ַ�0����ֹ����������Ϊ������һ���� 
            /*::GetPrivateProfileString(pSectionName,"id","Error",id,20,".\\ex1.ini"); 
            name.Format("%s",id);*/ 
            //�ڻ�ȡ������ʱ����Ի�ȡ�ý��м���ֵ��ǰ��������֪���ý�������Щ����  

            //AfxMessageBox(pSectionName); //���ҵ�����ʾ���� 
	        UpdateFileInf tmp;
			TCHAR buffer[MAX_PATH];

			// ��ȡ�ַ���
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

			// ����Ŀ����1
			++count;

			if(chSectionNames[i+1]==0) { 
				break; //���������ڵ��ַ�����0ʱ�������еĽ��������ҵ���ѭ����ֹ  
			} 
		} 
	} 

	return count; 
} 
    
//
// ����ļ��Ƿ���Ҫ����
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
// �����ļ�
CAutoUpdater::ErrorType CAutoUpdater::updateFile(CString serverFilePath, CString tmpFilePath, 
								   CString localFilePath, DWORD fileSize)
{
	if (!InternetOkay()) {
		return InternetConnectFailure;
	}

	bool bTransferSuccess = false;

	// ��ȡԶ�̸����ļ�
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

	// ������ʱ������ļ�������Ŀ¼���ļ�
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

	// ���ֻ�Ƚϰ汾���������ļ�����ֱ���˳���
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
    //msg.Format(_T("����һ�����ø��£���Ҫ������?"), exeName);
	//if (IDNO == MessageBox(GetActiveWindow(), msg, _T("���¿���"), MB_YESNO|MB_ICONQUESTION))
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
    //msg.Format(_T("����һ�����ø��£���Ҫ������?"), exeName);
	//if (IDNO == MessageBox(GetActiveWindow(), msg, _T("���¿���"), MB_YESNO|MB_ICONQUESTION))
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

	// ��ȡ�����ļ���С�������С�쳣�򷵻ش���
	//DWORD dwFileSize = GetFileSize(hFile, NULL);

	CloseHandle(hFile);
	return true;
}
    
// �����ļ����Ƚϴ�С
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

	// ��ȡ�����ļ���С�������С�쳣�򷵻ش���
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

