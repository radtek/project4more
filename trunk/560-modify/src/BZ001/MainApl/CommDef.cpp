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

CMenu g_menuGoods1;
CMenu g_menuGoods2;
CMenu g_menuGoods3;
CMenu g_menuGoods3_MS1;//material steel1
CMenu g_menuGoods3_MS2;//material steel2
CMenu g_menuGoods3_CC;//coal and carbon
CMenu g_menuGoods3_MUV1;//melon and fruit and vegetable
CMenu g_menuGoods3_MUV2;//melon and fruit and vegetable
CMenu g_menuGoods3_Vehicle;//Vehicle
CMenu g_menuGoods3_SubFood;//subsidiary foodstuff
CMenu g_menuGoods3_FarmProduce;//Farm Produce
CMenu g_menuGoods3_Paper;//paper
CMenu g_menuGoods3_GW;//grass and wood
CMenu g_menuGoods3_Animal;//Animal
CMenu g_menuGoods3_Electric;//electric
CMenu g_menuGoods3_SilkHail;//Silk and Hail
CMenu g_menuGoods3_Other;//Silk and Hail


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
		{
			vecCountiesName.push_back(it->name.c_str());
		}
		if( find(vecCountiesName.begin(), vecCountiesName.end(), NO_LIMIT_STRING) == vecCountiesName.end() )
		{
			vecCountiesName.push_back(NO_LIMIT_STRING);
		}
	}
}

int CheckAddress(const CString& sProvince, const CString& sCity, const CString& sCounty)
{
	if( sProvince.IsEmpty() )
	{
		return -1;
	}
	if( sCity.IsEmpty() )
	{
		return -2;
	}
	//if( sCounty.IsEmpty() )
	//{
	//	return -3;
	//}

	vector<CString> vecCity;
	GetCitiesNameByProvince(vecCity, sProvince);
	if( find(vecCity.begin(), vecCity.end(), sCity) == vecCity.end() )
	{
		return -4;
	}

	if( sCounty.IsEmpty() || sCounty == NO_LIMIT_STRING )
	{
		return 0;
	}

	vector<CString> vecCountiesName;
	GetCountiesNameByProvinceAndCity(vecCountiesName, sProvince, sCity);

	bool bFind = false;
	vector<CString>::iterator it = vecCountiesName.begin(), end = vecCountiesName.end();
	for(it; it != end; ++it)
	{
		if( (*it).Find(sCounty) != -1 )
		{
			return 0;
		}
	}
	return -5;
}

bool IsSpecialProvince(const CString& sProvince)
{
	return sProvince == "�Ϻ�" || sProvince == "����" || sProvince == "���" || sProvince == "����" || sProvince == "����";
}

