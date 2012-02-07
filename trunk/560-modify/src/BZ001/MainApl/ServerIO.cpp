#include "StdAfx.h"
#include "ServerIO.h"
#include "soap/FmpServiceImplServiceSoapBinding.nsmap"


ServerIO::ServerIO(void)
{
    // 初始化webservice网址
    svrURL = WEB_SERVICE_ADDRESS + "/fmp/service/fmpserver?wsdl";
    //svrURL = "http://www.wibang.com/fmp/service/fmpserver?wsdl";

    // 初始化颜色
    myColor.oddRowBKClr = RGB(38, 109, 59);
    myColor.oddRowFgClr = RGB(240, 239, 230);
    myColor.evenRowBKClr = RGB(75, 155, 62);
    myColor.evenRowFgClr = RGB(33, 53, 41);
    myColor.gridClr = RGB(186, 185, 176);

    // 初始化字体
    oddFont.lfFaceName = "宋体";
    oddFont.lfWeight = 400; 
    oddFont.lfWidth = 0; 
    oddFont.lfHeight = 16; // 字体大小 
    oddFont.lfEscapement = 0; 
    oddFont.lfUnderline = false; 
    oddFont.lfItalic = FALSE; 
    oddFont.lfStrikeOut = FALSE; 
    oddFont.lfCharSet = GB2312_CHARSET; //以上参数好像一个都不能少

    evenFont.lfFaceName = "黑体";
    evenFont.lfWeight = 400; 
    evenFont.lfWidth = 0; 
    evenFont.lfHeight = 16; // 字体大小 
    evenFont.lfEscapement = 0; 
    evenFont.lfUnderline = false; 
    evenFont.lfItalic = FALSE; 
    evenFont.lfStrikeOut = FALSE; 
    evenFont.lfCharSet = GB2312_CHARSET; //以上参数好像一个都不能少

    // 初始化广告信息
    sysScrollAd.id = "-1";
    sysScrollAd.inf = "杭州多特信息技术有限公司版权所有。";
    agPopAd.id = "-1";
    agPopAd.inf = "需要帮助，请联系您的代理商。";
    AdMsg tmp;
    tmp.id = "-1";
    tmp.inf = "可在此处发布您的信息,详情请咨询您的代理商。";
    agScrollAd.push_back(tmp);

    // 初始化 soap 
    initSoap();
}

ServerIO::~ServerIO(void)
{
    // 卸载 soap
    destroySoap();
}
      
// user login 用户登录
string ServerIO::usrLogin(string username, string pwd)
{
#ifdef _OFF_LINE_
    userInf.id = "79";
    userInf.userName = "大中华物流";
    userInf.realName = "张三";
    userInf.company = "大中华物流有限公司";
    userInf.tel = "0571-87703986";
    userInf.province = "浙江";
    userInf.city = "杭州";
#else
    // 调用
    ns2__usrLogin inData;
    std::string id(userInf.id);
    inData.username = &username;
    inData.pwd = &pwd;

    ns2__usrLoginResponse outData;
   
    if ( soap_call___ns1__usrLogin(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        string outTmp("");	
        vector<string> tokens;
        UTF8ToMultiByte(*(outData.return_), outTmp);
	    tokenize(outTmp, tokens, "|");
        if (tokens.at(0) == "TRUE" && tokens.size() >= 8) {
                userInf.id = tokens.at(1);
                userInf.realName = tokens.at(2);
                userInf.company = tokens.at(3);
                userInf.tel = tokens.at(4);
                userInf.province = tokens.at(5);
                userInf.city = tokens.at(6);
                userInf.userName = tokens.at(7);   
				userInf.sex = tokens.at(8);
        } else {
            return tokens.at(1);
        }
		destroySoap();
	   
   } else {
	   destroySoap();
	   return "连接服务器失败，请检查网络连接。";       
   }

#endif

    return "TRUE";
}
    
// get user custom information 获取定制货源的列表
string ServerIO::getUserCustomInfHY()
{
#ifdef _OFF_LINE_
    hyZoneInf.clear();
    cyZoneInf.clear();

    CustomZoneInf tmp;
    tmp.id = "100";
    tmp.type = "hy";
    tmp.startProvince = "浙江省";
    tmp.startCity = "杭州";
    tmp.endProvince = "江苏省";
    tmp.endCity = "苏州";    
    hyZoneInf.push_back(tmp);

    tmp.id = "101";
    tmp.type = "hy";
    tmp.startProvince = "江西省";
    tmp.startCity = "九江";
    tmp.endProvince = "河北省";
    tmp.endCity = "石家庄";
    hyZoneInf.push_back(tmp);

    tmp.id = "102";
    tmp.type = "cy";
    tmp.startProvince = "安徽省";
    tmp.startCity = "合肥";
    tmp.endProvince = "河北省";
    tmp.endCity = "保定";
    cyZoneInf.push_back(tmp);

    tmp.id = "103";
    tmp.type = "cy";
    tmp.startProvince = "四川省";
    tmp.startCity = "成都";
    tmp.endProvince = "陕西省";
    tmp.endCity = "西安";
    cyZoneInf.push_back(tmp);
#else
    // 调用
    ns2__getUserCustomInf inData;
    std::string id(userInf.id);
    inData.uid = &id;

    ns2__getUserCustomInfResponse outData;
   
    if ( soap_call___ns1__getUserCustomInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        hyZoneInf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
            string outTmp("");	
            vector<string> tokens;
            CustomZoneInf tmp;
			UTF8ToMultiByte(*iter, outTmp);            
            tokenize(outTmp, tokens, "|");
            if (tokens.at(0) == "FALSE") {
                return "FALSE";
            }

            if (tokens.at(0) == "TRUE" && tokens.size() >= 7) {
                tmp.type = tokens.at(1);
                tmp.id = tokens.at(2);
                tmp.startProvince = tokens.at(3);
                tmp.startCity = tokens.at(4);
                tmp.endProvince = tokens.at(5);
                tmp.endCity = tokens.at(6);
				if (tmp.type == "hy")
				{
                hyZoneInf.push_back(tmp);
				}
            }

			++iter;
		}	   
	  destroySoap(); 
   } else {
	   destroySoap();
       return "连接服务器失败，请检查网络连接。";       
   }
#endif
    
    //hyZoneInf.
    return "TRUE";
}
// get user custom information 获取定制车源的列表
string ServerIO::getUserCustomInfCY()
{
#ifdef _OFF_LINE_
	hyZoneInf.clear();
	cyZoneInf.clear();

	CustomZoneInf tmp;
	tmp.id = "100";
	tmp.type = "hy";
	tmp.startProvince = "浙江省";
	tmp.startCity = "杭州";
	tmp.endProvince = "江苏省";
	tmp.endCity = "苏州";    
	hyZoneInf.push_back(tmp);

	tmp.id = "101";
	tmp.type = "hy";
	tmp.startProvince = "江西省";
	tmp.startCity = "九江";
	tmp.endProvince = "河北省";
	tmp.endCity = "石家庄";
	hyZoneInf.push_back(tmp);

	tmp.id = "102";
	tmp.type = "cy";
	tmp.startProvince = "安徽省";
	tmp.startCity = "合肥";
	tmp.endProvince = "河北省";
	tmp.endCity = "保定";
	cyZoneInf.push_back(tmp);

	tmp.id = "103";
	tmp.type = "cy";
	tmp.startProvince = "四川省";
	tmp.startCity = "成都";
	tmp.endProvince = "陕西省";
	tmp.endCity = "西安";
	cyZoneInf.push_back(tmp);
#else
	// 调用
	ns2__getUserCustomInf inData;
	std::string id(userInf.id);
	inData.uid = &id;

	ns2__getUserCustomInfResponse outData;

	if ( soap_call___ns1__getUserCustomInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
		cyZoneInf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
			string outTmp("");	
			vector<string> tokens;
			CustomZoneInf tmp;
			UTF8ToMultiByte(*iter, outTmp);            
			tokenize(outTmp, tokens, "|");
			if (tokens.at(0) == "FALSE") {
				return "FALSE";
			}

			if (tokens.at(0) == "TRUE" && tokens.size() >= 7) {
				tmp.type = tokens.at(1);
				tmp.id = tokens.at(2);
				tmp.startProvince = tokens.at(3);
				tmp.startCity = tokens.at(4);
				tmp.endProvince = tokens.at(5);
				tmp.endCity = tokens.at(6);
				if (tmp.type == "cy")
				{
					cyZoneInf.push_back(tmp);
				}
				
			}

			++iter;
		}	   
		destroySoap();
	} else {
		destroySoap();
		return "连接服务器失败，请检查网络连接。";       
	}
#endif

	//hyZoneInf.
	return "TRUE";
}   
// add user custom information 添加定制
string ServerIO::addUserCustomInf(CustomZoneInf input)
{
#ifdef _OFF_LINE_
#else
    // 调用
    ns2__addUserCustomInf inData;
    std::string id(userInf.id);
    inData.uid = &id;
    string buf = input.type + "|" + input.startProvince + "|" + input.startCity
        + "|" + input.endProvince + "|" + input.endCity;
    std::string UTF8input;
    MultiByteToUTF8(buf, UTF8input);
    inData.input = &UTF8input;

    ns2__addUserCustomInfResponse outData;
   
    if ( soap_call___ns1__addUserCustomInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        string outTmp("");	
        vector<string> tokens;
        UTF8ToMultiByte(*(outData.return_), outTmp);
	    tokenize(outTmp, tokens, "|");
        if (tokens.at(0) == "FALSE" && tokens.size() >= 2) {
            return tokens.at(1);       
        }	
		destroySoap();
    } else {
		destroySoap();
	    return "连接服务器失败，请检查网络连接。";      
    }
#endif
    return "TRUE";
}
    
// delete user custom information 删除定制
string ServerIO::deleteUserCustomInf(string customID)
{
#ifdef _OFF_LINE_
#else
    // 调用
    ns2__deleteUserCustomInf inData;
    std::string id(userInf.id);
    inData.uid = &id;
    inData.input = &customID;

    ns2__deleteUserCustomInfResponse outData;
   
    if ( soap_call___ns1__deleteUserCustomInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        string outTmp("");	
        vector<string> tokens;
        UTF8ToMultiByte(*(outData.return_), outTmp);
	    tokenize(outTmp, tokens, "|");
        if (tokens.at(0) == "FALSE" && tokens.size() >= 2) {
            return tokens.at(1);       
        }	
		destroySoap();
    } else {
		destroySoap();
	    return "连接服务器失败，请检查网络连接。";      
    }
#endif
     return "TRUE";
}
    
// Get new goods inf 获取最新货源
int ServerIO::getNewGoodsInf(vector<TabNewInfRecord> &inf, inputParam& input)
{
#ifdef _OFF_LINE_
    inf.clear();

    for (int i=0; i<input.record; ++i) {
        TabNewInfRecord tmp;
        tmp.recordID = "296";
        tmp.startPlace = "浙江省杭州市";
        tmp.endPlace = "江苏省常州市";
        tmp.record = "有货9吨，求10米长车。";
        tmp.tel = "联系电话:15866666666";
        inf.push_back(tmp);
    }
#else
    // 调用
    ns2__getNewGoodsInf inData;
    std::string id(userInf.id);
    inData.uid = &id;
    inData.record = input.record;
    inData.curpage = input.curpage;

    ns2__getNewGoodsInfResponse outData;
	int n = soap_call___ns1__getNewGoodsInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData);
    if ( n== SOAP_OK) {
        inf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
            string outTmp("");	
            vector<string> tokens;
            TabNewInfRecord tmp;
			UTF8ToMultiByte(*iter, outTmp);            
            tokenize(outTmp, tokens, "|");

#ifdef _NEWCODE_
			if (tokens.at(0) == "TRUE" && tokens.size() >= 14) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);
				tmp.startPlace = tokens.at(4) + tokens.at(5);
				tmp.endPlace = tokens.at(6) + tokens.at(7);
				tmp.record = tokens.at(11) + "(" + tokens.at(12) + ")。";
				tmp.tel = " ";
				if (tokens.at(8) != "NULL") {
					tmp.tel +=  tokens.at(8);
					tmp.tel += " ";
				} else {
					if (tokens.at(9) != "NULL") {
						tmp.tel +=  tokens.at(9);
						tmp.tel += " ";
					}
				}
				tmp.tel += tokens.at(10);
				tmp.pubUID = tokens.at(13);
				inf.push_back(tmp);                
			}
#else
			if (tokens.at(0) == "TRUE" && tokens.size() >= 16)
			{
				FillNewGoodsInfo(tokens, tmp);
				inf.push_back(tmp);                
			}
#endif


			++iter;
		}	
		destroySoap();
	   
   } else {
	   destroySoap();
	   return -1;
	   //std::cout << "fail" << std::endl;       
   }

#endif
    return 0;
}
    
