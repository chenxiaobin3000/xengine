#include "stdafx.h"
#include "XeJson.h"

namespace XE {

Json::Value CJson::s_Value = Json::Value();

CJson::CJson() {

}

CJson::~CJson() {

}

Json::Value& CJson::GetByName(Json::Value array, const char* szName) {
    for (int i=0; i<array.size(); ++i) {
        Json::Value& value = array[i];
        std::string name = value["name"].asString();
        if (name == szName) {
            return value;
        }
    }
	return s_Value;
}

Json::Value& CJson::GetByType(Json::Value array, const char* szType) {
	for (int i=0; i<array.size(); ++i) {
        Json::Value& value = array[i];
        std::string type = value["type"].asString();
        if (type == szType) {
			return value;
		}
    }
	return s_Value;
}

}
