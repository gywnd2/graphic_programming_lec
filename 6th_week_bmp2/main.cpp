#include "image.h"

int main()
{
	unsigned char* pixels;  // 동적배열
	int width;
	int height;
	int bytesPerPixel;
	ReadImage("sails.bmp", &pixels, &width, &height, &bytesPerPixel);

	unsigned char *res = blur(&pixels, width, height, bytesPerPixel);
	WriteImage("sailblur.bmp", res, width, height, bytesPerPixel); 

	res = sharpen(&pixels, width, height, bytesPerPixel);
	WriteImage("sailsharpens.bmp", res, width, height, bytesPerPixel);

	fliphorizontal(&pixels, width, height, bytesPerPixel);
	WriteImage("sailshorizontal.bmp", pixels, width, height, bytesPerPixel);

	flipvertical(&pixels, width, height, bytesPerPixel);
	WriteImage("sailsvertical.bmp", pixels, width, height, bytesPerPixel);

	free(pixels);
	return 0;
}