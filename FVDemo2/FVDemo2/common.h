#ifndef _FINGER_VEIN_COMMON_H_
#define _FINGER_VEIN_COMMON_H_

int WriteBitmapHeader(BYTE *Buffer, int Width, int Height);

int WriteBitmap(BYTE *buffer, int Width, int Height, char *file);

HBITMAP BuildImage(BYTE *image, int width, int height);

int  Zoom(BYTE *lpSrcDib,BYTE *lpDstDib, long lWidth, long lHeight,
	long lDstWidth,long lDstHeight);

void rotate90(BYTE *Srcbmp, BYTE *Dstbmp,int width, int height);

BOOL is_digit(const TCHAR *str);
void ConvertImage( unsigned char *src,unsigned char *dst,int sw,int sh,int width,int height,int rotaImage);

#endif	//_FINGER_VEIN_COMMON_H_