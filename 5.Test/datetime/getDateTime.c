//: getDateTime.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void test1()
{
	time_t tm_now;
	struct tm *tm;

	time(&tm_now);

	tm = localtime(&tm_now);

	printf("Local time: %s.\n", asctime(&tm));
}

void test2()
{
	time_t lt;
	lt = time(NULL);

	printf(ctime(&lt));
	printf(asctime(localtime(&lt)));
	printf(asctime(gmtime(&lt)));
}

void test3()
{
	struct tm *ptm;
	time_t lt;
	char dateTimeStr[20] = {0};
	lt = time(NULL);

	printf(ctime(&lt));
	printf(asctime(localtime(&lt)));
	printf(asctime(gmtime(&lt)));

	ptm = localtime(&lt);

	year = ptm->tm_year + 1900;
	month = ptm->tm_mon + 1;
	day = ptm->tm_mday;
	hour = ptm->tm_hour;
	minute = ptm->tm_min;
	second = ptm->tm_sec;

	sprintf(dateTimeStr, "%d%d%d_%d%d%d", 
		ptm->tm_year + 1900, 
		ptm->tm_mon + 1,
		ptm->tm_mday,
		ptm->tm_hour,
		ptm->tm_min,
		ptm->tm_sec);

	printf("dateTimeStr=%s.\n", dateTimeStr);
}


int main(int argc, char* argv[])
{
	test3();

	return 0;
}


