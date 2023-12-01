#include<iostream>
#include<easyx.h>		//包含图形库头文件
#include<stdlib.h>
#include<time.h>
using namespace std;
//定义场景大小
#define WIDTH 1040
#define HEIGHT 640
//定义食物以及蛇的大小
#define SIZE  15
//定义蛇的朝向
#define UP 1
#define DOWN -1
#define LEFT 2
#define RIGHT -2
//蛇的最大长度
#define MAXLEN 1600


typedef struct {
	int x;
	int y;
}SnakeNode;

SnakeNode tmp[MAXLEN];	//用另外一个数组来存储蛇原来的位置
int speed = 80;		//蛇的速度(用在睡眠函数里面)

//创建蛇的类
class Snake
{
	friend class Food;
public:
	Snake();					//初始化
	void Move();				//移动
	void Draw();				//绘制蛇
	bool Eat(Food food);	    //吃食物
	bool Defeat();				//失败判定
private:
	int dirt;					//朝向
	int length;					//长度
	SnakeNode node[MAXLEN];		//蛇的结点
};

//创建食物的类
class Food
{
	friend class Snake;
public:
	Food(Snake snake);			//食物初始化
	void Draw();				//绘制食物
private:
	int x, y;					//坐标
};

int main() {
	initgraph(WIDTH, HEIGHT);
	Snake snake;
	Food food_tmp(snake);
	int flog = 0;
table:
	Food food(snake);
	Food food2(snake);
	if (flog == 1) {
		food2 = food_tmp;
	}
	else if (flog == 2) {
		food = food_tmp;
	}
	while (1) {
		BeginBatchDraw();
		FlushBatchDraw();
		snake.Draw();
		food.Draw();
		food2.Draw();
		if (snake.Eat(food)){
			food_tmp = food2;
			flog = 1;
			goto table;

		}
		else if (snake.Eat(food2)) {
			food_tmp = food;
			flog = 2;
			goto table;
		}
		if (snake.Defeat()) {
			break;
		}
		snake.Move();
	}
	//提示失败信息
	HWND window = GetHWnd();
	SetWindowText(window, L"提示");
	MessageBox(window, L"游戏失败", L"提示", MB_OKCANCEL);
	return 0;
}

//蛇的初始化
Snake::Snake()
{
	this->dirt = RIGHT;
	this->length = 3;
	//下标是0的位置为蛇的头部
	for (int i = 0; i < length; i++) {
		this->node[i].x = 60 - ((i + 1) * SIZE);
		this->node[i].y = 0;
	}
}

//移动
void Snake::Move() {
	//将原来的蛇结点拷贝一份
	for (int i = 0; i < this->length; i++) {
		tmp[i].x = this->node[i].x;
		tmp[i].y = this->node[i].y;
	}
	int status = 0;//用来判断是否点击了转向按键
	if (this->dirt == RIGHT) {
		//判断是否转向
		if (GetAsyncKeyState('W') && status == 0) {
			//this->node[0].y -= SIZE;
			this->dirt = UP;
			status = 1;
		}
		else if (GetAsyncKeyState('S') && status == 0) {
			this->dirt = DOWN;
			status = 1;
		}
		else {
			this->node[0].x += SIZE;
		}
	}
	if (this->dirt == DOWN) {
		//判断是否转向
		if (GetAsyncKeyState('A') && status == 0) {
			//this->node[0].x -= SIZE;
			this->dirt = LEFT;
			status = 1;
		}
		else if (GetAsyncKeyState('D') && status == 0) {
			this->node[0].x += SIZE;
			this->dirt = RIGHT;
			status = 1;
		}
		else {
			this->node[0].y += SIZE;
		}
	}
	if (this->dirt == LEFT) {
		//判断是否转向
		if (GetAsyncKeyState('W') && status == 0) {
			//this->node[0].y -= SIZE;
			this->dirt = UP;
			status = 1;
		}
		else if (GetAsyncKeyState('S') && status == 0) {
			this->node[0].y += SIZE;
			this->dirt = DOWN;
			status = 1;
		}
		else {
			this->node[0].x -= SIZE;
		}
	}
	if (this->dirt == UP) {
		//判断是否转向
		if (GetAsyncKeyState('A') && status == 0) {
			this->node[0].x -= SIZE;
			this->dirt = LEFT;
			status = 1;
		}
		else if (GetAsyncKeyState('D') && status == 0) {
			this->node[0].x += SIZE;
			this->dirt = RIGHT;
			status = 1;
		}
		else {
			this->node[0].y -= SIZE;
		}
	}
	//移动
	for (int i = 1; i < this->length; i++) {
		this->node[i].x = tmp[i - 1].x;
		this->node[i].y = tmp[i - 1].y;
	}
	Sleep(speed);
}

//绘制蛇
void Snake::Draw() {
	cleardevice();//清空原先的绘图
	for (int i = 0; i < this->length; i++) {
		setfillcolor(GREEN);
		fillrectangle(this->node[i].x, this->node[i].y, this->node[i].x + SIZE, this->node[i].y + SIZE);
	}
}

//吃食物
bool Snake::Eat(Food food) {
	if (food.x == this->node[0].x && food.y == this->node[0].y) {
		if (this->node[length - 1].x - this->node[length - 2].x == 0 && this->node[length - 1].y - this->node[length - 2].y == -SIZE) {
			this->length++;
			this->node[length - 1].x = this->node[length - 2].x;
			this->node[length - 1].y = this->node[length - 2].y - SIZE;
		}
		if (this->node[length - 1].x - this->node[length - 2].x == 0 && this->node[length - 1].y - this->node[length - 2].y == SIZE) {
			this->length++;
			this->node[length - 1].x = this->node[length - 2].x;
			this->node[length - 1].y = this->node[length - 2].y + SIZE;
		}
		if (this->node[length - 1].x - this->node[length - 2].x == SIZE && this->node[length - 1].y - this->node[length - 2].y == 0) {
			this->length++;
			this->node[length - 1].x = this->node[length - 2].x + SIZE;
			this->node[length - 1].y = this->node[length - 2].y;
		}
		if (this->node[length - 1].x - this->node[length - 2].x == -SIZE && this->node[length - 1].y - this->node[length - 2].y == 0) {
			this->length++;
			this->node[length - 1].x = this->node[length - 2].x - SIZE;
			this->node[length - 1].y = this->node[length - 2].y;
		}

		return true;
	}
	return false;
}

//失败判定
bool Snake::Defeat() {
	//1.碰到边界
	if (this->node[0].x < 0 || this->node[0].x >= WIDTH || this->node[0].y < 0 || this->node[0].y >= HEIGHT) {
		return true;
	}
	//2.碰到自己的身体
	for (int i = 1; i < this->length; i++) {
		if (this->node[0].x == this->node[i].x && this->node[0].y == this->node[i].y) {
			return true;
		}
	}
	return false;
}

//食物的初始化
Food::Food(Snake snake)
{
table:
	this->x = (rand() % (WIDTH / SIZE)) * SIZE;
	this->y = (rand() % (HEIGHT / SIZE)) * SIZE;
	for (int i = 0; i < snake.length; i++) {
		if (snake.node[i].x == this->x && snake.node[i].y == this->y) {
			goto table;
		}
	}
}

//绘制食物
void Food::Draw() {
	setfillcolor(YELLOW);
	fillrectangle(this->x, this->y, this->x + SIZE, this->y + SIZE);
}