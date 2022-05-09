#pragma once
#include"matrixUI.h"
#ifndef __POPUPMODULE_H__
#define __POPUPMODULE_H__
class PopUpModule {
	struct Rect {
		int ltx;
		int rbx;
		int lty;
		int rby;
	};
private:
	int _screenWidth=1280, _screenHeight=720;
	int _popWidth, _popHeight;
	IMAGE _oldImg;
	IMAGE _newImg;
	struct Rect _backButton;
public:
	void reset(void);//关闭弹窗
	void show(const wchar_t* filename);//显示弹窗
	void getBackButton(int *point);//返回退出按钮
};
#endif