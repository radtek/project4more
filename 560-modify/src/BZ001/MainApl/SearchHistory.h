#ifndef _FMP_SEARCH_HISTORY_H
#define _FMP_SEARCH_HISTORY_H

#include <string>
using std::string;

class CSearchCriteria;

class CSearchHistory
{
public:
	CSearchHistory(const string& sFormatString);
	CSearchHistory(const CSearchCriteria* pSearchFav);
public:
	string	toString();
	void	fromString(const string& str);
public:
	const string& GetPublisher()const
	{
		return m_sPubliser;
	}
	const string& GetPhoneNumber()const
	{
		return m_sPhoneNumber;
	}
	const string& GetKeyword()const
	{
		return m_sKeyword;
	}
private:
	string m_sPubliser;
	string m_sPhoneNumber;
	string m_sKeyword;
};

#endif //_FMP_SEARCH_FAVORITE_H


