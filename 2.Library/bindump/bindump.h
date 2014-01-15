
char* getCharBinary(char ch) 
{
}

char* getIntBinary(int value, int type)
{
	char* out = NULL;
	unsigned int mask = 0x80000000;
	int index = 0;
	switch (type) {
		case 8:
			mask = 0x80;
			break;
		case 16:
			mask = 0x8000;
			break;
		case 32:
			mask = 0x80000000;
			break;
	}

	out = (char*) malloc(type);
	if (NULL == out) {
		return;
	}

	while (mask > 0) {
		out[index] = (value & mask ? '1' : '0');

		index++;
		mask >>= 1;	
	}

	return out;
}

void bindump(char* buffer, int len)
{
	if (buffer == NULL || len <= 0) {
		return;
	}

	int i = 0;
	int j = 0;
	for (i = 0; i < len; i+=16) {
		printf("%06x: ", i);

		for (j = 0; j < 16; j++) {
		
			if (i + j < len) {
				printf("%s", "abc");
			} else {
				printf("   ");
			}
		}

		printf(" ");
	}
}
