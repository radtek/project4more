#include "stdafx.h"
#include "CommDef.h"

vector<CString>  g_vecGoodsType;
vector<CString>  g_vecCarType;
vector<CString>  g_vecCarSize;
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