// Get custom goods information 获取定制货源
int ServerIO::getCustomGoodsInf(vector<TabCustomInfRecord> &inf, inputParam& input)
{
#ifdef _OFF_LINE_
    inf.clear();
    bool ifFind = false;
    TabCustomInfRecord tmp;

    if (hyZoneInf.size() < 1) {
        return 0;
    }

    vector<CustomZoneInf>::iterator iter = hyZoneInf.begin();
	while (iter != hyZoneInf.end()) {
        if ((*iter).id == input.customid) {
            tmp.startPlace = (*iter).startProvince + (*iter).startCity;
            tmp.endPlace = (*iter).endProvince + (*iter).endCity;
            ifFind = true;
            break;
        }
		++iter;
	}    

    if (!ifFind) {
        tmp.startPlace = hyZoneInf.begin()->startProvince + hyZoneInf.begin()->startCity;
        tmp.endPlace = hyZoneInf.begin()->endProvince + hyZoneInf.begin()->endCity;
    }

    for (int i=0; i<input.record; ++i) {
        tmp.recordID = "296";
        tmp.record = "有货9吨，求10米长车。";
        tmp.tel = "联系电话:15866666666";
        inf.push_back(tmp);
    }
#else
    // 调用
    ns2__getCustomGoodsInf inData;
    std::string id(userInf.id);
    inData.uid = &id;
    inData.customid = atoi(input.customid.c_str());
    inData.record = input.record;
    inData.curpage = input.curpage;

    ns2__getCustomGoodsInfResponse outData;
   
    if ( soap_call___ns1__getCustomGoodsInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        inf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
            string outTmp("");	
            vector<string> tokens;
            TabCustomInfRecord tmp;
			UTF8ToMultiByte(*iter, outTmp);            
            tokenize(outTmp, tokens, "|");
#ifdef _NEWCODE_
			if (tokens.at(0) == "TRUE" && tokens.size() >= 14) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);
				tmp.startPlace = tokens.at(4) + tokens.at(5);
				tmp.endPlace = tokens.at(6) + tokens.at(7);
				tmp.record = tokens.at(11) + "(" + tokens.at(12) + ")。";
				tmp.tel = " ";
				if (tokens.at(8) != "NULL") {
					tmp.tel +=  tokens.at(8);
					tmp.tel += " ";
				} else {
					if (tokens.at(9) != "NULL") {
						tmp.tel +=  tokens.at(9);
						tmp.tel += " ";
					}
				}
				tmp.tel += tokens.at(10);
				tmp.pubUID = tokens.at(13);
				inf.push_back(tmp);                
			}
#else
			if (tokens.at(0) == "TRUE" && tokens.size() >= 16) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);
				tmp.startPlace = tokens.at(4) + tokens.at(5);
				if (tokens.at(6) != "NULL")
				{
					tmp.startPlace +=  tokens.at(6);
				}

				tmp.endPlace = tokens.at(7) + tokens.at(8);

				if (tokens.at(9) != "NULL")
				{
					tmp.endPlace +=  tokens.at(9);
				}

				tmp.record = tokens.at(13) + "(" + (tmp.pubTime = tokens.at(14)) + ")。";
				tmp.tel = " ";
				if (tokens.at(10) != "NULL") {
					tmp.tel +=  tmp.pubName = tokens.at(10);
					tmp.tel += " ";
				} else {
					if (tokens.at(11) != "NULL") {
						tmp.tel +=  tmp.pubName = tokens.at(11);
						tmp.tel += " ";
					}
				}
				//tmp.tel += tokens.at(12);
				if (tokens.at(12) != "NULL")
				{
					tmp.tel += tokens.at(12);
				}
				tmp.pubUID = tokens.at(15);

				if( tokens.size() >=  20 )
				{
					//tmp.pubURL = tokens.at(16);//not used
					tmp.pubAddress = tokens.at(17);
					tmp.dateTime = tokens.at(18);
					tmp.state = tokens.at(19);
				}

				inf.push_back(tmp);                
			}
#endif


			++iter;
		}	   
	   destroySoap();
   } else {
	   destroySoap();
	   return -1;
	   //std::cout << "fail" << std::endl;       
   }

#endif
    return 0;
}
    
// Get my goods information 我的货源
int ServerIO::getMyGoodsInf(vector<TabMyInfRecord> &inf, inputParam& input)
{
#ifdef _OFF_LINE_
    inf.clear();

    for (int i=0; i<input.record; ++i) {
        TabMyInfRecord tmp;
        tmp.recordID = "296";
        tmp.startPlace = "北京市";
        tmp.endPlace = "上海市";
        tmp.record = "有货20吨，求10米长车。";
        tmp.tel = "联系电话:13966666666";
        inf.push_back(tmp);
    }
#else
    // 调用
    ns2__getMyGoodsInf inData;
    std::string id(userInf.id);
    inData.uid = &id;
    inData.record = input.record;
    inData.curpage = input.curpage;

    ns2__getMyGoodsInfResponse outData;
   
    if ( soap_call___ns1__getMyGoodsInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        inf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
            string outTmp("");	
            vector<string> tokens;
            TabMyInfRecord tmp;
			UTF8ToMultiByte(*iter, outTmp);            
            tokenize(outTmp, tokens, "|");

#ifdef _NEWCODE_
			if (tokens.at(0) == "TRUE" && tokens.size() >= 14) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);
				tmp.startPlace = tokens.at(4) + tokens.at(5);
				tmp.endPlace = tokens.at(6) + tokens.at(7);
				tmp.record = tokens.at(11) + "(" + tokens.at(12) + ")。";
				tmp.tel = " ";
				if (tokens.at(8) != "NULL") {
					tmp.tel +=  tokens.at(8);
					tmp.tel += " ";
				} else {
					if (tokens.at(9) != "NULL") {
						tmp.tel +=  tokens.at(9);
						tmp.tel += " ";
					}
				}
				tmp.tel += tokens.at(10);                
				tmp.pubUID = tokens.at(13);
				inf.push_back(tmp);                
			}
#else
			if (tokens.at(0) == "TRUE" && tokens.size() >= 16) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);

				tmp.startPlace = (tmp.startProv = tokens.at(4)) + (tmp.startCity = tokens.at(5));
				if (tokens.at(6) != "NULL")
				{
					tmp.startPlace +=  (tmp.startCounty = tokens.at(6));
				}

				tmp.endPlace = (tmp.endProv = tokens.at(7)) + (tmp.endCity = tokens.at(8));

				if (tokens.at(9) != "NULL")
				{
					tmp.endPlace += tmp.endCounty = tokens.at(9);
				}

				tmp.record = (tmp.preview = tokens.at(13)) + "(" + (tmp.pubTime = tokens.at(14)) + ")。";
				tmp.tel = " ";
				 if (tokens.at(10) != "NULL") 
				{
					tmp.tel +=  tmp.pubName = tokens.at(10);
					tmp.tel += " ";
				} else {
					if (tokens.at(11) != "NULL") 
					{
						tmp.tel +=  tmp.pubName = tokens.at(11);
						tmp.tel += " ";
					}
				}
				//tmp.tel += tokens.at(12);
				if (tokens.at(12) != "NULL")
				{
					tmp.tel += tmp.phone = tokens.at(12);
				}
				tmp.pubUID = tokens.at(15);

				if( tokens.size() >=  20 )
				{
				//	tmp.pubURL = tokens.at(16); not used
					tmp.pubAddress = tokens.at(17);
					tmp.dateTime = tokens.at(18);
					tmp.state = tokens.at(19);
				}
				inf.push_back(tmp);                
			}
#endif
 

			++iter;
		}	   
	   destroySoap();
   } else {
	   destroySoap();
	   return -1;
	   //std::cout << "fail" << std::endl;       
   }

#endif

    return 0;    
}

int ServerIO::getPersisGoodsInfo(vector<TabNewInfRecord> &inf, inputParam& input)
{
#ifdef _OFF_LINE_
	inf.clear();

	for (int i=0; i<input.record; ++i) {
		TabMyInfRecord tmp;
		tmp.recordID = "296";
		tmp.startPlace = "北京市";
		tmp.endPlace = "上海市";
		tmp.record = "有货20吨，求10米长车。";
		tmp.tel = "联系电话:13966666666";
		inf.push_back(tmp);
	}
#else
	// 调用
	ns2__getPersisGoodsInfo inData;
	std::string id(userInf.id);
	inData.uid = &id;
	inData.record = input.record;
	inData.curpage = input.curpage;

	ns2__getPersisGoodsInfoResponse outData;

	if ( soap_call___ns1__getPersisGoodsInfo(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
		inf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
			string outTmp("");	
			vector<string> tokens;
			TabNewInfRecord tmp;
			UTF8ToMultiByte(*iter, outTmp);            
			tokenize(outTmp, tokens, "|");

#ifdef _NEWCODE_
			if (tokens.at(0) == "TRUE" && tokens.size() >= 14) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);
				tmp.startPlace = tokens.at(4) + tokens.at(5);
				tmp.endPlace = tokens.at(6) + tokens.at(7);
				tmp.record = tokens.at(11) + "(" + tokens.at(12) + ")。";
				tmp.tel = " ";
				if (tokens.at(8) != "NULL") {
					tmp.tel +=  tokens.at(8);
					tmp.tel += " ";
				} else {
					if (tokens.at(9) != "NULL") {
						tmp.tel +=  tokens.at(9);
						tmp.tel += " ";
					}
				}
				tmp.tel += tokens.at(10);                
				tmp.pubUID = tokens.at(13);
				inf.push_back(tmp);                
			}
#else
			if (tokens.at(0) == "TRUE" && tokens.size() >= 16) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);

				tmp.startPlace = tokens.at(4) + tokens.at(5);
				if (tokens.at(6) != "NULL")
				{
					tmp.startPlace +=  tokens.at(6);
				}

				tmp.endPlace = tokens.at(7) + tokens.at(8);

				if (tokens.at(9) != "NULL")
				{
					tmp.endPlace += tokens.at(9);
				}

				tmp.record = tokens.at(13) + "(" + (tmp.pubTime = tokens.at(14)) + ")。";
				tmp.tel = " ";
				if (tokens.at(10) != "NULL") {
					tmp.tel +=  tmp.pubName = tokens.at(10);
					tmp.tel += " ";
				} else {
					if (tokens.at(11) != "NULL") {
						tmp.tel +=  tmp.pubName = tokens.at(11);
						tmp.tel += " ";
					}
				}
				//tmp.tel += tokens.at(12);
				if (tokens.at(12) != "NULL")
				{
					tmp.tel += tokens.at(12);
				}
				tmp.pubUID = tokens.at(15);

				if( tokens.size() >=  20 )
				{
					//	tmp.pubURL = tokens.at(16); not used
					tmp.pubAddress = tokens.at(17);
					tmp.dateTime = tokens.at(18);
					tmp.state = tokens.at(19);
					tmp.bLongTime = true;
				}
				inf.push_back(tmp);                
			}
#endif


			++iter;
		}	   
		destroySoap();
	} else {
		destroySoap();
		return -1;
		//std::cout << "fail" << std::endl;       
	}

#endif

	return 0;    
}
       
// Get new bulkGoods information 最新零担
int ServerIO::getNewBulkGoodsInf(vector<TabNewInfRecord> &inf, inputParam& input)
{
#ifdef _OFF_LINE_
    inf.clear();

    for (int i=0; i<input.record; ++i) {
        TabNewInfRecord tmp;
        tmp.recordID = "296";
        tmp.startPlace = "北京市市辖区东城区";
        tmp.endPlace = "吉林省长春市市辖区";
        tmp.record = "有货:危险品,需要后八轮车 (07-26 12:00)。";
        tmp.tel = "上海宇佳物流，联系电话:15265965698 0571-9999999";
        inf.push_back(tmp);
    }
#else

    // 调用
    ns2__getNewBulkGoodsInf inData;
    std::string id(userInf.id);
    inData.uid = &id;
    inData.record = input.record;
    inData.curpage = input.curpage;

    ns2__getNewBulkGoodsInfResponse outData;
   
    if ( soap_call___ns1__getNewBulkGoodsInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        inf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
            string outTmp("");	
            vector<string> tokens;
            TabNewInfRecord tmp;
			UTF8ToMultiByte(*iter, outTmp);            
            tokenize(outTmp, tokens, "|");
#ifdef _NEWCODE_
			if (tokens.at(0) == "TRUE" && tokens.size() >= 14) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);
				tmp.startPlace = tokens.at(4) + tokens.at(5);
				tmp.endPlace = tokens.at(6) + tokens.at(7);
				tmp.record = tokens.at(11) + "(" + tokens.at(12) + ")。";
				tmp.tel = " ";
				if (tokens.at(8) != "NULL") {
					tmp.tel +=  tokens.at(8);
					tmp.tel += " ";
				} else {
					if (tokens.at(9) != "NULL") {
						tmp.tel +=  tokens.at(9);
						tmp.tel += " ";
					}
				}
				tmp.tel += tokens.at(10);
				tmp.pubUID = tokens.at(13);
				inf.push_back(tmp);                
			}
#else
			if (tokens.at(0) == "TRUE" && tokens.size() >= 16) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);
				tmp.startPlace = tokens.at(4) + tokens.at(5);
				if (tokens.at(6) != "NULL")
				{
					tmp.startPlace +=  tokens.at(6);
				}

				tmp.endPlace = tokens.at(7) + tokens.at(8);

				if (tokens.at(9) != "NULL")
				{
					tmp.endPlace +=  tokens.at(9);
				}

				tmp.record = tokens.at(13) + "(" + tokens.at(14) + ")。";
				tmp.tel = " ";
				if (tokens.at(10) != "NULL") {
					tmp.tel +=  tokens.at(10);
					tmp.tel += " ";
				} else {
					if (tokens.at(11) != "NULL") {
						tmp.tel +=  tokens.at(11);
						tmp.tel += " ";
					}
				}
				//tmp.tel += tokens.at(12);
				if (tokens.at(12) != "NULL")
				{
					tmp.tel += tokens.at(12);
				}
				tmp.pubUID = tokens.at(15);
				inf.push_back(tmp);                
			}
#endif
			++iter;
		}	   
	   destroySoap();
   } else {
	   destroySoap();
	   return -1;
	   //std::cout << "fail" << std::endl;       
   }

#endif

    return 0;
}
    
