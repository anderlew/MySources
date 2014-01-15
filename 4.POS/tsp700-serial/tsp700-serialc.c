//: tsp700-serialc.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

#ifndef FALSE
#define FALSE -1
#endif

#ifndef TRUE
#define TRUE 0 
#endif

#define DEVICE "/dev/ttyS0"

#define BUFF_SIZE 1024

#define EXT_NAME ".dat"

int SPEED_INT_LIST[] = {
	115200,
	38400,
	19200,
	9600,
	4800,
	2400,
	1200,
	300
};

int SPEED_LIST[] = {
	B115200,
	B38400,
	B19200,
	B9600,
	B4800,
	B2400,
	B1200,
	B300
};

int _perror(const char *format, ...) 
{
	va_list ap;
	int ret = 0;

	va_start(ap, format);
	ret = fprintf(stderr, format, ap); 
	va_end(ap);
	printf("\n");

	return ret;
}

int setSpeed(int fd, int speed) {
	int i;
	int status;
	struct termios ops;

	tcgetattr(fd, &ops);

	for (i = 0; i < sizeof(SPEED_INT_LIST) / sizeof(int); i++) {
		if (speed == SPEED_INT_LIST[i]) {
			tcflush(fd, TCIOFLUSH);
			cfsetispeed(&ops, SPEED_LIST[i]);
			cfsetospeed(&ops, SPEED_LIST[i]);

			status = tcsetattr(fd, TCSANOW, &ops);
			if (status == -1) {
				_perror("setSpeed: tcsetattr failed.");
				return;
			}

			tcflush(fd, TCIOFLUSH);

			return 0;
		}
	}

	return -1;
}

int setParity(int fd, int databits, int stopbits, int parity)
{
	struct termios ops;
	
	if (tcgetattr(fd, &ops) != 0) {
		_perror("setParity: tcgetattr failed.");
		return -1;
	}

	ops.c_cflag &= ~CSIZE;

	switch (databits) {
		case 7:
			ops.c_cflag |= CS7;
			break;
		case 8:
			ops.c_cflag |= CS8;
			break;
		default:
			_perror("setParity: Unsupported data size.");
			return -1;
	}

	switch (parity) {
		case 'n':
		case 'N':
			ops.c_cflag &= ~PARENB;
			ops.c_iflag &= ~INPCK;
			break;
		case 'o':
		case 'O':
			ops.c_cflag |= PARENB;
			ops.c_cflag &= ~PARODD;
			ops.c_iflag |= INPCK;
			break;
		case 'S':
		case 's':
			ops.c_cflag &= ~PARENB;
			ops.c_cflag &= ~CSTOPB;
			break;
		default:
			_perror("setParity: Unsupported parity.");
			return -1;
	}

	switch (stopbits) {
		case 1:
			ops.c_cflag &= ~CSTOPB;
			break;
		case 2:
			ops.c_cflag |= CSTOPB;
			break;
		default:
			_perror("setParity: Unsupported stop bits.");
			return -1;
	}

	if (parity != 'n' && parity != 'N') {
		ops.c_iflag |= INPCK;
	}

	tcflush(fd, TCIFLUSH);
	ops.c_cc[VTIME] = 150;
	ops.c_cc[VMIN] = 0;

	if (tcsetattr(fd, TCSANOW, &ops) != 0) {
		_perror("setParity: tcsetattr failed.");
		return -1;
	}

	return 0;
}

int openDev(char *dev)
{
	int fd = open(dev, O_RDWR);
	if (-1 == fd) {	
		_perror("Can't open serial port");
		return -1;
	}

	return fd;
}

int isValidHead(char* context)
{
}

int isValidTail(char* context)
{
}

/*
 * Format for Name: <Date Time>-<User Name>-<Host Name>-<Document Name>
 *
 */

