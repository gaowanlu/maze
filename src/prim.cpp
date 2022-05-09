#include"prim.h"
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
using namespace std;
//Prim随机生成迷宫构造函数
Prim::Prim(int width, int height) {
	_width = width;
	_height = height;
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
Prim::~Prim() {
	for (int i = 0; i < _height; i++) {
		free(*(_Map + i));
	}
	free(_Map);
}




/*
Prim随机生成迷宫算法
1.让迷宫全是墙（ 实现: 外部调用 Prim::createMaze）
2.选一个单元格作为迷宫的通路(在此选择起点)，然后把它的邻墙（上下左右）放入列表
3.当列表里面还有墙时:
①.从列表里随机选一个墙，如果这面墙分隔的两个单元格只有一个单元格被访问过
	（a）从列表里面移除这面墙，这样就把墙打通了，让为访问过的单元格称为迷宫的通路
	（b）把这个格子的墙加入列表
②.如果墙两面的单元格都已经被访问过（都打通了），那就从列表里移除这面墙
*/      
void Prim::_algorithm(void) {
	srand((unsigned)time(NULL));//随机数种子
	Point start, end;
	struct Block pathfinder;
	start.x = 1;//起点
	start.y = 1;
	pathfinder.x = start.x;//探路者
	pathfinder.y = start.y;
	end.x = _width - 2;//终点
	end.y = _height - 2;
	vector<struct Block> list;//存放点
	//选起点作为迷宫的通路，将其它的上下左右放入列表
	_addBlockToList(list, pathfinder);
	while (list.size()) {
		int randnum = rand() % list.size();
		Block selectBlock = list[randnum];
		//探路者来到“选择的墙”这里
		pathfinder = selectBlock;
		//根据当前选择的墙的方向进行后续操作
		//此时，起始点 选择的墙 目标块 三块区域在同一直线上
		//我们让矿工从“选择的墙”继续前进到“目标块”
		//矿工有穿墙能力 ：)
		switch (selectBlock.direction) {
			case 1: {//下
				pathfinder.y++;
				break;
			}
			case 3: {//右
				pathfinder.x++;
				break;
			}
			case 2: {//左
				pathfinder.x--;
				break;
			}
			case 0: {//上
				pathfinder.y--;
				break;
			}
		}
		//目标块如果是墙
		if (_Map[pathfinder.y][pathfinder.x] == '1') {
			//打通墙和目标块
			_Map[selectBlock.y][selectBlock.x] = _Map[pathfinder.y][pathfinder.x] = '0';
			//再次找出与矿工当前位置相邻的墙
			_addBlockToList(list, pathfinder);
		}
		else {//如果不是呢？说明我们的矿工挖到了一个空旷的通路上面 休息一下就好了
			//relax
		}
		//删除这堵墙(把用不了的墙删了，对于那些已经施工过了不必再施工了，同时也是确保我们能跳出循环)
		list.erase(list.begin() + randnum);
	}
}

//将指定的点的上下左右合法的点加入到列表中
void Prim::_addBlockToList(vector<struct Block>&list, struct Block center) {
	struct Block p;
	p.x = center.x + 1;//右
	p.y = center.y;
	if (p.x >= 1 && p.y >= 1 && p.x <= _width - 2 && p.y <= _height - 2&&_Map[p.y][p.x]=='1') {
		p.direction = 3;
		list.push_back(p);
	}
	p.x = center.x - 1;//左
	p.y = center.y;
	if (p.x >= 1 && p.y >= 1 && p.x <= _width - 2 && p.y <= _height - 2 && _Map[p.y][p.x] == '1') {
		p.direction = 2;
		list.push_back(p);
	}
	p.x = center.x;//上
	p.y = center.y-1;
	if (p.x >= 1 && p.y >= 1 && p.x <= _width - 2 && p.y <= _height - 2 && _Map[p.y][p.x] == '1') {
		p.direction = 0;
		list.push_back(p);
	}
	p.x = center.x;//下
	p.y = center.y + 1;
	if (p.x >= 1 && p.y >= 1 && p.x <= _width - 2 && p.y <= _height - 2 && _Map[p.y][p.x] == '1') {
		p.direction = 1;
		list.push_back(p);
	}
}













bool Prim::_judgePoint(int x, int y) {
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


void Prim::printMap(void) {
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

void Prim::setPoint(int x, int y, char val) {
	_Map[y][x] = val;
}
char Prim::getPoint(int x, int y) {
	return _Map[y][x];
}


//刷新迷宫函数
void Prim::createMaze(void) {
	//让迷宫全部都为墙
	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			_Map[i][j] = '1';
		}
	}
	_Map[1][0] = '1';
	_Map[_height - 2][_width - 1] = '0';//粮仓位置
	//起点置为'0'
	_Map[1][1] = '0';
	_algorithm();//Prim随机生成迷宫算法
}

void Prim::resetMap() {
	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			_Map[i][j] = '0';
		}
	}
}