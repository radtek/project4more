#pragma once

#include "PublishRecord.h"

class CHistoryManager
{
public:

	static CHistoryManager* getInstance();
	~CHistoryManager(void);

	publishList&		getPublishes()	{ return publishes; }
	void				addPublish(CPublishRecord* pPublish);

	list<string>&		getSearches()	{ return searches; }
	void				addSearch(CString str);

protected:
	CHistoryManager(void);

private:
	static CHistoryManager*		pInstance;
	publishList					publishes;
	list<string>				searches;

	void	savePublishRecords(char* filename);
	void	loadPublishRecords(char* filename);
	void	clearPublishList();

	void	saveSearchHistory(char* filename);
	void	loadSearchHistory(char* filename);
};
