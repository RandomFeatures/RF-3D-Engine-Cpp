//file debug.cpp
#ifdef _DEBUG
#include <stdio.h>
#include <stdarg.h>
#include <windows.h>

void _trace(char *fmt, ...)
{
     char out[1024];
     va_list body;
     va_start(body, fmt);
     vsprintf(out, fmt, body);
     va_end(body);
     OutputDebugString(out);
}


#endif