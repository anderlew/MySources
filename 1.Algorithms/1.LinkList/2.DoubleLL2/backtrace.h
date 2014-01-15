#ifndef BACKTRACE_H
#define BACKTRACE_H

#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define REG_DEBUG_SIGNAL signal(SIGSEGV, &sig_handler);

#define NOTIFY_DEBUG_SIGNAL kill(0, SIGSEGV);

//kill(0, SIGSEGV);
//signal(SIGSEGV, &sig_handler);
void sig_handler()
{
    void * array[25];
    int nSize = backtrace(array, 25);
    char ** symbols = backtrace_symbols(array, nSize);

    int i = 0;
    printf("<<<<<<<<<<<<<<<<BackTrace<<<<<<<<<<<<<<<\n");
    for (i = 0; i < nSize; i++)
    {
        puts(symbols[i]);;
    }
    printf(">>>>>>>>>>>>>>>>BackTrace>>>>>>>>>>>>>>>\n");

    free(symbols);

    exit(-1);
    //signal(sig, &sig_handler);
}

#endif // BACKTRACE_H
