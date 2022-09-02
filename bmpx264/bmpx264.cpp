
#include "bmpglobal.h"
#include "bmpx264.h"


#include <stdlib.h>
#include <string.h>
#include <math.h>

float RGBYUV02990[256], RGBYUV05870[256], RGBYUV01140[256];
float RGBYUV01684[256], RGBYUV03316[256];
float RGBYUV04187[256], RGBYUV00813[256];

int biHeightDirect;

void initLookupTable()
{
	for (int i = 0; i < 256; i++)
	{
		RGBYUV02990[i] = (float)0.2990 * i;
		RGBYUV05870[i] = (float)0.5870 * i;
		RGBYUV01140[i] = (float)0.1140 * i;
		RGBYUV01684[i] = (float)0.1684 * i;
		RGBYUV03316[i] = (float)0.3316 * i;
		RGBYUV04187[i] = (float)0.4187 * i;
		RGBYUV00813[i] = (float)0.0813 * i;
	}
}
static int readfileandinfo(FILE *bmpFile, BITMAPFILEHEADER & file_header, BITMAPINFOHEADER & info_header)
{
	/*
	typedef struct tagBITMAPFILEHEADER
	{
	unsigned char bfType[2]; //2 位图文件的类型，必须为“BM”
	unsigned long bfSize; //4 位图文件的大小，以字节为单位
	unsigned short int bfReserved1; //2 位图文件保留字，必须为0
	unsigned short int bfReserved2; //2 位图文件保留字，必须为0
	unsigned int bfOffBits; //4 位图数据的起始位置，以相对于位图文件头的偏移量表示，以字节为单位
	} BITMAPFILEHEADER;//该结构占据14个字节。

	*/
	//
	fread(&file_header.bfType[0], 1, 1, bmpFile);
	printf("类型为%c", file_header.bfType[0]);
	fread(&file_header.bfType[1], 1, 1, bmpFile);
	printf("%c\n", file_header.bfType[1]);

	if (file_header.bfType[0] != 'B' && file_header.bfType[1] != 'M')
	{
		printf("It's not bmp file\n");
		return -1;
	}

	fread(&file_header.bfSize, 4, 1, bmpFile);
	printf("文件长度为%d\n", file_header.bfSize);

	printf("sizeof(short int) = %d\n", sizeof(short int));
	fread(&file_header.bfReserved1, 2, 1, bmpFile);
	printf("保留字1为%d\n", file_header.bfReserved1);

	fread(&file_header.bfReserved2, 2, 1, bmpFile);
	printf("保留字2为%d\n", file_header.bfReserved2);

	printf("sizeof(long) = %d\n", sizeof(long));
	fread(&file_header.bfOffBits, 4, 1, bmpFile);
	printf("偏移量为%d\n", file_header.bfOffBits);
	if (file_header.bfOffBits != 54)
	{
		printf("bfOffBits is not 54\n");
	}

	/*
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
	*/


	fread(&info_header.biSize, 4, 1, bmpFile);
	printf("此结构大小为%d\n", info_header.biSize);

	fread(&info_header.biWidth, 4, 1, bmpFile);
	printf("位图的宽度为%d\n", info_header.biWidth);
	

	fread(&info_header.biHeight, 4, 1, bmpFile);
	printf("位图的高度为%d\n", info_header.biHeight);
	

	fread(&info_header.biPlanes, 2, 1, bmpFile);
	printf("目标设备位图数%d\n", info_header.biPlanes);

	fread(&info_header.biBitCount, 2, 1, bmpFile);
	printf("颜色深度为%d\n", info_header.biBitCount);

	fread(&info_header.biCompression, 4, 1, bmpFile);
	printf("位图压缩类型%d\n", info_header.biCompression);
	fread(&info_header.biSizeImage, 4, 1, bmpFile);
	printf("位图大小%d\n", info_header.biSizeImage);
	fread(&info_header.biXPelsPerMeter, 4, 1, bmpFile);
	printf("位图水平分辨率为%d\n", info_header.biXPelsPerMeter);
	fread(&info_header.biYPelsPerMeter, 4, 1, bmpFile);
	printf("位图垂直分辨率为%d\n", info_header.biYPelsPerMeter);
	fread(&info_header.biClrUsed, 4, 1, bmpFile);
	printf("位图实际使用颜色数%d\n", info_header.biClrUsed);
	fread(&info_header.biClrImportant, 4, 1, bmpFile);
	printf("位图显示中比较重要颜色数%d\n", info_header.biClrImportant);

	return 0;
}
int ReadBmp(FILE *bmpFile, BMPSTRUCT * bmpstruct, YUVSTRUCT * yuv)
{

	if (readfileandinfo(bmpFile, bmpstruct->file_header, bmpstruct->info_header) != 0)
	{
		printf("read bmp file info and info header error!\n");
		return -1;
	}
	biHeightDirect = 0;
	if (bmpstruct->info_header.biHeight < 0) {
		biHeightDirect = 1;
	}

	bmpstruct->info_header.biHeight = abs(bmpstruct->info_header.biHeight);

	if (((bmpstruct->info_header.biWidth / 8 * bmpstruct->info_header.biBitCount) % 4) == 0)
		bmpstruct->width = bmpstruct->info_header.biWidth;
	else
		bmpstruct->width = (bmpstruct->info_header.biWidth*bmpstruct->info_header.biBitCount + 31) / 32 * 4;

	if ((bmpstruct->info_header.biHeight % 2) == 0)
		bmpstruct->height = bmpstruct->info_header.biHeight;
	else
		bmpstruct->height = bmpstruct->info_header.biHeight + 1;

	bmpstruct->rgbData = (unsigned char *)malloc(bmpstruct->height*bmpstruct->width * 3);
	if (!bmpstruct->rgbData)
	{
		printf("malloc failed\n");
		return -1;
	}
	memset(bmpstruct->rgbData, 0, bmpstruct->height * bmpstruct->width * 3);

	yuv->Y = (unsigned char *)malloc(bmpstruct->height*bmpstruct->width);
	if (!yuv->Y)
	{
		printf("malloc  Y failed\n");
		return -1;
	}
	yuv->U = (unsigned char *)malloc((bmpstruct->height * bmpstruct->width) / 4);
	if (!yuv->U)
	{
		printf("malloc  U failed\n");
		return -1;
	}
	yuv->V = (unsigned char *)malloc((bmpstruct->height * bmpstruct->width) / 4);
	if (!yuv->V)
	{
		printf("malloc V failed\n");
		return -1;
	}

	printf("This is a %d bits image!\n", bmpstruct->info_header.biBitCount);
	printf("\nbmp size: \t%d X %d\n\n", bmpstruct->info_header.biWidth, bmpstruct->info_header.biHeight);	
	return 0;
}

