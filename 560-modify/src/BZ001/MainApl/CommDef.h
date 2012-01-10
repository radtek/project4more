#ifndef _FMP_COMM_DEFINE_H
#define _FMP_COMM_DEFINE_H

#include "CountryRegion.h"
#include <map>
#include <vector>
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

extern CountryRegion*   g_pCountryRegion;



const tdVecCity* GetCities(const CString& sProvince);
const tdVecCounty* GetCounties(const CString& sProvince, const CString& sCity);

void InitCommData();

#endif