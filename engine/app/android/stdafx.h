#pragma once

// 平台头文件
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/log.h>

#define TYPENAME					typename
#define ZeroMemory(ptr,size)		memset((ptr),0,(size))
#define GL_DEPTH24_STENCIL8			GL_DEPTH24_STENCIL8_OES
typedef unsigned char				byte;

// C 运行时头文件
#include <stdlib.h>
#include <typeinfo>
#include <memory.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>

// std
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <deque>
#include <algorithm>
#include <iterator>
#include <cctype>

// freetype
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H

// tinyxml
#include "tinyxml2.h"

// json
#include "json/json.h"

// lua
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

// 
#include "XeDefine.h"
#include "XeLog.h"
