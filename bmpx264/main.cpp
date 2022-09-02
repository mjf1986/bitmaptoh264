
#include "bmpglobal.h"
#include "bmpx264.h"
#include <stdlib.h>
#include <string.h>

//#include "libusb.h"
#include "lib264_interface.h"

#pragma comment(lib,"../Debug/lib264_encoder.lib")


int main(int argc, char*argv[])
{
	if (argc < 2)
	{
		printf("error argment ./main 1.bmp 2.bmp 3.bmp ......");
		exit(0);
	}

	BMPSTRUCT bmp;
	YUVSTRUCT yuv;

	FILE * file = NULL;
	FILE * yuvfile = NULL;
	FILE * h264file = NULL;

	bool  init_x264 = false;

	printf("ok\n");

	initLookupTable();//初始化查找表

	VideoCodec *m_pVideoCodec=NULL;
	unsigned char* H264Data = NULL;
	int frameLength;


	h264file = fopen("res.h264", "wb");
	yuvfile = fopen("res.yuv", "wb");


	for (int i = 1; i < argc ; ++i)
	{
		printf("file argc[%d]= %s\n", i, argv[i]);
		char temp[1024];
		strcpy(temp, argv[i]);
		file = fopen(argv[i], "rb");

		if (!file)
		{
			printf("file open failed\n");
			exit(0);
		}
		

		if (i == 1)
		{
			//yuvfile = fopen("1.yuv", "wb");
			
			memset(&bmp, 0, sizeof(BMPSTRUCT));
			memset(&yuv, 0, sizeof(YUVSTRUCT));
			//1 . read bmp info
			printf("read bmp info\n");
			if (ReadBmp(file, &bmp, &yuv) != 0)
			{
				printf("read BMP failed\n");
				break;
			}
			if (bmp.file_header.bfOffBits != 54)
			{
				printf("not 54\n");
				break;
			}

			if (InitH264Encode(m_pVideoCodec, bmp) != 0)
			{
				printf("init x264 encode failed!\n");
				break;
			}
			init_x264 = true;

			

		}
		else
		{
			printf("seek 54\n");
			fseek(file, 54, SEEK_SET);
		}

		printf("read RGB\n");
		unsigned long width = abs(bmp.width);
		unsigned long height = abs(bmp.height);
		memset(bmp.rgbData, 0, height * width * 3);
		if (ReadRGB(file, bmp.file_header, bmp.info_header, bmp.rgbData) != 0)
		{
			printf("ReadRGB failed\n");
			break;
		}
		
		printf(" RGB2YUV \n");
		memset(yuv.Y, 0, height * width);
		memset(yuv.U, 0, ((height * width) / 4));
		memset(yuv.V, 0, ((height * width) / 4));
		//rgb2yuv
		
		//RGB2YUV(bmp.width, bmp.height, bmp.rgbData, yuv.Y, yuv.U, yuv.V);
		//RGB2YUV_2(bmp.rgbData, bmp.width, bmp.height, yuv.Y, yuv.U, yuv.V);

		RGBTOYUV420P(bmp.rgbData, width, height, width, height, yuv.Y, yuv.U, yuv.V);

		WriteYuv(yuvfile, bmp, yuv);
		//fclose(yuvfile);
		
		printf("encode yuv\n");
		Encode_YUV(yuv.Y, yuv.U, yuv.V, width, height, &H264Data, frameLength);

		WriteH264(h264file, H264Data, frameLength);

		fclose(file);
		file = NULL;
		
	}

	fclose(h264file);
	fclose(yuvfile);


	if (init_x264)
	{ 
		printf("release x264\n");
		Release();
	}

	if (m_pVideoCodec)
	{
		delete m_pVideoCodec;
		m_pVideoCodec = NULL;
	}

	if (bmp.rgbData)
	{
		free(bmp.rgbData);
	}
	if (yuv.Y)
	{
		free(yuv.Y);
	}

	if (yuv.U)
	{
		free(yuv.U);
	}
	if (yuv.V)
	{
		free(yuv.V);
	}

	return 0;
}