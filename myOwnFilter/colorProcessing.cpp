#include "image.h"

// �������  -100 +100
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
			// RGB ����
			/*
			for (i = 0; i < bytesPerPixel; i++) {
				temp = pixels[loc + i] + 0.5*(float)(ratio)/100.0;
				temp = (temp > 255) ? 255 : (temp < 0) ? 0 : temp;
				result[loc + i] = temp;
			}*/

			// HSB ����
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


// ä�� �ֱ� ����  -100 +100
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
				Saturation ���� ����
			*/
			hsb.s += 0.5 * (float)(ratio) / 100.0;
			hsb.s = (hsb.s > 1.0) ? 1.0 : (hsb.s < 0.0) ? 0.0 : hsb.s;

			rgb = hsb2rgb(hsb);
			result[loc] = rgb.b; result[loc + 1] = rgb.g; result[loc + 2] = rgb.r;

		}
	}
	return result;
}
// �帮�� 0  +100
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
				  Fog Color(ȸ��) �� ���� Į�� ���� ȸ�� rgb�� ratio��ŭ ���ؼ� ���ϱ�
				  b, g, r
				*/
				temp = (float)(ratio / 100.0) * 100 + (float)(1 - ratio / 100.0) * temp;
				result[loc + i] = temp;
			}
		}
	}
    return result;
}
// ���̶���Ʈ   -100  +100
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
				�����κ��� �� ���
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
// �׸���   -100   +100
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
				��ο� �κ��� �� ��Ӱ�
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

// ��� -100  +100
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
				+ ��: ���� ���� �� ��� ��ο� ���� �� ��Ӱ�   (��� ����)
				- ��: ���� ���� �� ��Ӱ�, ��ο� ���� �� ���  (����ȭ)
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

// ��� �帮��    0  +100
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

		�ܰ��κ��� ��Ӱ�
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

// ���� ����
void edgedetect(unsigned char** pixelsptr, int width, int height, int bytesPerPixel)
{
	int x, y;
	int i, k, locOrigin, locLeft;
	unsigned char temp = NULL;
	unsigned char *pixels;
	float diff;

	pixels = *pixelsptr;
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			locOrigin = bytesPerPixel * (y * width + x);
			locLeft = bytesPerPixel * (y * width + x-1);
			rgb rgbOrigin = { pixels[locOrigin + 2], pixels[locOrigin + 1], pixels[locOrigin] };
			rgb rgbLeft = { pixels[locLeft + 2], pixels[locLeft + 1], pixels[locLeft] };
			hsb hsbOrigin = rgb2hsb(rgbOrigin);
			hsb hsbLeft = rgb2hsb(rgbLeft);
			diff = hsbOrigin.b-hsbLeft.b;
			hsbOrigin.b = diff;
			//hsbOrigin.b = (hsbOrigin.b > 1.0) ? 1.0 : (hsbOrigin.b < 0.0) ? 0.0 : hsbOrigin.b;
			rgbOrigin = hsb2rgb(hsbOrigin);
			pixels[locOrigin] = rgbOrigin.b; pixels[locOrigin + 1] = rgbOrigin.g; pixels[locOrigin + 2] = rgbOrigin.r;
			
		}
	}
}

// My filter
unsigned char* myfilter(unsigned char** pixelsptr, int width, int height, int bytesPerPixel)
{
	int x, y;
	int i, k, loc, loc2;
	unsigned char* pixels, * result, *pixelp1, *pixelp2;
	unsigned char temp=NULL;

	result = (unsigned char*)malloc(width * height * bytesPerPixel);
	pixels = *pixelsptr;

	// Ư�� ���� saturation�� �츮��
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++) {

			loc = bytesPerPixel * (y * width + x);

			rgb rgb = { pixels[loc + 2], pixels[loc + 1], pixels[loc] };
			hsb hsb = rgb2hsb(rgb);

			
			if ((hsb.h > 217)&&(x<562 && y>216)) { hsb.s = 0; }
			else if ((x > 561 && y< 268)) { hsb.s = 0; }
			else if (x < 562 && y < 217) { hsb.s = 0; }
			

			rgb = hsb2rgb(hsb);
			result[loc] = rgb.b; result[loc + 1] = rgb.g; result[loc + 2] = rgb.r;
		}

	}

	// 3X3 ����������� blur ó���ϱ�

	rgb colorr = { 0.0, 0.0, 0.0 };
	float matrix[3][3] = { {1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0},
							{1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0},
							{1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0} };

	for (y = 1; y < height - 1; y++)
	{
		for (x =1; x < width - 1; x++) {

			colorr.r = 0.0; colorr.g = 0.0; colorr.b = 0.0;
			for (int xa = -1; xa < 2; xa++) {
				for (int ya = -1; ya < 2; ya++) {
					loc = bytesPerPixel * ((y + ya) * width + x + xa);
					colorr.r += result[loc + 2] * matrix[xa + 1][ya + 1];
					colorr.g += result[loc + 1] * matrix[xa + 1][ya + 1];
					colorr.b += result[loc + 0] * matrix[xa + 1][ya + 1];
				}
			}

			loc = bytesPerPixel * ((y)*width + x);
			result[loc] = colorr.b;
			result[loc + 1] = colorr.g;
			result[loc + 2] = colorr.r;
		}
	}

	k = width / 2;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < k; x++) {
			loc = bytesPerPixel * (y * width + x);
			loc2 = bytesPerPixel * (y * width + width - 1 - x);

			pixelp1 = &result[loc];
			pixelp2 = &result[loc2];
			for (i = 0; i < bytesPerPixel; i++) {
				temp = pixelp1[i];
				pixelp1[i] = pixelp2[i];
				pixelp2[i] = temp;
			}
		}
	}


	/*����
			if (y <= height * 0.05 || y >= height * 0.95) {
				hsb.b = hsb.b * (1.0 - 0.3 * (float)(ratio) / 100.0);
			}
			else if (x <= width * 0.05 || x >= width * 0.95) {
				hsb.b = hsb.b * (1.0 - 0.3 * (float)(ratio) / 100.0);

				hsb.s = (hsb.s > 1.0) ? 1.0 : (hsb.s < 0.0) ? 0.0 : hsb.s;

				rgb = hsb2rgb(hsb);
				result[loc] = rgb.b; result[loc + 1] = rgb.g; result[loc + 2] = rgb.r;


			}
		}
		*/

	
	 /*/ sharpen ȿ��
	 for (y = 2; y < height - 2; y++)
	{
		for (x = 2; x < width - 2; x++) {

			colorr.r = 0.0; colorr.g = 0.0; colorr.b = 0.0;
			for (int xa = -1; xa < 2; xa++) {
				for (int ya = -1; ya < 2; ya++) {
					loc = bytesPerPixel * ((y + ya) * width + x + xa);
					colorr.r += (pixels[loc + 2]) / 255.0 * matrix[xa + 1][ya + 1];
					colorr.g += (pixels[loc + 1]) / 255.0 * matrix[xa + 1][ya + 1];
					colorr.b += (pixels[loc + 0]) / 255.0 * matrix[xa + 1][ya + 1];
				}
			}

			colorr.r = (colorr.r > 1.0) ? 1.0 : (colorr.r < 0.0) ? 0 : colorr.r;
			colorr.g = (colorr.g > 1.0) ? 1.0 : (colorr.g < 0.0) ? 0 : colorr.g;
			colorr.b = (colorr.b > 1.0) ? 1.0 : (colorr.b < 0.0) ? 0 : colorr.b;

			loc = bytesPerPixel * ((y)*width + x);
			result[loc] = 255.0 * colorr.b;
			result[loc + 1] = 255.0 * colorr.g;
			result[loc + 2] = 255.0 * colorr.r;
		}
	}
	*/

	return result;
}