char* getFileName(char* userName, char* hostName, char* docName)
{
	time_t lt;
	struct tm *ptm;
	char *fileName = NULL;
	int len = 0;

	lt = time(NULL);
	ptm = localtime(&lt);

	// Add the length of 'User Name'
	if (userName != NULL) {
		len += strlen(userName);
	}

	// Add the length of 'Host Name'
	if (hostName != NULL) {
		len += strlen(hostName);
	}

	// Add the length of 'Document Name'
	if (docName != NULL) {
		len += strlen(docName);
	}

	// Add the length of datetime
	len += 14;

	// Add the length of seprator and extension name
	len += 6 + 4;

	fileName = (char*) malloc(sizeof(char) * len);
	if (fileName == NULL) {
		return NULL;
	}

	sprintf(fileName, "%d%d%d%d%d%d", 
		ptm->tm_year + 1900,
		ptm->tm_mon + 1,
		ptm->tm_mday,
		ptm->tm_hour,
		ptm->tm_min,
		ptm->tm_sec);

	if (userName != NULL) {
		strcat(fileName, "-");
		strcat(fileName, userName);
	}

	if (hostName != NULL) {
		strcat(fileName, "-");
		strcat(fileName, hostName);
	}

	if (docName != NULL) {
		strcat(fileName, "-");
		strcat(fileName, docName);
	}

	strcat(fileName, EXT_NAME);

	return fileName;
}

FILE *openOutFile() {
	FILE *file;
	char *fileName = NULL;
	
	//outFD = open("1.txt.ps", O_WRONLY|O_CREAT, 0640);
	file = fopen(fileName, "wb+");
	//outFD = fopen("1.txt.ps", "wb");
	if (NULL == file) {
	//if (-1 == outFD) {
		_perror("Open <%s> failed.\n", fileName);
	}

	free(fileName);

	return file;
}

void closeOutFile(FILE* file)
{
	fclose(file);
}

void testSendSerial(int devFD)
{
	write(devFD, "123", 3);
	//write(devFD, 0x1b30, 1);
	//write(devFD, 0xff42, 1);
	//write(devFD, 0x1b00, 1);
	//write(devFD, 0xa44c, 1);
}

int main(int argc, char* argv[])
{
	int devFD;
	FILE *outFD;
	//int outFD;
	int nRead;
	char buff[1024] = {0};
	char *fileName = NULL;

	//printf("getFileName:%s.\n", getFileName(NULL, NULL, NULL));
	//exit(0);
	
	devFD = openDev(DEVICE);
	if (devFD == -1) {
		exit(-1);
	}

	if (setSpeed(devFD, SPEED_INT_LIST[1]) == -1) {
		_perror("setSpeed failed.\n");
		exit(-1);
	}

	if (setParity(devFD, 8, 1, 'N') == -1) {
		_perror("setParity failed.\n");
		exit(-1);
	}

	testSendSerial(devFD);
	exit(0);

	outFD = openOutFile();
	if (NULL == outFD) {
		_perror("openOutFile failed.\n");
		exit(-1);
	}

	fd_set readSet;
	
	FD_ZERO(&readSet);
	FD_SET(devFD, &readSet);
	//while (FD_ISSET(devFD, &readSet)) {
	if (FD_ISSET(devFD, &readSet)) {
		if (select(devFD + 1, &readSet, NULL, NULL, NULL) < 0) {
			_perror("Select failed.\n");
		} else {
			tcflush(devFD, TCIOFLUSH);
			memset(buff, '\0', 1024 * sizeof(char));
			while ((nRead = read(devFD, buff, 1024)) > 0) {
				printf("%s", buff);

				fwrite(buff, nRead, SEEK_CUR, outFD);
				//write(outFD, buff, nRead);

				fflush(outFD);
				memset(buff, '\0', 1024 * sizeof(char));
			}
		}
	}

	//while (1) {
	//	while ((nRead = read(devFD, buff, 1024)) > 0) {
	//		//printf("\nLef=%d\n", nRead);
	//		//buff[nRead+1] = '\0';
	//		printf("%s", buff);
	//		write(outFD, buff, 1024);
	//	}
	//}

	closeOutFile(outFD);
	close(devFD);

	return 0;
}

