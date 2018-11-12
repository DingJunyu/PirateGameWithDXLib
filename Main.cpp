#include"DxLib.h"
#include"MathDefine.h"
#include"ShipUniversal.h"
#include"Weapon.h"

#include<list>
#include<cmath>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;        // エラーが起きたら直ちに終了
	}
	
	int MyShipsHandle[20];
	int MyShipsHandleX[20];
	int MyShipsHandleY[20];
	int MapHandle;
	MapHandle = LoadGraph("Blue.jpg");
	MyShipsHandle[0] = LoadGraph("Allies_Ship_Lv1_6Guns.png");
	GetGraphSize(MyShipsHandle[0], &MyShipsHandleX[0],
		&MyShipsHandleY[0]);

	if (SetTransColor(0, 255, 0) == -1)
		exit(1);

	ShipUniversal MyShip(300, 200, 0.0, 1.0, 1, MyShipsHandle[0],
		GetNowCount(), MyShipsHandleX[0], MyShipsHandleY[0]);

	MyShip.Turn(true);

	MyShip.ChangeGear(GEAR_::HALF_SPEED);


	// キーが押されるまでループします
	// (因みにキーが押されるまで待つ事は『WaitKey』という専用の関数があります)
	while (CheckHitKey(KEY_INPUT_ESCAPE) != 1)
	{
		ClearDrawScreen();
		ClearDrawScreen();

		DrawGraph(0, 0, MapHandle, FALSE);

		MyShip.Move();

		MyShip.Draw();

		// メッセージループに代わる処理をする
		if (ProcessMessage() == -1)
		{
			break;        // エラーが起きたらループを抜ける
		}

	}

	DeleteGraph(MyShipsHandle[0]);
	DeleteGraph(MapHandle);

	// ＤＸライブラリ使用の終了処理
	DxLib_End();

	return 0;            // ソフトの終了
}
