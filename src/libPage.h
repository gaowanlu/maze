#pragma once
#ifndef __LIBPAGE_H__
#define __LIBPAGE_H__
#include"matrixUI.h"
#include"PopUpModule.h"//����ģ��
class LibPage {
struct Rect {
		int ltx;
		int rbx;
		int lty;
		int rby;
};
private:
	MatrixUI&UI;
	struct Rect _buttonRange[7] = {
	{968,1240, 44,100},
	{968,1240, 109 , 163},
	{968,1240, 173,230},
	{982,1100,382,510},
	{1136,1228,440,507},
	{1000,1200,579,626},
	{968,1240,251,299}//��ת�Թ���ť
	};

	int _width = 42, _height = 29;
	bool _game = false;//�Ƿ�Ϊ����Ϸģʽ
	struct Point _body = { 0,1 };
	bool _judgeInRect(ExMessage& m, struct Rect rect);//�ж�����Ƿ��ھ��η�Χ��
	void _setBlockColor(int x,int y,char r,char g,char b);
	void _setUIBuffer(struct Point point, char r, char g, char b);
	void _createMap(int type);//��ͬ�㷨���������ͼ����ͼ�ν�����µ���������
	void _moveBody(int x, int y);//��body�ƶ�
	void _WinPoPWindow(void);//����Ŀ�ĵصĵ���
	void _findRoadAndShow(void);//Ѱ��·���Լ���ʾ·��
	void _defaultInit(void);//Ĭ���Թ�����
	void _setBodyImg(int x, int y);//��ʾ����
	void _setLiangCang();//����������ͼ��
	//�����������λ����������λ��,���λ�������㲻��ǽ
	void _setRandomBody();
	//��ת�Թ������������֣��Լ�����λ�õ�
	void _reverseMap();
	bool reverseStatus = false;
public:
	char _Map[29][41];
	LibPage(MatrixUI& UI);
	int process(void);
	void printMap(void);
};







#endif