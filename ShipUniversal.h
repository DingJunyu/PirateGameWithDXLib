#pragma once
#include"DxLib.h"
#include"MathDefine.h"
#include"Weapon.h"
#include"MapObject.h"
#include<cmath>
#include<memory>
#include<stdlib.h>
class ShipUniversal
{
public:
	/*初期化
	入力必要なこと：
	X座標、Y座標、ラジアン、識別番号、図のハンドル、生成時間、
	長さ、幅*/
	ShipUniversal(double X, double Y, double Rad, double Spe, int Rec,
		int *ImageHandle, int *ShadowHdl, int *DesHdl, double LMT, int Lth, int Wth) :
		CoordX(X), CoordY(Y), Radian(Rad),
		Speed(Spe), Recognition(Rec), ShipHandle(ImageHandle),
		ShadowHandle(ShadowHdl), DestroyHandle(DesHdl),
		Gears(GEAR_::STOP), GearsToSpeed(0), LastMovedTime(LMT),
		Length(Lth), Width(Wth), ShipSin(0), ShipCos(1),
		CollisionCount(3), WeaponNumR(3), WeaponNumL(3), Visable(true),
		ShadowCenterX(SHADOW_X), ShadowCenterY(SHADOW_Y), HP(12), 
		FrameBeforeInvisable(300),
		FramePassed(0), FrameCount(0), FrameAnimationOwned(10),
		EndofAnimation(false),Wait(true)
		{
			for (int i = 0; i < CollisionCount; ++i)
				Collision[i] = new double[5];
			CalCoord();
		}

	~ShipUniversal();

	/*内容変更関数*/
	void Move(bool Player);
	void Unmove();
	void ChangeGear(int Gear);
	void Turn(bool Right);
	void Draw(double X,double Y, bool Me, bool Test);
	void ShowDestroy(double X, double Y,bool Me);

	void GetNewCosSin();
	void ChangeLMT(double LMT);
	void XChangeDirect();
	void YChangeDirect();
	void ChangeDirect() { XChangeDirect(); YChangeDirect(); }
	void InputCollision(double X, double Y, double R);
	void LoadWeapon(Weapon *Weapon);
	Ammo Shoot(bool right, int Num);
	bool WeaponUsable(bool right);
	void LoadWeaponPos(int Num, double X, double Y, bool right);
	void FreeMemory();
	void CalCoord();
	void ChangeHP(int x) { HP -= x; }
	void ChangeVisable() { Visable = false; }
	void ChangeWait() { Wait = false; }

	/*テスト用中身変更関数*/
	/*正式バッジョンは絶対使わない!*/
	void TESTFUNCTION();
	void ChangeMAXHP();

	/*問い合わせ関数*/
	int ReferRecognition() { return Recognition; }//識別番号
	double ReferCoordX() { return CoordX; }//X座標
	double ReferCoordY() { return CoordY; }//Y座標	
	double ReferXbeforeMove() { return XBeforeMove; }
	double ReferYbeforeMove() { return YBeforeMove; }
	double ReferRadian() { return Radian; }//角度
	int ReferGear() { return Gears; }

	double ReferCCount() { return CollisionCount; }
	double ReferRCollisionX(int N) 
	{ return Collision[N][COLLISION::REAL_COORD_X]; }
	double ReferRCollisionY(int N) 
	{ return Collision[N][COLLISION::REAL_COORD_Y]; }
	double ReferCollisionR(int N)
	{ return Collision[N][COLLISION::RADIUS]; }

	int ReferWeaponOnRight() { return WeaponNumR; }
	int ReferWeaponOnLeft() { return WeaponNumL; }
	bool ReferVisable() { return Visable; }
	bool ReferEnd() { return EndofAnimation; }
	bool ReferWait() { return Wait; }

	bool ReferKill() { return Visable != Wait; }

	int ReferHP() { return HP; }
	int ReferMaxHP() { return MaxHP; }
	int ReferAlive() { return HP > 0; }

private:
	const int *ShipHandle;//画像ハンドル
	const int Recognition;//識別番号
	
	int *ShadowHandle;
	int *DestroyHandle;
	/*初期化していません*/
	double ShadowCenterX;
	double ShadowCenterY;
	double AbsShadowCenterX;
	double AbsShadowCenterY;

	double CoordX;//X座標
	double CoordY;//Y座標
	/*打ち込む判定用*/
	double XBeforeMove;
	double YBeforeMove;

	double Length;//船の長さ
	double Width;//船の幅

	double Radian;//ラジアン//射撃の方向はRa+1/2pi and Ra+3/2pi
	double Speed;//速度
	int Gears;//GEAR_に参考してください
	double GearsToSpeed;//ギアと速度の関係

	double LastMovedTime;//前回移動した時間

	/*初期化していません*/
	double ShipSin;//sin値保存用
	double ShipCos;//cos値保存用

	/*あたり判定用*/
	/*後はフリーメモリに変える*/
	int CollisionCount;//円の数
	double **Collision = new double*[CollisionCount];
	
//	double Collision[10][5];//円のX座標、Y座標、半径、相対X座標、相対Y座標

	//中心点に対する座標
	int WeaponNumR;
	int WeaponNumL;
	double *WeaponXR = new double[WeaponNumR];
	double *WeaponYR = new double[WeaponNumR];
	double *WeaponXL = new double[WeaponNumL];
	double *WeaponYL = new double[WeaponNumL];

	Weapon *WeaponList;

	/*初期化していません！！！*/
	int CoolTime;
	int RightShootTime;
	int LeftShootTime;

	int HP;
	int MaxHP;//初期化していません

	bool Wait;
	bool Visable;
	int FrameBeforeInvisable;
	int FramePassed;
	int FrameCount;
	int FrameAnimationOwned;
	bool EndofAnimation;
};

/*ぶつかる判定やあたり判定*/
bool Crash(ShipUniversal *A, ShipUniversal *B);
bool Crash(ShipUniversal *A, Ammo *B);
bool Crash(ShipUniversal *A, MapObject B);