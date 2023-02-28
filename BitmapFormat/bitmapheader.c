#include <stdio.h>
#include <string.h>
#include "bitmapheader.h"

int LE4hexstring(const unsigned char* hexarray, char* hexstr)
{
	char hex[3] = {0x0};
	char sizehex[13] = {0x0};
	strcat(sizehex, "0x");
	for(int i = 3; i >= 0; i--)
	{
		sprintf(hex, "%02x", hexarray[i]);
		strcat(sizehex, hex);
	}
	if(strcpy(hexstr, sizehex) != NULL)
		return 0;
	return -1;
}