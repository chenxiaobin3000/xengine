/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11-18
 */

#ifndef _XECONFIG_H_
#define _XECONFIG_H_

namespace XE {

class CConfig
{
public:
	CConfig();
	virtual ~CConfig();

	static void SetScreenLandscape(bool b);
	static bool GetScreenLandscape();
	
	static void SetMouse2Touch(bool b);
	static bool GetMouse2Touch();
	
	static void SetUseShadow(bool b);
	static bool GetUseShadow();

	static void SetLocalMode(bool b);
	static bool GetLocalMode();
	
	static void SetDisableCull(bool b);
	static bool GetDisableCull();
	
	static void SetViewBones(bool b);
	static bool GetViewBones();
	
	static void SetSaveFont(bool b);
	static bool GetSaveFont();
	
	static void SetLuaDebug(bool b);
	static bool GetLuaDebug();
	
	static void SetLogBone(bool b);
	static bool GetLogBone();

	static void SetLogRTT(bool b);
	static bool GetLogRTT();
	
	static void SetSaveRT(bool b);
	static bool GetSaveRT();
	
	static void SetSaveDepth(bool b);
	static bool GetSaveDepth();
	
	static void SetShowLight(bool b);
	static bool GetShowLight();
	
	static void SetShowCamera(bool b);
	static bool GetShowCamera();
	
	static void SetDrawAABB(bool b);
	static bool GetDrawAABB();
	
	static void SetDrawAABB2(bool b);
	static bool GetDrawAABB2();
	
	static void SetPassName(bool b);
	static bool GetPassName();
	
private:
	static bool					s_bScreenLandscape;		// 是否横屏
	static bool					s_bMouse2Touch;			// 用鼠标模拟触摸
	static bool					s_bUseShadow;			// 开启阴影

	static bool					s_bLocalMode;			// 本地资源测试
	static bool					s_bDisableCull;			// 关闭背面剔除
	static bool					s_bViewBones;			// 显示骨骼
	static bool					s_bSaveFont;			// 保存字体纹理
	static bool					s_bLuaDebug;			// 打开lua调试模式
	static bool					s_bLogBone;				// 输出骨骼动画矩阵
	static bool					s_bLogRTT;				// 输出rtt第一个像素数据
	static bool					s_bSaveRT;				// 保存渲染目标
	static bool					s_bSaveDepth;			// 保存深度图
	static bool					s_bShowLight;			// 显示灯光
	static bool					s_bShowCamera;			// 显示摄像头
	static bool					s_bDrawAABB;			// 画aabb
	static bool					s_bDrawAABB2;			// 画aabb2
	static bool					s_bPassName;			// 记录pass来源
};

}

#endif //_XECONFIG_H_