// Get my BulkGoods information 我的零担
int ServerIO::getMyBulkGoodsInf(vector<TabMyInfRecord> &inf, inputParam& input)
{
#ifdef _OFF_LINE_
    inf.clear();

    for (int i=0; i<input.record; ++i) {
        TabMyInfRecord tmp;
        tmp.recordID = "296";
        tmp.startPlace = "浙江省杭州市市辖区";
        tmp.endPlace = "江西省南昌市市辖区";
        tmp.record = "有货:食品,(泡货) 重量：2,价格：2,需要5米车板车1辆. (06-25 19:08)。";
        tmp.tel = "江西卓越物流公司. 联系电话:15265965698 0571-9999999";
        inf.push_back(tmp);
    }  
#else
    // 调用
    ns2__getMyBulkGoodsInf inData;
    std::string id(userInf.id);
    inData.uid = &id;
    inData.record = input.record;
    inData.curpage = input.curpage;

    ns2__getMyBulkGoodsInfResponse outData;
   
    if ( soap_call___ns1__getMyBulkGoodsInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        inf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
            string outTmp("");	
            vector<string> tokens;
            TabMyInfRecord tmp;
			UTF8ToMultiByte(*iter, outTmp);            
            tokenize(outTmp, tokens, "|");

#ifdef _NEWCODE_
			if (tokens.at(0) == "TRUE" && tokens.size() >= 14) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);
				tmp.startPlace = tokens.at(4) + tokens.at(5);
				tmp.endPlace = tokens.at(6) + tokens.at(7);
				tmp.record = tokens.at(11) + "(" + tokens.at(12) + ")。";
				tmp.tel = " ";
				if (tokens.at(8) != "NULL") {
					tmp.tel +=  tokens.at(8);
					tmp.tel += " ";
				} else {
					if (tokens.at(9) != "NULL") {
						tmp.tel +=  tokens.at(9);
						tmp.tel += " ";
					}
				}
				tmp.tel += tokens.at(10);
				tmp.pubUID = tokens.at(13);
				inf.push_back(tmp);                
			}
#else
			if (tokens.at(0) == "TRUE" && tokens.size() >= 16) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);

				tmp.startPlace = tokens.at(4) + tokens.at(5);
				if (tokens.at(6) != "NULL")
				{
					tmp.startPlace +=  tokens.at(6);
				}

				tmp.endPlace = tokens.at(7) + tokens.at(8);

				if (tokens.at(9) != "NULL")
				{
					tmp.endPlace +=  tokens.at(9);
				}

				tmp.record = tokens.at(13) + "(" + tokens.at(14) + ")。";
				tmp.tel = " ";
				if (tokens.at(10) != "NULL") {
					tmp.tel +=  tokens.at(10);
					tmp.tel += " ";
				} else {
					if (tokens.at(11) != "NULL") {
						tmp.tel +=  tokens.at(11);
						tmp.tel += " ";
					}
				}
				//tmp.tel += tokens.at(12);
				if (tokens.at(12) != "NULL")
				{
					tmp.tel += tokens.at(12);
				}
				tmp.pubUID = tokens.at(15);
				inf.push_back(tmp);                
			}
#endif
			++iter;
		}	   
	   destroySoap();
   } else {
	   destroySoap();
	    return -1;
	   //std::cout << "fail" << std::endl;       
   }

#endif
 
    return 0;
}
      
// Get new cars information 最新车源
int ServerIO::getNewCarsInf(vector<TabNewInfRecord> &inf, inputParam& input)
{
#ifdef _OFF_LINE_
    inf.clear();

    for (int i=0; i<input.record; ++i) {
        TabNewInfRecord tmp;
        tmp.recordID = "296";
        tmp.startPlace = "福建省福州市市辖区";
        tmp.endPlace = "重庆市市辖区";
        tmp.record = "有7米集装箱车1辆, 载重:2吨,求货:冻品。(重货) (07-30 10:55)。";
        tmp.tel = "济南泺源货运公司 15267147987 010-3730987";
        inf.push_back(tmp);
    }
#else
    // 调用
	vector<TabNewInfRecord> infTemp;
    ns2__getNewCarsInf inData;
    std::string id(userInf.id);
    inData.uid = &id;
    inData.record = input.record;
    inData.curpage = input.curpage;

    ns2__getNewCarsInfResponse outData;
   
    if ( soap_call___ns1__getNewCarsInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        inf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
            string outTmp("");	
            vector<string> tokens;
            TabNewInfRecord tmp;
			UTF8ToMultiByte(*iter, outTmp);            
            tokenize(outTmp, tokens, "|");

#ifdef _NEWCODE_
			if (tokens.at(0) == "TRUE" && tokens.size() >= 14) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);
				tmp.startPlace = tokens.at(4) + tokens.at(5);
				tmp.endPlace = tokens.at(6) + tokens.at(7);
				tmp.record = tokens.at(11) + "(" + tokens.at(12) + ")。";
				tmp.tel = " ";
				if (tokens.at(8) != "NULL") {
					tmp.tel +=  tokens.at(8);
					tmp.tel += " ";
				} else {
					if (tokens.at(9) != "NULL") {
						tmp.tel +=  tokens.at(9);
						tmp.tel += " ";
					}
				}
				tmp.tel += tokens.at(10);
				tmp.pubUID = tokens.at(13);
				infTemp.push_back(tmp);                
			}
#else
			if (tokens.at(0) == "TRUE" && tokens.size() >= 22)
			{
				FillNewCarsInfo(tokens, tmp);
				inf.push_back(tmp);                
			}
#endif


			++iter;
		}	

	   //inf.assign(infTemp.begin(),   infTemp.end());
	   destroySoap();
   } else {
	   destroySoap();
	    return -1;
	   //std::cout << "fail" << std::endl;       
   }

#endif

    return 0;
}
       
// Get custom cars information 定制车源
int ServerIO::getCustomCarsInf(vector<TabCustomInfRecord> &inf, inputParam& input)
{    
#ifdef _OFF_LINE_
    inf.clear();
    bool ifFind = false;
    TabCustomInfRecord tmp;

    if (cyZoneInf.size() < 1) {
        return 0;
    }

    vector<CustomZoneInf>::iterator iter = cyZoneInf.begin();
	while (iter != cyZoneInf.end()) {
        if ((*iter).id == input.customid) {
            tmp.startPlace = (*iter).startProvince + (*iter).startCity;
            tmp.endPlace = (*iter).endProvince + (*iter).endCity;
            ifFind = true;
            break;
        }
		++iter;
	}    

    if (!ifFind) {
        tmp.startPlace = cyZoneInf.begin()->startProvince + cyZoneInf.begin()->startCity;
        tmp.endPlace = cyZoneInf.begin()->endProvince + cyZoneInf.begin()->endCity;
    }

    for (int i=0; i<input.record; ++i) {
        tmp.recordID = "296";
        tmp.record =  "有12.5米前四后四1辆,求货:机械设备。 (07-15 09:03)。";
        tmp.tel = "潍坊天宇物流公司 15267147987 0571-87703986";
        inf.push_back(tmp);
    } 
#else
    // 调用
    ns2__getCustomCarsInf inData;
    std::string id(userInf.id);
    inData.uid = &id;
    inData.customid = atoi(input.customid.c_str());
    inData.record = input.record;
    inData.curpage = input.curpage;

    ns2__getCustomCarsInfResponse outData;
   
    if ( soap_call___ns1__getCustomCarsInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        inf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
            string outTmp("");	
            vector<string> tokens;
            TabCustomInfRecord tmp;
			UTF8ToMultiByte(*iter, outTmp);            
            tokenize(outTmp, tokens, "|");
#ifdef _NEWCODE_
			if (tokens.at(0) == "TRUE" && tokens.size() >= 14) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);
				tmp.startPlace = tokens.at(4) + tokens.at(5);
				tmp.endPlace = tokens.at(6) + tokens.at(7);
				tmp.record = tokens.at(11) + "(" + tokens.at(12) + ")。";
				tmp.tel = " ";
				if (tokens.at(8) != "NULL") {
					tmp.tel +=  tokens.at(8);
					tmp.tel += " ";
				} else {
					if (tokens.at(9) != "NULL") {
						tmp.tel +=  tokens.at(9);
						tmp.tel += " ";
					}
				}
				tmp.tel += tokens.at(10);
				tmp.pubUID = tokens.at(13);
				inf.push_back(tmp);                
			}
#else
			if (tokens.at(0) == "TRUE" && tokens.size() >= 22) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);

				tmp.startPlace = tokens.at(4) + tokens.at(5);

				if (tokens.at(6) != "NULL")
				{
					tmp.startPlace +=  tokens.at(6);
				}

				tmp.endPlace = tokens.at(7) + tokens.at(8);

				if (tokens.at(9) != "NULL")
				{
					tmp.endPlace +=  tokens.at(9);
				}

				if (tokens.at(10) != "NULL")
				{
					tmp.endPlace += " ";
					tmp.endPlace += tokens.at(10);
					tmp.endPlace += tokens.at(11);
					if (tokens.at(12) != "NULL")
					{
						tmp.endPlace +=  tokens.at(12);
					}
				}

				if (tokens.at(13) != "NULL")
				{
					tmp.endPlace += " ";
					tmp.endPlace += tokens.at(13);
					tmp.endPlace += tokens.at(14);
					if (tokens.at(15) != "NULL")
					{
						tmp.endPlace +=  tokens.at(15);
					}
				}

				tmp.record = tokens.at(19) + "(" + (tmp.pubTime = tokens.at(20)) + ")。";
				tmp.tel = " ";
				if (tokens.at(16) != "NULL") {
					tmp.tel +=  tmp.pubName = tokens.at(16);
					tmp.tel += " ";
				} else {
					if (tokens.at(17) != "NULL") {
						tmp.tel +=  tmp.pubName = tokens.at(17);
						tmp.tel += " ";
					}
				}
				if (tokens.at(18) != "NULL")
				{
					tmp.tel += tokens.at(18);
				}
				tmp.pubUID = tokens.at(21);

				if( tokens.size() >= 26)
				{
					//tmp.pubURL = tokens.at(22); //not used
					tmp.pubAddress = tokens.at(23);
					tmp.dateTime = tokens.at(24);
					tmp.state = tokens.at(25);
				}
				inf.push_back(tmp);                
			}
#endif


			++iter;
		}	   
	   destroySoap();
   } else {
	   destroySoap();
	   //std::cout << "fail" << std::endl;       
   }

#endif
    return 0;
}
        
// Get my cars information 我的车源
int ServerIO::getMyCarsInf(vector<TabMyInfRecord> &inf, inputParam& input)
{
#ifdef _OFF_LINE_
    inf.clear();

    for (int i=0; i<input.record; ++i) {
        TabMyInfRecord tmp;
        tmp.recordID = "296";
        tmp.startPlace = "浙江省杭州市市辖区";
        tmp.endPlace = "湖北省武汉市市辖区";
        tmp.record = "有6.2米敞篷车1辆, 载重:5吨,求货:冻品。(重货) (06-23 12:32)。";
        tmp.tel = "江西卓越物流公司. 联系电话: 0571-9999999";
        inf.push_back(tmp);
    } 
#else
    // 调用
    ns2__getMyCarsInf inData;
    std::string id(userInf.id);
    inData.uid = &id;
    inData.record = input.record;
    inData.curpage = input.curpage;

    ns2__getMyCarsInfResponse outData;
   
    if ( soap_call___ns1__getMyCarsInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        inf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
            string outTmp("");	
            vector<string> tokens;
            TabMyInfRecord tmp;
			UTF8ToMultiByte(*iter, outTmp);            
            tokenize(outTmp, tokens, "|");

#ifdef _NEWCODE_
			if (tokens.at(0) == "TRUE" && tokens.size() >= 14) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);
				tmp.startPlace = tokens.at(4) + tokens.at(5);
				tmp.endPlace = tokens.at(6) + tokens.at(7);
				tmp.record = tokens.at(11) + "(" + tokens.at(12) + ")。";
				tmp.tel = " ";
				if (tokens.at(8) != "NULL") {
					tmp.tel +=  tokens.at(8);
					tmp.tel += " ";
				} else {
					if (tokens.at(9) != "NULL") {
						tmp.tel +=  tokens.at(9);
						tmp.tel += " ";
					}
				}
				tmp.tel += tokens.at(10);
				tmp.pubUID = tokens.at(13);
				inf.push_back(tmp);                
			}
#else
			if (tokens.at(0) == "TRUE" && tokens.size() >= 22) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);

				tmp.startPlace = (tmp.startProv = tokens.at(4)) + (tmp.startCity = tokens.at(5));
				
				if (tokens.at(6) != "NULL")
				{
					tmp.startPlace +=  tmp.startCounty = tokens.at(6);
				}

				tmp.endPlace = (tmp.endProv = tokens.at(7)) + (tmp.endCity = tokens.at(8));

				if (tokens.at(9) != "NULL")
				{
					tmp.endPlace +=  tmp.endCounty = tokens.at(9);
				}

				if (tokens.at(10) != "NULL")
				{
					tmp.endPlace += " ";
					tmp.endPlace += tokens.at(10);
					tmp.endPlace += tokens.at(11);
					if (tokens.at(12) != "NULL")
					{
						tmp.endPlace +=  tokens.at(12);
					}
				}

				if (tokens.at(13) != "NULL")
				{
					tmp.endPlace += " ";
					tmp.endPlace += tokens.at(13);
					tmp.endPlace += tokens.at(14);
					if (tokens.at(15) != "NULL")
					{
						tmp.endPlace +=  tokens.at(15);
					}
				}

				tmp.record = (tmp.preview = tokens.at(19)) + "(" + (tmp.pubTime = tokens.at(20)) + ")。";
				tmp.tel = " ";
				if (tokens.at(16) != "NULL") {
					tmp.tel +=  tmp.pubName = tokens.at(16);
					tmp.tel += " ";
				} 
				else
				{
					if (tokens.at(17) != "NULL") 
					{
						tmp.tel +=  tmp.pubName = tokens.at(17);
						tmp.tel += " ";
					}
				}
				if (tokens.at(18) != "NULL")
				{
					tmp.tel += tmp.phone = tokens.at(18);
				}
				tmp.pubUID = tokens.at(21);

				if( tokens.size() >= 26)
				{
				//	tmp.pubURL = tokens.at(22); //not used
					tmp.pubAddress = tokens.at(23);
					tmp.dateTime = tokens.at(24);
					tmp.state = tokens.at(25);
					if( tokens.size() > 26 )
					{
						tmp.carLength = tokens.at(26);
					}
				}

				inf.push_back(tmp);                
			}