int ReadRGB(FILE * pFile, BITMAPFILEHEADER & file_h, BITMAPINFOHEADER & info_h, unsigned char * rgbDataOut)
{
	unsigned long Loop, iLoop, jLoop, width, height, w, h;
	unsigned char mask, *Index_Data, *Data;

	if (((info_h.biWidth / 8 * info_h.biBitCount) % 4) == 0)
		w = info_h.biWidth;
	else
		w = (info_h.biWidth*info_h.biBitCount + 31) / 32 * 4;
	if ((info_h.biHeight % 2) == 0)
		h = info_h.biHeight;
	else
		h = info_h.biHeight + 1;

	width = w / 8 * info_h.biBitCount;
	height = h;

	Index_Data = (unsigned char *)malloc(height*width);
	Data = (unsigned char *)malloc(height*width);

	fseek(pFile, file_h.bfOffBits, 0);
	if (fread(Index_Data, height*width, 1, pFile) != 1)
	{
		printf("read file error!\n\n");
		return -1;
	}

	if (0 == biHeightDirect) {
		for (iLoop = 0; iLoop < height; iLoop++)
		{
			for (jLoop = 0; jLoop < width; jLoop++)
			{
				Data[iLoop * width + jLoop] = Index_Data[(height - iLoop - 1) * width + jLoop];
			}
		}
	}
	else {
		for (iLoop = 0; iLoop < height; iLoop++)
		{
			for (jLoop = 0; jLoop < width; jLoop++)
			{
				Data[(height - iLoop) * width + jLoop] = Index_Data[(height - iLoop - 1) * width + jLoop];
			}
		}
	}

	switch (info_h.biBitCount)
	{
		case 24:
			memcpy(rgbDataOut, Data, height*width);
			if (Index_Data)
				free(Index_Data);
			if (Data)
				free(Data);
			return 0;
	}
	return 0;

}
//////////////////////////////////////////////////////////////////////////  
//              rgb转yuv420  
//////////////////////////////////////////////////////////////////////////
bool  RGB2YUV_2(unsigned char * RgbBuf, unsigned long nWidth, unsigned long nHeight, unsigned char * y, unsigned char * u, unsigned char *v)
{
	return true;
}

