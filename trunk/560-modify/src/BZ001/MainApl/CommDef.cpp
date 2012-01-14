#include "stdafx.h"
#include "CommDef.h"
#include "GLB.h"

vector<CString>	 g_vecSearchGoods;
vector<CString>  g_vecSearchGoodsType;
vector<CString>  g_vecSearchCarType;
vector<CString>  g_vecSearchCarSize;

vector<CString>  g_vecPrices1;
vector<CString>  g_vecPrices2;
CountryRegion*   g_pCountryRegion;

vector<CString>	g_goodsType;
vector<CString>	g_goodsUnit;
vector<CString>	g_truckLength;
vector<CString>	g_truckType;
vector<CString>	g_priceType;

vector<CString>	g_priceTypeFor3;
vector<CString> g_commonDuanyu;
vector<CString> g_commonZi;
vector<CString> g_commonCi;
vector<CString> g_PeihuoInfo;

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
const string& GetCity(const CString& sProvince, int nCityIndex)
{
	const tdVecCity* pCities = GetCities(sProvince);
	if( pCities == NULL || nCityIndex<0 || nCityIndex>=pCities->size() )
	{
		return "";
	}

	return (*pCities)[nCityIndex].name;
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

static void InitSearchGoodsType()
{
	g_vecSearchGoodsType.push_back("����");
	g_vecSearchGoodsType.push_back("�㵣");
	g_vecSearchGoodsType.push_back("�׻�");
	g_vecSearchGoodsType.push_back("�ݻ�");
	g_vecSearchGoodsType.push_back("�ػ�");
	g_vecSearchGoodsType.push_back("�ջ�");
	g_vecSearchGoodsType.push_back("Σ��");
	g_vecSearchGoodsType.push_back("С��");
	g_vecSearchGoodsType.push_back("���̻�");
	g_vecSearchGoodsType.push_back("�س̻�");
	g_vecSearchGoodsType.push_back("������");
	g_vecSearchGoodsType.push_back("���ڻ�");
	g_vecSearchGoodsType.push_back("��һ�");
}
static void InitSearchGoods()
{
	g_vecSearchGoods.push_back("ԭ��");
	g_vecSearchGoods.push_back("����"); 
	g_vecSearchGoods.push_back("����");
	g_vecSearchGoods.push_back("ú̿");
	g_vecSearchGoods.push_back("���");
	g_vecSearchGoods.push_back("���");
	g_vecSearchGoods.push_back("�豸");
	g_vecSearchGoods.push_back("��е");
	g_vecSearchGoods.push_back("����");
	g_vecSearchGoods.push_back("����");
	g_vecSearchGoods.push_back("�Ҿ�");
	g_vecSearchGoods.push_back("����");
	g_vecSearchGoods.push_back("ҩ��");
	g_vecSearchGoods.push_back("ҽҩ");
	g_vecSearchGoods.push_back("�Լ�");
	g_vecSearchGoods.push_back("����");
	g_vecSearchGoods.push_back("���");
	g_vecSearchGoods.push_back("��װ");
	g_vecSearchGoods.push_back("��ʯ");
	g_vecSearchGoods.push_back("ʳƷ");
	g_vecSearchGoods.push_back("��ʳ");
	g_vecSearchGoods.push_back("�߲�");
	g_vecSearchGoods.push_back("ˮ��");
	g_vecSearchGoods.push_back("�Ϲ�");
	g_vecSearchGoods.push_back("����");
	g_vecSearchGoods.push_back("����");
	g_vecSearchGoods.push_back("����");
	g_vecSearchGoods.push_back("����Ʒ");
	g_vecSearchGoods.push_back("��֯Ʒ");
	g_vecSearchGoods.push_back("��ױƷ");
	g_vecSearchGoods.push_back("Σ��Ʒ");
	g_vecSearchGoods.push_back("ũ��Ʒ");
	g_vecSearchGoods.push_back("����Ʒ");
	g_vecSearchGoods.push_back("ϴ��Ʒ");
	g_vecSearchGoods.push_back("����Ʒ");
	g_vecSearchGoods.push_back("���Ʒ");
	g_vecSearchGoods.push_back("���Ӳ�Ʒ");
	g_vecSearchGoods.push_back("�Ṥ��Ʒ");
	g_vecSearchGoods.push_back("�����豸");
	g_vecSearchGoods.push_back("ʯ����Ʒ");
	g_vecSearchGoods.push_back("�칫�豸");
	g_vecSearchGoods.push_back("�䶳ʳƷ");
	g_vecSearchGoods.push_back("Ͱװ����");
	g_vecSearchGoods.push_back("��װ����");
}
static void InitSearchCarType()
{
	g_vecSearchCarType.push_back("��ͨ��");
	g_vecSearchCarType.push_back("ǰ�ĺ���");
	g_vecSearchCarType.push_back("ǰ�ĺ��");
	g_vecSearchCarType.push_back("ǰ�ĺ�ʮ");
	g_vecSearchCarType.push_back("����");
	g_vecSearchCarType.push_back("ƽ�峵");
	g_vecSearchCarType.push_back("������");
	g_vecSearchCarType.push_back("��װ��");
	g_vecSearchCarType.push_back("��س�");
	g_vecSearchCarType.push_back("���س�");
	g_vecSearchCarType.push_back("�����");
	g_vecSearchCarType.push_back("���ų�");
	g_vecSearchCarType.push_back("��ж��");
	g_vecSearchCarType.push_back("���ճ�");
	g_vecSearchCarType.push_back("��ҳ�");
	g_vecSearchCarType.push_back("���³�");
	g_vecSearchCarType.push_back("˫�ų�");
	g_vecSearchCarType.push_back("�ӳ��ҳ�");
	g_vecSearchCarType.push_back("�ޱ���");
	g_vecSearchCarType.push_back("�����ӳ�");
	g_vecSearchCarType.push_back("�ߵͰ�");
	g_vecSearchCarType.push_back("������");
}
static void InitSearchCarSize()
{
	g_vecSearchCarSize.push_back("4");
	g_vecSearchCarSize.push_back("4.2");
	g_vecSearchCarSize.push_back("4.3");
	g_vecSearchCarSize.push_back("4.5");
	g_vecSearchCarSize.push_back("4.8");
	g_vecSearchCarSize.push_back("5");
	g_vecSearchCarSize.push_back("5.8");
	g_vecSearchCarSize.push_back("6");
	g_vecSearchCarSize.push_back("6.2");
	g_vecSearchCarSize.push_back("6.8");
	g_vecSearchCarSize.push_back("7");
	g_vecSearchCarSize.push_back("7.2");
	g_vecSearchCarSize.push_back("7.4");
	g_vecSearchCarSize.push_back("7.8");
	g_vecSearchCarSize.push_back("8");
	g_vecSearchCarSize.push_back("8.7");
	g_vecSearchCarSize.push_back("8.8");
	g_vecSearchCarSize.push_back("9");
	g_vecSearchCarSize.push_back("9.6");
	g_vecSearchCarSize.push_back("12.5");
	g_vecSearchCarSize.push_back("13");
	g_vecSearchCarSize.push_back("13.5");
	g_vecSearchCarSize.push_back("17.5");
}

void InitCommData()
{
	InitSearchGoodsType();
	InitSearchGoods();
	InitSearchCarSize();
	InitSearchCarType();


	g_goodsType.push_back("����");
	g_goodsType.push_back("�㵣");
	g_goodsType.push_back("�ػ�");
	g_goodsType.push_back("�ݻ�");
	g_goodsType.push_back("Ʈ��");
	g_goodsType.push_back("�ջ�");
	g_goodsType.push_back("����");
	g_goodsType.push_back("�豸");
	g_goodsType.push_back("�߲�");
	g_goodsType.push_back("����");
	g_goodsType.push_back("ľ��");
	g_goodsType.push_back("ʳƷ");
	g_goodsType.push_back("��ʳ");
	g_goodsType.push_back("��Ʒ");
	g_goodsType.push_back("ũ����Ʒ");
	g_goodsType.push_back("���²���");
	g_goodsType.push_back("ˮ��");
	g_goodsType.push_back("��ʯ");
	g_goodsType.push_back("ú");
	g_goodsType.push_back("ҽҩ");
	g_goodsType.push_back("�Ҿ�");
	g_goodsType.push_back("ֽ��");
	g_goodsType.push_back("Σ��Ʒ");
	g_goodsType.push_back("���װ");
	g_goodsType.push_back("���");
	g_goodsType.push_back("С��");
	g_goodsType.push_back("�Ӵ���");

	g_goodsUnit.push_back("��");
	g_goodsUnit.push_back("��");
	g_goodsUnit.push_back("��");
	g_goodsUnit.push_back("��");

	g_truckLength.push_back("4��");
	g_truckLength.push_back("4.2��");
	g_truckLength.push_back("4.3��");
	g_truckLength.push_back("4.5��");
	g_truckLength.push_back("4.8��");
	g_truckLength.push_back("5��");
	g_truckLength.push_back("5.8��");
	g_truckLength.push_back("6��");
	g_truckLength.push_back("6.2��");
	g_truckLength.push_back("6.8��");
	g_truckLength.push_back("7��");
	g_truckLength.push_back("7.2��");
	g_truckLength.push_back("7.4��");
	g_truckLength.push_back("7.8��");
	g_truckLength.push_back("8��");
	g_truckLength.push_back("8.7��");
	g_truckLength.push_back("8.8��");
	g_truckLength.push_back("9��");
	g_truckLength.push_back("9.6��");
	g_truckLength.push_back("12.5��");
	g_truckLength.push_back("13��");
	g_truckLength.push_back("13.5��");
	g_truckLength.push_back("17.5��");

	g_truckType.push_back("��ͨ��");
	g_truckType.push_back("ǰ�ĺ���");
	g_truckType.push_back("ǰ�ĺ��");
	g_truckType.push_back("ǰ�ĺ�ʮ");
	g_truckType.push_back("����");
	g_truckType.push_back("ƽ�峵");
	g_truckType.push_back("������");
	g_truckType.push_back("��װ��");
	g_truckType.push_back("��س�");
	g_truckType.push_back("���س�");
	g_truckType.push_back("�����");
	g_truckType.push_back("���ų�");
	g_truckType.push_back("��ж��");
	g_truckType.push_back("���ճ�");
	g_truckType.push_back("��ҳ�");
	g_truckType.push_back("���³�");
	g_truckType.push_back("˫�ų�");
	g_truckType.push_back("�ӳ��ҳ�");
	g_truckType.push_back("�ޱ���");
	g_truckType.push_back("�����ӳ�");
	g_truckType.push_back("�ߵͰ�");
	g_truckType.push_back("������");

	g_priceType.push_back("Ԫ/��");
	g_priceType.push_back("Ԫ/��");
	g_priceType.push_back("Ԫ/��");
	g_priceType.push_back("Ԫ/��");
	g_priceType.push_back("Ԫ/�ܼ�");
	g_priceType.push_back("Ԫ/����");
	g_priceType.push_back("����");
	g_priceType.push_back("ȫ��");
	g_priceType.push_back("����");
	g_priceType.push_back("�۸��");
	g_priceType.push_back("�۸������");
	g_priceType.push_back("��Ǯ����");
	g_priceType.push_back("�۸߼���");

	g_priceTypeFor3.push_back("�۸��");
	g_priceTypeFor3.push_back("�۸߼���");
	g_priceTypeFor3.push_back("�۸�����");
	g_priceTypeFor3.push_back("�۸������");
	g_priceTypeFor3.push_back("ȫ��");

	g_commonDuanyu.push_back("�泵װ");
	g_commonDuanyu.push_back("���Ѷ���");
	g_commonDuanyu.push_back("����װ��");
	g_commonDuanyu.push_back("��ռ�ռ�");
	g_commonDuanyu.push_back("����ֻ�");
	g_commonDuanyu.push_back("������Ϣ");
	g_commonDuanyu.push_back("��һ����װ");
	g_commonDuanyu.push_back("���ڱ�վ");
	g_commonDuanyu.push_back("������վ��");
	g_commonDuanyu.push_back("��������");
	g_commonDuanyu.push_back("�����ܷ�");
	g_commonDuanyu.push_back("������һ����");
	g_commonDuanyu.push_back("���충��");
	g_commonDuanyu.push_back("����װ��");
	g_commonDuanyu.push_back("����Ҳ����װ");
	g_commonDuanyu.push_back("��ಿ����ֻ���");
	g_commonDuanyu.push_back("���С��");
	g_commonDuanyu.push_back("���Ѷ����������");
	g_commonDuanyu.push_back("װ����һ���˷ѣ���������");
	g_commonDuanyu.push_back("������ж����ѹ��");
	g_commonDuanyu.push_back("������");
	g_commonDuanyu.push_back("���λ");
	g_commonDuanyu.push_back("����ϵ");
	g_commonDuanyu.push_back("�ٻص���ϵ");

	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("ռ");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("ʣ");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("װ");
	g_commonZi.push_back("��");
	g_commonZi.push_back("ÿ");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("Ҳ");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("ǰ");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("С");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("˫");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("��");
	g_commonZi.push_back("λ");
	g_commonZi.push_back("ռ");

	g_commonCi.push_back("����");
	g_commonCi.push_back("����");
	g_commonCi.push_back("����");
	g_commonCi.push_back("����");
	g_commonCi.push_back("����");
	g_commonCi.push_back("����");
	g_commonCi.push_back("����");
	g_commonCi.push_back("ÿ��");
	g_commonCi.push_back("��װ");
	g_commonCi.push_back("Ͱװ");
	g_commonCi.push_back("��װ");
	g_commonCi.push_back("����");
	g_commonCi.push_back("���");
	g_commonCi.push_back("��;");
	g_commonCi.push_back("��;");
	g_commonCi.push_back("����");
	g_commonCi.push_back("��վ");
	g_commonCi.push_back("����");
	g_commonCi.push_back("�س�");
	g_commonCi.push_back("ר��");
	g_commonCi.push_back("����");
	g_commonCi.push_back("����");
	g_commonCi.push_back("����");
	g_commonCi.push_back("����");
	g_commonCi.push_back("����");
	g_commonCi.push_back("����");
	g_commonCi.push_back("����");
	g_commonCi.push_back("���");
	g_commonCi.push_back("��λ");
	g_commonCi.push_back("��ϵ");
	g_commonCi.push_back("�˷�");
	g_commonCi.push_back("����");
	g_commonCi.push_back("����");

	g_PeihuoInfo.push_back("1");
	g_PeihuoInfo.push_back("2");
	g_PeihuoInfo.push_back("3");
	g_PeihuoInfo.push_back("4");
	g_PeihuoInfo.push_back("5");
	g_PeihuoInfo.push_back("6");
	g_PeihuoInfo.push_back("7");
	g_PeihuoInfo.push_back("8");
	g_PeihuoInfo.push_back("9");
	g_PeihuoInfo.push_back("0");
	g_PeihuoInfo.push_back("��");
	g_PeihuoInfo.push_back("��");
	g_PeihuoInfo.push_back("Ҫ");
	g_PeihuoInfo.push_back("��");
	g_PeihuoInfo.push_back("��");
	g_PeihuoInfo.push_back("��");
	g_PeihuoInfo.push_back("��");
	g_PeihuoInfo.push_back("��");
	g_PeihuoInfo.push_back("ȥ");
	g_PeihuoInfo.push_back("��");
	g_PeihuoInfo.push_back("��");
	g_PeihuoInfo.push_back("��");
	g_PeihuoInfo.push_back("��");
	g_PeihuoInfo.push_back("��");
	g_PeihuoInfo.push_back("Ԫ");
	g_PeihuoInfo.push_back("Ԫ/��");
	g_PeihuoInfo.push_back("��λ");
}



#ifndef FIRST_LEV_SPLITER
#define FIRST_LEV_SPLITER	'|'
#endif

#ifndef SECOND_LEV_SPLITER
#define SECOND_LEV_SPLITER  ';'
#endif

#ifndef THRID_LEV_SPLITER
#define THRID_LEV_SPLITER	','
#endif

static void FormatAddr(const tdMapAddr& mapAddr, string& sAddr)
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
static void FormatStringList(const list<string>& lstData, string& sData, const string& sDefault=NO_LIMIT_STRING)
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

void FormatGoodsSearchString(const InSearchGoods& goodsSearch, string& sGoodsSearch)
{
	//start address
	FormatAddr(goodsSearch.lstStartAddr, sGoodsSearch);

	//snd address
	FormatAddr(goodsSearch.lstEndAddr, sGoodsSearch);

	//car type
	FormatStringList(goodsSearch.lstCarType, sGoodsSearch);

	//car length
	FormatStringList(goodsSearch.lstCarLength, sGoodsSearch);

	//goods type
	FormatStringList(goodsSearch.lstGoodsType, sGoodsSearch);

	//goods
	FormatStringList(goodsSearch.lstGoods, sGoodsSearch);

	//Pubilsher
	FormatStringList(goodsSearch.lstPublisher, sGoodsSearch);

	//Phone Number
	FormatStringList(goodsSearch.lstPhoneNum, sGoodsSearch);

	//keyword
	sGoodsSearch += goodsSearch.sKeyword;

	//wether match all
	sGoodsSearch += goodsSearch.bMatchAll?"|ALL":"|ANY";

}

void FormatCarsSearchString(const InSearchCars& carsSearch, string& sCarsSearch)
{
	//start address
	FormatAddr(carsSearch.lstStartAddr, sCarsSearch);

	//snd address
	FormatAddr(carsSearch.lstEndAddr, sCarsSearch);

	//car type
	FormatStringList(carsSearch.lstCarType, sCarsSearch);

	//car length
	FormatStringList(carsSearch.lstCarLength, sCarsSearch);

	//goods type
	FormatStringList(carsSearch.lstGoodsType, sCarsSearch);

	//goods
	FormatStringList(carsSearch.lstGoods, sCarsSearch);

	//Pubilsher
	FormatStringList(carsSearch.lstPublisher, sCarsSearch);

	//Phone Number
	FormatStringList(carsSearch.lstPhoneNum, sCarsSearch);

	//keyword
	sCarsSearch += carsSearch.sKeyword;

	//whether match all
	sCarsSearch += carsSearch.bMatchAll?"|ALL":"|ANY";
}
