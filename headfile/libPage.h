#pragma once
#ifndef __LIBPAGE_H__
#define __LIBPAGE_H__
#include"./matrixUI.h"
#include"./PopUpModule.h"//弹窗模块
class LibPage {
struct Rect {
		int ltx;
		int rbx;
		int lty;
		int rby;
};
private:
	MatrixUI&UI;
	struct Rect _buttonRange[6] = {
	{968,1240, 44,100},
	{968,1240, 109 , 163},
	{968,1240, 173,230},
	{982,1100,382,510},
	{1136,1228,440,507},
	{1000,1200,579,626}
	};
	
	int _width = 42, _height = 29;
	bool _game = false;//是否为可游戏模式
	struct Point _body = { 0,1 };
	bool _judgeInRect(MOUSEMSG& m, struct Rect rect);//判断鼠标是否在矩形范围内
	void _setBlockColor(int x,int y,char r,char g,char b);
	void _setUIBuffer(struct Point point, char r, char g, char b);
	void _createMap(int type);//不同算法产生随机地图并将图形界面更新到窗口上面
	void _moveBody(int x, int y);//将body移动
	void _WinPoPWindow(void);//到达目的地的弹窗
	void _findRoadAndShow(void);//寻找路径以及显示路径
	void _defaultInit(void);//默认迷宫生成
	void _setBodyImg(int x, int y);//显示人物
public:
	char _Map[29][41];
	LibPage(MatrixUI& UI);
	int process(void);
	void printMap(void);
};







#endif