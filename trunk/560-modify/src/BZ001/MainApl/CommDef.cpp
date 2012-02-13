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
	return sProvince == "上海" || sProvince == "北京" || sProvince == "天津" || sProvince == "深圳" || sProvince == "重庆";
}

static void InitSearchGoodsType()
{
	g_vecSearchGoodsType.push_back("整车");
	g_vecSearchGoodsType.push_back("零担");
	g_vecSearchGoodsType.push_back("漂货");
	g_vecSearchGoodsType.push_back("泡货");
	g_vecSearchGoodsType.push_back("重货");
	g_vecSearchGoodsType.push_back("普货");
	g_vecSearchGoodsType.push_back("危货");
	g_vecSearchGoodsType.push_back("小货");
	g_vecSearchGoodsType.push_back("倒短货");
	g_vecSearchGoodsType.push_back("回程货");
	g_vecSearchGoodsType.push_back("大量货");
	g_vecSearchGoodsType.push_back("长期货");
	g_vecSearchGoodsType.push_back("搬家货");
}
static void InitSearchGoods()
{
	g_vecSearchGoods.push_back("原料");
	g_vecSearchGoods.push_back("冻货"); 
	g_vecSearchGoods.push_back("化工");
	g_vecSearchGoods.push_back("煤炭");
	g_vecSearchGoods.push_back("配件");
	g_vecSearchGoods.push_back("矿产");
	g_vecSearchGoods.push_back("设备");
	g_vecSearchGoods.push_back("机械");
	g_vecSearchGoods.push_back("仪器");
	g_vecSearchGoods.push_back("电器");
	g_vecSearchGoods.push_back("家具");
	g_vecSearchGoods.push_back("建材");
	g_vecSearchGoods.push_back("药材");
	g_vecSearchGoods.push_back("医药");
	g_vecSearchGoods.push_back("试剂");
	g_vecSearchGoods.push_back("海鲜");
	g_vecSearchGoods.push_back("电机");
	g_vecSearchGoods.push_back("服装");
	g_vecSearchGoods.push_back("矿石");
	g_vecSearchGoods.push_back("食品");
	g_vecSearchGoods.push_back("粮食");
	g_vecSearchGoods.push_back("蔬菜");
	g_vecSearchGoods.push_back("水果");
	g_vecSearchGoods.push_back("瓜果");
	g_vecSearchGoods.push_back("饮料");
	g_vecSearchGoods.push_back("牲畜");
	g_vecSearchGoods.push_back("家禽");
	g_vecSearchGoods.push_back("肉制品");
	g_vecSearchGoods.push_back("纺织品");
	g_vecSearchGoods.push_back("化妆品");
	g_vecSearchGoods.push_back("危险品");
	g_vecSearchGoods.push_back("农产品");
	g_vecSearchGoods.push_back("工艺品");
	g_vecSearchGoods.push_back("洗涤品");
	g_vecSearchGoods.push_back("牧产品");
	g_vecSearchGoods.push_back("渔产品");
	g_vecSearchGoods.push_back("电子产品");
	g_vecSearchGoods.push_back("轻工产品");
	g_vecSearchGoods.push_back("大型设备");
	g_vecSearchGoods.push_back("石油制品");
	g_vecSearchGoods.push_back("办公设备");
	g_vecSearchGoods.push_back("冷冻食品");
	g_vecSearchGoods.push_back("桶装化工");
	g_vecSearchGoods.push_back("箱装化工");
}
static void InitSearchCarType()
{
	g_vecSearchCarType.push_back("普通车");
	g_vecSearchCarType.push_back("前四后四");
	g_vecSearchCarType.push_back("前四后八");
	g_vecSearchCarType.push_back("前四后十");
	g_vecSearchCarType.push_back("敞篷车");
	g_vecSearchCarType.push_back("平板车");
	g_vecSearchCarType.push_back("高栏车");
	g_vecSearchCarType.push_back("集装箱");
	g_vecSearchCarType.push_back("冷藏车");
	g_vecSearchCarType.push_back("起重车");
	g_vecSearchCarType.push_back("后八轮");
	g_vecSearchCarType.push_back("单桥车");
	g_vecSearchCarType.push_back("自卸车");
	g_vecSearchCarType.push_back("半封闭车");
	g_vecSearchCarType.push_back("半挂车");
	g_vecSearchCarType.push_back("保温车");
	g_vecSearchCarType.push_back("双桥车");
	g_vecSearchCarType.push_back("加长挂车");
	g_vecSearchCarType.push_back("棉被车");
	g_vecSearchCarType.push_back("大笼子车");
	g_vecSearchCarType.push_back("高低板");
	g_vecSearchCarType.push_back("翻斗车");
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
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "铁");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "盐");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "硅铁");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "硅钙");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "硅钡");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "硅石");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "硅渣");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "硅锰");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "锰铁");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "烙铁");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "生铁");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "钢筋");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "钢材");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "钢管");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "钢板");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "废钢");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "废铁");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "铁粉");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "铁末");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "铁件");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "铝锭");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "镁锭");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "电石");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "电池");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "化工");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "片碱");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "球团");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "废铝");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "废铜");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "稀土");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "腐钠");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "树脂");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "塑料");
	g_menuGoods3_MS1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "肥料");
}
static void InitMenuGoods3_MS2(int& nMenuId)
{
	g_menuGoods3_MS2.CreateMenu();
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "瓷砖");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "铸件");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "油漆");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "水泥");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "沙子");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "沙石");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "矿石");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "矿粉");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "石料");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "白灰");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "面包铁");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "碳化硅");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "硅微粉");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "石膏粉");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "石灰蛋");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "氯化钙");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "氯化钠");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "工业钠");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "工业萘");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "高岭土");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "铝矾土");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "耐火土");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "废塑料");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "空心砖");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "地板砖");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "耐火砖");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "废轮胎");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "钢丝绳");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "PVC颗粒");
	g_menuGoods3_MS2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "加密硅微粉");
}
static void InitMenuGoods3_CC(int& nMenuId)
{
	g_menuGoods3_CC.CreateMenu();
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "煤");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "块煤");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "原煤");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "沫煤");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "精煤");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "烟煤");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "粗苯");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "焦炭");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "碳素");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "木炭");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "大焦");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "小焦");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "焦粉");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "焦粒");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "蓝炭");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "沥青");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "煤泥");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "无烟煤");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "调运煤");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "精洗煤");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "煤矸石");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "煤焦油");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "2-4煤");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "2-6煤");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "3-8煤");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "粉煤灰");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "增碳剂");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "活性炭");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "电极糊");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "电锻料");
	g_menuGoods3_CC.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "煤沥青");
}
static void InitMenuGoods3_MUV1(int& nMenuId)
{
	g_menuGoods3_MUV1.CreateMenu();
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "梨");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "香瓜");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "西瓜");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "甘蔗");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "蜜瓜");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "橘子");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "香蕉");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "荔枝");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "桔子");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "菠萝");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "桃子");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "红枣");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "柿子");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "葡萄");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "苹果");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "沙果");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "圆葱");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "洋葱");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "萝卜");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "辣椒");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "青椒");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "黄瓜");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "豆角");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "芹菜");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "白菜");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "菠菜");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "番茄");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "韭菜");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "大蒜");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "蒜苔");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "山药");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "土豆");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "南瓜");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "冬瓜");
	g_menuGoods3_MUV1.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "茄子");

}
static void InitMenuGoods3_MUV2(int& nMenuId)
{
	g_menuGoods3_MUV2.CreateMenu();
	g_menuGoods3_MUV2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "菇娘");
	g_menuGoods3_MUV2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "榴莲");
	g_menuGoods3_MUV2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "海带");
	g_menuGoods3_MUV2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "哈密瓜");
	g_menuGoods3_MUV2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "苹果梨");
	g_menuGoods3_MUV2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "黑瓜子");
	g_menuGoods3_MUV2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "西红柿");
	g_menuGoods3_MUV2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "番茄酱");
	g_menuGoods3_MUV2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "干辣椒");
	g_menuGoods3_MUV2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "大头菜");
	g_menuGoods3_MUV2.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "脱水菜");
}
static void InitMenuGoods3_Vehicle(int& nMenuId)
{
	g_menuGoods3_Vehicle.CreateMenu();
	g_menuGoods3_Vehicle.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "挖机");
	g_menuGoods3_Vehicle.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "叉车");
	g_menuGoods3_Vehicle.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "铲车");
	g_menuGoods3_Vehicle.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "翻斗车");
	g_menuGoods3_Vehicle.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "自行车");
	g_menuGoods3_Vehicle.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "小轿车");
	g_menuGoods3_Vehicle.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "拖拉机");
	g_menuGoods3_Vehicle.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "摩托车");
	g_menuGoods3_Vehicle.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "搅拌机");
	g_menuGoods3_Vehicle.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "收割机");
	g_menuGoods3_Vehicle.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "装载机");
	g_menuGoods3_Vehicle.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "推土机");
}
static void InitMenuGoods3_SubFood(int& nMenuId)
{
	g_menuGoods3_SubFood.CreateMenu();
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "牛奶");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "饼干");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "酒");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "白酒");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "啤酒");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "蜂蜜");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "豆饼");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "麸皮");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "饲料");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "面粉");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "奶粉");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "粉条");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "淀粉");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "羊肉");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "牛肉");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "猪肉");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "茶叶");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "烟酒");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "小食品");
	g_menuGoods3_SubFood.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "花生米");

}
static void InitMenuGoods3_FarmProduce(int& nMenuId)
{
	g_menuGoods3_FarmProduce.CreateMenu();
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "黄豆");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "芸豆");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "大豆");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "绿豆");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "大米");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "水稻");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "胡麻");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "葵花油");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "葵仁");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "杏仁");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "瓜子");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "玉米");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "花生");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "花生果");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "枸杞子");
	g_menuGoods3_FarmProduce.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "油菜籽");
}
static void InitMenuGoods3_Paper(int& nMenuId)
{
	g_menuGoods3_Paper.CreateMenu();
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "纸箱");
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "书纸");
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "废纸壳");
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "废书本");
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "打包纸");
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "压缩纸");
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "黄板纸");
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "卷筒纸");
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "小卷纸");
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "卫生纸");
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "面巾纸");
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "餐巾纸");
	g_menuGoods3_Paper.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "油毡纸");
}
static void InitMenuGoods3_GW(int& nMenuId)
{
	g_menuGoods3_GW.CreateMenu();
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "苇包");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "苇块");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "苇捆");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "苇杆");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "苇子");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "草包");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "草块");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "草捆");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "草坪");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "原木");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "木材");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "木杆");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "筷子");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "木板");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "板方");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "鲜花");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "树苗");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "甘草");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "药材");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "工艺帘");
	g_menuGoods3_GW.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "草帘子");	

}
static void InitMenuGoods3_Animal(int& nMenuId)
{
	g_menuGoods3_Animal.CreateMenu();
	g_menuGoods3_Animal.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "蜜蜂");
	g_menuGoods3_Animal.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "牛");
	g_menuGoods3_Animal.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "羊");
	g_menuGoods3_Animal.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "马");
	g_menuGoods3_Animal.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "猪");
	g_menuGoods3_Animal.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "带鱼");

}
static void InitMenuGoods3_Electric(int& nMenuId)
{
	g_menuGoods3_Electric.CreateMenu();
	g_menuGoods3_Electric.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "冰箱");
	g_menuGoods3_Electric.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "电视");
	g_menuGoods3_Electric.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "洗衣机");
	g_menuGoods3_Electric.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "空调");
	g_menuGoods3_Electric.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "电脑");

}
static void InitMenuGoods3_SilkHail(int& nMenuId)
{
	g_menuGoods3_SilkHail.CreateMenu();
	g_menuGoods3_SilkHail.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "猪毛");
	g_menuGoods3_SilkHail.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "头发");
	g_menuGoods3_SilkHail.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "毛渣");
	g_menuGoods3_SilkHail.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "毛发");
	g_menuGoods3_SilkHail.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "羊毛");
	g_menuGoods3_SilkHail.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "鹅毛");
	g_menuGoods3_SilkHail.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "皮子");
	g_menuGoods3_SilkHail.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "羊皮");
	g_menuGoods3_SilkHail.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "牛皮");
	g_menuGoods3_SilkHail.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "羊绒");
	g_menuGoods3_SilkHail.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "布匹");
}
static void InitMenuGoods3_Other(int& nMenuId)
{
	int i = 0;
	g_menuGoods3_Other.CreateMenu();
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "海鲜");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "鲜活");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "干货");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "冻货");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "烟花");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "鞭炮");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "花炮");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "电缆");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "塔吊");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "网架");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "空桶");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "油桶");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "农药");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "种子");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "化肥");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "洁具");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "陶瓷");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "奇石");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "棉被");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "轮胎");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "玻璃");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "橡胶");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "沙发");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "机瓦");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "门窗");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "肥皂");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "酒瓶");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "洗衣粉");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "啤酒瓶");
	g_menuGoods3_Other.InsertMenu(nMenuId, MF_STRING|MF_BYPOSITION, nMenuId++, "钢模板");

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
	

	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_MS1.m_hMenu, "原料钢材类1");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_MS2.m_hMenu, "原料钢材类2");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_CC.m_hMenu, "煤炭品");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_MUV1.m_hMenu, "瓜果蔬菜类1");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_MUV2.m_hMenu, "瓜果蔬菜类2");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_Vehicle.m_hMenu, "车辆类");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_SubFood.m_hMenu, "副食品");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_FarmProduce.m_hMenu, "农产品");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_Paper.m_hMenu, "纸类");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_GW.m_hMenu, "草木类");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_Animal.m_hMenu, "动物类");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_Electric.m_hMenu, "电器类");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_SilkHail.m_hMenu, "丝毛类");
	g_menuGoods3.AppendMenu(MF_POPUP, (UINT_PTR)g_menuGoods3_Other.m_hMenu, "其他类");
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

	g_goodsType.push_back("整车");
	g_goodsType.push_back("零担");
	g_goodsType.push_back("重货");
	g_goodsType.push_back("泡货");
	g_goodsType.push_back("漂货");
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
	g_truckType.push_back("前四后十");
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
	g_priceType.push_back("价格好商量");
	g_priceType.push_back("给钱就走");
	g_priceType.push_back("价高急走");

	g_priceTypeFor3.push_back("价格高");
	g_priceTypeFor3.push_back("价高急走");
	g_priceTypeFor3.push_back("价格面议");
	g_priceTypeFor3.push_back("价格好商量");
	g_priceTypeFor3.push_back("全价");

	g_commonDuanyu.push_back("随车装");
	g_commonDuanyu.push_back("车已定好");
	g_commonDuanyu.push_back("马上装车");
	g_commonDuanyu.push_back("不占空间");
	g_commonDuanyu.push_back("请打手机");
	g_commonDuanyu.push_back("更正信息");
	g_commonDuanyu.push_back("在一个厂装");
	g_commonDuanyu.push_back("货在本站");
	g_commonDuanyu.push_back("货主本站等");
	g_commonDuanyu.push_back("货主跟车");
	g_commonDuanyu.push_back("货主管饭");
	g_commonDuanyu.push_back("两货可一起走");
	g_commonDuanyu.push_back("今天订车");
	g_commonDuanyu.push_back("明早装货");
	g_commonDuanyu.push_back("晚上也可以装");
	g_commonDuanyu.push_back("求多部后半轮或半挂");
	g_commonDuanyu.push_back("求大小车");
	g_commonDuanyu.push_back("货已定，请勿打扰");
	g_commonDuanyu.push_back("装车付一半运费，货到付清");
	g_commonDuanyu.push_back("货到就卸，不压车");
	g_commonDuanyu.push_back("三不超");
	g_commonDuanyu.push_back("大吨位");
	g_commonDuanyu.push_back("请联系");
	g_commonDuanyu.push_back("速回电联系");

	g_commonZi.push_back("从");
	g_commonZi.push_back("不");
	g_commonZi.push_back("占");
	g_commonZi.push_back("用");
	g_commonZi.push_back("空");
	g_commonZi.push_back("可");
	g_commonZi.push_back("以");
	g_commonZi.push_back("上");
	g_commonZi.push_back("走");
	g_commonZi.push_back("剩");
	g_commonZi.push_back("或");
	g_commonZi.push_back("是");
	g_commonZi.push_back("跟");
	g_commonZi.push_back("来");
	g_commonZi.push_back("拉");
	g_commonZi.push_back("装");
	g_commonZi.push_back("的");
	g_commonZi.push_back("每");
	g_commonZi.push_back("在");
	g_commonZi.push_back("带");
	g_commonZi.push_back("也");
	g_commonZi.push_back("各");
	g_commonZi.push_back("等");
	g_commonZi.push_back("和");
	g_commonZi.push_back("长");
	g_commonZi.push_back("宽");
	g_commonZi.push_back("高");
	g_commonZi.push_back("前");
	g_commonZi.push_back("后");
	g_commonZi.push_back("左");
	g_commonZi.push_back("右");
	g_commonZi.push_back("大");
	g_commonZi.push_back("小");
	g_commonZi.push_back("多");
	g_commonZi.push_back("少");
	g_commonZi.push_back("单");
	g_commonZi.push_back("双");
	g_commonZi.push_back("东");
	g_commonZi.push_back("西");
	g_commonZi.push_back("南");
	g_commonZi.push_back("北");
	g_commonZi.push_back("电");
	g_commonZi.push_back("话");
	g_commonZi.push_back("辆");
	g_commonZi.push_back("速");
	g_commonZi.push_back("请");
	g_commonZi.push_back("年");
	g_commonZi.push_back("月");
	g_commonZi.push_back("日");
	g_commonZi.push_back("配");
	g_commonZi.push_back("位");
	g_commonZi.push_back("占");

	g_commonCi.push_back("早上");
	g_commonCi.push_back("上午");
	g_commonCi.push_back("中午");
	g_commonCi.push_back("下午");
	g_commonCi.push_back("晚上");
	g_commonCi.push_back("今天");
	g_commonCi.push_back("明早");
	g_commonCi.push_back("每天");
	g_commonCi.push_back("袋装");
	g_commonCi.push_back("桶装");
	g_commonCi.push_back("箱装");
	g_commonCi.push_back("货主");
	g_commonCi.push_back("配货");
	g_commonCi.push_back("短途");
	g_commonCi.push_back("长途");
	g_commonCi.push_back("本地");
	g_commonCi.push_back("本站");
	g_commonCi.push_back("长期");
	g_commonCi.push_back("回程");
	g_commonCi.push_back("专线");
	g_commonCi.push_back("定车");
	g_commonCi.push_back("以上");
	g_commonCi.push_back("以下");
	g_commonCi.push_back("以内");
	g_commonCi.push_back("左右");
	g_commonCi.push_back("方向");
	g_commonCi.push_back("附近");
	g_commonCi.push_back("最好");
	g_commonCi.push_back("吨位");
	g_commonCi.push_back("联系");
	g_commonCi.push_back("运费");
	g_commonCi.push_back("车型");
	g_commonCi.push_back("不限");

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
	g_PeihuoInfo.push_back("急");
	g_PeihuoInfo.push_back("需");
	g_PeihuoInfo.push_back("要");
	g_PeihuoInfo.push_back("求");
	g_PeihuoInfo.push_back("有");
	g_PeihuoInfo.push_back("发");
	g_PeihuoInfo.push_back("到");
	g_PeihuoInfo.push_back("回");
	g_PeihuoInfo.push_back("去");
	g_PeihuoInfo.push_back("车");
	g_PeihuoInfo.push_back("货");
	g_PeihuoInfo.push_back("电");
	g_PeihuoInfo.push_back("吨");
	g_PeihuoInfo.push_back("米");
	g_PeihuoInfo.push_back("元");
	g_PeihuoInfo.push_back("元/吨");
	g_PeihuoInfo.push_back("单位");
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