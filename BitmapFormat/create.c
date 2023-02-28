#include <stdlib.h>
#include <time.h>
#include "bitmapheader.h"
#define WIDTH 31

int main(void)
{
	struct BitmapCoreHeader bmpheader = {
		{0x42, 0x4D}, 
		{0xd6, 0xb, 0x0, 0x0},
		{0x0, 0x0},
		{0x0, 0x0},
		{0x36, 0x0, 0x0, 0x0}
	};
	struct BitmapDIBHeader dibheader = {
		{0x28, 0x0, 0x0, 0x0},
		{0x1f, 0x0, 0x0, 0x0},
		{0x1f, 0x0, 0x0, 0x0},
		{0x1, 0x0},
		{0x18, 0x0},
		{0x0, 0x0, 0x0, 0x0},
		{0xa0, 0xb, 0x0, 0x0},
		{0xc4, 0xe, 0x0, 0x0},
		{0xc4, 0xe, 0x0, 0x0},
		{0x0, 0x0, 0x0, 0x0},
		{0x0, 0x0, 0x0, 0x0}
	};
	struct BitmapPixelArrayTable bitmapdata;
	/* 32 for width is a hard coded number. 
	 * Get the actual number from dibheader.pixelwidth by doing some bitshift + sprintf + strtoll
	 */
    bitmapdata.numberofpaddings = ((WIDTH * 3) % 4) > 0 ? 4 - ((WIDTH * 3) % 4) : 0;
	bitmapdata.numberofcolordata = WIDTH * WIDTH;
	bitmapdata.rowscolordata = calloc(sizeof(struct BGRColor), bitmapdata.numberofcolordata);
	if (bitmapdata.rowscolordata == NULL)
	{
		printf("Failed to allocate memory for bitmap data");
		return -1;
	}
	else
	{
		srand((unsigned int)time(NULL));
		for (int i = bitmapdata.numberofcolordata - 1; i >= 0; i--)
		{
			bitmapdata.rowscolordata[i].blue = (unsigned char) rand() % 255;
			bitmapdata.rowscolordata[i].green = (unsigned char) rand() % 255;
			bitmapdata.rowscolordata[i].red = (unsigned char) rand() % 255;
		}
	}
	FILE* bitmapfile = fopen("bitmap.bmp","wb");
	if (bitmapfile != NULL)
	{
		fwrite(&bmpheader, sizeof(struct BitmapCoreHeader), 1, bitmapfile);
		fwrite(&dibheader, sizeof(struct BitmapDIBHeader), 1, bitmapfile);
		for (unsigned int p = 0; p < bitmapdata.numberofcolordata; p++)
		{
			fwrite(&bitmapdata.rowscolordata[p], sizeof(struct BGRColor), 1, bitmapfile);
			if (((p+1) % WIDTH == 0) && (bitmapdata.numberofpaddings > 0))
			{
				for (unsigned int j = 0; j < bitmapdata.numberofpaddings; j++)
				{
					unsigned char paddings = 0x0;
					fwrite(&paddings, sizeof(char), 1, bitmapfile);
				}
			}
		}
		fclose(bitmapfile);
	}
	free(bitmapdata.rowscolordata);
	return 0;
}
