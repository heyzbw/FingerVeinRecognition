#include "stdafx.h"
#include "common.h"

int WriteBitmapHeader(BYTE *Buffer, int Width, int Height)
{
	BITMAPFILEHEADER *bmpfheader=(BITMAPFILEHEADER *)Buffer;
	BITMAPINFO *bmpinfo=(BITMAPINFO *)(((char*)bmpfheader)+14);
	int i,w;
	memset(bmpfheader,0,0x500);
	bmpfheader->bfType =19778;
	w = ((Width+3)/4)*4*Height+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFO)+255*sizeof(RGBQUAD);
	memcpy((void*)(((char*)bmpfheader)+2), &w, 4);
	//bmpfheader->bfOffBits;
	w= sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFO)+255*sizeof(RGBQUAD);
	memcpy((void*)(((char*)bmpfheader)+10), &w, 4);
	bmpinfo->bmiHeader.biWidth=Width;
	bmpinfo->bmiHeader.biHeight=Height;
	bmpinfo->bmiHeader.biBitCount=8;
	bmpinfo->bmiHeader.biClrUsed=0;
	bmpinfo->bmiHeader.biSize=sizeof(bmpinfo->bmiHeader);
	bmpinfo->bmiHeader.biPlanes=1;
	bmpinfo->bmiHeader.biSizeImage=((Width+3)/4)*4*Height;
	for(i=1;i<256;i++)
	{
		bmpinfo->bmiColors[i].rgbBlue=i;
		bmpinfo->bmiColors[i].rgbGreen=i;
		bmpinfo->bmiColors[i].rgbRed=i;
	}
	return sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+256*sizeof(RGBQUAD);
}

int WriteBitmap(BYTE *buffer, int Width, int Height, char *file)
{
	FILE *f=fopen(file, "wb");
	if(f)
	{
		unsigned char Buffer[0x500];
		int i, w=WriteBitmapHeader(Buffer, Width, Height);
		fwrite(Buffer, w, 1, f);
		w = ((Width+3)/4)*4;
		buffer+=Width*(Height-1);
		for(i=0; i<Height; i++)
		{
			fwrite(buffer, Width, 1, f);
			if(w-Width)
				fwrite(buffer, w-Width, 1, f);
			buffer-=Width;
		}
		fclose(f);
		return Width*Height;
	}
	return 0;
}

HBITMAP BuildImage(BYTE *image, int width, int height)
{
	HBITMAP pic = NULL;
	try
	{
		CClientDC dc(NULL);
		BYTE info[256 * 4 + 40], *colors;
		BITMAPINFOHEADER *header  = (BITMAPINFOHEADER*)info;

		header -> biSize          = 40;
		header -> biHeight        = height;
		header -> biWidth         = width;
		header -> biPlanes        = 1;
		header -> biCompression   = 0;
		header -> biSizeImage     = width * height;
		header -> biXPelsPerMeter = 0;
		header -> biYPelsPerMeter = 0;
		header -> biClrImportant  = 0;
		header -> biBitCount      = 8;
		header -> biClrUsed       = 256;

		colors = info + 40;
		for(int i = 0; i < 256; i++)
		{
			*colors++ = i;
			*colors++ = i;
			*colors++ = i;
			*colors++ = 0;
		}

		if(pic)
			DeleteObject(pic);

		void *ptr;
		//	CClientDC dc(NULL);
		pic = CreateDIBSection(dc.m_hDC, (BITMAPINFO*)info, DIB_RGB_COLORS, &ptr, NULL, 0);

		for(int i = 0; i < height; i++)
		{
			memcpy((char *)ptr+i*width, image+(height-i-1)*width, width);
		}
	}
	catch (...)
	{
		pic = NULL;
	}
	return pic;
}

int  Zoom(BYTE *lpSrcDib,BYTE *lpDstDib, long lWidth, long lHeight,
	long lDstWidth,long lDstHeight)
{				
	long i;                 //行循环变量
	long j;                 //列循环变量
	long i1;                 //行循环变量
	long j1;                 //列循环变量
	BYTE	*lpSrcDIBBits;	//指向源像素的指针
	BYTE	*lpDstDIBBits;	//指向临时图象对应像素的指针
	BYTE	*lpDstStartBits;	//指向临时图象对应像素的指针 
	BYTE	*lpSrcStartBits;

	float fhorRatio,fverRatio;

	lpDstStartBits=lpDstDib;	
	lpSrcStartBits = lpSrcDib;
	fhorRatio = (float)lDstWidth/(float)lWidth;
	fverRatio = (float)lDstHeight/(float)lHeight;
	for(i = 0; i < lDstHeight; i++)// 行操作
	{		
		for(j = 0; j < lDstWidth; j++)// 列操作
		{
			// 指向新DIB第i行，第j个像素的指针
			lpDstDIBBits= (BYTE *)lpDstStartBits + lDstWidth * (lDstHeight-1-i)+j;						
			i1= (long) (i / fverRatio + 0.5);// 计算该像素在源DIB中的坐标
			j1= (long) (j / fhorRatio + 0.5);			

			if( (j1>= 0) && (j1< lWidth) && (i1>= 0) && (i1< lHeight))
			{// 判断是否在源图内				
				lpSrcDIBBits= (BYTE *)lpSrcStartBits+ lWidth * (lHeight - 1 -i1) + j1;// 指向源DIB第i行，第j个像素的指针								
				*lpDstDIBBits= *lpSrcDIBBits;// 复制像素
			}
			else
			{
				* ((BYTE*)lpDstDIBBits) = 255;// 源图中不存在的像素，赋为255
			}				
		}		
	}
	return 0;
}

void rotate90(BYTE *Srcbmp, BYTE *Dstbmp,int width, int height)
{
	int lineByte=width;
	int myLineByte=height;
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{ 

				Dstbmp[(width-1-j)*myLineByte+i] = Srcbmp[i*lineByte+j];

		}
	}
}

BOOL is_digit(const TCHAR *str)
{
	size_t len = _tcslen(str);
	while(len > 0) {
		if (*str < _T('0') || *str > _T('9')) {
			return FALSE;
		}
		str++;
		len--;
	}
	return TRUE; 
}

void ConvertImage( unsigned char *src,unsigned char *dst,int sw,int sh,int width,int height,int rotaImage)
{
	int deltaHeight,deltaWidth,j,i,k,iHeight,iWidth;
	unsigned char *pLine; 
	memset(dst,255,width*height);	//clear to white,avoid some pixel no value
	deltaHeight = (sh - height) / 2;
	deltaWidth  = (sw  - width) / 2;
	j = -1;
	k=-1;
	if (deltaHeight >= 0) 
		iHeight = height + deltaHeight;
	else
		iHeight = sh;	  
	for (i = deltaHeight;i< iHeight;i++)
	{
		j++;
		if (i< 0)  continue;
		k++;
		if (rotaImage)
			pLine = src + (iHeight-k-1) * sw;
		else
			pLine = src + i * sw;

		if (deltaWidth >= 0)
			memcpy(dst + j*width, pLine+deltaWidth, width);
		else 
		{
			iWidth = -deltaWidth;
			memcpy(dst + j*width + iWidth, pLine, sw);
		}
	}
}