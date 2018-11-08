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
	SetGraphMode(1280, 720, 24, 60);

	// キーが押されるまでループします
	// (因みにキーが押されるまで待つ事は『WaitKey』という専用の関数があります)
	while (CheckHitKeyAll() == 0)
	{
		// メッセージループに代わる処理をする
		if (ProcessMessage() == -1)
		{
			break;        // エラーが起きたらループを抜ける
		}
	}

	// ＤＸライブラリ使用の終了処理
	DxLib_End();

	return 0;            // ソフトの終了
}
