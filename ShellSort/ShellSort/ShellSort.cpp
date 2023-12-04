#include<iostream>
#include<easyx.h>
#include <conio.h>

using namespace std;
#define SIZE 4
#define HIGH 720
#define WIDTH 1440
#define LENTH 360
#define LEFT 0
#define RIGHT 359
int i_tmp;
int j_tmp;

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
		if (i == i_tmp) {
			fillrectangle(Left_X, arr[i].High, Right_X, HIGH);
			setfillcolor(YELLOW);
		}
		if (i == j_tmp) {
			fillrectangle(Left_X, arr[i].High, Right_X, HIGH);
			setfillcolor(RED);
		}
		fillrectangle(Left_X, arr[i].High, Right_X, HIGH);
		setfillcolor(GREEN);
	}
}
void ShellSort(column arr[], int Lenth) {
	int gap = Lenth;
	BeginBatchDraw();
	while (gap > 1) {

		gap /= 2;
		for (int i = 0; i < Lenth - gap; i++)
		{
			FlushBatchDraw();
			int end = i;
			column tmp = arr[end + gap];
			while (end >= 0) {
				if (arr[end].num > tmp.num) {
					i_tmp = arr[end + gap].num;
					j_tmp = arr[end].num;
					arr[end + gap] = arr[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			//Sleep(10);
			arr[end + gap] = tmp;
			Draw(arr);
		}
	}

}

void Rand(column arr[]) {
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
	for (int i = 0; i <= LENTH - 1; i++) {
		square[i].Size = (i + 1) * 2;
		int Left_X = i * SIZE;
		int Right_X = (i + 1) * SIZE;
		square[i].High = HIGH - square[i].Size;
		if (i != 0) {
			square[i].num = square[i - 1].num + 1;
		}
	}
	initgraph(WIDTH, HIGH);// 创建绘图窗口，大小为 1040x640 像素
	Rand(square);
	//quickSort(square, LEFT, RIGHT);
	ShellSort(square, LENTH);
	EndBatchDraw();
	while (true) {}
}