#endif


			++iter;
		}		   
	   destroySoap();
   } else {
	   destroySoap();
	    return -1;
	   //std::cout << "fail" << std::endl;       
   }

#endif

    return 0;
}

int ServerIO::getPersisCarsInfo(vector<TabNewInfRecord> &inf, inputParam& input)
{
#ifdef _OFF_LINE_
	inf.clear();

	for (int i=0; i<input.record; ++i) {
		TabNewInfRecord tmp;
		tmp.recordID = "296";
		tmp.startPlace = "浙江省杭州市市辖区";
		tmp.endPlace = "湖北省武汉市市辖区";
		tmp.record = "有6.2米敞篷车1辆, 载重:5吨,求货:冻品。(重货) (06-23 12:32)。";
		tmp.tel = "江西卓越物流公司. 联系电话: 0571-9999999";
		inf.push_back(tmp);
	} 
#else
	// 调用
	ns2__getPersisCarsInfo inData;
	std::string id(userInf.id);
	inData.uid = &id;
	inData.record = input.record;
	inData.curpage = input.curpage;

	ns2__getPersisCarsInfoResponse outData;

	if ( soap_call___ns1__getPersisCarsInfo(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
		inf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
			string outTmp("");	
			vector<string> tokens;
			TabNewInfRecord tmp;
			UTF8ToMultiByte(*iter, outTmp);            
			tokenize(outTmp, tokens, "|");

#ifdef _NEWCODE_
			if (tokens.at(0) == "TRUE" && tokens.size() >= 14) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);
				tmp.startPlace = tokens.at(4) + tokens.at(5);
				tmp.endPlace = tokens.at(6) + tokens.at(7);
				tmp.record = tokens.at(11) + "(" + tokens.at(12) + ")。";
				tmp.tel = " ";
				if (tokens.at(8) != "NULL") {
					tmp.tel +=  tokens.at(8);
					tmp.tel += " ";
				} else {
					if (tokens.at(9) != "NULL") {
						tmp.tel +=  tokens.at(9);
						tmp.tel += " ";
					}
				}
				tmp.tel += tokens.at(10);
				tmp.pubUID = tokens.at(13);
				inf.push_back(tmp);                
			}
#else
			if (tokens.at(0) == "TRUE" && tokens.size() >= 22) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);

				tmp.startPlace = (tokens.at(4)) + (tokens.at(5));

				if (tokens.at(6) != "NULL")
				{
					tmp.startPlace += tokens.at(6);
				}

				tmp.endPlace = (tokens.at(7)) + (tokens.at(8));

				if (tokens.at(9) != "NULL")
				{
					tmp.endPlace +=  tokens.at(9);
				}

				if (tokens.at(10) != "NULL")
				{
					tmp.endPlace += " ";
					tmp.endPlace += tokens.at(10);
					tmp.endPlace += tokens.at(11);
					if (tokens.at(12) != "NULL")
					{
						tmp.endPlace +=  tokens.at(12);
					}
				}

				if (tokens.at(13) != "NULL")
				{
					tmp.endPlace += " ";
					tmp.endPlace += tokens.at(13);
					tmp.endPlace += tokens.at(14);
					if (tokens.at(15) != "NULL")
					{
						tmp.endPlace +=  tokens.at(15);
					}
				}

				tmp.record = tokens.at(19) + "(" + (tmp.pubTime = tokens.at(20)) + ")。";
				tmp.tel = " ";
				if (tokens.at(16) != "NULL") {
					tmp.tel +=  tmp.pubName = tokens.at(16);
					tmp.tel += " ";
				} else {
					if (tokens.at(17) != "NULL") {
						tmp.tel +=  tmp.pubName = tokens.at(17);
						tmp.tel += " ";
					}
				}
				if (tokens.at(18) != "NULL")
				{
					tmp.tel += tokens.at(18);
				}
				tmp.pubUID = tokens.at(21);

				if( tokens.size() >= 26)
				{
					//	tmp.pubURL = tokens.at(22); //not used
					tmp.pubAddress = tokens.at(23);
					tmp.dateTime = tokens.at(24);
					tmp.state = tokens.at(25);
					tmp.bLongTime = true;
				}

				inf.push_back(tmp);                
			}
#endif


			++iter;
		}		   
		destroySoap();
	} else {
		destroySoap();
		return -1;
		//std::cout << "fail" << std::endl;       
	}

#endif

	return 0;
}
        
// Get all special line information 所有专线
int ServerIO::getAllSpecialLineInf(vector<TabSpecialLineRecord> &inf, inputParam& input)
{  
#ifdef _OFF_LINE_
    inf.clear();

    for (int i=0; i<input.record; ++i) {
        TabSpecialLineRecord tmp;
        tmp.recordID = "296";
        tmp.startPlace = "广东省东莞市";
        tmp.endPlace = "浙江省金华市";
        tmp.weightPrice = "450元/吨";
        tmp.lightPrice = "120元/方";
        tmp.schedules = "每隔1天一班(单程)";
        tmp.needTime = "途中时间: 1天";
        tmp.record = "联系人：黄力。";
        tmp.tel = "电话：0571-87703986 15267147987";
        inf.push_back(tmp);
    } 
#else
    // 调用
    ns2__getAllSpecialLineInf inData;
    std::string id(userInf.id);
    inData.uid = &id;
    inData.record = input.record;
    inData.curpage = input.curpage;

    ns2__getAllSpecialLineInfResponse outData;
   
    if ( soap_call___ns1__getAllSpecialLineInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        inf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
            string outTmp("");	
            vector<string> tokens;
            TabSpecialLineRecord tmp;
			UTF8ToMultiByte(*iter, outTmp);            
            tokenize(outTmp, tokens, "|");
            if (tokens.at(0) == "TRUE" && tokens.size() >= 16) {
                tmp.totalNum = tokens.at(1);
                tmp.returnNum = tokens.at(2);
                tmp.recordID = tokens.at(3);
                tmp.startPlace = tokens.at(4) + tokens.at(5);
                tmp.endPlace = tokens.at(6) + tokens.at(7);
                tmp.weightPrice = tokens.at(8);
                tmp.lightPrice = tokens.at(9);
                tmp.schedules = tokens.at(10);
                tmp.needTime = tokens.at(11);
                tmp.record = "(" + tokens.at(14) + ")";

                tmp.tel = " 联系方式：";
                if (tokens.at(12) != "NULL") {
                    tmp.tel +=  tmp.pubName = tokens.at(12);
                    tmp.tel += " ";
                }
				if (tokens.at(13) != "NULL")
				{
					tmp.tel += tokens.at(13);
				}
                tmp.pubUID = tokens.at(15);

				if( tokens.size() == 22)
				{
					tmp.startAddr = tokens.at(16);
					tmp.startContact = tokens.at(17);
					tmp.startPhone = tokens.at(18);
					tmp.destAddr = tokens.at(19);
					tmp.destContact = tokens.at(20);
					tmp.destPhone = tokens.at(21);
				}
                inf.push_back(tmp);                
            }

			++iter;
		}	
		destroySoap();
   } else {
	   destroySoap();
	    return -1;
	   //std::cout << "fail" << std::endl;       
   }
#endif

    return 0;
}
    
// Get My special line information 我的专线
int ServerIO::getMySpecialLineInf(vector<TabSpecialLineRecord> &inf, inputParam& input)
{
#ifdef _OFF_LINE_
    inf.clear();

    for (int i=0; i<input.record; ++i) {
        TabSpecialLineRecord tmp;
        tmp.recordID = "296";
        tmp.startPlace = "浙江省杭州市";
        tmp.endPlace = "浙江省金华市";
        tmp.weightPrice = "600元/吨";
        tmp.lightPrice = "200元/方";
        tmp.schedules = "每隔1天一班(单程)";
        tmp.needTime = "途中时间: 1天";
        tmp.record = "联系人：张三。";
        tmp.tel = "电话：0571-87703986 15267147987";
        inf.push_back(tmp);
    } 
#else
    // 调用
    ns2__getMySpecialLineInf inData;
    std::string id(userInf.id);
    inData.uid = &id;
    inData.record = input.record;
    inData.curpage = input.curpage;

    ns2__getMySpecialLineInfResponse outData;
   
    if ( soap_call___ns1__getMySpecialLineInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        inf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
            string outTmp("");	
            vector<string> tokens;
            TabSpecialLineRecord tmp;
			UTF8ToMultiByte(*iter, outTmp);            
            tokenize(outTmp, tokens, "|");
            if (tokens.at(0) == "TRUE" && tokens.size() >= 16) {
                tmp.totalNum = tokens.at(1);
                tmp.returnNum = tokens.at(2);
                tmp.recordID = tokens.at(3);
                tmp.startPlace = tokens.at(4) + tokens.at(5);
                tmp.endPlace = tokens.at(6) + tokens.at(7);
                tmp.weightPrice = tokens.at(8);
                tmp.lightPrice = tokens.at(9);
                tmp.schedules = tokens.at(10);
                tmp.needTime = tokens.at(11);
                tmp.record = "(" + tokens.at(14) + ")";

                tmp.tel = " 联系方式：";
                if (tokens.at(12) != "NULL") {
                    tmp.tel +=  tmp.pubName = tokens.at(12);
                    tmp.tel += " ";
                }
				if (tokens.at(13) != "NULL")
				{
					tmp.tel += tokens.at(13);
				}
                tmp.pubUID = tokens.at(15);

				if( tokens.size() == 22)
				{
					tmp.startAddr = tokens.at(16);
					tmp.startContact = tokens.at(17);
					tmp.startPhone = tokens.at(18);
					tmp.destAddr = tokens.at(19);
					tmp.destContact = tokens.at(20);
					tmp.destPhone = tokens.at(21);
				}

                inf.push_back(tmp);                
            }

			++iter;
		}	   
	   destroySoap();
   } else {
	   destroySoap();
	    return -1;
	   //std::cout << "fail" << std::endl;       
   }

#endif
    return 0;
}
    
// Get Favorite special line information 我的收藏
int ServerIO::getFavoriteSpecialLineInf(vector<TabSpecialLineRecord> &inf, inputParam& input)
{
#ifdef _OFF_LINE_
    inf.clear();

    for (int i=0; i<input.record; ++i) {
        TabSpecialLineRecord tmp;
        tmp.recordID = "296";
        tmp.startPlace = "广东省东莞市";
        tmp.endPlace = "广东省深圳市";
        tmp.weightPrice = "900元/吨";
        tmp.lightPrice = "120元/方";
        tmp.schedules = "每隔1天一班(单程)";
        tmp.needTime = "途中时间: 1天";
        tmp.record = "联系人：李四。";
        tmp.tel = "电话：0571-87703986 15267147987";
        inf.push_back(tmp);
    } 
#else
    // 调用
    ns2__getFavoriteSpecialLineInf inData;
    std::string id(userInf.id);
    inData.uid = &id;
    inData.record = input.record;
    inData.curpage = input.curpage;

    ns2__getFavoriteSpecialLineInfResponse outData;
   
    if ( soap_call___ns1__getFavoriteSpecialLineInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        inf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
            string outTmp("");	
            vector<string> tokens;
            TabSpecialLineRecord tmp;
			UTF8ToMultiByte(*iter, outTmp);            
            tokenize(outTmp, tokens, "|");
            if (tokens.at(0) == "TRUE" && tokens.size() >= 16) {
                tmp.totalNum = tokens.at(1);
                tmp.returnNum = tokens.at(2);
                tmp.recordID = tokens.at(3);
                tmp.startPlace = tokens.at(4) + tokens.at(5);
                tmp.endPlace = tokens.at(6) + tokens.at(7);
                tmp.weightPrice = tokens.at(8);
                tmp.lightPrice = tokens.at(9);
                tmp.schedules = tokens.at(10);
                tmp.needTime = tokens.at(11);
                tmp.record = "(" + tokens.at(14) + ")";

                tmp.tel = " 联系方式：";
                if (tokens.at(12) != "NULL") {
                    tmp.tel +=  tmp.pubName = tokens.at(12);
                    tmp.tel += " ";
                }
				if (tokens.at(13) != "NULL")
				{
					tmp.tel += tokens.at(13);
				}
                tmp.pubUID = tokens.at(15);

				if( tokens.size() == 22)
				{
					tmp.startAddr = tokens.at(16);
					tmp.startContact = tokens.at(17);
					tmp.startPhone = tokens.at(18);
					tmp.destAddr = tokens.at(19);
					tmp.destContact = tokens.at(20);
					tmp.destPhone = tokens.at(21);
				}

                inf.push_back(tmp);                
            }

			++iter;
		}	   
	   destroySoap();
   } else {
	   destroySoap();
	    return -1;
	   //std::cout << "fail" << std::endl;       
   }

#endif

    return 0;
}
    
