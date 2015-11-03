#include "stdafx.h"
#include "XeLog.h"

namespace XE {

void XLog(const char* format, ...) {
	char tmp[1024];

	va_list ap;
	va_start(ap, format);
	vsprintf(tmp, format, ap);
	va_end(ap);

	__android_log_print(ANDROID_LOG_DEBUG, "xe_engine", "%s", tmp);
}

}
