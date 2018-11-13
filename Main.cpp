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
#include<time.h>

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
	MapHandle = LoadGraph("Blue.jpg");
	/*分割して読み込む*/
	LoadDivGraph("Allies_Ship_Lv1_6cannons.png",
		5,5,1,160,160, MyShipsHandle);
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
	ShipUniversal MyShip(300, 200, 0.0, 3.0, 1, MyShipsHandle,
		GetNowCount(), MyShipsHandleX[0], MyShipsHandleY[0]);
	UserInterface UI(&SWHandle, &HPHandleBackground);
	Camera MainCamera;
	/************************/

	/*テスト用先処理*/
	UI.Inif();
	MyShip.Turn(true);
	MyShip.ChangeGear(GEAR_::HALF_SPEED);
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
		if (KeyBuf[KEY_INPUT_UP] == 1 && MyShip.ReferGear()
			> GEAR_::FULL_SPEED&& GetInputChar(TRUE)) {
			MyShip.ChangeGear(MyShip.ReferGear() - 1);
			KeyBuf[KEY_INPUT_UP] = 0;
		}
		if (KeyBuf[KEY_INPUT_DOWN] == 1 && MyShip.ReferGear()
			< GEAR_::BACK_UP && GetInputChar(TRUE)) {
			MyShip.ChangeGear(MyShip.ReferGear() + 1);
			KeyBuf[KEY_INPUT_DOWN] = 0;
		}
		MyShip.Move();
		/********************/

		/*カメラ位置を取る*/
		MainCamera.GetPos(MyShip.ReferCoordX(), MyShip.ReferCoordY());
		/********************/

		/*輸出関数*/
		ClearDrawScreen();
		DrawRectGraph(0, 0, MainCamera.ReferPSX(), MainCamera.ReferPSY()
			, 640, 480, MapHandle, FALSE,FALSE);
		MyShip.Draw(MainCamera.ReferCameraX(),MainCamera.ReferCameraY());
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

	// ＤＸライブラリ使用の終了処理
	DxLib::DxLib_End();

	return 0;            // ソフトの終了
}
