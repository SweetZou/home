#ifndef __BMP_H__
#define __BMP_H__


#include "gl/glut.h"

typedef struct BmpData_Struct {
	GLubyte* PixelData;
	GLint DataLen;
	GLint Width;
	GLint Height;
} BmpData;

extern int BmpInit(char* bmpFile, BmpData* bmp);
extern BmpData* get_sub_bmp(BmpData* bmp, int offset_x, int offset_y, int width, int height);
extern void BmpToRGB(BmpData* bmp);
extern void BmpRmNevus(BmpData* bmp);
extern void BmpSpecProc(BmpData* bmp, int x, int y, int size, GLubyte clrR, GLubyte clrG, GLubyte clrB);
extern void BmpDraw(BmpData* bmp);
extern int BmpDestroy(BmpData* bmp);

#endif
