#ifndef _FMP_HISTORY_MANAGER_H
#define _FMP_HISTORY_MANAGER_H
#pragma once

#include "PublishRecord.h"
#include "SearchHistory.h"
#include "SearchFavorite.h"

class CSearchCriteria;

typedef list<CSearchHistory*> tdListSearchHistory;
typedef list<CSearchFavorite*> tdListSearchFavorite;

class CHistoryManager
{
public:

	static CHistoryManager* getInstance();
	~CHistoryManager(void);

	publishVector&				getPublishes()	{ return publishes; }
	void						addPublish(CPublishRecord* pPublish);
	void						deletePublish(int n);

	tdListSearchFavorite&		getSearchesFav()	 { return searchesFav; }
	const tdListSearchFavorite&	getSearchesFav()const{ return searchesFav; }
	void						addSearchFav(const CSearchCriteria* pSearchCriteria);
	void						delSearchFav(const string& sName);
	void						renameSearchFav(const string& sOldName, const string& sNewName);
	const CSearchFavorite*		findSearchFav(const string& sName);

	tdListSearchHistory&		getSearchesHis()	 { return searchesHis; }
	const tdListSearchHistory&	getSearchesHis()const{ return searchesHis; }
	void						addSearchHis(const CSearchCriteria* pSearchCriteria);
protected:
	CHistoryManager(void);
private:
	void CleanPublishHis();
	void CleanSearchHis();
	void CleanSearchFav();
private:
	static CHistoryManager*		pInstance;
	publishVector					publishes;
	tdListSearchHistory			searchesHis;
	tdListSearchFavorite		searchesFav;

	void	savePublishRecords(char* filename);
	void	loadPublishRecords(char* filename);
	void	clearPublishList();

	void	saveSearchHistory(char* filename);
	void	loadSearchHistory(char* filename);

	void	saveSearchFavorite(char* filename);
	void	loadSearchFavorite(char* filename);
private:
	char	m_szPublishHisFile[MAX_PATH];
	char	m_szSearchHisFile[MAX_PATH];
	char	m_szSearchFavFile[MAX_PATH];
};

#endif //#define _FMP_HISTORY_MANAGER_H