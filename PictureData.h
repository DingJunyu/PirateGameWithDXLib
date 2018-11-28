#pragma once
#define ALLIES_SHIP_COUNT 1
#define ENEMIES_SHIP_COUNT 1
#define AMMO_TYPE 1

/*���̃N���X�͉摜�f�[�^��ۊǂ���N���X�ł�*/
class PictureData
{
public:
	PictureData();
	~PictureData();

	/*�������֐�*/
	void AllInif();

	/*�₢���킹�֐�*/
	/*�D*/
	int *ReferAlliesShipHandle(int x) { return AlliesShipsHandle[x]; }
	int *ReferAlliesShipSinkHandle(int x)
	{
		return AlliesShipsSinkHandle[x];
	}
	int ReferAlliesShipShadowHandle(int x)
	{
		return AlliesShipShadowHandle[x];
	}
	int *ReferEnemyShipHandle(int x) { return EnemyShipsHandle[x]; }
	int *ReferEnemyShipsSinkHandle(int x)
	{
		return EnemyShipsSinkHandle[x];
	}
	int ReferEnemyShipsShadowHandle(int x)
	{
		return EnemyShipShadowHandle[x];
	}
	int ReferShipX() { return ShipX; }
	int ReferShipY() { return ShipY; }

	/*�}�b�v*/
	int ReferMap(int x) { return MapHandle[x]; }
	int ReferMapX(int x) { return MapX[x]; }
	int ReferMapY(int x) { return MapY[x]; }

	/*�e*/
	int ReferAmmo(int x) { return AmmoHandle[x]; }
	int ReferAmmoX(int x) { return AmmoX[x]; }
	int ReferAmmoY(int x) { return AmmoY[x]; }


private:
	/*�D�f�[�^*/
	/*�n���h��*/
	int **AlliesShipsHandle;
	int **AlliesShipsSinkHandle;
	int *AlliesShipShadowHandle;
	int **EnemyShipsHandle;
	int **EnemyShipsSinkHandle;
	int *EnemyShipShadowHandle;
	/*�T�C�Y*/
	int ShipX;
	int ShipY;
	/****************************/

	/*�}�b�v�f�[�^*/
	/*�n���h��*/
	int *MapHandle;
	/*�T�C�Y*/
	int *MapX;
	int *MapY;
	/****************************/

	/*�e�f�[�^*/
	/*�n���h��*/
	int *AmmoHandle;
	/*�T�C�Y*/
	int *AmmoX;
	int *AmmoY;
	/****************************/

	/*UI�f�[�^*/
	/*HP�o�[*/
	int *HPBarHandle;
	int HPBX;
	int HPBY;
	/*��*/
	int SWHandle;
	int SWX;
	int SWY;
	/*�X�s�[�g����*/
	/*�w�i*/
	int SpeedControlHandle;
	int SCX;
	int SCY;
	/*�}�[�J�[*/
	int SpeedControlMarkHandle;
	int SCMX;
	int SCMY;
	/****************************/
};

