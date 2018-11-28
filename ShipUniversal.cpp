#include "ShipUniversal.h"
using namespace std;

ShipUniversal::~ShipUniversal()
{
}

void ShipUniversal::Move(bool Player) {
	XBeforeMove = CoordX;
	YBeforeMove = CoordY;

	/*X軸の移動や境界チェック*/
	CoordX += ShipSin*Speed*GearsToSpeed;
	if (CoordX > BOARDER_X - OUTLINE) {
		CoordX = BOARDER_X - OUTLINE;
		ChangeGear(Gears+1);
		if (!Player)
			XChangeDirect();
	}
	if (CoordX < OUTLINE) {
		CoordX = OUTLINE;
		ChangeGear(Gears+1);
		if (!Player)
			XChangeDirect();
	}	

	/*Y軸の移動や境界チェック*/
	CoordY -= ShipCos*Speed*GearsToSpeed;
	if (CoordY > BOARDER_Y - OUTLINE) {
		CoordY = BOARDER_Y - OUTLINE;
		ChangeGear(Gears+1);
		if (!Player)
			YChangeDirect();
	}
	if (CoordY < OUTLINE) {
		CoordY = OUTLINE;
		ChangeGear(Gears+1);
		if (!Player)
			YChangeDirect();
	}
	CalCoord();
}

/*スピード変更*/
void ShipUniversal::ChangeGear(int Gear) {
	if (Gear < 0 || Gear>6)
		return;
	Gears = Gear;//記録して、速度も応じて変わる
	switch (Gears) {
	case GEAR_::FULL_SPEED:GearsToSpeed = FULL_SPEED_RATE; break;
	case GEAR_::THREE_QUARTER:GearsToSpeed = THREE_QUARTER_RATE; break;
	case GEAR_::HALF_SPEED:GearsToSpeed = HALF_SPEED_RATE; break;
	case GEAR_::A_QUARTER:GearsToSpeed = A_QUARTER_RATE; break;
	case GEAR_::STOP:GearsToSpeed = STOP_RATE; break;
	case GEAR_::BACK_UP:GearsToSpeed = BACK_UP_RATE; break;
	};
}

