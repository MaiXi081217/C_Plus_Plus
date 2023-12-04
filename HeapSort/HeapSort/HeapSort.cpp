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

void max_heapify(column a[], int len, int i)
{
	int l = i * 2 + 1;  //左节点
	int r = i * 2 + 2;  //右节点
	int m = i;

	// 找出最大值节点
	if (l < len && a[l].num > a[m].num) {
		m = l;
	}
	if (r < len && a[r].num > a[m].num) {
		m = r;
	}
	if (m != i) {
		// 把当前节点设为最大，递归调整子节点
		swap(a[i], a[m]);
		max_heapify(a, len, m);
	}
}

// 建堆
void build_max_heap(column a[], int len)
{
	for (int i = len / 2 - 1; i >= 0; i--) {
		max_heapify(a, len, i);
	}
}

// 堆排序
void heap_sort(column a[], int len)
{
	build_max_heap(a, len);
	BeginBatchDraw();
	for (int i = len - 1; i > 0; i--) {
		FlushBatchDraw();
		i_tmp.num = a[i].num;
		j_tmp.num = a[0].num;
		swap(a[i], a[0]);
		max_heapify(a, i, 0);
		Draw(a);
		Sleep(30);
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
	heap_sort(square, LENTH);
	EndBatchDraw();
	while (true) {}
}