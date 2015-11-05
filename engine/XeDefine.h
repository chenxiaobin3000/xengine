/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11- 3
 */

#ifndef _XEDEFINE_H_
#define _XEDEFINE_H_

// 调试功能宏
#ifdef _DEBUG
//	#define LOCAL_MODE				// 本地资源测试
//	#define DISABLE_CULL			// 关闭背面剔除
//	#define VIEW_BONES				// 显示骨骼
//	#define SAVE_FONT				// 保存字体纹理
//	#define ANIMAL_DEBUG			// 动画调试模式
#	define LUA_DEBUG				// 打开lua调试模式
//	#define LOG_BONE				// 输出骨骼动画矩阵
//	#define LOG_RTT					// 输出rtt第一个像素数据
//	#define LOG_DBVT				// 输出动态二叉树
//	#define SAVE_RT					// 保存渲染目标
//	#define SAVE_DEPTH				// 保存深度图
#	define SHOW_LIGHT				// 显示灯光
//	#define SHOW_CAMERA				// 显示摄像头
//	#define DRAW_AABB				// 画aabb
//	#define DRAW_AABB2				// 画aabb2
//	#define DRAW_QUADTREE			// 画四叉树
//	#define DRAW_OCTREE				// 画八叉树
//	#define DRAW_BSPTREE			// 画bsp树
//	#define DRAW_SCENE_LEAF			// 画场景树叶子节点
//	#define WATER_LOG				// 输出添加水记录
#	define PASS_NAME				// 记录pass来源
#endif //_DEBUG

// 辅助函数宏
#ifdef _DEBUG
#	define XELOG		XE::XLog
#	define XEASSERT		assert
#	define NEW_LOG(x)	new x//; XELOG("new file: %s:%d\n", __FILE__, __LINE__)
#	define PUSH(x)		push_back(x)//; XELOG("push file: %s:%d\n", __FILE__, __LINE__)
#	define INSERT(x)	insert(x)//; XELOG("insert file: %s:%d\n", __FILE__, __LINE__)
#else
#	define XELOG
#	define XEASSERT
#	define NEW_LOG(x)	new x
#	define PUSH(x)		push_back(x)
#	define INSERT(x)	insert(x)
#endif //_DEBUG

// 正式项目宏
#define MOUSE2TOUCH					// 用鼠标模拟触摸
//#define USE_SHADOW					// 开启阴影

#endif //_XEDEFINE_H_
