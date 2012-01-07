#ifndef WLRCLIENT_USER_DATA_H
#define WLRCLIENT_USER_DATA_H

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
using std::fstream;
using std::string;
using std::vector;
using std::iostream;

class WLRUserData
{
public:
	WLRUserData(void){std::locale::global(std::locale(""));}
	~WLRUserData(void){}

public:
    // �ʺ�
    string userName;    
    
    // ����
    string passWord;   

    // ��ס�ʺ�
    bool ifRemUserName;

    // ��ס����
    bool ifRemPassWord;

// { ʵ�ִ��л�
friend class boost::serialization::access;
protected: 
    template<class Archive> 
        void serialize(Archive& ar, const unsigned int /* file_version */) {   
            ar& userName;
            ar& passWord;
			ar& ifRemUserName;
            ar& ifRemPassWord;
    } 
  
public:
    static void saveData(const WLRUserData& obj, std::string fileName) {
        std::ofstream ofile(fileName.c_str());
        //boost::archive::text_oarchive oa(ofile);
		boost::archive::binary_oarchive oa(ofile);
        oa << obj;        
    } 
  
    static int loadData(WLRUserData& obj, std::string fileName) {
        std::ifstream ifile(fileName.c_str());
        if ( ifile.good() ) {
            //boost::archive::text_iarchive ia(ifile);
			boost::archive::binary_iarchive ia(ifile);
            ia >> obj;
            return 0;
        } else {
            return -1;
        }
    } 
// ʵ�ִ��л� }

};

#endif // WLRCLIENT_USER_DATA_H
