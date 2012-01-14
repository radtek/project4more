#include "StdAfx.h"
#include "HistoryManager.h"
#include <iostream>
#include <fstream>
#include "SearchCriteria.h"

CHistoryManager* CHistoryManager::pInstance = NULL;

#define PUBLISH_HIS_FILE_NAME "publish.his"
#define SEARCH_HIS_FILE_NAME "search.his"
#define SEARCH_FAV_FILE_NAME "search.fav"

CHistoryManager::CHistoryManager(void)
{
	char szModuleFile[MAX_PATH] = {'\0'};
	GetModuleFileNameA(NULL, szModuleFile, sizeof(szModuleFile));
	char* pcszPath = strrchr(szModuleFile, '\\');
	if( pcszPath != NULL )
	{
		*pcszPath = '\0'; 
	}
	sprintf(m_szPublishHisFile, "%s\\%s", szModuleFile, PUBLISH_HIS_FILE_NAME);
	sprintf(m_szSearchHisFile, "%s\\%s", szModuleFile, SEARCH_HIS_FILE_NAME);
	sprintf(m_szSearchFavFile, "%s\\%s", szModuleFile, SEARCH_FAV_FILE_NAME);

	loadPublishRecords(m_szPublishHisFile);
	loadSearchHistory(m_szSearchHisFile);
	loadSearchFavorite(m_szSearchFavFile);
}

CHistoryManager::~CHistoryManager(void)
{
	CleanPublishHis();
	CleanSearchHis();
	CleanSearchFav();
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
	savePublishRecords(m_szPublishHisFile);
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


/****************search history*********************/
void CHistoryManager::addSearchHis(const CSearchCriteria* pSearchCriteria)
{
	if( !pSearchCriteria->GetKeyword().empty() || pSearchCriteria->GetPublisherList().size() > 0 || pSearchCriteria->GetPhoneNumList().size() > 0 )
	{
		searchesHis.push_back(new CSearchHistory(pSearchCriteria));
		saveSearchHistory(m_szSearchHisFile);
	}
}
void CHistoryManager::saveSearchHistory(char* filename)
{
	ofstream hisFile (filename);

	if ( hisFile.is_open() )
	{
		tdListSearchHistory::iterator iter = searchesHis.begin(), end = searchesHis.end();
		for ( iter; iter != end; iter++ )
		{
			string str = (*iter)->toString();
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
		searchesHis.clear();

		while ( hisFile.good() )
		{
			getline(hisFile, line);
			if ( line.size() == 0 )
			{
				continue;
			}
			searchesHis.push_back(new CSearchHistory(line));
		}
	}
}


/**************** search favorite *********************/
void CHistoryManager::addSearchFav(const CSearchCriteria* pSearchCriteria)
{
	CSearchFavorite* pSearchFav = new CSearchFavorite(pSearchCriteria);
	searchesFav.push_back(pSearchFav);
	saveSearchFavorite(m_szSearchFavFile);
}
void CHistoryManager::delSearchFav(const string& sName)
{
	tdListSearchFavorite::iterator iter = searchesFav.begin(), end = searchesFav.end();
	for(iter; iter != end; ++iter)
	{
		if( (*iter)->GetName() == sName )
		{
			searchesFav.erase(iter);
			saveSearchFavorite(m_szSearchFavFile);
			break;
		}
	}
}
void CHistoryManager::renameSearchFav(const string& sOldName, const string& sNewName)
{
	tdListSearchFavorite::iterator iter = searchesFav.begin(), end = searchesFav.end();
	for(iter; iter != end; ++iter)
	{
		CSearchFavorite* pSearchFav = *iter; 
		if( pSearchFav->GetName() == sOldName )
		{
			pSearchFav->SetName(sNewName);
			saveSearchFavorite(m_szSearchFavFile);
			break;
		}
	}
}
const CSearchFavorite*	CHistoryManager::findSearchFav(const string& sName)
{
	tdListSearchFavorite::iterator iter = searchesFav.begin(), end = searchesFav.end();
	for(iter; iter != end; ++iter)
	{
		CSearchFavorite* pSearchFav = *iter; 
		if( pSearchFav->GetName() == sName )
		{
			return pSearchFav;
		}
	}
	return NULL;
}


void CHistoryManager::saveSearchFavorite(char* filename)
{
	ofstream hisFile (filename);

	if ( hisFile.is_open() )
	{
		tdListSearchFavorite::iterator iter = searchesFav.begin(), end = searchesFav.end();
		for ( iter; iter != end; iter++ )
		{
			hisFile << (*iter)->toString() << '\n';
		}
		hisFile.close();
	}
}

void CHistoryManager::loadSearchFavorite(char* filename)
{
	ifstream hisFile (filename);

	if ( hisFile.is_open() )
	{
		string	line;
		searchesFav.clear();

		while ( hisFile.good() )
		{
			getline(hisFile, line);
			if ( line.size() == 0 )
			{
				continue;
			}
			searchesFav.push_back(new CSearchFavorite(line));
		}
	}
}


void CHistoryManager::CleanPublishHis()
{
	publishList::iterator it = publishes.begin(), end = publishes.end();
	for(it; it != end; ++it)
	{
		delete *it;
	}
}
void CHistoryManager::CleanSearchHis()
{
	tdListSearchHistory::iterator it = searchesHis.begin(), end = searchesHis.end();
	for(it; it != end; ++it)
	{
		delete *it;
	}
}
void CHistoryManager::CleanSearchFav()
{
	tdListSearchFavorite::iterator it = searchesFav.begin(), end = searchesFav.end();
	for(it; it != end; ++it)
	{
		delete *it;
	}
}