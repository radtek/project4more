#include "stdafx.h"
#include "SearchCriteria.h"

#ifndef FIRST_LEV_SPLITER
#define FIRST_LEV_SPLITER	'|'
#endif

#ifndef SECOND_LEV_SPLITER
#define SECOND_LEV_SPLITER  ';'
#endif

#ifndef THRID_LEV_SPLITER
#define THRID_LEV_SPLITER	','
#endif

void CSearchCriteria::FormatSearchString(string& sSearch)const
{
	//start address
	FormatAddr(m_mapStartAddr , sSearch);

	//snd address
	FormatAddr(m_mapEndAddr, sSearch);

	//car type
	FormatStringList(m_lstCarType, sSearch);

	//car length
	FormatStringList(m_lstCarLength, sSearch);

	//goods type
	FormatStringList(m_lstGoodsType, sSearch);

	//goods
	FormatStringList(m_lstGoods, sSearch);

	//Pubilsher
	FormatStringList(m_lstPublisher, sSearch);

	//Phone Number
	FormatStringList(m_lstPhoneNum, sSearch);

	//keyword
	sSearch += m_sKeyword;

	//wether match all
	sSearch += m_bMatchAll?"|ALL":"|ANY";

}

void CSearchCriteria::FormatAddr(const tdMapAddr& mapAddr, string& sAddr)const
{
	if( mapAddr.size() > 0 )
	{
		tdMapAddr::const_iterator it = mapAddr.begin(), end = mapAddr.end();
		for(it; it != end; ++it)
		{
			const string& sProvince = (*it).first;
			const tdMapCity& mapCity = (*it).second;
			if( mapCity.size() > 0 )
			{
				tdMapCity::const_iterator mit = mapCity.begin(), mend = mapCity.end();
				for(mit; mit != mend; ++mit)
				{
					const string& sCity = (*mit).first;
					const tdListCounty& lstCounty = (*mit).second;
					if( lstCounty.size() > 0 )
					{
						tdListCounty::const_iterator lit = lstCounty.begin(), lend = lstCounty.end();
						for(lit; lit != lend; ++lit)
						{
							sAddr += sProvince + THRID_LEV_SPLITER + sCity + THRID_LEV_SPLITER + *lit + SECOND_LEV_SPLITER;
						}
					}
					else
					{
						sAddr += sProvince + THRID_LEV_SPLITER + sCity + THRID_LEV_SPLITER + string(NO_LIMIT_STRING) + SECOND_LEV_SPLITER;
					}
				}
			}
			else
			{
				sAddr += sProvince + THRID_LEV_SPLITER + string(NO_LIMIT_STRING) + THRID_LEV_SPLITER + string(NO_LIMIT_STRING) + SECOND_LEV_SPLITER;
			}
		}
		sAddr.replace(sAddr.length()-1, 1, 1, FIRST_LEV_SPLITER);//replace the last ';' with  '|'
	}
	else
	{
		sAddr += string(NO_LIMIT_STRING) + THRID_LEV_SPLITER + string(NO_LIMIT_STRING) + THRID_LEV_SPLITER + string(NO_LIMIT_STRING) + FIRST_LEV_SPLITER;
	}

}
void CSearchCriteria::FormatStringList(const list<string>& lstData, string& sData, const string& sDefault/*=NO_LIMIT_STRING*/)const
{
	if( lstData.size() > 0 )
	{
		list<string>::const_iterator it = lstData.begin(), end = lstData.end();
		for(it; it != end; ++it)
		{
			sData += *it + SECOND_LEV_SPLITER;
		}
		sData.replace(sData.length()-1, 1, 1, FIRST_LEV_SPLITER);//replace the last ';' with  '|'
	}
	else
	{
		sData += sDefault + FIRST_LEV_SPLITER;
	}
}
