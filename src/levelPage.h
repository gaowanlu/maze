#pragma once
#ifndef __LEVELPAGE_H__
#define __LEVELPAGE_H__
#include"matrixUI.h"
#include"mapread.h"
#include<ctime>
#include <sstream>
#include <string>
#include <iostream>
#include <locale>
#include <cstdlib>
class LevelPage {
	struct Rect {
		int ltx;
		int rbx;
		int lty;
		int rby;
	};

private:
	//地图文件读取
	MapRead _MapRead;
	//@闯关页面的背景图片
	const wchar_t *_backgroundSrc=L"./img/levelPage/1.png";
	//按键位置
	struct Rect _buttonDatas[2]={
		{1042,1198,634,685},
		{2,6,7,8}
	};
	//此时的关卡
	char _NOWLEVEL;
	int _getMouseState(ExMessage& m);
	bool _judgeInRect(ExMessage& m, struct Rect rect);
	//存储人的位置
	Point _body;
	//存储迷宫地图
	char _Map[29][41];
	void _setBodyImg(int x, int y);//显示人物
	void _setBlockColor(int x, int y, char r, char g, char b);//设置迷宫格颜色
	void _setUIBuffer(struct Point point, char r, char g, char b);//像素指针操作
	void _moveBody(int x, int y);
	void _WinPoPWindow(clock_t& start, int& ss);
	void _showTime(clock_t& start,int&ss, RECT* r);
	void _setLiangCang();
	void _alertOver();
public:
	LevelPage(unsigned char level);
	void process(void);
};
#endif
