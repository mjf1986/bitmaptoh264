#ifndef COMMON_STRUCT_H_
#define COMMON_STRUCT_H_
struct VideoCodec {
	unsigned short      width;
	unsigned short      height;
	unsigned int        targetBitrate;  // kilobits/sec.
	unsigned char       mFramerate;
};
#endif