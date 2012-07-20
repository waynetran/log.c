/* Copyright (c) 2012 Wayne Tran <wayne@tran.io>
 * License: MIT
 */

#include <stdio.h>
#include <stdlib.h>
#include "log.h"

bool test_default();
bool test_file();
bool test_syslog();

int main(int argc, char * argv[])
{
	test_default();
	test_file();
	test_syslog();
	return 0;
}

bool test_default(){
	logInit("test_default");
	logInfo("this is an info with an integer: %d",15);
	logError("this is an error in scientifc notation: %e",102020222);
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
	logError("this is an error in scientifc notation: %e",102020222);
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
