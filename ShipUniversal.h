#pragma once
#include"DxLib.h"
#include"MathDefine.h"
#include<cmath>
enum GEAR_ { FULL_SPEED = 1,THREE_QUARTER,HALF_SPEED,A_QUARTER,
	STOP,BACK_UP};
/*1:全速
2:3/4速
3:1/2速
4:1/4速
5:停車
6:1/4速後退*/

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
	/*初期化
	入力必要なこと：
	X座標、Y座標、ラジアン、識別番号、図のハンドル、生成時間、
	長さ、幅*/
	ShipUniversal(int X, int Y, double Rad, double Spe, int Rec,
		int *ImageHandle, double LMT, int Lth, int Wth) :
		CoordX(X), CoordY(Y), Radian(Rad),
		Speed(Spe), Recognition(Rec), ShipHandle(ImageHandle),
		Gears(GEAR_::STOP), GearsToSpeed(0), LastMovedTime(LMT),
		Length(Lth), Width(Wth), ShipSin(0), ShipCos(1),
		CollisionCount(0){}

	~ShipUniversal();

	/*内容変更関数*/
	void Move();
	void ChangeGear(int Gear);
	void Turn(bool Right);
	void Draw(double X,double Y);
	void GetNewCosSin();
	void ChangeLMT(double LMT);
	void XChangeDirect();
	void YChangeDirect();
	void InputCollisionCount(double X, double Y, double R);

	/*問い合わせ関数*/
	int ReferRecognition() { return Recognition; }//識別番号
	double ReferCoordX() { return CoordX; }//X座標
	double ReferCoordY() { return CoordY; }//Y座標	
	double ReferRadian() { return Radian; }//角度
	int ReferGear() { return Gears; }
	double ReferCCount() { return CollisionCount; }
	double ReferCollisionX(int N) { return Collision[N][0]; }
	double ReferCollisionY(int N) { return Collision[N][1]; }
	double ReferCollisionR(int N) { return Collision[N][2]; }
	bool Crash(double X, double Y, double R); //当たったらtrueを戻す

private:
	const int *ShipHandle;//画像ハンドル
	const int Recognition;//識別番号

	double CoordX;//X座標
	double CoordY;//Y座標

	double Length;//船の長さ
	double Width;//船の幅

	double Radian;//ラジアン//射撃の方向はRa+1/2pi and Ra+3/2pi
	double Speed;//速度
	int Gears;//GEAR_に参考してください
	double GearsToSpeed;//ギアと速度の関係

	double LastMovedTime;//前回移動した時間

	double ShipSin;//sin値保存用
	double ShipCos;//cos値保存用

	/*あたり判定用*/
	int CollisionCount;//円の数
	double Collision[10][3];//円のX座標、Y座標、半径
};
