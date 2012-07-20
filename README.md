# Overview
**log.c** is an extremely simple logging library for C on linux.
It was thrown together while doing various experimental projects in C.

# Example
The following will write to test_file.log in the current directory
with all levels enabled.
	/*If you've installed the library*/
	#include <log.c/log.h>

	...

	logInit("test_file.log");
	/*Optional*/
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

Possible flags:
Defaults are set when logInit() is called.

	LOGFLAG_FILE	/* log to a file with the name specified by domain */
	LOGFLAG_STDOUT	/* (Default) log to stdout */
	LOGFLAG_STDERR	/* log to stderr for ERROR and WARNING messages */
	LOGFLAG_SYSLOG	/* log to system logs */
	LOGFLAG_ERROR	/* (Default) log error messages */
	LOGFLAG_INFO	/* (Default) log info messages  */
	LOGFLAG_DEBUG	/* (Default) log debug messages */
	LOGFLAG_TRACE	/* (Default) log trace messages */
	LOGFLAG_WARN	/* (Default) log warning messages */

# Build and Install
This will build and install the header into usr/local/include/log.c/log.h
and library to /usr/local/lib/liblog.c.a

	make && sudo make install

# Contact
Author: Wayne Tran
Email: wayne@tran.io
License: MIT

