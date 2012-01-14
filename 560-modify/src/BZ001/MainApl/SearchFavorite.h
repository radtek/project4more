#ifndef _FMP_SEARCH_FAVORITE_H
#define _FMP_SEARCH_FAVORITE_H

#pragma once
#include "CommDef.h"
#include <string>
#include <map>
using std::string;
using std::map;

class CSearchCriteria;

class CSearchFavorite
{
public:
	CSearchFavorite(const string& sFormatString);
	CSearchFavorite(const CSearchCriteria* pSearchCriteria);
	~CSearchFavorite(void){}
public:
	const string& GetName()const
	{
		return m_sName;
	}
	void SetName(const string& sName)
	{
		m_sName = sName;
	}

	const string& GetSearchCriteria()const
	{
		return m_sSearchCriteria;
	}

	int GetSearchType()const
	{
		return m_nSearchType;
	}
public:
	string	toString();
	void	fromString(const string& str);
private:
	void ForamtName(const tdMapAddr& mapAddr, string& sName);
public:
	int     m_nSearchType;
	string	m_sName;
	string  m_sSearchCriteria;
};

#endif//_FMP_SEARCH_FAVORITE_H