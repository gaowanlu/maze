#include"RecursiveSegmentation.h"
#include<cstdlib>
#include<cstdio>

//构造函数
Division::Division(int width, int height) {
	_width = width;
	_height = height;
	this->width = width;
	this->height = height;
	_Map = (char**)malloc(sizeof(char*) * height);
	for (int i = 0; i < height; i++) {
		*(_Map + i) = (char*)malloc(sizeof(char) * width);
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			_Map[i][j] = '0';
		}
	}
}

//析构函数
Division::~Division() {
	for (int i = 0; i < _height; i++) {
		free(*(_Map + i));
	}
	free(_Map);
}

void Division::printMap(void) {
	if (!_Map) {
		return;
	}
	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			printf("%c", _Map[i][j]);
		}
		printf("\n");
	}
}

void Division::setPoint(int x, int y, char val) {
	_Map[y][x] = val;
}
char Division::getPoint(int x, int y) {
	return _Map[y][x];
}


//刷新迷宫函数
void Division::createMaze(void) {
	//最外面一圈为墙
	for (int i = 0; i < _height; i++) {
		_Map[i][0] = '1';
		_Map[i][_width-1] = '1';
	}
	for (int i = 0; i < _width; i++) {
		_Map[0][i] = '1';
		_Map[_height - 1][i] = '1';
	}
	//设置出口与入口
	_Map[_height - 2][_width - 1] = '0';
	//生成迷宫
	_Map[1][0] = '1';
	_algorithm(1, 1, _width - 2, _height - 2);
}

void Division::resetMap() {
	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			_Map[i][j] = '0';
		}
	}
}

//递归分割生成迷宫算法
void Division::_algorithm(int ltx, int lty, int rbx, int rby) {
	////判断是否还能继续分割
	if (rbx - ltx <= 1 || rby - lty <= 1) {//递归出口
		return;
	}
	//随机去一个点，十字划分的十字中心,中心点只能在偶数列与偶数行
	int x = ltx + 1 + rand() % (rbx - ltx - 1);
	int y = lty + 1 + rand() % (rby - lty - 1);


	//BUG解决:2020/12/27 ！最近太忙了！
	while (x % 2 != 0 || y % 2 != 0) {
		x = ltx + 1 + rand() % (rbx - ltx - 1);
		y = lty + 1 + rand() % (rby - lty - 1);
	}

	//画墙不能把上一次打的洞给堵住
	for (int i = ltx; i <= rbx; i++) {//竖着画墙
		_Map[y][i] = '1';
	}
	for (int i = lty; i <= rby; i++) {//横着画墙
		_Map[i][x] = '1';
	}
	////递归分割
	_algorithm(ltx, lty, x - 1, y - 1);
	_algorithm(x + 1, y + 1, rbx, rby);
	_algorithm(x + 1, lty, rbx, y - 1);
	_algorithm(ltx, y + 1, x - 1, rby);

	////随机取其中的三面墙
	int randWall[4] = { 0 };
	randWall[rand() % 4] = 1;

	////在墙上随机取点打洞
	for (int i = 0; i < 4; i++) {
		if (randWall[i] == 0) {//要打洞
			int rx = x;
			int ry = y;
			switch (i)
			{
				//判断改位置是否能确保打通相邻两块区域，判断依据，上下左右位置最多只有两面墙
			case 0:
				do {
					rx = ltx + rand() % (x - ltx);
				} while (_judgePoint(rx,y));
				break;
			case 1:
				do {
					ry = y + 1 + rand() % (rby - y);
				} while (_judgePoint(x, ry));
				break;
			case 2:
				do {
					rx = x + 1 + rand() % (rbx - x);
				} while (_judgePoint(rx, y));
				break;
			case 3:
				do {
					ry = lty + rand() % (y-lty);
				} while ( _judgePoint(x, ry));
				break;
			default:
				break;
			}
			_Map[ry][rx] = '0';
		}
	}




}

bool Division::_judgePoint(int x, int y) {
	int sum = 0;
	if (_Map[y - 1][x] == '0') {
		sum++;
	}
	if (_Map[y + 1][x] == '0') {
		sum++;
	}
	if (_Map[y][x - 1] == '0') {
		sum++;
	}
	if (_Map[y][x + 1] == '0') {
		sum++;
	}
	if (sum < 2) {//就是周围的墙小于等于2个
		return 1;
	}
	else {
		return 0;
	}
}

