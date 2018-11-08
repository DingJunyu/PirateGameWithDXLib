#include "Weapon.h"

Weapon::~Weapon()
{
}

Ammo Weapon::Shoot(int Radian, bool Right) {
	/*方向を判断し、弾を生成して返す*/
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
	/*X軸の移動や境界チェック*/
	x += sin(Radian)*Speed;
	if (x > BOARDER_X) {
		return true;
	}
	if (x < 0) {
		return true;
	}

	/*Y軸の移動や境界チェック*/
	y += sin(Radian)*Speed;
	if (y > BOARDER_Y) {
		return true;
	}
	if (y < 0) {
		return true;
	}
	/*有効範囲に超えたら*/
	if (GetNowCount() > ShootTime + MaxFlyTime)
		return true;
}