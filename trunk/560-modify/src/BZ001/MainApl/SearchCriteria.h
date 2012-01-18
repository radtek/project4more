#ifndef _FMP_SEARCH_CRITERIA_H
#define _FMP_SEARCH_CRITERIA_H

#include <afxstr.h>
#include <algorithm>
#include <list>
#include <string>
#include <map>
#include "CommDef.h"
using namespace std;

class CSearchCriteria
{
public:
	CSearchCriteria()
	{
		m_bMatchAll = true;
	}
	virtual void Clean()
	{
		m_mapStartAddr.clear();
		m_mapEndAddr.clear();

		m_lstCarType.clear();
		m_lstCarLength.clear();
		m_lstGoods.clear();
		m_lstGoodsType.clear();

		m_sKeyword.clear();
	}
	virtual void Confirm(){}


	bool AddStartAddr(const CString& sProvince, const CString& sCity, const CString& sCounty)
	{
		return AddAddr(sProvince, sCity, sCounty, m_mapStartAddr);
	}
	bool AddEndAddr(const CString& sProvince, const CString& sCity, const CString& sCounty)
	{
		return AddAddr(sProvince, sCity, sCounty, m_mapEndAddr);
	}

	bool RemoveStartAddr(const CString& sProvince, const CString& sCity, const CString& sCounty)
	{
		return RemoveAddr(sProvince, sCity, sCounty, m_mapStartAddr);
	}
	bool RemoveEndAddr(const CString& sProvince, const CString& sCity, const CString& sCounty)
	{
		return RemoveAddr(sProvince, sCity, sCounty, m_mapEndAddr);
	}

	bool AddCarType(const CString& sCarType)
	{
		return AddData(sCarType, m_lstCarType);
	}
	bool AddCarLength(const CString& sCarLength)
	{
		return AddData(sCarLength, m_lstCarLength);
	}
	bool AddGoods(const CString& sGoods)
	{
		return AddData(sGoods, m_lstGoods);
	}
	bool AddGoodsType(const CString& sGoodsType)
	{
		return AddData(sGoodsType, m_lstGoodsType);
	}

	void RemoveCarType(const CString& sCarType)
	{
		return RemoveData(sCarType, m_lstCarType);
	}
	void RemoveCarLength(const CString& sCarLength)
	{
		return RemoveData(sCarLength, m_lstCarLength);
	}
	void RemoveGoods(const CString& sGoods)
	{
		return RemoveData(sGoods, m_lstGoods);
	}
	void RemoveGoodsType(const CString& sGoodsType)
	{
		return RemoveData(sGoodsType, m_lstGoodsType);
	}
public:
	const tdMapAddr& GetStartAddrList()const
	{
		return m_mapStartAddr;
	}
	const tdMapAddr& GetEndAddrList()const
	{
		return m_mapEndAddr;
	}
	const list<string>& GetCarTypeList()const
	{
		return m_lstCarType;
	}
	const list<string>& GetCarLengthList()const
	{
		return m_lstCarLength;
	}

	const list<string>& GetGoodsList()const
	{
		return m_lstGoods;
	}
	const list<string>& GetGoodsTypeList()const
	{
		return m_lstGoodsType;
	}

	const list<string>& GetPublisherList()const
	{
		return m_lstPublisher;
	}

	const list<string>& GetPhoneNumList()const
	{
		return m_lstPhoneNum;
	}

	bool IsMatchAll()const
	{
		return m_bMatchAll;
	}

	const string& GetKeyword()const
	{
		return m_sKeyword;
	}

	int GetSearchType()const
	{
		return m_nSearchType;
	}
	void SetSearchType(int nSearchType)
	{
		m_nSearchType = nSearchType;
	}
protected:
	bool AddAddr(const CString& sProvince, const CString& sCity, const CString& sCounty, tdMapAddr& mapAddr)
	{
		tdMapCity& mapCity = mapAddr[string(sProvince)];
		if( sCity == NO_LIMIT_STRING )
		{
			mapCity.clear();
			tdListCounty& lstCounty = mapCity[NO_LIMIT_STRING];
			lstCounty.push_back(NO_LIMIT_STRING);
			return true;
		}
		
		mapCity.erase(NO_LIMIT_STRING);

		tdMapCity::iterator it = mapCity.find(string(sCity));
		if( it == mapCity.end() )
		{
			tdListCounty& lstCounty = mapCity[string(sCity)];
			lstCounty.push_back(string(sCounty));
			return true;

		}
		tdListCounty& lstCounty = (*it).second;
		if( sCounty == NO_LIMIT_STRING )
		{
			lstCounty.clear();
		}
		else
		{
			lstCounty.remove(NO_LIMIT_STRING);
		}
		return AddData(sCounty, lstCounty);
	}
	bool RemoveAddr(const CString& sProvince, const CString& sCity, const CString& sCounty, tdMapAddr& mapAddr)
	{
		tdMapAddr::iterator it = mapAddr.find(string(sProvince));
		if( it == mapAddr.end() )
		{
			return false;
		}
		tdMapCity& mapCity = (*it).second;
		if( sCity == NO_LIMIT_STRING && sCounty == NO_LIMIT_STRING)
		{
			mapCity.clear();
			mapAddr.erase(it);
			return true;
		}

		if( !sCity.IsEmpty() )
		{
			tdMapCity::iterator cityIt = mapCity.find(string(sCity));
			if( cityIt == mapCity.end() )
			{
				return false;
			}

			tdListCounty& lstCounty = (*cityIt).second;
			if( sCounty == NO_LIMIT_STRING )
			{
				lstCounty.clear();
				mapCity.erase(cityIt);
				if( mapCity.size() == 0 )
				{
					mapAddr.erase(it);
				}
			}
			else
			{
				lstCounty.remove(string(sCounty));
				if( lstCounty.size() == 0 )
				{
					mapCity.erase(cityIt);
					if( mapCity.size() == 0 )
					{
						mapAddr.erase(it);
					}
				}
			}
		}
		else
		{
			tdMapCity::iterator cit = mapCity.begin(), cend = mapCity.end();
			for(cit; cit != cend; ++cit)
			{
				tdListCounty& lstCounty = (*cit).second;
				tdListCounty::iterator lit = find(lstCounty.begin(), lstCounty.end(), string(sCounty));
				if( lit != lstCounty.end() )
				{
					lstCounty.erase(lit);
					break;
				}
			}
		}
		return true;
	}


	bool AddData(const CString& sData, list<string>& lstData)
	{
		if( find(lstData.begin(), lstData.end(), string(sData)) == lstData.end() )
		{
			lstData.push_back(string(sData));
			return true;
		}
		return false;
	}
	void RemoveData(const CString& sData, list<string>& lstData)
	{
		lstData.remove(string(sData));
	}
public:
	void FormatSearchString(string& sGoodsSearch)const;
	void FormatAddr(const tdMapAddr& mapAddr, string& sAddr)const;
	void FormatStringList(const list<string>& lstData, string& sData, const string& sDefault=NO_LIMIT_STRING)const;
protected:

	map<string ,map<string, list<string>>> m_mapStartAddr;
	map<string ,map<string, list<string>>> m_mapEndAddr;
	
	list<string> m_lstGoods;
	list<string> m_lstGoodsType;

	list<string> m_lstCarType;
	list<string> m_lstCarLength;
	list<string> m_lstPublisher;
	list<string> m_lstPhoneNum;

	string		m_sKeyword;

	bool		m_bMatchAll;
	int			m_nSearchType;//can be one or the combination of ESearchType
};
#endif