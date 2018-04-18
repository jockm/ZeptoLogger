#ifndef ZEPTOLOGGER_H
#	define ZEPTOLOGGER_H

#ifdef __MBED__
#include "mbed.h"
#endif

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

enum {
	ZERROR   = 0,
	ZWARNING = 10,
	ZINFO    = 100,
	ZDEBUG   = 255,
};

class ZeptoLogger
{
public:
	ZeptoLogger(const char *fName);
	~ZeptoLogger();
	
	void close();
	
	void setLogLevel(uint8_t level);
	
	void log(uint8_t level, const char *msg);
	void log(uint8_t level, const char *fmt, ...);
	void log(uint8_t level, const char *format, va_list arg);
	
	void error(const char *msg);
	void error(const char *fmt, ...);
	
	void warn(const char *msg);
	void warn(const char *fmt, ...);
	
	void info(const char *msg);
	void info(const char *fmt, ...);
	
	void debug(const char *msg);
	void debug(const char *fmt, ...);

private:
	FILE    *logFile;
	uint8_t  level;
};

#endif // ZEPTOLOGGER_H
