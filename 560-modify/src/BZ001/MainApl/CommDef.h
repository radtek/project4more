#ifndef _FMP_COMM_DEFINE_H
#define _FMP_COMM_DEFINE_H

#include <afxwin.h>
#include "CountryRegion.h"
#include <string>
#include <map>
#include <vector>
#include <string>
using std::map;
using std::vector;
using std::string;


typedef list<string> tdListCounty;
typedef map<string, tdListCounty> tdMapCity;
typedef map<string, tdMapCity> tdMapProvince, tdMapAddr;

typedef vector<Province> tdVecProvince;
typedef vector<City>	tdVecCity;
typedef vector<County>  tdVecCounty;


extern vector<CString>	g_vecSearchGoods;
extern vector<CString>  g_vecSearchGoodsType;
extern vector<CString>  g_vecSearchCarType;
extern vector<CString>  g_vecSearchCarSize;

extern vector<CString>  g_vecPrices1;
extern vector<CString>  g_vecPrices2;

extern vector<CString>	g_goodsType;
extern vector<CString>	g_goodsUnit;
extern vector<CString>	g_truckLength;
extern vector<CString>	g_truckType;
extern vector<CString>	g_priceType;

extern vector<CString>	g_priceTypeFor3;
extern vector<CString> g_commonDuanyu;
extern vector<CString> g_commonZi;
extern vector<CString> g_commonCi;
extern vector<CString> g_PeihuoInfo;

extern CountryRegion*   g_pCountryRegion;

extern CMenu g_menuGoods1;
extern CMenu g_menuGoods2;
extern CMenu g_menuGoods3;
extern CMenu g_menuGoods3_MS1;//material steel1
extern CMenu g_menuGoods3_MS2;//material steel2
extern CMenu g_menuGoods3_CC;//coal and carbon
extern CMenu g_menuGoods3_MUV1;//melon and fruit and vegetable
extern CMenu g_menuGoods3_MUV2;//melon and fruit and vegetable
extern CMenu g_menuGoods3_Vehicle;//Vehicle
extern CMenu g_menuGoods3_SubFood;//subsidiary foodstuff
extern CMenu g_menuGoods3_FarmProduce;//Farm Produce
extern CMenu g_menuGoods3_Paper;//paper
extern CMenu g_menuGoods3_GW;//grass and wood
extern CMenu g_menuGoods3_Animal;//Animal
extern CMenu g_menuGoods3_Electric;//electric
extern CMenu g_menuGoods3_SilkHail;//Silk and Hail
extern CMenu g_menuGoods3_Other;//Silk and Hail


struct InSearchGoods;
struct InSearchCars;

enum ESearchType{eSearchType_Goods = 0x01, eSearchType_Car = 0x02, eSearchType_SpecialLine = 0x04, eSearchType_BulkGoods = 0x08};

#define NO_LIMIT_STRING "²»ÏÞ"


const tdVecCity* GetCities(const CString& sProvince);
const tdVecCounty* GetCounties(const CString& sProvince, const CString& sCity);
const string& GetCity(const CString& sProvince, int nCityIndex);


const void GetProvincesName(vector<CString> &vecProvincesName);
const void GetCitiesNameByProvince(vector<CString> &vecCitiesName, const CString &strProvince);
int CheckAddress(const CString& sProvince, const CString& sCity, const CString& sCounty);
bool IsSpecialProvince(const CString& sProvince);

const void GetCountiesNameByProvinceAndCity(vector<CString> &vecCountiesName, const CString &strProvince, const CString &strCity);

void FormatGoodsSearchString(const InSearchGoods& goodsSearch, string& sGoodsSearch);
void FormatCarsSearchString(const InSearchCars& goodsSearch, string& sCarsSearch);

void InitCommData();

#endif