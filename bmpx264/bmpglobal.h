#ifndef  BMPGLOBAL_H_
#define  BMPGLOBAL_H_

#include <stdio.h>

typedef struct tagBITMAPFILEHEADER
{
	unsigned char bfType[2]; //2 位图文件的类型，必须为“BM”
	unsigned long bfSize; //4 位图文件的大小，以字节为单位
	unsigned short int bfReserved1; //2 位图文件保留字，必须为0
	unsigned short int bfReserved2; //2 位图文件保留字，必须为0
	unsigned int bfOffBits; //4 位图数据的起始位置，以相对于位图文件头的偏移量表示，以字节为单位
} BITMAPFILEHEADER;//该结构占据14个字节。


typedef struct tagBITMAPINFOHEADER{
	unsigned long biSize;           //4 本结构所占用字节数
	long biWidth;                   //4 位图的宽度，以像素为单位
	long biHeight;                  //4 位图的高度，以像素为单位
	unsigned short biPlanes;        //2 目标设备的平面数不清，必须为1
	unsigned short biBitCount;      //2 每个像素所需的位数，必须是1(双色), 4(16色)，8(256色)或24(真彩色)之一
	unsigned long biCompression;    //4 位图压缩类型，必须是 0(不压缩),1(BI_RLE8压缩类型)或2(BI_RLE4压缩类型)之一
	unsigned long biSizeImage;      //4 位图的大小，以字节为单位
	long biXPelsPerMeter;           //4 位图水平分辨率，每米像素数
	long biYPelsPerMeter;           //4 位图垂直分辨率，每米像素数
	unsigned long biClrUsed;        //4 位图实际使用的颜色表中的颜色数
	unsigned long biClrImportant;   //4 位图显示过程中重要的颜色数
} BITMAPINFOHEADER;//该结构占据40个字节。


typedef struct
{
	BITMAPFILEHEADER file_header;
	BITMAPINFOHEADER info_header;
	//unsigned long width, height;
	long width, height;
	unsigned char *rgbData;

}BMPSTRUCT;

typedef struct
{
	unsigned char *Y, *U, *V;

}YUVSTRUCT;





#endif