static void InitSearchGoodsType()
{
	g_vecSearchGoodsType.push_back("����");
	g_vecSearchGoodsType.push_back("�㵣");
	g_vecSearchGoodsType.push_back("Ư��");
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

static void InitPubWay2Good1Menu()
{
	g_menuGoods1.CreatePopupMenu();
	int size = g_vecSearchGoodsType.size();
	for(int i = 0; i<size; ++i)
	{
		g_menuGoods1.InsertMenu(i, MF_STRING|MF_BYPOSITION, i+1, g_vecSearchGoodsType[i]);//the item id start from 1
	}
}
static void InitPubWay2Good2Menu()
{
	g_menuGoods2.CreatePopupMenu();
	int size = g_vecSearchGoods.size();
	for(int i = 0; i<size; ++i)
	{
		g_menuGoods2.InsertMenu(i, MF_STRING|MF_BYPOSITION, i+1, g_vecSearchGoods[i]);
	}
}

static void InitMenuGoods3_MS1(int& nMenuId)
{
	g_menuGoods3_MS1.CreateMenu();
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "���");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�豵");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ʯ");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ֽ�");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ֲ�");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ֹ�");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ְ�");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ϸ�");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ĩ");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "þ��");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ʯ");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "���");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "Ƭ��");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ͭ");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ϡ��");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��֬");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
}
static void InitMenuGoods3_MS2(int& nMenuId)
{
	g_menuGoods3_MS2.CreateMenu();
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ש");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ˮ��");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ɳ��");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ɳʯ");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ʯ");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "���");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ʯ��");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�׻�");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�����");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "̼����");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��΢��");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ʯ���");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ʯ�ҵ�");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�Ȼ���");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�Ȼ���");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ҵ��");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ҵ��");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "������");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "������");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ͻ���");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "������");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����ש");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ذ�ש");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ͻ�ש");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����̥");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��˿��");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "PVC����");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "���ܹ�΢��");
}
static void InitMenuGoods3_CC(int& nMenuId)
{
	g_menuGoods3_CC.CreateMenu();
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ú");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ú");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ԭú");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ĭú");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ú");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ú");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ֱ�");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��̿");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "̼��");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ľ̿");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "С��");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��̿");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ú��");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����ú");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����ú");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ϴú");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ú�ʯ");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ú����");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "2-4ú");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "2-6ú");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "3-8ú");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ú��");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��̼��");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����̿");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�缫��");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�����");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ú����");
}
static void InitMenuGoods3_MUV1(int& nMenuId)
{
	g_menuGoods3_MUV1.CreateMenu();
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "���");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�۹�");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�㽶");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��֦");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ƻ��");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ɳ��");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "Բ��");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "���");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ܲ�");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ཷ");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ƹ�");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�۲�");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ײ�");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�²�");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��̦");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ɽҩ");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�Ϲ�");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");

}
static void InitMenuGoods3_MUV2(int& nMenuId)
{
	g_menuGoods3_MUV2.CreateMenu();
	g_menuGoods3_MUV2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MUV2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MUV2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_MUV2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "���ܹ�");
	g_menuGoods3_MUV2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ƻ����");
	g_menuGoods3_MUV2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ڹ���");
	g_menuGoods3_MUV2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "������");
	g_menuGoods3_MUV2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "���ѽ�");
	g_menuGoods3_MUV2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "������");
	g_menuGoods3_MUV2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ͷ��");
	g_menuGoods3_MUV2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ˮ��");
}
static void InitMenuGoods3_Vehicle(int& nMenuId)
{
	g_menuGoods3_Vehicle.CreateMenu();
	g_menuGoods3_Vehicle.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ڻ�");
	g_menuGoods3_Vehicle.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�泵");
	g_menuGoods3_Vehicle.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_Vehicle.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "������");
	g_menuGoods3_Vehicle.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "���г�");
	g_menuGoods3_Vehicle.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "С�γ�");
	g_menuGoods3_Vehicle.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "������");
	g_menuGoods3_Vehicle.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "Ħ�г�");
	g_menuGoods3_Vehicle.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�����");
	g_menuGoods3_Vehicle.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ո��");
	g_menuGoods3_Vehicle.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "װ�ػ�");
	g_menuGoods3_Vehicle.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "������");
}
static void InitMenuGoods3_SubFood(int& nMenuId)
{
	g_menuGoods3_SubFood.CreateMenu();
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ţ��");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�׾�");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ơ��");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��Ƥ");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "���");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�̷�");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "���");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ţ��");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��Ҷ");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�̾�");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "СʳƷ");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "������");

}
static void InitMenuGoods3_FarmProduce(int& nMenuId)
{
	g_menuGoods3_FarmProduce.CreateMenu();
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ƶ�");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ܿ��");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�̶�");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ˮ��");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "������");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "������");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�����");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�Ͳ���");
}
static void InitMenuGoods3_Paper(int& nMenuId)
{
	g_menuGoods3_Paper.CreateMenu();
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ֽ��");
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ֽ");
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ֽ��");
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "���鱾");
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "���ֽ");
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ѹ��ֽ");
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ư�ֽ");
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��Ͳֽ");
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "С��ֽ");
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����ֽ");
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "���ֽ");
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ͽ�ֽ");
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ձֽ");
}
static void InitMenuGoods3_GW(int& nMenuId)
{
	g_menuGoods3_GW.CreateMenu();
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "έ��");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "έ��");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "έ��");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "έ��");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "έ��");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ݰ�");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ݿ�");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ƺ");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ԭľ");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ľ��");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ľ��");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ľ��");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�巽");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ʻ�");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ʲ�");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ҩ��");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "������");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "������");	

}
static void InitMenuGoods3_Animal(int& nMenuId)
{
	g_menuGoods3_Animal.CreateMenu();
	g_menuGoods3_Animal.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�۷�");
	g_menuGoods3_Animal.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ţ");
	g_menuGoods3_Animal.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��");
	g_menuGoods3_Animal.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��");
	g_menuGoods3_Animal.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��");
	g_menuGoods3_Animal.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");

}
static void InitMenuGoods3_Electric(int& nMenuId)
{
	g_menuGoods3_Electric.CreateMenu();
	g_menuGoods3_Electric.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_Electric.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_Electric.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ϴ�»�");
	g_menuGoods3_Electric.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�յ�");
	g_menuGoods3_Electric.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");

}
static void InitMenuGoods3_SilkHail(int& nMenuId)
{
	g_menuGoods3_SilkHail.CreateMenu();
	g_menuGoods3_SilkHail.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ë");
	g_menuGoods3_SilkHail.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ͷ��");
	g_menuGoods3_SilkHail.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ë��");
	g_menuGoods3_SilkHail.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ë��");
	g_menuGoods3_SilkHail.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ë");
	g_menuGoods3_SilkHail.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ë");
	g_menuGoods3_SilkHail.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "Ƥ��");
	g_menuGoods3_SilkHail.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��Ƥ");
	g_menuGoods3_SilkHail.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ţƤ");
	g_menuGoods3_SilkHail.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_SilkHail.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ƥ");
}
static void InitMenuGoods3_Other(int& nMenuId)
{
	int i = 0;
	g_menuGoods3_Other.CreateMenu();
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ʻ�");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ɻ�");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�̻�");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��Ͱ");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��Ͱ");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ũҩ");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "���");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�մ�");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ʯ");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�ޱ�");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��̥");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ɳ��");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "�Ŵ�");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "����");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ƿ");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ϴ�·�");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "ơ��ƿ");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "��ģ��");

}

