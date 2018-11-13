#include "ShipUniversal.h"

ShipUniversal::~ShipUniversal()
{
}

void ShipUniversal::Move() {

	double TimeDifference;
	int NewTime = GetNowCount();//���̎��Ԃ����
	TimeDifference = (double)(NewTime - LastMovedTime) / 10;//���Ԃ̍����v�Z
	LastMovedTime = NewTime;//�V���Ȉړ����Ԃ��L�^

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

void ShipUniversal::Draw(double X, double Y) {
	int Target = Gears;
	if (Gears == GEAR_::BACK_UP)
		Target = GEAR_::STOP;
	Target--;
	DrawRotaGraph3(X, Y, Width / 2, Length / 2,
		ZOOM_MULTIPLE, ZOOM_MULTIPLE,
		Radian, *(ShipHandle + Target), TRUE, FALSE);
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
void ShipUniversal::InputCollisionCount(double X, double Y, double R) {
	Collision[CollisionCount][COLLISION::COORD_X] = X;
	Collision[CollisionCount][COLLISION::COORD_Y] = Y;
	Collision[CollisionCount][COLLISION::RADIUS] = R;
	CollisionCount++;
}

/*�ł����ރ`�F�b�N*/
bool ShipUniversal::Crash(double X, double Y, double R) {
	for (int i = 0; i < CollisionCount; i++) {
		double Ans;
		Ans = abs((X - Collision[i][COLLISION::COORD_X])*
			(Y - Collision[i][COLLISION::COORD_Y]));
		Ans = sqrt(Ans);
		if (R + Collision[i][COLLISION::RADIUS] <= Ans)
			return true;
	}
	return false;
}

