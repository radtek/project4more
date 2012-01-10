#pragma once

#include "PublishRecord.h"

class CHistoryManager
{
public:

	static CHistoryManager* getInstance();
	~CHistoryManager(void);

	publishList&		getPublishes() { return publishes; }
	void				addPublish(CPublishRecord* pPublish);

protected:
	CHistoryManager(void);

private:
	static CHistoryManager*		pInstance;
	publishList					publishes;

	void	savePublishRecords(char* filename);
	void	loadPublishRecords(char* filename);
	void	clearPublishList();
};
