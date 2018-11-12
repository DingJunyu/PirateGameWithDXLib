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
class ShipUniversal
{
public:
	/*初期化
	入力必要なこと：
	X座標、Y座標、ラジアン、識別番号、図のハンドル*/
	ShipUniversal(int X, int Y, double Rad, double Spe, int Rec,
		int ImageHandle, double LMT, int Lth, int Wth) :
		CoordX(X), CoordY(Y), Radian(Rad),
		Speed(Spe), Recognition(Rec), ShipHandle(ImageHandle),
		Gears(GEAR_::STOP), GearsToSpeed(0), LastMovedTime(LMT),
		Length(Lth), Width(Wth), ShipSin(0), ShipCos(1) {}
	~ShipUniversal();

	/*内容変更関数*/
	void Move();
	void ChangeGear(int Gear);
	void Turn(bool Right);
	void Draw();
	void GetNewCosSin();

	/*問い合わせ関数*/
	int ReferRecognition() { return Recognition; }//識別番号
	double ReferCoordX() { return CoordX; }//X座標
	double ReferCoordY() { return CoordY; }//Y座標	
	double ReferRadian() { return Radian; }//角度
	int ReferGear() { return Gears; }

private:
	const int ShipHandle;//画像ハンドル
	const int Recognition;//識別番号
	double CoordX;//X座標
	double CoordY;//Y座標
	double Radian;//ラジアン//射撃の方向はRa+1/2pi and Ra+3/2pi
	double Speed;//速度
	int Gears;//GEAR_に参考してください
	double GearsToSpeed;//ギアと速度の関係
	double Length;//船の長さ
	double Width;//船の幅
	double LastMovedTime;//前回移動した時間

	double ShipSin;
	double ShipCos;
};