#include <stdio.h>

int main()
{
  union w
 {
  int a;  //4 bytes
  char b; //1 byte
 } c;
  c.a=1;
  if (c.b==1)
  printf("It is Little_endian!\n");
  else
  printf("It is Big_endian!\n");
  return 1;
}
