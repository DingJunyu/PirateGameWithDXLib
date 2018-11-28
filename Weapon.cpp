#include "Weapon.h"

Weapon::~Weapon()
{
}

/*���x�̉e���͂��Ƃœ����*/
Ammo Weapon::Shoot(double Radian, bool Right,
	double X,double Y){
	LastUsed = GetNowCount();
	/*�����𔻒f���A�e�𐶐����ĕԂ�*/
	if (Right) {
		Ammo AmmoShoot(Speed, Radian + (PI / 2), GetNowCount(),
			MaxFlyTime, AmmoFlyHandle, AmmoBoomHandle,
			X, Y, Damage);
			
		return AmmoShoot;
	}
	else {
		Ammo AmmoShoot(Speed, Radian + (PI * 1.5), GetNowCount(),
			MaxFlyTime, AmmoFlyHandle, AmmoBoomHandle,
			X, Y, Damage);
		return AmmoShoot;
	}
}

bool Ammo::Move() {
	if (!Usable)
		return false;
	/*X���̈ړ��⋫�E�`�F�b�N*/
	StartX = x;
	StartY = y;
	x += sin(Radian)*Speed;
	if (x > BOARDER_X) {
		ChangeUsable();
	}
	if (x < 0) {
		ChangeUsable();
	}

	/*Y���̈ړ��⋫�E�`�F�b�N*/
	y -= cos(Radian)*Speed;
	if (y > BOARDER_Y) {
		ChangeUsable();
	}
	if (y < 0) {
		ChangeUsable();
	}
	/*�L���͈͂ɒ�������*/
	if (GetNowCount() > ShootTime + MaxFlyTime)
		ChangeUsable();
	return false;
}

void Ammo::Show(double StartX, double StartY) {
	if (Usable)
		DrawExtendGraph((int)(x - StartX), (int)(y - StartY),
		(int)(x - StartX + AMMO_LENGTH),
			(int)(y - StartY + AMMO_LENGTH), *FlyHandle, TRUE);
	else {
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
		DrawExtendGraph((int)(x - StartX), (int)(y - StartY),
			(int)(x - StartX + AMMO_LENGTH),
			(int)(y - StartY + AMMO_LENGTH), *BoomHandle, TRUE);
	}
}

void Ammo::ChangeUsable() {
	Usable = false;
}