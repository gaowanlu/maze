#include"../headfile/matrix.h"
int main()
{
    MatrixUI UI;
    UI.init(1280, 720);
    IndexPage indexPage(UI);//首页界面对象
    BreakthroughPage breakthroughPage(UI);//闯关界面对象
    LibPage libPage(UI);//实验室界面对象
    while (1) {
        switch (indexPage.process()){
        case 1:breakthroughPage.process(); break;//闯关触发
        case 2:libPage.process(); break;//实验室触发
        case 3:UI.close(); cout << "程序结束\n";return 0;//退出触发
        default:break;
        }
    }
    return 0;
}


//#include<iostream>
//#include"../headfile/DataBaseMode.h"
//int main()
//{
//    class DataBaseMode Db;
//    std::string newUserId = "gaowanlu";
//    std::string newUserPassword = "gaowanlu";
//    Db.AddUser(newUserId, newUserPassword);
//    newUserId = "gaowanlu";
//    Db.DelRecord(newUserId, 5, 0);
//    Db.PrintAllRecord();
//
//    return 0;
//}
