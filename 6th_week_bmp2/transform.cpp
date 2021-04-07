#include "image.h"

void flipvertical(unsigned char** pixelsptr, int width, int height, int bytesPerPixel)
{
	int x, y;
	int i, k, loc1, loc2;
	unsigned char temp = NULL;
	unsigned char *pixelp1, *pixelp2, *pixels;

	k = height / 2;

	pixels = *pixelsptr;
	for (y = 0; y < k; y++)
	{
		for (x = 0; x < width; x++) {
			loc1 = bytesPerPixel * (y * width + x);
			loc2 = bytesPerPixel * ((height - 1 - y) * width + x);

			pixelp1 = &pixels[loc1]; //pixelp1 = *pixelsptr+loc1;
			pixelp2 = &pixels[loc2]; //pixelp2 = *pixelsptr+loc2;

			for (i = 0; i < bytesPerPixel; i++) {
				temp = pixelp1[i]; //*(*pixelsptr + loc1 + i)
				pixelp1[i] = pixelp2[i]; //*(*pixelsptr + loc2 + i)
				pixelp2[i] = temp;
			}
		}
	}
}

// fliphorizontal
void fliphorizontal(unsigned char** pixelsptr, int width, int height, int bytesPerPixel)
{
	int x, y;
	int i, k, loc1, loc2;
	unsigned char temp = NULL;
	unsigned char *pixelp1, *pixelp2, *pixels;

	k = width / 2;

	pixels = *pixelsptr;
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < k; x++) {
			loc1 = bytesPerPixel * (y * width + x);
			loc2 = bytesPerPixel * (y * width + width - 1 - x);

			pixelp1 = &pixels[loc1];
			pixelp2 = &pixels[loc2];
			for (i = 0; i < bytesPerPixel; i++) {
				temp = pixelp1[i];
				pixelp1[i] = pixelp2[i];
				pixelp2[i] = temp;
			}
		}
	}
}
