#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	unsigned char header[] = {'B', 'M'};
	unsigned char size[] = {0xff, 0xff, 0xff, 0xff}; /* {0x46, 0xd2, 0x3b, 0x0}; */
	char hex[3];
    char sizehex[11] = {0x0};
	printf("Header in ASCII: %c %c\nASCII value: %d %d\nHex values: %x %x\n",
			header[0], header[1],
			header[0], header[1],
			header[0], header[1]);
	printf("File size in header: %02x %02x %02x %02x\n", size[0], size[1], size[2], size[3]);
    for(int i = 3; i >=0; i--)
    {
        sprintf(hex, "%02x", size[i]);
        strcat(sizehex, hex);
    }
	printf("Decoded file size in header: 0x%s\nFile size in bytes: %lu bytes\n", 
			sizehex, strtoll(sizehex, NULL, 16));
	printf("File size in MiB: %lu", strtoll(sizehex, NULL, 16) / 1024 / 1024);
	return 0;
}
