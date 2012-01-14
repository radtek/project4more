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
	g_truckType.push_back("ǰ�ĺ�ʮ");
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
	g_priceType.push_back("�۸����");
	g_priceType.push_back("��Ǯ����");
	g_priceType.push_back("�۸߼���");
}