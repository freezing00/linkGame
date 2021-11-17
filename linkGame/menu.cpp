#include "menu.h"

Menu::Menu() {
	loadimage(&_img, _T("img/menuUI.jpg"));
	loadimage(&_start, _T("img/menuStart.jpg"));
	loadimage(&_quit, _T("img/menuQuit.jpg"));
	loadimage(&_rank, _T("img/menuRank.jpg"));
	loadimage(&_level, _T("img/menuLevel.jpg"));
	loadimage(&_set, _T("img/menuSet.jpg"));
	loadimage(&_help, _T("img/menuHelp.jpg"));
	initgraph(1080, 781);
}

void Menu::cursorResponce() {
	switch (mouseChooseMode()) {
	case 0:
		putimage(0, 0, &_img);
		break;
	case 1:
		putimage(0, 0, &_quit);
		break;
	case 2:
		putimage(0, 0, &_start);
		break;
	case 3:
		putimage(0, 0, &_rank);
		break;
	case 4:
		putimage(0, 0, &_level);
		break;
	case 5:
		putimage(0, 0, &_set);
		break;
	case 6:
		putimage(0, 0, &_help);
		break;
	};
	FlushBatchDraw();
}

int Menu::mouseChooseMode() {
	if ((_mouse.x > 920 && _mouse.x < 1025) && (_mouse.y > 635 && _mouse.y < 740)) {//退出
		return 1;
	}
	if ((_mouse.x > 665 && _mouse.x < 925) && (_mouse.y > 287 && _mouse.y < 367)) {//开始
		return 2;
	}
	if ((_mouse.x > 430 && _mouse.x < 685) && (_mouse.y > 438 && _mouse.y < 518)) {//排名
		return 3;
	}
	if ((_mouse.x > 620 && _mouse.x < 870) && (_mouse.y > 590 && _mouse.y < 670)) {//选择难度
		return 4;
	}
	if ((_mouse.x > 185 && _mouse.x < 285) && (_mouse.y > 670 && _mouse.y < 735)) {//设置
		return 5;
	}
	if ((_mouse.x > 53 && _mouse.x < 153) && (_mouse.y > 670 && _mouse.y < 735)) {//帮助
		return 6;
	}
	return 0;
}

void Menu::selectLevelButton() {
	setlinecolor(BLACK);
	LINESTYLE* lineStyle = new LINESTYLE();
	lineStyle->thickness = 5;
	setlinestyle(lineStyle);
	_rect = { 40, 400, 400, 655 };
	rectangle(40, 315, 400, 655);
	makeFontStyle(30, WHITE, LIGHTBLUE);
	RECT titleRect = { 40, 315, 400, 360 };
	drawtext(_T(" LEVEL CHOICES"), &titleRect, DT_CENTER | DT_BOTTOM | DT_WORDBREAK);
	drawtext(_T(" easy level\n\n\nnormal level\n\n\nhard level\n\n\n"), &_rect, DT_LEFT | DT_VCENTER | DT_WORDBREAK);
	circle(235, 420, 10);
	circle(235, 517, 10);
	circle(235, 610, 10);
	FlushBatchDraw();
	while(_mouse.mkLButton || _levelSureFlag == false){
		getMouseInfo();
		if (((_mouse.y >= 410&&_mouse.y<=430)&&(_mouse.x >= 225 && _mouse.x <= 245))&&_mouse.mkLButton){
			_levelChoice = 14;
			_levelSureFlag = true;
			break;
		}
		else if (((_mouse.y >= 507 && _mouse.y <= 527) && (_mouse.x >= 225 && _mouse.x <= 245)) && _mouse.mkLButton){
			_levelChoice = 15;
			_levelSureFlag = true;
			break;
		}
		else if (((_mouse.y >= 600 && _mouse.y <= 620) && (_mouse.x >= 225 && _mouse.x <= 245)) && _mouse.mkLButton) {
			_levelChoice = 16;
			_levelSureFlag = true;
			break;
		}
	}
	_levelSureFlag = false; 
	
}


