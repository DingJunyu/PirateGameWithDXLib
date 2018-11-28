/****************************************************************/
/*オブジェクトテスト用状態*/
/****************************************************************/

#include"Functions.h"
using namespace std;
using namespace DxLib;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(SCREEN_X, SCREEN_Y, 32);
	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;        // エラーが起きたら直ちに終了
	}
	SetMainWindowText("Pirate");
	SetAlwaysRunFlag(TRUE);

	/**/
	int MyShipsHandleX;
	int MyShipsHandleY;
	int EnemyShipsHandleX;
	int EnemyShipsHandleY;

	/*ここに追加されたものは必ず使い終わったら解放する！！！！*/
	/*画像読む、画像ハンドルの宣言*/
	int MyShipsHandle[20];
	int ShipShadowHandle;
	int EnemyShipsHandle[20];
	int EnemyShipShadowHandle;
	int MapHandle;
	int ShipSinkHandle[20];
	/*UI*/
	int HPHandleBackground;
	int SWHandle;
	int SpeedControlHandle;
	int SpeedControlMarkHandle;
	/*島など*/
	int MapObjectHandle;
	/*弾*/
	int AmmoHandle[20];

	/*分割して読み込む*/
	LoadDivGraph("Image/Allies_Ship_Lv1_6cannons.png",
		5, 5, 1, 160, 160, MyShipsHandle);
	LoadDivGraph("Image/Ammo_Base_Finish.png", 2, 2, 1
		, 20, 20, AmmoHandle);
	LoadDivGraph("Image/Enemy_Ship_LV1_4Cannons.png",
		5, 5, 1, 160, 160, EnemyShipsHandle);
	/*普通に読み込む*/
	MapHandle = LoadGraph("Image/Background.jpg");
	/*UI*/
	HPHandleBackground = LoadGraph("Image/HP_BANNER_BACKGROUND.png");
	SWHandle = LoadGraph("Image/Steering_Wheel.png");
	SpeedControlHandle = LoadGraph("Image/SPEED_BAR.png");
	SpeedControlMarkHandle = LoadGraph("Image/MARKER.png");
	/*MAPOBJECT*/
	MapObjectHandle =LoadGraph("Image/Island_1.png");
	/*船*/
	ShipShadowHandle =
		LoadGraph("Image/Allies_Ship_Lv1_6Cannons_Shadow.png");
	EnemyShipShadowHandle = LoadGraph(
		"Image/Enemy_Ship_LV1_4Cannons_SD.png");
	LoadDivGraph("Image/Allies_Ship_Lv1_6cannon_sink.png",
		10, 10, 1, 160, 160, ShipSinkHandle);
	/*画像のサイズを保存*/
	GetGraphSize(MyShipsHandle[0], &MyShipsHandleX,
		&MyShipsHandleY);
	GetGraphSize(EnemyShipsHandle[0],&EnemyShipsHandleX,
		&EnemyShipsHandleY);
	/******************************/

	/*フレームコントローラー*/
	const int FRAMES_PER_SECOND = 60;
	const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
	DWORD next_game_tick = GetTickCount();
	int sleep_time = 10;
	/************************/

	/*全体変数初期化など*/
	int Count = 0;
	int ShootCount = 0;
	srand((unsigned)time(NULL));
	char KeyBuf[256];
	/********************/

	/*ゲームオブジェクト宣言*/
	ShipUniversal MyShip(300, 200, 0.0, 2.5, 1, MyShipsHandle, 
		&ShipShadowHandle, ShipSinkHandle,
		GetNowCount(), MyShipsHandleX, MyShipsHandleY);
	UserInterface UI(&SWHandle, &HPHandleBackground,&SpeedControlHandle,
		&SpeedControlMarkHandle);
	Camera MainCamera;
	/*動的メモリを使う*/
	Weapon *Alfa[WEAPON_TYPE_NUMBER];
	for (int i = 0; i < WEAPON_TYPE_NUMBER; ++i)
		Alfa[i] = new Weapon(500, 500, 1, 5.0, &AmmoHandle[0],
			&AmmoHandle[1],1);
	list<Ammo> AmmoOntheField;
	list<Ammo> EnemyAmmoOntheField;
	list<ShipUniversal> EnemyShips;
	MapObject MPO(3,&MapObjectHandle);
	/************************/

	/*テスト変数*/
	bool Ans = false;
	int EnemyKilled = 0;
	int Counter = 0;
	const int MaxCount = 10;
	int RP = 5;
	/************************/

	/*テスト用先処理*/
	MyShip.LoadWeapon(*Alfa);
	MyShip.TESTFUNCTION();
	MyShip.ChangeMAXHP();
	UI.Inif();
	MPO.TEST();
	/************************/

	// キーが押されるまでループします
	// (因みにキーが押されるまで待つ事は『WaitKey』という専用の関数があります)
	while (KeyBuf[KEY_INPUT_ESCAPE] != 1)
	{
		// メッセージループに代わる処理をする
		if (ProcessMessage() == -1)
		{
			break;        // エラーが起きたらループを抜ける
		}


		GetHitKeyStateAll(KeyBuf);
		/*船　　テ　　ス　　ト*/
		if ((rand() % 100 < RP) && (Counter < MaxCount)) {
			double X, Y;
			X = rand() % (BOARDER_X) - 60 + 60;
			Y = rand() % (BOARDER_Y) - 60 + 60;
			double R;
			R = (((double)((rand() % 16 + 1)) / 16)) * PI;
			EnemyShips.push_back(
				ShipUniversal(X, Y, R, 1.4, 2, EnemyShipsHandle,
				&EnemyShipShadowHandle, ShipSinkHandle,
				0, EnemyShipsHandleX, EnemyShipsHandleY));
			auto Able = EnemyShips.end();
			Able--;
			Able->TESTFUNCTION();
			Able->LoadWeapon(*Alfa);
			Counter ++;
		}


		/*動作関数*/
		/*方向コントローラー*/
		if (KeyBuf[KEY_INPUT_RIGHT] == 1) {
			MyShip.Turn(true);
			KeyBuf[KEY_INPUT_RIGHT] = 0;
		}
		if (KeyBuf[KEY_INPUT_LEFT] == 1) {
			MyShip.Turn(false);
			KeyBuf[KEY_INPUT_LEFT] = 0;
		}
		/*スピードコントローラー*/
		if (KeyBuf[KEY_INPUT_UP] == 1 && MyShip.ReferGear() > 
			GEAR_::FULL_SPEED&& GetInputChar(TRUE)) {
			MyShip.ChangeGear(MyShip.ReferGear() - 1);
			KeyBuf[KEY_INPUT_UP] = 0;
		}
		if (KeyBuf[KEY_INPUT_DOWN] == 1 && MyShip.ReferGear()
			< GEAR_::BACK_UP && GetInputChar(TRUE)) {
			MyShip.ChangeGear(MyShip.ReferGear() + 1);
			KeyBuf[KEY_INPUT_DOWN] = 0;
		}

		if (KeyBuf[KEY_INPUT_X] == 1 && GetInputChar(TRUE)) {
			if (MyShip.WeaponUsable(true)) {
				for (int i = 0; i < MyShip.ReferWeaponOnRight(); i++) {
					ShootCount++;
					AmmoOntheField.push_back(MyShip.Shoot(true, i));
				}
			}
			if (MyShip.WeaponUsable(false)) {
				for (int i = 0; i < MyShip.ReferWeaponOnLeft(); i++) {
					ShootCount++;
					AmmoOntheField.push_back(MyShip.Shoot(false, i));
				}
			}
			KeyBuf[KEY_INPUT_X] = 0;
		}

		if (KeyBuf[KEY_INPUT_C] == 1&& GetInputChar(TRUE)
			&&MyShip.WeaponUsable(true)) {
			for (int i = 0; i < MyShip.ReferWeaponOnRight(); i++) {
				ShootCount++;
				AmmoOntheField.push_back(MyShip.Shoot(true, i));
			}
			KeyBuf[KEY_INPUT_C] = 0;
		}

		if (KeyBuf[KEY_INPUT_Z] == 1 && GetInputChar(TRUE)
			&& MyShip.WeaponUsable(false)) {
			for (int i = 0; i < MyShip.ReferWeaponOnLeft(); i++) {
				ShootCount++;
				AmmoOntheField.push_back(MyShip.Shoot(false, i));
			}
			KeyBuf[KEY_INPUT_Z] = 0;
		}
		MyShip.Move(true);

		/*敵移動*/
		for (auto Mark = EnemyShips.begin(); 
			Mark != EnemyShips.end();Mark++) {
			if (!Mark->ReferWait())
				continue;
			if (rand() % 100 > 95&&Mark->ReferGear()>GEAR_::FULL_SPEED) {
				Mark->ChangeGear(Mark->ReferGear() - 1);
			}
			else if (rand() % 100 > 98 && Mark->ReferGear() < GEAR_::BACK_UP) 
			{
				Mark->ChangeGear(Mark->ReferGear() + 1);
			}
			if (rand() % 100 > 90) {
				Mark->Turn(true);
			}
			else if (rand() % 100 > 90) {
				Mark->Turn(false);
			}
			
			if(sqrt(pow(Mark->ReferCoordX()-MyShip.ReferCoordX(),2)+
				pow(Mark->ReferCoordY() - MyShip.ReferCoordY(), 2))<200)
			if (rand() % 100 > 97 && Mark->WeaponUsable(false)) {
				for (int i = 0; i < Mark->ReferWeaponOnLeft(); i++) {
					EnemyAmmoOntheField.push_back(Mark->Shoot(false, i));
				}
			}
			if (rand() % 100 > 97 && Mark->WeaponUsable(true)) {
				for (int i = 0; i < Mark->ReferWeaponOnRight(); i++) {
					EnemyAmmoOntheField.push_back(Mark->Shoot(true, i));
				}
			}
			Mark->Move(false);
		}

		/*弾移動操作*/
		if (!AmmoOntheField.empty())
		for (auto itr = AmmoOntheField.begin(); 
			itr != AmmoOntheField.end(); itr++) {
			itr->Move();
		}
		if (!EnemyAmmoOntheField.empty())
			for (auto itr = EnemyAmmoOntheField.begin();
				itr != EnemyAmmoOntheField.end(); itr++) {
			itr->Move();
		}

		/*あたり判定*/
		if (!AmmoOntheField.empty() && !EnemyShips.empty())
			for (auto itr = AmmoOntheField.begin();
				itr != AmmoOntheField.end(); itr++) {
			if (!itr->ReferUsable()) continue;
			for (auto Mark = EnemyShips.begin();
				Mark != EnemyShips.end(); Mark++) {
				if (Crash(&*Mark, &*itr)) {
					if (Mark->ReferKill())
						EnemyKilled++;
					break;
				}
			}
		}

		/*敵の弾と自分*/
		if (!EnemyAmmoOntheField.empty())
			for (auto itr = EnemyAmmoOntheField.begin();
				itr != EnemyAmmoOntheField.end(); itr++) {
			Crash(&MyShip, &*itr);
		}


		/*使えないものを削除*/
		/*沈んだ敵の船*/
		for (auto Mark = EnemyShips.begin(); Mark != EnemyShips.end();) {
			if (Mark->ReferEnd()) {
				Counter--;
				Mark->FreeMemory();
				Mark = EnemyShips.erase(Mark);
			}
			else
				Mark++;
			if (EnemyShips.empty())
				break;
		}
		/*自分の弾*/
		for (auto Mark = AmmoOntheField.begin(); 
			Mark != AmmoOntheField.end();) {
			if (Mark->ReferEOA())
				Mark = AmmoOntheField.erase(Mark);
			else
				Mark++;
			if (AmmoOntheField.empty())
				break;
		}
		/*敵の弾*/
		for (auto Mark = EnemyAmmoOntheField.begin();
			Mark != EnemyAmmoOntheField.end();) {
			if (Mark->ReferEOA())
				Mark = EnemyAmmoOntheField.erase(Mark);
			else
				Mark++;
			if (EnemyAmmoOntheField.empty())
				break;
		}
		/*************************************/

		/*ぶつかる判定部分*/
		/*船の間*/
		if(!EnemyShips.empty()){
			for (auto Mark = EnemyShips.begin();
				Mark != EnemyShips.end(); Mark++) {
				Crash(&MyShip, &*Mark);
				for (auto BMark = EnemyShips.begin();
					BMark != EnemyShips.end(); BMark++) {
					if (Mark == BMark)
						continue;
					Crash(&*Mark, &*BMark);
				}
			}
		}
		/*敵と島*/
		if (!EnemyShips.empty())
			for (auto Mark = EnemyShips.begin();
				Mark != EnemyShips.end(); Mark++) {
			if (!Mark->ReferWait())
				continue;
			Crash(&*Mark, MPO);
		}

		/*自機と島*/
		for (int i = 0; i < MPO.ReferColCount(); ++i) {
			Crash(&MyShip, MPO);
		}		
		/********************/

		/*カメラ位置を取る*/
		MainCamera.GetPos(MyShip.ReferCoordX(), MyShip.ReferCoordY());
		UI.ReadHPandMaxHP(MyShip.ReferHP(), MyShip.ReferMaxHP());
		/********************/

		/*輸出関数*/
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		/*マップ描画*/
		DrawRectGraph(0, 0, (int)(MainCamera.ReferPSX()),
			(int)(MainCamera.ReferPSY())
			, SCREEN_X, SCREEN_Y, MapHandle, FALSE, FALSE);
		MPO.Show(MainCamera.ReferPSX(), MainCamera.ReferPSY());
		/*船描画*/
		MyShip.Draw(MainCamera.ReferCameraX(), MainCamera.ReferCameraY()
			,true,false);
		if (!EnemyShips.empty()) {
			for (auto Mark = EnemyShips.begin();
				Mark != EnemyShips.end(); Mark++)
				Mark->Draw(MainCamera.ReferPSX(), MainCamera.ReferPSY(),
					false, false);

		}
		/*弾描画*/
		if (!AmmoOntheField.empty())
			for (auto itr = AmmoOntheField.begin();
				itr != AmmoOntheField.end();itr++) {
			itr->Show(MainCamera.ReferPSX(), MainCamera.ReferPSY());
		}
		if (!EnemyAmmoOntheField.empty())
			for (auto itr = EnemyAmmoOntheField.begin(); 
				itr != EnemyAmmoOntheField.end();itr++) {
			itr->Show(MainCamera.ReferPSX(), MainCamera.ReferPSY());
		}
		/*UI描画*/
		UI.Show(MyShip.ReferRadian(),MyShip.ReferGear());
		char str[25];
		_itoa_s(EnemyKilled, str, 10);
		unsigned int Cr = GetColor(255, 0, 0);
		DrawString(20, 60, str, Cr);
		if (MyShip.ReferHP() <= 0) {
			DrawString(SCREEN_X / 2, SCREEN_Y / 2,
				"GAME OVER", Cr);
		}
		/********************/

		ScreenFlip();//画像輸出

		if (MyShip.ReferHP() <= 0) {
			rewind(stdin);
			WaitKey();
			break;
		}

		
		/*スリープ処理*/
		next_game_tick += SKIP_TICKS;
		sleep_time = next_game_tick - GetTickCount();
		if (sleep_time >= 0)
		{
			Sleep(sleep_time);
		}
		/**************/
	}
	/*メモリ解放*/
	for (int i = 0; i < 5; i++) {
		DeleteGraph(MyShipsHandle[1]);
		DeleteGraph(EnemyShipsHandle[i]);
	}
	for (int i = 0; i < 2; i++) {
		DeleteGraph(AmmoHandle[i]);
	}
	for (int i = 0; i < 10; i++) {
		DeleteGraph(ShipSinkHandle[i]);
	}
	DeleteGraph(MapHandle);
	DeleteGraph(HPHandleBackground);
	DeleteGraph(ShipShadowHandle);
	DeleteGraph(EnemyShipShadowHandle);
	DeleteGraph(MapObjectHandle);

	for(int i=0;i<10;i++)
	DeleteGraph(ShipSinkHandle[i]);
	/*動的メモリ解放*/
	for (int i = 0; i < 6; ++i)
		delete Alfa[i];

	// ＤＸライブラリ使用の終了処理
	DxLib_End();

	return 0;            // ソフトの終了
}

void SingleGameMain() {

}