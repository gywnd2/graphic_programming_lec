#include "image.h"

int main()
{
	unsigned char* pixels;  // 동적배열
	int width;
	int height;
	int bytesPerPixel;
	ReadImage("boy.bmp", &pixels, &width, &height, &bytesPerPixel);

	pixels = backgrounddark(&pixels, width, height, bytesPerPixel, 100);

	WriteImage("boyshadow.bmp", pixels, width, height, bytesPerPixel);

	std::cout << "test";

	free(pixels);
	return 0;
}