#ifndef COUNTRY_REGION_H
#define COUNTRY_REGION_H

// { ʵ�ִ��л�
// fewest include headers 
#include <boost/archive/binary_iarchive.hpp> 
#include <boost/archive/binary_oarchive.hpp> 
#include <boost/archive/text_iarchive.hpp> 
#include <boost/archive/text_oarchive.hpp> 
//#include <boost/archive/xml_oarchive.hpp>
//#include <boost/archive/xml_iarchive.hpp>
//#include <boost/serialization/nvp.hpp>
#include <boost/serialization/vector.hpp> 
#include <boost/serialization/string.hpp>
//#include <boost/serialization/deque.hpp>
#include <fstream>
// ʵ�ִ��л� }

#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct County {
	string id;
	string name;
	// { ʵ�ִ��л� 
	template<class Archive> 
	void serialize(Archive& ar, const unsigned int /* file_version */) {   
		ar& id;
		ar& name;
    }	// ʵ�ִ��л� }
};

struct City {
	string id;
	string name;
	vector<County> govCounty;
	// { ʵ�ִ��л� 
	template<class Archive> 
	void serialize(Archive& ar, const unsigned int /* file_version */) {   
		ar& id;
		ar& name;
		ar& govCounty;
    }	// ʵ�ִ��л� }
};

struct Province {
	string id;
	string name;
	vector<City> govCity;
	// { ʵ�ִ��л� 
	template<class Archive> 
	void serialize(Archive& ar, const unsigned int /* file_version */) {   
		ar& id;
		ar& name;
		ar& govCity;
    }	// ʵ�ִ��л� }
};

struct BufferData {
	std::string id;
	std::string name;
	std::string upId;
	std::string zone;
};

class CountryRegion
{
public:
	CountryRegion(void);
	~CountryRegion(void);

public:
	//int init();
	int CreateData(vector<BufferData> &regData);

private:
	int addProvince(string &name, string &id);
	int addCity(string &name, string &id, string &proId);
	int addCounty(string &name, string &id, string &cityId);

public:
	string name;
	vector<Province> govProvince;

// { ʵ�ִ��л�
friend class boost::serialization::access;
protected: 
    template<class Archive> 
        void serialize(Archive& ar, const unsigned int /* file_version */) {   
            ar& name;
            ar& govProvince;            
    } 
  
public:
    static void saveData(const CountryRegion& obj, std::string fileName) {
        std::ofstream ofile(fileName.c_str());
        boost::archive::text_oarchive oa(ofile);
		//boost::archive::binary_oarchive oa(ofile);
        oa << obj;        
    } 
  
    static int loadData(CountryRegion& obj, std::string fileName) {
        std::ifstream ifile(fileName.c_str());
        if ( ifile.good() ) {
            boost::archive::text_iarchive ia(ifile);
			//boost::archive::binary_iarchive ia(ifile);
            ia >> obj;
            return 0;
        } else {
            return -1;
        }
    } 
// ʵ�ִ��л� }

};

#endif // COUNTRY_REGION_H
