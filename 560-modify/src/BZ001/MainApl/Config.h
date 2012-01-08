#ifndef WLRCLIENT_CONFIG_H
#define WLRCLIENT_CONFIG_H

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
//using namespace std;
using std::fstream;
using std::string;
using std::vector;
using std::iostream;

// ��������
struct FontConfig {
    long    lfHeight;
    long    lfWidth;
    long    lfEscapement;
    long    lfOrientation;
    long    lfWeight;
    unsigned char   lfItalic;
    unsigned char   lfUnderline;
    unsigned char   lfStrikeOut;
    unsigned char   lfCharSet;
    unsigned char   lfOutPrecision;
    unsigned char   lfClipPrecision;
    unsigned char   lfQuality;
    unsigned char   lfPitchAndFamily;
    string    lfFaceName;

    // { ʵ�ִ��л� 
    template<class Archive> 
        void serialize(Archive& ar, const unsigned int /* file_version */) {   
            ar& lfHeight;
            ar& lfWidth;
            ar& lfEscapement;
            ar& lfOrientation;
            ar& lfWeight;
            ar& lfItalic;
            ar& lfUnderline;
            ar& lfStrikeOut;
            ar& lfCharSet;
            ar& lfOutPrecision;
            ar& lfClipPrecision;
            ar& lfQuality;
            ar& lfPitchAndFamily;
            ar& lfFaceName;
    }
    // } ʵ�ִ��л�
};

// ��ɫ����
struct ColorConfig {   
    unsigned long  sysBKClr;  // ϵͳ����ɫ
    unsigned long  oddRowBKClr; // �����б���ɫ    
    unsigned long  oddRowFgClr; // ����������ɫ    
    unsigned long  evenRowBKClr; // ż���б���ɫ    
    unsigned long  evenRowFgClr; // ż��������ɫ    
    unsigned long  gridClr; // ��������ɫ
    // { ʵ�ִ��л� 
    template<class Archive> 
        void serialize(Archive& ar, const unsigned int /* file_version */) {   
            ar& sysBKClr;
            ar& oddRowBKClr;
            ar& oddRowFgClr;
            ar& evenRowBKClr;
            ar& evenRowFgClr;
            ar& gridClr;
    }
    // } ʵ�ִ��л�
};

class WLRConfig
{
public:
	WLRConfig(void){std::locale::global(std::locale(""));}
	~WLRConfig(void){}

public:
    // ������������Ϣ
    FontConfig oddFont;    
    
    // ż����������Ϣ
    FontConfig evenFont;   

    // ��ɫ����
    ColorConfig colorSetting;

// { ʵ�ִ��л�
friend class boost::serialization::access;
protected: 
    template<class Archive> 
        void serialize(Archive& ar, const unsigned int /* file_version */) {   
            ar& oddFont;
            ar& evenFont;
			ar& colorSetting;
    } 
  
public:
    static void saveData(const WLRConfig& obj, std::string fileName) {
        std::ofstream ofile(fileName.c_str());
        //boost::archive::text_oarchive oa(ofile);
		boost::archive::binary_oarchive oa(ofile);
        oa << obj;        
    } 
  
    static int loadData(WLRConfig& obj, std::string fileName) {
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

#endif // WLRCLIENT_CONFIG_H
