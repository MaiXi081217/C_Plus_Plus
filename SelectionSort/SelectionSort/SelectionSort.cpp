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
column j_tmp;
column i_tmp;

void Draw(column arr[]) {
	cleardevice();
	for (int i = 0; i <= LENTH - 1; i++) {
		int Left_X = i * SIZE;
		int Right_X = (i + 1) * SIZE;
		if (i == i_tmp.num) {
			fillrectangle(Left_X, arr[i].High, Right_X, HIGH);
			setfillcolor(YELLOW);
		}
		if (i == j_tmp.num) {
			fillrectangle(Left_X, arr[i].High, Right_X, HIGH);
			setfillcolor(RED);
		}
		fillrectangle(Left_X, arr[i].High, Right_X, HIGH);
		setfillcolor(GREEN);
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

void selectionSort(column arr[], int n) {
	BeginBatchDraw();
	for (int i = 0; i < n; i++) {

		// 寻找[i, n)区间里的最小值
		int minIndex = i;
		for (int j = i + 1; j < n; j++) {
			FlushBatchDraw();
			if (arr[j].num < arr[minIndex].num)
			{
				minIndex = j;
			}
		}
		swap(arr[i], arr[minIndex]);
		i_tmp.num = i;
		j_tmp.num = minIndex;
		Draw(arr);
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
	selectionSort(square, LENTH);
	EndBatchDraw();
	while (true) {}
}