#ifndef WLRCLIENT_CONFIG_H
#define WLRCLIENT_CONFIG_H

// { 实现串行化
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
// 实现串行化 }

#include <string>
#include <vector>
#include <iostream>
//using namespace std;
using std::fstream;
using std::string;
using std::vector;
using std::iostream;

// 字体设置
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

    // { 实现串行化 
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
    // } 实现串行化
};

// 颜色设置
struct ColorConfig {   
    unsigned long  sysBKClr;  // 系统背景色
    unsigned long  oddRowBKClr; // 奇数行背景色    
    unsigned long  oddRowFgClr; // 奇数行文字色    
    unsigned long  evenRowBKClr; // 偶数行背景色    
    unsigned long  evenRowFgClr; // 偶数行文字色    
    unsigned long  gridClr; // 网格线颜色
    // { 实现串行化 
    template<class Archive> 
        void serialize(Archive& ar, const unsigned int /* file_version */) {   
            ar& sysBKClr;
            ar& oddRowBKClr;
            ar& oddRowFgClr;
            ar& evenRowBKClr;
            ar& evenRowFgClr;
            ar& gridClr;
    }
    // } 实现串行化
};

class WLRConfig
{
public:
	WLRConfig(void){std::locale::global(std::locale(""));}
	~WLRConfig(void){}

public:
    // 奇数行字体信息
    FontConfig oddFont;    
    
    // 偶数行字体信息
    FontConfig evenFont;   

    // 颜色设置
    ColorConfig colorSetting;

// { 实现串行化
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
// 实现串行化 }

};

#endif // WLRCLIENT_CONFIG_H
