#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[1])
{
 int fp;
 char cBuf[64], cOut[2];

 printf("Hi, welcome\n Press <ENTER> to finish");
 fp = open("/dev/ttyS0",O_WRONLY);
 printf("fp = %i",fp);

 write(fp,"\n\n\n\n",4);
 write(fp,"Hello World\n\n\n\n\n",14);
 write(fp,"\x1D\x56\x01",3);
 close(fp);

 return EXIT_SUCCESS;
}
