#pragma once
#ifndef __RECURSIONTRACING_H__
#define __RECURSIONTRACING_H__

class RecursionTracing {
	struct Point {
		int x;
		int y;
	};
private:
	int _width, _height;
	char** _Map;
	bool _judgePoint(int x, int y);
	void _algorithm(void);
	int Width ;
	int Height ;
	char wall ='1';
	char road ='0';
	int breakable[3][2];
	//À„∑®:Design by Œ§ §“¯
	int canBreak(int x, int y);
	void _deepFirst(int ltx, int lty);
	void createMap();
public:
	RecursionTracing(int width, int height);
	~RecursionTracing();
	void printMap(void);//¥Ú”°µÿÕº
	void setPoint(int x, int y, char val);
	char getPoint(int x, int y);
	void createMaze(void);//À¢–¬√‘π¨
	void resetMap(void);//÷ÿ÷√√‘π¨
};


#endif