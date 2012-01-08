#include "stdafx.h"
#include "CountryRegion.h"

CountryRegion::CountryRegion(void)
{
	
}

CountryRegion::~CountryRegion(void)
{
}

int CountryRegion::CreateData(vector<BufferData> &regData) {
	vector<BufferData>::iterator iter = regData.begin();
    while (iter != regData.end()) {
		if ( 2 == (*iter).id.length() ) {
			addProvince((*iter).name, (*iter).id);
		}
		if ( 4 == (*iter).id.length() ) {
			addCity((*iter).name, (*iter).id, (*iter).upId);
		}
		if ( 4 < (*iter).id.length() ) {
			addCounty((*iter).name, (*iter).id, (*iter).upId);
		}
        ++iter;
    }

/*
	// 增加省
	vector<BufferData>::iterator iter = regData.data.begin();
    while (iter != regData.data.end()) {
		if ( 2 == (*iter).id.length() ) {
			addProvince((*iter).name, (*iter).id);
		}
        ++iter;
    }

	// 增加市
	iter = regData.data.begin();
    while (iter != regData.data.end()) {
		if ( 4 == (*iter).id.length() ) {
			addCity((*iter).name, (*iter).id, (*iter).upId);
		}
        ++iter;
    }

	// 增加县
	iter = regData.data.begin();
    while (iter != regData.data.end()) {
		if ( 4 < (*iter).id.length() ) {
			addCounty((*iter).name, (*iter).id, (*iter).upId);
		}
        ++iter;
    }
	//*/

	return 0;
}

int CountryRegion::addProvince(string& name, string& id)
{
	Province tmpPro;
	tmpPro.id = id;
	tmpPro.name = name;
	govProvince.push_back(tmpPro);
	return 0;
}

int CountryRegion::addCity(string& name, string& id, string& proId)
{
	City tmpCity;
	tmpCity.id = id;
	tmpCity.name = name;

	vector<Province>::iterator iter = govProvince.begin();
    while (iter != govProvince.end()) {
		if((*iter).id == proId) {
			(*iter).govCity.push_back(tmpCity);
			break;
		}
        ++iter;
    }

	return 0;
}

int CountryRegion::addCounty(string& name, string& id, string& cityId)
{
	County tmpCounty;
	tmpCounty.id = id;
	tmpCounty.name = name;

	// 根据cityId查找所属的Province
	vector<Province>::iterator iter = govProvince.begin();
    while (iter != govProvince.end()) {
		//cout << (*iter).id << "	" << (*iter).name << "	" << (*iter).upId << endl;
		vector<City>::iterator iter2 = (*iter).govCity.begin();
		while (iter2 != (*iter).govCity.end()) {
			if((*iter2).id == cityId ) {
				(*iter2).govCounty.push_back(tmpCounty);
				break;
			}
			++iter2;
		}
        ++iter;
    }

	return 0;
}