void Menu::startGameButton(void) {
	_startGame = true;
}


void Menu::rankListButton() {
	_rect = { 40, 315, 400, 655 };
	makeFontStyle(27, WHITE, LIGHTBLUE);
	string text = readFile(FILENAME_RANK);
	LPCWSTR outputText = convertWstringType(text);
	drawtext(outputText, &_rect, DT_LEFT | DT_VCENTER | DT_WORDBREAK);
	FlushBatchDraw();
	waitKey(2000);
}

void Menu::helpButton() {
	_rect = { 40, 315, 400, 655 };
	makeFontStyle(29, WHITE, LIGHTBLUE);
	string text = readFile(FILENAME_HELP);
	LPCWSTR outputText = convertWstringType(text);
	drawtext(outputText, &_rect, DT_LEFT | DT_VCENTER | DT_WORDBREAK);
	FlushBatchDraw();
	waitKey(2000);

}


void Menu::setButton() {
	_rect = { 40, 315, 400, 655 };
	makeFontStyle(29, WHITE, LIGHTBLUE);
	string text = readFile(FILENAME_SET);
	LPCWSTR outputText = convertWstringType(text);
	drawtext(outputText, &_rect, DT_LEFT | DT_VCENTER | DT_WORDBREAK);
	circle(235, 365, 10);
	FlushBatchDraw();
	waitKey(2000);
}


void Menu::buttonResponce() {
	if (_mouse.mkLButton) {
		switch (mouseChooseMode()) {
		case 0:
		case 1:
			break;
		case 2:
			startGameButton();
			break;
		case 3:
			rankListButton();
			break;
		case 4:
			selectLevelButton();
			break;
		case 5:
			setButton();
			break;
		case 6:
			helpButton();
			break;
		};
	}
	FlushBatchDraw();
}

void Menu::menuProcess() {
	getMouseInfo();
	cursorResponce();
	buttonResponce();
}


void Menu::getMouseInfo() {
	_mouse = GetMouseMsg();
}

bool Menu::getQuitMenu() {
	if ((_mouse.x > 920 && _mouse.x < 1025)&&(_mouse.y>635&&_mouse.y<740)) {
		if (_mouse.mkLButton) {
			cout << "Quit game completely!" << endl;
			return 1;
		}
	}
	return 0;
}

string  Menu::readFile(string  fileName) {
	ifstream in(fileName); 
	string text;
	if (in.is_open()) {
		while (!in.eof()) {//读完文件
			getline(in, text); //读取每一行
		}
		in.close(); //关闭文件
	}
	else{
		cout << "Can not open file" << endl;
	}
	return text;
}

LPCWSTR Menu::convertWstringType(string text) {
	wstring result = StoWs(text);
	LPCWSTR outText = result.c_str();
	return outText;
}


wstring Menu::StoWs(const string& s){
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	wstring r(buf);
	delete[] buf;
	return r;
}

void Menu::makeFontStyle(int fontSize, int fontColor, int backgroundColor) {
	LOGFONT f;
	gettextstyle(&f);					//获取字体样式
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	f.lfHeight = fontSize;
	settextstyle(&f);                    // 设置字体样式
	settextcolor(fontColor);				//字体颜色
	setbkcolor(backgroundColor);				//背景颜色
}

void Menu::openMusic(void) {

	// 打开音乐
	mciSendString(convertWstringType("open background.mp3 alias bkmusic"), NULL, 0, NULL);
	// 播放音乐
	mciSendString(convertWstringType("play bkmusic repeat"), NULL, 0, NULL);

}

bool Menu::getStart() {
	return _startGame;
}

bool Menu::getLevel() {
	return _levelSureFlag;
}

int  Menu::getLevelChoice() {
	return _levelChoice;
}

void Menu::setInMenu() {
	_startGame = false;
	initgraph(1080, 781);
}
