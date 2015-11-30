#include "stdafx.h"
#include "XeLog.h"

namespace XE {

void XLog(const char* format, ...) {
	char tmp[1024];

	va_list ap;
	va_start(ap, format);
	vsprintf(tmp, format, ap);
	va_end(ap);

	printf("%s\n", tmp);
}

}
