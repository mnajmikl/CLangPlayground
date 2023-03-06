#include <stdio.h>
#include <stdlib.h>
#include "bitmapheader.h"

int main(void)
{
	struct BitmapCoreHeader bmpheader;
	struct BitmapDIBHeader dibheader;
	FILE* grayscale = fopen("grayscale.bmp","wb");
	if (grayscale == NULL)
	{
		printf("File grayscale.bmp is not accessible.\n");
		return -1;
	}
	FILE* bitmapfile = fopen("bitmap.bmp","rb");
	if (bitmapfile != NULL)
	{
		size_t fileheader_read = fread(&bmpheader, sizeof(struct BitmapCoreHeader), 1, bitmapfile);
		if (fileheader_read == 0)
		{
			printf("Cannot read the bitmap file header\n");
			return -2;
		}
		fwrite(&bmpheader, sizeof(struct BitmapCoreHeader), 1, grayscale);
		size_t dibheader_read = fread(&dibheader, sizeof(struct BitmapDIBHeader), 1, bitmapfile);
		if (dibheader_read == 0)
		{
			printf("Cannot read the bitmap DIB header\n");
			return -3;
		}
		fwrite(&dibheader, sizeof(struct BitmapDIBHeader), 1, grayscale);
		char sizehex[13] = {0x0};
		LE4hexstring(dibheader.pixelwidth, sizehex);
		int imagewidth = strtol(sizehex, NULL, 16);
		LE4hexstring(dibheader.pixelheight, sizehex);
		int imageheight = strtol(sizehex, NULL, 16);
		struct BitmapPixelArrayTable pixelcolortable;
		int numberofpaddings = ((imagewidth * 3) % 4) > 0 ? 4 - ((imagewidth * 3) % 4) : 0;
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
					getgrayscale(&pixelcolortable.rowscolordata[i]);
					fwrite(&pixelcolortable.rowscolordata[i], sizeof(struct BGRColor), 1, grayscale);
				}
				if (((i+1) % imagewidth == 0) && (pixelcolortable.numberofpaddings > 0))
				{
					unsigned char padding = {0x0};
					fread(&padding, sizeof(char), pixelcolortable.numberofpaddings, bitmapfile);
					fwrite(&padding, sizeof(char), pixelcolortable.numberofpaddings, grayscale);
				}
			}
			free(pixelcolortable.rowscolordata);
			printf("Grayscale bitmap grayscale.bmp has been created.\n");
		}
		fclose(grayscale);
		fclose(bitmapfile);
	}
	else
	{
		printf("File bitmap.bmp is not accessible.\n");
	}
	return 0;
}
