#pragma once
#include"DxLib.h"
#include"MathDefine.h"
#include"Weapon.h"
#include<cmath>
#include<memory>
#include<stdlib.h>

enum GEAR_ {
	FULL_SPEED = 1, THREE_QUARTER, HALF_SPEED, A_QUARTER,
	STOP, BACK_UP
};
/*1:�S��
2:3/4��
3:1/2��
4:1/4��
5:���
6:1/4�����*/
const int TURN_WHEN_INPUT = 64;
const double FULL_SPEED_RATE = 1.0;
const double THREE_QUARTER_RATE = 0.75;
const double HALF_SPEED_RATE = 0.5;
const double A_QUARTER_RATE = 0.25;
const double STOP_RATE = 0;
const double BACK_UP_RATE = -0.25;

enum COLLISION {
	COORD_X = 0, COORD_Y, RADIUS,
	REAL_COORD_X, REAL_COORD_Y
};

class ShipUniversal
{
public:
	/*������
	���͕K�v�Ȃ��ƁF
	X���W�AY���W�A���W�A���A���ʔԍ��A�}�̃n���h���A�������ԁA
	�����A��*/
	ShipUniversal(double X, double Y, double Rad, double Spe, int Rec,
		int *ImageHandle, double LMT, int Lth, int Wth) :
		CoordX(X), CoordY(Y), Radian(Rad),
		Speed(Spe), Recognition(Rec), ShipHandle(ImageHandle),
		Gears(GEAR_::STOP), GearsToSpeed(0), LastMovedTime(LMT),
		Length(Lth), Width(Wth), ShipSin(0), ShipCos(1),
		CollisionCount(0),WeaponNumR(3),WeaponNumL(3),Visable(true), 
		ShadowCenterX(8),ShadowCenterY(8){}

	~ShipUniversal();

	/*���e�ύX�֐�*/
	void Move();
	void Unmove();
	void ChangeGear(int Gear);
	void Turn(bool Right);
	void Draw(double X,double Y, bool Me);
	void GetNewCosSin();
	void ChangeLMT(double LMT);
	void XChangeDirect();
	void YChangeDirect();
	void InputCollision(double X, double Y, double R);
	void LoadWeapon(Weapon *Weapon);
	Ammo Shoot(bool right, int Num);
	bool WeaponUsable(bool right);
	void LoadWeaponPos(int Num, double X, double Y, bool right);
	void FreeMemory();
	void CalCoord();

	/*�e�X�g�p���g�ύX�֐�*/
	/*�����o�b�W�����͐�Ύg��Ȃ�!*/
	void TESTFUNCTION();

	/*�₢���킹�֐�*/
	int ReferRecognition() { return Recognition; }//���ʔԍ�
	double ReferCoordX() { return CoordX; }//X���W
	double ReferCoordY() { return CoordY; }//Y���W	
	double ReferXbeforeMove() { return XBeforeMove; }
	double ReferYbeforeMove() { return YBeforeMove; }
	double ReferRadian() { return Radian; }//�p�x
	int ReferGear() { return Gears; }
	double ReferCCount() { return CollisionCount; }
	double ReferRCollisionX(int N) 
	{ return Collision[N][COLLISION::REAL_COORD_X]+CoordX; }
	double ReferRCollisionY(int N) 
	{ return Collision[N][COLLISION::REAL_COORD_Y]+CoordY; }
	double ReferCollisionR(int N)
	{ return Collision[N][COLLISION::RADIUS]; }
	bool Crash(double X, double Y, double R,
		double StartX,double StartY); //����������true��߂�
	bool Crash(double X, double Y, double R); //����������true��߂�
	int ReferWeaponOnRight() { return WeaponNumR; }
	int ReferWeaponOnLeft() { return WeaponNumL; }
	bool ReferVisable() { return Visable; }

private:
	const int *ShipHandle;//�摜�n���h��
	const int Recognition;//���ʔԍ�
	
	int ShadowHandle;
	/*���������Ă��܂���*/
	double ShadowCenterX;
	double ShadowCenterY;
	double AbsShadowCenterX;
	double AbsShadowCenterY;

	double CoordX;//X���W
	double CoordY;//Y���W
	double XBeforeMove;
	double YBeforeMove;

	double Length;//�D�̒���
	double Width;//�D�̕�

	double Radian;//���W�A��//�ˌ��̕�����Ra+1/2pi and Ra+3/2pi
	double Speed;//���x
	int Gears;//GEAR_�ɎQ�l���Ă�������
	double GearsToSpeed;//�M�A�Ƒ��x�̊֌W

	double LastMovedTime;//�O��ړ���������

	/*���������Ă��܂���*/
	double ShipSin;//sin�l�ۑ��p
	double ShipCos;//cos�l�ۑ��p

	/*�����蔻��p*/
	/*��̓t���[�������ɕς���*/
	int CollisionCount;//�~�̐�
	double Collision[10][5];//�~��X���W�AY���W�A���a�A����X���W�A����Y���W

	//���S�_�ɑ΂�����W
	int WeaponNumR;
	int WeaponNumL;
	double *WeaponXR = new double[WeaponNumR];
	double *WeaponYR = new double[WeaponNumR];
	double *WeaponXL = new double[WeaponNumL];
	double *WeaponYL = new double[WeaponNumL];

	Weapon *WeaponList;

	/*���������Ă��܂���I�I�I*/
	int CoolTime;
	int RightShootTime;
	int LeftShootTime;

	int HP;
	int MaxHP;

	bool Visable;
};