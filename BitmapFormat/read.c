#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bitmapheader.h"

int main(void)
{
	struct BitmapCoreHeader bmpheader;
	struct BitmapDIBHeader dibheader;
	FILE* bitmapfile = fopen("bitmap.bmp","rb");
	if (bitmapfile != NULL)
	{
		size_t fileheader_read = fread(&bmpheader, sizeof(struct BitmapCoreHeader), 1, bitmapfile);
		if (fileheader_read == 0)
		{
			printf("Cannot read the bitmap file header\n");
			return -1;
		}
		char sizehex[13] = {0x0};
		LE4hexstring(bmpheader.size, sizehex);
		printf("%c%c\nFile size: %s %ld bytes\n", bmpheader.tag[0], bmpheader.tag[1], sizehex, strtol(sizehex, NULL, 16));
		size_t dibheader_read = fread(&dibheader, sizeof(struct BitmapDIBHeader), 1, bitmapfile);
		if (dibheader_read == 0)
		{
			printf("Cannot read the bitmap DIB header\n");
			return -1;
		}
		LE4hexstring(dibheader.pixelwidth, sizehex);
		int imagewidth = strtol(sizehex, NULL, 16);
		printf("Pixel Width: %s %d\n", sizehex, imagewidth);
		LE4hexstring(dibheader.pixelheight, sizehex);
		int imageheight = strtol(sizehex, NULL, 16);
		printf("Pixel Height: %s %d\n", sizehex, imageheight);
		LE4hexstring(dibheader.pixelarraysize, sizehex);
		int pixelarraysize = strtol(sizehex, NULL, 16);
		printf("Pixel Array Table size: %s %d\n", sizehex, pixelarraysize);
		struct BitmapPixelArrayTable pixelcolortable;
		int numberofpaddings = ((imagewidth * 3) % 4) > 0 ? 4 - ((imagewidth * 3) % 4) : 0;
		printf("Paddings per width: %d\n", numberofpaddings);
		printf("Type a key and press Enter to continue: ");
		fgetc(stdin);
		pixelcolortable.numberofpaddings =  numberofpaddings;
		pixelcolortable.numberofcolordata = imagewidth * imageheight;
		pixelcolortable.rowscolordata = calloc(sizeof(struct BGRColor), pixelcolortable.numberofcolordata);
		if (pixelcolortable.rowscolordata == NULL)
		{
			printf("Unable to allocate memory for the pixel array table");
		}
		else
		{
			for (unsigned int i = 0; i < pixelcolortable.numberofcolordata; i++)
			{
				size_t table_read = fread(&pixelcolortable.rowscolordata[i], sizeof(struct BGRColor), 1, bitmapfile);
				if (table_read == 0)
				{
					break;
				}
				else
				{
					printf("0x%02x 0x%02x 0x%02x ", pixelcolortable.rowscolordata[i].red, pixelcolortable.rowscolordata[i].green,
							pixelcolortable.rowscolordata[i].blue);
				}
				if (((i+1) % imagewidth == 0) && (pixelcolortable.numberofpaddings > 0))
				{
					for (unsigned int j = 0; j < pixelcolortable.numberofpaddings; j++)
					{
						unsigned char padding;
						fread(&padding, sizeof(char), 1, bitmapfile);
						printf("0x%02x ", padding);
					}
				}
			}
			printf("\n");
			free(pixelcolortable.rowscolordata);
		}
		fclose(bitmapfile);
	}
	else
	{
		printf("File bitmap.bmp is not accessible.\n");
	}
	return 0;
}