// Collect special Line
string ServerIO::collectSpecialLine(string recordID)
{
#ifdef _OFF_LINE_
#else
    ns2__collectSpecialLine inData;
    std::string id(userInf.id);
    inData.uid = &id;
    inData.recordID = &recordID;

    ns2__collectSpecialLineResponse outData;
   
    if ( soap_call___ns1__collectSpecialLine(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        string outTmp("");	
        vector<string> tokens;
        UTF8ToMultiByte(*(outData.return_), outTmp);
	    tokenize(outTmp, tokens, "|");
        if (tokens.at(0) == "FALSE" && tokens.size() >= 2) {
            return tokens.at(1);       
        }	
		destroySoap();
   } else {
	   destroySoap();
	   return "连接服务器失败，请检查网络连接。";       
   }
#endif
    return "TRUE";
}
    
// Get search goods result
int ServerIO::getSearchGoodsInf(const InSearchGoods& keyword, vector<TabNewInfRecord> &inf, inputParam& input)
{
#ifdef _OFF_LINE_
    inf.clear();

    for (int i=0; i<input.record; ++i) {
        TabNewInfRecord tmp;
        tmp.recordID = "296";
        tmp.startPlace = "江苏南京";//keyword.startProvince + keyword.startCity;
        tmp.endPlace = "上海浦东";//keyword.endProvince + keyword.endCity;
        tmp.record = "有货5吨，求:" + string("前四后十") + "3.4米";//keyword.carLength + keyword.carType + "。";
        tmp.tel = "联系电话:13866666666";
        inf.push_back(tmp);
    }
#else
	string sKeyword;
	FormatGoodsSearchString(keyword, sKeyword);
	return getSearchGoodsInf(sKeyword, inf, input);
#endif

    return 0;
}
int ServerIO::getSearchGoodsInf(const string& sKeyword, vector<TabNewInfRecord> &inf, inputParam& input)
{
#ifdef _OFF_LINE_
	inf.clear();

	for (int i=0; i<input.record; ++i) {
		TabNewInfRecord tmp;
		tmp.recordID = "296";
		tmp.startPlace = "江苏南京";//keyword.startProvince + keyword.startCity;
		tmp.endPlace = "上海浦东";//keyword.endProvince + keyword.endCity;
		tmp.record = "有货5吨，求:" + string("前四后十") + "3.4米";//keyword.carLength + keyword.carType + "。";
		tmp.tel = "联系电话:13866666666";
		inf.push_back(tmp);
	}
#else
	// 调用
	ns2__getSearchGoodsInfNew inData;
	std::string id(userInf.id);
	inData.uid = &id;
	inData.record = input.record;
	inData.curpage = input.curpage;

	std::string UTF8input;
	MultiByteToUTF8(sKeyword, UTF8input);
	inData.input = &UTF8input;

	ns2__getSearchGoodsInfNewResponse outData;

	if ( soap_call___ns1__getSearchGoodsInfNew(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
		inf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
			string outTmp("");	
			vector<string> tokens;
			TabNewInfRecord tmp;
			UTF8ToMultiByte(*iter, outTmp);            
			tokenize(outTmp, tokens, "|");
#ifdef _NEWCODE_
			if (tokens.at(0) == "TRUE" && tokens.size() >= 14) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);
				tmp.startPlace = tokens.at(4) + tokens.at(5);
				tmp.endPlace = tokens.at(6) + tokens.at(7);
				tmp.record = tokens.at(11) + "(" + tokens.at(12) + ")。";
				tmp.tel = " ";
				if (tokens.at(8) != "NULL") {
					tmp.tel +=  tokens.at(8);
					tmp.tel += " ";
				} else {
					if (tokens.at(9) != "NULL") {
						tmp.tel +=  tokens.at(9);
						tmp.tel += " ";
					}
				}
				tmp.tel += tokens.at(10);
				tmp.pubUID = tokens.at(13);
				inf.push_back(tmp);                
			}
#else
			if (tokens.at(0) == "TRUE" && tokens.size() >= 16) 
			{
				FillNewGoodsInfo(tokens, tmp);
				inf.push_back(tmp);                
			}
#endif


			++iter;
		}	   
		destroySoap();
	} else {
		destroySoap();
		//std::cout << "fail" << std::endl;       
	}

#endif

	return 0;
}
    
// Get search cars result
int ServerIO::getSearchCarsInf(const InSearchCars& keyword, vector<TabNewInfRecord> &inf, inputParam& input)
{
#ifdef _OFF_LINE_
    inf.clear();

    for (int i=0; i<input.record; ++i) {
        TabNewInfRecord tmp;
        tmp.recordID = "296";
        tmp.startPlace = "浙江杭州";//keyword.startProvince + keyword.startCity;
        tmp.endPlace = "江苏常州";//keyword.endProvince + keyword.endCity;
        tmp.record = "有7米集装箱车1辆, 载重:2吨,求货:冻品。(重货)";
        tmp.tel = "联系电话:13600000000";
        inf.push_back(tmp);
    }
#else
   
	string sKeyword;
	FormatCarsSearchString(keyword, sKeyword);
	return getSearchCarsInf(sKeyword, inf, input);
#endif

    return 0;
}
int ServerIO::getSearchCarsInf(const string& sKeyword, vector<TabNewInfRecord> &inf, inputParam& input)
{
#ifdef _OFF_LINE_
    inf.clear();

    for (int i=0; i<input.record; ++i) {
        TabNewInfRecord tmp;
        tmp.recordID = "296";
		tmp.startPlace = "浙江杭州";//keyword.startProvince + keyword.startCity;
		tmp.endPlace = "江苏常州";//keyword.endProvince + keyword.endCity;
        tmp.record = "有7米集装箱车1辆, 载重:2吨,求货:冻品。(重货)";
        tmp.tel = "联系电话:13600000000";
        inf.push_back(tmp);
    }
#else
    // 调用
    ns2__getSearchCarsInfNew inData;
    std::string id(userInf.id);
    inData.uid = &id;
    inData.record = input.record;
    inData.curpage = input.curpage;
    std::string UTF8input;
    MultiByteToUTF8(sKeyword, UTF8input);
    inData.input = &UTF8input;

    ns2__getSearchCarsInfNewResponse outData;
   
    if ( soap_call___ns1__getSearchCarsInfNew(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        inf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
            string outTmp("");	
            vector<string> tokens;
            TabNewInfRecord tmp;
			UTF8ToMultiByte(*iter, outTmp);            
            tokenize(outTmp, tokens, "|");
#ifdef _NEWCODE_
			if (tokens.at(0) == "TRUE" && tokens.size() >= 14) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);
				tmp.startPlace = tokens.at(4) + tokens.at(5);
				tmp.endPlace = tokens.at(6) + tokens.at(7);
				tmp.record = tokens.at(11) + "(" + tokens.at(12) + ")。";
				tmp.tel = " ";
				if (tokens.at(8) != "NULL") {
					tmp.tel +=  tokens.at(8);
					tmp.tel += " ";
				} else {
					if (tokens.at(9) != "NULL") {
						tmp.tel +=  tokens.at(9);
						tmp.tel += " ";
					}
				}
				tmp.tel += tokens.at(10);
				tmp.pubUID = tokens.at(13);
				inf.push_back(tmp);                
			}
#else
			if (tokens.at(0) == "TRUE" && tokens.size() >= 22) 
			{
				FillNewCarsInfo(tokens,tmp);
				inf.push_back(tmp);                
			}
#endif


			++iter;
		}	   
	   destroySoap();
   } else {
	   destroySoap();
	   //std::cout << "fail" << std::endl;       
   }

#endif

    return 0;
}

int ServerIO::getSearchGoodsAndCarsInfo(const string& sSearchKeyword, vector<TabNewInfRecord> &inf, inputParam& input)
{
#ifdef _OFF_LINE_
	inf.clear();

	for (int i=0; i<input.record; ++i) {
		TabNewInfRecord tmp;
		tmp.recordID = "296";
		tmp.startPlace = "浙江杭州";//keyword.startProvince + keyword.startCity;
		tmp.endPlace = "江苏常州";//keyword.endProvince + keyword.endCity;
		tmp.record = "有7米集装箱车1辆, 载重:2吨,求货:冻品。(重货)";
		tmp.tel = "联系电话:13600000000";
		inf.push_back(tmp);
	}
#else
	// 调用
	ns2__getGoodsAndCarsInfNew inData;
	std::string id(userInf.id);
	inData.uid = &id;
	inData.record = input.record;
	inData.curpage = input.curpage;
	std::string UTF8input;
	MultiByteToUTF8(sSearchKeyword, UTF8input);
	inData.input = &UTF8input;

	ns2__getGoodsAndCarsInfNewResponse outData;

	if ( soap_call___ns1__getGoodsAndCarsInfNew(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
		inf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
			string outTmp("");	
			vector<string> tokens;
			TabNewInfRecord tmp;
			UTF8ToMultiByte(*iter, outTmp);            
			tokenize(outTmp, tokens, "|");
#ifdef _NEWCODE_
			if (tokens.at(0) == "TRUE" && tokens.size() >= 14) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);
				tmp.startPlace = tokens.at(4) + tokens.at(5);
				tmp.endPlace = tokens.at(6) + tokens.at(7);
				tmp.record = tokens.at(11) + "(" + tokens.at(12) + ")。";
				tmp.tel = " ";
				if (tokens.at(8) != "NULL") {
					tmp.tel +=  tokens.at(8);
					tmp.tel += " ";
				} else {
					if (tokens.at(9) != "NULL") {
						tmp.tel +=  tokens.at(9);
						tmp.tel += " ";
					}
				}
				tmp.tel += tokens.at(10);
				tmp.pubUID = tokens.at(13);
				inf.push_back(tmp);                
			}
#else
			if (tokens.at(0) == "TRUE") 
			{
				if( tokens.at(tokens.size()-1) == "0")
				{
					FillNewGoodsInfo(tokens, tmp);
				}
				else
				{
					FillNewCarsInfo(tokens, tmp);
				}
				inf.push_back(tmp);                
			}
#endif

			++iter;
		}	   
		destroySoap();
	} else {
		destroySoap();
		//std::cout << "fail" << std::endl;       
	}

#endif

	return 0;
}
    
// Get search special line result
int ServerIO::getSearchSpecialLineInf(const InSearchSpecail& keyword, vector<TabSpecialLineRecord> &inf, inputParam& input)
{
#ifdef _OFF_LINE_
    inf.clear();

    for (int i=0; i<input.record; ++i) {
        TabSpecialLineRecord tmp;
        tmp.recordID = "296";
        tmp.startPlace = keyword.startProvince + keyword.startCity;
        tmp.endPlace = keyword.endProvince + keyword.endCity;
        tmp.weightPrice = "180元/吨";
        tmp.lightPrice = "120元/方";
        tmp.schedules = "每隔2天一班(单程)";
        tmp.needTime = "途中时间: 1天";
        tmp.record = "联系人：赵先生。";
        tmp.tel = "电话：0571-87703986 15267147987";
        inf.push_back(tmp);
    } 
#else
    // 调用
    ns2__getSearchSpecialLineInf inData;
    std::string id(userInf.id);
    inData.uid = &id;
    inData.record = input.record;
    inData.curpage = input.curpage;
    string buf = keyword.startProvince + "|" + keyword.startCity + "|" + keyword.startCounty
        + "|" + keyword.endProvince + "|" + keyword.endCity + "|" + keyword.endCounty;
    std::string UTF8input;
    MultiByteToUTF8(buf, UTF8input);
    inData.input = &UTF8input;

    ns2__getSearchSpecialLineInfResponse outData;
   
    if ( soap_call___ns1__getSearchSpecialLineInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        inf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
            string outTmp("");	
            vector<string> tokens;
            TabSpecialLineRecord tmp;
			UTF8ToMultiByte(*iter, outTmp);            
            tokenize(outTmp, tokens, "|");
            if (tokens.at(0) == "TRUE" && tokens.size() >= 16) {
                tmp.totalNum = tokens.at(1);
                tmp.returnNum = tokens.at(2);
                tmp.recordID = tokens.at(3);
                tmp.startPlace = tokens.at(4) + tokens.at(5);
                tmp.endPlace = tokens.at(6) + tokens.at(7);
                tmp.weightPrice = tokens.at(8);
                tmp.lightPrice = tokens.at(9);
                tmp.schedules = tokens.at(10);
                tmp.needTime = tokens.at(11);
                tmp.record = "(" + tokens.at(14) + ")";

				tmp.tel = " 联系方式：";
				if (tokens.at(12) != "NULL") {
					tmp.tel +=  tmp.pubName = tokens.at(12);
					tmp.tel += " ";
				}
				if (tokens.at(13) != "NULL")
				{
					tmp.tel += tokens.at(13);
				}

                tmp.pubUID = tokens.at(15);

				if( tokens.size() == 22)
				{
					tmp.startAddr = tokens.at(16);
					tmp.startContact = tokens.at(17);
					tmp.startPhone = tokens.at(18);
					tmp.destAddr = tokens.at(19);
					tmp.destContact = tokens.at(20);
					tmp.destPhone = tokens.at(21);
				}
                inf.push_back(tmp);                
            }

			++iter;
		}	   
	   destroySoap();
   } else {
	   destroySoap();
	   //std::cout << "fail" << std::endl;       
   }

#endif

    return 0;
}

// Get search bulk goods result
int ServerIO::getSearchBulkGoodsInf(const InSearchBulkGoods& keyword, vector<TabNewInfRecord> &inf, inputParam& input)
{
#ifdef _OFF_LINE_
	inf.clear();
	for (int i=0; i<input.record; ++i) {
		TabNewInfRecord tmp;
		tmp.startPlace = keyword.startProvince + keyword.startCity;
		tmp.endPlace = keyword.endProvince + keyword.endCity;
		tmp.record = "有货5吨，求10米长车。";
		tmp.tel = "联系电话:13866666666";
		inf.push_back(tmp);
	}
#else
	// 调用
	ns2__getSearchBulkGoodsInf inData;
	std::string id(userInf.id);
	inData.uid = &id;
	inData.record = input.record;
	inData.curpage = input.curpage;
	string buf = keyword.startProvince + "|" + keyword.startCity + "|" + keyword.startCounty
		+ "|" + keyword.endProvince + "|" + keyword.endCity + "|" + keyword.endCounty;
	std::string UTF8input;
	MultiByteToUTF8(buf, UTF8input);
	inData.input = &UTF8input;

	ns2__getSearchBulkGoodsInfResponse outData;

	if ( soap_call___ns1__getSearchBulkGoodsInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
		inf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
			string outTmp("");	
			vector<string> tokens;
			TabNewInfRecord tmp;
			UTF8ToMultiByte(*iter, outTmp);            
			tokenize(outTmp, tokens, "|");

#ifdef _NEWCODE_
			if (tokens.at(0) == "TRUE" && tokens.size() >= 14) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);
				tmp.startPlace = tokens.at(4) + tokens.at(5);
				tmp.endPlace = tokens.at(6) + tokens.at(7);
				tmp.record = tokens.at(11) + "(" + tokens.at(12) + ")。";
				tmp.tel = " ";
				if (tokens.at(8) != "NULL") {
					tmp.tel +=  tokens.at(8);
					tmp.tel += " ";
				} else {
					if (tokens.at(9) != "NULL") {
						tmp.tel +=  tokens.at(9);
						tmp.tel += " ";
					}
				}
				tmp.tel += tokens.at(10);
				tmp.pubUID = tokens.at(13);
				inf.push_back(tmp);                
			}
