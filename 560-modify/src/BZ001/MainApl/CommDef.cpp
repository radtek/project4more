#include "stdafx.h"
#include "CommDef.h"

tdMapProvince g_mapProvince;

static void InitAddr()
{
	g_mapProvince[_T("北京")];
	g_mapProvince[_T("天津")];
	g_mapProvince[_T("河北")];
	g_mapProvince[_T("山西")];
	g_mapProvince[_T("内蒙古")];
	g_mapProvince[_T("辽宁")];
	g_mapProvince[_T("吉林")];
	g_mapProvince[_T("黑龙江")];
	g_mapProvince[_T("上海")];
	g_mapProvince[_T("江苏")];
	g_mapProvince[_T("浙江")];
	g_mapProvince[_T("安徽")];
	g_mapProvince[_T("福建")];
	g_mapProvince[_T("江西")];
	g_mapProvince[_T("山东")];
	g_mapProvince[_T("河南")];
	g_mapProvince[_T("湖北")];
	g_mapProvince[_T("湖南")];
	g_mapProvince[_T("广东")];
	g_mapProvince[_T("广西")];
	g_mapProvince[_T("海南")];
	g_mapProvince[_T("重庆")];
	g_mapProvince[_T("四川")];
	g_mapProvince[_T("贵州")];
	g_mapProvince[_T("云南")];
	g_mapProvince[_T("西藏")];
	g_mapProvince[_T("陕西")];
	g_mapProvince[_T("甘肃")];
	g_mapProvince[_T("青海")];
	g_mapProvince[_T("宁夏")];
	g_mapProvince[_T("新疆")];
	g_mapProvince[_T("台湾")];
	g_mapProvince[_T("香港")];
	g_mapProvince[_T("澳门")];
	
}

void InitCommData()
{
	InitAddr();
}