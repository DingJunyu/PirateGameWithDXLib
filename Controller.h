#pragma once
#include"DxLib.h"
enum CONTROL {
	EMPTY = 0,
	UP=10,DOWN,RIGHT,LEFT,
	LEFT_SHOOT=20,RIGHT_SHOOT,ALL_SHOOT,
	ESC=30,ENTER
};


class Controller
{
public:
	Controller();
	~Controller();
	int GetOrder();
	
private:
	int Action;
	char KeyBuf[256];
};

