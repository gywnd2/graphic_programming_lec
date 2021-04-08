#include "image.h"

// 밝기조절  -100 +100
unsigned char* brightness(unsigned char** pixelsptr, int width, int height, int bytesPerPixel, int ratio)
{
	int x, y;
	int i, loc;
	unsigned char* pixels, * result;
	float temp;

	result = (unsigned char*)malloc(width * height * bytesPerPixel);
	pixels = *pixelsptr;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++) {

			loc = bytesPerPixel * (y * width + x);  // pixels[loc]  b g r
			// RGB 조정
			/*
			for (i = 0; i < bytesPerPixel; i++) {
				temp = pixels[loc + i] + 0.5*(float)(ratio)/100.0;
				temp = (temp > 255) ? 255 : (temp < 0) ? 0 : temp;
				result[loc + i] = temp;
			}*/

			// HSB 조절
			rgb rgb = { pixels[loc + 2], pixels[loc + 1], pixels[loc] };
			hsb hsb = rgb2hsb(rgb);
			hsb.b += 0.5 * (float)(ratio) / 100.0;
			hsb.b = (hsb.b > 1.0) ? 1.0 : (hsb.b < 0.0) ? 0.0 : hsb.b;
			rgb = hsb2rgb(hsb);
			result[loc] = rgb.b; result[loc + 1] = rgb.g; result[loc + 2] = rgb.r;
		}
	}
	return result;
}


// 채도 넣기 빼기  -100 +100
unsigned char* saturation(unsigned char** pixelsptr, int width, int height, int bytesPerPixel, int ratio)
{
	int x, y;
	int i, loc;
	unsigned char* pixels, * result;
	float temp;

	result = (unsigned char*)malloc(width * height * bytesPerPixel);
	pixels = *pixelsptr;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++) {

			loc = bytesPerPixel * (y * width + x);

			rgb rgb = { pixels[loc + 2], pixels[loc + 1], pixels[loc] };
			hsb hsb = rgb2hsb(rgb);

			/*
				Saturation 증가 감소
			*/
			hsb.s += 0.5 * (float)(ratio) / 100.0;
			hsb.s = (hsb.s > 1.0) ? 1.0 : (hsb.s < 0.0) ? 0.0 : hsb.s;

			rgb = hsb2rgb(hsb);
			result[loc] = rgb.b; result[loc + 1] = rgb.g; result[loc + 2] = rgb.r;

		}
	}
	return result;
}
// 흐리게 0  +100
unsigned char* fog(unsigned char** pixelsptr, int width, int height, int bytesPerPixel, int ratio)
{
	int x, y;
	int i, loc;
	unsigned char* pixels, * result;
	float temp;

	result = (unsigned char*)malloc(width * height * bytesPerPixel);
	pixels = *pixelsptr;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++) {

			loc = bytesPerPixel * (y * width + x);

			for (i = 0; i < bytesPerPixel; i++) {
				temp = pixels[loc + i];
				/*  TODO
				  Fog Color(회색) 와 원래 칼라를 블렌딩 회색 rgb에 ratio만큼 곱해서 더하기
				  b, g, r
				*/
				temp = (float)(ratio / 100.0) * 100 + (float)(1 - ratio / 100.0) * temp;
				result[loc + i] = temp;
			}
		}
	}
    return result;
}
// 하이라이트   -100  +100
unsigned char* highlight(unsigned char** pixelsptr, int width, int height, int bytesPerPixel, int ratio)
{
	int x, y;
	int i, loc;
	unsigned char* pixels, * result;
	float temp;

	result = (unsigned char*)malloc(width * height * bytesPerPixel);
	pixels = *pixelsptr;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++) {

			loc = bytesPerPixel * (y * width + x);

			rgb rgb = { pixels[loc + 2], pixels[loc + 1], pixels[loc] };
			hsb hsb = rgb2hsb(rgb);

			/*
				밝은부분을 더 밝게
			*/
			if (hsb.b > 0.7) {
				hsb.b = hsb.b * (1.0 + 0.3 * (float)(ratio) / 100.0);
			}
			hsb.b = (hsb.b > 1.0) ? 1.0 : (hsb.b < 0.0) ? 0.0 : hsb.b;

			rgb = hsb2rgb(hsb);
			result[loc] = rgb.b; result[loc + 1] = rgb.g; result[loc + 2] = rgb.r;
		}
	}
	return result;
}
// 그림자   -100   +100
unsigned char* shadow(unsigned char** pixelsptr, int width, int height, int bytesPerPixel, int ratio)
{
	int x, y;
	int i, loc;
	unsigned char* pixels, * result;
	float temp;

	result = (unsigned char*)malloc(width * height * bytesPerPixel);
	pixels = *pixelsptr;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++) {

			loc = bytesPerPixel * (y * width + x);

			rgb rgb = { pixels[loc + 2], pixels[loc + 1], pixels[loc] };
			hsb hsb = rgb2hsb(rgb);

			/*
				어두운 부분을 더 어둡게
			*/
			// To Do

			if (hsb.b <= 0.5) {
				hsb.b = hsb.b * (1.0 - 0.3 * (float)(ratio) / 100.0);
			}
			hsb.b = (hsb.b > 1.0) ? 1.0 : (hsb.b < 0.0) ? 0.0 : hsb.b;

			rgb = hsb2rgb(hsb);
			result[loc] = rgb.b; result[loc + 1] = rgb.g; result[loc + 2] = rgb.r;
		}
	}
	return result;
}

