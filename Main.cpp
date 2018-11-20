/****************************************************************/
/*オブジェクトテスト用状態*/
/****************************************************************/

#include"Functions.h"
using namespace std;

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

	/*画像読む、画像ハンドルの宣言*/
	int MyShipsHandle[20];
	int MyShipsHandleX[20];
	int MyShipsHandleY[20];
	int ShipShadowHandle;
	int MapHandle;
	int ShipSinkHandle[20];
	/*UI*/
	int HPHandleBackground;
	int SWHandle;
	/*島など*/
	int MapObjectHandle;
	/*弾*/
	int AmmoHandle[20];
	MapHandle = LoadGraph("Background.jpg");
	/*分割して読み込む*/
	LoadDivGraph("Allies_Ship_Lv1_6cannons.png",
		5, 5, 1, 160, 160, MyShipsHandle);
	LoadDivGraph("Ammo_Base_Finish.png", 2, 2, 1, 20, 20, AmmoHandle);
	HPHandleBackground = LoadGraph("HP_BANNER_BACKGROUND.png");
	SWHandle = LoadGraph("Steering_Wheel.png");
	MapObjectHandle =LoadGraph("Island_1.png");
	ShipShadowHandle = LoadGraph("Allies_Ship_Lv1_6Cannons_Shadow.png");
	LoadDivGraph("Allies_Ship_Lv1_6cannon_sink.png",
		10, 10, 1, 160, 160, ShipSinkHandle);
	GetGraphSize(MyShipsHandle[0], &MyShipsHandleX[0],
		&MyShipsHandleY[0]);
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
	ShipUniversal MyShip(300, 200, 0.0, 2.0, 1, MyShipsHandle, 
		&ShipShadowHandle, ShipSinkHandle,
		GetNowCount(), MyShipsHandleX[0], MyShipsHandleY[0]);
	UserInterface UI(&SWHandle, &HPHandleBackground);
	Camera MainCamera;
	/*動的メモリを使う*/
	Weapon *Alfa[WEAPON_TYPE_NUMBER];
	for (int i = 0; i < WEAPON_TYPE_NUMBER; ++i)
		Alfa[i] = new Weapon(1000, 500, 1, 3, &AmmoHandle[0],
			&AmmoHandle[1]);
	list<Ammo> AmmoOntheField;
	list<ShipUniversal> EnemyShips;
	MapObject MPO(3,&MapObjectHandle);
	/************************/

	/*テスト変数*/
	bool Ans = false;
	int EnemyKilled = 0;
	int Counter = 0;
	const int MaxCount = 20;
	int RP = 5;
	/************************/

	/*テスト用先処理*/
	MyShip.LoadWeapon(*Alfa);
	MyShip.TESTFUNCTION();
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
			EnemyShips.push_back(ShipUniversal(X, Y, R, 2.0, 2, MyShipsHandle,
				&ShipShadowHandle, ShipSinkHandle,
				0,MyShipsHandleX[0], MyShipsHandleY[0]));
			auto Able = EnemyShips.end();
			Able--;
			Able->TESTFUNCTION();
			Able->CalCoord();
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

		/*弾移動操作*/
		if (!AmmoOntheField.empty())
		for (auto itr = AmmoOntheField.begin(); 
			itr != AmmoOntheField.end(); itr++) {
			if (itr->Move())
				itr->ChangeUsable();
		}

		/*あたり判定*/
		if (!AmmoOntheField.empty()&&!EnemyShips.empty())
		for (auto itr = AmmoOntheField.begin();
			itr != AmmoOntheField.end();itr++) {
			if (!itr->ReferUsable())
				continue;
			for (auto Mark = EnemyShips.begin();
				Mark != EnemyShips.end(); Mark++) {
				if (Mark->Crash(itr->ReferX(), itr->ReferY(), itr->ReferR(),
					itr->ReferSX(), itr->ReferSY())) {
					itr->ChangeUsable();
					if (Mark->ReferVisable()) {
						EnemyKilled++;
					}
					break;
				}
			}
		}

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

		for (auto Mark = AmmoOntheField.begin(); 
			Mark != AmmoOntheField.end();) {
			if (Mark->ReferEOA())
				Mark = AmmoOntheField.erase(Mark);
			else
				Mark++;
			if (AmmoOntheField.empty())
				break;
		}

		/*打ち込む判定*/
		MyShip.Move();
		MyShip.CalCoord();
		bool Movable = true;
		if(!EnemyShips.empty())
			for (auto Mark = EnemyShips.begin();
				Mark != EnemyShips.end();Mark++) {
			for (int i = 0; i < MyShip.ReferCCount(); ++i) {
				if (Mark->Crash(MyShip.ReferRCollisionX(i), 
					MyShip.ReferRCollisionY(i),
					MyShip.ReferCollisionR(i))) {
					Movable = false;
					goto Outline;//テスト用
				}
			}
		}
		for (int i = 0; i < MPO.ReferColCount(); ++i) {
			if (MyShip.Crash(MPO.ReferColRX(i), MPO.ReferColRY(i),
				MPO.ReferColR(i))) {
				Movable = false;
				break;
			}
		}
Outline:
		if (!Movable) {
			MyShip.ChangeGear(GEAR_::STOP);
			MyShip.Unmove();
			MyShip.CalCoord();
		}
		
		/********************/

		/*カメラ位置を取る*/
		MainCamera.GetPos(MyShip.ReferCoordX(), MyShip.ReferCoordY());
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
		MyShip.Draw(MainCamera.ReferCameraX(), MainCamera.ReferCameraY(),true);
		if (!EnemyShips.empty()) {
			for (auto Mark = EnemyShips.begin();
				Mark != EnemyShips.end();Mark++)
				Mark->Draw(MainCamera.ReferPSX(), MainCamera.ReferPSY(), false);

		}
		/*弾描画*/
		if (!AmmoOntheField.empty())
			for (auto itr = AmmoOntheField.begin(); itr != AmmoOntheField.end();
				itr++) {
			itr->Show(MainCamera.ReferPSX(), MainCamera.ReferPSY());
		}
		/*UI描画*/
		UI.Show(MyShip.ReferRadian());
		char str[25];
		_itoa_s(EnemyKilled, str, 10);
		unsigned int Cr = GetColor(255, 0, 0);
		DrawString(20, 60, str, Cr);
		/********************/
		ScreenFlip();

		
		/*スリープ処理*/
		next_game_tick += SKIP_TICKS;
		sleep_time = next_game_tick - GetTickCount();
		if (sleep_time >= 0)
		{
			Sleep(sleep_time);
		}
		/**************/
	}

	DxLib::DeleteGraph(MyShipsHandle[0]);
	DxLib::DeleteGraph(MapHandle);
	DxLib::DeleteGraph(HPHandleBackground);
	DxLib::DeleteGraph(ShipShadowHandle);
	DxLib::DeleteGraph(MapObjectHandle);
	for(int i=0;i<10;i++)
	DxLib::DeleteGraph(ShipSinkHandle[i]);
	/*動的メモリ解放*/
	for (int i = 0; i < 6; ++i)
		delete Alfa[i];

	// ＤＸライブラリ使用の終了処理
	DxLib::DxLib_End();

	return 0;            // ソフトの終了
}