// test
void showHSBinfo(unsigned char** pixelsptr, int width, int height, int bytesPerPixel)
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

			std::cout << "hsb.h : " << hsb.h << "hsb.s : " << hsb.s <<  "hsb.b : " << hsb.b << std::endl;
		}
	}
}

unsigned char* myfilmeffect(unsigned char** pixelsptr, int width, int height, int bytesPerPixel) 
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

			// ä�� ���� -20
			rgb rgb = { pixels[loc + 2], pixels[loc + 1], pixels[loc] };
			hsb hsb = rgb2hsb(rgb);
			hsb.s += 0.5 * (float)(-20) / 100.0;
			hsb.s = (hsb.s > 1.0) ? 1.0 : (hsb.s < 0.0) ? 0.0 : hsb.s;

			// ��� ���̱� -20
			if (hsb.b > 0.7) {
				hsb.b = hsb.b * (1.0 + 0.3 * (float)(-20) / 100.0);
			}
			else if (hsb.b <= 0.3) {
				hsb.b = hsb.b * (1.0 - 0.3 * (float)(-20) / 100.0);
			}
			hsb.b = (hsb.b > 1.0) ? 1.0 : (hsb.b < 0.0) ? 0.0 : hsb.b;

			// shadow 30
		    if (hsb.b <= 0.5) {
				hsb.b = hsb.b * (1.0 - 0.3 * (float)(30) / 100.0);
			}
			hsb.b = (hsb.b > 1.0) ? 1.0 : (hsb.b < 0.0) ? 0.0 : hsb.b;

			rgb = hsb2rgb(hsb);
			result[loc] = rgb.b; result[loc + 1] = rgb.g; result[loc + 2] = rgb.r;
		}
	}

	
	// blur 1/49��ŭ
	rgb colorr = { 0.0, 0.0, 0.0 };
	float matrix[7][7] = { {1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0},
							{1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0}, 
							{1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0}, 
							{1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0}, 
							{1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0}, 
							{1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0}, 
							{1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0, 1.0 / 49.0}};

	for (y = 6; y < height - 6; y++)
	{
		for (x = 6; x < width - 6; x++) {

			colorr.r = 0.0; colorr.g = 0.0; colorr.b = 0.0;
			for (int xa = -3; xa < 4; xa++) {
				for (int ya = -3; ya < 4; ya++) {
					loc = bytesPerPixel * ((y + ya) * width + x + xa);
					colorr.r += result[loc + 2] * matrix[xa + 3][ya + 3];
					colorr.g += result[loc + 1] * matrix[xa + 3][ya + 3];
					colorr.b += result[loc + 0] * matrix[xa + 3][ya + 3];
				}
			}

			loc = bytesPerPixel * ((y)*width + x);
			result[loc] = colorr.b;
			result[loc + 1] = colorr.g;
			result[loc + 2] = colorr.r;
		}
	}

	// �ʸ� ������
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++) {

			loc = bytesPerPixel * (y * width + x);
			rgb rgb = { result[loc + 2], result[loc + 1], result[loc] };
			hsb hsb = rgb2hsb(rgb);
			if (y <= height * 0.05 || y >= height * 0.8) {
				hsb.h = 0;
				hsb.s = 0;
				hsb.b = 100;
			}
			else if (x <= width * 0.05 || x >= width * 0.95) {
				hsb.h = 0;
				hsb.s = 0;
				hsb.b = 100;
			}
			hsb.b = (hsb.b > 1.0) ? 1.0 : (hsb.b < 0.0) ? 0.0 : hsb.b;
			rgb = hsb2rgb(hsb);
			result[loc] = rgb.b; result[loc + 1] = rgb.g; result[loc + 2] = rgb.r;
		}
	}
	
	return result;
}