#else
			if (tokens.at(0) == "TRUE" && tokens.size() >= 16) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);
				tmp.startPlace = tokens.at(4) + tokens.at(5);
				if (tokens.at(6) != "NULL")
				{
					tmp.startPlace +=  tokens.at(6);
				}

				tmp.endPlace = tokens.at(7) + tokens.at(8);

				if (tokens.at(9) != "NULL")
				{
					tmp.endPlace +=  tokens.at(9);
				}

				tmp.record = tokens.at(13) + "(" + tokens.at(14) + ")。";
				tmp.tel = " ";
				if (tokens.at(10) != "NULL") {
					tmp.tel +=  tokens.at(10);
					tmp.tel += " ";
				} else {
					if (tokens.at(11) != "NULL") {
						tmp.tel +=  tokens.at(11);
						tmp.tel += " ";
					}
				}
				//tmp.tel += tokens.at(12);
				if (tokens.at(12) != "NULL")
				{
					tmp.tel += tokens.at(12);
				}
				tmp.pubUID = tokens.at(15);
				inf.push_back(tmp);                
			}
#endif


			++iter;
		}	   
		destroySoap();
	} else {
		destroySoap();
		//std::cout << "fail" << std::endl;       
	}

#endif

	return 0;
}
    
// Get click search goods information
int ServerIO::getClickSearchGoodsInf(const InClickSearch& keyword, vector<TabNewInfRecord> &inf, inputParam& input)
{
#ifdef _OFF_LINE_
    inf.clear();

   for (int i=0; i<input.record; ++i) {
        TabNewInfRecord tmp;
        tmp.recordID = "296";
        tmp.startPlace = keyword.province + keyword.city;
        tmp.endPlace = keyword.province + keyword.city;
        tmp.record = "有货5吨，求10米长车。";
        tmp.tel = "联系电话:13866666666";
        inf.push_back(tmp);
    }
#else
    // 调用
    ns2__getClickSearchGoodsInf inData;
    std::string id(userInf.id);
    inData.uid = &id;
    inData.record = input.record;
    inData.curpage = input.curpage;
    string buf = keyword.province + "|" + keyword.city;
    std::string UTF8input;
    MultiByteToUTF8(buf, UTF8input);
    inData.input = &UTF8input;

    ns2__getClickSearchGoodsInfResponse outData;
   
    if ( soap_call___ns1__getClickSearchGoodsInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        inf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
            string outTmp("");	
            vector<string> tokens;
            TabNewInfRecord tmp;
			UTF8ToMultiByte(*iter, outTmp);            
            tokenize(outTmp, tokens, "|");
#ifdef _NEWCODE_
			if (tokens.at(0) == "TRUE" && tokens.size() >= 14) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);
				tmp.startPlace = tokens.at(4) + tokens.at(5);
				tmp.endPlace = tokens.at(6) + tokens.at(7);
				tmp.record = tokens.at(11) + "(" + tokens.at(12) + ")。";
				tmp.tel = " ";
				if (tokens.at(8) != "NULL") {
					tmp.tel +=  tokens.at(8);
					tmp.tel += " ";
				} else {
					if (tokens.at(9) != "NULL") {
						tmp.tel +=  tokens.at(9);
						tmp.tel += " ";
					}
				}
				tmp.tel += tokens.at(10);
				tmp.pubUID = tokens.at(13);
				inf.push_back(tmp);                
			}
#else
			if (tokens.at(0) == "TRUE" && tokens.size() >= 16) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);
				tmp.startPlace = tokens.at(4) + tokens.at(5);
				if (tokens.at(6) != "NULL")
				{
					tmp.startPlace +=  tokens.at(6);
				}

				tmp.endPlace = tokens.at(7) + tokens.at(8);

				if (tokens.at(9) != "NULL")
				{
					tmp.endPlace +=  tokens.at(9);
				}

				tmp.record = tokens.at(13) + "(" + tokens.at(14) + ")。";
				tmp.tel = " ";
				if (tokens.at(10) != "NULL") {
					tmp.tel +=  tokens.at(10);
					tmp.tel += " ";
				} else {
					if (tokens.at(11) != "NULL") {
						tmp.tel +=  tokens.at(11);
						tmp.tel += " ";
					}
				}
				//tmp.tel += tokens.at(12);
				if (tokens.at(12) != "NULL")
				{
					tmp.tel += tokens.at(12);
				}
				tmp.pubUID = tokens.at(15);
				inf.push_back(tmp);                
			}
#endif


			++iter;
		}	   
	   destroySoap();
   } else {
	   destroySoap();
	   //std::cout << "fail" << std::endl;       
   }

#endif

    return 0;
}
    
// Get click search cars information
int ServerIO::getClickSearchCarsInf(const InClickSearch& keyword, vector<TabNewInfRecord> &inf, inputParam& input)
{
#ifdef _OFF_LINE_
	inf.clear();

	for (int i=0; i<input.record; ++i) {
		TabNewInfRecord tmp;
		tmp.recordID = "296";
		tmp.startPlace = keyword.province + keyword.city;
		tmp.endPlace = keyword.province + keyword.city;
		tmp.record = "有7米集装箱车1辆, 载重:2吨,求货:冻品。(重货) (07-30 10:55) 。";
		tmp.tel = " 济南泺源货运公司 15267147987 010-3730987";
		inf.push_back(tmp);
	}
#else
	// 调用
	ns2__getClickSearchCarsInf inData;
	std::string id(userInf.id);
	inData.uid = &id;
	inData.record = input.record;
	inData.curpage = input.curpage;
	string buf = keyword.province + "|" + keyword.city;
	std::string UTF8input;
	MultiByteToUTF8(buf, UTF8input);
	inData.input = &UTF8input;

	ns2__getClickSearchCarsInfResponse outData;

	if ( soap_call___ns1__getClickSearchCarsInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
		inf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
			string outTmp("");	
			vector<string> tokens;
			TabNewInfRecord tmp;
			UTF8ToMultiByte(*iter, outTmp);            
			tokenize(outTmp, tokens, "|");

#ifdef _NEWCODE_
			if (tokens.at(0) == "TRUE" && tokens.size() >= 14) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);
				tmp.startPlace = tokens.at(4) + tokens.at(5);
				tmp.endPlace = tokens.at(6) + tokens.at(7);
				tmp.record = tokens.at(11) + "(" + tokens.at(12) + ")。";
				tmp.tel = " ";
				if (tokens.at(8) != "NULL") {
					tmp.tel +=  tokens.at(8);
					tmp.tel += " ";
				} else {
					if (tokens.at(9) != "NULL") {
						tmp.tel +=  tokens.at(9);
						tmp.tel += " ";
					}
				}
				tmp.tel += tokens.at(10);
				tmp.pubUID = tokens.at(13);
				inf.push_back(tmp);                
			}
#else
			if (tokens.at(0) == "TRUE" && tokens.size() >= 22) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);

				tmp.startPlace = tokens.at(4) + tokens.at(5);

				if (tokens.at(6) != "NULL")
				{
					tmp.startPlace +=  tokens.at(6);
				}

				tmp.endPlace = tokens.at(7) + tokens.at(8);

				if (tokens.at(9) != "NULL")
				{
					tmp.endPlace +=  tokens.at(9);
				}

				if (tokens.at(10) != "NULL")
				{
					tmp.endPlace += " ";
					tmp.endPlace += tokens.at(10);
					tmp.endPlace += tokens.at(11);
					if (tokens.at(12) != "NULL")
					{
						tmp.endPlace +=  tokens.at(12);
					}
				}

				if (tokens.at(13) != "NULL")
				{
					tmp.endPlace += " ";
					tmp.endPlace += tokens.at(13);
					tmp.endPlace += tokens.at(14);
					if (tokens.at(15) != "NULL")
					{
						tmp.endPlace +=  tokens.at(15);
					}
				}

				tmp.record = tokens.at(19) + "(" + tokens.at(20) + ")。";
				tmp.tel = " ";
				if (tokens.at(16) != "NULL") {
					tmp.tel +=  tokens.at(16);
					tmp.tel += " ";
				} else {
					if (tokens.at(17) != "NULL") {
						tmp.tel +=  tokens.at(17);
						tmp.tel += " ";
					}
				}
				//tmp.tel += tokens.at(18);
				if (tokens.at(18) != "NULL")
				{
					tmp.tel += tokens.at(18);
				}
				tmp.pubUID = tokens.at(21);
				inf.push_back(tmp);                
			}
#endif


			++iter;
		}	   
		destroySoap();
	} else {
		destroySoap();
		//std::cout << "fail" << std::endl;       
	}

#endif

	return 0;
}

// Get click search special line information
int ServerIO::getClickSearchSpecialLineInf(const InClickSearch& keyword, vector<TabSpecialLineRecord> &inf, inputParam& input)
{
#ifdef _OFF_LINE_
	inf.clear();

	for (int i=0; i<input.record; ++i) {
		TabSpecialLineRecord tmp;
		tmp.recordID = "296";
		tmp.startPlace = keyword.province + keyword.city;
		tmp.endPlace = keyword.province + keyword.city;
		tmp.weightPrice = "600元/吨";
		tmp.lightPrice = "120元/方";
		tmp.schedules = "每隔2天一班(单程)";
		tmp.needTime = "途中时间: 1天";
		tmp.record = "联系人：赵先生。";
		tmp.tel = "电话：0571-87703986 15267147987";
		inf.push_back(tmp);
	}
#else
	// 调用
	ns2__getClickSearchSpecialLineInf inData;
	std::string id(userInf.id);
	inData.uid = &id;
	inData.record = input.record;
	inData.curpage = input.curpage;
	string buf = keyword.province + "|" + keyword.city;
	std::string UTF8input;
	MultiByteToUTF8(buf, UTF8input);
	inData.input = &UTF8input;

	ns2__getClickSearchSpecialLineInfResponse outData;

	if ( soap_call___ns1__getClickSearchSpecialLineInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
		inf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
			string outTmp("");	
			vector<string> tokens;
			TabSpecialLineRecord tmp;
			UTF8ToMultiByte(*iter, outTmp);            
			tokenize(outTmp, tokens, "|");
			if (tokens.at(0) == "TRUE" && tokens.size() >= 16) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);
				tmp.startPlace = tokens.at(4) + tokens.at(5);
				tmp.endPlace = tokens.at(6) + tokens.at(7);
				tmp.weightPrice = tokens.at(8);
				tmp.lightPrice = tokens.at(9);
				tmp.schedules = tokens.at(10);
				tmp.needTime = tokens.at(11);
				tmp.record = "(" + tokens.at(14) + ")";

				tmp.tel = " 联系方式：";
				if (tokens.at(12) != "NULL") {
					tmp.tel +=  tokens.at(12);
					tmp.tel += " ";
				}
				tmp.tel += tokens.at(13);
				tmp.pubUID = tokens.at(15);
				inf.push_back(tmp);                
			}

			++iter;
		}	   
		destroySoap();
	} else {
		destroySoap();
		//std::cout << "fail" << std::endl;       
	}

#endif

	return 0;
}

// Get click search bulkGoods information
int ServerIO::getClickSearchBulkGoodsInf(const InClickSearch& keyword, vector<TabNewInfRecord> &inf, inputParam& input)
{
#ifdef _OFF_LINE_
    inf.clear();

    for (int i=0; i<input.record; ++i) {
        TabNewInfRecord tmp;
        tmp.recordID = "296";
        tmp.startPlace = keyword.province + keyword.city;
        tmp.endPlace = keyword.province + keyword.city;
        tmp.record = "有货:危险品,需要后八轮车 (07-26 12:00) 。";
        tmp.tel = "上海宇佳物流，联系电话:15265965698 0571-9999999";
        inf.push_back(tmp);
    }
#else
    // 调用
    ns2__getClickSearchBulkGoodsInf inData;
    std::string id(userInf.id);
    inData.uid = &id;
    inData.record = input.record;
    inData.curpage = input.curpage;
    string buf = keyword.province + "|" + keyword.city;
    std::string UTF8input;
    MultiByteToUTF8(buf, UTF8input);
    inData.input = &UTF8input;

    ns2__getClickSearchBulkGoodsInfResponse outData;
   
    if ( soap_call___ns1__getClickSearchBulkGoodsInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        inf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
            string outTmp("");	
            vector<string> tokens;
            TabNewInfRecord tmp;
			UTF8ToMultiByte(*iter, outTmp);            
            tokenize(outTmp, tokens, "|");
#ifdef _NEWCODE_
			if (tokens.at(0) == "TRUE" && tokens.size() >= 14) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);
				tmp.startPlace = tokens.at(4) + tokens.at(5);
				tmp.endPlace = tokens.at(6) + tokens.at(7);
				tmp.record = tokens.at(11) + "(" + tokens.at(12) + ")。";
				tmp.tel = " ";
				if (tokens.at(8) != "NULL") {
					tmp.tel +=  tokens.at(8);
					tmp.tel += " ";
				} else {
					if (tokens.at(9) != "NULL") {
						tmp.tel +=  tokens.at(9);
						tmp.tel += " ";
					}
				}
				tmp.tel += tokens.at(10);
				tmp.pubUID = tokens.at(13);
				inf.push_back(tmp);                
			}
