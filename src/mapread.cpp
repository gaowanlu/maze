#include"mapread.h"
MapRead::MapRead() {

}
void MapRead::UpMap(char level) {
	//共计20个字符
	char mapFileName[20] = { '.','/','d','a','t','a','/','l','e','v','e','l','/',level,'.','m','a','p','\0' };
	printf("%s\n", mapFileName);
	//根据参数level进行读取地图文件
	FILE* fp = NULL;
	fopen_s(&fp,mapFileName,"r");
	if (!fp) {//读取文件失败
		printf("读取地图%c失败\n",level);
		return;
	}
	char readChar = '0';
	int x = 0, y = 0;
	while (1) {
		readChar = fgetc(fp);
		if (readChar == EOF) {
			break;
		}
		if (y == 29) {
			break;
		}
		if (x == 41) {
			++y;
			x = 0;
		}
		if (readChar == '0' || readChar == '1') {
			_Map[y][x++] = readChar;
		}
	}
	fclose(fp);
}