#include "Weapon.h"

Weapon::~Weapon()
{
}

Ammo Weapon::Shoot(double Radian, bool Right,
	double X,double Y){
	LastUsed = GetNowCount();
	/*方向を判断し、弾を生成して返す*/
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
	/*X軸の移動や境界チェック*/
	x += sin(Radian)*Speed;
	if (x > BOARDER_X) {
		return true;
	}
	if (x < 0) {
		return true;
	}

	/*Y軸の移動や境界チェック*/
	y -= cos(Radian)*Speed;
	if (y > BOARDER_Y) {
		return true;
	}
	if (y < 0) {
		return true;
	}
	/*有効範囲に超えたら*/
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