#include "image.h"

int main()
{
	unsigned char* pixels;  // 동적배열
	int width;
	int height;
	int bytesPerPixel;
	ReadImage("C:/repo/graphic_programming_lec/myOwnFilter/target.bmp", &pixels, &width, &height, &bytesPerPixel);

	pixels=myfilmeffect(&pixels, width, height, bytesPerPixel);

	WriteImage("C:/repo/graphic_programming_lec/myOwnFilter/target_result.bmp", pixels, width, height, bytesPerPixel);

	std::cout << "test";

	free(pixels);
	return 0;
}