#include "image.h"
#include "windows.h"

int main()
{
	unsigned char* pixels;
	int width;
	int height;
	int bytesPerPixel;
	int ratio;

	while (1) {
		std::cout << "블러효과를 얼마나 줄까요? (3, 5,... 홀수로 입력, 종료하려면 -1 입력) : ";
		std::cin >> ratio;
		system("cls");
		if (ratio == -1){
			std::cout << "종료합니다." << std::endl;
			break;
		}
		else if ((ratio % 2 == 0)||(ratio<3)) {
			std::cout << "3 이상의 홀수를 입력하세요." << std::endl;
			Sleep(1500);
			system("cls");
		}
		else {
			ReadImage("C:/repo/graphic_programming_lec/myOwnFilter/images/target4.bmp", &pixels, &width, &height, &bytesPerPixel);
			pixels = myfilmeffect(&pixels, width, height, bytesPerPixel, ratio);
			WriteImage("C:/repo/graphic_programming_lec/myOwnFilter/images/target_result4.bmp", pixels, width, height, bytesPerPixel);
			std::cout << "이미지 수정됨";
			free(pixels);
			break;
		}
	}
	return 0;
}