#pragma once
enum CONTROL {
	UP=0,DOWN,RIGHT,LEFT,
	RIGHT_SHOOT=10,LEFT_SHOOT,ALL_SHOOT,
	ESC=20,ENTER
};


class Controller
{
public:
	Controller();
	~Controller();
private:
	int Action;
	
};

