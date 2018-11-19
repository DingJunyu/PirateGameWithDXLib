#pragma once
#include"DxLib.h"
#include"MathDefine.h"
#include"Weapon.h"
#include<cmath>
#include<memory>
#include<stdlib.h>
class ShipUniversal
{
public:
	/*������
	���͕K�v�Ȃ��ƁF
	X���W�AY���W�A���W�A���A���ʔԍ��A�}�̃n���h���A�������ԁA
	�����A��*/
	ShipUniversal(double X, double Y, double Rad, double Spe, int Rec,
		int *ImageHandle, int *ShadowHdl, int *DesHdl, double LMT, int Lth, int Wth) :
		CoordX(X), CoordY(Y), Radian(Rad),
		Speed(Spe), Recognition(Rec), ShipHandle(ImageHandle),
		ShadowHandle(ShadowHdl), DestroyHandle(DesHdl),
		Gears(GEAR_::STOP), GearsToSpeed(0), LastMovedTime(LMT),
		Length(Lth), Width(Wth), ShipSin(0), ShipCos(1),
		CollisionCount(3), WeaponNumR(3), WeaponNumL(3), Visable(true),
		ShadowCenterX(3), ShadowCenterY(3), HP(1), TimeBeforeInvisable(60),
		TimePassed(0), FrameCount(0), FrameAnimationOwned(5),
		EndofAnimation(false),Wait(true)
		{
			for (int i = 0; i < CollisionCount; ++i)
				Collision[i] = new double[5];
		}

	~ShipUniversal();

	/*���e�ύX�֐�*/
	void Move();
	void Unmove();
	void ChangeGear(int Gear);
	void Turn(bool Right);
	void Draw(double X,double Y, bool Me);
	void ShowDestroy(double X, double Y,bool Me);

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
	{ return Collision[N][COLLISION::REAL_COORD_X]; }
	double ReferRCollisionY(int N) 
	{ return Collision[N][COLLISION::REAL_COORD_Y]; }
	double ReferCollisionR(int N)
	{ return Collision[N][COLLISION::RADIUS]; }

	bool Crash(double X, double Y, double R,
		double StartX,double StartY); //����������true��߂�
	bool Crash(double X, double Y, double R); //����������true��߂�
	int ReferWeaponOnRight() { return WeaponNumR; }
	int ReferWeaponOnLeft() { return WeaponNumL; }
	bool ReferVisable() { return Visable; }
	bool ReferEnd() { return EndofAnimation; }

private:
	const int *ShipHandle;//�摜�n���h��
	const int Recognition;//���ʔԍ�
	
	int *ShadowHandle;
	int *DestroyHandle;
	/*���������Ă��܂���*/
	double ShadowCenterX;
	double ShadowCenterY;
	double AbsShadowCenterX;
	double AbsShadowCenterY;

	double CoordX;//X���W
	double CoordY;//Y���W
	/*�ł����ޔ���p*/
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
	double **Collision = new double*[CollisionCount];
	
//	double Collision[10][5];//�~��X���W�AY���W�A���a�A����X���W�A����Y���W

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

	bool Wait;
	bool Visable;
	int TimeBeforeInvisable;
	int TimePassed;
	int FrameCount;
	int FrameAnimationOwned;
	bool EndofAnimation;
};