#pragma once
#include"MathDefine.h"
#include<cmath>
#include"DxLib.h"
class Ammo {
public:
	Ammo(int Spe,double Rad,int Time,int MFT) : Speed(Spe), Radian(Rad),
		ShootTime(Time),MaxFlyTime(MFT) {}
	~Ammo() {}

	/*true��Ԃ��΁A���C���֐��̃��X�g����폜*/
	bool Move();//�ő��s���Ԃɒ�����/�}�b�v�̕ӂ��z��������true��Ԃ�
	bool Hit(int **map);//�����̎���true��Ԃ�

private:
	const int Speed;
	const int MaxFlyTime;//�ő��s����//ms�P��
	const int ShootTime;//��s�o�ߎ���//ms�P��
	double x;//X���W
	double y;//Y���W
	const double Radian;
};

class Weapon
{
public:
	/*���������邽�߂ɂ�Ran,CD��type���K�v*/
	Weapon(int Ran, int CD, int Ty,int Spe) :Range(Ran), CoolDown(CD),
		Type(Ty),Speed(Spe) {}
	~Weapon();

	Ammo Shoot(int Radian, bool Right);

private:
	const int Speed;//�e�̑��x
	const int Range;//�U������//��s���ԂɕύX//ms�P��
	const int CoolDown;//�ˌ��Ԋu
	const int Type;//����̎��ʔԍ�
	double LastUsed;//�O��g�������Ԃ��L�^
};

