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
#include<vector>
#include<time.h>
using namespace std;

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
	int AmmoHandle[20];
	MapHandle = LoadGraph("Blue.jpg");
	/*�������ēǂݍ���*/
	LoadDivGraph("Allies_Ship_Lv1_6cannons.png",
		5, 5, 1, 160, 160, MyShipsHandle);
	LoadDivGraph("Ammo_Base_Finish.png", 2, 2, 1, 20, 20, AmmoHandle);
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
	ShipUniversal MyShip(300, 200, 0.0, 2.0, 1, MyShipsHandle,
		GetNowCount(), MyShipsHandleX[0], MyShipsHandleY[0]);
	UserInterface UI(&SWHandle, &HPHandleBackground);
	Camera MainCamera;
	/*���I���������g��*/
	Weapon *Alfa[WEAPON_TYPE_NUMBER];
	for (int i = 0; i < WEAPON_TYPE_NUMBER; ++i)
		Alfa[i] = new Weapon(1000, 500, 1, 3, &AmmoHandle[0], &AmmoHandle[1]);
	list<Ammo> AmmoOntheField;
	/************************/

	/*�e�X�g�p�揈��*/
	MyShip.LoadWeapon(*Alfa);
	MyShip.TESTFUNCTION();
	UI.Inif();
	MyShip.ChangeGear(GEAR_::STOP);
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

		/*�J�����ʒu�����*/
		MainCamera.GetPos(MyShip.ReferCoordX(), MyShip.ReferCoordY());
		/********************/

		/*�A�o�֐�*/
		ClearDrawScreen();
		/*�}�b�v�`��*/
		DrawRectGraph(0, 0, MainCamera.ReferPSX(), MainCamera.ReferPSY()
			, 640, 480, MapHandle, FALSE, FALSE);
		/*�e�ړ�*/
		if (!AmmoOntheField.empty())
		for (auto itr = AmmoOntheField.begin(); itr != AmmoOntheField.end();
			itr++) {
			itr->Show(MainCamera.ReferPSX(), MainCamera.ReferPSY());
		}
		/*�D�`��*/
		MyShip.Draw(MainCamera.ReferCameraX(), MainCamera.ReferCameraY());
		/*UI�`��*/
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
	/*���I���������*/
	for (int i = 0; i < 6; ++i)
		delete Alfa[i];

	// �c�w���C�u�����g�p�̏I������
	DxLib::DxLib_End();

	return 0;            // �\�t�g�̏I��
}
