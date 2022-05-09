#include"levelPage.h"
#include"PopUpModule.h"
LevelPage::LevelPage(unsigned char level) {
	/*
	设置不同关卡的
	*/
	_NOWLEVEL = level;
	//加载背景
    IMAGE img;//_backgroundSrc
	wchar_t backgroundSrc[22];
	for (int i = 0; i < 21; i++) {
		backgroundSrc[i] = _backgroundSrc[i];
	}
	backgroundSrc[21] = '\0';
	backgroundSrc[16] = level;
    loadimage(&img,backgroundSrc);
    putimage(0, 0, &img);
	//画矩形,即画迷宫的边界框
	setlinecolor(RGB(212, 123, 66));
	rectangle(18, 18, 926, 662);
	//初始化迷宫
	_MapRead.UpMap(level);//更新地图
	for (int x = 0; x < 41; ++x) {
		for (int y = 0; y < 29; ++y) {
			_Map[y][x] = _MapRead._Map[y][x];
			if (_Map[y][x] == '1') {
				_setBlockColor(x, y, 234, 123, 78);
			}
		}
	}
	//初始化人的位置
	_body.x = 1;
	_body.y = 1;
	_setLiangCang();//设置粮仓
}
void LevelPage::process(void) {
	//设置小人
	_moveBody(_body.x, _body.y );
	MOUSEMSG m;
	settextcolor(RGB(255,168,102));	
	settextstyle(38,22, _T("Consolas"));
	RECT r = { 1040, 231, 1257, 304 };
	//计数器 demo
	clock_t start = clock();
	//设置倒计时初始时间
	int SUMTIMES[8] = { 400,350,300,250,200,150,100,60 };
	int TIME = 1000;
	switch (_NOWLEVEL)
	{
	case '1':TIME = SUMTIMES[0]; break;
	case '2':TIME = SUMTIMES[1]; break;
	case '3':TIME = SUMTIMES[2]; break;
	case '4':TIME = SUMTIMES[3]; break;
	case '5':TIME = SUMTIMES[4]; break;
	case '6':TIME = SUMTIMES[5]; break;
	case '7':TIME = SUMTIMES[6]; break;
	case '8':TIME = SUMTIMES[7]; break;
	default:TIME = 1000;
		break;
	}
	int ss = TIME;
	while (1) {//循环事件监听
		if ((double)(clock() - start) / 1000.0 >= 1.0) {//时间监听
			ss--;
			_showTime(start,ss,&r);
		}
		//检测是否到达了终点
		if (_body.x == 40 && _body.y == 27) {
			_WinPoPWindow(start, ss);
			//重置计时
			ss = TIME;
		}
		//检查时间是否已经完了
		if (ss <= 0) {//结束此居，弹窗再接再厉
			_alertOver();
			//重置时间
			ss = TIME;
		}
		ExMessage message;
		if (peekmessage(&message, EM_CHAR|EM_MOUSE)) {//有按键输入
			if (message.message == WM_CHAR) {
				char input = message.ch;
				switch (input)
				{
				case 'w'://上
					_moveBody(_body.x, _body.y - 1);
					break;
				case 's'://下
					_moveBody(_body.x, _body.y + 1);
					break;
				case 'a'://左
					_moveBody(_body.x - 1, _body.y);
					break;
				case 'd'://右
					_moveBody(_body.x + 1, _body.y);
					break;
				default:
					break;
				}
			}
			if (message.lbutton)//鼠标事件
			{
				if (_getMouseState(message) == 0) {
					return;
				}
			}
		}
	}
}

//获得鼠标事件
int LevelPage::_getMouseState(ExMessage& m) {
    for (int i = 0; i < 2; i++) {
        if (_buttonDatas[i].ltx<m.x&&m.x<_buttonDatas[i].rbx) {
            if (_buttonDatas[i].lty < m.y && m.y < _buttonDatas[i].rby) {
                return i;
            }
        }
    }
    return -1;
}

//判断鼠标是否在一定的范围内
bool LevelPage::_judgeInRect(ExMessage& m, struct Rect rect) {
	if (m.x >= rect.ltx && m.x <= rect.rbx && m.y >= rect.lty && m.y <= rect.rby) {
		return true;
	}
	else {
		return false;
	}
}

//显示人物
void LevelPage::_setBodyImg(int x, int y) {
	//以22像素为长度
	struct Point point;
	//左上角为（20，20）
	int tlx = (x + 1) * 22;
	int tly = (y + 1) * 22;
	int rbx = tlx + 22;
	int rby = tly + 22;
	//加载人物图片
	IMAGE body;
	loadimage(&body, L"./img/cat.png");
	putimage(tlx, tly, &body);

}

