#pragma once
#include"MathDefine.h"
class UserInterface
{
public:
	UserInterface(int *SWH, int *HPBBH,int *SBH,
		int *SMH): SteeringWheelHandle(SWH),
		HPBarBaseHandle(HPBBH),SpeedBarHandle(SBH),
		SpeedMarkHandle(SMH){}
	~UserInterface();

	void Show(double Radian, int Gear);
	void Inif();
	void ReadHPandMaxHP(int H,int MH);

private:
	const int *SteeringWheelHandle;
	const int *HPBarBaseHandle;
	const int *SpeedBarHandle;
	const int *SpeedMarkHandle;
	int SWL, SWW;
	int HP, MAXHP;
};

