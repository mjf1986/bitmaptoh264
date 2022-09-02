#ifndef  BMPGLOBAL_H_
#define  BMPGLOBAL_H_

#include <stdio.h>

typedef struct tagBITMAPFILEHEADER
{
	unsigned char bfType[2]; //2 λͼ�ļ������ͣ�����Ϊ��BM��
	unsigned long bfSize; //4 λͼ�ļ��Ĵ�С�����ֽ�Ϊ��λ
	unsigned short int bfReserved1; //2 λͼ�ļ������֣�����Ϊ0
	unsigned short int bfReserved2; //2 λͼ�ļ������֣�����Ϊ0
	unsigned int bfOffBits; //4 λͼ���ݵ���ʼλ�ã��������λͼ�ļ�ͷ��ƫ������ʾ�����ֽ�Ϊ��λ
} BITMAPFILEHEADER;//�ýṹռ��14���ֽڡ�


typedef struct tagBITMAPINFOHEADER{
	unsigned long biSize;           //4 ���ṹ��ռ���ֽ���
	long biWidth;                   //4 λͼ�Ŀ�ȣ�������Ϊ��λ
	long biHeight;                  //4 λͼ�ĸ߶ȣ�������Ϊ��λ
	unsigned short biPlanes;        //2 Ŀ���豸��ƽ�������壬����Ϊ1
	unsigned short biBitCount;      //2 ÿ�����������λ����������1(˫ɫ), 4(16ɫ)��8(256ɫ)��24(���ɫ)֮һ
	unsigned long biCompression;    //4 λͼѹ�����ͣ������� 0(��ѹ��),1(BI_RLE8ѹ������)��2(BI_RLE4ѹ������)֮һ
	unsigned long biSizeImage;      //4 λͼ�Ĵ�С�����ֽ�Ϊ��λ
	long biXPelsPerMeter;           //4 λͼˮƽ�ֱ��ʣ�ÿ��������
	long biYPelsPerMeter;           //4 λͼ��ֱ�ֱ��ʣ�ÿ��������
	unsigned long biClrUsed;        //4 λͼʵ��ʹ�õ���ɫ���е���ɫ��
	unsigned long biClrImportant;   //4 λͼ��ʾ��������Ҫ����ɫ��
} BITMAPINFOHEADER;//�ýṹռ��40���ֽڡ�


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