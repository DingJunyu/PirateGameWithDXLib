#include"DxLib.h"
#include"MathDefine.h"
#include"ShipUniversal.h"
#include"Weapon.h"

#include<list>
#include<cmath>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;        // �G���[���N�����璼���ɏI��
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


	// �L�[���������܂Ń��[�v���܂�
	// (���݂ɃL�[���������܂ő҂��́wWaitKey�x�Ƃ�����p�̊֐�������܂�)
	while (CheckHitKey(KEY_INPUT_ESCAPE) != 1)
	{
		ClearDrawScreen();
		ClearDrawScreen();

		DrawGraph(0, 0, MapHandle, FALSE);

		MyShip.Move();

		MyShip.Draw();

		// ���b�Z�[�W���[�v�ɑ��鏈��������
		if (ProcessMessage() == -1)
		{
			break;        // �G���[���N�����烋�[�v�𔲂���
		}

	}

	DeleteGraph(MyShipsHandle[0]);
	DeleteGraph(MapHandle);

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();

	return 0;            // �\�t�g�̏I��
}
