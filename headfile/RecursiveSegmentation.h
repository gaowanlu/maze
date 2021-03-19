#pragma once
#ifndef __RECURSIVESEGMENTATION_H__
#define __RECURSIVESEGMENTATION_H__
class Division {
	private:
		char** _Map;
		int _width;
		int _height;
		void _algorithm(int tlx,int tly,int rbx,int rby);
		bool _judgePoint(int x, int y);
	public:
		int width;//水平长度即为x的长度
		int height;//竖直长度即为y的长度
		Division(int width, int height);//构造函数
		~Division();//析构函数
		void printMap(void);//打印地图
		void setPoint(int x, int y, char val);
		char getPoint(int x, int y);
		void createMaze(void);//刷新迷宫
		void resetMap(void);//重置迷宫
};


#endif