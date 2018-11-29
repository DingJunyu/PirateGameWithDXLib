#pragma once
#include"DxLib.h"
#include"MathDefine.h"
#include"ShipUniversal.h"
#include"Weapon.h"
#include"UserInterface.h"
#include"Camera.h"
#include"Controller.h"
#include"MapObject.h"
#include"PictureData.h"
#include"GameControl.h"
#include"SingleGameControl.h"
#include"MainGameProgress.h"
#include"GraphicControl.h"
#include"FrameControl.h"

#include<list>
#include<cmath>
#include<vector>
#include<time.h>
#include<string>
#include<sstream>
#include<stdlib.h>


void GameMain();
void SingleGameMain(Controller *Control);
ShipUniversal PutInAnEnemy(int *ESH,int *ESShadowH,
	int *ESSinkH,int ShipX,int ShipY, Weapon *Alfa);