#include "StdAfx.h"
#include "HistoryManager.h"
#include <iostream>
#include <fstream>

CHistoryManager* CHistoryManager::pInstance = NULL;

CHistoryManager::CHistoryManager(void)
{
	loadPublishRecords("publish.his");
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

void CHistoryManager::savePublishRecords(char* filename)
{
	ofstream configFile (filename);
	int	n = publishes.size();

	if ( configFile.is_open() )
	{
		publishIter		iter;
		for ( iter = publishes.begin(); iter != publishes.end(); iter++ )
		{
			CPublishRecord* pRecord = (*iter);
			configFile << pRecord->toString() << '\n';
		}
		configFile.close();
	}
}

void CHistoryManager::loadPublishRecords(char* filename)
{
	ifstream myfile (filename);

	if ( myfile.is_open() )
	{
		string	line;
		clearPublishList();

		while ( myfile.good() )
		{
			getline(myfile, line);
			if ( line.size() == 0 )
			{
				continue;
			}
			CPublishRecord* pRecord = new CPublishRecord(line);
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