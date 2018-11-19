#include "ShipUniversal.h"
using namespace std;

ShipUniversal::~ShipUniversal()
{
}

void ShipUniversal::Move() {
	XBeforeMove = CoordX;
	YBeforeMove = CoordY;

	/*X���̈ړ��⋫�E�`�F�b�N*/
	CoordX += ShipSin*Speed*GearsToSpeed;
	if (CoordX > BOARDER_X - OUTLINE) {
		CoordX = BOARDER_X - OUTLINE;
		ChangeGear(Gears+1);
	}
	if (CoordX < OUTLINE) {
		CoordX = OUTLINE;
		ChangeGear(Gears+1);
	}	

	/*Y���̈ړ��⋫�E�`�F�b�N*/
	CoordY -= ShipCos*Speed*GearsToSpeed;
	if (CoordY > BOARDER_Y - OUTLINE) {
		CoordY = BOARDER_Y - OUTLINE;
		ChangeGear(Gears+1);
	}
	if (CoordY < OUTLINE) {
		CoordY = OUTLINE;
		ChangeGear(Gears+1);
	}
}

/*�X�s�[�h�ύX*/
void ShipUniversal::ChangeGear(int Gear) {
	if (Gear < 0 || Gear>6)
		return;
	Gears = Gear;//�L�^���āA���x�������ĕς��
	switch (Gears) {
	case GEAR_::FULL_SPEED:GearsToSpeed = FULL_SPEED_RATE; break;
	case GEAR_::THREE_QUARTER:GearsToSpeed = THREE_QUARTER_RATE; break;
	case GEAR_::HALF_SPEED:GearsToSpeed = HALF_SPEED_RATE; break;
	case GEAR_::A_QUARTER:GearsToSpeed = A_QUARTER_RATE; break;
	case GEAR_::STOP:GearsToSpeed = STOP_RATE; break;
	case GEAR_::BACK_UP:GearsToSpeed = BACK_UP_RATE; break;
	};
}

void ShipUniversal::Draw(double X, double Y, bool Me) {
	if (!Wait)//�����蔻�肾���ł͐���ɓ����Ȃ��AVisable�̕ύX�͂��Ƃɏ���
		Visable = false;
	if (!Visable) {
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
/*		unsigned int Cr = GetColor(0, 250, 0);
		for (int i = 0; i < CollisionCount; i++) {
			DrawCircle(Collision[i][COLLISION::REAL_COORD_X] - CoordX 
			+ X,
				Collision[i][COLLISION::REAL_COORD_Y] -CoordY
				+ Y,
				Collision[i][COLLISION::RADIUS], Cr, FALSE);
		}*/
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
		/*test************************************************/
/*		unsigned int Cr = GetColor(0, 250, 0);
		for (int i = 0; i < CollisionCount; i++) {
			DrawCircle(Collision[i][COLLISION::REAL_COORD_X] - X,
				Collision[i][COLLISION::REAL_COORD_Y] - Y,
				Collision[i][COLLISION::RADIUS], Cr, FALSE);
		}*/
		/*****************************************************/
	}
	/*���S���W��XY���W*/
}

/*�s�������ύX�֐�*/
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

/*�s�������ς�鎞�O�p�֐��Ɋւ���f�[�^��C�ɒ���*/
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

/*�����蔻��f�[�^�A��*/
void ShipUniversal::InputCollision(double X, double Y, double R) {
	Collision[CollisionCount][COLLISION::COORD_X] = X;
	Collision[CollisionCount][COLLISION::COORD_Y] = Y;
	Collision[CollisionCount][COLLISION::RADIUS] = R;
	CollisionCount++;
}

/*�ł����ރ`�F�b�N*/
bool ShipUniversal::Crash(double X, double Y, double R,
	double StartX, double StartY) {
	for (int i = 0; i < CollisionCount; i++) {
		double Ans;
		double &NewX = Collision[i][COLLISION::REAL_COORD_X];
		double &NewY = Collision[i][COLLISION::REAL_COORD_Y];

		double RightX = StartX > X ? StartX : X;
		double LeftX = StartX < X ? StartX : X;
		double UpY = StartY < Y ? StartY : Y;
		double BottomY = StartY > Y ? StartY : Y;
		/*�ړ���̒e�͖ڕW���z���邩�ǂ���*/
		if (NewX >= LeftX && NewX <= RightX && NewY >= UpY 
			&& NewY <= BottomY)
			Ans = (fabs((Y - StartY)*NewX + (StartX - X)*NewY +
			((X*StartY) - (StartX*Y)))) /
				(sqrt(pow(Y - StartY, 2) + pow(StartX - X, 2)));
		/*���ʂ̂����蔻��*/
		else {
			Ans = abs((X - NewX) * (X - NewX) +
				(Y - NewY)*(Y - NewY));
			Ans = sqrt(Ans);
		}
		

		if (R + Collision[i][COLLISION::RADIUS] >= Ans) {
			HP--;
			if (HP <= 0)
				Wait = false;;
			return true;
		}
	}
	return false;
}

bool ShipUniversal::Crash(double X, double Y, double R) {
	for (int i = 0; i < CollisionCount; i++) {
		double Ans;
		double &NewX = Collision[i][COLLISION::REAL_COORD_X];
		double &NewY = Collision[i][COLLISION::REAL_COORD_Y];

		Ans = abs((X - NewX) * (X - NewX) +
			(Y - NewY)*(Y - NewY));
		Ans = sqrt(Ans);

		if (R + Collision[i][COLLISION::RADIUS] >= Ans) {
			return true;
		}
	}
	return false;
}


/*�㒼��*/
void ShipUniversal::LoadWeapon(Weapon *Weapon) {
	WeaponList = Weapon;
}

/*�E�̎���true,Num�͕���̔ԍ�*/
/*�s��̖��͂��Ƃł���x�m�F*/
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

/*�E��true*/
bool ShipUniversal::WeaponUsable(bool right) {
	if (right)
		if (CoolTime + RightShootTime <= GetNowCount())
			return true;
	if (!right)
		if (CoolTime + LeftShootTime <= GetNowCount())
			return true;
	return false;
}

/*����ԍ��AX���W�AY���W�A�E��true*/
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

/*!!!!!!!!!!!!!�e�X�g�p!!!!!!!!!!!!!!!!*/
void ShipUniversal::TESTFUNCTION() {
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
	CollisionCount = 3;
	Collision[0][0] = 0;
	Collision[0][1] = -17;
	Collision[0][2] = 11;
	Collision[1][0] = 0;
	Collision[1][1] = 0;
	Collision[1][2] = 11;
	Collision[2][0] = 0;
	Collision[2][1] = 17;
	Collision[2][2] = 11;
	GetNewCosSin();
}
/*!!!!!!!!!!!!!�e�X�g�p!!!!!!!!!!!!!!!!*/

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
	int &TBI = TimeBeforeInvisable;
	int &TP = TimePassed;
	int &FC = FrameCount;
	int &FAO = FrameAnimationOwned;
	TP++;
	if (TP % (TBI / FAO) == 0 && TP != 0) {
		FC++;
	}
	if (TP == TimeBeforeInvisable)
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