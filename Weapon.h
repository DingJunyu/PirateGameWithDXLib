#pragma once
#include"MathDefine.h"
#include<cmath>
#include"DxLib.h"
class Ammo {
public:
	Ammo(int Spe,double Rad,int Time,int MFT,int Hdl) : Speed(Spe), 
		Radian(Rad),
		ShootTime(Time),MaxFlyTime(MFT),Handle(Hdl) {}
	~Ammo() {}

	/*trueを返せば、メイン関数のリストから削除*/
	bool Move();//最大飛行時間に超えた/マップの辺を越えた時はtrueを返す

private:
	const int Handle;
	const int Speed;
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
	Weapon(int Ran, int CD, int Ty,int Spe,int Hdl) :Range(Ran), CoolDown(CD),
		Type(Ty),Speed(Spe), AmmoHandle(Hdl){}
	~Weapon();

	Ammo Shoot(int Radian, bool Right);

private:
	const int Speed;//弾の速度
	const int Range;//攻撃距離//飛行時間に変更//ms単位
	const int CoolDown;//射撃間隔
	const int Type;//武器の識別番号
	const int AmmoHandle;
	int LastUsed;//前回使った時間を記録
};
