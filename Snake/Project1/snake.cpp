#include<iostream>
#include<easyx.h>		//����ͼ�ο�ͷ�ļ�
#include<stdlib.h>
#include<time.h>
using namespace std;
//���峡����С
#define WIDTH 1040
#define HEIGHT 640
//����ʳ���Լ��ߵĴ�С
#define SIZE  15
//�����ߵĳ���
#define UP 1
#define DOWN -1
#define LEFT 2
#define RIGHT -2
//�ߵ���󳤶�
#define MAXLEN 1600


typedef struct {
	int x;
	int y;
}SnakeNode;

SnakeNode tmp[MAXLEN];	//������һ���������洢��ԭ����λ��
int speed = 80;		//�ߵ��ٶ�(����˯�ߺ�������)

//�����ߵ���
class Snake
{
	friend class Food;
public:
	Snake();					//��ʼ��
	void Move();				//�ƶ�
	void Draw();				//������
	bool Eat(Food food);	    //��ʳ��
	bool Defeat();				//ʧ���ж�
private:
	int dirt;					//����
	int length;					//����
	SnakeNode node[MAXLEN];		//�ߵĽ��
};

//����ʳ�����
class Food
{
	friend class Snake;
public:
	Food(Snake snake);			//ʳ���ʼ��
	void Draw();				//����ʳ��
private:
	int x, y;					//����
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
	//��ʾʧ����Ϣ
	HWND window = GetHWnd();
	SetWindowText(window, L"��ʾ");
	MessageBox(window, L"��Ϸʧ��", L"��ʾ", MB_OKCANCEL);
	return 0;
}

//�ߵĳ�ʼ��
Snake::Snake()
{
	this->dirt = RIGHT;
	this->length = 3;
	//�±���0��λ��Ϊ�ߵ�ͷ��
	for (int i = 0; i < length; i++) {
		this->node[i].x = 60 - ((i + 1) * SIZE);
		this->node[i].y = 0;
	}
}

//�ƶ�
void Snake::Move() {
	//��ԭ�����߽�㿽��һ��
	for (int i = 0; i < this->length; i++) {
		tmp[i].x = this->node[i].x;
		tmp[i].y = this->node[i].y;
	}
	int status = 0;//�����ж��Ƿ�����ת�򰴼�
	if (this->dirt == RIGHT) {
		//�ж��Ƿ�ת��
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
		//�ж��Ƿ�ת��
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
		//�ж��Ƿ�ת��
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
		//�ж��Ƿ�ת��
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
	//�ƶ�
	for (int i = 1; i < this->length; i++) {
		this->node[i].x = tmp[i - 1].x;
		this->node[i].y = tmp[i - 1].y;
	}
	Sleep(speed);
}

//������
void Snake::Draw() {
	cleardevice();//���ԭ�ȵĻ�ͼ
	for (int i = 0; i < this->length; i++) {
		setfillcolor(GREEN);
		fillrectangle(this->node[i].x, this->node[i].y, this->node[i].x + SIZE, this->node[i].y + SIZE);
	}
}

//��ʳ��
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

//ʧ���ж�
bool Snake::Defeat() {
	//1.�����߽�
	if (this->node[0].x < 0 || this->node[0].x >= WIDTH || this->node[0].y < 0 || this->node[0].y >= HEIGHT) {
		return true;
	}
	//2.�����Լ�������
	for (int i = 1; i < this->length; i++) {
		if (this->node[0].x == this->node[i].x && this->node[0].y == this->node[i].y) {
			return true;
		}
	}
	return false;
}

//ʳ��ĳ�ʼ��
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

//����ʳ��
void Food::Draw() {
	setfillcolor(YELLOW);
	fillrectangle(this->x, this->y, this->x + SIZE, this->y + SIZE);
}