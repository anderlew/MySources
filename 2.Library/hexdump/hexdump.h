//: start of hexdump.h
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/**
  *
  * Usage:
  *     char *str = "hello";
  *     hexdump(str, 5);
  */
void hexdump(void *ptr, int buflen) {
    unsigned char *buf = (unsigned char*)ptr;
    int i, j;
    for (i=0; i<buflen; i+=16) {
        // Print offset number
        printf("%06x: ", i);

        // Print hex value
        for (j=0; j<16; j++) {
            if (i+j < buflen) {
                printf("%02x ", buf[i+j]);
            } else {
                printf("   ");
            }

            printf(" ");
        }

        // Print character value
        for (j=0; j<16; j++) {
            if (i+j < buflen) {
                printf("%c", isprint(buf[i+j]) ? buf[i+j] : '.');
            }
        }

        printf("\n");
    }
}

/**
  *
  * Usage:
  *     char *str = "hello";
  *     hexdump2("str=", str, 5);
  */
void hexdump2(char *desc, void *addr, int len) {
    int i;
    unsigned char buff[17];
    unsigned char *pc = (unsigned char*)addr;

    // Output description if given.
    if (desc != NULL)
        printf ("%s:\n", desc);

    // Process every byte in the data.
    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Just don't print ASCII for the zeroth line.
            if (i != 0)
                printf ("  %s\n", buff);

            // Output the offset.
            printf ("  %04x ", i);
        }

        // Now the hex code for the specific character.
        printf (" %02x", pc[i]);

        // And store a printable ASCII character for later.
        if ((pc[i] < 0x20) || (pc[i] > 0x7e))
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.
    while ((i % 16) != 0) {
        printf ("   ");
        i++;
    }

    // And print the final ASCII bit.
    printf ("  %s\n", buff);
}

//: end of hexdump.h