#else
			if (tokens.at(0) == "TRUE" && tokens.size() >= 16) 
			{
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);
				tmp.startPlace = tokens.at(4) + tokens.at(5);
				if (tokens.at(6) != "NULL")
				{
					tmp.startPlace +=  tokens.at(6);
				}

				tmp.endPlace = tokens.at(7) + tokens.at(8);

				if (tokens.at(9) != "NULL")
				{
					tmp.endPlace +=  tokens.at(9);
				}

				tmp.record = tokens.at(13) + "(" + tokens.at(14) + ")。";
				tmp.tel = " ";
				if (tokens.at(10) != "NULL") {
					tmp.tel +=  tokens.at(10);
					tmp.tel += " ";
				} else {
					if (tokens.at(11) != "NULL") {
						tmp.tel +=  tokens.at(11);
						tmp.tel += " ";
					}
				}
				//tmp.tel += tokens.at(12);
				if (tokens.at(12) != "NULL")
				{
					tmp.tel += tokens.at(12);
				}
				tmp.pubUID = tokens.at(15);
				inf.push_back(tmp);                
			}
#endif


			++iter;
		}	   
	   destroySoap();
   } else {
	   destroySoap();
	   //std::cout << "fail" << std::endl;       
   }

#endif
    return 0;
}
    
// Set pub goods information 
string ServerIO::setPubGoodsInf(const string& input)
{
#ifdef _OFF_LINE_

#else
    ns2__setPubGoodsInf inData;
    std::string id(userInf.id);
    std::string UTF8input;
    MultiByteToUTF8(input, UTF8input);
    inData.uid = &id;
    inData.input = &UTF8input;

    ns2__setPubGoodsInfResponse outData;
   
    if ( soap_call___ns1__setPubGoodsInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        string outTmp("");	
        vector<string> tokens;
        UTF8ToMultiByte(*(outData.return_), outTmp);
	    tokenize(outTmp, tokens, "|");
        if (tokens.size() >= 2 && tokens.at(0) == "FALSE") {
            return tokens.at(1);      
        }   
		destroySoap();
   } else {
	   destroySoap();
	   //std::cout << "fail" << std::endl;       
   }
#endif
    return "TRUE";
}
    
// Set pub bulk goods information
string ServerIO::setPubBulkGoodsInf(const string& input)
{
#ifdef _OFF_LINE_

#else
    ns2__setPubBulkGoodsInf inData;
    std::string id(userInf.id);
    std::string UTF8input;
    MultiByteToUTF8(input, UTF8input);
    inData.uid = &id;
    inData.input = &UTF8input;

    ns2__setPubBulkGoodsInfResponse outData;
   
    if ( soap_call___ns1__setPubBulkGoodsInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        string outTmp("");	
        vector<string> tokens;
        UTF8ToMultiByte(*(outData.return_), outTmp);
	    tokenize(outTmp, tokens, "|");
        if (tokens.size() >= 2 && tokens.at(0) == "FALSE") {
            return tokens.at(1);      
        }   
		destroySoap();
   } else {
	   destroySoap();
	   //std::cout << "fail" << std::endl;       
   }
#endif
    return "TRUE";
}
        
// Set pub cars information
string ServerIO::setPubCarsInf(const string& input)
{
#ifdef _OFF_LINE_

#else
    ns2__setPubCarsInf inData;
    std::string id(userInf.id);
    std::string UTF8input;
    MultiByteToUTF8(input, UTF8input);
    inData.uid = &id;
    inData.input = &UTF8input;

    ns2__setPubCarsInfResponse outData;
   
    if ( soap_call___ns1__setPubCarsInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        string outTmp("");	
        vector<string> tokens;
        UTF8ToMultiByte(*(outData.return_), outTmp);
	    tokenize(outTmp, tokens, "|");
        if (tokens.size() >= 2 && tokens.at(0) == "FALSE") {
            return tokens.at(1);      
        }  
		destroySoap();
   } else {
	   destroySoap();
	   //std::cout << "fail" << std::endl;       
   }
#endif
    return "TRUE";
}
    
// Set pub special line information
string ServerIO::setPubSpecialLineInf(const string& input)
{
#ifdef _OFF_LINE_

#else
    ns2__setPubSpecialLineInf inData;
    std::string id(userInf.id);
    std::string UTF8input;
    MultiByteToUTF8(input, UTF8input);
    inData.uid = &id;
    inData.input = &UTF8input;

    ns2__setPubSpecialLineInfResponse outData;
   
    if ( soap_call___ns1__setPubSpecialLineInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        string outTmp("");	
        vector<string> tokens;
        UTF8ToMultiByte(*(outData.return_), outTmp);
	    tokenize(outTmp, tokens, "|");
        if (tokens.size() >= 2 && tokens.at(0) == "FALSE") {
            return tokens.at(1);      
        }  
		destroySoap();
   } else {
	   destroySoap();
	   //std::cout << "fail" << std::endl;       
   }
#endif
    return "TRUE";
}
    
// Delete goods information
string ServerIO::delGoodsInf(string recordID)
{
#ifdef _OFF_LINE_
#else
    ns2__delGoodsInf inData;
    std::string id(userInf.id);
    inData.uid = &id;
    inData.recordID = &recordID;

    ns2__delGoodsInfResponse outData;
   
    if ( soap_call___ns1__delGoodsInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        string outTmp("");	
        vector<string> tokens;
        UTF8ToMultiByte(*(outData.return_), outTmp);
	    tokenize(outTmp, tokens, "|");
        if (tokens.at(0) == "FALSE" && tokens.size() >= 2) {
            return tokens.at(1);       
        }	
		destroySoap();
   } else {
	   destroySoap();
	   return "连接服务器失败，请检查网络连接。";       
   }
#endif
    return "TRUE";
}
    
// Delete bulk goods information
string ServerIO::delBulkGoodsInf(string recordID)
{
#ifdef _OFF_LINE_
#else
    ns2__delBulkGoodsInf inData;
    std::string id(userInf.id);
    inData.uid = &id;
    inData.recordID = &recordID;

    ns2__delBulkGoodsInfResponse outData;
   
    if ( soap_call___ns1__delBulkGoodsInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        string outTmp("");	
        vector<string> tokens;
        UTF8ToMultiByte(*(outData.return_), outTmp);
	    tokenize(outTmp, tokens, "|");
        if (tokens.at(0) == "FALSE" && tokens.size() >= 2) {
            return tokens.at(1);       
        }	 
		destroySoap();
   } else {
	   destroySoap();
	   return "连接服务器失败，请检查网络连接。";       
   }
#endif
    return "TRUE";
}
    
// Delete cars information
string ServerIO::delCarsInf(string recordID)
{
#ifdef _OFF_LINE_
#else
    ns2__delCarsInf inData;
    std::string id(userInf.id);
    inData.uid = &id;
    inData.recordID = &recordID;

    ns2__delCarsInfResponse outData;
   
    if ( soap_call___ns1__delCarsInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        string outTmp("");	
        vector<string> tokens;
        UTF8ToMultiByte(*(outData.return_), outTmp);
	    tokenize(outTmp, tokens, "|");
        if (tokens.at(0) == "FALSE" && tokens.size() >= 2) {
            return tokens.at(1);       
        }	
		destroySoap();
   } else {
	   destroySoap();
	   return "连接服务器失败，请检查网络连接。";       
   }
#endif
    return "TRUE";
}
    
// Delete special line information
string ServerIO::delSpecialLineInf(string recordID)
{
#ifdef _OFF_LINE_
#else
    ns2__delSpecialLineInf inData;
    std::string id(userInf.id);
    inData.uid = &id;
    inData.recordID = &recordID;

    ns2__delSpecialLineInfResponse outData;
   
    if ( soap_call___ns1__delSpecialLineInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        string outTmp("");	
        vector<string> tokens;
        UTF8ToMultiByte(*(outData.return_), outTmp);
	    tokenize(outTmp, tokens, "|");
        if (tokens.at(0) == "FALSE" && tokens.size() >= 2) {
            return tokens.at(1);       
        }	
		destroySoap();
   } else {
	   destroySoap();
	   return "连接服务器失败，请检查网络连接。";       
   }
#endif
    return "TRUE";
}
    
