#include "StdAfx.h"
#include "SearchHistory.h"
#include "SearchCriteria.h"

#define SH_SPLITER '|'

CSearchHistory::CSearchHistory(const string& sFormatString)
{
	fromString(sFormatString);
}
CSearchHistory::CSearchHistory(const CSearchCriteria *pSearchFav)
{
	const list<string>& lstPublisher = pSearchFav->GetPublisherList();
	if( lstPublisher.size() > 0 )
	{
		m_sPubliser = *lstPublisher.begin();
	}

	const list<string>& lstPhoneNum = pSearchFav->GetPhoneNumList();
	if( lstPhoneNum.size() > 0 )
	{
		m_sPhoneNumber = *lstPhoneNum.begin();
	}

	m_sKeyword = pSearchFav->GetKeyword();
}

string CSearchHistory::toString()
{
	return string(m_sPubliser+SH_SPLITER+m_sPhoneNumber+SH_SPLITER+m_sKeyword);
}

void CSearchHistory::fromString(const string& sFormatString)
{
	string::size_type pos = sFormatString.find(SH_SPLITER, 0);
	if( pos == string::npos )
	{
		return;
	}
	m_sPubliser = sFormatString.substr(0, pos);

	pos+=1;
	string::size_type pos1 = sFormatString.find(SH_SPLITER, pos);
	if( pos == string::npos )
	{
		return;
	}
	m_sPhoneNumber = sFormatString.substr(pos,pos1-pos);

	m_sKeyword = sFormatString.substr(pos1+1);
}