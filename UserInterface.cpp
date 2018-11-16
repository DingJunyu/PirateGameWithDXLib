#include "UserInterface.h"
#include "DxLib.h"

UserInterface::~UserInterface()
{
}

void UserInterface::Show(double Radian){
	DrawExtendGraph(0, 0, 300, 30, *HPBarBaseHandle, TRUE);
	DrawRotaGraph3(SCREEN_X/2, SCREEN_Y+20, SWW / 2, SWL / 2,
		0.25, 0.25, Radian, *SteeringWheelHandle, TRUE, FALSE);
}

void UserInterface::Inif() {
	GetGraphSize(*SteeringWheelHandle, &SWW,&SWL);
}