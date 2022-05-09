#include"MazePathFind.h"
#include"matrixUI.h"

//构造函数
MazePathFind::MazePathFind(char**map,int Width, int Height) {
	_Map = (char**)malloc(sizeof(char*) * Height);
	for (int i = 0; i < Height; ++i) {
		_Map[i] = (char*)malloc(sizeof(char) * Width);
	}
	for (int i = 0; i < Height; ++i) {
		for (int j = 0; j < Width; ++j) {
			_Map[i][j] =map[i][j];
            //cout << "-" << _Map[i][j];
		}
        //cout << endl;
	}
	_width = Width;
	_height = Height;
}

//析构函数:释放存储的地图
MazePathFind::~MazePathFind() {
	for (int i = 0; i < _height; ++i) {
		free(_Map[i]);
	}
	free(_Map);
}

//传过来的map为实际的地图
Road MazePathFind::findPath(int start_x,int start_y,int end_x,int end_y) {
    //寻找路径
    //返回的为链表
    Road niceRoad=dfs(start_x, start_y, end_x, end_y);
    //cout << "dfs调用完毕\n";
   /* for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            cout << _Map[i][j];
        }
        cout << endl;
    }*/
    return niceRoad;//返回路径
    /*if (!niceRoad) {
        return NULL;
    }
    cout << "返回了链表\n";
    Road temp = niceRoad;
    while (temp) {
        cout << "[" << temp->x << "," << temp->y << "]";
        temp = temp->next;
    }*/
}

/*
    深度优先查找最短路径
    从最后开始，逐个确定遍历到的点到终点最短的路径，
    返回值是起点到终点的路径
*/
Road MazePathFind::dfs(int sx, int sy, int ex, int ey)
{
    if (_Map[sy][sx] == '1' || _Map[ey][ex] == '1')
    {
        //防止错误位置
        return NULL;
    }
    const static int x[] = { 1,0,-1,0 };
    const static int y[] = { 0,1,0,-1 };
    //右下左上

    //储存各个分支
    if (map[sy][sx] != NULL)
    {
        //已经找到该位置到终点的位置，直接返回
        return map[sy][sx];
    }
    if (sx == ex && sy == ey)
    {
        //找到终点，
        map[ey][ex] = new node{
            0,
            0,
            ex,
            ey,
            NULL,
        };
        return map[ey][ex];
    }
    n++;
    _Map[sy][sx] = '1';
    //防止回头
    for (int i = 0; i < 4; i++)
    {
        int ltx = sx + x[i];
        int lty = sy + y[i];
        if ((ltx >= 0) && (ltx <= WIDTH - 1) && (lty >=0) && (lty <= HEIGHT - 1) && (_Map[lty][ltx] == '0'))
        {
            //沿着有路的方向寻找，
            dfs(ltx, lty, ex, ey);
        }
    }
    int min = 32767;
    for (int i = 0; i < 4; i++)
    {
        //找出最小分支
        int ltx = sx + x[i];
        int lty = sy + y[i];
        if (map[lty][ltx] != NULL)
        {
            if (map[lty][ltx]->length < min) {
                if (map[sy][sx] == NULL) {
                    map[sy][sx] = new node;
                    map[sy][sx]->inDegree = 0;
                    map[sy][sx]->x = sx;
                    map[sy][sx]->y = sy;
                }
                else {
                    map[sy][sx]->next->inDegree--;
                }
                min = map[lty][ltx]->length;
                map[sy][sx]->length = map[lty][ltx]->length + 1;
                map[sy][sx]->next = map[lty][ltx];
                map[sy][sx]->next->inDegree++;
            }
        }
    }
    n--;
    if (n == 0)
    {
        //最后删除多余分支
        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                if (map[i][j] != NULL && i != sy && j != sx)
                {
                    Road temp, temp1;
                    for (temp = map[i][j]; temp->inDegree == 0; temp = temp1)
                    {
                        temp1 = temp->next;
                        temp1->inDegree--;
                        delete temp;
                    }
                }
            }
        }
    }
    _Map[sy][sx] = '0';
    //恢复当前位置的通路状态
    return map[sy][sx];
    //返回当前位置到终点的最短路径
}