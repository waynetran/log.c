/* Copyright (c) 2012 Wayne Tran <wayne@tran.io>
 * License: MIT
 */

#include "log.h"
#include <syslog.h>
#include <stdarg.h>

typedef struct {
	const char *domain;
	int fd;
	DWORD flags;

} Logger;

static Logger logger = {"",-1,0};

bool logInit(const char *domain){
	if(!domain)
		return false;

	logger.domain = domain;
	logSetFlags(LOGFLAG_STDOUT|LOGFLAG_INFO|LOGFLAG_ERROR|
				LOGFLAG_DEBUG|LOGFLAG_TRACE|LOGFLAG_WARN);

	return true;

}

bool logClose(){
	closelog();
	if(logger.fd != -1 && close(logger.fd)){
		logError("Could not close log file.");
		return false;
	}
	logger.fd = -1;
	return true;
}

void logSetFlags(DWORD logflags){
	logClose();
	logger.flags = logflags;

	if(logger.domain && strlen(logger.domain) > 0){
		if((logger.flags & LOGFLAG_FILE) == LOGFLAG_FILE){
			int openFlags;
			mode_t filePerms;
			openFlags = O_CREAT | O_WRONLY | O_APPEND;
			filePerms = S_IRUSR | S_IWUSR;
			logger.fd = open(logger.domain, openFlags, filePerms);

			if (logger.fd == -1){
				logError("Could not open file for logging.");
			}
		}

		if((logger.flags & LOGFLAG_SYSLOG) == LOGFLAG_SYSLOG){
			/*logs PID, connects immediately and are generic user level messages*/
			openlog (logger.domain, LOG_PID | LOG_NDELAY, LOG_USER);
		}
	}

}

DWORD logGetFlags(){
	return logger.flags;
}

DWORD logRemoveFlags(DWORD mask){
	DWORD flags = logger.flags & ~mask;
	logSetFlags(flags);
	return flags;
}

DWORD logAddFlags(DWORD mask){
	DWORD flags = logger.flags | mask;
	logSetFlags(flags);
	return flags;
}

char * currentTimeString(){
	time_t rawtime;
	struct tm * timeinfo;
	char *buffer = (char*) malloc(sizeof(char) * 81);
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );

	strftime (buffer,80,"%c",timeinfo);
	return buffer;

}


void logMsg(const char *format, va_list args, bool isError){
	char timeformat[MAXLENGTH];
	char buffer[MAXLENGTH];
	char * timeString = currentTimeString();


	snprintf(timeformat,MAXLENGTH,"[%s] %s\n",timeString,format);
	size_t bufferSize = vsnprintf(buffer, MAXLENGTH, timeformat, args);


	/*If the STDERR flag is not set, we print all messages to STDOUT if that
	 *flag is set.  Otherwise, we split up the error messages*/
	if((logger.flags & LOGFLAG_STDERR) != LOGFLAG_STDERR){
		if((logger.flags & LOGFLAG_STDOUT) == LOGFLAG_STDOUT){
			printf("%s",buffer);
			fflush(stdout);
		}
	}else{
		if(!isError && (logger.flags & LOGFLAG_STDOUT) == LOGFLAG_STDOUT){
			printf("%s",buffer);
			fflush(stdout);
		}

		if(isError && (logger.flags & LOGFLAG_STDERR) == LOGFLAG_STDERR){
			fprintf(stderr,"%s",buffer);
			fflush(stderr);
		}
	}

	/*Write out to a file if the flag is set*/
	if((logger.flags & LOGFLAG_FILE) == LOGFLAG_FILE){
		write(logger.fd,buffer,bufferSize);
	}


	free(timeString);
}


void logError(const char *format, ...){
	if((logger.flags & LOGFLAG_ERROR) != LOGFLAG_ERROR)
	    return;

	va_list args;
	va_start(args,format);
	char buffer[MAXLENGTH];
	if(snprintf(buffer,MAXLENGTH,"ERROR: %s",format)){

		logMsg(buffer, args,true);

	}
	/*Write to syslog if flag is set*/
	if((logger.flags & LOGFLAG_SYSLOG) == LOGFLAG_SYSLOG){
		vsyslog(LOG_ERR,buffer,args);
	}
	va_end(args);
}

void logInfo(const char *format, ...){
	if((logger.flags & LOGFLAG_INFO) != LOGFLAG_INFO)
	    return;
	va_list args;
	va_start(args,format);

	char buffer[MAXLENGTH];
	if(snprintf(buffer,MAXLENGTH,"INFO: %s",format)){
		logMsg(buffer, args, false);
	}
	/*Write to syslog if flag is set*/
	if((logger.flags & LOGFLAG_SYSLOG) == LOGFLAG_SYSLOG){
		vsyslog(LOG_INFO,buffer,args);
	}
	va_end(args);
}

void logDebug(const char *format, ...){
	if((logger.flags & LOGFLAG_DEBUG) != LOGFLAG_DEBUG)
	    return;
	va_list args;
	va_start(args,format);

	char buffer[MAXLENGTH];
	if(snprintf(buffer,MAXLENGTH,"DEBUG: %s",format)){
		logMsg(buffer, args, false);
	}

	/*Write to syslog if flag is set*/
	if((logger.flags & LOGFLAG_SYSLOG) == LOGFLAG_SYSLOG){
		vsyslog(LOG_DEBUG,buffer,args);
	}
	va_end(args);
}

void logTrace(const char *format, ...){
	if((logger.flags & LOGFLAG_TRACE) != LOGFLAG_TRACE)
	    return;
	va_list args;
	va_start(args,format);

	char buffer[MAXLENGTH];
	if(snprintf(buffer,MAXLENGTH,"TRACE: %s",format)){
		logMsg(buffer, args, false);
	}
	/*Write to syslog if flag is set*/
	if((logger.flags & LOGFLAG_SYSLOG) == LOGFLAG_SYSLOG){
		vsyslog(LOG_DEBUG,buffer,args);
	}
	va_end(args);
}

void logWarn(const char *format, ...){
	if((logger.flags & LOGFLAG_WARN) != LOGFLAG_WARN)
	    return;
	va_list args;
	va_start(args,format);

	char buffer[MAXLENGTH];
	if(snprintf(buffer,MAXLENGTH,"WARNING: %s",format)){
		logMsg(buffer, args, true);
	}

	/*Write to syslog if flag is set*/
	if((logger.flags & LOGFLAG_SYSLOG) == LOGFLAG_SYSLOG){
		vsyslog(LOG_WARNING,buffer,args);
	}
	va_end(args);
}
