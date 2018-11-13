#include "ShipUniversal.h"

ShipUniversal::~ShipUniversal()
{
}

void ShipUniversal::Move() {

	double TimeDifference;
	int NewTime = GetNowCount();//今の時間を取る
	TimeDifference = (double)(NewTime - LastMovedTime) / 10;//時間の差を計算
	LastMovedTime = NewTime;//新たな移動時間を記録

	/*X軸の移動や境界チェック*/
	CoordX += ShipSin*Speed*GearsToSpeed*TimeDifference;
	if (CoordX > BOARDER_X - OUTLINE) {
		CoordX = BOARDER_X - OUTLINE;
		ChangeGear(GEAR_::STOP);
	}
	if (CoordX < OUTLINE) {
		CoordX = OUTLINE;
		ChangeGear(GEAR_::STOP);
	}	

	/*Y軸の移動や境界チェック*/
	CoordY -= ShipCos*Speed*GearsToSpeed*TimeDifference;
	if (CoordY > BOARDER_Y - OUTLINE) {
		CoordY = BOARDER_Y - OUTLINE;
		ChangeGear(GEAR_::STOP);
	}
	if (CoordY < OUTLINE) {
		CoordY = OUTLINE;
		ChangeGear(GEAR_::STOP);
	}
}

/*スピード変更*/
void ShipUniversal::ChangeGear(int Gear) {
	if (Gear < 0 || Gear>6)
		return;
	Gears = Gear;//記録する
	switch (Gears) {
	case GEAR_::FULL_SPEED:GearsToSpeed = FULL_SPEED_RATE; break;
	case GEAR_::THREE_QUARTER:GearsToSpeed = THREE_QUARTER_RATE; break;
	case GEAR_::HALF_SPEED:GearsToSpeed = HALF_SPEED_RATE; break;
	case GEAR_::A_QUARTER:GearsToSpeed = A_QUARTER_RATE; break;
	case GEAR_::STOP:GearsToSpeed = STOP_RATE; break;
	case GEAR_::BACK_UP:GearsToSpeed = BACK_UP_RATE; break;
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
		Radian += (PI / TURN_WHEN_INPUT);
		GetNewCosSin();
	}
	else {
		Radian -= (PI / TURN_WHEN_INPUT);
		GetNewCosSin();
	}	
}

/*行く方向変わる時三角関数に関するデータ一気に直す*/
void ShipUniversal::GetNewCosSin() {
	ShipSin = sin(Radian);
	ShipCos = cos(Radian);
}

void ShipUniversal::ChangeLMT(double LMT) {
	LastMovedTime = LMT;
}

void ShipUniversal::XChangeDirect() {
	Radian = 0 - Radian;
	GetNewCosSin();
}

void ShipUniversal::YChangeDirect() {
	Radian = PI - Radian;
	GetNewCosSin();
}

/*あたり判定データ輸入*/
void ShipUniversal::InputCollisionCount(double X, double Y, double R) {
	Collision[CollisionCount][0] = X;
	Collision[CollisionCount][1] = Y;
	Collision[CollisionCount][2] = R;
	CollisionCount++;
}

bool ShipUniversal::Crash(double X, double Y, double R) {
	for (int i = 0; i < CollisionCount; i++) {
		double Ans;
		Ans = abs((X - Collision[i][0])*(Y - Collision[i][1]));
		Ans = sqrt(Ans);
		if (R + Collision[i][2] <= Ans)
			return true;
	}
	return false;
}