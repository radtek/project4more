// AutoUpdater.h: interface for the CAutoUpdater class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOUPDATER_H__227B2B21_B6AE_4164_B3A5_BFDAAF13D85D__INCLUDED_)
#define AFX_AUTOUPDATER_H__227B2B21_B6AE_4164_B3A5_BFDAAF13D85D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Wininet.h>

// 更新文件检查地址
#define SERVICE_UPDATE_PATH _T("http://10.66.6.10/fmp/pc_client/update/updates.txt")
//#define SERVICE_UPDATE_PATH _T("http://www.666156.com/fmp/pc_client/update/")
//#define LOCATION_UPDATE_FILE_CHECK _T("update.txt")
//#define LOCATION_UPDATE_FILE_NAME _T("WLRClient.exe")

#include <string>
#include <vector>
//using namespace std;

// 更新文件信息
struct UpdateFileInf {
	CString name;
	CString url; // 文件下载地址
	DWORD fileSize; // 需要更新的文件大小
	CString md5;
	CString serverFileName; // 需要更新的文件名
	CString version; // 需要更新的文件版本
};

class CAutoUpdater  
{
public:
	CAutoUpdater();
	virtual ~CAutoUpdater();

	enum ErrorType { Success, InternetConnectFailure, InternetSessionFailure, 
						ConfigDownloadFailure, FileDownloadFailure, NoExecutableVersion,
						UpdateRequired, UpdateNotRequired, UpdateNotComplete };

	//ErrorType CheckForUpdate(LPCTSTR UpdateServerURL);
	ErrorType CheckForUpdate(LPCTSTR UpdateServerURL, CString &verFile, 
		                     CString &exeFile, bool onlyCheck = false);
	HINTERNET GetSession(CString &URL);

	bool InternetOkay();
	bool DownloadConfig(HINTERNET hSession, BYTE *pBuf, DWORD bufSize);
	bool DownloadFile(HINTERNET hSession, LPCTSTR localFile);
	// 下载文件，比较大小
    bool DownloadFile(HINTERNET hSession, LPCTSTR localFile, DWORD getFileSize);

	CString GetFileVersion(LPCTSTR file);
	int		CompareVersions(CString ver1, CString ver2);
	bool	IsDigits(CString text);
	CString GetExecutable();
	BOOL	Switch(CString executable, CString update, bool WaitForReboot);

public:
	// 检查更新
	ErrorType CheckUpdate(CString serverURL, CString updateConfigFileName);

	// 执行更新
	ErrorType RunUpdate(CString serverURL, CString updateConfigFileName);

private:
	HINTERNET hInternet;

private:
	CString _verFile;
	CString _exeFile;

private:
	// 获取下载下来的配置文件信息
	int getUpdateFileInf(const CString &strPath, std::vector<UpdateFileInf> &section);
	
	// 检查文件是否需要更新
	bool checkFile(CString filePath, CString updateVersion);

	// 更新文件
	ErrorType updateFile(CString serverFilePath, CString tmpFilePath, CString localFilePath, DWORD fileSize); 
};

#endif // !defined(AFX_AUTOUPDATER_H__227B2B21_B6AE_4164_B3A5_BFDAAF13D85D__INCLUDED_)
