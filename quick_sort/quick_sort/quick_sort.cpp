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
int i_tmp ;
int j_tmp ;

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
		if (i == i_tmp ) {
			fillrectangle(Left_X, arr[i].High, Right_X, HIGH);
			setfillcolor(YELLOW);
		}
		if ( i == j_tmp) {
			fillrectangle(Left_X, arr[i].High, Right_X, HIGH);
			setfillcolor(RED);
		}
		fillrectangle(Left_X, arr[i].High, Right_X, HIGH);
		setfillcolor(GREEN);
	}
}
void quickSort(column a[], int l, int r) {
	if (l >= r)
		return;
	int i = l;
	int j = r;
	column key = a[l];//选择第一个数为key
	BeginBatchDraw();
	while (i < j) {
		FlushBatchDraw();
		while (i < j && a[j].num >= key.num){//从右向左找第一个小于key的值
			j--;
		}
		if (i < j) {
			a[i] = a[j];
			i_tmp = i;
			i++;
		}
		while (i < j && a[i].num < key.num){//从左向右找第一个大于key的值
			i++;
		}
		if (i < j) {
			a[j] = a[i];
			j_tmp = j;
			j--;
		}
		Sleep(50);
		Draw(a);
		//Sleep(30);
	}
	a[i] = key;
	quickSort(a, l, i - 1);//继续排左部分，递归调用
	quickSort(a, i + 1, r);//继续排右部分，递归调用
	
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
	quickSort(square, LEFT, RIGHT);
	EndBatchDraw();
		while (true) {}
	}