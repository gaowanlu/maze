#include"breakthroughPage.h"
BreakthroughPage::BreakthroughPage(MatrixUI& UI):UI(UI) {//构造函数

}

//判断点击点是否在矩形范围内
bool BreakthroughPage::_judgeInRect(MOUSEMSG& m, struct Rect rect) {
    if (m.x >= rect.ltx && m.x <= rect.rbx && m.y >= rect.lty && m.y <= rect.rby) {
        return true;
    }
    else {
        return false;
    }
}

void BreakthroughPage::_buttonHover(bool button[9], MOUSEMSG& m) {
    //判断现在是否在这九个按钮内
    int target = -1;//不在九个按钮中
    for (int i = 0; i < 9; i++) {
        if (_judgeInRect(m, _buttonRange[i])) {
            button[i] = true;
            for (int j = 0; j < 9; j++) {
                if (i != j) {
                    button[j] = false;
                }
            }
            target = i;
            break;
        }
    }//更新现在的状态

    int same = 1;//与上一次没有变化
    for (int i = 0; i < 9; i++) {
        if (_lastHoverStatus[i] != button[i]) {
            same = 0;
            break;
        }
    }



    if (target == -1&&same==0) {//不在九个按钮中,且对于上一次有变化
        for (int i = 0; i < 9; i++) {
            button[i] = false;
        }
        //贴原图
        IMAGE img;
        loadimage(&img, _T("./img/breakthroughpage.png"));
        putimage(0, 0, &img);
        return;
    }
    if (same)return;//状态内无改变         
   
    //记录这一次的按钮状态，便于下一次的利用
    for (int j = 0; j < 9; j++) {
        _lastHoverStatus[j] = button[j];
    }
    _resizeButton(button,target);
}


//动画重新设定按钮的大小
void BreakthroughPage::_resizeButton(bool button[9],int target) {
    if (target == -1) {
        return;
    }
    //使得按钮围绕中心放大
    IMAGE img;
    switch (target)
    {
    case 0:
        loadimage(&img, _T("./img/buttonResize/button0.png"));
        putimage(0, 0, &img); 
        break;
    case 1:
        loadimage(&img, _T("./img/buttonResize/button1.png"));
        putimage(0, 0, &img);
        break;
    case 2:
        loadimage(&img, _T("./img/buttonResize/button2.png"));
        putimage(0, 0, &img);
        break;
    case 3:
        loadimage(&img, _T("./img/buttonResize/button3.png"));
        putimage(0, 0, &img);
        break;
    case 4:
        loadimage(&img, _T("./img/buttonResize/button4.png"));
        putimage(0, 0, &img);
        break;
    case 5:
        loadimage(&img, _T("./img/buttonResize/button5.png"));
        putimage(0, 0, &img);
        break;
    case 6:
        loadimage(&img, _T("./img/buttonResize/button6.png"));
        putimage(0, 0, &img);
        break;
    case 7:
        loadimage(&img, _T("./img/buttonResize/button7.png"));
        putimage(0, 0, &img);
        break;
    case 8:
        loadimage(&img, _T("./img/buttonResize/button8.png"));
        putimage(0, 0, &img);
        break;
    default:
        break;
    }
}

int BreakthroughPage::_mClick(MOUSEMSG& m) {
    for (int i = 0; i < 9; i++) {
        if (_judgeInRect(m, _buttonRange[i])) {
            return i;
        }
    }
    return -1;
}


int BreakthroughPage::process(void) {//循环监听
	//贴页面图
	IMAGE img;
	loadimage(&img, _T("./img/breakthroughpage.png"));
	putimage(0, 0, &img);
    MOUSEMSG m;//鼠标事件
    bool button[9] = { 0 };//按钮
    while (true)
    {
        // 获取一条鼠标消息
        m = GetMouseMsg();
        _buttonHover(button,m);
        switch (m.uMsg)
        {
        case WM_LBUTTONDOWN:
            int event = _mClick(m);
            //返回的按钮序号为0-8,0-7位关卡的顺序，8为退出退回到上一级的按钮
            if (event == 8) {
                cout << 8 << endl;
                return 8;
            }
            else if(0<=event&&event<=7){
                LevelPage level(event+49);
                cout << event + 49 <<endl;
                level.process();//界面跳出后恢复闯关界面
                _resetUI();
            }
            break;
        }
    }
}
void BreakthroughPage::_resetUI(void) {
    //贴背景
    IMAGE img;
    loadimage(&img, _T("./img/breakthroughpage.png"));
    putimage(0, 0, &img);
}


