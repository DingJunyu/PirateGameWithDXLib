#pragma once
#include"DxLib.h"
const int ALLIES_SHIP_COUNT = 2;
const int ENEMY_SHIP_COUNT = 2;
const int AMMO_TYPE = 2;
const int MAP_COUNT = 2;
const int MAP_OBJECT_TYPE = 2;
/*このクラスは画像データを保管するクラスです*/
class PictureData
{
public:
	PictureData();
	~PictureData();

	/*初期化関数*/
	void AllInif();

	/*問い合わせ関数*/
	/*船*/
	int *ReferAlliesShipHandle(int x) { return AlliesShipsHandle[x]; }
	int *ReferAlliesShipSinkHandle(int x)
	{
		return AlliesShipsSinkHandle[x];
	}
	int ReferAlliesShipShadowHandle(int x)
	{
		return AlliesShipShadowHandle[x];
	}
	int *ReferEnemyShipHandle(int x) { return EnemyShipsHandle[x]; }
	int *ReferEnemyShipsSinkHandle(int x)
	{
		return EnemyShipsSinkHandle[x];
	}
	int ReferEnemyShipsShadowHandle(int x)
	{
		return EnemyShipShadowHandle[x];
	}
	int ReferShipX() { return ShipX; }
	int ReferShipY() { return ShipY; }

	/*マップ*/
	int ReferMap(int x) { return MapHandle[x]; }
	int ReferMapX(int x) { return MapX[x]; }
	int ReferMapY(int x) { return MapY[x]; }

	/*弾*/
	int ReferAmmo(int x) { return AmmoHandle[x]; }
	int ReferAmmoX(int x) { return AmmoX[x]; }
	int ReferAmmoY(int x) { return AmmoY[x]; }

	/*UI*/
	/*HPバー*/
	int ReferHPBar() { return HPBarHandle; }
	int ReferHPBarX() { return HPBX; }
	int ReferHPBarY() { return HPBY; }

	/*輪*/
	int ReferSW() { return SWHandle; }
	int ReferSWX() { return SWX; }
	int ReferSWY() { return SWY; }

	int ReferSpeedControl() { return SpeedControlHandle; }
	int ReferSpeedControlX() { return SCMX; }
	int ReferSpeedControlY() { return SCMY; }

	/*メモリ回収*/
	void FreeMemory();
	void FreePicture();
	void FREE_ALL() { FreeMemory(); FreePicture(); }

private:
	/*船データ*/
	/*ハンドル*/
	int **AlliesShipsHandle;
	int **AlliesShipsSinkHandle;
	int *AlliesShipShadowHandle;
	int **EnemyShipsHandle;
	int **EnemyShipsSinkHandle;
	int *EnemyShipShadowHandle;
	/*サイズ*/
	int ShipX;
	int ShipY;
	/****************************/

	/*マップオブジェクト*/
	int *MapObjectHandle;
	int *MapObjectShadowHandle;
	int *MOX;
	int *MOY;
	/****************************/

	/*マップデータ*/
	/*ハンドル*/
	int *MapHandle;
	/*サイズ*/
	int *MapX;
	int *MapY;
	/****************************/

	/*弾データ*/
	/*ハンドル*/
	int *AmmoHandle;
	/*サイズ*/
	int *AmmoX;
	int *AmmoY;
	/****************************/

	/*UIデータ*/
	/*HPバー*/
	int HPBarHandle;
	int HPBX;
	int HPBY;
	/*輪*/
	int SWHandle;
	int SWX;
	int SWY;
	/*スピート部分*/
	/*背景*/
	int SpeedControlHandle;
	int SCX;
	int SCY;
	/*マーカー*/
	int SpeedControlMarkHandle;
	int SCMX;
	int SCMY;
	/****************************/
};

