#pragma once
#define PI 3.1415926535897932384626 //円周率

/*マップはスクリームの倍数にならないといかない*/
#define BOARDER_X 1920 //X座標の限界
#define BOARDER_Y 1080 //Y座標の限界
#define SCREEN_X 1024 //スクリームX限界
#define SCREEN_Y 768 //スクリームY限界
#define OUTLINE 15 //辺境範囲

enum WEAPON_TYPE { A = 101, B, C, D };

enum COLLISION {
	COORD_X = 0, COORD_Y, RADIUS,
	REAL_COORD_X, REAL_COORD_Y
};

enum GEAR_ {
	FULL_SPEED = 1, THREE_QUARTER, HALF_SPEED, A_QUARTER,
	STOP, BACK_UP
};
/*1:全速
2:3/4速
3:1/2速
4:1/4速
5:停車
6:1/4速後退*/
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