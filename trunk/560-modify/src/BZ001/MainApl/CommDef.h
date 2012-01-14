#ifndef _FMP_COMM_DEFINE_H
#define _FMP_COMM_DEFINE_H

#include "CountryRegion.h"
#include <map>
#include <vector>
#include <string>
using std::map;
using std::vector;

typedef vector<Province> tdVecProvince;
typedef vector<City>	tdVecCity;
typedef vector<County>  tdVecCounty;


extern vector<CString>	g_vecGoods;
extern vector<CString>  g_vecGoodsType;
extern vector<CString>  g_vecCarType;
extern vector<CString>  g_vecCarSize;
extern vector<CString>  g_vecPrices1;
extern vector<CString>  g_vecPrices2;

extern vector<string>	g_goodsType;
extern vector<string>	g_goodsUnit;
extern vector<string>	g_truckLength;
extern vector<string>	g_truckType;
extern vector<string>	g_priceType;

extern CountryRegion*   g_pCountryRegion;

enum ESearchType{eSearchType_Goods = 0x01, eSearchType_Car = 0x02, eSearchType_SpecialLine = 0x04, eSearchType_BulkGoods = 0x08};

#define NO_LIMIT_STRING "²»ÏÞ"


const tdVecCity* GetCities(const CString& sProvince);
const tdVecCounty* GetCounties(const CString& sProvince, const CString& sCity);

const void GetProvincesName(vector<CString> &vecProvincesName);
const void GetCitiesNameByProvince(vector<CString> &vecCitiesName, const CString &strProvince);

const void GetCountiesNameByProvinceAndCity(vector<CString> &vecCountiesName, const CString &strProvince, const CString &strCity);

void InitCommData();

#endif