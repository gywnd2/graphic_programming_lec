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
unsigned char* myfilter(unsigned char** pixelsptr, int width, int height, int bytesPerPixel)
{
	int x, y;
	int i, k, loc, loc2;
	unsigned char* pixels, * result, * pixelp1, * pixelp2;
	unsigned char temp = NULL;

	result = (unsigned char*)malloc(width * height * bytesPerPixel);
	pixels = *pixelsptr;

	// 특정 색의 saturation만 살리기
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++) {

			loc = bytesPerPixel * (y * width + x);

			rgb rgb = { pixels[loc + 2], pixels[loc + 1], pixels[loc] };
			hsb hsb = rgb2hsb(rgb);


			if ((hsb.h > 217) && (x < 562 && y>216)) { hsb.s = 0; }
			else if ((x > 561 && y < 268)) { hsb.s = 0; }
			else if (x < 562 && y < 217) { hsb.s = 0; }


			rgb = hsb2rgb(hsb);
			result[loc] = rgb.b; result[loc + 1] = rgb.g; result[loc + 2] = rgb.r;
		}

	}

	// 3X3 컨벌루션으로 blur 처리하기

	rgb colorr = { 0.0, 0.0, 0.0 };
	float matrix[3][3] = { {1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0},
							{1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0},
							{1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0} };

	for (y = 1; y < height - 1; y++)
	{
		for (x = 1; x < width - 1; x++) {

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


	/*액자
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


		/*/ sharpen 효과
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

// HSB값 출력
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

			std::cout << "hsb.h : " << hsb.h << "hsb.s : " << hsb.s << "hsb.b : " << hsb.b << std::endl;
		}
	}
}

unsigned char* myfilmeffect(unsigned char** pixelsptr, int width, int height, int bytesPerPixel, int ratio)
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

			// 채도 빼기 -20
			rgb rgb = { pixels[loc + 2], pixels[loc + 1], pixels[loc] };
			hsb hsb = rgb2hsb(rgb);
			hsb.s += 0.5 * (float)(-20) / 100.0;
			hsb.s = (hsb.s > 1.0) ? 1.0 : (hsb.s < 0.0) ? 0.0 : hsb.s;

			// 대비 줄이기 -20
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


	// blur 1/49만큼
	rgb colorr = { 0.0, 0.0, 0.0 };
	float** matrix;
	matrix = (float**)malloc(sizeof(float) * ratio);
	for (int i = 0; i < ratio; i++) {
		matrix[i] = (float*)malloc(sizeof(float) * ratio);
	}
	for (int i = 0; i < ratio; i++) {
		for (int j = 0; j < ratio; j++) {
			matrix[i][j] = 1.0 / (float)(ratio*ratio);
		}
	}

	for (y = ratio - 1; y < height - (ratio - 1); y++)
	{
		for (x = ratio - 1; x < width - (ratio - 1); x++) {

			colorr.r = 0.0; colorr.g = 0.0; colorr.b = 0.0;
			for (int xa = -(ratio / 2); xa < (ratio / 2) + 1; xa++) {
				for (int ya = -(ratio / 2); ya < (ratio / 2) + 1; ya++) {
					loc = bytesPerPixel * ((y + ya) * width + x + xa);
					colorr.r += result[loc + 2] * matrix[xa + (ratio / 2)][ya + (ratio / 2)];
					colorr.g += result[loc + 1] * matrix[xa + (ratio / 2)][ya + (ratio / 2)];
					colorr.b += result[loc + 0] * matrix[xa + (ratio / 2)][ya + (ratio / 2)];
				}
			}

			loc = bytesPerPixel * ((y)*width + x);
			result[loc] = colorr.b;
			result[loc + 1] = colorr.g;
			result[loc + 2] = colorr.r;
		}
	}

	// 필름 프레임
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