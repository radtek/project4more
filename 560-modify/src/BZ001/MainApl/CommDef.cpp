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