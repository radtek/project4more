#include "StdAfx.h"
#include "SearchFavorite.h"
#include "SearchCriteria.h"

#define SH_SPLITER '|'

CSearchFavorite::CSearchFavorite(const string& sFormatString)
{
	fromString(sFormatString);
}
CSearchFavorite::CSearchFavorite(const CSearchCriteria* pSearchCriteria)
{
	m_nSearchType = pSearchCriteria->GetSearchType();

	ForamtName(pSearchCriteria->GetStartAddrList(), m_sName);

	string sEndName;
	ForamtName(pSearchCriteria->GetEndAddrList(), sEndName);
	if( !sEndName.empty() )
	{
		m_sName += (m_sName.empty()?"":"¡ª") + sEndName	;
	}
	m_sName += " " + pSearchCriteria->GetKeyword();

	pSearchCriteria->FormatSearchString(m_sSearchCriteria);
}

string CSearchFavorite::toString()
{
	char szSearchType[32] = {'\0'};
	sprintf(szSearchType, "%d|", m_nSearchType);
	return string(szSearchType+m_sName+SH_SPLITER+m_sSearchCriteria);
}

void CSearchFavorite::fromString(const string& sFormatString)
{
	string::size_type pos = sFormatString.find(SH_SPLITER, 0);
	if( pos == string::npos )
	{
		return;
	}
	m_nSearchType = atoi(sFormatString.substr(0, pos).c_str());

	pos+=1;
	string::size_type pos1 = sFormatString.find(SH_SPLITER, pos);
	if( pos == string::npos )
	{
		return;
	}
	m_sName = sFormatString.substr(pos,pos1-pos);

	m_sSearchCriteria = sFormatString.substr(pos1+1);
}

void CSearchFavorite::ForamtName(const tdMapAddr& mapAddr, string& sName)
{
	if( mapAddr.size() > 0 )
	{
		tdMapAddr::const_iterator it = mapAddr.begin(), end = mapAddr.end();
		for(it; it != end; ++it)
		{
			const string& sProvince = (*it).first;
			const tdMapCity& mapCity = (*it).second;
			tdMapCity::const_iterator mit = mapCity.begin(), mend = mapCity.end();
			if( mapCity.size() > 0 )
			{
				for(mit; mit != mend; ++mit)
				{
					const string& sCity = (*mit).first;
					const tdListCounty& lstCounty = (*mit).second;
					tdListCounty::const_iterator lit = lstCounty.begin(), lend = lstCounty.end();
					if( lstCounty.size() > 1 )
					{
						for(lit; lit != lend; ++lit)
						{
							sName += " " + *lit;
						}
					}
					else if( lstCounty.size() == 1 && *lit != NO_LIMIT_STRING )
					{
						sName += " " + *lit;
					}
					else
					{
						sName += " " + sCity;
					}
				}
			}
			else if( mapCity.size() == 1 && ((*mit).first) != NO_LIMIT_STRING )
			{
				sName += " " + (*mit).first;
			}
			else
			{
				sName += " " + sProvince;
			}
		}

	}
}