// delete favorite specail line
string ServerIO::delFavoriteSpecialLine(string recordID)
{
#ifdef _OFF_LINE_
#else
    ns2__delFavoriteSpecialLine inData;
    std::string id(userInf.id);
    inData.uid = &id;
    inData.recordID = &recordID;

    ns2__delFavoriteSpecialLineResponse outData;
   
    if ( soap_call___ns1__delFavoriteSpecialLine(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        string outTmp("");	
        vector<string> tokens;
        UTF8ToMultiByte(*(outData.return_), outTmp);
	    tokenize(outTmp, tokens, "|");
        if (tokens.at(0) == "FALSE" && tokens.size() >= 2) {
            return tokens.at(1);       
        }	
		destroySoap();
   } else {
	   destroySoap();
	   return "连接服务器失败，请检查网络连接。";       
   }
#endif
    return "TRUE";
}


string ServerIO::setGoodsStatus(const string& recordID, const string& sStatus)
{
#ifdef _OFF_LINE_
#else
	ns2__setGoodsStatus inData;
	std::string id(userInf.id);
	inData.uid = &id;
	inData.gid = const_cast<string*>(&recordID);

	std::string UTF8status;
	MultiByteToUTF8(sStatus, UTF8status);
	inData.status = const_cast<string*>(&UTF8status);

	ns2__setGoodsStatusResponse outData;

	if ( soap_call___ns1__setGoodsStatus(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
		string outTmp("");	
		vector<string> tokens;
		UTF8ToMultiByte(*(outData.return_), outTmp);
		tokenize(outTmp, tokens, "|");
		if (tokens.at(0) == "FALSE" && tokens.size() >= 2) {
			return tokens.at(1);       
		}	
		destroySoap();
	}
	else 
	{
		destroySoap();
		return "连接服务器失败，请检查网络连接。";       
	}
#endif
	return "TRUE";
}
string ServerIO::setCarsStatus(const string& recordID, const string& sStatus)
{
#ifdef _OFF_LINE_
#else
	ns2__setCarsStatus inData;
	std::string id(userInf.id);
	inData.uid = &id;
	inData.cid = const_cast<string*>(&recordID);

	std::string UTF8status;
	MultiByteToUTF8(sStatus, UTF8status);
	inData.status = const_cast<string*>(&UTF8status);
	
	ns2__setCarsStatusResponse outData;

	if ( soap_call___ns1__setCarsStatus(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
		string outTmp("");	
		vector<string> tokens;
		UTF8ToMultiByte(*(outData.return_), outTmp);
		tokenize(outTmp, tokens, "|");
		if (tokens.at(0) == "FALSE" && tokens.size() >= 2) {
			return tokens.at(1);       
		}	
		destroySoap();
	}
	else 
	{
		destroySoap();
		return "连接服务器失败，请检查网络连接。";       
	}
#endif
	return "TRUE";
}
    
// Send Phone Message
string ServerIO::sendPhoneMessage(string phone, string msg)
{
#ifdef _OFF_LINE_
#else
    ns2__sendPhoneMessage inData;
    std::string id(userInf.id);
    inData.uid = &id;
    inData.phone = &phone;
	std::string UTF8input;
	MultiByteToUTF8(msg, UTF8input);
    inData.msg = &UTF8input;

    ns2__sendPhoneMessageResponse outData;
   
    if ( soap_call___ns1__sendPhoneMessage(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        string outTmp("");	
        vector<string> tokens;
        UTF8ToMultiByte(*(outData.return_), outTmp);
	    tokenize(outTmp, tokens, "|");
        if (tokens.at(0) == "FALSE" && tokens.size() >= 2) {
            return tokens.at(1);       
        }	
		destroySoap();
   } else {
	   destroySoap();
	   return "连接服务器失败，请检查网络连接。";       
   }
#endif
    return "TRUE";
}
    
// 获取系统滚动广告信息
string ServerIO::getSystemScrollAd()
{
#ifdef _OFF_LINE_
    //sysMsg = "金秋10月欢乐大放送，充值满100元送100元。详情请咨询代理商。";
    return "FALSE";
#else
    // 调用
    ns2__getSystemScrollAd inData;
    std::string id(userInf.id);
    inData.uid = &id;
    std::string msgid(sysScrollAd.id);
    inData.msgid = &msgid;

    ns2__getSystemScrollAdResponse outData;
   
    if ( soap_call___ns1__getSystemScrollAd(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        string outTmp("");	
        vector<string> tokens;
        UTF8ToMultiByte(*(outData.return_), outTmp);
	    tokenize(outTmp, tokens, "|");
        if (tokens.at(0) == "TRUE" && tokens.size() >= 4) {
                sysScrollAd.id = tokens.at(1); // 消息ID
                sysScrollAd.inf = tokens.at(2); // 消息内容
                //sysMsg = sysMsg + "(" + tokens.at(3); + ")"; // 发布时间        
        } else {
            //return tokens.at(1);
            return "FALSE";
        }
	   destroySoap();
   } else {
	   destroySoap();
	   return "连接服务器失败，请检查网络连接。";       
   }

    //sysMsg = "金秋10月欢乐大放送，充值满100元送100元。详情请咨询代理商。";
#endif
    return "TRUE";
}
        
// 获取代理商弹出广告信息
string ServerIO::getAgentPopAd()
{
#ifdef _OFF_LINE_
    //agentMsg = "您的代理商电话：13600136000。";
    return "FALSE";
#else
    // 调用
    ns2__getAgentPopAd inData;
    std::string id(userInf.id);
    inData.uid = &id;
    std::string msgid(agPopAd.id);
    inData.msgid = &msgid;

    ns2__getAgentPopAdResponse outData;
   
    if ( soap_call___ns1__getAgentPopAd(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
        string outTmp("");	
        vector<string> tokens;
        UTF8ToMultiByte(*(outData.return_), outTmp);
	    tokenize(outTmp, tokens, "|");
        if (tokens.at(0) == "TRUE" && tokens.size() >= 4) {
                agPopAd.id = tokens.at(1); // 消息ID
                agPopAd.inf = tokens.at(2); // 消息内容
                //sysMsg = sysMsg + "(" + tokens.at(3); + ")"; // 发布时间        
        } else {
            //return tokens.at(1);
            return "FALSE";
        }
	   destroySoap();
   } else {
	   destroySoap();
	   return "连接服务器失败，请检查网络连接。";       
   }
#endif
    return "TRUE";
}
    
// 获取代理商滚动广告信息
string ServerIO::getAgentScrollAd()
{
#ifdef _OFF_LINE_
    //string str = "有7米集装箱车1辆, 载重:2吨,求货:冻品。(重货) 济南泺源货运公司 15267147987 010-3730987";
    //msg.push_back(str);
    
    //str = "有货:危险品,需要后八轮车。上海宇佳物流，联系电话:15265965698 0571-9999999";
    //msg.push_back(str);
    
    //str = "有货5吨，求10米长车。联系电话:13866666666";
    //msg.push_back(str);

    return "FALSE";
#else
    // 调用
    ns2__getAgentScrollAd inData;
    std::string id(userInf.id);
    inData.uid = &id;
    std::string msgid(agScrollAd.front().id);
    inData.msgid = &msgid;

    ns2__getAgentScrollAdResponse outData;
   
    if ( soap_call___ns1__getAgentScrollAd(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
		vector<string>::iterator iter = outData.return_.begin();
        string outTmp("");	
        vector<string> tokens;
		UTF8ToMultiByte(*iter, outTmp);            
        tokenize(outTmp, tokens, "|");
        if (tokens.at(0) != "TRUE")    
            return "FALSE";
        agScrollAd.clear();
		while (iter != outData.return_.end()) {
            outTmp.clear();
            tokens.clear();
            AdMsg tmp;
			UTF8ToMultiByte(*iter, outTmp);            
            tokenize(outTmp, tokens, "|");

            tmp.id = tokens.at(1);
            tmp.inf = tokens.at(2);
            agScrollAd.push_back(tmp);

			++iter;
		}	   
	   destroySoap();
   } else {
	   destroySoap();
       return "连接服务器失败，请检查网络连接。";       
   }

#endif
    return "TRUE";
}
//服务站信息
string ServerIO::getServicestationInf(const InSearchService& keyword, vector<ServiceInfo> &inf, inputParamFwz& input)
{
	
	// 调用
	ns2__getClickServiceStationInf inData;
	std::string id(userInf.id);
	inData.uid = &id;
	inData.record = input.record;
	inData.curpage = input.curpage;


	string buf = keyword.Province + "|" + keyword.City ;

	//string buf = "浙江|杭州";
	std::string UTF8input;
	MultiByteToUTF8(buf, UTF8input);
	inData.input = &UTF8input;

	ns2__getClickServiceStationInfResponse outData;

	if ( soap_call___ns1__getClickServiceStationInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
		inf.clear();
		vector<string>::iterator iter = outData.return_.begin();
		while (iter != outData.return_.end()) {
			string outTmp("");	
			vector<string> tokens;
			ServiceInfo tmp;
			UTF8ToMultiByte(*iter, outTmp);            
			tokenize(outTmp, tokens, "|");
			if (tokens.at(0) == "TRUE" && tokens.size() >= 9) {
				tmp.totalNum = tokens.at(1);
				tmp.returnNum = tokens.at(2);
				tmp.recordID = tokens.at(3);
				tmp.serviceName = tokens.at(4);
				tmp.serviceNo = tokens.at(5);
				tmp.serviceAddr = tokens.at(6);
				tmp.servicePerson = tokens.at(7);
				tmp.tel = tokens.at(8);
				//tmp.serviceID = tokens.at(9);
				/*tmp.serviceAddr = tokens.at(11) + "(" + tokens.at(12) + ")。";
				tmp.tel = " ";
				if (tokens.at(8) != "NULL") {
					tmp.tel +=  tokens.at(8);
					tmp.tel += " ";
				} else {
					if (tokens.at(9) != "NULL") {
						tmp.tel +=  tokens.at(9);
						tmp.tel += " ";
					}
				}
				tmp.tel += tokens.at(10);
				tmp.pubUID = tokens.at(13);*/
				inf.push_back(tmp);                
			}

			++iter;
		}	   
		destroySoap();
	} else {
		destroySoap();
		//std::cout << "fail" << std::endl;       
	}


	 return "TRUE";
}
string ServerIO::setServicesMsg(string recordID,string sendMsg)
{
#ifdef _OFF_LINE_
#else
	ns2__setServiceStationInf inData;
	std::string id(userInf.id);
	inData.uid = &id;
	std::string UTF8input;
	MultiByteToUTF8(sendMsg, UTF8input);



	inData.sid = &recordID;
	inData.msg = &UTF8input;

	ns2__setServiceStationInfResponse outData;
	//int f  =soap_call___ns1__setServiceStationInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData);
	if ( soap_call___ns1__setServiceStationInf(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {
		string outTmp("");	
		vector<string> tokens;
		UTF8ToMultiByte(*(outData.return_), outTmp);
		tokenize(outTmp, tokens, "|");
		if (tokens.at(0) == "FALSE" && tokens.size() >= 2) {
			return tokens.at(1);       
		}	
		destroySoap();
	} else {
		destroySoap();
		return "连接服务器失败，请检查网络连接。";       
	}
#endif
	return "TRUE";
}
// UTF8编码字符串转换为多字节编码字符串
int ServerIO::UTF8ToMultiByte(const std::string& in, std::string& out)
{
	wstring wstr(in.length(), _T(' '));
	size_t len = ::MultiByteToWideChar(CP_UTF8, 0, in.c_str(), in.length(), &wstr[0], wstr.length());
	wstr.resize(len);

	DWORD dwNum = WideCharToMultiByte(CP_OEMCP,NULL,wstr.c_str(),-1,NULL,0,NULL,FALSE);
	char* psText = new char[dwNum];
	if(!psText)	{
		delete[] psText;
		return -1;
	}
	WideCharToMultiByte (CP_OEMCP, NULL, wstr.c_str(), -1, psText, dwNum, NULL, FALSE);
	out = psText;
	delete []psText;

	return 0;
}
    
// 宽字符转UTF8
string ServerIO::EncodeUtf8(wstring in)
{
	string s(in.length()*3+1,' ');
	size_t len = ::WideCharToMultiByte(CP_UTF8, 0, in.c_str(), in.length(),	&s[0], s.length(),
		NULL, NULL);
	s.resize(len);
	return s;
}
    
// 多字节编码字符串转换为UTF8编码字符串
int ServerIO::MultiByteToUTF8(const std::string& in, std::string& out)
{
	int nSize = ::MultiByteToWideChar(CP_ACP, 0, in.c_str(), -1, 0, 0);
	if(nSize <= 0) {
		return -1;
	}
	WCHAR *pwszDst = new WCHAR[nSize+1];
	if( NULL == pwszDst) {
		return -1;
	}
	::MultiByteToWideChar(CP_ACP, 0, in.c_str(), -1, pwszDst, nSize);
	pwszDst[nSize] = 0;
	if( pwszDst[0] == 0xFEFF) {// skip Oxfeff
		for(int i = 0; i < nSize; i ++) 
		pwszDst[i] = pwszDst[i+1];
	}
	
	wstring wStr(pwszDst);
	delete[] pwszDst;

	string tmpStr(wStr.length()*3+1, ' ');
	size_t len = ::WideCharToMultiByte(CP_UTF8, 0, wStr.c_str(), wStr.length(),	
		&tmpStr[0], tmpStr.length(), NULL, NULL);
	tmpStr.resize(len);
	out = tmpStr;

    return 0;
}
    
// 通过界定符串拆分字符串
int ServerIO::tokenize(const std::string& str, 
                       std::vector<std::string>& tokens, 
                       const std::string& delimiters)
{
    //skip delimiters at beginning
    std::string::size_type lastPos = str.find_first_not_of(delimiters,0);
    //find first "non-delimiter".
    std::string::size_type pos = str.find_first_of(delimiters,lastPos);

    while(std::string::npos != pos || std::string::npos != lastPos)
    {
        //found a token, add it to the vector
        tokens.push_back(str.substr(lastPos,pos-lastPos));
        //skip delimiters. Note the "not_of"
        lastPos=str.find_first_not_of(delimiters,pos);
        //find next "non-delimiter"
        pos=str.find_first_of(delimiters,lastPos);
    }
    return 0;
}
    
// 初始化soap
int ServerIO::initSoap() {
    soap_init(&mySoap); // 初始化运行环境（只执行一次）
	soap_set_mode(&mySoap, SOAP_C_UTFSTRING);
    return 0;
}
    
// 卸载soap
int ServerIO::destroySoap() {
	//SuspendThread(hThread);
    //soap_print_fault(&mySoap, stderr); // 在stderr中显示错误信息
	try
	{
		soap_destroy(&mySoap); // 删除类实例（仅用于C++中）
		soap_end(&mySoap); // 清除运行环境变量
		//Sleep(1000);
		//soap_done(&mySoap); // 卸载运行环境变量
	}
	catch (...)
	{
	}
    return 0;
}

/* ==============================================
*
*================================================= */
string ServerIO::check_charge_user (string login_name)
{
	string retval = "";

#ifdef _OFF_LINE_
#else
	ns2__checkChargeUser  inData;
	inData.loginname = &login_name;
	
	::ns2__checkChargeUserResponse outData;

	if ( soap_call___ns1__checkChargeUser(&mySoap, svrURL.c_str(), NULL, &inData, &outData)== SOAP_OK) {

		string outTmp("");	
		vector<string> tokens;

        //编码转换
		UTF8ToMultiByte(*(outData.return_), outTmp);

        //返回信息分段
		tokenize(outTmp, tokens, "|");
		
		//执行失败
		if (tokens.at(0) == "FALSE" && tokens.size() >= 2) {
			retval = "执行失败";
		} else {//执行成功
			retval = tokens.at(1);
		}

		destroySoap();
	} else {
		destroySoap();
		retval =  "连接服务器失败，请检查网络连接。";       
	}
#endif
	return retval;
}


void ServerIO::FillNewCarsInfo(const vector<string>& tokens, TabNewInfRecord& record)
{
	if (tokens.at(0) == "TRUE" && tokens.size() >= 22)
	{
		record.totalNum = tokens.at(1);
		record.returnNum = tokens.at(2);
		record.recordID = tokens.at(3);

		record.startPlace = tokens.at(4) + tokens.at(5);

		if (tokens.at(6) != "NULL")
		{
			record.startPlace +=  tokens.at(6);
		}

		record.endPlace = tokens.at(7) + tokens.at(8);

		if (tokens.at(9) != "NULL")
		{
			record.endPlace +=  tokens.at(9);
		}

		if (tokens.at(10) != "NULL")
		{
			record.endPlace += " ";
			record.endPlace += tokens.at(10);
			record.endPlace += tokens.at(11);
			if (tokens.at(12) != "NULL")
			{
				record.endPlace +=  tokens.at(12);
			}
		}

		if (tokens.at(13) != "NULL")
		{
			record.endPlace += " ";
			record.endPlace += tokens.at(13);
			record.endPlace += tokens.at(14);
			if (tokens.at(15) != "NULL")
			{
				record.endPlace +=  tokens.at(15);
			}
		}

		record.record = tokens.at(19) + "(" + (record.pubTime = tokens.at(20)) + ")。";
		record.tel = " ";
		if (tokens.at(16) != "NULL") {
			record.tel +=  record.pubName = tokens.at(16);
			record.tel += " ";
		} else {
			if (tokens.at(17) != "NULL") {
				record.tel +=  record.pubName = tokens.at(17);
				record.tel += " ";
			}
		}
		if (tokens.at(18) != "NULL")
		{
			record.tel += tokens.at(18);
		}
		record.pubUID = tokens.at(21);

		if( tokens.size() >= 26)
		{
			//record.pubURL = tokens.at(22); not used
			record.pubAddress = tokens.at(23);
			record.dateTime = tokens.at(24);
			record.state = tokens.at(25);
		}
	}
}
void ServerIO::FillNewGoodsInfo(const vector<string>& tokens, TabNewInfRecord& record)
{
	if (tokens.at(0) == "TRUE" && tokens.size() >= 16)
	{
		record.totalNum = tokens.at(1);
		record.returnNum = tokens.at(2);
		record.recordID = tokens.at(3);
		record.startPlace = tokens.at(4) + tokens.at(5);
		if (tokens.at(6) != "NULL")
		{
			record.startPlace +=  tokens.at(6);
		}

		record.endPlace = tokens.at(7) + tokens.at(8);

		if (tokens.at(9) != "NULL")
		{
			record.endPlace +=  tokens.at(9);
		}

		record.record = tokens.at(13) + "(" + (record.pubTime = tokens.at(14)) + ")。";
		record.tel = " ";
		if (tokens.at(10) != "NULL") {
			record.tel +=  record.pubName = tokens.at(10);
			record.tel += " ";
		} else {
			if (tokens.at(11) != "NULL") {
				record.tel +=  record.pubName = tokens.at(11);
				record.tel += " ";
			}
		}
		//record.tel += tokens.at(12);
		if (tokens.at(12) != "NULL")
		{
			record.tel += tokens.at(12);
		}
		record.pubUID = tokens.at(15);

		if( tokens.size() >=  20 )
		{
			record.pubAddress = tokens.at(17);
			record.dateTime = tokens.at(18);
			record.state = tokens.at(19);
		}
	}
}