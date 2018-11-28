#include "UserInterface.h"
#include "DxLib.h"

UserInterface::~UserInterface()
{
}

void UserInterface::Show(double Radian,int Gear){
	unsigned int Cr = GetColor(0, 180, 100);
	double Percent = (double)HP / (double)MAXHP;
	DrawBox(7, 7, 293 * Percent, 23, Cr, TRUE);
	DrawExtendGraph(0, 0, 300, 30, *HPBarBaseHandle, TRUE);
	DrawRotaGraph3(SCREEN_X/2, SCREEN_Y+20, SWW / 2, SWL / 2,
		0.25, 0.25, Radian, *SteeringWheelHandle, TRUE, FALSE);
	DrawExtendGraph(SCREEN_X - 150, SCREEN_Y - 200, SCREEN_X+50,
		SCREEN_Y, *SpeedBarHandle, TRUE);
	switch (Gear)
	{
	case GEAR_::FULL_SPEED:
		DrawExtendGraph(SCREEN_X - 90, SCREEN_Y - 220, SCREEN_X + 10,
		SCREEN_Y - 120, *SpeedMarkHandle, TRUE); break;
	case GEAR_::THREE_QUARTER:
		DrawExtendGraph(SCREEN_X - 90, SCREEN_Y - 190, SCREEN_X + 10,
		SCREEN_Y - 90 , *SpeedMarkHandle, TRUE); break;
	case GEAR_::HALF_SPEED:
		DrawExtendGraph(SCREEN_X - 90, SCREEN_Y - 160, SCREEN_X + 10,
		SCREEN_Y - 60, *SpeedMarkHandle, TRUE); break;
	case GEAR_::A_QUARTER:
		DrawExtendGraph(SCREEN_X - 90, SCREEN_Y - 130, SCREEN_X + 10,
		SCREEN_Y - 30, *SpeedMarkHandle, TRUE); break;
	case GEAR_::STOP:
		DrawExtendGraph(SCREEN_X - 90, SCREEN_Y - 100, SCREEN_X + 10,
		SCREEN_Y , *SpeedMarkHandle, TRUE); break;
	case GEAR_::BACK_UP:
		DrawExtendGraph(SCREEN_X - 90, SCREEN_Y - 70, SCREEN_X + 10,
		SCREEN_Y + 30, *SpeedMarkHandle, TRUE); break;

	};
}

void UserInterface::Inif() {
	GetGraphSize(*SteeringWheelHandle, &SWW,&SWL);
}

void UserInterface::ReadHPandMaxHP(int H, int MH) {
	HP = H;
	MAXHP = MH;
}