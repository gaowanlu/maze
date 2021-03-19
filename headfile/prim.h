#pragma once
#ifndef __PRIM_H__
#define __PRIM_H__
#include<vector>
class Prim {
	struct Point {
		int x;
		int y;
	};
	struct Block {
		int x;
		int y;
		int direction;//0 up ,1 down,2 left,3right
	};
private:
	int _width, _height;
	char** _Map;
	bool _judgePoint(int x, int y);
	void _algorithm(void);
	void _addBlockToList(std::vector<struct Block>&list, struct Block p);
public:
	Prim(int width, int height);
	~Prim();
	void printMap(void);//¥Ú”°µÿÕº
	void setPoint(int x, int y, char val);
	char getPoint(int x, int y);
	void createMaze(void);//À¢–¬√‘π¨
	void resetMap(void);//÷ÿ÷√√‘π¨
};










#endif