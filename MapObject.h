#pragma once
#include"MathDefine.h"
#include<stdlib.h>
#include<stdio.h>
#include<cmath>
#include"DxLib.h"

class MapObject
{
public:
	MapObject(int CoCount, int *Hdle) :CollisionCount(CoCount),
		MapHandle(Hdle)
	{
		for (int i = 0; i < CollisionCount; ++i)
			Collision[i] = new double[5];
	}
	~MapObject();

	/*使い終わったら必ず使う！！！！！！！！！！！*/
	void FreeMemory();

	/*中身変更関数*/
	void ReadCollision(FILE *FLPointer);
	void Cal();
	void Show(double X, double Y);

	/*テスト用関数*/
	void TEST();

	/*問い合わせ関数*/
	int ReferColCount() { return CollisionCount; }
	double ReferColR(int i) { return Collision[i][2]; }
	double ReferColRX(int i) { return Collision[i][3]; }
	double ReferColRY(int i) { return Collision[i][4]; }
	bool ReferUsable();

private:
	const int *MapHandle; 
	int Width, Length;
	double CoordX;
	double CoordY;
	double Radian;
	double SinSaved;
	double CosSaved;

	const int CollisionCount;//円の数
	double **Collision = new double*[CollisionCount];
	//円のX座標、Y座標、半径、相対X座標、相対Y座標
};

