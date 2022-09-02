#ifndef BMPX264_H_
#define BMPX264_H_

#include <stdio.h>
#include "bmpglobal.h"
#include "lib264_interface.h"

void initLookupTable();
int ReadBmp(FILE *bmpFile, BMPSTRUCT * bmpstruct, YUVSTRUCT * yuv);
int ReadRGB(FILE * pFile, BITMAPFILEHEADER & file_h, BITMAPINFOHEADER & info_h, unsigned char * rgbDataOut);
int RGB2YUV(unsigned long w, unsigned long h, unsigned char * rgbData, unsigned char * y, unsigned char * u, unsigned char *v);
int  WriteYuv(FILE *outFile, BMPSTRUCT &bmp, YUVSTRUCT & yuv);
int  WriteH264(FILE *outFile, unsigned char* H264Data, int frameLength);

int InitH264Encode(VideoCodec *m_pVideoCodec, BMPSTRUCT & bmp);

#endif