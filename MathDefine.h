#pragma once
#define PI 3.1415926535897932384626 //円周率

/*マップはスクリームの倍数にならないといかない*/
#define BOARDER_X 1920 //X座標の限界
#define BOARDER_Y 1440 //Y座標の限界
#define SCREEN_X 640 //スクリームX限界
#define SCREEN_Y 480 //スクリームY限界
#define OUTLINE 5 //辺境範囲

enum WEAPON_TYPE { A = 101, B, C, D };

#define ZOOM_MULTIPLE 0.5