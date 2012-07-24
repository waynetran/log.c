/* Copyright (c) 2012 Wayne Tran <wayne@tran.io>
 * License: MIT
 */

#include <stdio.h>
#include <stdlib.h>
#include "log.h"

bool test_default();
bool test_file();
bool test_syslog();
bool test_flags();

int main(int argc, char * argv[])
{
	if(!test_default()){
		printf("test_default() failed!\n");
		return 1;
	}

	if(!test_file()){
		printf("test_file failed!\n");
		return 1;
	}

	if(!test_syslog()){
		printf("test_syslog() failed!\n");
		return 1;
	}

	if(!test_flags()){
		printf("test_flags() failed!\n");
		return 1;
	}
	return 0;
}

bool test_default(){
	logInit("test_default");
	logInfo("this is an info with an integer: %d",15);
	logError("this is an error in scientifc notation: %e",1023332.222);
	logDebug("this is a debug with string: %s %s", "hello", "world");
	logWarn ("this is a warning with three decimals %0.3f", 3.33333);
	logTrace("this is a trace with two decimals %0.2f", 3.33333);
	logClose();
	return true;
}

bool test_file(){
	logInit("test_file.log");
	logSetFlags(LOGFLAG_FILE |
				LOGFLAG_INFO |
				LOGFLAG_ERROR |
				LOGFLAG_WARN |
				LOGFLAG_TRACE|
				LOGFLAG_DEBUG);
	logInfo("this is an info with an integer: %d",15);
	logError("this is an error in scientifc notation: %e",1023332.222);
	logDebug("this is a debug with string: %s %s", "hello", "world");
	logWarn ("this is a warning with three decimals %0.3f", 3.33333);
	logTrace("this is a trace with two decimals %0.2f", 3.33333);
	logClose();
	return true;
}

bool test_syslog(){
	logInit("test_syslog");
	logSetFlags(LOGFLAG_SYSLOG |
				LOGFLAG_INFO |
				LOGFLAG_ERROR |
				LOGFLAG_WARN |
				LOGFLAG_TRACE|
				LOGFLAG_DEBUG);
	logInfo("this is an info with an integer: %d",15);
	logError("this is an error in scientifc notation: %e",102020222);
	logDebug("this is a debug with string: %s %s", "hello", "world");
	logWarn ("this is a warning with three decimals %0.3f", 3.33333);
	logTrace("this is a trace with two decimals %0.2f", 3.33333);
	logClose();
	return true;
}

bool test_flags(){
	logInit("test_flags.log");
	DWORD flags = LOGFLAG_FILE |
			LOGFLAG_INFO |
			LOGFLAG_ERROR |
			LOGFLAG_WARN |
			LOGFLAG_TRACE|
			LOGFLAG_DEBUG;

	logSetFlags(flags);
	DWORD result = logGetFlags();
	DWORD expected = flags;
	if(result != expected){
		printf("Error: Found flags %lu, expected %lu\n",result, expected);
		return false;
	}

	logRemoveFlags(LOGFLAG_FILE);
	result = logGetFlags();
	expected = LOGFLAG_INFO |
			LOGFLAG_ERROR |
			LOGFLAG_WARN |
			LOGFLAG_TRACE|
			LOGFLAG_DEBUG;

	if(result != expected){
		printf("Error: Found flags %lu, expected %lu\n",result, expected);
		return false;
	}

	logRemoveFlags(LOGFLAG_INFO|LOGFLAG_WARN|LOGFLAG_DEBUG);
	result = logGetFlags();
	expected = LOGFLAG_ERROR | LOGFLAG_TRACE;

	if(result != expected){
		printf("Error: Found flags %lu, expected %lu\n",result, expected);
		return false;
	}

	logRemoveFlags(LOGFLAG_ERROR | LOGFLAG_TRACE);
	result = logGetFlags();
	expected = 0;

	if(result != expected){
		printf("Error: Found flags %lu, expected %lu\n",result, expected);
		return false;
	}

	logAddFlags(LOGFLAG_SYSLOG|LOGFLAG_DEBUG);
	result = logGetFlags();
	expected = LOGFLAG_SYSLOG|LOGFLAG_DEBUG;

	if(result != expected){
		printf("Error: Found flags %lu, expected %lu\n",result, expected);
		return false;
	}


	return true;
}

