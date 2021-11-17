#include "initGraph.h"

Graph::Graph() {
	//加载图片,如果现实没有重载的函数，就是字符集的问题
	loadimage(&img_total[0], _T("img/fruit.bmp"));
	loadimage(&img_total[1], _T("img/initial.jpg"), 1080, 781);
	loadimage(&_img, _T("img/menuUI.jpg"));
	//创建一个图形窗口，贴图片
	initgraph(1080, 781, EW_SHOWCONSOLE);
}

void Graph::gameInit() {
	//设置随机数种子
	srand(GetTickCount());
	//把整个图片进行分割，保存到新的数组
	IMAGE p = img_total[0];
	SetWorkingImage(&p);
	for (int i = 0; i < MAX_ANIMAL_NUM; i++) {
		for (int k = 0; k < 2; k++) {
			getimage(&_imgFruit[i][k], k * IMG_SIZE, i * IMG_SIZE, IMG_SIZE, IMG_SIZE);
		}
	}
	SetWorkingImage();
	//11111  222 3333
	//每张图片来14张_MAPSIZE
	int temp = 1, _count = 1;
	for (int i = 1; i <= _mapSize; i++) {
		for (int k = 1; k <= _mapSize; k++) {
			_map[i][k] = temp;
			if (_count % 14 == 0){
				temp++;
			}
			_count++;

		}
	}
	reunionData();
	start = clock();
}

void Graph::timeDown() {
	int cosume = 500 - durationTime;
	nowTime = cosume;
	LINESTYLE* lineStyle = new LINESTYLE();
	lineStyle->thickness = 5;
	setlinestyle(lineStyle);
	rectangle (820, 100, 860, nowTime);
	if (nowTime == 0) {
		RECT rect = { 130, 200, 850, 650 };
		makeFontStyle(60, WHITE, LIGHTBLUE);
		drawtext(_T("game over!"), &rect, DT_LEFT | DT_VCENTER | DT_WORDBREAK);
		FlushBatchDraw();
		cv::waitKey(1500);
	}
	FlushBatchDraw();
}

void Graph::timeConsume(){
	durationTime = ((stop - start)) / CLOCKS_PER_SEC;
	//cout << "in" << start << endl;
	//cout << "延时时间：" << durationTime << " s" << endl;
}


void Graph::reunionData() {
	//打乱图片，实际上就是打乱数组数据
	for (int i = 1; i <= _mapSize; i++) {
		for (int k = 1; k <= _mapSize; k++) {
			int temp = _map[i][k];
			int row = rand() % 14 + 1;
			int col = rand() % 14 + 1;
			_map[i][k] = _map[row][col];
			_map[row][col] = temp;//两两交换
		}
	}
	BeginBatchDraw();//批量绘制
}


void Graph::gameDraw(){
	putimage(0, 0, &img_total[1]);
	for (int i = 1; i <= _mapSize; i++){
		for (int k = 1; k <= _mapSize; k++){
			if (_map[i][k] > 0){//说明该位置上有数据——放图
				loc_tl[i][k].x = k * IMG_SIZE;
				loc_tl[i][k].y = i * IMG_SIZE;
				loc_br[i][k].x = k * IMG_SIZE + 43;
				loc_br[i][k].y = i * IMG_SIZE + 43;
				//用透明贴图，使图片背景透明
				putimage(k * IMG_SIZE, i * IMG_SIZE, &_imgFruit[_map[i][k]][1], SRCAND);
				//把击中图标和屏幕颜色进行与运算，就可以让击中时候的方框作为生成地图上图标之间的间隔
				putimage(k * IMG_SIZE, i * IMG_SIZE, &_imgFruit[_map[i][k]][0], SRCPAINT);
			}
		}
	}
}
int Graph::returnMenu() {
	if ((_mouse.x > 920 && _mouse.x < 1030) && (_mouse.y > 635 && _mouse.y < 740)) {
		if (_mouse.mkLButton) {
			 return 1;
		}
	}
	return 0;
}

void Graph::resetMap() {
	if ((_mouse.x > 920 && _mouse.x < 1025) && (_mouse.y > 540 && _mouse.y < 610)||(_resetMap == (_mapSize*_mapSize))) {
		if (_mouse.mkLButton) {
			reunionData();
		}
	}
}

void Graph::addTime() {
	if((_mouse.x >955 && _mouse.x < 1035) && (_mouse.y > 135 && _mouse.y <200)) {
		if (_mouse.mkLButton) {
			start += 5000;
		}
	}
}


