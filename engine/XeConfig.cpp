#include "stdafx.h"
#include "XeConfig.h"

namespace XE {

bool CConfig::s_bMouse2Touch = false;
bool CConfig::s_bUseShadow = false;
bool CConfig::s_bLocalMode = false;
bool CConfig::s_bDisableCull = false;
bool CConfig::s_bViewBones = false;
bool CConfig::s_bSaveFont = false;
bool CConfig::s_bLuaDebug = false;
bool CConfig::s_bLogBone = false;
bool CConfig::s_bLogRTT = false;
bool CConfig::s_bSaveRT = false;
bool CConfig::s_bSaveDepth = false;
bool CConfig::s_bShowLight = false;
bool CConfig::s_bShowCamera = false;
bool CConfig::s_bDrawAABB = false;
bool CConfig::s_bDrawAABB2 = false;
bool CConfig::s_bPassName = false;
	
CConfig::CConfig() {

}

CConfig::~CConfig() {
	
}

void CConfig::SetMouse2Touch(bool b) {
	s_bMouse2Touch = b;
}

bool CConfig::GetMouse2Touch() {
	return s_bMouse2Touch;
}
	
void CConfig::SetUseShadow(bool b) {
	s_bUseShadow = b;
}
	
bool CConfig::GetUseShadow() {
	return s_bUseShadow;
}

void CConfig::SetLocalMode(bool b) {
	s_bLocalMode = b;
}
	
bool CConfig::GetLocalMode() {
	return s_bLocalMode;
}
	
void CConfig::SetDisableCull(bool b) {
	s_bDisableCull = b;
}
	
bool CConfig::GetDisableCull() {
	return s_bDisableCull;
}

void CConfig::SetViewBones(bool b) {
	s_bViewBones = b;
}
	
bool CConfig::GetViewBones() {
	return s_bViewBones;
}

void CConfig::SetSaveFont(bool b) {
	s_bSaveFont = b;
}
	
bool CConfig::GetSaveFont() {
	return s_bSaveFont;
}

void CConfig::SetLuaDebug(bool b) {
	s_bLuaDebug = b;
}
	
bool CConfig::GetLuaDebug() {
	return s_bLuaDebug;
}

void CConfig::SetLogBone(bool b) {
	s_bLogBone = b;
}
	
bool CConfig::GetLogBone() {
	return s_bLogBone;
}

void CConfig::SetLogRTT(bool b) {
	s_bLogRTT = b;
}
	
bool CConfig::GetLogRTT() {
	return s_bLogRTT;
}

void CConfig::SetSaveRT(bool b) {
	s_bSaveRT = b;
}
	
bool CConfig::GetSaveRT() {
	return s_bSaveRT;
}

void CConfig::SetSaveDepth(bool b) {
	s_bSaveDepth = b;
}
	
bool CConfig::GetSaveDepth() {
	return s_bSaveDepth;
}

void CConfig::SetShowLight(bool b) {
	s_bShowLight = b;
}
	
bool CConfig::GetShowLight() {
	return s_bShowLight;
}

void CConfig::SetShowCamera(bool b) {
	s_bShowCamera = b;
}
	
bool CConfig::GetShowCamera() {
	return s_bShowCamera;
}

void CConfig::SetDrawAABB(bool b) {
	s_bDrawAABB = b;
}
	
bool CConfig::GetDrawAABB() {
	return s_bDrawAABB;
}

void CConfig::SetDrawAABB2(bool b) {
	s_bDrawAABB2 = b;
}
	
bool CConfig::GetDrawAABB2() {
	return s_bDrawAABB2;
}

void CConfig::SetPassName(bool b) {
	s_bPassName = b;
}
	
bool CConfig::GetPassName() {
	return s_bPassName;
}

}
