/****************************************************************/
/*オブジェクトテスト用状態*/
/****************************************************************/

#include"DxLib.h"
#include"MathDefine.h"
#include"ShipUniversal.h"
#include"Weapon.h"
#include"UserInterface.h"
#include"Camera.h"

#include<list>
#include<cmath>
#include<vector>
#include<time.h>
using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;        // エラーが起きたら直ちに終了
	}

	/*画像読む、画像ハンドルの宣言*/
	int MyShipsHandle[20];
	int MyShipsHandleX[20];
	int MyShipsHandleY[20];
	int MapHandle;
	int HPHandleBackground;
	int SWHandle;
	int AmmoHandle[20];
	MapHandle = LoadGraph("Blue.jpg");
	/*分割して読み込む*/
	LoadDivGraph("Allies_Ship_Lv1_6cannons.png",
		5, 5, 1, 160, 160, MyShipsHandle);
	LoadDivGraph("Ammo_Base_Finish.png", 2, 2, 1, 20, 20, AmmoHandle);
	HPHandleBackground = LoadGraph("HP_BANNER_BACKGROUND.png");
	SWHandle = LoadGraph("Steering_Wheel.png");
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
	srand((unsigned)time(NULL));
	char KeyBuf[256];
	/********************/

	/*ゲームオブジェクト宣言*/
	ShipUniversal MyShip(300, 200, 0.0, 2.0, 1, MyShipsHandle,
		GetNowCount(), MyShipsHandleX[0], MyShipsHandleY[0]);
	UserInterface UI(&SWHandle, &HPHandleBackground);
	Camera MainCamera;
	/*動的メモリを使う*/
	Weapon *Alfa[WEAPON_TYPE_NUMBER];
	for (int i = 0; i < WEAPON_TYPE_NUMBER; ++i)
		Alfa[i] = new Weapon(1000, 500, 1, 3, &AmmoHandle[0], &AmmoHandle[1]);
	list<Ammo> AmmoOntheField;
	/************************/

	/*テスト用先処理*/
	MyShip.LoadWeapon(*Alfa);
	MyShip.TESTFUNCTION();
	UI.Inif();
	MyShip.ChangeGear(GEAR_::STOP);
	/************************/

	// キーが押されるまでループします
	// (因みにキーが押されるまで待つ事は『WaitKey』という専用の関数があります)
	while (KeyBuf[KEY_INPUT_ESCAPE] != 1)
	{
		GetHitKeyStateAll(KeyBuf);
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
			if (MyShip.WeaponUsable(true))
				for (int i = 0; i<MyShip.ReferWeaponOnRight(); i++)
					AmmoOntheField.push_back(MyShip.Shoot(true, i));
			if (MyShip.WeaponUsable(false))
				for (int i = 0; i<MyShip.ReferWeaponOnLeft(); i++)
					AmmoOntheField.push_back(MyShip.Shoot(false, i));
			KeyBuf[KEY_INPUT_X] = 0;
		}

		if (KeyBuf[KEY_INPUT_C] == 1&& GetInputChar(TRUE)
			&&MyShip.WeaponUsable(true)) {
			for (int i = 0; i<MyShip.ReferWeaponOnRight(); i++)
				AmmoOntheField.push_back(MyShip.Shoot(true, i));
			KeyBuf[KEY_INPUT_C] = 0;
		}

		if (KeyBuf[KEY_INPUT_Z] == 1 && GetInputChar(TRUE)
			&& MyShip.WeaponUsable(false)) {
			for (int i = 0; i<MyShip.ReferWeaponOnLeft(); i++)
				AmmoOntheField.push_back(MyShip.Shoot(false, i));
			KeyBuf[KEY_INPUT_Z] = 0;
		}

		for (auto itr = AmmoOntheField.begin(); 
			itr != AmmoOntheField.end();) {
			if (itr->Move())
				itr = AmmoOntheField.erase(itr);
			else
				itr++;
			if (AmmoOntheField.empty())
				break;
		}

		MyShip.Move();
		/********************/

		/*カメラ位置を取る*/
		MainCamera.GetPos(MyShip.ReferCoordX(), MyShip.ReferCoordY());
		/********************/

		/*輸出関数*/
		ClearDrawScreen();
		/*マップ描画*/
		DrawRectGraph(0, 0, MainCamera.ReferPSX(), MainCamera.ReferPSY()
			, 640, 480, MapHandle, FALSE, FALSE);
		/*弾移動*/
		if (!AmmoOntheField.empty())
		for (auto itr = AmmoOntheField.begin(); itr != AmmoOntheField.end();
			itr++) {
			itr->Show(MainCamera.ReferPSX(), MainCamera.ReferPSY());
		}
		/*船描画*/
		MyShip.Draw(MainCamera.ReferCameraX(), MainCamera.ReferCameraY());
		/*UI描画*/
		UI.Show(MyShip.ReferRadian());
		/********************/

		// メッセージループに代わる処理をする
		if (ProcessMessage() == -1)
		{
			break;        // エラーが起きたらループを抜ける
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

	DxLib::DeleteGraph(MyShipsHandle[0]);
	DxLib::DeleteGraph(MapHandle);
	DxLib::DeleteGraph(HPHandleBackground);
	/*動的メモリ解放*/
	for (int i = 0; i < 6; ++i)
		delete Alfa[i];

	// ＤＸライブラリ使用の終了処理
	DxLib::DxLib_End();

	return 0;            // ソフトの終了
}
