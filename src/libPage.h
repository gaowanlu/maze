#pragma once
#ifndef __LIBPAGE_H__
#define __LIBPAGE_H__
#include"matrixUI.h"
#include"PopUpModule.h"//弹窗模块
class LibPage {
struct Rect {
		int ltx;
		int rbx;
		int lty;
		int rby;
};
private:
	MatrixUI&UI;
	struct Rect _buttonRange[7] = {
	{968,1240, 44,100},
	{968,1240, 109 , 163},
	{968,1240, 173,230},
	{982,1100,382,510},
	{1136,1228,440,507},
	{1000,1200,579,626},
	{968,1240,251,299}//反转迷宫按钮
	};

	int _width = 42, _height = 29;
	bool _game = false;//是否为可游戏模式
	struct Point _body = { 0,1 };
	bool _judgeInRect(ExMessage& m, struct Rect rect);//判断鼠标是否在矩形范围内
	void _setBlockColor(int x,int y,char r,char g,char b);
	void _setUIBuffer(struct Point point, char r, char g, char b);
	void _createMap(int type);//不同算法产生随机地图并将图形界面更新到窗口上面
	void _moveBody(int x, int y);//将body移动
	void _WinPoPWindow(void);//到达目的地的弹窗
	void _findRoadAndShow(void);//寻找路径以及显示路径
	void _defaultInit(void);//默认迷宫生成
	void _setBodyImg(int x, int y);//显示人物
	void _setLiangCang();//张贴画粮仓图像
	//靠近中央随机位置设置老鼠位置,这个位置需满足不是墙
	void _setRandomBody();
	//反转迷宫，并重置粮仓，以及老鼠位置等
	void _reverseMap();
	bool reverseStatus = false;
public:
	char _Map[29][41];
	LibPage(MatrixUI& UI);
	int process(void);
	void printMap(void);
};







#endif