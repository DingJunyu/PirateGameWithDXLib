/****************************************************************/
/*�I�u�W�F�N�g�e�X�g�p���*/
/****************************************************************/

#include"Functions.h"
using namespace std;
using namespace DxLib;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(SCREEN_X, SCREEN_Y, 32);
	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;        // �G���[���N�����璼���ɏI��
	}
	SetMainWindowText("Pirate");
	SetAlwaysRunFlag(TRUE);

	/**/
	int MyShipsHandleX;
	int MyShipsHandleY;
	int EnemyShipsHandleX;
	int EnemyShipsHandleY;

	/*�����ɒǉ����ꂽ���͕̂K���g���I�������������I�I�I�I*/
	/*�摜�ǂށA�摜�n���h���̐錾*/
	int MyShipsHandle[20];
	int ShipShadowHandle;
	int EnemyShipsHandle[20];
	int EnemyShipShadowHandle;
	int MapHandle;
	int ShipSinkHandle[20];
	/*UI*/
	int HPHandleBackground;
	int SWHandle;
	/*���Ȃ�*/
	int MapObjectHandle;
	/*�e*/
	int AmmoHandle[20];

	/*�������ēǂݍ���*/
	LoadDivGraph("Image/Allies_Ship_Lv1_6cannons.png",
		5, 5, 1, 160, 160, MyShipsHandle);
	LoadDivGraph("Image/Ammo_Base_Finish.png", 2, 2, 1
		, 20, 20, AmmoHandle);
	LoadDivGraph("Image/Enemy_Ship_LV1_4Cannons.png",
		5, 5, 1, 160, 160, EnemyShipsHandle);
	/*���ʂɓǂݍ���*/
	MapHandle = LoadGraph("Image/Background.jpg");
	HPHandleBackground = LoadGraph("Image/HP_BANNER_BACKGROUND.png");
	SWHandle = LoadGraph("Image/Steering_Wheel.png");
	MapObjectHandle =LoadGraph("Image/Island_1.png");
	ShipShadowHandle =
		LoadGraph("Image/Allies_Ship_Lv1_6Cannons_Shadow.png");
	EnemyShipShadowHandle = LoadGraph(
		"Image/Enemy_Ship_LV1_4Cannons_SD.png");
	LoadDivGraph("Image/Allies_Ship_Lv1_6cannon_sink.png",
		10, 10, 1, 160, 160, ShipSinkHandle);
	/*�摜�̃T�C�Y��ۑ�*/
	GetGraphSize(MyShipsHandle[0], &MyShipsHandleX,
		&MyShipsHandleY);
	GetGraphSize(EnemyShipsHandle[0],&EnemyShipsHandleX,
		&EnemyShipsHandleY);
	/******************************/

	/*�t���[���R���g���[���[*/
	const int FRAMES_PER_SECOND = 60;
	const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
	DWORD next_game_tick = GetTickCount();
	int sleep_time = 10;
	/************************/

	/*�S�̕ϐ��������Ȃ�*/
	int Count = 0;
	int ShootCount = 0;
	srand((unsigned)time(NULL));
	char KeyBuf[256];
	/********************/

	/*�Q�[���I�u�W�F�N�g�錾*/
	ShipUniversal MyShip(300, 200, 0.0, 1.5, 1, MyShipsHandle, 
		&ShipShadowHandle, ShipSinkHandle,
		GetNowCount(), MyShipsHandleX, MyShipsHandleY);
	UserInterface UI(&SWHandle, &HPHandleBackground);
	Camera MainCamera;
	/*���I���������g��*/
	Weapon *Alfa[WEAPON_TYPE_NUMBER];
	for (int i = 0; i < WEAPON_TYPE_NUMBER; ++i)
		Alfa[i] = new Weapon(500, 500, 1, 5.0, &AmmoHandle[0],
			&AmmoHandle[1]);
	list<Ammo> AmmoOntheField;
	list<Ammo> EnemyAmmoOntheField;
	list<ShipUniversal> EnemyShips;
	MapObject MPO(3,&MapObjectHandle);
	/************************/

	/*�e�X�g�ϐ�*/
	bool Ans = false;
	int EnemyKilled = 0;
	int Counter = 0;
	const int MaxCount = 20;
	int RP = 5;
	/************************/

	/*�e�X�g�p�揈��*/
	MyShip.LoadWeapon(*Alfa);
	MyShip.TESTFUNCTION();
	MyShip.ChangeMAXHP();
	UI.Inif();
	MPO.TEST();
	/************************/

	// �L�[���������܂Ń��[�v���܂�
	// (���݂ɃL�[���������܂ő҂��́wWaitKey�x�Ƃ�����p�̊֐�������܂�)
	while (KeyBuf[KEY_INPUT_ESCAPE] != 1)
	{
		// ���b�Z�[�W���[�v�ɑ��鏈��������
		if (ProcessMessage() == -1)
		{
			break;        // �G���[���N�����烋�[�v�𔲂���
		}


		GetHitKeyStateAll(KeyBuf);
		/*�D�@�@�e�@�@�X�@�@�g*/
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
			Able->CalCoord();
			Able->LoadWeapon(*Alfa);
			Counter ++;
		}


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

		/*�G�ړ�*/
		for (auto Mark = EnemyShips.begin(); 
			Mark != EnemyShips.end();Mark++) {
			if (!Mark->ReferWait())
				continue;
			if (rand() % 100 > 95&&Mark->ReferGear()>GEAR_::FULL_SPEED) {
				Mark->ChangeGear(Mark->ReferGear() - 1);
			}
			else if (rand() % 100 > 99 && Mark->ReferGear() < GEAR_::BACK_UP) 
			{
				Mark->ChangeGear(Mark->ReferGear() + 1);
			}
			if (rand() % 100 > 90) {
				Mark->Turn(true);
			}
			else if (rand() % 100 > 90) {
				Mark->Turn(false);
			}
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

		/*�e�ړ�����*/
		if (!AmmoOntheField.empty())
		for (auto itr = AmmoOntheField.begin(); 
			itr != AmmoOntheField.end(); itr++) {
			if (itr->Move())
				itr->ChangeUsable();
		}
		if (!EnemyAmmoOntheField.empty())
			for (auto itr = EnemyAmmoOntheField.begin();
				itr != EnemyAmmoOntheField.end(); itr++) {
			if (itr->Move())
				itr->ChangeUsable();
		}

		/*�����蔻��*/
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
					if(Mark->ReferVisable()!=Mark->ReferWait())
						EnemyKilled++;
					break;
				}
			}
		}
		/*�G�̒e�Ǝ���*/
		if (!EnemyAmmoOntheField.empty())
			for (auto itr = EnemyAmmoOntheField.begin();
				itr != EnemyAmmoOntheField.end(); itr++) {
			if (!itr->ReferUsable())
				continue;
			if (MyShip.Crash(itr->ReferX(), itr->ReferY(), itr->ReferR(),
				itr->ReferSX(), itr->ReferSY())) {
				itr->ChangeUsable();
			}
		}


		/*�g���Ȃ����̂��폜*/
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
		/*�����̒e*/
		for (auto Mark = AmmoOntheField.begin(); 
			Mark != AmmoOntheField.end();) {
			if (Mark->ReferEOA())
				Mark = AmmoOntheField.erase(Mark);
			else
				Mark++;
			if (AmmoOntheField.empty())
				break;
		}
		/*�G�̒e*/
		for (auto Mark = EnemyAmmoOntheField.begin();
			Mark != EnemyAmmoOntheField.end();) {
			if (Mark->ReferEOA())
				Mark = EnemyAmmoOntheField.erase(Mark);
			else
				Mark++;
			if (EnemyAmmoOntheField.empty())
				break;
		}

		/*�G�̑ł����ޔ���*/
		if(!EnemyShips.empty()){
			for (auto Mark = EnemyShips.begin();
				Mark != EnemyShips.end(); Mark++) {
				if (!Mark->ReferWait())
					continue;
				for (int i = 0; i < Mark->ReferCCount(); ++i) {
					if (MyShip.Crash(Mark->ReferRCollisionX(i),
						Mark->ReferRCollisionY(i),
						Mark->ReferCollisionR(i))) {
						if (rand() % 2 == 0)
							Mark->XChangeDirect();
						else
							Mark->YChangeDirect();
					}
				}
				for (auto BMark = EnemyShips.begin();
					BMark != EnemyShips.end(); BMark++) {
					if (!BMark->ReferWait())
						continue;
					if (BMark == Mark)
						continue;
					for (int i = 0; i < Mark->ReferCCount(); ++i) {
						if (Mark->Crash(BMark->ReferRCollisionX(i),
							BMark->ReferRCollisionY(i),
							BMark->ReferCollisionR(i))) {
							if (rand() % 2 == 0)
								Mark->XChangeDirect();
							else
								Mark->YChangeDirect();
						}
					}

				}
			}
		}

		if (!EnemyShips.empty())
			for (auto Mark = EnemyShips.begin();
				Mark != EnemyShips.end(); Mark++) {
			if (!Mark->ReferWait())
				continue;
			for (int i = 0; i < MPO.ReferColCount(); ++i) {
				if (Mark->Crash(MPO.ReferColRX(i), MPO.ReferColRY(i),
					MPO.ReferColR(i))) {
					if (rand() % 2 == 0)
						Mark->XChangeDirect();
					else
						Mark->YChangeDirect();
				}
			}
		}

		/*�ł����ޔ���*/
		MyShip.Move(true);
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
					goto Outline;//�e�X�g�p
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

		/*�J�����ʒu�����*/
		MainCamera.GetPos(MyShip.ReferCoordX(), MyShip.ReferCoordY());
		UI.ReadHPandMaxHP(MyShip.ReferHP(), MyShip.ReferMaxHP());
		/********************/

		/*�A�o�֐�*/
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		/*�}�b�v�`��*/
		DrawRectGraph(0, 0, (int)(MainCamera.ReferPSX()),
			(int)(MainCamera.ReferPSY())
			, SCREEN_X, SCREEN_Y, MapHandle, FALSE, FALSE);
		MPO.Show(MainCamera.ReferPSX(), MainCamera.ReferPSY());
		/*�D�`��*/
		MyShip.Draw(MainCamera.ReferCameraX(), MainCamera.ReferCameraY(),true);
		if (!EnemyShips.empty()) {
			for (auto Mark = EnemyShips.begin();
				Mark != EnemyShips.end();Mark++)
				Mark->Draw(MainCamera.ReferPSX(), MainCamera.ReferPSY(), false);

		}
		/*�e�`��*/
		if (!AmmoOntheField.empty())
			for (auto itr = AmmoOntheField.begin(); itr != AmmoOntheField.end();
				itr++) {
			itr->Show(MainCamera.ReferPSX(), MainCamera.ReferPSY());
		}
		if (!EnemyAmmoOntheField.empty())
			for (auto itr = EnemyAmmoOntheField.begin(); 
				itr != EnemyAmmoOntheField.end();
				itr++) {
			itr->Show(MainCamera.ReferPSX(), MainCamera.ReferPSY());
		}
		/*UI�`��*/
		UI.Show(MyShip.ReferRadian());
		char str[25];
		_itoa_s(EnemyKilled, str, 10);
		unsigned int Cr = GetColor(255, 0, 0);
		DrawString(20, 60, str, Cr);
		if (MyShip.ReferHP() <= 0) {
			DrawString(SCREEN_X / 2, SCREEN_Y / 2,
				"GAME OVER", Cr);
		}
		/********************/
		ScreenFlip();

		if (MyShip.ReferHP() <= 0) {
			rewind(stdin);
			WaitKey();
			break;
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
	/*���������*/
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
	/*���I���������*/
	for (int i = 0; i < 6; ++i)
		delete Alfa[i];

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();

	return 0;            // �\�t�g�̏I��
}
