#include "stdafx.h"
#include "XeXFile.h"

#import <Foundation/Foundation.h>
#import <UIKit/UIDevice.h>

namespace XE {

std::string CXFile::s_strTmp;

CXFile::CXFile() {

}

CXFile::~CXFile() {

}

bool CXFile::IsExist(const char* name) {
	std::string str = GetWritablePath();
	str += name;
    return CFile::IsExist(str.c_str());
}

bool CXFile::ReadFile(const char* name, byte*& buffer, unsigned int& size) {
	std::string str = GetWritablePath();
	str += name;
    return CFile::ReadFile(str.c_str(), buffer, size);
}

bool CXFile::ReadText(const char* name, byte*& buffer, unsigned int& size) {
	std::string str = GetWritablePath();
	str += name;
    return CFile::ReadText(str.c_str(), buffer, size);
}

const char* CXFile::GetWritablePath() {
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDirectory = [paths objectAtIndex:0];
	s_strTmp = [documentsDirectory UTF8String];
	s_strTmp.append("/");
	return s_strTmp.c_str();
}

}
