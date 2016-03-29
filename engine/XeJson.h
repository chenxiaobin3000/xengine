/**
 * desc: 
 * auth: chenxiaobin
 * data: 2016-03-29
 */

#ifndef _XEJSON_H_
#define _XEJSON_H_

namespace XE {

class CJson
{
public:
	CJson();
	virtual ~CJson();

	static Json::Value& GetByName(Json::Value array, const char* szName);
	
	static Json::Value& GetByType(Json::Value array, const char* szType);
    
private:
    static Json::Value s_Value;
};

}

#endif //_XEJSON_H_
