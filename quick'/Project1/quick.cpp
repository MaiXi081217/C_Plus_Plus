#include<iostream>
#include<easyx.h>
#include <conio.h>

using namespace std;
#define SIZE 4
#define HIGH 720
#define WIDTH 1440
#define LENTH 360

class column {
public:
	int Size;
	int Left_X;
	int Right_X;
	int num;
	int High;
	column() {
		this->num = 0;
	}
};
void Draw(column arr[]) {
	cleardevice();
	for (int i = 0; i <= LENTH - 1; i++) {
		int Left_X = i * SIZE;
		int Right_X = (i + 1) * SIZE;
		fillrectangle(Left_X, arr[i].High, Right_X, HIGH);
		setfillcolor(GREEN);
	}
}
void Rand(column arr[]){
	for (int i = 0; i < LENTH - 1; i++) {
		int i_tmp = rand() % LENTH;
		column tmp;
		tmp = arr[i];
		arr[i] = arr[i_tmp];
		arr[i_tmp] = tmp;
	}
}
int main()
{	
	column square[LENTH];
	for (int i = 0; i <= LENTH-1; i++){
			square[i].Size = (i + 1)*2;
			int Left_X = i*SIZE;
			int Right_X = (i + 1) * SIZE;
			square[i].High = HIGH - square[i].Size;
			if (i!=0){
				square[i].num = square[i - 1].num + 1;
			}
	}
	initgraph(WIDTH,HIGH);// 创建绘图窗口，大小为 1040x640 像素
	BeginBatchDraw();
	Rand(square);
	for (int i = 1; i <= LENTH - 1; ++i) {
		FlushBatchDraw();
			for (int j = 0; j < LENTH - 1 - i; ++j)
				if (square[j].num > square[j + 1].num)
					swap(square[j], square[j + 1]);
			Draw(square);
			Sleep(10);
		}
	EndBatchDraw();
	while (true){}
}