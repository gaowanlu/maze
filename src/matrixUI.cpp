#include"matrixUI.h"
//构造函数
MatrixUI::MatrixUI() {

}

//私有方法
bool MatrixUI::getInitFlag(void) {//获得是否已经创建界面
	return _initFlag;
}
void MatrixUI::init(int width, int height) {//创建界面
	if (width < 500 || width>10000 || height < 500 || height>10000) {
		return;
	}
	if (_initFlag == false) {//只能创建一次图形界面
		initgraph(width, height, EW_SHOWCONSOLE);
		//initgraph(width, height);
		_initFlag = true;
		_width = width;
		_height = height;
		setorigin(0,0);//设置原点坐标
	}
}
void MatrixUI::close(void) {//关闭界面
	if (getInitFlag()) {
		closegraph();
		_initFlag = false;
		_width = 0;
		_height = 0;
	}
}

void MatrixUI::setBkColor(char r, char g, char b) {//设置背景图像颜色
	if (getInitFlag() == false) {
		return;
	}
	// 设置背景色为蓝色
	setbkcolor(RGB(r,g,b));
	// 用背景色清空屏幕
	cleardevice();
}

void MatrixUI::setUIBuffer(struct Point point, char r, char g, char b) {
	if (_initFlag == false || point.x < 0 || point.x >= _width || point.y < 0 || point.y >= _height) {
		return;
	}
	// 获取指向显示缓冲区的指针
	DWORD* pMem = GetImageBuffer();
	// 直接对显示缓冲区赋值
	pMem[_width * point.y + point.x] = BGR(RGB(r, g, b));
}

int	 MatrixUI::getWidth(void) {
	return _width;
}
int	 MatrixUI::getHeight(void) {
	return _height;
}
