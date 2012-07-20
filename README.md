# LOG.C - an extremely simple logging library for C on linux.
It was thrown together while doing various experimental projects in C. 
Comments, suggestions, feature/pull requests (unit tests!) are always welcome. 

###Planned features:
* Rolling logs with size threshold. 
* Cross platform support.
* Threaded queued message logging. 
* True unit tests.

# Example
The following will write to test_file.log in the current directory
with all levels enabled.

```C
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
logError("this is an error in scientifc notation: %e",1023332.222);
logDebug("this is a debug with string: %s %s", "hello", "world");
logWarn ("this is a warning with three decimals %0.3f", 3.33333);
logTrace("this is a trace with two decimals %0.2f", 3.33333);
logClose();
```

###./test_file.log
```
[Fri Jul 20 01:09:59 2012] INFO: this is an info with an integer: 15
[Fri Jul 20 01:09:59 2012] ERROR: this is an error in scientifc notation: 1.023332e+06
[Fri Jul 20 01:09:59 2012] DEBUG: this is a debug with string: hello world
[Fri Jul 20 01:09:59 2012] WARNING: this is a warning with three decimals 3.333
[Fri Jul 20 01:09:59 2012] TRACE: this is a trace with two decimals 3.33

```

# Flags
Call logSetFlags() after logInit() with a set of flags to change defaults:

	LOGFLAG_FILE	/* log to a file with the name specified by logInit's domain argument*/
	LOGFLAG_STDOUT	/* (Default) log to stdout */
	LOGFLAG_STDERR	/* log to stderr for ERROR and WARNING messages */
	LOGFLAG_SYSLOG	/* log to system logs */
	LOGFLAG_ERROR	/* (Default) log error messages */
	LOGFLAG_INFO	/* (Default) log info messages  */
	LOGFLAG_DEBUG	/* (Default) log debug messages */
	LOGFLAG_TRACE	/* (Default) log trace messages */
	LOGFLAG_WARN	/* (Default) log warning messages */

# Build and Install

	make && sudo make install

This will build and install into:  
* ***/usr/local/include/log.c/log.h***
* ***/usr/local/lib/liblog.c.a***



# Contact
Author: Wayne Tran  
Email: wayne@tran.io  
License: MIT  

