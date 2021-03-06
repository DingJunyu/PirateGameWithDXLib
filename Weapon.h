#pragma once
#include"MathDefine.h"
#include<cmath>
#include"DxLib.h"
class Ammo {
public:
	Ammo(double Spe,double Rad,int Time,int MFT,const int *FHdl,
		const int *BHdl,double NewX,double NewY,int Da) : 
		Speed(Spe), Radian(Rad),
		ShootTime(Time),MaxFlyTime(rand()%50+MFT),FlyHandle(FHdl),
		BoomHandle(BHdl),x(NewX),y(NewY),StartX(NewX),
		StartY(NewY),Damage(Da), Usable(true),
		FrameBeforeInvisable(10),
		FramePassed(0), FrameCount(0), FrameAnimationOwned(1),
		EndofAnimation(false) {}
	~Ammo() {}

	/*trueを返せば、メイン関数のリストから削除*/
	bool Move();//最大飛行時間に超えた/マップの辺を越えた時はtrueを返す
	bool Out() { return true; }
	void Show(double StartX, double StartY);
	void ChangeUsable();

	double ReferX() { return x; }
	double ReferY() { return y; }
	double ReferR() { return 2; }
	double ReferSX() { return StartX; }
	double ReferSY() { return StartY; }
	int ReferDamage() { return Damage; }

	bool ReferUsable() { return Usable; }
	bool ReferEOA() { return EndofAnimation; }


private:
	const int *FlyHandle;
	const int *BoomHandle;

	const double Speed;
	const int MaxFlyTime;//最大飛行時間//ms単位
	const int ShootTime;//飛行経過時間//ms単位

	double x;//X座標
	double y;//Y座標
	double StartX;
	double StartY;

	const double Radian;

	const int Damage;
	bool Usable;
	int FrameBeforeInvisable;
	int FramePassed;
	int FrameCount;
	int FrameAnimationOwned;
	bool EndofAnimation;
};

class Weapon
{
public:
	/*初期化するためにはRan,CDとtypeが必要*/
	Weapon(int Ran, int CD, int Ty, double Spe,int *AFHdl,int *ABHdl,
		int Da) :
		MaxFlyTime(Ran), CoolDown(CD),Type(Ty),Speed(Spe),
		AmmoFlyHandle(AFHdl), AmmoBoomHandle(ABHdl),CoordXtoShip(1),
		CoordYtoShip(-3),Damage(Da) {}
	~Weapon();

	Ammo Shoot(double Radian, bool Right,double X, double Y);

private:
	const double Speed;//弾の速度
	const int MaxFlyTime;//最大飛行時間//ms単位

	const int CoolDown;//射撃間隔
	const int Type;//武器の識別番号

	const int Damage;

	int LastUsed;//前回使った時間を記録

	const int *AmmoFlyHandle;
	const int *AmmoBoomHandle;

	/*もう使わないものを後で消す*/
	//中心点に対する座標
	double CoordXtoShip;
	double CoordYtoShip;

	bool Right;
};