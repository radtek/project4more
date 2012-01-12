#ifndef _FMP_SEARCH_CRITERIA_H
#define _FMP_SEARCH_CRITERIA_H

#include <afxstr.h>
#include <algorithm>
#include <list>
using namespace std;

class CSearchCriteria
{
public:
	virtual void Clean()
	{
		m_lstStartProvince.clear();
		m_lstStartCity.clear();
		m_lstStartCounty.clear();
		m_lstEndProvince.clear();
		m_lstEndCity.clear();
		m_lstEndCounty.clear();
		m_lstCarType.clear();
		m_lstCarLength.clear();
		m_lstGoods.clear();
		m_lstGoodsType.clear();
	}
	virtual void Confirm(){}

	bool AddStartProvice(const CString& sProvince)
	{
		return AddData(sProvince, m_lstStartProvince);
	}
	bool AddStartCity(const CString& sCity)
	{
		return AddData(sCity, m_lstStartCity);
	}
	bool AddStartCounty(const CString& sCounty)
	{
		return AddData(sCounty, m_lstStartCounty);
	}
	bool AddEndProvice(const CString& sProvince)
	{
		return AddData(sProvince, m_lstEndProvince);
	}
	bool AddEndCity(const CString& sCity)
	{
		return AddData(sCity, m_lstEndCity);
	}
	bool AddEndCounty(const CString& sCounty)
	{
		return AddData(sCounty, m_lstEndCounty);
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

	void RemoveStartProvice(const CString& sProvince)
	{
		return RemoveData(sProvince, m_lstStartProvince);
	}
	void RemoveStartCity(const CString& sCity)
	{
		return RemoveData(sCity, m_lstStartCity);
	}
	void RemoveStartCounty(const CString& sCounty)
	{
		return RemoveData(sCounty, m_lstStartCounty);
	}
	void RemoveEndProvice(const CString& sProvince)
	{
		return RemoveData(sProvince, m_lstEndProvince);
	}
	void RemoveEndCity(const CString& sCity)
	{
		return RemoveData(sCity, m_lstEndCity);
	}
	void RemoveEndCounty(const CString& sCounty)
	{
		return RemoveData(sCounty, m_lstEndCounty);
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
	const list<CString>& GetStartProvinceList()const
	{
		return m_lstStartProvince;
	}
	const list<CString>& GetStartCityList()const
	{
		return m_lstStartCity;
	}
	const list<CString>& GetStartCountyList()const
	{
		return m_lstStartCounty;
	}
	const list<CString>& GetEndProvinceList()const
	{
		return m_lstEndProvince;
	}
	const list<CString>& GetEndCityList()const
	{
		return m_lstEndCity;
	}
	const list<CString>& GetEndCountyList()const
	{
		return m_lstEndCounty;
	}
	const list<CString>& GetCarTypeList()const
	{
		return m_lstCarType;
	}
	const list<CString>& GetCarLengthList()const
	{
		return m_lstCarLength;
	}

	const list<CString>& GetGoodsList()const
	{
		return m_lstGoods;
	}
	const list<CString>& GetGoodsTypeList()const
	{
		return m_lstGoodsType;
	}
protected:
	bool AddData(const CString& sData, list<CString>& lstData)
	{
		if( find(lstData.begin(), lstData.end(), sData) == lstData.end() )
		{
			lstData.push_back(sData);
			return true;
		}
		return false;
	}
	void RemoveData(const CString& sData, list<CString>& lstData)
	{
		lstData.remove(sData);
	}
protected:
	list<CString> m_lstStartProvince;
	list<CString> m_lstStartCity;
	list<CString> m_lstStartCounty;

	list<CString> m_lstEndProvince;
	list<CString> m_lstEndCity;
	list<CString> m_lstEndCounty;

	list<CString> m_lstGoods;
	list<CString> m_lstGoodsType;

	list<CString> m_lstCarType;
	list<CString> m_lstCarLength;

	//CString m_sStartProvince;
	//CString m_sStartCity;
	//CString m_sStartCounty;

	//CString m_sEndProvince;
	//CString m_sEndCity;
	//CString m_sEndCounty;

	//CString m_sCarType;
	//CString m_sCarLength;

	//CString m_sGoods;
	//CString m_sGoodsType;
	//
};
#endif