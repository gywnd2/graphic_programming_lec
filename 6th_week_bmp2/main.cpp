#include "image.h"

int main()
{
	unsigned char* pixels;  // 동적배열
	int width;
	int height;
	int bytesPerPixel;
	ReadImage("C:/repo/OpenCV_lec/HW1/images/gt4.bmp", &pixels, &width, &height, &bytesPerPixel);

	unsigned char *res = blur(&pixels, width, height, bytesPerPixel);
	WriteImage("C:/repo/OpenCV_lec/HW1/images/blur_gt4.bmp", res, width, height, bytesPerPixel);

	res = sharpen(&pixels, width, height, bytesPerPixel);
	WriteImage("C:/repo/OpenCV_lec/HW1/images/sharpen_gt4.bmp", res, width, height, bytesPerPixel);

	fliphorizontal(&pixels, width, height, bytesPerPixel);
	WriteImage("C:/repo/OpenCV_lec/HW1/images/flip_horizontal_gt4.bmp", pixels, width, height, bytesPerPixel);

	flipvertical(&pixels, width, height, bytesPerPixel);
	WriteImage("C:/repo/OpenCV_lec/HW1/images/flip_vertical_gt4.bmp", pixels, width, height, bytesPerPixel);

	free(pixels);
	return 0;
}