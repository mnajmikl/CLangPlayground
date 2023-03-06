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
		return 1;
	return 0;
}

void defaultbitmapheader(struct BitmapCoreHeader* bch)
{
	struct BitmapCoreHeader bmpheader = {
		{0x42, 0x4D}, 
		{0x0, 0x0, 0x0, 0x0},
		{0x0, 0x0},
		{0x0, 0x0},
		{0x36, 0x0, 0x0, 0x0}
	};
	memcpy(bch, &bmpheader, sizeof(struct BitmapCoreHeader));
}

void defaultdibheader(struct BitmapDIBHeader* dbh)
{
	struct BitmapDIBHeader dibheader = {
		{0x28, 0x0, 0x0, 0x0},
		{0x00, 0x0, 0x0, 0x0},
		{0x00, 0x0, 0x0, 0x0},
		{0x1, 0x0},
		{0x18, 0x0},
		{0x0, 0x0, 0x0, 0x0},
		{0x0, 0x0, 0x0, 0x0},
		{0xc4, 0xe, 0x0, 0x0},
		{0xc4, 0xe, 0x0, 0x0},
		{0x0, 0x0, 0x0, 0x0},
		{0x0, 0x0, 0x0, 0x0}
	};
	memcpy(dbh, &dibheader, sizeof(struct BitmapDIBHeader));
}

void setbitmapheadersize(struct BitmapCoreHeader* bch, const unsigned int size)
{
	bch->size[0] = size & 0xff;
	bch->size[1] = (size>>8) & 0xff;
	bch->size[2] = (size>>16) & 0xff;
	bch->size[3] = (size>>24) & 0xff;
}

void setdibheadersize(struct BitmapDIBHeader* dbh, const unsigned int size)
{
	dbh->pixelarraysize[0] = size & 0xff;
	dbh->pixelarraysize[1] = (size>>8) & 0xff;
	dbh->pixelarraysize[2] = (size>>16) & 0xff;
	dbh->pixelarraysize[3] = (size>>24) & 0xff;
}

void setbitmappixeldimensions(struct BitmapDIBHeader* dbh, const unsigned int width, const unsigned int height)
{
	dbh->pixelwidth[0] = width & 0xff;
	dbh->pixelwidth[1] = (width>>8) & 0xff;
	dbh->pixelwidth[2] = (width>>16) & 0xff;
	dbh->pixelwidth[3] = (width>>24) & 0xff;
	dbh->pixelheight[0] = height & 0xff;
	dbh->pixelheight[1] = (height>>8) & 0xff;
	dbh->pixelheight[2] = (height>>16) & 0xff;
	dbh->pixelheight[3] = (height>>24) & 0xff;
}

void getgrayscale(struct BGRColor* bgr)
{
	double newcolor = (bgr->blue * 0.11) + (bgr->green * 0.59) + (bgr->red * 0.3);
	bgr->blue = (unsigned char) newcolor;
	bgr->green = (unsigned char) newcolor;
	bgr->red = (unsigned char) newcolor;
}
