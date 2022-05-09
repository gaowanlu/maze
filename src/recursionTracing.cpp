#include"recursionTracing.h"
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>

using namespace std;
//递归回溯随机生成迷宫构造函数
RecursionTracing::RecursionTracing(int width, int height) {
	_width = width;
	_height = height;
	this->Width = width;
	this->Height = height;
	_Map = (char**)malloc(sizeof(char*) * height);
	for (int i = 0; i < height; i++) {
		*(_Map + i) = (char*)malloc(sizeof(char) * width);
	}
	for (int i = 0; i < height; i++) {//初始化全部赋为'0'
		for (int j = 0; j < width; j++) {
			_Map[i][j] = '0';
		}
	}
}
RecursionTracing::~RecursionTracing() {
	for (int i = 0; i < _height; i++) {
		free(*(_Map + i));
	}
	free(_Map);
}



void RecursionTracing::_algorithm(void) {
	createMap();
}





bool RecursionTracing::_judgePoint(int x, int y) {
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


void RecursionTracing::printMap(void) {
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

void RecursionTracing::setPoint(int x, int y, char val) {
	_Map[y][x] = val;
}
char RecursionTracing::getPoint(int x, int y) {
	return _Map[y][x];
}


//刷新迷宫函数
void RecursionTracing::createMaze(void) {
	//让迷宫全部都为墙
	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			_Map[i][j] = '1';
		}
	}

	_Map[_height - 2][_width - 1] = '0';
	//起点置为'0'
	//_Map[1][1] = '0';
	_algorithm();//Prim随机生成迷宫算法
	_Map[1][0] = '1';
}

void RecursionTracing::resetMap() {
	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			_Map[i][j] = '0';
		}
	}
}


/**
 * 判断_Map[y][x]处是否有可以连接的节点
 * 将节点保存到breakable中
 * @param x 横坐标
 * @param y 纵坐标
 * @return 可以连接的节点个数
 */
int RecursionTracing::canBreak(int x, int y) {
	int n = 0;
	if (x > 1) {
		//右边
		if (_Map[y][x - 2] == wall) {
			breakable[n][0] = x - 2;
			breakable[n++][1] = y;
		}
	}
	if (x < Width - 2) {
		//左边
		if (_Map[y][x + 2] == wall) {
			breakable[n][0] = x + 2;
			breakable[n++][1] = y;
		}
	}
	if (y > 1) {
		//上面
		if (_Map[y - 2][x] == wall) {
			breakable[n][0] = x;
			breakable[n++][1] = y - 2;
		}
	}
	if (y < Height - 2) {
		//下面
		if (_Map[y + 2][x] == wall) {
			breakable[n][0] = x;
			breakable[n++][1] = y + 2;
		}
	}
	return n;
}

/**
* 深度优先法生成迷宫
* @param ltx 开始的横坐标，
* @param lty 开始的纵坐标。
 */
void RecursionTracing::_deepFirst(int ltx, int lty) {
	_Map[lty][ltx] = road;
	for (int i = canBreak(ltx, lty); i > 0; i = canBreak(ltx, lty)) {
		int n = rand() % i;
		_Map[(lty + breakable[n][1]) / 2][(ltx + breakable[n][0]) / 2] = road;
		_deepFirst(breakable[n][0], breakable[n][1]);
	}
}


void RecursionTracing::createMap() {
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			_Map[i][j] = wall;
		}
	}
	_Map[Height - 2][Width - 1] = road;
	_Map[1][0] = road;
	_deepFirst(1, 1);
}
