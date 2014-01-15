#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void sig_handler(int sig)
{
    void * array[25];
    int nSize = backtrace(array, 25);
    char ** symbols = backtrace_symbols(array, nSize);

    int i = 0;
    for (i = 0; i < nSize; i++)
    {
        puts(symbols[i]);;
    }

    free(symbols);

    signal(sig, &sig_handler);
}

void h()
{
    kill(0, SIGSEGV);
}

void g()
{
    h();
}

void f()
{
    g();
}

int main(int argc, char ** argv)
{
    signal(SIGSEGV, &sig_handler);
    f();
}
