#ifndef _FMP_COMM_DEFINE_H
#define _FMP_COMM_DEFINE_H

#include <map>
#include <vector>
using std::map;
using std::vector;

typedef vector<CString> tdVecCounty;
typedef map<CString,  tdVecCounty > tdMapCity;
typedef map<CString, tdMapCity > tdMapProvince;

extern tdMapProvince g_mapProvince;

inline const tdMapCity* GetCities(const CString& sProvince)
{
	tdMapProvince::const_iterator it = g_mapProvince.find(sProvince);
	return it != g_mapProvince.end()?&(*it).second:NULL;
}
inline const tdVecCounty* GetCounties(const CString& sProvince, const CString& sCity)
{
	const tdMapCity* pCities = GetCities(sProvince);
	if( pCities == NULL )
	{
		return NULL;
	}
	tdMapCity::const_iterator it = pCities->find(sCity);
	return it != pCities->end()?&(*it).second:NULL;
}

void InitCommData();

#endif