int RGB2YUV(unsigned long w, unsigned long h, unsigned char * rgbData, unsigned char * y, unsigned char * u, unsigned char *v)
{	
	unsigned char *ytemp = NULL;
	unsigned char *utemp = NULL;
	unsigned char *vtemp = NULL;
	utemp = (unsigned char *)malloc(w*h);
	vtemp = (unsigned char *)malloc(w*h);

	unsigned long i, nr, ng, nb, nSize;
	//对每个像素进行 rgb -> yuv的转换
	for (i = 0, nSize = 0; nSize < w*h * 3; nSize += 3)
	{
		nb = rgbData[nSize];
		ng = rgbData[nSize + 1];
		nr = rgbData[nSize + 2];
		y[i] = (unsigned char)(RGBYUV02990[nr] + RGBYUV05870[ng] + RGBYUV01140[nb]);
		utemp[i] = (unsigned char)(-RGBYUV01684[nr] - RGBYUV03316[ng] + nb / 2 + 128);
		vtemp[i] = (unsigned char)(nr / 2 - RGBYUV04187[ng] - RGBYUV00813[nb] + 128);
		i++;
	}
	//对u信号及v信号进行采样
	int k = 0;
	for (i = 0; i < h; i += 2)
		for (unsigned long j = 0; j < w; j += 2)
		{
			u[k] = (utemp[i*w + j] + utemp[(i + 1)*w + j] + utemp[i*w + j + 1] + utemp[(i + 1)*w + j + 1]) / 4;
			v[k] = (vtemp[i*w + j] + vtemp[(i + 1)*w + j] + vtemp[i*w + j + 1] + vtemp[(i + 1)*w + j + 1]) / 4;
			k++;
		}
	//对y、u、v 信号进行抗噪处理
	for (i = 0; i < w*h; i++)
	{
		if (y[i] < 16)
			y[i] = 16;
		if (y[i] > 235)
			y[i] = 235;
	}
	for (i = 0; i < h*w / 4; i++)
	{
		if (u[i] < 16)
			u[i] = 16;
		if (v[i] < 16)
			v[i] = 16;
		if (u[i] > 240)
			u[i] = 240;
		if (v[i] > 240)
			v[i] = 240;
	}
	if (utemp)
		free(utemp);
	if (vtemp)
		free(vtemp);
	return 0;
}

int  WriteYuv(FILE *outFile, BMPSTRUCT &bmp, YUVSTRUCT & yuv)
{
	unsigned int size = bmp.width*bmp.height;

	if (fwrite(yuv.Y, 1, size, outFile) != size)
		return -1;
	if (fwrite(yuv.U, 1, size / 4, outFile) != size / 4)
		return -1;
	if (fwrite(yuv.V, 1, size / 4, outFile) != size / 4)
		return -1;
	return 1;
}
int  WriteH264(FILE *outFile, unsigned char* H264Data, int frameLength)
{

	if (fwrite(H264Data, 1, frameLength, outFile) != frameLength)
		return -1;


	return 0;
}


int InitH264Encode(VideoCodec *m_pVideoCodec, BMPSTRUCT & bmp)
{
	if (m_pVideoCodec)
	{
		delete m_pVideoCodec;
		m_pVideoCodec = NULL;
	}

	m_pVideoCodec = new VideoCodec;
	if (!m_pVideoCodec)
	{
		printf("new VideoCodec failed\n");
		return -1; 
	}
	m_pVideoCodec->mFramerate = 10;
	m_pVideoCodec->targetBitrate = 500;
	m_pVideoCodec->width = bmp.width;
	m_pVideoCodec->height = bmp.height;

	int nResult = InitEncode(m_pVideoCodec);
	if (nResult != 0)
	{
		printf("init x264 encode failed\n");
		return -1;
	}
	return 0;

}