void ShipUniversal::Draw(double X, double Y, bool Me, bool Test) {
	if (!Wait) {
		ShowDestroy(X, Y, Me);
		return;
	}
	int Target = Gears;
	if (Gears == GEAR_::BACK_UP)
		Target = GEAR_::STOP;
	Target--;
	if (Me) {
		DrawRotaGraph3((int)(X+ShadowCenterX), 
			(int)(Y+ShadowCenterY),
			(int)(Width / 2), (int)(Length / 2),
			ZOOM_MULTIPLE, ZOOM_MULTIPLE,
			Radian, *ShadowHandle, TRUE, FALSE);
		DrawRotaGraph3((int)(X),(int)(Y), 
			(int)(Width / 2), (int)(Length / 2),
			ZOOM_MULTIPLE, ZOOM_MULTIPLE,
			Radian, *(ShipHandle + Target), TRUE, FALSE);
		if (Test) {
			unsigned int Cr = GetColor(0, 250, 0);
			for (int i = 0; i < CollisionCount; i++) {
				DrawCircle((int)(Collision[i][COLLISION::REAL_COORD_X] 
					- CoordX + X),
					(int)(Collision[i][COLLISION::REAL_COORD_Y]
					- CoordY + Y),
					(int)Collision[i][COLLISION::RADIUS], Cr, FALSE);
			}
		}
	}
	else {
		DrawRotaGraph3((int)(CoordX - X + ShadowCenterX), 
			(int)(CoordY - Y + ShadowCenterY),
			(int)(Width / 2), (int)(Length / 2),
			ZOOM_MULTIPLE, ZOOM_MULTIPLE,
			Radian, *ShadowHandle, TRUE, FALSE);

		DrawRotaGraph3((int)(CoordX - X), (int)(CoordY - Y), 
			(int)(Width / 2),(int)( Length / 2),
			ZOOM_MULTIPLE, ZOOM_MULTIPLE,
			Radian, *(ShipHandle + Target), TRUE, FALSE);
		if (Test) {
			unsigned int Cr = GetColor(0, 250, 0);
			for (int i = 0; i < CollisionCount; i++) {
				DrawCircle((int)(Collision[i][COLLISION::REAL_COORD_X]
					- X),
					(int)(Collision[i][COLLISION::REAL_COORD_Y] - Y),
					(int)(Collision[i][COLLISION::RADIUS]), Cr, FALSE);
			}
		}
		/*****************************************************/
	}
	/*中心座標はXY座標*/
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
	CalCoord();
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
void ShipUniversal::InputCollision(double X, double Y, double R) {
	Collision[CollisionCount][COLLISION::COORD_X] = X;
	Collision[CollisionCount][COLLISION::COORD_Y] = Y;
	Collision[CollisionCount][COLLISION::RADIUS] = R;
	CollisionCount++;
}


/*武器を船にロードする*/
void ShipUniversal::LoadWeapon(Weapon *Weapon) {
	WeaponList = Weapon;
}

/*右の時はtrue,Numは武器の番号*/
/*武器の相対位置と船の絶対位置に合わせて弾を打つ*/
/*行列の問題はあとでも一度確認*/
Ammo ShipUniversal::Shoot(bool right, int Num) {
	if (right) {
		RightShootTime = GetNowCount();
		return WeaponList->Shoot(Radian, true,
			CoordX - WeaponYR[Num] * ShipSin + WeaponXR[Num] * ShipCos,
			CoordY + WeaponYR[Num] * ShipCos + WeaponXR[Num] * ShipSin);
	}
	else {
		LeftShootTime = GetNowCount();
		return WeaponList->Shoot(Radian, false,
			CoordX - WeaponYL[Num] * ShipSin + WeaponXL[Num] * ShipCos,
			CoordY + WeaponYL[Num] * ShipCos + WeaponXL[Num] * ShipSin);
	}
}

/*右はtrue*/
bool ShipUniversal::WeaponUsable(bool right) {
	if (right)
		if (CoolTime + RightShootTime <= GetNowCount())
			return true;
	if (!right)
		if (CoolTime + LeftShootTime <= GetNowCount())
			return true;
	return false;
}

/*武器番号、X座標、Y座標、右はtrue*/
void ShipUniversal::LoadWeaponPos(int Num, double X, double Y, bool right) {
	if (right) {
		WeaponXR[Num] = X;
		WeaponYR[Num] = Y;
	}
	else {
		WeaponXL[Num] = X;
		WeaponYL[Num] = Y;
	}
}

/*!!!!!!!!!!!!!テスト用!!!!!!!!!!!!!!!!*/
void ShipUniversal::TESTFUNCTION() {
	//武器を配置
	WeaponXR[0] = -5;
	WeaponYR[0] = -8;
	WeaponXR[1] = -5;
	WeaponYR[1] = 1;
	WeaponXR[2] = -5;
	WeaponYR[2] = 10;
	WeaponXL[0] = 5;
	WeaponYL[0] = -8;
	WeaponXL[1] = 5;
	WeaponYL[1] = 1;
	WeaponXL[2] = 5;
	WeaponYL[2] = 10;
	CoolTime = 500;
	RightShootTime = 0;
	LeftShootTime = 0;
	//あたり判定用
	CollisionCount = 3;
	Collision[0][0] = 0;
	Collision[0][1] = -22;
	Collision[0][2] = 11;
	Collision[1][0] = 0;
	Collision[1][1] = 0;
	Collision[1][2] = 11;
	Collision[2][0] = 0;
	Collision[2][1] = 17;
	Collision[2][2] = 11;
	//今のsinとcos状態を記録
	GetNewCosSin();
}
/*!!!!!!!!!!!!!テスト用!!!!!!!!!!!!!!!!*/

void ShipUniversal::FreeMemory() {
	delete[] WeaponXR;
	delete[] WeaponYR;
	delete[] WeaponXL;
	delete[] WeaponYL;
	for (int i = 0; i < CollisionCount; i++) {
		delete[] Collision[i];
	}
	delete[] Collision;
}

void ShipUniversal::Unmove() {
	CoordX = XBeforeMove;
	CoordY = YBeforeMove;
}

void ShipUniversal::CalCoord() {
	for (int i = 0; i < CollisionCount; i++) {
		Collision[i][COLLISION::REAL_COORD_X] = CoordX +
			Collision[i][COLLISION::COORD_X] * ShipCos
			- Collision[i][COLLISION::COORD_Y] * ShipSin;
		Collision[i][COLLISION::REAL_COORD_Y] = CoordY +
			Collision[i][COLLISION::COORD_Y] * ShipCos
			+ Collision[i][COLLISION::COORD_X] * ShipSin;
	}
}

void ShipUniversal::ShowDestroy(double X, double Y, bool Me) {
	int &TBI = FrameBeforeInvisable;
	int &TP = FramePassed;
	int &FC = FrameCount;
	int &FAO = FrameAnimationOwned;
	TP++;
	if (TP % (TBI / FAO) == 0 && TP != 0) {
		FC++;
	}
	if (TP == TBI)
		EndofAnimation = true;

	if(Me)
		DrawRotaGraph3((int)(X),(int)(Y),
			(int)(Width / 2), (int)(Length / 2),
			ZOOM_MULTIPLE, ZOOM_MULTIPLE,
			Radian, *(DestroyHandle + FC), TRUE, FALSE);

	else
		DrawRotaGraph3((int)(CoordX - X), (int)(CoordY - Y),
		(int)(Width / 2), (int)(Length / 2),
			ZOOM_MULTIPLE, ZOOM_MULTIPLE,
			Radian, *(DestroyHandle + FC), TRUE, FALSE);
}

void ShipUniversal::ChangeMAXHP() {
	HP = 30;
	MaxHP = 30;
}

//渡されたデータを直接操作したいのため、ポインターで渡す
bool Crash(ShipUniversal *A, ShipUniversal *B) {
	for (int i = 0; i < A->ReferCCount(); i++) {
		for (int j = 0; j < B->ReferCCount(); j++) {
			double Ans;
			Ans = abs(pow(A->ReferRCollisionX(i) - B->ReferRCollisionX(j), 2)
				+pow(A->ReferRCollisionY(i)-B->ReferRCollisionY(j),2));
			Ans = sqrt(Ans);
			/*ぶつかったら両側も止まって、前の位置の戻る*/
			if (A->ReferCollisionR(i) + B->ReferCollisionR(j) >= Ans) {
				A->ChangeGear(GEAR_::STOP);
				A->Unmove();
				B->ChangeGear(GEAR_::STOP);
				B->Unmove();
				return true;
			}
		}
	}
	return false;
}

bool Crash(ShipUniversal *A, MapObject B) {
	for (int i = 0; i < A->ReferCCount(); i++) {
		for (int j = 0; j < B.ReferColCount(); j++) {
			double Ans;
			Ans = abs(pow(A->ReferRCollisionX(i) - B.ReferColRX(j), 2)
				+ pow(A->ReferRCollisionY(i) - B.ReferColRY(j), 2));
			Ans = sqrt(Ans);
			if (A->ReferCollisionR(i) + B.ReferColR(j) >= Ans) {
				A->ChangeGear(GEAR_::STOP);
				if (A->ReferRecognition() != 1)
				A->ChangeDirect();
				A->Unmove();
				return true;
			}
		}
	}
	return false;
}

/*打ち込むチェック*/
bool Crash(ShipUniversal *A, Ammo *B) {
	if (!B->ReferUsable())
		return false;

	double RightX = B->ReferSX() > B->ReferX() ?
		B->ReferSX() : B->ReferX();
	double LeftX = B->ReferSX() < B->ReferX() ?
		B->ReferSX() : B->ReferX();
	double UpY = B->ReferSY() < B->ReferY() ?
		B->ReferSY() : B->ReferY();
	double BottomY = B->ReferSY() > B->ReferY() ?
		B->ReferSY() : B->ReferY();

	for (int i = 0; i < A->ReferCCount(); i++) {
		double Ans;

		/*移動後の弾は目標を越えるかどうか*/
		if (A->ReferRCollisionX(i) >= LeftX && A->ReferRCollisionX(i)
			<= RightX && A->ReferRCollisionY(i) >= UpY
			&& A->ReferRCollisionY(i) <= BottomY)

			Ans = (fabs((B->ReferY() - B->ReferSY())*A->ReferRCollisionX(i) 
				+ (B->ReferSX() - B->ReferX())*A->ReferRCollisionY(i) +
			((B->ReferX()*B->ReferSY()) - (B->ReferSX()*B->ReferY())))) /
				(sqrt(pow(B->ReferY() - B->ReferSY(), 2) + pow(B->ReferSX()
					- B->ReferX(), 2)));

		/*普通のあたり判定*/
		else {
			Ans = abs(pow(B->ReferX() - A->ReferRCollisionX(i),2) +
				pow(B->ReferY() - A->ReferRCollisionY(i),2));

			Ans = sqrt(Ans);
		}


		if (B->ReferR() + A->ReferCollisionR(i) >= Ans) {
			A->ChangeHP(B->ReferDamage());
			B->ChangeUsable();
			if (!A->ReferWait()) {
				A->ChangeVisable();
				return true;
			}
			if (!A->ReferAlive()) {
				A->ChangeGear(GEAR_::STOP);
				A->ChangeWait();
			}
			return true;
		}
	}
	return false;
}