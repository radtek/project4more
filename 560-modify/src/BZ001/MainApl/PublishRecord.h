#pragma once
#include <map>
#include <string>
#include <list>

using namespace std;

class CPublishRecord
{
public:
	CPublishRecord();
	CPublishRecord(string str);
	~CPublishRecord(void);

	string	toString();
	void	fromString(string str);

	CString	get(string key);
	void	set(string key, CString value);

	int		sn;

private:
	map<string, string>		paras;
};

typedef list<CPublishRecord *>	publishList;
typedef publishList::iterator	publishIter;