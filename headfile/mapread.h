#pragma once
#ifndef __MAPREAD_H__
#define __MAPREAD_H__
#include<cstdio>
class MapRead {
public:
	MapRead();
	void UpMap(char level);
	char _Map[29][41];
};


#endif