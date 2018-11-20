#pragma once
#include"MathDefine.h"
#include<cmath>
#include"DxLib.h"
class Ammo {
public:
	Ammo(double Spe,double Rad,int Time,int MFT,const int *FHdl,
		const int *BHdl,double NewX,double NewY,int Da) : 
		Speed(Spe), Radian(Rad),
		ShootTime(Time),MaxFlyTime(MFT),FlyHandle(FHdl),
		BoomHandle(BHdl),x(NewX),y(NewY),Damage(Da), Usable(true),
		FrameBeforeInvisable(60),
		FramePassed(0), FrameCount(0), FrameAnimationOwned(1),
		EndofAnimation(false) {}
	~Ammo() {}

	/*true��Ԃ��΁A���C���֐��̃��X�g����폜*/
	bool Move();//�ő��s���Ԃɒ�����/�}�b�v�̕ӂ��z��������true��Ԃ�
	bool Out() { return true; }
	void Show(double StartX, double StartY);
	void ChangeUsable();

	double ReferX() { return x; }
	double ReferY() { return y; }
	double ReferR() { return 2; }
	double ReferSX() { return StartX; }
	double ReferSY() { return StartY; }

	bool ReferUsable() { return Usable; }
	bool ReferEOA() { return EndofAnimation; }


private:
	const int *FlyHandle;
	const int *BoomHandle;

	const double Speed;
	const int MaxFlyTime;//�ő��s����//ms�P��
	const int ShootTime;//��s�o�ߎ���//ms�P��

	double x;//X���W
	double y;//Y���W
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
	/*���������邽�߂ɂ�Ran,CD��type���K�v*/
	Weapon(int Ran, int CD, int Ty, double Spe,int *AFHdl,int *ABHdl) :
		MaxFlyTime(Ran), CoolDown(CD),Type(Ty),Speed(Spe),
		AmmoFlyHandle(AFHdl), AmmoBoomHandle(ABHdl),CoordXtoShip(1),
		CoordYtoShip(-3) {}
	~Weapon();

	Ammo Shoot(double Radian, bool Right,double X, double Y);

private:
	const double Speed;//�e�̑��x
	const int MaxFlyTime;//�ő��s����//ms�P��

	const int CoolDown;//�ˌ��Ԋu
	const int Type;//����̎��ʔԍ�

	int LastUsed;//�O��g�������Ԃ��L�^

	const int *AmmoFlyHandle;
	const int *AmmoBoomHandle;

	/*�����g��Ȃ����̂���ŏ���*/
	//���S�_�ɑ΂�����W
	double CoordXtoShip;
	double CoordYtoShip;

	bool Right;
	int Damage;
};