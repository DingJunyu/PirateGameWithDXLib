#include "Weapon.h"

Weapon::~Weapon()
{
}

Ammo Weapon::Shoot(double Radian, bool Right,
	double X,double Y){
	LastUsed = GetNowCount();
	/*�����𔻒f���A�e�𐶐����ĕԂ�*/
	if (Right) {
		Ammo AmmoShoot(Speed, Radian + (PI / 2), GetNowCount(),
			MaxFlyTime, AmmoFlyHandle, AmmoBoomHandle,
			X, Y, 10);
			
		return AmmoShoot;
	}
	else {
		Ammo AmmoShoot(Speed, Radian + (PI * 1.5), GetNowCount(),
			MaxFlyTime, AmmoFlyHandle, AmmoBoomHandle,
			X, Y, 10);
		return AmmoShoot;
	}
}

bool Ammo::Move() {
	/*X���̈ړ��⋫�E�`�F�b�N*/
	x += sin(Radian)*Speed;
	if (x > BOARDER_X) {
		return true;
	}
	if (x < 0) {
		return true;
	}

	/*Y���̈ړ��⋫�E�`�F�b�N*/
	y -= cos(Radian)*Speed;
	if (y > BOARDER_Y) {
		return true;
	}
	if (y < 0) {
		return true;
	}
	/*�L���͈͂ɒ�������*/
	if (GetNowCount() > ShootTime + MaxFlyTime)
		return true;
	return false;
}

void Ammo::Show(double StartX, double StartY) {
	DrawExtendGraph(x - StartX, y - StartY, x - StartX + 10,
		y - StartY + 10, *FlyHandle, TRUE);
}

bool Weapon::Usable() {
	if (GetNowCount() - CoolDown >= LastUsed)
		return true;
	return false;
}