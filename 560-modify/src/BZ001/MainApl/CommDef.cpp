#include "stdafx.h"
#include "CommDef.h"

vector<CString>  g_vecGoodsType;
vector<CString>  g_vecCarType;
vector<CString>  g_vecCarSize;
vector<CString>  g_vecPrices1;
vector<CString>  g_vecPrices2;
CountryRegion*   g_pCountryRegion;

vector<string>	g_goodsType;
vector<string>	g_goodsUnit;
vector<string>	g_truckLength;
vector<string>	g_truckType;
vector<string>	g_priceType;

const tdVecCity* GetCities(const CString& sProvince)
{
	if(g_pCountryRegion == NULL)
	{
		return NULL;
	}
	vector<Province>::iterator it = g_pCountryRegion->govProvince.begin(), end = g_pCountryRegion->govProvince.end();
	for(it; it != end; ++it)
	{
		const Province& prov = *it;
		if(sProvince == prov.name.c_str())
		{
			return &prov.govCity;
		}
	}
	return NULL;
}

const tdVecCounty* GetCounties(const CString& sProvince, const CString& sCity)
{
	const tdVecCity* pCities = GetCities(sProvince);
	if( pCities == NULL )
	{
		return NULL;
	}
	tdVecCity::const_iterator it = pCities->begin(), end = pCities->end();
	for(it; it != end; ++it)
	{
		const City& oCity = *it;
		if(sCity == oCity.name.c_str() )
		{
			return &oCity.govCounty;
		}
	}
	return NULL;
}

const void GetProvincesName(vector<CString> &vecProvincesName)
{
	if (g_pCountryRegion)
	{
		vecProvincesName.clear();

		vector<Province>::const_iterator it = g_pCountryRegion->govProvince.begin(), end = g_pCountryRegion->govProvince.end();
		for(it; it != end; ++it)
			vecProvincesName.push_back(it->name.c_str());
	}
}

const void GetCitiesNameByProvince(vector<CString> &vecCitiesName, const CString &strProvince)
{
	const tdVecCity *pVecCities = GetCities(strProvince);

	if (pVecCities)
	{
		vecCitiesName.clear();

		tdVecCity::const_iterator it = pVecCities->begin(), end = pVecCities->end();
		for(it; it != end; ++it)
			vecCitiesName.push_back(it->name.c_str());
	}
}

const void GetCountiesNameByProvinceAndCity(vector<CString> &vecCountiesName, const CString &strProvince, const CString &strCity)
{
	const tdVecCounty *pVecCounties = GetCounties(strProvince, strCity);

	if (pVecCounties)
	{
		vecCountiesName.clear();

		tdVecCounty::const_iterator it = pVecCounties->begin(), end = pVecCounties->end();
		for(it; it != end; ++it)
			vecCountiesName.push_back(it->name.c_str());
	}
}

void InitCommData()
{
	g_goodsType.push_back("整车");
	g_goodsType.push_back("零担");
	g_goodsType.push_back("重货");
	g_goodsType.push_back("泡货");
	g_goodsType.push_back("飘货");
	g_goodsType.push_back("普货");
	g_goodsType.push_back("化工");
	g_goodsType.push_back("设备");
	g_goodsType.push_back("蔬菜");
	g_goodsType.push_back("建材");
	g_goodsType.push_back("木材");
	g_goodsType.push_back("食品");
	g_goodsType.push_back("粮食");
	g_goodsType.push_back("冻品");
	g_goodsType.push_back("农副产品");
	g_goodsType.push_back("保温材料");
	g_goodsType.push_back("水果");
	g_goodsType.push_back("矿石");
	g_goodsType.push_back("煤");
	g_goodsType.push_back("医药");
	g_goodsType.push_back("家具");
	g_goodsType.push_back("纸箱");
	g_goodsType.push_back("危化品");
	g_goodsType.push_back("随便装");
	g_goodsType.push_back("配件");
	g_goodsType.push_back("小货");
	g_goodsType.push_back("捎带货");

	g_goodsUnit.push_back("吨");
	g_goodsUnit.push_back("方");
	g_goodsUnit.push_back("件");
	g_goodsUnit.push_back("车");

	g_truckLength.push_back("4米");
	g_truckLength.push_back("4.2米");
	g_truckLength.push_back("4.3米");
	g_truckLength.push_back("4.5米");
	g_truckLength.push_back("4.8米");
	g_truckLength.push_back("5米");
	g_truckLength.push_back("5.8米");
	g_truckLength.push_back("6米");
	g_truckLength.push_back("6.2米");
	g_truckLength.push_back("6.8米");
	g_truckLength.push_back("7米");
	g_truckLength.push_back("7.2米");
	g_truckLength.push_back("7.4米");
	g_truckLength.push_back("7.8米");
	g_truckLength.push_back("8米");
	g_truckLength.push_back("8.7米");
	g_truckLength.push_back("8.8米");
	g_truckLength.push_back("9米");
	g_truckLength.push_back("9.6米");
	g_truckLength.push_back("12.5米");
	g_truckLength.push_back("13米");
	g_truckLength.push_back("13.5米");
	g_truckLength.push_back("17.5米");

	g_truckType.push_back("普通车");
	g_truckType.push_back("前四后四");
	g_truckType.push_back("前四后八");
	g_truckType.push_back("敞篷车");
	g_truckType.push_back("平板车");
	g_truckType.push_back("高栏车");
	g_truckType.push_back("集装箱");
	g_truckType.push_back("冷藏车");
	g_truckType.push_back("起重车");
	g_truckType.push_back("后八轮");
	g_truckType.push_back("单桥车");
	g_truckType.push_back("自卸车");
	g_truckType.push_back("半封闭车");
	g_truckType.push_back("半挂车");
	g_truckType.push_back("保温车");
	g_truckType.push_back("双桥车");
	g_truckType.push_back("加长挂车");
	g_truckType.push_back("棉被车");
	g_truckType.push_back("前四后十");
	g_truckType.push_back("大笼子车");
	g_truckType.push_back("高低板");
	g_truckType.push_back("翻斗车");

	g_priceType.push_back("元/车");
	g_priceType.push_back("元/吨");
	g_priceType.push_back("元/方");
	g_priceType.push_back("元/件");
	g_priceType.push_back("元/总价");
	g_priceType.push_back("元/公斤");
	g_priceType.push_back("公斤");
	g_priceType.push_back("全价");
	g_priceType.push_back("面议");
	g_priceType.push_back("价格高");
	g_priceType.push_back("价格好商");
	g_priceType.push_back("给钱就走");
	g_priceType.push_back("价高急走");
}