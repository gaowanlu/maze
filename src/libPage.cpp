#include"../headfile/libPage.h"
#include"../headfile/RecursiveSegmentation.h"//递归分割
#include"../headfile/prim.h"//Prim
#include"../headfile/recursionTracing.h"//递归回溯
#include"../headfile/MazePathFind.h"//dfs寻径
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
			_WinPoPWindow();
		}
		if (_game&&_kbhit()) {//有按键输入
			char input = _getch();
			switch (input)
			{
			case 'w'://上
				_moveBody(_body.x,_body.y-1);
				break;
			case 's'://下
				_moveBody(_body.x, _body.y + 1);
				break;
			case 'a'://左
				_moveBody(_body.x-1, _body.y);
				break;
			case 'd'://右
				_moveBody(_body.x+1, _body.y);
				break;
			default:
				break;
			}
		}
		if (MouseHit()) {
			m = GetMouseMsg();
			switch (m.uMsg)//鼠标事件
			{
				case WM_LBUTTONDOWN:
					if (_judgeInRect(m, _buttonRange[5])) {//退出
						_game = false;
						return 0;
					}
					if (_judgeInRect(m, _buttonRange[2])) {//递归分割
						_createMap(3);
						//人的坐标初始化
						_body.x = 0;
						_body.y = 1;
						_setBodyImg(_body.x, _body.y);
					}
					else if (_judgeInRect(m, _buttonRange[1])) {//递归回溯
						_createMap(2);
						//人的坐标初始化
						_body.x = 0;
						_body.y = 1;
						_setBodyImg(_body.x, _body.y);
					}
					else if (_judgeInRect(m, _buttonRange[0])) {//Prim生成迷宫
						_createMap(1);
						//人的坐标初始化
						_body.x = 0;
						_body.y = 1;
						_setBodyImg(_body.x, _body.y);
					}else if (_judgeInRect(m, _buttonRange[3])) {
						_game = _game ? false : true;
					}
					else if (_judgeInRect(m, _buttonRange[4])) {//迷宫寻径
						_findRoadAndShow();
					}
				break;
			default:break;
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


bool LibPage::_judgeInRect(MOUSEMSG& m, struct Rect rect) {
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
	MOUSEMSG m;
	while (1) {
		if (MouseHit()) {
			//cout << "click\n";
			//cout << backButton.ltx << backButton.lty << backButton.rbx << backButton.rby << "\n";
			m = GetMouseMsg();
			switch (m.uMsg)//鼠标事件
			{
			case WM_LBUTTONDOWN:
				if (_judgeInRect(m, backButton) ){//退出
					cout << "点击叉号\n";
					popWindow.reset();
					//人回到终点并将终点涂白
					_setBlockColor(_body.x, _body.y, 255,0,0);
					_body.x = 0;
					_body.y = 1;
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
	_body.x = 0;
	_body.y = 1;
	_setBodyImg(_body.x, _body.y);
}

//显示人物
void LibPage::_setBodyImg(int x,int y) {
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