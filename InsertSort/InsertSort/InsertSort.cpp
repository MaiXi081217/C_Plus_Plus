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

void insertSort(column a[], int n)
{
	BeginBatchDraw();
	for (int i = 1; i < n; i++) //第一个元素作为基准元素，从第二个元素开始把其插到正确的位置
	{

		if (a[i].num < a[i - 1].num) //如果第i个元素比前面的元素小
		{
			int j = i - 1;     //需要判断第i个元素与前面的多个元素的大小，换成j继续判断
			column x = a[i]; //将第i个元素复制为哨兵
			while (j >= 0 && x.num < a[j].num) //找哨兵的正确位置，比哨兵大的元素依次后移
			{
				FlushBatchDraw();
				a[j + 1] = a[j];
				j--;
			}
			a[j + 1] = x;  //把哨兵插入到正确的位置
			i_tmp.num = j + 1;
			j_tmp.num = x.num;
			Draw(a);
		}
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
	insertSort(square, LENTH);
	EndBatchDraw();
	while (true) {}
}