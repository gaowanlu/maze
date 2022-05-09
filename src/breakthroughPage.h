#pragma once
#ifndef __BREAKTHROUGHPAGE_H__
#define __BREAKTHROUGHPAGE_H__
#include"matrixUI.h"
#include"levelPage.h"
class BreakthroughPage {
	struct Rect {
		int ltx;
		int rbx;
		int lty;
		int rby;
	};
private:
	MatrixUI UI;
	struct Rect _buttonRange[9] = {
	{48,296,39,269},
	{373,623,39,273},
	{689,936,39,273},
	{987,1230,39,273},
	{48,296,350,587},
	{373,623,350,587},
	{689,936,350,587},
	{987,1230,350,587},
	{21,79,653,700}
	};
	bool _lastHoverStatus[9] = {0};//保存上一次移动鼠标的hover状态
	bool _judgeInRect(MOUSEMSG& m, struct Rect rect);
	void _buttonHover(bool button[9], MOUSEMSG& m);
	void _resizeButton(bool button[9],int target);
	int _mClick(MOUSEMSG& m);
	void _resetUI(void);
public:
	BreakthroughPage(MatrixUI& UI);
	int process(void);
};


#endif