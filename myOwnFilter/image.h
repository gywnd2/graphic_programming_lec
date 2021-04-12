#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cmath> 
#include <cstdio> 
#include <cstdlib> 

#define DATA_OFFSET_OFFSET 0x000A
#define WIDTH_OFFSET 0x0012
#define HEIGHT_OFFSET 0x0016
#define BITS_PER_PIXEL_OFFSET 0x001C
#define HEADER_SIZE 14
#define INFO_HEADER_SIZE 40
#define NO_COMPRESION 0
#define MAX_NUMBER_OF_COLORS 0
#define ALL_COLORS_REQUIRED 0

typedef struct {
	float r;       // 0 - 255 
	float g;       // 0 - 255
	float b;       // 0 - 255 
}rgb;

typedef struct {
	float h;       // 0.0 - 360.0 angle in degrees
	float s;       // 0.0 -1.0 percent
	float b;       // 0.0 -1.0 percent
}hsb;

typedef struct {
	float y;
	float cb;
	float cr;
}ycbcr;

hsb  rgb2hsb(rgb in);
rgb  hsb2rgb(hsb in);
ycbcr rgb2ycbcr(rgb in);
rgb ycbcr2rgb(ycbcr in);

void ReadImage(const char* fileName, unsigned char** pixels, int* width, int* height, int* bytesPerPixel);
void WriteImage(const char* fileName, unsigned char* pixels, int width, int height, int bytesPerPixel);


//위아래 뒤집기
void flipvertical(unsigned char** pixels, int width, int height, int bytesPerPixel);
//좌우 뒤집기
void fliphorizontal(unsigned char** pixels, int width, int height, int bytesPerPixel);

// 밝기조절  -100 +100
unsigned char* brightness(unsigned char** pixelsptr, int width, int height, int bytesPerPixel, int ratio);
// 채도 넣기 빼기  -100 +100
unsigned char* saturation(unsigned char** pixelsptr, int width, int height, int bytesPerPixel, int ratio);
// 흐리게 0  +100
unsigned char* fog(unsigned char** pixelsptr, int width, int height, int bytesPerPixel, int ratio);

// 하이라이트   -100  +100
unsigned char* highlight(unsigned char** pixelsptr, int width, int height, int bytesPerPixel, int ratio);
// 그림자   -100   +100
unsigned char* shadow(unsigned char** pixelsptr, int width, int height, int bytesPerPixel, int ratio);
// 대비 -100  +100
unsigned char* contrast(unsigned char** pixelsptr, int width, int height, int bytesPerPixel, int ratio);

// 배경 흐리게    0  +100
unsigned char* backgrounddark(unsigned char** pixelsptr, int width, int height, int bytesPerPixel, int ratio);

// My filter
unsigned char* myfilter(unsigned char** pixelsptr, int width, int height, int bytesPerPixel);

//blur, sharpen
unsigned char* blur(unsigned char** pixelsptr, int width, int height, int bytesPerPixel);
unsigned char* sharpen(unsigned char** pixelsptr, int width, int height, int bytesPerPixel);;;

// HSB값 출력
void showHSBinfo(unsigned char** pixelsptr, int width, int height, int bytesPerPixel);

//myfilter
unsigned char* myfilmeffect(unsigned char** pixelsptr, int width, int height, int bytesPerPixel, int ratio);