#include <stdio.h>

struct BMPHeader
{
	char tag[2];
	char size[4];
	char padding1[2];
	char padding2[2];
	char offset[4];
};

struct DIBHeader
{
	char header[4];
	char pixelwidth[4];
	char pixelheight[4];
	char planes[2];
	char bitperpixel[2];
	char compressionmethod[4];
	char imagesize[4];
	char horizontalres[4];
	char verticalres[4];
	char colorpalette[4];
	char importantcolors[4];
}

struct BitmapData
{
	char* color[3];
	char padding[2];
};

int main(void)
{
	struct BMPHeader bmpheader;
	struct DIBHeader dibheader;
	struct BitmapData bitmapdata;
	
	FILE* bitmapfile = fopen("bitmap.bmp","wb");
	
	if (bitmapfile != NULL)
	{
		fwrite(&bmpheader, sizeof(struct BMPHeader), 1, bitmapfile);
		fwrite(&dibheader, sizeof(struct DIBHeader), 1, bitmapfile);
		fwrite(&bitmapdata, sizeof(struct BitmapData), 1, bitmapfile);
	}
	else
	{
		return -1;
	}
	fclose(bitmapfile);
	return 0;
}
