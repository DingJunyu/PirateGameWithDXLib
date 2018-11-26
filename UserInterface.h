#pragma once
#include"MathDefine.h"
class UserInterface
{
public:
	UserInterface(int *SWH, int *HPBBH): SteeringWheelHandle(SWH),
		HPBarBaseHandle(HPBBH) {}
	~UserInterface();

	void Show(double Radian);
	void Inif();
	void ReadHPandMaxHP(int H,int MH);

private:
	const int *SteeringWheelHandle;
	const int *HPBarBaseHandle;
	int SWL, SWW;
	int HP, MAXHP;
};

