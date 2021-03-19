#pragma once
#ifndef __INDEXPAGE_H__
#define __INDEXPAGE_H__
#include"matrixUI.h"
#include"breakthroughPage.h"
#include<ctime>
class IndexPage {
struct Rect {
		int ltx;
		int rbx;
		int lty;
		int rby;
};	
private:
	MatrixUI& UI;
	struct Rect _buttonRange[3] = {
	{500 + 120, 500 + 673, 50 + 105, 50 + 207},
	{500 + 136, 500 + 672, 50 + 264 , 50 + 367},
	{500 + 133, 500 + 684, 50 + 427, 50 + 528}
	};
	void _buttonHover(bool button[3], MOUSEMSG& m);
	bool _judgeInRect(MOUSEMSG& m, struct Rect rect);//判断鼠标是否在矩形范围内
	bool _lastHoverStatus[3] = {0};//保存上一次移动鼠标的hover状态
	bool _diffHoverStatus(bool button[3]);//判断这一次与上一次是否有变化
	void _setLastHoverStatus(bool button[3]);//更新这一次的hover状态
	void _resetAll(void);//重置界面，跳出对象时
public:
	IndexPage(MatrixUI& UI);
	int process(void);
};








#endif