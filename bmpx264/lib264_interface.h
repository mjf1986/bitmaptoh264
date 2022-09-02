#ifndef LIB264_INTERFACE_H
#define LIB264_INTERFACE_H
#ifdef WIN32
#ifdef  LIB264_EXPORTS
#define LIB264_API __declspec(dllexport)
#else
#define LIB264_API __declspec(dllimport)
#endif
#else
#define LIB264_API extern
#endif
#include "common_struct.h"
/************************************************
�������ܣ�����h264����ĳ�ʼ����������ȡ��߶ȡ�֡�ʺ�����
������codecSettingsΪ��ʼ�����ṹ��
************************************************/
LIB264_API int InitEncode(const VideoCodec* codecSettings);
/************************************************
�������ܣ���RGB��32λ������Ϊh264��
p_rgb_��RGB����
ImageWidth��ͼ��Ŀ��
ImageHeight��ͼ��ĸ߶�
_buffer����������������
framelength�������һ֡���ݵĳ���
************************************************/
LIB264_API int Encode(unsigned char *p_rgb_,int ImageWidth,int ImageHeight,int DstiWidth,int DstHeight,unsigned char **_buffer,int &framelength);

LIB264_API int Encode_YUV(unsigned char *dst_y,unsigned char *dst_u,unsigned char *dst_v,int ImageWidth,int ImageHeight,unsigned char **_buffer,int &framelength);
/************************************************
�������ܣ�����I֡����
************************************************/
LIB264_API void RequestKeyFrame();
/************************************************
�������ܣ��������ڴ��ͷ�
************************************************/
LIB264_API int Release();

LIB264_API int RGBTOYUV420P(unsigned char *src_frame, int screen_width_, int screen_height_, int dstwidth, int dstheight, unsigned char *dst_y, unsigned char *dst_u, unsigned char *dst_v);

#endif