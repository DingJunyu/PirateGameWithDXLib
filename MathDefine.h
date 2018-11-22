#pragma once
#define PI 3.1415926535897932384626 //�~����

/*�}�b�v�̓X�N���[���̔{���ɂȂ�Ȃ��Ƃ����Ȃ�*/
#define BOARDER_X 1920 //X���W�̌��E
#define BOARDER_Y 1080 //Y���W�̌��E
#define SCREEN_X 1024 //�X�N���[��X���E
#define SCREEN_Y 768 //�X�N���[��Y���E
#define OUTLINE 15 //�Ӌ��͈�

enum WEAPON_TYPE { A = 101, B, C, D };

enum COLLISION {
	COORD_X = 0, COORD_Y, RADIUS,
	REAL_COORD_X, REAL_COORD_Y
};

enum GEAR_ {
	FULL_SPEED = 1, THREE_QUARTER, HALF_SPEED, A_QUARTER,
	STOP, BACK_UP
};
/*1:�S��
2:3/4��
3:1/2��
4:1/4��
5:���
6:1/4�����*/
const int TURN_WHEN_INPUT = 64;
const double FULL_SPEED_RATE = 1.0;
const double THREE_QUARTER_RATE = 0.75;
const double HALF_SPEED_RATE = 0.5;
const double A_QUARTER_RATE = 0.25;
const double STOP_RATE = 0;
const double BACK_UP_RATE = -0.25;

enum QUADRANT { UL = 0, UR, LR, LL };


#define ZOOM_MULTIPLE 0.5

#define WEAPON_TYPE_NUMBER 6

#define SHADOW_X 4
#define SHADOW_Y 4

#define AMMO_LENGTH 15