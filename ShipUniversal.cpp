#include "ShipUniversal.h"

ShipUniversal::~ShipUniversal()
{
}

void ShipUniversal::Move(int **map) {
	/*X軸の移動や境界チェック*/
	CoordX += sin(Radian)*Speed*GearsToSpeed;
	if (CoordX > BOARDER_X) {
		CoordX = BOARDER_X;
		Radian = 0 - Radian;
	}
	if (CoordX < 0) {
		CoordX = 0;
		Radian = 0 - Radian;
	}

	/*Y軸の移動や境界チェック*/
	CoordY += sin(Radian)*Speed*GearsToSpeed;
	if (CoordY > BOARDER_Y) {
		CoordY = BOARDER_Y;
		Radian = PI - Radian;
	}
	if (CoordY < 0) {
		CoordY = 0;
		Radian = PI - Radian;
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
