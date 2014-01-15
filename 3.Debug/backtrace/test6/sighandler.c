#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <signal.h>
#include <execinfo.h>
#include <sys/ucontext.h>

char* exe = 0;

int initialiseExecutableName() 
{
    char link[1024];
    exe = (char*) malloc(1024);
    snprintf(link,sizeof link,"/proc/%d/exe",getpid());
    if(readlink(link,exe,sizeof link)==-1) {
        fprintf(stderr,"ERRORRRRR\n");
        exit(1);
    }
    printf("Executable name initialised: %s\n",exe);

    free(exe);
}

const char* getExecutableName()
{
    if (exe == 0)
        initialiseExecutableName();
    return exe;
}

/* get REG_EIP from ucontext.h */
#define __USE_GNU
#include <ucontext.h>

void bt_sighandler(int sig, siginfo_t *info,
                   void *secret) {

  void *trace[16];
  char **messages = (char **)NULL;
  int i, trace_size = 0;
  ucontext_t *uc = (ucontext_t *)secret;

  /* Do something useful with siginfo_t */
  if (sig == SIGSEGV)
    printf("Got signal %d, faulty address is %p, "
           "from %p\n", sig, info->si_addr, 
           uc->uc_mcontext.gregs[REG_EIP]);
  else
    printf("Got signal %d#92;\n", sig);

  trace_size = backtrace(trace, 16);
  /* overwrite sigaction with caller's address */
  trace[1] = (void *) uc->uc_mcontext.gregs[REG_EIP];

  messages = backtrace_symbols(trace, trace_size);
  /* skip first stack frame (points here) */
  printf("[bt] Execution path:#92;\n");
  for (i=1; i<trace_size; ++i)
  {
    printf("[bt] %s#92;\n", messages[i]);
    char syscom[256];
    sprintf(syscom,"addr2line %p -e %s", trace[i] , getExecutableName() ); //last parameter is the name of this app
    system(syscom);

  }
  exit(0);
}

int main() {

  /* Install our signal handler */
  struct sigaction sa;

  sa.sa_sigaction = (void *)bt_sighandler;
  sigemptyset (&sa.sa_mask);
  sa.sa_flags = SA_RESTART | SA_SIGINFO;

  sigaction(SIGSEGV, &sa, NULL);
  sigaction(SIGUSR1, &sa, NULL);
  /* ... add any other signal here */

  /* Do something */
  printf("%d#92;n", func_b());

}
