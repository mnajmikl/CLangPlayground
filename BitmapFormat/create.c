#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bitmapheader.h"
#define WIDTH 31
#define HEIGHT 31

int main(void)
{
	struct BitmapCoreHeader bmpheader;
	struct BitmapDIBHeader dibheader;
	struct BitmapPixelArrayTable bitmapdata;
	defaultbitmapheader(&bmpheader);
	defaultdibheader(&dibheader);
    	bitmapdata.numberofpaddings = ((WIDTH * 3) % 4) > 0 ? 4 - ((WIDTH * 3) % 4) : 0;
	bitmapdata.numberofcolordata = WIDTH * HEIGHT;
	int pixelarraytablesize = ((WIDTH * 3) + bitmapdata.numberofpaddings) * HEIGHT;
	setbitmapheadersize(&bmpheader, 54 + pixelarraytablesize);
	setdibheadersize(&dibheader, pixelarraytablesize);
	setbitmappixeldimensions(&dibheader, WIDTH, HEIGHT);
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
		printf("File bitmap.bmp has been created\n");
		fclose(bitmapfile);
	}
	free(bitmapdata.rowscolordata);
	return 0;
}
