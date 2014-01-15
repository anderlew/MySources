#include <stdio.h>
#include <stdlib.h>

#include "bindump.h"

int main(int argc, char* argv[])
{
	printf("main[+]\n");

	char* out = getIntBinary(10, 32);
	printf("getIntBinary(10, 32): %s.\n", out);

	printf("main[-]\n");

	return 0;
}

