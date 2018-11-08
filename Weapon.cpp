#include "Weapon.h"

Weapon::~Weapon()
{
}

Ammo Weapon::Shoot(int Radian, bool Right) {
	/*�����𔻒f���A�e�𐶐����ĕԂ�*/
	if (Right) {
		Ammo AmmoShoot(Speed, Radian + PI / 2, GetNowCount(), Range);
		return AmmoShoot;
	}
	else {
		Ammo AmmoShoot(Speed, Radian + PI * 1.5, GetNowCount(), Range);
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
	y += sin(Radian)*Speed;
	if (y > BOARDER_Y) {
		return true;
	}
	if (y < 0) {
		return true;
	}
	/*�L���͈͂ɒ�������*/
	if (GetNowCount() > ShootTime + MaxFlyTime)
		return true;
}