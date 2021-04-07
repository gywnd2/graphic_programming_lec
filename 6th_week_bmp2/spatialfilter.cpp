#include "image.h"

unsigned char* blur(unsigned char** pixelsptr, int width, int height, int bytesPerPixel)
{
	int x, y;
	int i, j, loc;
	unsigned char *pixels, *result;
	rgb colorr = { 0.0, 0.0, 0.0 };
	pixels = *pixelsptr;

	result = (unsigned char*)malloc(width * height * bytesPerPixel);
	
	for (y = 2; y < height - 2; y++)
	{
		for (x = 2; x < width - 2; x++) {

			colorr.r = 0.0; colorr.g = 0.0; colorr.b = 0.0;
			for (int xa = -1; xa < 2; xa++) {
				for (int ya = -1; ya < 2; ya++) {
					loc = bytesPerPixel * ((y + ya) * width + x + xa);
					colorr.r += 1.0 / 9.0 * pixels[loc + 2];
					colorr.g += 1.0 / 9.0 * pixels[loc + 1];
					colorr.b += 1.0 / 9.0 * pixels[loc + 0];
				}
			}
			loc = bytesPerPixel * ((y)* width + x);
			result[loc] = colorr.b;
			result[loc + 1] = colorr.g;
			result[loc + 2] = colorr.r;
		}
	}
	return result;
}

unsigned char* sharpen(unsigned char** pixelsptr, int width, int height, int bytesPerPixel)
{
	int x, y;
	int i, j, loc;
	unsigned char* pixels, *result;
	rgb colorr = { 0.0, 0.0, 0.0 };
	pixels = *pixelsptr;
	float matrix[3][3] = { {-1.0, -1.0, -1.0}, {-1.0, 9.0, -1.0}, {-1.0, -1.0, -1.0} };
 
	result = (unsigned char*)malloc(width * height * bytesPerPixel);

	for (y = 2; y < height - 2; y++)
	{
		for (x = 2; x < width - 2; x++) {

			colorr.r = 0.0; colorr.g = 0.0; colorr.b = 0.0;
			for (int xa = -1; xa < 2; xa++) {
				for (int ya = -1; ya < 2; ya++) {
					loc = bytesPerPixel * ((y + ya) * width + x + xa);
					colorr.r += (pixels[loc + 2])/255.0 * matrix[xa+1][ya+1];
					colorr.g += (pixels[loc + 1])/255.0  * matrix[xa + 1][ya + 1];
					colorr.b += (pixels[loc + 0])/255.0  * matrix[xa + 1][ya + 1];
				}
			}
			
			colorr.r = (colorr.r > 1.0) ? 1.0 : (colorr.r < 0.0) ? 0 : colorr.r;
			colorr.g = (colorr.g > 1.0) ? 1.0 : (colorr.g < 0.0) ? 0 : colorr.g;
			colorr.b = (colorr.b > 1.0) ? 1.0 : (colorr.b < 0.0) ? 0 : colorr.b;

			loc = bytesPerPixel * ((y)* width + x);
			result[loc] = 255.0*colorr.b;
			result[loc + 1] = 255.0*colorr.g;
			result[loc + 2] = 255.0*colorr.r;
		}
	}

	return result;
}