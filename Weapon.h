#pragma once
#include"MathDefine.h"
#include<cmath>
#include"DxLib.h"
class Ammo {
public:
	Ammo(double Spe,double Rad,int Time,int MFT,const int *FHdl,
		const int *BHdl,double NewX,double NewY) : 
		Speed(Spe), Radian(Rad),
		ShootTime(Time),MaxFlyTime(MFT),FlyHandle(FHdl),
		BoomHandle(BHdl),x(NewX),y(NewY) {}
	~Ammo() {}

	/*trueを返せば、メイン関数のリストから削除*/
	bool Move();//最大飛行時間に超えた/マップの辺を越えた時はtrueを返す
	bool Out() { return true; }
	void Show(double StartX, double StartY);

private:
	const int *FlyHandle;
	const int *BoomHandle;

	const double Speed;
	const int MaxFlyTime;//最大飛行時間//ms単位
	const int ShootTime;//飛行経過時間//ms単位

	double x;//X座標
	double y;//Y座標
	const double Radian;
};

class Weapon
{
public:
	/*初期化するためにはRan,CDとtypeが必要*/
	Weapon(int Ran, int CD, int Ty, double Spe,int *AFHdl,int *ABHdl) :
		MaxFlyTime(Ran), CoolDown(CD),Type(Ty),Speed(Spe),
		AmmoFlyHandle(AFHdl), AmmoBoomHandle(),CoordXtoShip(1),
		CoordYtoShip(-3) {}
	~Weapon();

	Ammo Shoot(double Radian, bool Right, double Sin, double Cos,
		double X, double Y);


	bool Usable();

private:
	const double Speed;//弾の速度
	const int MaxFlyTime;//最大飛行時間//ms単位

	const int CoolDown;//射撃間隔
	const int Type;//武器の識別番号

	int LastUsed;//前回使った時間を記録

	const int *AmmoFlyHandle;
	const int *AmmoBoomHandle;

	//中心点に対する座標
	double CoordXtoShip;
	double CoordYtoShip;

	bool Right;
};