#include "ShipUniversal.h"

ShipUniversal::~ShipUniversal()
{
}

void ShipUniversal::Move() {

	double TimeDifference;
	int NewTime = GetNowCount();
	TimeDifference = (double)(NewTime - LastMovedTime) / 10;
	LastMovedTime = NewTime;

	/*X軸の移動や境界チェック*/
	CoordX += ShipSin*Speed*GearsToSpeed*TimeDifference;
	if (CoordX > BOARDER_X) {
		CoordX = BOARDER_X;
		Radian = 0 - Radian;
		GetNewCosSin();
	}
	if (CoordX < 0) {
		CoordX = 0;
		Radian = 0 - Radian;
		GetNewCosSin();
	}	

	/*Y軸の移動や境界チェック*/
	CoordY -= ShipCos*Speed*GearsToSpeed*TimeDifference;
	if (CoordY > BOARDER_Y) {
		CoordY = BOARDER_Y;
		Radian = PI - Radian;
		GetNewCosSin();
	}
	if (CoordY < 0) {
		CoordY = 0;
		Radian = PI - Radian;
		GetNewCosSin();
	}
}

/*スピード変更*/
void ShipUniversal::ChangeGear(int Gear) {
	if (Gear < 0 || Gear>6)
		return;
	Gears = Gear;//記録する
	switch (Gears) {
	case GEAR_::FULL_SPEED:GearsToSpeed = 1.0; break;
	case GEAR_::THREE_QUARTER:GearsToSpeed = 0.75; break;
	case GEAR_::HALF_SPEED:GearsToSpeed = 0.5; break;
	case GEAR_::A_QUARTER:GearsToSpeed = 0.25; break;
	case GEAR_::STOP:GearsToSpeed = 0; break;
	case GEAR_::BACK_UP:GearsToSpeed = -0.25; break;
	};
}

void ShipUniversal::Draw() {
	DrawRotaGraph3(CoordX, CoordY, Width/2, Length/2,
		ZOOM_MULTIPLE, ZOOM_MULTIPLE,
		Radian, ShipHandle, TRUE, FALSE);
}

/*行く方向変更関数*/
void ShipUniversal::Turn(bool Right) {
	if (Right) {
		Radian += (PI / 64);
		GetNewCosSin();
	}
	else {
		Radian -= (PI / 64);
		GetNewCosSin();
	}	
}

/*行く方向変わる時三角関数に関するデータ一気に直す*/
void ShipUniversal::GetNewCosSin() {
	ShipSin = sin(Radian);
	ShipCos = cos(Radian);
}