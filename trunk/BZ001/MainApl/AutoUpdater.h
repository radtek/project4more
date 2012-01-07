// AutoUpdater.h: interface for the CAutoUpdater class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOUPDATER_H__227B2B21_B6AE_4164_B3A5_BFDAAF13D85D__INCLUDED_)
#define AFX_AUTOUPDATER_H__227B2B21_B6AE_4164_B3A5_BFDAAF13D85D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Wininet.h>

// �����ļ�����ַ
#define SERVICE_UPDATE_PATH _T("http://10.66.6.10/fmp/pc_client/update/updates.txt")
//#define SERVICE_UPDATE_PATH _T("http://www.666156.com/fmp/pc_client/update/")
//#define LOCATION_UPDATE_FILE_CHECK _T("update.txt")
//#define LOCATION_UPDATE_FILE_NAME _T("WLRClient.exe")

#include <string>
#include <vector>
//using namespace std;

// �����ļ���Ϣ
struct UpdateFileInf {
	CString name;
	CString url; // �ļ����ص�ַ
	DWORD fileSize; // ��Ҫ���µ��ļ���С
	CString md5;
	CString serverFileName; // ��Ҫ���µ��ļ���
	CString version; // ��Ҫ���µ��ļ��汾
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
	// �����ļ����Ƚϴ�С
    bool DownloadFile(HINTERNET hSession, LPCTSTR localFile, DWORD getFileSize);

	CString GetFileVersion(LPCTSTR file);
	int		CompareVersions(CString ver1, CString ver2);
	bool	IsDigits(CString text);
	CString GetExecutable();
	BOOL	Switch(CString executable, CString update, bool WaitForReboot);

public:
	// ������
	ErrorType CheckUpdate(CString serverURL, CString updateConfigFileName);

	// ִ�и���
	ErrorType RunUpdate(CString serverURL, CString updateConfigFileName);

private:
	HINTERNET hInternet;

private:
	CString _verFile;
	CString _exeFile;

private:
	// ��ȡ���������������ļ���Ϣ
	int getUpdateFileInf(const CString &strPath, std::vector<UpdateFileInf> &section);
	
	// ����ļ��Ƿ���Ҫ����
	bool checkFile(CString filePath, CString updateVersion);

	// �����ļ�
	ErrorType updateFile(CString serverFilePath, CString tmpFilePath, CString localFilePath, DWORD fileSize); 
};

#endif // !defined(AFX_AUTOUPDATER_H__227B2B21_B6AE_4164_B3A5_BFDAAF13D85D__INCLUDED_)
