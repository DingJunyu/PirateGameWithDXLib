#include "Weapon.h"

Weapon::~Weapon()
{
}

/*速度の影響はあとで入れる*/
Ammo Weapon::Shoot(double Radian, bool Right,
	double X,double Y){
	LastUsed = GetNowCount();
	/*方向を判断し、弾を生成して返す*/
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
	/*X軸の移動や境界チェック*/
	StartX = x;
	StartY = y;
	x += sin(Radian)*Speed;
	if (x > BOARDER_X) {
		ChangeUsable();
	}
	if (x < 0) {
		ChangeUsable();
	}

	/*Y軸の移動や境界チェック*/
	y -= cos(Radian)*Speed;
	if (y > BOARDER_Y) {
		ChangeUsable();
	}
	if (y < 0) {
		ChangeUsable();
	}
	/*有効範囲に超えたら*/
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