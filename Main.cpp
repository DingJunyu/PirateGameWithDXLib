/****************************************************************/
/*�I�u�W�F�N�g�e�X�g�p���*/
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
	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;        // �G���[���N�����璼���ɏI��
	}

	/*�摜�ǂށA�摜�n���h���̐錾*/
	int MyShipsHandle[20];
	int MyShipsHandleX[20];
	int MyShipsHandleY[20];
	int MapHandle;
	int HPHandleBackground;
	int SWHandle;
	MapHandle = LoadGraph("Blue.jpg");
	/*�������ēǂݍ���*/
	LoadDivGraph("Allies_Ship_Lv1_6cannons.png",
		5,5,1,160,160, MyShipsHandle);
	HPHandleBackground = LoadGraph("HP_BANNER_BACKGROUND.png");
	SWHandle = LoadGraph("Steering_Wheel.png");
	GetGraphSize(MyShipsHandle[0], &MyShipsHandleX[0],
		&MyShipsHandleY[0]);
	/******************************/

	/*�t���[���R���g���[���[*/
	const int FRAMES_PER_SECOND = 60;
	const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
	DWORD next_game_tick = GetTickCount();
	int sleep_time = 10;
	/************************/

	/*�S�̕ϐ��������Ȃ�*/
	int Count = 0;
	srand((unsigned)time(NULL));
	char KeyBuf[256];
	/********************/

	/*�Q�[���I�u�W�F�N�g�錾*/
	ShipUniversal MyShip(300, 200, 0.0, 3.0, 1, MyShipsHandle,
		GetNowCount(), MyShipsHandleX[0], MyShipsHandleY[0]);
	UserInterface UI(&SWHandle, &HPHandleBackground);
	Camera MainCamera;
	/************************/

	/*�e�X�g�p�揈��*/
	UI.Inif();
	MyShip.Turn(true);
	MyShip.ChangeGear(GEAR_::HALF_SPEED);
	/************************/

	// �L�[���������܂Ń��[�v���܂�
	// (���݂ɃL�[���������܂ő҂��́wWaitKey�x�Ƃ�����p�̊֐�������܂�)
	while (KeyBuf[KEY_INPUT_ESCAPE] != 1)
	{
		GetHitKeyStateAll(KeyBuf);
		/*����֐�*/
		/*�����R���g���[���[*/
		if (KeyBuf[KEY_INPUT_RIGHT] == 1) {
			MyShip.Turn(true);
			KeyBuf[KEY_INPUT_RIGHT] = 0;
		}
		if (KeyBuf[KEY_INPUT_LEFT] == 1) {
			MyShip.Turn(false);
			KeyBuf[KEY_INPUT_LEFT] = 0;
		}
		/*�X�s�[�h�R���g���[���[*/
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

		/*�J�����ʒu�����*/
		MainCamera.GetPos(MyShip.ReferCoordX(), MyShip.ReferCoordY());
		/********************/

		/*�A�o�֐�*/
		ClearDrawScreen();
		DrawRectGraph(0, 0, MainCamera.ReferPSX(), MainCamera.ReferPSY()
			, 640, 480, MapHandle, FALSE,FALSE);
		MyShip.Draw(MainCamera.ReferCameraX(),MainCamera.ReferCameraY());
		UI.Show(MyShip.ReferRadian());
		/********************/

		// ���b�Z�[�W���[�v�ɑ��鏈��������
		if (ProcessMessage() == -1)
		{
			break;        // �G���[���N�����烋�[�v�𔲂���
		}

		/*�X���[�v����*/
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

	// �c�w���C�u�����g�p�̏I������
	DxLib::DxLib_End();

	return 0;            // �\�t�g�̏I��
}
