


#include <stdio.h>
#include <stdlib.h>
#include "Bmp.h"

#define DIFF(X, Y) ((X) - (Y) > 0 ? (X) - (Y) : (Y) - (X))
//void display(void)
//{
//	glutSwapBuffers();
//}

/***************************************************
 * Return value: 0 - OK
 *               1 - File open error
 *               2 - Memory request error
 ***************************************************/
int BmpInit(char* bmpFile, BmpData* bmp)
{
	//打开文件
	FILE* fptr = fopen(bmpFile, "rb");
	if (fptr == NULL)
	{
		return 1;
	}
	
	//读取图像大小
	fseek(fptr, 0x0012, SEEK_SET);
	fread(&bmp->Width, sizeof(bmp->Width), 1, fptr);
	fread(&bmp->Height,sizeof(bmp->Height), 1, fptr);
	
	//计算像素数据长度
	bmp->DataLen = bmp->Width * 3;
	bmp->DataLen += 3;
	bmp->DataLen &= ~3;
	bmp->DataLen *= bmp->Height;
	
	//读取像素数据
	bmp->PixelData = (GLubyte*)malloc(bmp->DataLen);
	if(bmp->PixelData == NULL)
	{
		return 2;
	}
	fseek(fptr, 54, SEEK_SET);
	fread(bmp->PixelData, bmp->DataLen, 1, fptr);

	//关闭文件
	fclose(fptr);
	return 0;
}

void BmpToRGB(BmpData* bmp)
{
	int col;
	int row;
	int offset;
	for (row = 0; row < bmp->Height; row++)
	{
		offset = bmp->DataLen / bmp->Height * row;
		for (col = 0; col < bmp->Width; col++)
		{
			GLubyte temp = bmp->PixelData[offset + col * 3];
			bmp->PixelData[offset + col * 3] = bmp->PixelData[offset + col * 3 + 2];
			bmp->PixelData[offset + col * 3 + 2] = temp;
		}
	}
}

void BmpSpecProc(BmpData* bmp, int x, int y, int size, GLubyte clrR, GLubyte clrG, GLubyte clrB)
{
	int col;
	int row;
	int offset;
	for (row = y ; row < y + size; row++)
	{
		offset = bmp->DataLen / bmp->Height * row;
		for (col = x; col < x + size; col++)
		{
			bmp->PixelData[offset + col * 3 + 0] = clrR;
			bmp->PixelData[offset + col * 3 + 1] = clrG;
			bmp->PixelData[offset + col * 3 + 2] = clrB;
		}
	}
}

void BmpRmNevus(BmpData* bmp)
{
	int col;
	int row;
	int offset;
	for (row = 0; row < bmp->Height; row++)
	{
		offset = bmp->DataLen / bmp->Height * row;
		for (col = 0; col < bmp->Width; col++)
		{
			GLubyte clrR = bmp->PixelData[offset + col * 3 + 0];
			GLubyte clrG = bmp->PixelData[offset + col * 3 + 1];
			GLubyte clrB = bmp->PixelData[offset + col * 3 + 2];
			if ((DIFF(clrR, clrG) > 60) 
				|| (DIFF(clrR, clrB) > 60) 
				|| (DIFF(clrB, clrG) > 60))
			{
				bmp->PixelData[offset + col * 3 + 0] = 254;
				bmp->PixelData[offset + col * 3 + 1] = 241;
				bmp->PixelData[offset + col * 3 + 2] = 225;
			}
			//if (bmp->PixelData[offset + col * 3 + 0] > 128)
			//{
			//	bmp->PixelData[offset + col * 3 + 0] = 254;
			//}
			//if (bmp->PixelData[offset + col * 3 + 1] > 128)
			//{
			//	bmp->PixelData[offset + col * 3 + 1] = 241;
			//}
			//if (bmp->PixelData[offset + col * 3 + 2] > 128)
			//{
			//	bmp->PixelData[offset + col * 3 + 2] = 225;
			//}
			//bmp->PixelData[offset + col * 3 + 0] = bmp->PixelData[offset + col * 3 + 0] << 1;
			//bmp->PixelData[offset + col * 3 + 1] = bmp->PixelData[offset + col * 3 + 1] << 1;
			//bmp->PixelData[offset + col * 3 + 2] = bmp->PixelData[offset + col * 3 + 2] >> 1;
		}
	}
}

void BmpDraw(BmpData* bmp)
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(bmp->Width, 
	             bmp->Height, 
				 GL_RGB, 
				 GL_UNSIGNED_BYTE, 
				 bmp->PixelData);
	//glFlush();
	//glutSwapBuffers();
}

int BmpDestroy(BmpData* bmp)
{
	if (bmp->PixelData != NULL)
	{
		free(bmp->PixelData);
		bmp->PixelData = NULL;
	}
	bmp->DataLen = 0;
	bmp->Width = 0;
	bmp->Height = 0;
	return 0;
}

//int main(int argc,char* argv[])
//{
//
//	//初始化glut运行
//	glutInit(&argc,argv);
//	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
//	glutInitWindowPosition(100,100);
//	glutInitWindowSize(imagewidth,imageheight);
//	glutCreateWindow(FileName);
//	glutDisplayFunc(display);
//	glutMainLoop();
//
//
//	return 0;
//}