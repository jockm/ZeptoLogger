#include <time.h>

#include "ZeptoLogger.h"

ZeptoLogger::ZeptoLogger(const char *fName)
{
	this->level = ZWARNING;
	
	// TODO make sure file is opened?
	this->logFile = fopen(fName, "a+b");
}

ZeptoLogger::~ZeptoLogger()
{
	this->close();
}



void ZeptoLogger::close()
{
	fclose(this->logFile);
}


void ZeptoLogger::setLogLevel(uint8_t level)
{
	this->level = level;
}


void ZeptoLogger::log(uint8_t level, const char *msg)
{
	if(level > this->level) {
		return;
	}
	
	char log[100];
	time_t t;
	
	memset(log, 0, sizeof(log));
	
	time(&t);
	memcpy(log, (uint8_t *) &t, 8);
	
	log[8] = level;
	
	strncpy(log + 9, msg, 90);
	
	// TODO need to wrap around if file too large
	fwrite(log, sizeof(char), sizeof(log), this->logFile);
	fflush(this->logFile);
}


void ZeptoLogger::logf(uint8_t level, const char *fmt, ...)
{	
	va_list args;

	va_start(args, fmt);
	this->vlogf(level, fmt, args);
	va_end(args);
}


void ZeptoLogger::vlogf(uint8_t level, const char *fmt, va_list arg)
{
	char msg[90];
	memset(msg, 0, sizeof(msg));

	vsnprintf(msg, sizeof(msg), fmt, arg);
	this->log(level, msg);
}


void ZeptoLogger::error(const char *fmt, ...)
{	
	va_list args;

	va_start(args, fmt);
	this->vlogf(ZERROR, fmt, args);
	va_end(args);
}



void ZeptoLogger::warn(const char *fmt, ...)
{	
	va_list args;

	va_start(args, fmt);
	this->vlogf(ZWARNING, fmt, args);
	va_end(args);
}


void ZeptoLogger::info(const char *fmt, ...)
{	
	va_list args;

	va_start(args, fmt);
	this->vlogf(ZINFO, fmt, args);
	va_end(args);
}


void ZeptoLogger::debug(const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	this->vlogf(ZDEBUG, fmt, args);
	va_end(args);
}