static void InitPubway2Good3Menu()
{
	int nFirstLevId = 1;
	int nSndLevId = 100;
	g_menuGoods3.CreatePopupMenu();

	InitMenuGoods3_MS1(nSndLevId);//material steel1
	InitMenuGoods3_MS2(nSndLevId);//material steel2
	InitMenuGoods3_CC(nSndLevId);//coal and carbon
	InitMenuGoods3_MUV1(nSndLevId);//melon and fruit and vegetable
	InitMenuGoods3_MUV2(nSndLevId);//melon and fruit and vegetable
	InitMenuGoods3_Vehicle(nSndLevId);//Vehicle
	InitMenuGoods3_SubFood(nSndLevId);//subsidiary foodstuff
	InitMenuGoods3_FarmProduce(nSndLevId);//Farm Produce
	InitMenuGoods3_Paper(nSndLevId);//paper
	InitMenuGoods3_GW(nSndLevId);//grass and wood
	InitMenuGoods3_Animal(nSndLevId);//Animal
	InitMenuGoods3_Electric(nSndLevId);//electric
	InitMenuGoods3_SilkHail(nSndLevId);//Silk and Hail
	InitMenuGoods3_Other(nSndLevId);//Silk and Hail
	

	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_MS1.m_hMenu, "ԭ�ϸֲ���1");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_MS2.m_hMenu, "ԭ�ϸֲ���2");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_CC.m_hMenu, "ú̿Ʒ");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_MUV1.m_hMenu, "�Ϲ��߲���1");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_MUV2.m_hMenu, "�Ϲ��߲���2");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_Vehicle.m_hMenu, "������");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_SubFood.m_hMenu, "��ʳƷ");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_FarmProduce.m_hMenu, "ũ��Ʒ");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_Paper.m_hMenu, "ֽ��");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_GW.m_hMenu, "��ľ��");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_Animal.m_hMenu, "������");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_Electric.m_hMenu, "������");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_SilkHail.m_hMenu, "˿ë��");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_Other.m_hMenu, "������");
}

void InitCommData()
{
	InitSearchGoodsType();
	InitSearchGoods();
	InitSearchCarSize();
	InitSearchCarType();

	InitPubWay2Good1Menu();
	InitPubWay2Good2Menu();
	InitPubway2Good3Menu();

	g_goodsType.push_back("����");
	g_goodsType.push_back("�㵣");
	g_goodsType.push_back("�ػ�");
	g_goodsType.push_back("�ݻ�");
	g_goodsType.push_back("Ư��");
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

BOOL CheckNumberString(const CString& str, BOOL required/*=FALSE*/)
{
	if ( str.GetLength() == 0 )
	{
		return !required;
	}
	int temp = atoi(str);
	if ( 0 == temp )
	{
		if ( "0" != str )
		{
			return FALSE;
		}
	}
	return TRUE;
}