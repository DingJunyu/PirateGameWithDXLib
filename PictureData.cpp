#include "PictureData.h"



PictureData::PictureData()
{
	/*船の動的メモリを宣言*/
	AlliesShipsHandle = new int *[ALLIES_SHIP_COUNT];
	for (int i = 0; i < ALLIES_SHIP_COUNT; ++i)
		AlliesShipsHandle[i] = new int[5];

	AlliesShipsSinkHandle = new int *[ALLIES_SHIP_COUNT];
	for (int i = 0; i < ALLIES_SHIP_COUNT; ++i)
		AlliesShipsSinkHandle[i] = new int[10];

	AlliesShipShadowHandle = new int[ALLIES_SHIP_COUNT];

	EnemyShipsHandle = new int *[ENEMY_SHIP_COUNT];
	for (int i = 0; i < ENEMY_SHIP_COUNT; ++i)
		EnemyShipsHandle[i] = new int[5];

	EnemyShipsSinkHandle = new int *[ENEMY_SHIP_COUNT];
	for (int i = 0; i < ENEMY_SHIP_COUNT; ++i)
		EnemyShipsSinkHandle[i] = new int[10];

	EnemyShipShadowHandle = new int[ENEMY_SHIP_COUNT];

	/*マップオブジェクト*/
	MapObjectHandle = new int[MAP_OBJECT_TYPE];
	MapObjectShadowHandle = new int[MAP_OBJECT_TYPE];
	MOX = new int[MAP_OBJECT_TYPE];
	MOY = new int[MAP_OBJECT_TYPE];

	/*マップ*/
	MapHandle = new int[MAP_COUNT];
	MapX = new int[MAP_COUNT];
	MapY = new int[MAP_COUNT];

	/*弾*/
	AmmoHandle = new int[AMMO_TYPE];
	AmmoX = new int[AMMO_TYPE];
	AmmoY = new int[AMMO_TYPE];
}


PictureData::~PictureData()
{
}

void PictureData::FreeMemory() {
	/*船用回収*/
	for (int i = 0; i < ALLIES_SHIP_COUNT; ++i)
		delete[] AlliesShipsHandle[i];
	delete[] AlliesShipsHandle;

	for (int i = 0; i < ALLIES_SHIP_COUNT; ++i)
		delete[] AlliesShipsSinkHandle[i];

	delete[] AlliesShipShadowHandle;

	for (int i = 0; i < ENEMY_SHIP_COUNT; ++i)
		delete[] EnemyShipsHandle[i];
	delete[] EnemyShipsHandle;

	for (int i = 0; i < ENEMY_SHIP_COUNT; ++i)
		delete[] EnemyShipsSinkHandle[i];

	delete[] EnemyShipShadowHandle;

	/*マップオブジェクト*/
	delete[] MapObjectHandle;
	delete[] MapObjectShadowHandle;
	delete[] MOX;
	delete[] MOY;

	/*マップ*/
	delete[] MapHandle;
	delete[] MapX;
	delete[] MapY;

	/*弾*/
	delete[] AmmoHandle;
	delete[] AmmoX;
	delete[] AmmoY;
}

void PictureData::AllInif() {
	/*船*/
	LoadDivGraph("Image/Allies_Ship_Lv1_6cannons.png",
		5, 5, 1, 160, 160, AlliesShipsHandle[0]);
	AlliesShipShadowHandle[0] =
		LoadGraph("Image/Allies_Ship_Lv1_6Cannons_Shadow.png");
	LoadDivGraph("Image/Enemy_Ship_LV1_4Cannons.png",
		5, 5, 1, 160, 160, EnemyShipsHandle[0]);
	EnemyShipShadowHandle[0] = LoadGraph(
		"Image/Enemy_Ship_LV1_4Cannons_SD.png");
	LoadDivGraph("Image/Allies_Ship_Lv1_6cannon_sink.png",
		10, 10, 1, 160, 160, AlliesShipsSinkHandle[0]);

	/*マップ*/
	MapHandle[0] = LoadGraph("Image/Background.jpg");

	/*弾*/
	LoadDivGraph("Image/Ammo_Base_Finish.png", 2, 2, 1
		, 20, 20, AmmoHandle);
	
	/*MAPOBJECT*/
	MapObjectHandle[0] = LoadGraph("Image/Island_1.png");

	/*UI*/
	HPBarHandle = LoadGraph("Image/HP_BANNER_BACKGROUND.png");
	SWHandle = LoadGraph("Image/Steering_Wheel.png");
	SpeedControlHandle = LoadGraph("Image/SPEED_BAR.png");
	SpeedControlMarkHandle = LoadGraph("Image/MARKER.png");

	/*画像のサイズを保存*/
	GetGraphSize(AlliesShipsHandle[0][0], &ShipX,
		&ShipY);
	/******************************/
}

void PictureData::FreePicture() {
	/*船*/
	for (int i = 0; i < 5; i++) {
		DeleteGraph(AlliesShipsHandle[0][i]);
		DeleteGraph(EnemyShipsHandle[0][i]);
	}

	for (int i = 0; i < 10; i++) {
		DeleteGraph(AlliesShipsSinkHandle[0][i]);
	}
	DeleteGraph(AlliesShipShadowHandle[0]);
	DeleteGraph(EnemyShipShadowHandle[0]);

	/*マップ*/
	DeleteGraph(MapHandle[0]);

	/*弾*/
	for (int i = 0; i < 2; i++) {
		DeleteGraph(AmmoHandle[i]);
	}
	/*マップオブジェクト*/
	DeleteGraph(MapObjectHandle[0]);

	/*UI*/
	DeleteGraph(HPBarHandle);
	DeleteGraph(SWHandle);
	DeleteGraph(SpeedControlHandle);
	DeleteGraph(SpeedControlMarkHandle);
}