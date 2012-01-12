#include "StdAfx.h"
#include "HistoryManager.h"
#include <iostream>
#include <fstream>

CHistoryManager* CHistoryManager::pInstance = NULL;

CHistoryManager::CHistoryManager(void)
{
	loadPublishRecords("publish.his");
	loadPublishRecords("search.his");
}

CHistoryManager::~CHistoryManager(void)
{
}

CHistoryManager* CHistoryManager::getInstance()
{
	if ( pInstance == NULL) {
		pInstance = new CHistoryManager;
	}
	return pInstance;
}

void CHistoryManager::addPublish(CPublishRecord* pPublish)
{
	publishes.push_back(pPublish);
	savePublishRecords("publish.his");
}

void CHistoryManager::addSearch(CString str)
{
	string s(str.GetBuffer());
	str.ReleaseBuffer();
	searches.push_back(s);
	saveSearchHistory("search.his");
}

void CHistoryManager::savePublishRecords(char* filename)
{
	ofstream hisFile (filename);
	int	n = publishes.size();

	if ( hisFile.is_open() )
	{
		publishIter		iter;
		for ( iter = publishes.begin(); iter != publishes.end(); iter++ )
		{
			CPublishRecord* pRecord = (*iter);
			hisFile << pRecord->toString() << '\n';
		}
		hisFile.close();
	}
}


void CHistoryManager::loadPublishRecords(char* filename)
{
	ifstream hisFile (filename);
	
	if ( hisFile.is_open() )
	{
		string	line;
		clearPublishList();
		int		count = 0;

		while ( hisFile.good() )
		{
			getline(hisFile, line);
			if ( line.size() == 0 )
			{
				continue;
			}
			CPublishRecord* pRecord = new CPublishRecord(line);
			pRecord->sn = count;
			count++;
			publishes.push_back(pRecord);
		}
	}
}

void CHistoryManager::clearPublishList()
{
	if ( publishes.empty() )
	{
		return;
	}

	publishIter		iter;

	for ( iter = publishes.begin(); iter != publishes.end(); iter++ )
	{
		CPublishRecord* pRecord = (*iter);
		delete pRecord;
	}

	publishes.clear();
}

void CHistoryManager::saveSearchHistory(char* filename)
{
	ofstream hisFile (filename);

	if ( hisFile.is_open() )
	{
		list<string>::iterator		iter;
		for ( iter = searches.begin(); iter != searches.end(); iter++ )
		{
			string str = (*iter);
			hisFile << str << '\n';
		}
		hisFile.close();
	}

}

void CHistoryManager::loadSearchHistory(char* filename)
{
	ifstream hisFile (filename);

	if ( hisFile.is_open() )
	{
		string	line;
		searches.clear();

		while ( hisFile.good() )
		{
			getline(hisFile, line);
			if ( line.size() == 0 )
			{
				continue;
			}
			searches.push_back(line);
		}
	}
}