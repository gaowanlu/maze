#include"libPage.h"
#include"RecursiveSegmentation.h"//递归分割
#include"prim.h"//Prim
#include"recursionTracing.h"//递归回溯
#include"MazePathFind.h"//dfs寻径

//972 251 1241 299

LibPage::LibPage(MatrixUI& UI):UI(UI){//构造函数
	for (int i = 0; i < 41; i++) {
		for (int j = 0; j < 29; j++) {
			_Map[j][i] = '0';
		}
	}
}

int LibPage::process(void) {
	//贴页面图
	IMAGE img;
	loadimage(&img, _T("./img/libPage.png"));
	putimage(0, 0, &img);
	//画矩形,即画迷宫的边界框
	setlinecolor(RGB(212,123,66));
	rectangle(18,18,926,662);
	//实验室默认调用Prim生成迷宫
	_defaultInit();

	MOUSEMSG m;//鼠标事件
	while (1) {
		//检测是否到达了终点
		if (_body.x == 40 && _body.y == 27) {
			_WinPoPWindow();//弹窗
			_setRandomBody();//重新设置老鼠的位置
		}
		ExMessage message;
		if (peekmessage(&message, EM_CHAR | EM_MOUSE)) {//有按键输入
			if (_game && message.message == WM_CHAR) {
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
				if (_judgeInRect(message, _buttonRange[5])) {//退出
					_game = false;
					return 0;
				}
				if (_judgeInRect(message, _buttonRange[2])) {//递归分割
					reverseStatus = false;
					_createMap(3);
					//人的坐标初始化
					_setRandomBody();
					//设置粮仓
					_setLiangCang();
				}
				else if (_judgeInRect(message, _buttonRange[1])) {//递归回溯
					reverseStatus = false;
					_createMap(2);
					//人的坐标初始化
					_setRandomBody();
					//设置粮仓
					_setLiangCang();
				}
				else if (_judgeInRect(message, _buttonRange[0])) {//Prim生成迷宫
					reverseStatus = false;
					_createMap(1);
					//人的坐标初始化
					_setRandomBody();
					//设置粮仓
					_setLiangCang();
				}
				else if (_judgeInRect(message, _buttonRange[3])) {
					reverseStatus = false;
					_game = _game ? false : true;
				}
				else if (_judgeInRect(message, _buttonRange[4]) && reverseStatus == false) {//迷宫寻径
					_findRoadAndShow();
					//设置粮仓
					_setLiangCang();
				}
				else if (_judgeInRect(message, _buttonRange[6])) {//反转迷宫
					reverseStatus = !reverseStatus;
					cout << "反转迷宫\n";
					_reverseMap();
				}
			}
		}
	}

}//process



void LibPage::_setBlockColor(int x, int y, char r, char g, char b) {
	//以22像素为长度
	struct Point point;
	//左上角为（20，20）
	int tlx = (x+1)*22;
	int tly = (y+1)*22;
	int rbx = tlx+22;
	int rby = tly + 22;
	for (int i = tlx; i < rbx; i++) {
		for (int j = tly; j < rby; j++) {
			point.x = i;
			point.y = j;
			_setUIBuffer(point, r, g, b);
		}
	}
}

void LibPage::_setUIBuffer(struct Point point, char r, char g, char b) {
	// 获取指向显示缓冲区的指针
	DWORD* pMem = GetImageBuffer();
	// 直接对显示缓冲区赋值
	pMem[1280 * point.y + point.x] = BGR(RGB(r, g, b));
}


bool LibPage::_judgeInRect(ExMessage& m, struct Rect rect) {
	if (m.x >= rect.ltx && m.x <= rect.rbx && m.y >= rect.lty && m.y <= rect.rby) {
		return true;
	}
	else {
		return false;
	}
}


void LibPage::_createMap(int type) {
	if (type == 1) {//随机prim
		Prim map(41, 29);
		map.createMaze();
		//更新界面显示
		for (int i = 0; i < 41; i++) {
			for (int j = 0; j < 29; j++) {
				if (map.getPoint(i, j) == '1') {//墙
					_setBlockColor(i, j, 234, 123, 78);
				}
				else if (map.getPoint(i, j) == '0') {//空
					_setBlockColor(i, j, 255, 255, 255);
				}
			}
		}
		//更新_Map
		for (int i = 0; i < 41; i++) {
			for (int j = 0; j < 29; j++) {
				_Map[j][i] = map.getPoint(i, j);
			}
		}
		this->printMap();//打印地图		
	}
	else if (type == 2) {//回溯递归
		RecursionTracing map(41, 29);
		map.createMaze();
		//更新界面显示
		for (int i = 0; i < 41; i++) {
			for (int j = 0; j < 29; j++) {
				if (map.getPoint(i, j) == '1') {//墙
					_setBlockColor(i, j, 234, 123, 78);
				}
				else if (map.getPoint(i, j) == '0') {//空
					_setBlockColor(i, j, 255, 255, 255);
				}
			}
		}
		//更新_Map
		for (int i = 0; i < 41; i++) {
			for (int j = 0; j < 29; j++) {
				_Map[j][i] = map.getPoint(i, j);
			}
		}
		this->printMap();//打印地图	
	}
	else if (type == 3) {//递归分割
		Division map(41, 29);
		map.createMaze();
		//更新界面显示
		for (int i = 0; i < 41; i++) {
			for (int j = 0; j < 29; j++) {
				if (map.getPoint(i, j) == '1') {//墙
					_setBlockColor(i, j, 234, 123, 78);
				}
				else if (map.getPoint(i, j) == '0') {//空
					_setBlockColor(i, j, 255, 255, 255);
				}
			}
		}
		//更新_Map
		for (int i = 0; i < 41; i++) {
			for (int j = 0; j < 29; j++) {
				_Map[j][i] = map.getPoint(i, j);
			}
		}
		this->printMap();//打印地图
	}
}

