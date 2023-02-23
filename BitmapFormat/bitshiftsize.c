#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	unsigned int size = 3920454;
	printf("Size in decimal: %u\n" \
			"Size in bytes array: %02x %02x %02x %02x\n", 
			size, (size>>24)&0xff, (size>>16)&0xff,
            (size>>8)&0xff, size&0xff);
	return 0;
}
