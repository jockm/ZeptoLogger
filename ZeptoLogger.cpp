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
	memccpy(log, (uint8_t *) &t, 8);
	
	log[8] = level;
	
	strncpy(log + 9, msg, 90);
	
	// TODO need to wrap around if file too large
	fwrite(log, sizeof(char), sizeof(log), this->logFile);
	fflush(this->logFile);
}


void ZeptoLogger::log(uint8_t level, const char *fmt, ...)
{	
	va_list args;

	va_start(args, fmt);
	this->log(level, fmt, args);
	va_end(args);
}


void ZeptoLogger::log(uint8_t level, const char *format, va_list arg);

void ZeptoLogger::error(const char *msg)
{
	this->log(ZERROR, msg);
}

void ZeptoLogger::error(const char *fmt, ...)
{	
	va_list args;

	va_start(args, fmt);
	this->log(ZERROR, fmt, args);
	va_end(args);
}


void ZeptoLogger::warn(const char *msg)
{
	this->log(ZWARNING, msg);
}


void ZeptoLogger::warn(const char *fmt, ...)
{	
	va_list args;

	va_start(args, fmt);
	this->log(ZWARNING, fmt, args);
	va_end(args);
}


void ZeptoLogger::info(const char *msg)
{
	this->log(ZINFO, msg);
}


void ZeptoLogger::info(const char *fmt, ...)
{	
	va_list args;

	va_start(args, fmt);
	this->log(ZINFO, fmt, args);
	va_end(args);
}

void ZeptoLogger::debug(const char *msg)
{
	this->log(ZDEBUG, msg);
}


void ZeptoLogger::debug(const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	this->log(ZDEBUG, fmt, args);
	va_end(args);
}