// 대비 -100  +100
unsigned char* contrast(unsigned char** pixelsptr, int width, int height, int bytesPerPixel, int ratio)
{
	int x, y;
	int i, loc;
	unsigned char* pixels, * result;
	float temp;

	result = (unsigned char*)malloc(width * height * bytesPerPixel);
	pixels = *pixelsptr;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++) {

			loc = bytesPerPixel * (y * width + x);

			rgb rgb = { pixels[loc + 2], pixels[loc + 1], pixels[loc] };
			hsb hsb = rgb2hsb(rgb);

			/*
				TODO
				+ 값: 밝은 곳은 더 밝게 어두운 곳은 더 어둡게   (대비 증가)
				- 값: 밝은 곳은 더 어둡게, 어두운 곳은 더 밝게  (평준화)
			*/
			if (hsb.b > 0.7) {
				hsb.b = hsb.b * (1.0 + 0.3 * (float)(ratio) / 100.0);
			}
			else if (hsb.b <= 0.5) {
				hsb.b = hsb.b * (1.0 - 0.3 * (float)(ratio) / 100.0);
			}
			hsb.b = (hsb.b > 1.0) ? 1.0 : (hsb.b < 0.0) ? 0.0 : hsb.b;
			rgb = hsb2rgb(hsb);
			result[loc] = rgb.b; result[loc + 1] = rgb.g; result[loc + 2] = rgb.r;
		}
	}
	return result;
}

// 배경 흐리게    0  +100
unsigned char* backgrounddark(unsigned char** pixelsptr, int width, int height, int bytesPerPixel, int ratio)
{
	int x, y;
	int i, loc;
	unsigned char* pixels, * result;
	float temp;

	result = (unsigned char*)malloc(width * height * bytesPerPixel);
	pixels = *pixelsptr;

	/*
		ToDo

		외곽부분을 어둡게
	*/
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++) {

			loc = bytesPerPixel * (y * width + x);
			rgb rgb = { pixels[loc + 2], pixels[loc + 1], pixels[loc] };
			hsb hsb = rgb2hsb(rgb);
			// To Do
			if (y <= height * 0.05 || y >= height * 0.95) {
				hsb.b = hsb.b * (1.0 - 0.3 * (float)(ratio) / 100.0);
			}
			else if (x <= width * 0.05 || x >= width * 0.95) {
				hsb.b = hsb.b * (1.0 - 0.3 * (float)(ratio) / 100.0);
			}
			hsb.b = (hsb.b > 1.0) ? 1.0 : (hsb.b < 0.0) ? 0.0 : hsb.b;
			rgb = hsb2rgb(hsb);
			result[loc] = rgb.b; result[loc + 1] = rgb.g; result[loc + 2] = rgb.r;
		}
	}
	return result;
}

// My filter
unsigned char* myfilter(unsigned char** pixelsptr, int width, int height, int bytesPerPixel, int ratio)
{
	int x, y;
	int i, loc;
	unsigned char* pixels, * result;
	float temp;

	result = (unsigned char*)malloc(width * height * bytesPerPixel);
	pixels = *pixelsptr;

	/*
		ToDo


	*/
	return result;
}