void LibPage::printMap(void) {
	for (int i = 0; i < 29; i++) {
		for (int j = 0; j < 41; j++) {
			printf("%c", _Map[i][j]);
		}
		printf("\n");
	}
}

//将body移动
void LibPage::_moveBody(int x, int y) {
	if (x < 0 || x>40 || y < 0 || y>28) {//不合法位置
		return;
	}
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
void LibPage::_WinPoPWindow(void) {
	PopUpModule popWindow;
	popWindow.show(L"./img/popWindow.png");
	int points[4];
	popWindow.getBackButton(points);
	Rect backButton = { points[0],points[1], points[2], points[3] };
	ExMessage message;
	while (1) {
		if (peekmessage(&message)) {
			if (message.lbutton) {
				if (_judgeInRect(message, backButton)) {//退出
					cout << "点击叉号\n";
					popWindow.reset();
					//人回到终点并将终点涂白
					_setBlockColor(_body.x, _body.y, 255, 0, 0);
					_body.x = 0;
					_body.y = 1;
					//重新设置粮仓
					_setLiangCang();
					return;
				}
			}
		}
	}	
}


void LibPage::_findRoadAndShow(void) {
	char** temp=NULL;
	//先将_Map拷贝一份这样才能将地址传给外部
	temp = (char**)malloc(sizeof(char*) * _height);
	for (int i = 0; i < _height; ++i) {
		temp[i] = (char*)malloc(sizeof(char) * _width);
	}
	//拷贝
	for (int i = 0; i < _height; ++i) {
		for (int j = 0; j < _width; ++j) {
			temp[i][j] = _Map[i][j];
		}
	}
	cout << "调用dfs\n";
	//调用dfs
	MazePathFind FindPath(temp, _width, _height);
	//调用findPath方法
	Road niceRoad=FindPath.findPath(_body.x,_body.y,_width-2,_height-2);
	if (!niceRoad) {//没有获得正确路径不做处理
		cout << "没有找到路径\n" << endl;
		return;
	}
	else {//把相应迷宫路径显示到界面上去
		Road temp = niceRoad->next;//niceRoad节点为body所在节点
		while (temp) {
			//cout << "[" << temp->x << "," << temp->y << "]";
			//show color
			_setBlockColor(temp->x, temp->y, 0, 153, 51);
			temp = temp->next;
		}
		//将Road链表内存进行释放
		temp = niceRoad;
		while (temp) {
			Road freeNode = temp;
			temp = temp->next;
			free(freeNode);
		}
	}


	//释放临时地图存储空间
	for (int i = 0; i < _height; ++i) {
		free(temp[i]);
	}
	free(temp);
}


//默认迷宫生成
void LibPage::_defaultInit(void) {
	_createMap(1);
	//人的坐标初始化
	_setRandomBody();
	//设置粮仓
	_setLiangCang();
}

//显示人物
void LibPage::_setBodyImg(int x,int y) {
	if (x < 0 || x>40 || y < 0 || y>28) {//不合法位置
		return;
	}
	_body.x = x;
	_body.y = y;
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

//张贴粮仓图片
void LibPage::_setLiangCang() {
	int x=40, y=27;
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

//靠近中央随机位置设置老鼠位置,这个位置需满足不是墙
void LibPage::_setRandomBody() {
	//int center
	int target_x = (rand() % (20 - 14 + 1)) + 14, target_y = (rand() % (20 - 10 + 1)) + 10;
	while (_Map[target_y][target_x] == '1') {
		target_x = (rand() % (20 - 14 + 1)) + 14, target_y = (rand() % (20 - 10 + 1)) + 10;
	}
	//设置老鼠位置
	_setBodyImg(target_x,target_y);
}

//反转迷宫，并重置粮仓，以及老鼠位置等
void LibPage::_reverseMap() {
	//反转Map
	for (int i = 0; i <= 40; i++) {
		for (int j = 0; j <= 28; j++) {
			if (_Map[j][i] == '1') {
				_Map[j][i] = '0';
			}
			else {
				_Map[j][i] = '1';
			}
		}
	}
	//画出地图
	//更新界面显示
	for (int i = 0; i <= 40; i++) {
		for (int j = 0; j <= 28; j++) {
			if (_Map[j][i] == '1') {//墙
				_setBlockColor(i, j, 234, 123, 78);
			}
			else if (_Map[j][i] == '0') {//空
				_setBlockColor(i, j, 255, 255, 255);
			}
		}
	}
	//重置老鼠
	_setRandomBody();
	//重置粮仓
	_setLiangCang();
	printMap();
}