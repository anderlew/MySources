#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

#include <errno.h>

#define CPERROR         1
#define CPSTATUS        2
#define CPDEBUG         4

#define LOG_FILE "/var/log/rastertostar.log"

static void log_event(short type, char* fmt, ...) 
{
    va_list args;
    va_start(args, fmt);
    time_t secs;
    char ctype[8] = {0};
    char *timestring = NULL;
    char *detail = NULL;

    FILE *logfp = NULL;
    char logfile[128] = LOG_FILE; 
    logfp = fopen(logfile, "a");

    (void) time(&secs);
    timestring=ctime(&secs);
    timestring[strlen(timestring)-1]='\0';

    if (type == CPERROR) {
        snprintf(ctype, 8, "ERROR");
    } else if (type == CPSTATUS) {
        snprintf(ctype, 8, "STATUS");
    } else {
        snprintf(ctype, 8, "DEBUG");
    }

    detail = (char*) malloc(1024);
    vsprintf(detail, fmt, args);

    if (detail != NULL)  {
        fprintf(logfp,"%s [%s] (%s)\n", timestring, ctype, detail);
    } else {
        fprintf(logfp,"%s [%s] %s\n", timestring, ctype, detail);
    }

    free(detail);
    
    (void) fflush(logfp);
    fclose(logfp);
    va_end(args);

    return;
}

int main(int argc, char *argv[])
{
    log_event(CPDEBUG, "rastertostar: %s", "hello, world");

    //////////////////////////////////
    //int m = 0;
    //for (m = 0; m < argc; m++) {
    //  log_event(CPDEBUG, "rastertostar [%d]=%s\n", m, argv[m]);
    //}
    //////////////////////////////////

    return 0;
}

// end of rastertostar.c
