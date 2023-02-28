#ifndef __BITMAPFILEHEADER__
#define __BITMAPFILEHEADER__

/*
 * Format of Windows BITMAPCOREHEADER
 * Total of 14 bytes
 */
struct BitmapCoreHeader
{
	/* The ID is always 'B','M' {0x42, 0x4D} */
	unsigned char tag[2];
	/*
	 * Update this last because it reflects the actual file size
	 * (BITMAPCOREHEADER 14 + BITMAPINFOHEADER 40) 54 + actual pixel array data size in bytes
	 * Little endian (the first byte are the last digits)
	 * e.g {0x46, 0xd2, 0x3b, 0x0} will be read as 0x003bd246 = 3920454
 	 */
	unsigned char size[4];
	/* Application specific data, usually {0x0, 0x0} */
	unsigned char padding1[2];
	/* Application specific data, usually {0x0, 0x0} */
	unsigned char padding2[2];
	/*
	 * The offset/starting address of the pixel array after
	 * BITMAPCOREHEADER 14 + BITMAPINFOHEADER 40 = 54 = 0x36 {0x36 0x0 0x0 0x0}
	 * Little endian (the first byte are the last digits)
	 * e.g {0x36, 0x0, 0x0, 0x0} will be read as 0x00000036 = 54
	 */
	unsigned char offset[4];
};

/*
 * Format of Windows BITMAPINFOHEADER
 * 40 bytes bytes
 */
struct BitmapDIBHeader
{
	/*
	 * The header size is always 40 (28 00 00 00) bytes
	 * Little endian (the first byte are the last digits)
	 * e.g {0x28, 0x0, 0x0, 0x0} will be read as 0x00000028 = 40
	 */
	unsigned char header[4];
	/*
	 * Pixel width i.e. X plane (columns, left to right)
	 * Little endian (the first byte are the last digits)
	 * e.g {0x38, 0x4, 0x0, 0x0} will be read as 0x00000438 = 1080
	 */
	unsigned char pixelwidth[4];
	/*
	 * Pixel height i.e. Y plane (rows, top to bottom)
	 * Little endian (the first byte are the last digits)
	 * e.g {0xBA, 0x04, 0x0, 0x0} will be read as 0x000004BA = 1210
	 */
	unsigned char pixelheight[4];
	/*
	 * Color plane usually 1
	 * Little endian (the first byte are the last digits)
	 * e.g {0x1, 0x0} will be read as 0x0001 = 1
	 */
	unsigned char planes[2];
	/*
	 * Number of bits per pixel i.e. 1, 8, 16, 24 or 32 bits
	 * Little endian (the first byte are the last digits)
	 * e.g {0x18, 0x0} will be read as 0x0018 = 24
	 */
	unsigned char bitperpixel[2];
	/*
	 * Pixel array compression type
	 * Little endian (the first byte are the last digits)
	 * e.g {0x0, 0x0, 0x0, 0x0} will be read as 0x00000000 = 0, no compression
	 */
	unsigned char compressionmethod[4];
	/*
	 * Actual pixel array data size in bytes
	 * Little endian (the first byte are the last digits)
	 * e.g {0x10, 0xd2, 0x3b, 0x0} will be read as 0x003bd210 = 3920400
 	 */
	unsigned char pixelarraysize[4];
	/*
	 * Horizontal pixels per meter 39.3701 x DPI i.e. 72 or 96 (rounded to the highest integer)
	 * Little endian (the first byte are the last digits)
	 * e.g {0xc4, 0xe, 0x0, 0x0} will be read as 0x00000ec4 = 3780
 	 */
	unsigned char horizontalres[4];
	/*
	 * Vertical pixels per meter 39.3701 x DPI i.e. 72 or 96 (rounded to the highest integer)
	 * Little endian (the first byte are the last digits)
	 * e.g {0xc4, 0xe, 0x0, 0x0} will be read as 0x00000ec4 = 3780
 	 */
	unsigned char verticalres[4];
	/*
	 * Number of colors in the color palette. Default is 0 2^(bit per pixel)
	 * Little endian (the first byte are the last digits)
	 * e.g {0x0, 0x0, 0x0, 0x0} will be read as 0x00000000  = 0 (default)
 	 */
	unsigned char colorpalette[4];
	/*
	 * Number of important colors used. Default is 0 (all colors are important)
	 * Little endian (the first byte are the last digits)
	 * e.g {0x0, 0x0, 0x0, 0x0} will be read as 0x00000000  = 0 (default)
 	 */
	unsigned char importantcolors[4];
};

struct BGRColor
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
};

struct BitmapPixelArrayTable
{
	/*
	 * The actual pixel array data
	 * RGB colordata for each x,y 
	 * Start from bottom most left to its right, and then row moves up
	 * i.e. 5 pixel width, 3 pixel height
	 * the movement would be
	 *        col0  col1  col2  col3  col4 
	 * row 2: 0,2   1,2   2,2   3,2   4,2  ↓ bottom row
	 * row 1: 0,1   1,1   2,1   3,1   4,1  ↓ move one row up
	 * row 0: 0,0   1,0   2,0   3,0   4,0  ↓ upmost row                          
	 *        left → right
	 */
	struct BGRColor* rowscolordata;
	/*
	 * Total number of color data for rowscolordata (width * height * 3)
	 */
	unsigned int numberofcolordata;
	/*
	 * Total number of required paddings
	 * Paddings to fill sequence of 4 bytes
	 * e.g. dimension 5 width 3 height = 15
	 * Color bytes = dimension * 3 = 45
	 * Paddings : (Color bytes % 4) == 0 ? 0 : 4 - (Color bytes % 4)
	 * Each padding value is 0x0
	 */
	unsigned int numberofpaddings;
};
#endif
