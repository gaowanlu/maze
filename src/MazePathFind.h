#pragma once
#ifndef __MAZEPATHFIND_H__
#define __MAZEPATHFIND_H__
#define HEIGHT 29
#define WIDTH 41
struct node {
    int length;
    //到终点的长度
    int inDegree;
    //入度
    int x;
    //当前位置的横坐标
    int y;
    //当前位置的纵坐标
    node* next;
    //下一个位置 
};
typedef struct node* Road;

class MazePathFind {
private:
	char** _Map;
	int _width, _height;
    int n = 0;
    Road map[HEIGHT][WIDTH];
    Road dfs(int sx, int sy, int ex, int ey);
public:
	MazePathFind(char**map,int Width, int Height);
	~MazePathFind();
	Road findPath(int start_x, int start_y, int end_x, int end_y);
};

#endif