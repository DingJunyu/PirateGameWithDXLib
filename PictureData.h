#pragma once
#define ALLIES_SHIP_COUNT 1
#define ENEMIES_SHIP_COUNT 1
#define AMMO_TYPE 1

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
	int *HPBarHandle;
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

