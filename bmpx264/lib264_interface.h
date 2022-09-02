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
函数功能：设置h264编码的初始化参数，宽度、高度、帧率和码率
参数：codecSettings为初始参数结构体
************************************************/
LIB264_API int InitEncode(const VideoCodec* codecSettings);
/************************************************
函数功能：将RGB（32位）编码为h264流
p_rgb_：RGB数据
ImageWidth：图像的宽度
ImageHeight：图像的高度
_buffer：编码后输出的数据
framelength：编码后一帧数据的长度
************************************************/
LIB264_API int Encode(unsigned char *p_rgb_,int ImageWidth,int ImageHeight,int DstiWidth,int DstHeight,unsigned char **_buffer,int &framelength);

LIB264_API int Encode_YUV(unsigned char *dst_y,unsigned char *dst_u,unsigned char *dst_v,int ImageWidth,int ImageHeight,unsigned char **_buffer,int &framelength);
/************************************************
函数功能：发送I帧请求
************************************************/
LIB264_API void RequestKeyFrame();
/************************************************
函数功能：编码器内存释放
************************************************/
LIB264_API int Release();

LIB264_API int RGBTOYUV420P(unsigned char *src_frame, int screen_width_, int screen_height_, int dstwidth, int dstheight, unsigned char *dst_y, unsigned char *dst_u, unsigned char *dst_v);

#endif