//设置迷宫格颜色
void LevelPage::_setBlockColor(int x, int y, char r, char g, char b) {
	//以22像素为长度
	struct Point point;
	//左上角为（20，20）
	int tlx = (x + 1) * 22;
	int tly = (y + 1) * 22;
	int rbx = tlx + 22;
	int rby = tly + 22;
	for (int i = tlx; i < rbx; i++) {
		for (int j = tly; j < rby; j++) {
			point.x = i;
			point.y = j;
			_setUIBuffer(point, r, g, b);
		}
	}
}

//像素指针操作
void LevelPage::_setUIBuffer(struct Point point, char r, char g, char b) {
	// 获取指向显示缓冲区的指针
	DWORD* pMem = GetImageBuffer();
	// 直接对显示缓冲区赋值
	pMem[1280 * point.y + point.x] = BGR(RGB(r, g, b));
}

//将body移动
void LevelPage::_moveBody(int x, int y) {
	if (_Map[y][x] != '1') {
		//将现在的body不显示
		_setBlockColor(_body.x, _body.y, 255, 255, 255);
		//更新位置后的body进行显示
		_body.x = x;
		_body.y = y;
		_setBodyImg(_body.x, _body.y);
	}
}

//到达目的地的弹窗
void LevelPage::_WinPoPWindow(clock_t& start, int& ss) {
	PopUpModule popWindow;
	popWindow.show(L"./img/popWindow.png");
	start = clock();
	stringstream str_ss;
	str_ss << ss;
	string time_str = str_ss.str();
	const char* cstr = time_str.data();
	//字体框变为白色
	wchar_t ps[1000];
	swprintf_s(ps, L"还剩%S秒", cstr);//%S标志符表示字符串的char与wchar_t相互转换
	setfillcolor(RGB(80,80,80));
	solidrectangle(650,165,960,215);
	RECT r = { 650,165,960,215 };
	drawtext(ps, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);



	int points[4];
	popWindow.getBackButton(points);
	Rect backButton = { points[0],points[1], points[2], points[3] };
	ExMessage m;
	while (1) {
		//cout << "闯关弹窗事件监听\n";
		getmessage(&m);
		if (m.lbutton) {
				if (_judgeInRect(m, backButton)) {//退出
					cout << "点击叉号\n";
					popWindow.reset();
					//人回到终点并将终点涂白
					_setBlockColor(_body.x, _body.y, 255, 0, 0);
					_body.x = 0;
					_body.y = 1;
					_setLiangCang();
					return;
				}
			}
	}
}
void LevelPage::_alertOver() {
	PopUpModule popWindow;
	popWindow.show(L"./img/AlertOver.png");

	int points[4];
	popWindow.getBackButton(points);
	Rect backButton = { points[0],points[1], points[2], points[3] };
	ExMessage m;
	while (1) {
		getmessage(&m);
		if(m.lbutton)//鼠标事件
		{
			cout << "点击鼠标\n";
			if (_judgeInRect(m, backButton)) {//退出
				cout << "点击叉号\n";
				popWindow.reset();
				//人回到终点并将终点涂白
				_setBlockColor(_body.x, _body.y, 255, 0, 0);
				_body.x = 0;
				_body.y = 1;
				_setLiangCang();
				return;
			}
		}
	}
}

void LevelPage::_showTime(clock_t& start,int& ss,RECT *r) {
	start = clock();
	stringstream str_ss;
	str_ss << ss;
	string time_str = str_ss.str();
	const char* cstr = time_str.data();
	//字体框变为白色
	wchar_t ps[1000];
	swprintf_s(ps, L"%S", cstr);//%S标志符表示字符串的char与wchar_t相互转换
	drawtext(ps, r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	if (ss >= 100000) {
		ss = 0;
	}
}

//张贴粮仓图片
void LevelPage::_setLiangCang() {
	int x = 40, y = 27;
	_Map[y][x] = '0';
	//以22像素为长度
	struct Point point;
	//左上角为（20，20）
	int tlx = (x + 1) * 22;
	int tly = (y + 1) * 22;
	int rbx = tlx + 22;
	int rby = tly + 22;
	//加载人物图片
	IMAGE liangcang;
	loadimage(&liangcang, L"./img/liangcang.png");
	putimage(tlx, tly, &liangcang);
}