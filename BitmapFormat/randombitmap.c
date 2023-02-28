#include <stdio.h>
#include "bitmapheader.h"

int main(void)
{
	struct BitmapCoreHeader bmpheader;
	struct BitmapDIBHeader dibheader;
	struct BitmapPixelArrayTable bitmapdata;
	
	FILE* bitmapfile = fopen("bitmap.bmp","wb");
	
	if (bitmapfile != NULL)
	{
		fwrite(&bmpheader, sizeof(struct BitmapCoreHeader), 1, bitmapfile);
		fwrite(&dibheader, sizeof(struct BitmapDIBHeader), 1, bitmapfile);
		fwrite(bitmapdata.rowscolordata, sizeof(struct BGRColor), bitmapdata.numberofcolordata, bitmapfile);
	}
	else
	{
		return -1;
	}
	fclose(bitmapfile);
	return 0;
}
