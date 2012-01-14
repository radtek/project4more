#ifndef _FMP_PUBLISH_RECORD_H
#define _FMP_PUBLISH_RECORD_H

#pragma once
#include <map>
#include <string>
#include <list>

using namespace std;

class CPublishRecord
{
public:
	CPublishRecord();
	CPublishRecord(const string& str);
	~CPublishRecord(void);

	string	toString();
	void	fromString(const string& str);

	CString	get(const string& key);
	void	set(const string& key, const CString& value);

	int		sn;

private:
	map<string, string>		paras;
};

typedef list<CPublishRecord *>	publishList;
typedef publishList::iterator	publishIter;

#endif //_FMP_PUBLISH_RECORD_H