int Graph::classifyHitStatus() {
	if (!findFlag1) {
		if (findFlag2){
			findFlag2 = false;
		}
		//FlushMouseMsgBuffer();
		MOUSEMSG mouseFirst = GetMouseMsg();
		_mouse = mouseFirst;
		if (mouseFirst.mkLButton) {
			int x = mouseFirst.x;
			int y = mouseFirst.y;
			for (size_t i = 1; i <= _mapSize; i++) {
				for (size_t j = 1; j <= _mapSize; j++) {
					if ((x >= loc_tl[i][j].x && y >= loc_tl[i][j].y) && (x <= loc_br[i][j].x && y <= loc_br[i][j].y)) {
						_match[0].x = i;
						_match[0].y = j;
						findFlag1 = 1;
						//cout << "one" << _match[0].x << " " << _match[0].y << endl;
						break;
					}
				}
				if (findFlag1) {
					break;
				}
			}
			if (!findFlag1) {
				return 0;
			}
		}
	}
	if (!findFlag2&&findFlag1) {
		//FlushMouseMsgBuffer();
		MOUSEMSG mouseLater = GetMouseMsg();
		if (mouseLater.mkLButton) {
			int x = mouseLater.x;
			int y = mouseLater.y;
			for (size_t i = 1; i <= _mapSize; i++) {
				for (size_t j = 1; j <= _mapSize; j++) {
					if ((x >= loc_tl[i][j].x && y >= loc_tl[i][j].y) && (x <= loc_br[i][j].x && y <= loc_br[i][j].y)) {
						_match[1].x = i;
						_match[1].y = j;
						findFlag2 = 1;
						//cout << "two" << _match[1].x << " " << _match[1].y << endl;
						break;
					}
				}
				if (findFlag2) {
					break;
				}
			}
			if (!findFlag2) {
				return 0;
			}
		}
	}
	if (findFlag1&&findFlag2 &&_match[0].x!=0&& _match[1].y != 0){
		if (_map[_match[0].x][_match[0].y]== _map[_match[1].x][_match[1].y]){
			findFlag1 = false;
			findFlag2 = false;
			return 1;
		}
		findFlag1 = false;
		findFlag2 = false;
		return 0;
	}
	return 0;
}


LPCWSTR Graph::convertWstringType(string text) {
	wstring result = StoWs(text);
	LPCWSTR outText = result.c_str();
	return outText;
}


wstring Graph::StoWs(const string& s) {
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	wstring r(buf);
	delete[] buf;
	return r;
}

void Graph::makeFontStyle(int fontSize, int fontColor, int backgroundColor) {
	LOGFONT f;
	gettextstyle(&f);					//获取字体样式
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	f.lfHeight = fontSize;
	settextstyle(&f);                    // 设置字体样式
	settextcolor(fontColor);				//字体颜色
	setbkcolor(backgroundColor);				//背景颜色
}
void Graph::showScore(int score) {
	RECT  _rect = { 1, 720, 100,780 }; 
	makeFontStyle(27, WHITE, LIGHTBLUE);
	drawtext(_T("score:"+ score), &_rect, DT_LEFT | DT_VCENTER | DT_WORDBREAK);
	FlushBatchDraw();
}

void Graph::initProcess() {
	gameDraw();//画图
	FlushBatchDraw();
	stop = clock();//时间初始化
	timeConsume();//计时
	resetMap();//刷新地图
	timeDown();//倒计时
	addTime();//延时
	//showScore(_score);
	if (classifyHitStatus()){//判断图标配对状态
		for (int i = 1; i <= _mapSize; i++) {//更新图标排布矩阵
			for (int k = 1; k <= _mapSize; k++) {
				_bingo.image[i][k] = _map[i][k];
				//cout << "_bingo.image[i][k]" << _bingo.image[i][k] << endl;
			}
		}
		if (_bingo.judgeProcess(_match[0].y, _match[0].x, _match[1].y, _match[1].x)) {//消除
			_map[_match[0].x][_match[0].y] = 0;
			_map[_match[1].x][_match[1].y] = 0;
			_resetMap = _resetMap + 2;
			_score = _score + 2;
		}
	}
}

void Graph::setMapSize(int mapSize) {
	if (mapSize != 0) {
		_mapSize = mapSize;
		_winSize = mapSize * IMG_SIZE + 2 * IMG_SIZE;
		_bingo._mapSize = this->_mapSize;
	}
}