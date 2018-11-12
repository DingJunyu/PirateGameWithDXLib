#include "ShipUniversal.h"

ShipUniversal::~ShipUniversal()
{
}

void ShipUniversal::Move() {

	double TimeDifference;
	int NewTime = GetNowCount();
	TimeDifference = (double)(NewTime - LastMovedTime) / 10;
	LastMovedTime = NewTime;

	/*X���̈ړ��⋫�E�`�F�b�N*/
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

	/*Y���̈ړ��⋫�E�`�F�b�N*/
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

/*�X�s�[�h�ύX*/
void ShipUniversal::ChangeGear(int Gear) {
	if (Gear < 0 || Gear>6)
		return;
	Gears = Gear;//�L�^����
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

/*�s�������ύX�֐�*/
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

/*�s�������ς�鎞�O�p�֐��Ɋւ���f�[�^��C�ɒ���*/
void ShipUniversal::GetNewCosSin() {
	ShipSin = sin(Radian);
	ShipCos = cos(Radian);
}