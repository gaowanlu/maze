#include"indexPage.h"
IndexPage::IndexPage(MatrixUI& UI):UI(UI){//构造函数

}
bool IndexPage::_judgeInRect(MOUSEMSG& m,struct Rect rect ) {
    if (m.x >= rect.ltx&&m.x<=rect.rbx&&m.y>=rect.lty&&m.y<=rect.rby) {
        return true;
    }
    else {
        return false;
    }
}

void IndexPage::_buttonHover(bool button[3], MOUSEMSG& m) {//按钮hover变色
    static int sum = 0;
    if ( _judgeInRect(m,_buttonRange[0])) {
        button[0] = true;
        button[1] = false;
        button[2] = false;
        sum++;
        //cout << "闯关" << sum << endl;
    }
    else if (_judgeInRect(m, _buttonRange[1])) {
        button[0] = false;
        button[1] = true;
        button[2] = false;
        sum++;
        //cout << "存档"<<sum<<endl;
    }
    else if (_judgeInRect(m, _buttonRange[2])) {
        button[0] = false;
        button[1] = false;
        button[2] = true;
        sum++;
        //cout << "退出游戏"<<sum<<endl;
    }
    else {
        button[0] = false;
        button[1] = false;
        button[2] = false;
        sum++;
        //cout << "没有触发按钮"<<sum<<endl;
    }
    if (sum > 2000) {
        sum = 0;
    }
    //判断情况更改按钮颜色
    int target;
    if (button[0]&&_diffHoverStatus(button)) {
        IMAGE img;
        loadimage(&img, _T("./img/indexPageButton1.png"));
        putimage(500, 50, &img);
        _setLastHoverStatus(button);
    }
    else if (button[1] && _diffHoverStatus(button)) {
        IMAGE img;
        loadimage(&img, _T("./img/indexPageButton2.png"));
        putimage(500, 50, &img);
        _setLastHoverStatus(button);
    }
    else if (button[2] && _diffHoverStatus(button)) {
        IMAGE img;
        loadimage(&img, _T("./img/indexPageButton3.png"));
        putimage(500, 50, &img);
        _setLastHoverStatus(button);
    }
    else if(_diffHoverStatus(button)){
        IMAGE img;
        loadimage(&img, _T("./img/indexPageButton.png"));
        putimage(500, 50, &img);
        _setLastHoverStatus(button);
    }
}


int IndexPage::process(void) {
    struct Point point;
    UI.setBkColor(255, 255, 255);

    for (int i = 0; i < UI.getWidth(); i++) {//首页顶部
        for (int j = 0; j < 50; j++) {
            point.y = j;
            point.x = i;
            UI.setUIBuffer(point,180,124,72);
        }
    }

    FlushBatchDraw();
    IMAGE img1, img2;
    loadimage(&img1, _T("./img/test.png"));
    putimage(0, 50, &img1);
    loadimage(&img2, _T("./img/indexPageButton.png"));
    putimage(500, 50, &img2);
    MOUSEMSG m;//鼠标事件
    bool button[3] = { 0 };//按钮hover动态效果
    while (true)
    {
        // 获取一条鼠标消息
        m = GetMouseMsg();
        _buttonHover(button, m);//按钮hover效果
        switch (m.uMsg)
        {
        case WM_LBUTTONDOWN:
            if (_judgeInRect(m, _buttonRange[0])) {
                _resetAll();
                cout << "闯关\n";
                return 1;
            }
            else if (_judgeInRect(m, _buttonRange[1])) {
                _resetAll();
                cout << "实验室\n";
                return 2;
            }
            else if (_judgeInRect(m, _buttonRange[2])) {
                _resetAll();
                cout << "退出游戏\n";
                return 3;
            }
            break;
        }
    }

}


//判断这一次与上一次是否有变化
bool IndexPage::_diffHoverStatus(bool button[3]) {
    if (button[0] != _lastHoverStatus[0]) {
        return 1;
    }
    if (button[1] != _lastHoverStatus[1]) {
        return 1;
    }
    if (button[2] != _lastHoverStatus[2]) {
        return 1;
    }
    return 0;//没有变化
}

//保存这一次的hover状态
void IndexPage::_setLastHoverStatus(bool button[3]) {
    for (int i = 0; i < 3; i++) {
        _lastHoverStatus[i] = button[i];
    }
}


//重置界面，跳出对象时
void IndexPage::_resetAll(void) {
    _lastHoverStatus[0] = false;
    _lastHoverStatus[1] = false;
    _lastHoverStatus[2] = false;
    IMAGE img;
    loadimage(&img, _T("./img/indexPageButton.png"));
    putimage(500, 50, &img);
}