#pragma once
#ifndef __MATRIXUI_H__
#define __MATRIXUI_H__
#include<iostream>
#include <graphics.h>
#include <conio.h>
#include <easyx.h>
#include<windows.h>
using namespace std;
struct Point {
		int x;
		int y;
};
class MatrixUI {

public:
	MatrixUI();
	void init(int width, int height);//创建界面
	void close(void);//关闭界面
	bool getInitFlag(void);//获得是否创建了界面
	void setBkColor(char r,char g,char b);//设置背景图像颜色
	void setUIBuffer(struct Point, char r, char g, char b);//设置像素颜色
	int	 getWidth(void);
	int	 getHeight(void);
private:
	bool _initFlag = false;//是否创建了界面
	int _width = 0;
	int _height = 0;
};



#endif
