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
class ShipUniversal
{
public:
	/*������
	���͕K�v�Ȃ��ƁF
	X���W�AY���W�A���W�A���A���ʔԍ��A�}�̃n���h��*/
	ShipUniversal(int X, int Y, int Rad, double Spe, int Rec,
		int ImageHandle) :CoordX(X), CoordY(Y), Radian(Rad),
		Speed(Spe), Recognition(Rec), ShipHandle(ImageHandle),
		Gears(GEAR_::STOP), GearsToSpeed(0) {}
	~ShipUniversal();

	/*���e�ύX�֐�*/
	void Move(int **map);
	void ChangeGear(int Gear);
	void Turn(bool Right);

	/*�₢���킹�֐�*/
	int ReferRecognition() { return Recognition; }//���ʔԍ�
	double ReferCoordX() { return CoordX; }//X���W
	double ReferCoordY() { return CoordY; }//Y���W	
	double ReferRadian() { return Radian; }//�p�x

private:
	const int ShipHandle;//�摜�n���h��
	const int Recognition;//���ʔԍ�
	double CoordX;//X���W
	double CoordY;//Y���W
	double Radian;//���W�A��//�ˌ��̕�����Ra+1/2pi and Ra+3/2pi
	double Speed;//���x
	int Gears;//GEAR_�ɎQ�l���Ă�������
	double GearsToSpeed;//�M�A�Ƒ��x�̊֌W
	double Length;
	double Width;


};
