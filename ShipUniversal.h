#pragma once
#include"DxLib.h"
#include"MathDefine.h"
#include<cmath>
enum GEAR_ { FULL_SPEED = 1,THREE_QUARTER,HALF_SPEED,A_QUARTER,
	STOP,BACK_UP};
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

class ShipUniversal
{
public:
	/*������
	���͕K�v�Ȃ��ƁF
	X���W�AY���W�A���W�A���A���ʔԍ��A�}�̃n���h���A�������ԁA
	�����A��*/
	ShipUniversal(int X, int Y, double Rad, double Spe, int Rec,
		int *ImageHandle, double LMT, int Lth, int Wth) :
		CoordX(X), CoordY(Y), Radian(Rad),
		Speed(Spe), Recognition(Rec), ShipHandle(ImageHandle),
		Gears(GEAR_::STOP), GearsToSpeed(0), LastMovedTime(LMT),
		Length(Lth), Width(Wth), ShipSin(0), ShipCos(1),
		CollisionCount(0){}

	~ShipUniversal();

	/*���e�ύX�֐�*/
	void Move();
	void ChangeGear(int Gear);
	void Turn(bool Right);
	void Draw(double X,double Y);
	void GetNewCosSin();
	void ChangeLMT(double LMT);
	void XChangeDirect();
	void YChangeDirect();
	void InputCollisionCount(double X, double Y, double R);

	/*�₢���킹�֐�*/
	int ReferRecognition() { return Recognition; }//���ʔԍ�
	double ReferCoordX() { return CoordX; }//X���W
	double ReferCoordY() { return CoordY; }//Y���W	
	double ReferRadian() { return Radian; }//�p�x
	int ReferGear() { return Gears; }
	double ReferCCount() { return CollisionCount; }
	double ReferCollisionX(int N) { return Collision[N][0]; }
	double ReferCollisionY(int N) { return Collision[N][1]; }
	double ReferCollisionR(int N) { return Collision[N][2]; }
	bool Crash(double X, double Y, double R); //����������true��߂�

private:
	const int *ShipHandle;//�摜�n���h��
	const int Recognition;//���ʔԍ�

	double CoordX;//X���W
	double CoordY;//Y���W

	double Length;//�D�̒���
	double Width;//�D�̕�

	double Radian;//���W�A��//�ˌ��̕�����Ra+1/2pi and Ra+3/2pi
	double Speed;//���x
	int Gears;//GEAR_�ɎQ�l���Ă�������
	double GearsToSpeed;//�M�A�Ƒ��x�̊֌W

	double LastMovedTime;//�O��ړ���������

	double ShipSin;//sin�l�ۑ��p
	double ShipCos;//cos�l�ۑ��p

	/*�����蔻��p*/
	int CollisionCount;//�~�̐�
	double Collision[10][3];//�~��X���W�AY���W�A���a
};
