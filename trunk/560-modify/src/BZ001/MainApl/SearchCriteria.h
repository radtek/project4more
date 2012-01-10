#ifndef _FMP_SEARCH_CRITERIA_H
#define _FMP_SEARCH_CRITERIA_H

#include <afxstr.h>

class CSearchCriteria
{
public:
	virtual void Clean(){};
public:
	const CString& GetStartProvince()const
	{
		return m_sStartProvince;
	}
	const CString& GetStartCity()const
	{
		return m_sStartCity;
	}
	const CString& GetStartCounty()const
	{
		return m_sStartCounty;
	}
	const CString& GetEndProvince()const
	{
		return m_sEndProvince;
	}
	const CString& GetEndCity()const
	{
		return m_sEndCity;
	}
	const CString& GetEndCounty()const
	{
		return m_sEndCounty;
	}
	const CString& GetCarType()const
	{
		return m_sCarType;
	}
	const CString& GetCarLength()const
	{
		return m_sCarLength;
	}

	const CString& GetGoods()const
	{
		return m_sGoods;
	}
	const CString& GetGoodsType()const
	{
		return m_sGoodsType;
	}
protected:
	CString m_sStartProvince;
	CString m_sStartCity;
	CString m_sStartCounty;

	CString m_sEndProvince;
	CString m_sEndCity;
	CString m_sEndCounty;

	CString m_sCarType;
	CString m_sCarLength;

	CString m_sGoods;
	CString m_sGoodsType;
};
#endif